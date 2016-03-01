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
#include "Analysis/VLQAna/interface/BTagSFUtils.h"
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

    // ----------member data ---------------------------
    edm::InputTag l_runno                        ;
    edm::InputTag l_lumisec                      ;
    edm::InputTag l_evtno                        ;
    edm::InputTag l_isData                       ;
    edm::InputTag l_evtwtGen                     ;
    edm::InputTag l_evtwtPV                      ;
    edm::InputTag l_evtwtPVLow                   ;
    edm::InputTag l_evtwtPVHigh                  ;
    edm::InputTag l_htHat                        ;
    edm::InputTag l_lhewtids                     ;
    edm::InputTag l_lhewts                       ;
    edm::InputTag l_hltdecision                  ;
    edm::InputTag l_npv                          ;
    edm::InputTag l_npuTrue                      ;
    JetMaker     jetAK8maker                     ; 
    JetMaker     jetHTaggedmaker                 ; 
    const std::string  btageffFile_              ;
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
  l_runno                 (iConfig.getParameter<edm::InputTag>     ("runno")),
  l_lumisec               (iConfig.getParameter<edm::InputTag>     ("lumisec")),
  l_evtno                 (iConfig.getParameter<edm::InputTag>     ("evtno")),
  l_isData                (iConfig.getParameter<edm::InputTag>     ("isData")),
  l_evtwtGen              (iConfig.getParameter<edm::InputTag>     ("evtwtGen")),
  l_evtwtPV               (iConfig.getParameter<edm::InputTag>     ("evtwtPV")),
  l_evtwtPVLow            (iConfig.getParameter<edm::InputTag>     ("evtwtPVLow")),
  l_evtwtPVHigh           (iConfig.getParameter<edm::InputTag>     ("evtwtPVHigh")),
  l_htHat                 (iConfig.getParameter<edm::InputTag>     ("htHat")),
  l_lhewtids              (iConfig.getParameter<edm::InputTag>     ("lhewtids")),
  l_lhewts                (iConfig.getParameter<edm::InputTag>     ("lhewts")),
  l_hltdecision           (iConfig.getParameter<edm::InputTag>     ("hltdecision")),
  l_npv                   (iConfig.getParameter<edm::InputTag>     ("npv")),
  l_npuTrue               (iConfig.getParameter<edm::InputTag>     ("npuTrue")),
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams")),
  btageffFile_            (iConfig.getParameter<std::string>       ("btageffFile"))
{
}

HH4b::~HH4b() {}

bool HH4b::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<int>h_runno              ; evt.getByLabel(l_runno      , h_runno      ) ; 
  Handle<int>h_lumisec            ; evt.getByLabel(l_lumisec    , h_lumisec    ) ; 
  Handle<int>h_evtno              ; evt.getByLabel(l_evtno      , h_evtno      ) ; 
  Handle<bool>h_isData            ; evt.getByLabel(l_isData     , h_isData     ) ; 
  Handle<double>  h_evtwtGen      ; evt.getByLabel(l_evtwtGen   , h_evtwtGen   ) ; 
  Handle<double>  h_evtwtPV       ; evt.getByLabel(l_evtwtPV    , h_evtwtPV    ) ; 
  Handle<double>h_evtwtPVLow      ; evt.getByLabel(l_evtwtPVLow , h_evtwtPVLow ) ; 
  Handle<double>h_evtwtPVHigh     ; evt.getByLabel(l_evtwtPVHigh, h_evtwtPVHigh) ; 
  Handle<double>  h_htHat         ; evt.getByLabel(l_htHat      , h_htHat      ) ; 
  Handle<int>h_npuTrue            ; evt.getByLabel(l_npuTrue    , h_npuTrue    ) ; 
  Handle<vector<int>>h_lhewtids   ; evt.getByLabel(l_lhewtids   , h_lhewtids   ) ; 
  Handle<vector<double>>h_lhewts  ; evt.getByLabel(l_lhewts     , h_lhewts     ) ; 
  Handle<bool>    h_hltdecision   ; evt.getByLabel(l_hltdecision, h_hltdecision) ; 
  Handle<unsigned>h_npv           ; evt.getByLabel(l_npv        , h_npv        ) ; 

  const int runno(*h_runno.product()) ; 
  const int lumisec(*h_lumisec.product()) ; 
  const int evtno(*h_evtno.product()) ; 
  const bool isData(*h_isData.product()) ; 
  const double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 
  const double htHat((*h_htHat.product())) ; 
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

      if ( !isData ) { 
        //// Get b-tag SF weight
        //// Get btag SFs
        if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,0) ; 
        else btagsf *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,0)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
        if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,0) ; 
        else btagsf *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,0)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 


        //// Get btag SF up bc err
        if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_bcUp *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),1,0) ; 
        else btagsf_bcUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),1,0)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
        if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_bcUp *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),1,0) ; 
        else btagsf_bcUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),1,0)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 


        if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_bcDown *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),-1,0) ; 
        else btagsf_bcDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),-1,0)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
        if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_bcDown *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),-1,0) ; 
        else btagsf_bcDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),-1,0)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 

        //// Get btag SF up light err
        if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_lUp *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,1) ; 
        else btagsf_lUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,1)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
        if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_lUp *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,1) ; 
        else btagsf_lUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,1)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 


        if ( (ijet.second).getCSVSubjet0() > 0.605 ) btagsf_lDown *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,-1) ; 
        else btagsf_lDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0(),0,-1)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet0(), (ijet.second).getHadronFlavourSubjet0()) ); 
        if ( (ijet.second).getCSVSubjet1() > 0.605 ) btagsf_lDown *= BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,-1) ; 
        else btagsf_lDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1(),0,-1)*BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L((ijet.second).getPtSubjet1(), (ijet.second).getHadronFlavourSubjet1()) ); 
      } 

    } /// Loop over all Higgs jets

    //} //// If N(H jets) >= 2

    std::vector<std::pair<int, double>> lhe_ids_wts;
    for (auto idx : index(*h_lhewtids.product()) ) {
      int id = (*h_lhewtids.product()).at(idx.first) ; 
      double wt = (*h_lhewts.product()).at(idx.first) ; 
      lhe_ids_wts.push_back(std::make_pair(id, wt)) ; 
    }

    selectedevt.runno_ = int(runno);
    selectedevt.lumisec_ = int(lumisec);
    selectedevt.evtno_ = int(evtno);
    selectedevt.evtwt_ = evtwt ; 
    selectedevt.evtwtPV_ = double(*h_evtwtPV.product()) ; 
    selectedevt.evtwtPVLow_ = double(*h_evtwtPVLow.product()) ; 
    selectedevt.evtwtPVHigh_ = double(*h_evtwtPVHigh.product()) ; 
    selectedevt.btagsf_ = btagsf;
    selectedevt.btagsf_bcUp_ = btagsf_bcUp ; 
    selectedevt.btagsf_bcDown_ = btagsf_bcDown ; 
    selectedevt.btagsf_lUp_ = btagsf_lUp ; 
    selectedevt.btagsf_lDown_ = btagsf_lDown ; 
    selectedevt.npv_ = npv ; 
    selectedevt.npuTrue_ = int(*h_npuTrue.product()) ; 
    selectedevt.lhewts_ = lhe_ids_wts;
    selectedevt.htHat_ = htHat ; 

    tree_->Fill();

    return true ; 
}

bool HH4b::passHiggsTagging(vlq::Jet jet) {
  bool passHiggsTagging(0);
  if (jet.getPt() > 200. 
      && abs(jet.getEta()) <= 2.4
      && abs(jet.getPrunedMass()) >= 90 
      && (jet.getTau1() == 0. || jet.getTau2()/jet.getTau1() < 0.75)
     ) passHiggsTagging = true ; 
  return passHiggsTagging;
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
