#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/VLQCandProducer.h"
#include<algorithm>

VLQCandProducer::VLQCandProducer (edm::ParameterSet const&  pset) :
  l_tjets       (pset.getParameter<edm::InputTag> ("tjetsLabel")),
  l_wjets       (pset.getParameter<edm::InputTag> ("wjetsLabel")),
  l_bjets       (pset.getParameter<edm::InputTag> ("bjetsLabel")),
  l_jets        (pset.getParameter<edm::InputTag> ("jetsLabel")),
  l_zll         (pset.getParameter<edm::InputTag> ("zllLabel")),
  mass_t_      (pset.getParameter<double>("mass_t")), 
  mass_w_      (pset.getParameter<double>("mass_w")), 
  mass_z_      (pset.getParameter<double>("mass_z")), 
  sigma_t_      (pset.getParameter<double>("sigma_t")), 
  sigma_w_      (pset.getParameter<double>("sigma_w")), 
  sigma_z_      (pset.getParameter<double>("sigma_z")), 
  sigma_hadvlq_ (pset.getParameter<double>("sigma_hadvlq")), 
  sigma_lepvlq_ (pset.getParameter<double>("sigma_lepvlq"))  
{ 
  vquarks_.clear() ; 
}

VLQCandProducer::~VLQCandProducer () {
  vquarks_.clear() ; 
}

bool VLQCandProducer::filter(edm::Event& evt, const edm::EventSetup& iSetup) {

  Handle<vlq::JetCollection>       h_tjets ; evt.getByLabel(l_tjets, h_tjets) ; 
  Handle<vlq::JetCollection>       h_wjets ; evt.getByLabel(l_wjets, h_wjets) ; 
  Handle<vlq::JetCollection>       h_bjets ; evt.getByLabel(l_bjets, h_bjets) ; 
  Handle<vlq::JetCollection>       h_jets  ; evt.getByLabel(l_jets , h_jets ) ; 
  Handle<vlq::CandidateCollection> h_zll   ; evt.getByLabel(l_zll  , h_zll  ) ; 

  vlq::JetCollection tjets(*h_tjets) ; 
  vlq::JetCollection wjets(*h_wjets) ; 
  vlq::JetCollection bjets(*h_bjets) ; 


  int njets( 6 ) ; //  - 2*( (h_tjets.product())->size() + (h_wjets.product())->size() ) ) ;
  vlq::JetCollection jets(njets) ; 
  std::copy_n((h_jets.product())->begin(), njets, jets.begin()) ;

  if (jets.size() < 6 || bjets.size() < 2) return false ; 

  vlq::Candidate zllcand( (h_zll.product())->at(0)) ; 

  std::vector<double> v_chi2 ; 
  std::vector<TLorentzVector> v_p4lepvlq, v_p4hadvlq ; 

  do {

    vlq::Jet jet0(jets.at(0)) ; 
    vlq::Jet jet1(jets.at(1)) ; 
    vlq::Jet jet2(jets.at(2)) ; 
    vlq::Jet jet3(jets.at(3)) ; 
    vlq::Jet jet4(jets.at(4)) ; 
    vlq::Jet jet5(jets.at(5)) ; 

    TLorentzVector p4_w0 = jet0.getP4()+jet1.getP4() ;
    TLorentzVector p4_w1 = jet2.getP4()+jet3.getP4() ;
    TLorentzVector p4_w2 = jet4.getP4()+jet5.getP4() ;

    double chi2_w0 = pow( (p4_w0.Mag() - mass_w_)/sigma_w_, 2.0); 
    double chi2_w1 = pow( (p4_w1.Mag() - mass_w_)/sigma_w_, 2.0); 
    double chi2_w2 = pow( (p4_w2.Mag() - mass_w_)/sigma_w_, 2.0); 

    do {

      vlq::Jet bjet0(bjets.at(0)) ; 
      vlq::Jet bjet1(bjets.at(1)) ; 
      TLorentzVector p4_t0 = p4_w0+bjet0.getP4() ; 
      TLorentzVector p4_t1 = p4_w1+bjet1.getP4() ;

      double chi2_t0 = pow( (p4_t0.Mag() - mass_t_)/sigma_t_, 2.0);
      double chi2_t1 = pow( (p4_t1.Mag() - mass_t_)/sigma_t_, 2.0);

      TLorentzVector p4_T0 = p4_t0 + zllcand.getP4();
      TLorentzVector p4_T1 = p4_t1 + p4_w2  ;

      double chi2_T0 = pow( (p4_T0.Mag() - 800)/sigma_lepvlq_, 2.0) ; 
      double chi2_T1 = pow( (p4_T1.Mag() - 800)/sigma_hadvlq_, 2.0) ; 

      double chi2 = chi2_w0 + chi2_w1 + chi2_w2 + chi2_t0 + chi2_t1 + chi2_T0 + chi2_T1 ; 

      v_chi2.push_back(chi2) ; 
      v_p4lepvlq.push_back(p4_T0) ; 
      v_p4hadvlq.push_back(p4_T1) ; 

    }
    while ( std::next_permutation(bjets.begin(), bjets.end(), compareByPt())) ; 


  }
  while ( std::next_permutation(jets.begin(), jets.end(), compareByPt()) ) ; 

  if (v_chi2.size() == 0) return false ; 

  std::vector<double>::iterator smallest_chi_at = std::min_element(std::begin(v_chi2), std::end(v_chi2));
  std::cout << " Min chi2 is at : " << std::distance(std::begin(v_chi2), smallest_chi_at) << " of value " << *smallest_chi_at << std::endl ;

  std::cout << " Mass of leptonic VLQ is " << v_p4lepvlq.at(std::distance(std::begin(v_chi2), smallest_chi_at)).Mag() 
    << " and hadronic VLQ is " <<  v_p4hadvlq.at(std::distance(std::begin(v_chi2), smallest_chi_at)).Mag() << std::endl ; 

  h1_["mass_Tlep"] -> Fill(v_p4lepvlq.at(std::distance(std::begin(v_chi2), smallest_chi_at)).Mag() ) ; 
  h1_["mass_Thad"] -> Fill(v_p4hadvlq.at(std::distance(std::begin(v_chi2), smallest_chi_at)).Mag()) ;  

  return true; 

}
void VLQCandProducer::beginJob() {
  h1_["mass_Tlep"] = fs->make<TH1D>("mass_Tlep", ";M(T quark) [GeV];;" ,100 ,0., 2000.) ; 
  h1_["mass_Thad"] = fs->make<TH1D>("mass_Thad", ";M(T quark) [GeV];;" ,100 ,0., 2000.) ; 
  return ; 
}

void VLQCandProducer::endJob() {
  return ; 
}

DEFINE_FWK_MODULE(VLQCandProducer);
