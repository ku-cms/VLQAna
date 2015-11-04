#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/VLQCandProducer.h"
#include<algorithm>

VLQCandProducer::VLQCandProducer (edm::ParameterSet const&  pset) :
  l_tjets       (pset.getParameter<edm::InputTag> ("tjetsLabel")),
  l_wjets       (pset.getParameter<edm::InputTag> ("wjetsLabel")),
  l_bjets       (pset.getParameter<edm::InputTag> ("bjetsLabel")),
  l_jets        (pset.getParameter<edm::InputTag> ("jetsLabel")),
  l_zll         (pset.getParameter<edm::InputTag> ("zllLabel")),
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

  int njets( 6 - 2*( (h_tjets.product())->size() + (h_wjets.product())->size() ) ) ;
  vlq::JetCollection jets(njets) ; 
  std::copy_n((h_jets.product())->begin(), njets, jets.begin()) ;

  vlq::Candidate zllcand( (h_zll.product())->at(0)) ; 

  do {

    for ( vlq::Jet jet : jets ) { 

      do {

        for ( vlq::Jet bjet : bjets ) { 
          std::cout << " jet pt " << jet.getPt() << " b jet pt " << bjet.getPt() << std::endl ; 
        }

      }
      while ( std::next_permutation(bjets.begin(), bjets.end(), compareByPt())) ; 

    }

  }
  while ( std::next_permutation(jets.begin(), jets.end(), compareByPt()) ) ; 

  return true; 

}
void VLQCandProducer::beginJob() {
  return ; 
}

void VLQCandProducer::endJob() {
  return ; 
}

DEFINE_FWK_MODULE(VLQCandProducer);
