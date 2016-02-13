#include <iostream>
#include <memory>
#include <vector>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/HH4bTree.h"
#include <TH1D.h>
#include <TTree.h>
#include <TF1.h>

class HH4b : public edm::EDFilter {
  public:
    explicit HH4b(const edm::ParameterSet&) ;
    ~HH4b() ; 
  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    bool passHiggsTagging(vlq::Jet jet) ; 
    double getBTagEff_CSVv2L (double pt, double hadFl) ; 
    double getBTagSF_CSVv2L (double pt, double hadFl, double err_bc, double err_l) ; 

    // ----------member data ---------------------------
    edm::InputTag l_evtwtGen                     ;
    edm::InputTag l_evtwtPV                      ;
    edm::InputTag l_partonBin                    ;
    edm::InputTag l_hltdecision                  ;
    edm::InputTag l_npv                          ;
    JetMaker     jetAK8maker                     ; 
    JetMaker     jetHTaggedmaker                 ; 
    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    EventInfoBranches selectedevt; 
    JetInfoBranches ak8jets ; 
    JetInfoBranches hjets ; 
    TTree* tree_ ; 
};

using namespace std; 

template <typename T>
struct iterator_extractor { typedef typename T::iterator type; };

template <typename T>
struct iterator_extractor<T const> { typedef typename T::const_iterator type; };


template <typename T>
class Indexer {
  public:
    class iterator {
      typedef typename iterator_extractor<T>::type inner_iterator;

      typedef typename std::iterator_traits<inner_iterator>::reference inner_reference;
      public:
      typedef std::pair<size_t, inner_reference> reference;

      iterator(inner_iterator it): _pos(0), _it(it) {}

      reference operator*() const { return reference(_pos, *_it); }

      iterator& operator++() { ++_pos; ++_it; return *this; }
      iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }

      bool operator==(iterator const& it) const { return _it == it._it; }
      bool operator!=(iterator const& it) const { return !(*this == it); }

      private:
      size_t _pos;
      inner_iterator _it;
    };

    Indexer(T& t): _container(t) {}

    iterator begin() const { return iterator(_container.begin()); }
    iterator end() const { return iterator(_container.end()); }

  private:
    T& _container;
}; // class Indexer

template <typename T>
Indexer<T> index(T& t) { return Indexer<T>(t); }

HH4b::HH4b(const edm::ParameterSet& iConfig) :
  l_evtwtGen              (iConfig.getParameter<edm::InputTag>     ("evtwtGen")),
  l_evtwtPV               (iConfig.getParameter<edm::InputTag>     ("evtwtPV")),
  l_partonBin             (iConfig.getParameter<edm::InputTag>     ("partonBin")),
  l_hltdecision           (iConfig.getParameter<edm::InputTag>     ("hltdecision")),
  l_npv                   (iConfig.getParameter<edm::InputTag>     ("npv")),
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams"))   
{
}

HH4b::~HH4b() {}

bool HH4b::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<double>  h_evtwtGen   ; evt.getByLabel(l_evtwtGen   , h_evtwtGen   ) ; 
  Handle<double>  h_evtwtPV    ; evt.getByLabel(l_evtwtPV    , h_evtwtPV    ) ; 
  Handle<double>  h_partonBin  ; evt.getByLabel(l_partonBin  , h_partonBin  ) ; 
  Handle<bool>    h_hltdecision; evt.getByLabel(l_hltdecision, h_hltdecision) ; 
  Handle<unsigned>h_npv        ; evt.getByLabel(l_npv        , h_npv        ) ; 

  const double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 
  const double partonBin((*h_partonBin.product())) ; 
  const bool hltdecision(*h_hltdecision.product()) ; 
  const unsigned npv(*h_npv.product()) ; 

  vlq::JetCollection  goodAK8Jets ;  
  jetAK8maker(evt, goodAK8Jets); 

  double cosThetaStar(goodAK8Jets.size()>=2 ? abs(goodAK8Jets.at(0).getEta() -  goodAK8Jets.at(1).getEta()) : 999999) ; 
  TLorentzVector p4null; p4null.SetPtEtaPhiE(0,0,0,0); 
  TLorentzVector p4_jet0 = goodAK8Jets.size()>=1 ? goodAK8Jets.at(0).getP4() : p4null ;
  TLorentzVector p4_jet1 = goodAK8Jets.size()>=2 ? goodAK8Jets.at(1).getP4() : p4null ;
  double invm(goodAK8Jets.size()>=2 ? (p4_jet0 + p4_jet1).Mag() : -999999) ; 
  double mj_0(goodAK8Jets.size()>=2 ? goodAK8Jets.at(0).getPrunedMass() : -999999) ;
  double mj_1(goodAK8Jets.size()>=2 ? goodAK8Jets.at(1).getPrunedMass() : -999999) ;
  double t21_0(goodAK8Jets.size()>=2 ? 
      ( goodAK8Jets.at(0).getTau1() != 0 ? goodAK8Jets.at(0).getTau2() / goodAK8Jets.at(0).getTau1() : 999999 ) 
      : 999999) ; 
  double t21_1(goodAK8Jets.size()>=2 ? 
      ( goodAK8Jets.at(1).getTau1() != 0 ? goodAK8Jets.at(1).getTau2() / goodAK8Jets.at(1).getTau1() : 999999 ) 
      : 999999) ; 
  int nsjBTagged(goodAK8Jets.size()>=2 ? 
      goodAK8Jets.at(0).getNSubjetsBTaggedCSVL() + goodAK8Jets.at(1).getNSubjetsBTaggedCSVL() : -999999 ) ; 

  //// Event flags for cut flows
  const bool hltNPV   (hltdecision && (npv > 0)) ; 
  const bool ak8Pt    (goodAK8Jets.size()>=2) ; 
  const bool ak8eta   (goodAK8Jets.size()>=2 && ( abs(goodAK8Jets.at(0).getEta()) <= 2.4 && abs(goodAK8Jets.at(1).getEta()) <= 2.4) ); 
  const bool ak8DEta  (cosThetaStar < 1.3);
  const bool ak8Mjj   (invm > 1000.);
  const bool ak8Mj    ((mj_0 >= 105 && mj_0 <= 135) && (mj_1 >= 105 && mj_1 <= 135) ) ; 
  const bool ak8t21   ((t21_0 < 0.75 && t21_1 < 0.75) && (t21_0 < 0.6 || t21_1 < 0.6)); 
  const bool evt0b    (nsjBTagged == 0) ; 
  const bool evt1b    (nsjBTagged == 1) ; 
  const bool evt2b    (nsjBTagged == 2) ; 
  const bool evt3b    (nsjBTagged == 3) ; 
  const bool evt4b    (nsjBTagged == 4) ; 
  const bool evt3bHPHP(nsjBTagged == 3 && (t21_0 < 0.6 && t21_1 < 0.6));

  //// Cut flow
  h1_["cutflow"] -> Fill(1) ; 
  if ( hltNPV  ) h1_["cutflow"] -> Fill(2) ; 
  if ( hltNPV && ak8Pt  ) h1_["cutflow"] -> Fill(3) ; 
  if ( hltNPV && ak8Pt && ak8eta  ) h1_["cutflow"] -> Fill(4) ; 
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta ) h1_["cutflow"] -> Fill(5) ; 
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj  ) h1_["cutflow"] -> Fill(6) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj  ) h1_["cutflow"] -> Fill(7) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21  ) h1_["cutflow"] -> Fill(8) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt0b  ) h1_["cutflow"] -> Fill( 9) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt1b  ) h1_["cutflow"] -> Fill(10) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt2b  ) h1_["cutflow"] -> Fill(11) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt3b  ) h1_["cutflow"] -> Fill(12) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt4b  ) h1_["cutflow"] -> Fill(13) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt3bHPHP) h1_["cutflow"] -> Fill(14) ;


  //// Event selection
  if ( !hltNPV || !ak8Pt ) return false; 

  h1_["npv"] -> Fill(*h_npv.product()); 

  //// Leading 2 jets pass Higgs tagging
  if ( !passHiggsTagging(goodAK8Jets.at(0)) || !passHiggsTagging(goodAK8Jets.at(1)) ) return false ;

  vlq::JetCollection goodHTaggedJets ;
  goodHTaggedJets.push_back(goodAK8Jets.at(0)); 
  goodHTaggedJets.push_back(goodAK8Jets.at(1)); 

  //for (auto ijet : index(goodAK8Jets) ) {
  //  ak8jets.Index[ijet.first] = (ijet.second).getIndex() ;
  //  ak8jets.ParentIndex[ijet.first] = -1 ;
  //  ak8jets.Pt[ijet.first] = (ijet.second).getPt() ;
  //  ak8jets.Eta[ijet.first] = (ijet.second).getEta() ;
  //  ak8jets.Phi[ijet.first] = (ijet.second).getPhi() ;
  //  ak8jets.Mass[ijet.first] = (ijet.second).getMass() ;
  //  ak8jets.MassPruned[ijet.first] = (ijet.second).getPrunedMass() ;
  //  ak8jets.MassSoftDrop[ijet.first] = (ijet.second).getSoftDropMass() ;
  //  ak8jets.tau1[ijet.first] = (ijet.second).getTau1() ;
  //  ak8jets.tau2[ijet.first] = (ijet.second).getTau2() ;
  //  ak8jets.tau3[ijet.first] = (ijet.second).getTau3() ;
  //  ak8jets.hadFlavour[ijet.first] = (ijet.second).getHadronFlavour() ;
  //  ak8jets.CSVIVFv2[ijet.first] = (ijet.second).getCSV() ;
  //  ak8jets.nhf[ijet.first] = (ijet.second).getNHF() ;
  //  ak8jets.chf[ijet.first] = (ijet.second).getCHF() ;
  //  ak8jets.emf[ijet.first] = (ijet.second).getEMF() ;
  //  ak8jets.phf[ijet.first] = (ijet.second).getPHF() ;
  //  ak8jets.muf[ijet.first] = (ijet.second).getMUF() ;
  //  ak8jets.nconsts[ijet.first] = (ijet.second).getNConsts() ;
  //  ak8jets.groomedMassCorr[ijet.first] = (ijet.second).getGroomedMassCorr() ;
  //  ak8jets.nsubjets[ijet.first] = (ijet.second).getNSubjets() ;
  //  ak8jets.nsubjetsBTaggedCSVL[ijet.first] = (ijet.second).getNSubjetsBTaggedCSVL() ;
  //  ak8jets.hadFlavourSubjet0[ijet.first] = (ijet.second).getHadronFlavourSubjet0() ;
  //  ak8jets.hadFlavourSubjet1[ijet.first] = (ijet.second).getHadronFlavourSubjet1() ;
  //  ak8jets.ptSubjet0[ijet.first] = (ijet.second).getPtSubjet0() ;
  //  ak8jets.ptSubjet1[ijet.first] = (ijet.second).getPtSubjet1() ;
  //  ak8jets.etaSubjet0[ijet.first] = (ijet.second).getEtaSubjet0() ;
  //  ak8jets.etaSubjet1[ijet.first] = (ijet.second).getEtaSubjet1() ;
  //  ak8jets.csvSubjet0[ijet.first] = (ijet.second).getCSVSubjet0() ;
  //  ak8jets.csvSubjet1[ijet.first] = (ijet.second).getCSVSubjet1() ;
  //}

  double btagsf(1) ;
  double btagsf_bcUp(1) ; 
  double btagsf_bcDown(1) ; 
  double btagsf_lUp(1) ; 
  double btagsf_lDown(1) ; 

  //if (goodHTaggedJets.size() >= 2) { 

    TLorentzVector p4_hjet0 = goodHTaggedJets.at(0).getP4() ; 
    TLorentzVector p4_hjet1 = goodHTaggedJets.at(1).getP4() ; 
    TLorentzVector p4_leading2hjets = p4_hjet0+p4_hjet1 ;

    selectedevt.deta_leading2hjets_ = cosThetaStar ; 
    selectedevt.minv_leading2hjets_ = p4_leading2hjets.Mag();
    selectedevt.minv_leading2hjets_subtr_ = p4_leading2hjets.Mag() - (goodHTaggedJets.at(0).getMass() - 125.) - (goodHTaggedJets.at(1).getMass() -125.);
    selectedevt.pt_leading2hjets_ = p4_leading2hjets.Pt();
    selectedevt.eta_leading2hjets_ = p4_leading2hjets.Eta();
    selectedevt.y_leading2hjets_ = p4_leading2hjets.Rapidity();
    selectedevt.phi_leading2hjets_ = p4_leading2hjets.Phi();

    selectedevt.nsubjetsBTaggedCSVL_ = 0 ;

    hjets.njets = goodHTaggedJets.size() ; 
    for (auto ijet : index(goodHTaggedJets) ) {
      hjets.Index[ijet.first] = (ijet.second).getIndex() ;
      hjets.ParentIndex[ijet.first] = -1 ;
      hjets.Pt[ijet.first] = (ijet.second).getPt() ;
      hjets.Eta[ijet.first] = (ijet.second).getEta() ;
      hjets.Phi[ijet.first] = (ijet.second).getPhi() ;
      hjets.Mass[ijet.first] = (ijet.second).getMass() ;
      hjets.MassPruned[ijet.first] = (ijet.second).getPrunedMass() ;
      hjets.MassSoftDrop[ijet.first] = (ijet.second).getSoftDropMass() ;
      hjets.tau1[ijet.first] = (ijet.second).getTau1() ;
      hjets.tau2[ijet.first] = (ijet.second).getTau2() ;
      hjets.tau3[ijet.first] = (ijet.second).getTau3() ;
      hjets.hadFlavour[ijet.first] = (ijet.second).getHadronFlavour() ;
      hjets.CSVIVFv2[ijet.first] = (ijet.second).getCSV() ;
      hjets.nhf[ijet.first] = (ijet.second).getNHF() ;
      hjets.chf[ijet.first] = (ijet.second).getCHF() ;
      hjets.emf[ijet.first] = (ijet.second).getEMF() ;
      hjets.phf[ijet.first] = (ijet.second).getPHF() ;
      hjets.muf[ijet.first] = (ijet.second).getMUF() ;
      hjets.nconsts[ijet.first] = (ijet.second).getNConsts() ;
      hjets.groomedMassCorr[ijet.first] = (ijet.second).getGroomedMassCorr() ;
      hjets.nsubjets[ijet.first] = (ijet.second).getNSubjets() ;
      hjets.nsubjetsBTaggedCSVL[ijet.first] = (ijet.second).getNSubjetsBTaggedCSVL() ;
      selectedevt.nsubjetsBTaggedCSVL_  += (ijet.second).getNSubjetsBTaggedCSVL() ;  
      hjets.hadFlavourSubjet0[ijet.first] = (ijet.second).getHadronFlavourSubjet0() ;
      hjets.hadFlavourSubjet1[ijet.first] = (ijet.second).getHadronFlavourSubjet1() ;
      hjets.ptSubjet0[ijet.first] = (ijet.second).getPtSubjet0() ;
      hjets.ptSubjet1[ijet.first] = (ijet.second).getPtSubjet1() ;
      hjets.etaSubjet0[ijet.first] = (ijet.second).getEtaSubjet0() ;
      hjets.etaSubjet1[ijet.first] = (ijet.second).getEtaSubjet1() ;
      hjets.csvSubjet0[ijet.first] = (ijet.second).getCSVSubjet0() ;
      hjets.csvSubjet1[ijet.first] = (ijet.second).getCSVSubjet1() ;

      //// Get b-tag SF weight
      //// Get btag SFs
      if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf *= getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,0) ; 
      else btagsf *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,0)*getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
      if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf *= getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,0) ; 
      else btagsf *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,0)*getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 


      //// Get btag SF up bc err
      if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_bcUp *= getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),1,0) ; 
      else btagsf_bcUp *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),1,0)*getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
      if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_bcUp *= getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),1,0) ; 
      else btagsf_bcUp *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),1,0)*getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 


      if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_bcDown *= getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),-1,0) ; 
      else btagsf_bcDown *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),-1,0)*getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
      if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_bcDown *= getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),-1,0) ; 
      else btagsf_bcDown *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),-1,0)*getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 

      //// Get btag SF up light err
      if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_lUp *= getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,1) ; 
      else btagsf_lUp *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,1)*getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
      if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_lUp *= getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,1) ; 
      else btagsf_lUp *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,1)*getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 


      if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_lDown *= getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,-1) ; 
      else btagsf_lDown *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,-1)*getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
      if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_lDown *= getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,-1) ; 
      else btagsf_lDown *= ( 1 - getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,-1)*getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 

    } /// Loop over all Higgs jets

  //} //// If N(H jets) >= 2

  selectedevt.partonBin_ = partonBin ; 
  selectedevt.evtwt_ = evtwt ; 
  selectedevt.btagsf_ = btagsf;
  selectedevt.btagsf_bcUp_ = btagsf_bcUp ; 
  selectedevt.btagsf_bcDown_ = btagsf_bcDown ; 
  selectedevt.btagsf_lUp_ = btagsf_lUp ; 
  selectedevt.btagsf_lDown_ = btagsf_lDown ; 

  tree_->Fill();

  return true ; 
}

bool HH4b::passHiggsTagging(vlq::Jet jet) {
  bool passHiggsTagging(0);
  if (jet.getPt() > 200. 
      && abs(jet.getEta() <= 2.4)
      && abs(jet.getPrunedMass()) >= 90 
      && (jet.getTau1() == 0. || jet.getTau2()/jet.getTau1() < 0.75)
     ) passHiggsTagging = true ; 
  return passHiggsTagging;
}

double HH4b::getBTagEff_CSVv2L (double pt, double jetFl) {
  double eff(1) ; 
  if (jetFl == 5) eff = 0.8 ; 
  else if (jetFl == 4) eff = 0.3 ; 
  else if (jetFl == 0) eff = 0.1 ; 
  return eff ;
}

double HH4b::getBTagSF_CSVv2L (double pt, double jetFl, double errbc, double errl) {
  double btagsf(1);

  TF1* SFb_CSVv2L = new TF1("SFb_CSVv2L", "0.908299+(2.70877e-06*(log(x+370.144)*(log(x+370.144)*(3-(-(104.614*log(x+370.144)))))))",0,2000) ;

  std::map<std::pair<double,double>,double> SFb_CSVv2L_err = { 
    {std::make_pair(30,50)  , 0.022327613085508347}, 
    {std::make_pair(50,70)  , 0.015330483205616474}, 
    {std::make_pair(70,100) , 0.024493992328643799}, 
    {std::make_pair(100,140), 0.020933238789439201}, 
    {std::make_pair(140,200), 0.029219608753919601}, 
    {std::make_pair(200,300), 0.039571482688188553}, 
    {std::make_pair(300,670), 0.047329759448766708}  
  } ;

  TF1* SFc_CSVv2L = new TF1("SFc_CSVv2L", "0.908299+(2.70877e-06*(log(x+370.144)*(log(x+370.144)*(3-(-(104.614*log(x+370.144)))))))",0,2000) ;

  std::map<std::pair<double,double>,double> SFc_CSVv2L_err = { 
    {std::make_pair(30,50)  , 0.044655226171016693}, 
    {std::make_pair(50,70)  , 0.030660966411232948}, 
    {std::make_pair(70,100) , 0.048987984657287598}, 
    {std::make_pair(100,140), 0.041866477578878403}, 
    {std::make_pair(140,200), 0.058439217507839203}, 
    {std::make_pair(200,300), 0.079142965376377106}, 
    {std::make_pair(300,670), 0.094659518897533417}  
  } ;

  TF1* SFl_CSVv2L = new TF1("SFl_CSVv2L", "((1.07278+(0.000535714*x))+(-1.14886e-06*(x*x)))+(7.0636e-10*(x*(x*x)))",0,2000) ;
  TF1* SFl_CSVv2L_errUp = new TF1("SFl_CSVv2L_errUp", "((1.12921+(0.000804962*x))+(-1.87332e-06*(x*x)))+(1.18864e-09*(x*(x*x)))",0,2000) ; 
  TF1* SFl_CSVv2L_errDown = new TF1("SFl_CSVv2L_errDown", "((1.01637+(0.000265653*x))+(-4.22531e-07*(x*x)))+(2.23396e-10*(x*(x*x)))",0,2000) ;

  double errb(0), errc(0) ; 
  for ( auto const& ent : SFb_CSVv2L_err ) if (pt >= (ent.first).first && pt < (ent.first).second ) errb = ent.second ; 
  for ( auto const& ent : SFc_CSVv2L_err ) if (pt >= (ent.first).first && pt < (ent.first).second ) errc = ent.second ; 

  if (jetFl == 5) btagsf = SFb_CSVv2L->Eval(pt) + errb*errbc; 
  else if (jetFl == 4) btagsf = SFc_CSVv2L->Eval(pt) + errc*errbc; 
  else if (jetFl == 0) btagsf = (
      SFl_CSVv2L->Eval(pt)*(1 - abs(errl)) + 
      (SFl_CSVv2L_errUp->Eval(pt)*abs(errl)*(1+errl)/2) + 
      (SFl_CSVv2L_errDown->Eval(pt)*abs(errl)*(1-errl)/2) ) ;  

  delete SFb_CSVv2L;
  delete SFl_CSVv2L ; 
  delete SFl_CSVv2L_errUp ; 
  delete SFl_CSVv2L_errDown ;

  return btagsf ; 
}

// ------------ method called once each job just before starting event loop  ------------
void HH4b::beginJob() {

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 14, 0.5, 14.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1,"All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2,"Trigger") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3 ,"p_{T}") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4,"|#eta|") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5,"|#Delta#eta|") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6,"M(jet_{0},jet(1))") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7,"M(jets)") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8,"#tau_{21}") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9,"0b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(10,"1b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(11,"2b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(12,"3b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(13,"4b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(14,"3b+HPHP") ; 

  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 
  tree_ = fs->make<TTree>("tree", "HH4b") ; 
  selectedevt.RegisterTree(tree_,"SelectedEvent") ; 
  //ak8jets.RegisterTree(tree_,"AK8Jets") ; 
  hjets.RegisterTree(tree_,"HJets") ; 

}

void HH4b::endJob() {

  return ; 
}

DEFINE_FWK_MODULE(HH4b);
