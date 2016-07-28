// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      VLQAna
// 
/**\class VLQAna VLQAna.cc Analysis/VLQAna/plugins/VLQAna.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Devdatta Majumder
//         Created:  Fri, 27 Feb 2015 16:09:10 GMT
//
//

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

#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

#include "Analysis/VLQAna/interface/HT.h"
#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/CandidateCleaner.h"
#include "Analysis/VLQAna/interface/TtHTree.h"
#include "Analysis/VLQAna/interface/BTagSFUtils.h"

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>

#include <sstream>

class VLQAna : public edm::EDFilter {
  public:
    explicit VLQAna(const edm::ParameterSet&);
    ~VLQAna();

  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    double getHTReweightingSF(double ht, double err); 

    // ----------member data ---------------------------
    edm::EDGetTokenT<bool>           t_isData     ;
    edm::EDGetTokenT<bool>           t_hltdecision;
    edm::EDGetTokenT<string>         t_evttype    ;
    edm::EDGetTokenT<double>         t_evtwtGen   ;
    edm::EDGetTokenT<double>         t_evtwtPV    ;
    edm::EDGetTokenT<double>         t_evtwtPVLow ;
    edm::EDGetTokenT<double>         t_evtwtPVHigh;
    edm::EDGetTokenT<unsigned>       t_npv        ;
    edm::EDGetTokenT<int>            t_npuTrue    ;
    edm::EDGetTokenT<double>         t_htHat      ;
    edm::EDGetTokenT<vector<int>>    t_lhewtids   ;
    edm::EDGetTokenT<vector<double>> t_lhewts     ;

    JetMaker jetAK4maker                          ; 
    JetMaker jetAK8maker                          ; 
    JetMaker jetHTaggedmaker                      ; 
    JetMaker jetTopTaggedmaker                    ; 
    JetMaker jetAntiHTaggedmaker                  ; 

    double HTMin_                                 ; 
    bool   doBTagSFUnc_                           ; 
    bool   storePreselEvts_                       ; 
    bool   doPreselOnly_                          ; 

    edm::Service<TFileService> fs                 ; 
    std::map<std::string, TH1D*> h1_              ; 
    std::map<std::string, TH2D*> h2_              ; 

    TtHEventInfoBranches selectedevt_; 
    TtHJetInfoBranches jets_ ; 
    TTree* tree_ ; 

};

using namespace std; 

VLQAna::VLQAna(const edm::ParameterSet& iConfig) :
  t_isData                (consumes<bool>           (iConfig.getParameter<edm::InputTag>("isData"))),
  t_hltdecision           (consumes<bool>           (iConfig.getParameter<edm::InputTag>("hltdecision"))),
  t_evttype               (consumes<string>         (iConfig.getParameter<edm::InputTag>("evttype"))),
  t_evtwtGen              (consumes<double>         (iConfig.getParameter<edm::InputTag>("evtwtGen"))),
  t_evtwtPV               (consumes<double>         (iConfig.getParameter<edm::InputTag>("evtwtPV"))),
  t_evtwtPVLow            (consumes<double>         (iConfig.getParameter<edm::InputTag>("evtwtPVLow"))),
  t_evtwtPVHigh           (consumes<double>         (iConfig.getParameter<edm::InputTag>("evtwtPVHigh"))),
  t_npv                   (consumes<unsigned>       (iConfig.getParameter<edm::InputTag>("npv"))),
  t_npuTrue               (consumes<int>            (iConfig.getParameter<edm::InputTag>("npuTrue"))),
  t_htHat                 (consumes<double>         (iConfig.getParameter<edm::InputTag>("htHat"))),
  t_lhewtids              (consumes<vector<int>>    (iConfig.getParameter<edm::InputTag>("lhewtids"))),
  t_lhewts                (consumes<vector<double>> (iConfig.getParameter<edm::InputTag>("lhewts"))),
  jetAK4maker             (iConfig.getParameter<edm::ParameterSet>("jetAK4selParams"), consumesCollector()), 
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet>("jetAK8selParams"), consumesCollector()), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet>("jetHTaggedselParams"), consumesCollector()), 
  jetTopTaggedmaker       (iConfig.getParameter<edm::ParameterSet>("jetTopTaggedselParams"), consumesCollector()),  
  jetAntiHTaggedmaker     (iConfig.getParameter<edm::ParameterSet>("jetAntiHTaggedselParams"), consumesCollector()), 
  HTMin_                  (iConfig.getParameter<double>           ("HTMin")), 
  doBTagSFUnc_            (iConfig.getParameter<bool>             ("doBTagSFUnc")),
  storePreselEvts_        (iConfig.getParameter<bool>             ("storePreselEvts")),
  doPreselOnly_           (iConfig.getParameter<bool>             ("doPreselOnly")) 
{

}

VLQAna::~VLQAna() {
}

bool VLQAna::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<bool>           h_isData        ; evt.getByToken(t_isData     , h_isData) ; 
  Handle<bool>           h_hltdecision   ; evt.getByToken(t_hltdecision, h_hltdecision) ; 
  Handle<string>         h_evttype       ; evt.getByToken(t_evttype    , h_evttype) ; 
  Handle<double>         h_evtwtGen      ; evt.getByToken(t_evtwtGen   , h_evtwtGen) ; 
  Handle<double>         h_evtwtPV       ; evt.getByToken(t_evtwtPV    , h_evtwtPV) ; 
  Handle<double>         h_evtwtPVLow    ; evt.getByToken(t_evtwtPVLow , h_evtwtPVLow) ; 
  Handle<double>         h_evtwtPVHigh   ; evt.getByToken(t_evtwtPVHigh, h_evtwtPVHigh) ; 
  Handle<unsigned>       h_npv           ; evt.getByToken(t_npv        , h_npv) ; 
  Handle<int>            h_npuTrue       ; evt.getByToken(t_npuTrue    , h_npuTrue) ; 
  Handle<double>         h_htHat         ; evt.getByToken(t_htHat      , h_htHat) ; 
  Handle<vector<int>>    h_lhewtids      ; evt.getByToken(t_lhewtids   , h_lhewtids) ; 
  Handle<vector<double>> h_lhewts        ; evt.getByToken(t_lhewts     , h_lhewts) ; 

  const bool isData(*h_isData.product()) ; 
  const bool hltdecision(*h_hltdecision.product()) ; 
  double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 
  int npv(*h_npv.product()) ; 
  const double htHat((*h_htHat.product())) ; 

  h1_["cutflow"] -> Fill(1, evtwt) ; 

  if ( isData && !hltdecision ) return false; 

  h1_["cutflow"] -> Fill(2, evtwt) ; 

  vlq::JetCollection goodAK4Jets;
  jetAK4maker(evt, goodAK4Jets) ;
  //// Event pre-selection
  if (goodAK4Jets.size() < 4) return false ; 
  h1_["cutflow"] -> Fill(3, evtwt) ; 

  HT htak4(goodAK4Jets) ; 
  //// Event pre-selection
  if (htak4.getHT() < HTMin_) return false ; 
  h1_["cutflow"] -> Fill(4, evtwt) ; 

  vlq::JetCollection goodAK8Jets; 
  jetAK8maker(evt, goodAK8Jets); 
  //// Event pre-selection
  if (goodAK8Jets.size() < 1) return false ; 
  h1_["cutflow"] -> Fill(5, evtwt) ; 

  h1_["npv_noreweight"] -> Fill(*h_npv.product(), *h_evtwtGen.product()); 
  h1_["npv"] -> Fill(*h_npv.product(), evtwt); 

  if ( storePreselEvts_ || doPreselOnly_ ) { 
    h1_["Presel_HT"] -> Fill(htak4.getHT(), evtwt) ; 

    h1_["Presel_ptAK4_0"] -> Fill (goodAK4Jets.at(0).getPt(),evtwt) ;  
    h1_["Presel_ptAK4_1"] -> Fill (goodAK4Jets.at(1).getPt(),evtwt) ;  
    h1_["Presel_ptAK4_2"] -> Fill (goodAK4Jets.at(2).getPt(),evtwt) ;  
    h1_["Presel_ptAK4_3"] -> Fill (goodAK4Jets.at(3).getPt(),evtwt) ;  
    h1_["Presel_ptAK8_0"] -> Fill (goodAK8Jets.at(0).getPt(),evtwt) ;  

    h1_["Presel_etaAK4_0"] -> Fill (goodAK4Jets.at(0).getEta(),evtwt) ;  
    h1_["Presel_etaAK4_1"] -> Fill (goodAK4Jets.at(1).getEta(),evtwt) ;  
    h1_["Presel_etaAK4_2"] -> Fill (goodAK4Jets.at(2).getEta(),evtwt) ;  
    h1_["Presel_etaAK4_3"] -> Fill (goodAK4Jets.at(3).getEta(),evtwt) ;  
    h1_["Presel_etaAK8_0"] -> Fill (goodAK8Jets.at(0).getEta(),evtwt) ;  

    h1_["Presel_NAK4"] -> Fill(goodAK4Jets.size(), evtwt) ; 
    h1_["Presel_NAK8"] -> Fill(goodAK8Jets.size(), evtwt) ; 

    if ( !storePreselEvts_ && doPreselOnly_ ) return true;
  }

  vlq::JetCollection goodHTaggedJets, goodTopTaggedJets, antiHTaggedJets ; 

  jetHTaggedmaker(evt, goodHTaggedJets);
  jetTopTaggedmaker(evt, goodTopTaggedJets);
  jetAntiHTaggedmaker(evt, antiHTaggedJets);

  unsigned nAK4      (goodAK4Jets.size());
  unsigned nAK8      (goodAK8Jets.size());
  unsigned nHiggs    (goodHTaggedJets.size()); 
  unsigned nTop      (goodTopTaggedJets.size()); 
  unsigned nAntiHiggs(antiHTaggedJets.size()); 

  //// Create 4 regions of the ABCD method according the the scheme below 
  //// | A: Anti-H Anti-top | B: Anti-H Good top | 
  //// | C: Good H Anti-top | D: Good H Good top | 

  bool isRegionA(false), isRegionB(false), isRegionC(false), isRegionD(false), isRegionNotABCD(false); 

  std::unique_ptr<vlq::Jet> theHiggs ;  
  std::unique_ptr<vlq::Jet> theTop ;
  std::unique_ptr<vlq::Jet> theAntiHiggs ; 

  if (nTop > 0) {

    theTop = std::unique_ptr<vlq::Jet>(new vlq::Jet(goodTopTaggedJets.at(0))) ; 

    if (nHiggs > 0) {
      for (vlq::Jet& hjet : goodHTaggedJets) {
        double dphi = abs((theTop->getP4()).DeltaPhi(hjet.getP4())) ;  
        if (dphi > 2.0) {
          theHiggs = std::unique_ptr<vlq::Jet>(new vlq::Jet(hjet)) ; 
          isRegionD = true ; 
          break ; 
        }
      }
    } //// isRegionD 
    else isRegionD = false ; 

    if (isRegionD == false && nAntiHiggs > 0) {
      for (vlq::Jet& antihjet : antiHTaggedJets) {
        double dphi = abs((theTop->getP4()).DeltaPhi(antihjet.getP4())) ;  
        if (dphi > 2.0) {
          theAntiHiggs = std::unique_ptr<vlq::Jet>(new vlq::Jet(antihjet)) ; 
          isRegionB = true ; 
          break ; 
        }
      }
    } //// isRegionB
    else isRegionNotABCD = true ;

  }
  else {

    if (nHiggs > 0) {
      theHiggs = std::unique_ptr<vlq::Jet>(new vlq::Jet(goodHTaggedJets.at(0))) ; 
      isRegionC = true;
    } //// isRegionC 
    else if (nAntiHiggs > 0) {
      theAntiHiggs = std::unique_ptr<vlq::Jet>(new vlq::Jet(antiHTaggedJets.at(0))) ; 
      isRegionA = true;
    } //// isRegionA 
    else isRegionNotABCD = true ;

  }

  if ( !storePreselEvts_ && !isRegionA && !isRegionB && !isRegionC && !isRegionD ) return false ; 

  bool isOneOfABCD(isRegionA ^ isRegionB ^ isRegionC ^ isRegionD) ;
  if ( !storePreselEvts_ && isOneOfABCD == false) edm::LogInfo("ERROR ABCD") << ">>>> Check ABCD logic: Only one of A, B C, D should be true\n" ; 

  if ( theHiggs != nullptr ) h1_["cutflow"] -> Fill(6, evtwt) ; 
  if ( theTop != nullptr ) h1_["cutflow"] -> Fill(7, evtwt) ; 
  if ( isRegionA ) h1_["cutflow"] -> Fill(8, evtwt) ; 
  if ( isRegionB ) h1_["cutflow"] -> Fill(9, evtwt) ; 
  if ( isRegionC ) h1_["cutflow"] -> Fill(10, evtwt) ; 
  if ( isRegionD ) h1_["cutflow"] -> Fill(11, evtwt) ; 

  TLorentzVector p4_tprime, p4_TprimeDummy ; 
  double Mtprime(0), Mtprime_corr(0), MtprimeDummy(0), MtprimeDummy_corr(0) ; 

  if (isRegionD) {
    p4_tprime = theTop->getP4() + theHiggs->getP4() ; 
    Mtprime = p4_tprime.Mag();
    Mtprime_corr = Mtprime - theTop->getSoftDropMass() - theHiggs->getPrunedMass() + 172.5 + 125. ; 
  }
  else if (isRegionB) {
    p4_TprimeDummy = theTop->getP4() + theAntiHiggs->getP4() ; 
    MtprimeDummy = p4_TprimeDummy.Mag() ; 
    MtprimeDummy_corr = MtprimeDummy - theTop->getSoftDropMass() - theAntiHiggs->getPrunedMass() + 172.5 + 125. ; 
  }

  double evtwtHT(1), evtwtHTUp(1), evtwtHTDown(1);
  double toptagsf(1), toptagsfUp(1), toptagsfDown(1);
  double btagsf(1), btagsf_bcUp(1), btagsf_bcDown(1), btagsf_lUp(1), btagsf_lDown(1) ; 

  if ( !isData ) { 

    evtwtHT = getHTReweightingSF(htak4.getHT(), 0) ; 
    evtwtHTUp = getHTReweightingSF(htak4.getHT(), 1) ; 
    evtwtHTDown = getHTReweightingSF(htak4.getHT(), -1) ; 

    if ( theTop != nullptr && theTop->getPt() >= 400. && theTop->getPt() < 550.) {
      toptagsf = 0.88 ;
      toptagsfUp = 0.88+0.13 ; 
      toptagsfDown = 0.88-0.13;
    }
    else if ( theTop != nullptr && theTop->getPt() >= 550.)  {
      toptagsf = 0.94 ;
      toptagsfUp = 0.94+0.29 ; 
      toptagsfDown = 0.94-0.29;
    }

    if ( theHiggs != nullptr || theAntiHiggs != nullptr ) {

      double sj0csv(0) ; 
      double sj0pt (0) ; 
      double sj0fl (0) ; 
      double sj1csv(0) ; 
      double sj1pt (0) ; 
      double sj1fl (0) ; 
      if ( theHiggs != nullptr ) {
        sj0csv=(theHiggs->getCSVSubjet0()) ; 
        sj0pt =(theHiggs->getPtSubjet0()) ; 
        sj0fl =(theHiggs->getHadronFlavourSubjet0()) ; 
        sj1csv=(theHiggs->getCSVSubjet1()) ; 
        sj1pt =(theHiggs->getPtSubjet1()) ; 
        sj1fl =(theHiggs->getHadronFlavourSubjet1()) ; 
      }
      else if ( theAntiHiggs != nullptr ) {
        sj0csv=(theAntiHiggs->getCSVSubjet0()) ; 
        sj0pt =(theAntiHiggs->getPtSubjet0()) ; 
        sj0fl =(theAntiHiggs->getHadronFlavourSubjet0()) ; 
        sj1csv=(theAntiHiggs->getCSVSubjet1()) ; 
        sj1pt =(theAntiHiggs->getPtSubjet1()) ; 
        sj1fl =(theAntiHiggs->getHadronFlavourSubjet1()) ; 
      }

      ////// Get btag SFs
      if ( sj0csv > 0.605 ) btagsf *= BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl, 0, 0) ; 
      else btagsf *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,0,0)*BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
      if ( sj1csv > 0.605 ) btagsf *= BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl, 0, 0) ; 
      else btagsf *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,0,0)*BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

      //// Get btag SF up bc err
      if ( sj0csv > 0.605 ) btagsf_bcUp *= BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,1,0) ; 
      else btagsf_bcUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,1,0)*BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
      if ( sj1csv > 0.605 ) btagsf_bcUp *= BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,1,0) ; 
      else btagsf_bcUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,1,0)*BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

      if ( sj0csv > 0.605 ) btagsf_bcDown *= BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,-1,0) ; 
      else btagsf_bcDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,-1,0)*BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
      if ( sj1csv > 0.605 ) btagsf_bcDown *= BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,-1,0) ; 
      else btagsf_bcDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,-1,0)*BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

      //// Get btag SF up light err
      if ( sj0csv > 0.605 ) btagsf_lUp *= BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,0,1) ; 
      else btagsf_lUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,0,1)*BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
      if ( sj1csv > 0.605 ) btagsf_lUp *= BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,0,1) ; 
      else btagsf_lUp *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,0,1)*BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

      if ( sj0csv > 0.605 ) btagsf_lDown *= BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,0,-1) ; 
      else btagsf_lDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj0pt, sj0fl,0,-1)*BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
      if ( sj1csv > 0.605 ) btagsf_lDown *= BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,0,-1) ; 
      else btagsf_lDown *= ( 1 - BTagSFUtils::getBTagSF_CSVv2L(sj1pt, sj1fl,0,-1)*BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - BTagSFUtils::getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

    } //// Do b-tag SFs

  } //// if !isData

  if ( isRegionB ) {
    h1_["RegB_HT"] -> Fill(htak4.getHT(), evtwt) ; 
    h1_["RegB_HT_wts"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf) ; 
    h1_["RegB_HT_btagsf_bcUp"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_bcUp) ; 
    h1_["RegB_HT_btagsf_bcDown"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_bcDown) ; 
    h1_["RegB_HT_btagsf_lUp"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_lUp) ; 
    h1_["RegB_HT_btagsf_lDown"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_lDown) ; 
    h1_["RegB_HT_toptagsfUp"] -> Fill(htak4.getHT(), evtwt*toptagsfUp*evtwtHT*btagsf) ; 
    h1_["RegB_HT_toptagsfDown"] -> Fill(htak4.getHT(), evtwt*toptagsfDown*evtwtHT*btagsf) ; 
    h1_["RegB_HT_htwtUp"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHTUp*btagsf) ; 
    h1_["RegB_HT_htwtDown"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHTDown*btagsf) ; 

    h1_["RegB_mtprime"] -> Fill(MtprimeDummy, evtwt) ; 
    h1_["RegB_mtprime_wts"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHT*btagsf) ; 
    h1_["RegB_mtprime_btagsf_bcUp"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHT*btagsf_bcUp) ; 
    h1_["RegB_mtprime_btagsf_bcDown"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHT*btagsf_bcDown) ; 
    h1_["RegB_mtprime_btagsf_lUp"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHT*btagsf_lUp) ; 
    h1_["RegB_mtprime_btagsf_lDown"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHT*btagsf_lDown) ; 
    h1_["RegB_mtprime_toptagsfUp"] -> Fill(MtprimeDummy, evtwt*toptagsfUp*evtwtHT*btagsf) ; 
    h1_["RegB_mtprime_toptagsfDown"] -> Fill(MtprimeDummy, evtwt*toptagsfDown*evtwtHT*btagsf) ; 
    h1_["RegB_mtprime_htwtUp"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHTUp*btagsf) ; 
    h1_["RegB_mtprime_htwtDown"] -> Fill(MtprimeDummy, evtwt*toptagsf*evtwtHTDown*btagsf) ; 

    h1_["RegB_mtprime_corr"] -> Fill(MtprimeDummy_corr, evtwt) ; 
    h1_["RegB_mtprime_corr_wts"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHT*btagsf) ; 
    h1_["RegB_mtprime_corr_btagsf_bcUp"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHT*btagsf_bcUp) ; 
    h1_["RegB_mtprime_corr_btagsf_bcDown"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHT*btagsf_bcDown) ; 
    h1_["RegB_mtprime_corr_btagsf_lUp"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHT*btagsf_lUp) ; 
    h1_["RegB_mtprime_corr_btagsf_lDown"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHT*btagsf_lDown) ; 
    h1_["RegB_mtprime_corr_toptagsfUp"] -> Fill(MtprimeDummy_corr, evtwt*toptagsfUp*evtwtHT*btagsf) ; 
    h1_["RegB_mtprime_corr_toptagsfDown"] -> Fill(MtprimeDummy_corr, evtwt*toptagsfDown*evtwtHT*btagsf) ; 
    h1_["RegB_mtprime_corr_htwtUp"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHTUp*btagsf) ; 
    h1_["RegB_mtprime_corr_htwtDown"] -> Fill(MtprimeDummy_corr, evtwt*toptagsf*evtwtHTDown*btagsf) ; 
  }

  if ( isRegionD ) {
    h1_["RegD_HT"] -> Fill(htak4.getHT(), evtwt) ; 
    h1_["RegD_HT_wts"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf) ; 
    h1_["RegD_HT_btagsf_bcUp"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_bcUp) ; 
    h1_["RegD_HT_btagsf_bcDown"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_bcDown) ; 
    h1_["RegD_HT_btagsf_lUp"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_lUp) ; 
    h1_["RegD_HT_btagsf_lDown"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHT*btagsf_lDown) ; 
    h1_["RegD_HT_toptagsfUp"] -> Fill(htak4.getHT(), evtwt*toptagsfUp*evtwtHT*btagsf) ; 
    h1_["RegD_HT_toptagsfDown"] -> Fill(htak4.getHT(), evtwt*toptagsfDown*evtwtHT*btagsf) ; 
    h1_["RegD_HT_htwtUp"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHTUp*btagsf) ; 
    h1_["RegD_HT_htwtDown"] -> Fill(htak4.getHT(), evtwt*toptagsf*evtwtHTDown*btagsf) ; 

    h1_["RegD_mtprime"] -> Fill(Mtprime, evtwt) ; 
    h1_["RegD_mtprime_wts"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHT*btagsf) ; 
    h1_["RegD_mtprime_btagsf_bcUp"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHT*btagsf_bcUp) ; 
    h1_["RegD_mtprime_btagsf_bcDown"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHT*btagsf_bcDown) ; 
    h1_["RegD_mtprime_btagsf_lUp"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHT*btagsf_lUp) ; 
    h1_["RegD_mtprime_btagsf_lDown"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHT*btagsf_lDown) ; 
    h1_["RegD_mtprime_toptagsfUp"] -> Fill(Mtprime, evtwt*toptagsfUp*evtwtHT*btagsf) ; 
    h1_["RegD_mtprime_toptagsfDown"] -> Fill(Mtprime, evtwt*toptagsfDown*evtwtHT*btagsf) ; 
    h1_["RegD_mtprime_htwtUp"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHTUp*btagsf) ; 
    h1_["RegD_mtprime_htwtDown"] -> Fill(Mtprime, evtwt*toptagsf*evtwtHTDown*btagsf) ; 

    h1_["RegD_mtprime_corr"] -> Fill(Mtprime_corr, evtwt) ; 
    h1_["RegD_mtprime_corr_wts"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHT*btagsf) ; 
    h1_["RegD_mtprime_corr_btagsf_bcUp"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHT*btagsf_bcUp) ; 
    h1_["RegD_mtprime_corr_btagsf_bcDown"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHT*btagsf_bcDown) ; 
    h1_["RegD_mtprime_corr_btagsf_lUp"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHT*btagsf_lUp) ; 
    h1_["RegD_mtprime_corr_btagsf_lDown"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHT*btagsf_lDown) ; 
    h1_["RegD_mtprime_corr_toptagsfUp"] -> Fill(Mtprime_corr, evtwt*toptagsfUp*evtwtHT*btagsf) ; 
    h1_["RegD_mtprime_corr_toptagsfDown"] -> Fill(Mtprime_corr, evtwt*toptagsfDown*evtwtHT*btagsf) ; 
    h1_["RegD_mtprime_corr_htwtUp"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHTUp*btagsf) ; 
    h1_["RegD_mtprime_corr_htwtDown"] -> Fill(Mtprime_corr, evtwt*toptagsf*evtwtHTDown*btagsf) ; 
  }

  std::vector<std::pair<int, double>> lhe_ids_wts;
  for (auto idx : index(*h_lhewtids.product()) ) {
    int id = (*h_lhewtids.product()).at(idx.first) ; 
    double wt = (*h_lhewts.product()).at(idx.first) ; 
    lhe_ids_wts.push_back(std::make_pair(id, wt)) ; 
  }

  selectedevt_.EvtWeight_ = double(*h_evtwtGen.product());
  selectedevt_.EvtWtPV_ = double(*h_evtwtPV.product()) ; 
  selectedevt_.EvtWtPVLow_ = double(*h_evtwtPVLow.product()) ; 
  selectedevt_.EvtWtPVHigh_ = double(*h_evtwtPVHigh.product()) ; 
  selectedevt_.EvtWtHT_ = evtwtHT;
  selectedevt_.EvtWtHTUp_ = evtwtHTUp;
  selectedevt_.EvtWtHTDown_ = evtwtHTDown;
  selectedevt_.npv_ = npv ; 
  selectedevt_.npuTrue_ = int(*h_npuTrue.product()) ; 
  selectedevt_.toptagsf_ = toptagsf ; 
  selectedevt_.toptagsf_Up_ = toptagsfUp ; 
  selectedevt_.toptagsf_Down_ = toptagsfDown ; 
  selectedevt_.btagsf_ = btagsf ; 
  selectedevt_.btagsf_bcUp_ = btagsf_bcUp ; 
  selectedevt_.btagsf_bcDown_ = btagsf_bcDown ; 
  selectedevt_.btagsf_lUp_ = btagsf_lUp ; 
  selectedevt_.btagsf_lDown_ = btagsf_lDown ; 
  selectedevt_.mtprime_ = Mtprime ;
  selectedevt_.mtprimeDummy_ = MtprimeDummy ;
  selectedevt_.ht_ = htak4.getHT();
  selectedevt_.nAK4_ = int(nAK4);
  selectedevt_.nAK8_ = int(nAK8);
  selectedevt_.isRegionA_ = isRegionA ; 
  selectedevt_.isRegionB_ = isRegionB ; 
  selectedevt_.isRegionC_ = isRegionC ; 
  selectedevt_.isRegionD_ = isRegionD ; 
  selectedevt_.isRegionNotABCD_ = isRegionNotABCD;
  selectedevt_.lhewts_ = lhe_ids_wts;
  selectedevt_.htHat_ = htHat ; 

  jets_.idxAK4             .clear() ; jets_.idxAK4             .reserve(goodAK4Jets.size()) ;   
  jets_.ptAK4              .clear() ; jets_.ptAK4              .reserve(goodAK4Jets.size()) ; 
  jets_.etaAK4             .clear() ; jets_.etaAK4             .reserve(goodAK4Jets.size()) ;   
  jets_.phiAK4             .clear() ; jets_.phiAK4             .reserve(goodAK4Jets.size()) ;   
  jets_.MAK4               .clear() ; jets_.MAK4               .reserve(goodAK4Jets.size()) ;   
  jets_.csvAK4             .clear() ; jets_.csvAK4             .reserve(goodAK4Jets.size()) ;   
  jets_.partonFlavourAK4   .clear() ; jets_.partonFlavourAK4   .reserve(goodAK4Jets.size()) ;   
  jets_.hadronFlavourAK4   .clear() ; jets_.hadronFlavourAK4   .reserve(goodAK4Jets.size()) ;   

  for (vlq::Jet jet : goodAK4Jets) {
    jets_.idxAK4             .push_back(jet.getIndex()) ; 
    jets_.ptAK4              .push_back(jet.getPt()) ; 
    jets_.etaAK4             .push_back(jet.getEta()) ; 
    jets_.phiAK4             .push_back(jet.getPhi()) ; 
    jets_.MAK4               .push_back(jet.getMass()) ; 
    jets_.csvAK4             .push_back(jet.getCSV());
    jets_.partonFlavourAK4   .push_back(jet.getPartonFlavour());
    jets_.hadronFlavourAK4   .push_back(jet.getHadronFlavour());
  }

  jets_.idxAK8             .clear() ; jets_.idxAK8             .reserve(goodAK8Jets.size()) ;  
  jets_.ptAK8              .clear() ; jets_.ptAK8              .reserve(goodAK8Jets.size()) ;  
  jets_.etaAK8             .clear() ; jets_.etaAK8             .reserve(goodAK8Jets.size()) ;  
  jets_.phiAK8             .clear() ; jets_.phiAK8             .reserve(goodAK8Jets.size()) ;  
  jets_.MAK8               .clear() ; jets_.MAK8               .reserve(goodAK8Jets.size()) ;  
  jets_.SoftDropMassAK8    .clear() ; jets_.SoftDropMassAK8    .reserve(goodAK8Jets.size()) ;  
  jets_.PrunedMassAK8      .clear() ; jets_.PrunedMassAK8      .reserve(goodAK8Jets.size()) ;  
  jets_.tau1AK8            .clear() ; jets_.tau1AK8            .reserve(goodAK8Jets.size()) ;  
  jets_.tau2AK8            .clear() ; jets_.tau2AK8            .reserve(goodAK8Jets.size()) ;  
  jets_.tau3AK8            .clear() ; jets_.tau3AK8            .reserve(goodAK8Jets.size()) ;  
  jets_.csvAK8             .clear() ; jets_.csvAK8             .reserve(goodAK8Jets.size()) ;  
  jets_.partonFlavourAK8   .clear() ; jets_.partonFlavourAK8   .reserve(goodAK8Jets.size()) ;  
  jets_.hadronFlavourAK8   .clear() ; jets_.hadronFlavourAK8   .reserve(goodAK8Jets.size()) ;  
  jets_.sj0CSVAK8          .clear() ; jets_.sj0CSVAK8          .reserve(goodAK8Jets.size()) ;  
  jets_.sj1CSVAK8          .clear() ; jets_.sj1CSVAK8          .reserve(goodAK8Jets.size()) ;  
  jets_.hadronFlavourSJ0AK8.clear() ; jets_.hadronFlavourSJ0AK8.reserve(goodAK8Jets.size()) ;  
  jets_.hadronFlavourSJ1AK8.clear() ; jets_.hadronFlavourSJ1AK8.reserve(goodAK8Jets.size()) ;  

  for (vlq::Jet jet : goodAK8Jets) {
    jets_.idxAK8             .push_back(jet.getIndex()) ; 
    jets_.ptAK8              .push_back(jet.getPt()) ; 
    jets_.etaAK8             .push_back(jet.getEta()) ; 
    jets_.phiAK8             .push_back(jet.getPhi()) ; 
    jets_.MAK8               .push_back(jet.getMass()) ; 
    jets_.SoftDropMassAK8    .push_back(jet.getSoftDropMass()) ;
    jets_.PrunedMassAK8      .push_back(jet.getPrunedMass()) ;
    jets_.tau1AK8            .push_back(jet.getTau1()) ;
    jets_.tau2AK8            .push_back(jet.getTau2()) ;
    jets_.tau3AK8            .push_back(jet.getTau3()) ;
    jets_.csvAK8             .push_back(jet.getCSV());
    jets_.partonFlavourAK8   .push_back(jet.getPartonFlavour());
    jets_.hadronFlavourAK8   .push_back(jet.getHadronFlavour());
    jets_.sj0CSVAK8          .push_back(jet.getCSVSubjet0()) ;
    jets_.sj1CSVAK8          .push_back(jet.getCSVSubjet1()) ;
    jets_.hadronFlavourSJ0AK8.push_back(jet.getHadronFlavourSubjet0()) ;
    jets_.hadronFlavourSJ1AK8.push_back(jet.getHadronFlavourSubjet1()) ;
  }

  jets_.idxHTagged             .clear() ; jets_.idxHTagged             .reserve(goodHTaggedJets.size()) ;   
  jets_.ptHTagged              .clear() ; jets_.ptHTagged              .reserve(goodHTaggedJets.size()) ;   
  jets_.etaHTagged             .clear() ; jets_.etaHTagged             .reserve(goodHTaggedJets.size()) ;   
  jets_.phiHTagged             .clear() ; jets_.phiHTagged             .reserve(goodHTaggedJets.size()) ;   
  jets_.MHTagged               .clear() ; jets_.MHTagged               .reserve(goodHTaggedJets.size()) ;   
  jets_.SoftDropMassHTagged    .clear() ; jets_.SoftDropMassHTagged    .reserve(goodHTaggedJets.size()) ;   
  jets_.PrunedMassHTagged      .clear() ; jets_.PrunedMassHTagged      .reserve(goodHTaggedJets.size()) ;   
  jets_.tau1HTagged            .clear() ; jets_.tau1HTagged            .reserve(goodHTaggedJets.size()) ;   
  jets_.tau2HTagged            .clear() ; jets_.tau2HTagged            .reserve(goodHTaggedJets.size()) ;   
  jets_.tau3HTagged            .clear() ; jets_.tau3HTagged            .reserve(goodHTaggedJets.size()) ;   
  jets_.csvHTagged             .clear() ; jets_.csvHTagged             .reserve(goodHTaggedJets.size()) ;   
  jets_.partonFlavourHTagged   .clear() ; jets_.partonFlavourHTagged   .reserve(goodHTaggedJets.size()) ;   
  jets_.hadronFlavourHTagged   .clear() ; jets_.hadronFlavourHTagged   .reserve(goodHTaggedJets.size()) ;   
  jets_.sj0CSVHTagged          .clear() ; jets_.sj0CSVHTagged          .reserve(goodHTaggedJets.size()) ;   
  jets_.sj1CSVHTagged          .clear() ; jets_.sj1CSVHTagged          .reserve(goodHTaggedJets.size()) ;   
  jets_.hadronFlavourSJ0HTagged.clear() ; jets_.hadronFlavourSJ0HTagged.reserve(goodHTaggedJets.size()) ;   
  jets_.hadronFlavourSJ1HTagged.clear() ; jets_.hadronFlavourSJ1HTagged.reserve(goodHTaggedJets.size()) ;   

  for (vlq::Jet jet : goodHTaggedJets) {
    jets_.idxHTagged             .push_back(jet.getIndex()) ; 
    jets_.ptHTagged              .push_back(jet.getPt()) ; 
    jets_.etaHTagged             .push_back(jet.getEta()) ; 
    jets_.phiHTagged             .push_back(jet.getPhi()) ; 
    jets_.MHTagged               .push_back(jet.getMass()) ; 
    jets_.SoftDropMassHTagged    .push_back(jet.getSoftDropMass()) ;
    jets_.PrunedMassHTagged      .push_back(jet.getPrunedMass()) ;
    jets_.tau1HTagged            .push_back(jet.getTau1()) ;
    jets_.tau2HTagged            .push_back(jet.getTau2()) ;
    jets_.tau3HTagged            .push_back(jet.getTau3()) ;
    jets_.csvHTagged             .push_back(jet.getCSV());
    jets_.partonFlavourHTagged   .push_back(jet.getPartonFlavour());
    jets_.hadronFlavourHTagged   .push_back(jet.getHadronFlavour());
    jets_.sj0CSVHTagged          .push_back(jet.getCSVSubjet0()) ;
    jets_.sj1CSVHTagged          .push_back(jet.getCSVSubjet1()) ;
    jets_.hadronFlavourSJ0HTagged.push_back(jet.getHadronFlavourSubjet0()) ;
    jets_.hadronFlavourSJ1HTagged.push_back(jet.getHadronFlavourSubjet1()) ;
  }

  jets_.idxAntiHTagged             .clear() ; jets_.idxAntiHTagged             .reserve(antiHTaggedJets.size()) ;   
  jets_.ptAntiHTagged              .clear() ; jets_.ptAntiHTagged              .reserve(antiHTaggedJets.size()) ;   
  jets_.etaAntiHTagged             .clear() ; jets_.etaAntiHTagged             .reserve(antiHTaggedJets.size()) ;   
  jets_.phiAntiHTagged             .clear() ; jets_.phiAntiHTagged             .reserve(antiHTaggedJets.size()) ;   
  jets_.MAntiHTagged               .clear() ; jets_.MAntiHTagged               .reserve(antiHTaggedJets.size()) ;   
  jets_.SoftDropMassAntiHTagged    .clear() ; jets_.SoftDropMassAntiHTagged    .reserve(antiHTaggedJets.size()) ;   
  jets_.PrunedMassAntiHTagged      .clear() ; jets_.PrunedMassAntiHTagged      .reserve(antiHTaggedJets.size()) ;   
  jets_.tau1AntiHTagged            .clear() ; jets_.tau1AntiHTagged            .reserve(antiHTaggedJets.size()) ;   
  jets_.tau2AntiHTagged            .clear() ; jets_.tau2AntiHTagged            .reserve(antiHTaggedJets.size()) ;   
  jets_.tau3AntiHTagged            .clear() ; jets_.tau3AntiHTagged            .reserve(antiHTaggedJets.size()) ;   
  jets_.csvAntiHTagged             .clear() ; jets_.csvAntiHTagged             .reserve(antiHTaggedJets.size()) ;   
  jets_.partonFlavourAntiHTagged   .clear() ; jets_.partonFlavourAntiHTagged   .reserve(antiHTaggedJets.size()) ;   
  jets_.hadronFlavourAntiHTagged   .clear() ; jets_.hadronFlavourAntiHTagged   .reserve(antiHTaggedJets.size()) ;   
  jets_.sj0CSVAntiHTagged          .clear() ; jets_.sj0CSVAntiHTagged          .reserve(antiHTaggedJets.size()) ;   
  jets_.sj1CSVAntiHTagged          .clear() ; jets_.sj1CSVAntiHTagged          .reserve(antiHTaggedJets.size()) ;   
  jets_.hadronFlavourSJ0AntiHTagged.clear() ; jets_.hadronFlavourSJ0AntiHTagged.reserve(antiHTaggedJets.size()) ;   
  jets_.hadronFlavourSJ1AntiHTagged.clear() ; jets_.hadronFlavourSJ1AntiHTagged.reserve(antiHTaggedJets.size()) ;   

  for (vlq::Jet jet : antiHTaggedJets) {
    jets_.idxAntiHTagged             .push_back(jet.getIndex()) ; 
    jets_.ptAntiHTagged              .push_back(jet.getPt()) ; 
    jets_.etaAntiHTagged             .push_back(jet.getEta()) ; 
    jets_.phiAntiHTagged             .push_back(jet.getPhi()) ; 
    jets_.MAntiHTagged               .push_back(jet.getMass()) ; 
    jets_.SoftDropMassAntiHTagged    .push_back(jet.getSoftDropMass()) ;
    jets_.PrunedMassAntiHTagged      .push_back(jet.getPrunedMass()) ;
    jets_.tau1AntiHTagged            .push_back(jet.getTau1()) ;
    jets_.tau2AntiHTagged            .push_back(jet.getTau2()) ;
    jets_.tau3AntiHTagged            .push_back(jet.getTau3()) ;
    jets_.csvAntiHTagged             .push_back(jet.getCSV());
    jets_.partonFlavourAntiHTagged   .push_back(jet.getPartonFlavour());
    jets_.hadronFlavourAntiHTagged   .push_back(jet.getHadronFlavour());
    jets_.sj0CSVAntiHTagged          .push_back(jet.getCSVSubjet0()) ;
    jets_.sj1CSVAntiHTagged          .push_back(jet.getCSVSubjet1()) ;
    jets_.hadronFlavourSJ0AntiHTagged.push_back(jet.getHadronFlavourSubjet0()) ;
    jets_.hadronFlavourSJ1AntiHTagged.push_back(jet.getHadronFlavourSubjet1()) ;
  }

  jets_.idxTopTagged             .clear() ; jets_.idxTopTagged             .reserve(goodTopTaggedJets.size()) ;   
  jets_.ptTopTagged              .clear() ; jets_.ptTopTagged              .reserve(goodTopTaggedJets.size()) ;   
  jets_.etaTopTagged             .clear() ; jets_.etaTopTagged             .reserve(goodTopTaggedJets.size()) ;   
  jets_.phiTopTagged             .clear() ; jets_.phiTopTagged             .reserve(goodTopTaggedJets.size()) ;   
  jets_.MTopTagged               .clear() ; jets_.MTopTagged               .reserve(goodTopTaggedJets.size()) ;   
  jets_.SoftDropMassTopTagged    .clear() ; jets_.SoftDropMassTopTagged    .reserve(goodTopTaggedJets.size()) ;   
  jets_.PrunedMassTopTagged      .clear() ; jets_.PrunedMassTopTagged      .reserve(goodTopTaggedJets.size()) ;   
  jets_.tau1TopTagged            .clear() ; jets_.tau1TopTagged            .reserve(goodTopTaggedJets.size()) ;   
  jets_.tau2TopTagged            .clear() ; jets_.tau2TopTagged            .reserve(goodTopTaggedJets.size()) ;   
  jets_.tau3TopTagged            .clear() ; jets_.tau3TopTagged            .reserve(goodTopTaggedJets.size()) ;   
  jets_.csvTopTagged             .clear() ; jets_.csvTopTagged             .reserve(goodTopTaggedJets.size()) ;   
  jets_.partonFlavourTopTagged   .clear() ; jets_.partonFlavourTopTagged   .reserve(goodTopTaggedJets.size()) ;   
  jets_.hadronFlavourTopTagged   .clear() ; jets_.hadronFlavourTopTagged   .reserve(goodTopTaggedJets.size()) ;   
  jets_.sj0CSVTopTagged          .clear() ; jets_.sj0CSVTopTagged          .reserve(goodTopTaggedJets.size()) ;   
  jets_.sj1CSVTopTagged          .clear() ; jets_.sj1CSVTopTagged          .reserve(goodTopTaggedJets.size()) ;   
  jets_.hadronFlavourSJ0TopTagged.clear() ; jets_.hadronFlavourSJ0TopTagged.reserve(goodTopTaggedJets.size()) ;   
  jets_.hadronFlavourSJ1TopTagged.clear() ; jets_.hadronFlavourSJ1TopTagged.reserve(goodTopTaggedJets.size()) ;   

  for (vlq::Jet jet : goodTopTaggedJets) {
    jets_.idxTopTagged             .push_back(jet.getIndex()) ; 
    jets_.ptTopTagged              .push_back(jet.getPt()) ; 
    jets_.etaTopTagged             .push_back(jet.getEta()) ; 
    jets_.phiTopTagged             .push_back(jet.getPhi()) ; 
    jets_.MTopTagged               .push_back(jet.getMass()) ; 
    jets_.SoftDropMassTopTagged    .push_back(jet.getSoftDropMass()) ;
    jets_.PrunedMassTopTagged      .push_back(jet.getPrunedMass()) ;
    jets_.tau1TopTagged            .push_back(jet.getTau1()) ;
    jets_.tau2TopTagged            .push_back(jet.getTau2()) ;
    jets_.tau3TopTagged            .push_back(jet.getTau3()) ;
    jets_.csvTopTagged             .push_back(jet.getCSV());
    jets_.partonFlavourTopTagged   .push_back(jet.getPartonFlavour());
    jets_.hadronFlavourTopTagged   .push_back(jet.getHadronFlavour());
    jets_.sj0CSVTopTagged          .push_back(jet.getCSVSubjet0()) ;
    jets_.sj1CSVTopTagged          .push_back(jet.getCSVSubjet1()) ;
    jets_.hadronFlavourSJ0TopTagged.push_back(jet.getHadronFlavourSubjet0()) ;
    jets_.hadronFlavourSJ1TopTagged.push_back(jet.getHadronFlavourSubjet1()) ;
  }

  tree_->Fill();

  return true;


}

// ------------ method called once each job just before starting event loop  ------------
void VLQAna::beginJob() {

  h1_["npv_noreweight"] = fs->make<TH1D>("npv_noreweight", ";N(PV);;", 51, -0.5, 50.5) ; 
  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 

  if ( !doPreselOnly_ ) {
    tree_ = fs->make<TTree>("tree", "TtHT") ; 
    selectedevt_.RegisterTree(tree_,"SelectedEvent") ; 
    jets_.RegisterTree(tree_,"JetInfo") ; 
  }

  if (storePreselEvts_ || doPreselOnly_) {

    h1_["Presel_HT"] = fs->make<TH1D>("Presel_HT", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 

    h1_["Presel_ptAK4_0"] = fs->make<TH1D>("Presel_ptAK4_0", "p_{T} AK4;p_{T} (1st AK4 jet) [GeV];;",50,0,2000) ; 
    h1_["Presel_ptAK4_1"] = fs->make<TH1D>("Presel_ptAK4_1", "p_{T} AK4;p_{T} (2nd AK4 jet) [GeV];;",50,0,2000) ; 
    h1_["Presel_ptAK4_2"] = fs->make<TH1D>("Presel_ptAK4_2", "p_{T} AK4;p_{T} (3rd AK4 jet) [GeV];;",50,0,2000) ; 
    h1_["Presel_ptAK4_3"] = fs->make<TH1D>("Presel_ptAK4_3", "p_{T} AK4;p_{T} (4th AK4 jet) [GeV];;",50,0,2000) ; 
    h1_["Presel_ptAK8_0"] = fs->make<TH1D>("Presel_ptAK8_0", "p_{T} AK8;p_{T} (1st AK8 jet) [GeV];;",50,0,2000) ; 

    h1_["Presel_etaAK4_0"] = fs->make<TH1D>("Presel_etaAK4_0", "#eta AK4;#eta (1st AK4 jet) [GeV];;",60,-6.,6.) ; 
    h1_["Presel_etaAK4_1"] = fs->make<TH1D>("Presel_etaAK4_1", "#eta AK4;#eta (2nd AK4 jet) [GeV];;",60,-6.,6.) ; 
    h1_["Presel_etaAK4_2"] = fs->make<TH1D>("Presel_etaAK4_2", "#eta AK4;#eta (3rd AK4 jet) [GeV];;",60,-6.,6.) ; 
    h1_["Presel_etaAK4_3"] = fs->make<TH1D>("Presel_etaAK4_3", "#eta AK4;#eta (4th AK4 jet) [GeV];;",60,-6.,6.) ; 
    h1_["Presel_etaAK8_0"] = fs->make<TH1D>("Presel_etaAK8_0", "#eta AK8;#eta (1st AK8 jet) [GeV];;",60,-6.,6.) ; 

    h1_["Presel_NAK4"] = fs->make<TH1D>("Presel_NAK4", ";N(AK4 jets);;", 21, -0.5, 20.5) ; 
    h1_["Presel_NAK8"] = fs->make<TH1D>("Presel_NAK8", ";N(AK4 jets);;", 11, -0.5, 10.5) ; 

    if ( doPreselOnly_ ) {
      h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 5, 0.5, 5.5) ;  
      h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1,  "All") ; 
      h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2,  "Trig.+PV") ; 
      h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3,  "N(AK4)>=4") ; 
      h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4,  "H_{T}>1000GeV") ; 
      h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5,  "N(AK8)>=1") ; 
      return ; 
    }

  }

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 11, 0.5, 11.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1,  "All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2,  "Trig.+PV") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3,  "N(AK4)>=4") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4,  "H_{T}>1000GeV") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5,  "N(AK8)>=1") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6,  "N(H)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7,  "N(top)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8,  "RegionA") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9,  "RegionB") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(10, "RegionC") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(11, "RegionD") ; 

  h1_["RegD_HT"] = fs->make<TH1D>("RegD_HT", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_wts"] = fs->make<TH1D>("RegD_HT_wts", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_btagsf_bcUp"] = fs->make<TH1D>("RegD_HT_btagsf_bcUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_btagsf_bcDown"] = fs->make<TH1D>("RegD_HT_btagsf_bcDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_btagsf_lUp"] = fs->make<TH1D>("RegD_HT_btagsf_lUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_btagsf_lDown"] = fs->make<TH1D>("RegD_HT_btagsf_lDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_toptagsfUp"] = fs->make<TH1D>("RegD_HT_toptagsfUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_toptagsfDown"] = fs->make<TH1D>("RegD_HT_toptagsfDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_htwtUp"] = fs->make<TH1D>("RegD_HT_htwtUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegD_HT_htwtDown"] = fs->make<TH1D>("RegD_HT_htwtDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 

  h1_["RegB_HT"] = fs->make<TH1D>("RegB_HT", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_wts"] = fs->make<TH1D>("RegB_HT_wts", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_btagsf_bcUp"] = fs->make<TH1D>("RegB_HT_btagsf_bcUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_btagsf_bcDown"] = fs->make<TH1D>("RegB_HT_btagsf_bcDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_btagsf_lUp"] = fs->make<TH1D>("RegB_HT_btagsf_lUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_btagsf_lDown"] = fs->make<TH1D>("RegB_HT_btagsf_lDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_toptagsfUp"] = fs->make<TH1D>("RegB_HT_toptagsfUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_toptagsfDown"] = fs->make<TH1D>("RegB_HT_toptagsfDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_htwtUp"] = fs->make<TH1D>("RegB_HT_htwtUp", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 
  h1_["RegB_HT_htwtDown"] = fs->make<TH1D>("RegB_HT_htwtDown", "H_{T};H_{T} [GeV];;",50,1000,3000) ; 

  //////////

  h1_["RegD_mtprime"] = fs->make<TH1D>("RegD_mtprime", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_wts"] = fs->make<TH1D>("RegD_mtprime_wts", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_btagsf_bcUp"] = fs->make<TH1D>("RegD_mtprime_btagsf_bcUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_btagsf_bcDown"] = fs->make<TH1D>("RegD_mtprime_btagsf_bcDown", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_btagsf_lUp"] = fs->make<TH1D>("RegD_mtprime_btagsf_lUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_btagsf_lDown"] = fs->make<TH1D>("RegD_mtprime_btagsf_lDown", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_toptagsfUp"] = fs->make<TH1D>("RegD_mtprime_toptagsfUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_toptagsfDown"] = fs->make<TH1D>("RegD_mtprime_toptagsfDown", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_htwtUp"] = fs->make<TH1D>("RegD_mtprime_htwtUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_htwtDown"] = fs->make<TH1D>("RegD_mtprime_htwtDown", "M(T);M(T) [GeV];;",80,500,2500) ; 

  h1_["RegD_mtprime_corr"] = fs->make<TH1D>("RegD_mtprime_corr", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_wts"] = fs->make<TH1D>("RegD_mtprime_corr_wts", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_btagsf_bcUp"] = fs->make<TH1D>("RegD_mtprime_corr_btagsf_bcUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_btagsf_bcDown"] = fs->make<TH1D>("RegD_mtprime_corr_btagsf_bcDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_btagsf_lUp"] = fs->make<TH1D>("RegD_mtprime_corr_btagsf_lUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_btagsf_lDown"] = fs->make<TH1D>("RegD_mtprime_corr_btagsf_lDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_toptagsfUp"] = fs->make<TH1D>("RegD_mtprime_corr_toptagsfUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_toptagsfDown"] = fs->make<TH1D>("RegD_mtprime_corr_toptagsfDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_htwtUp"] = fs->make<TH1D>("RegD_mtprime_corr_htwtUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegD_mtprime_corr_htwtDown"] = fs->make<TH1D>("RegD_mtprime_corr_htwtDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 

  h1_["RegB_mtprime"] = fs->make<TH1D>("RegB_mtprime", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_wts"] = fs->make<TH1D>("RegB_mtprime_wts", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_btagsf_bcUp"] = fs->make<TH1D>("RegB_mtprime_btagsf_bcUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_btagsf_bcDown"] = fs->make<TH1D>("RegB_mtprime_btagsf_bcDown", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_btagsf_lUp"] = fs->make<TH1D>("RegB_mtprime_btagsf_lUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_btagsf_lDown"] = fs->make<TH1D>("RegB_mtprime_btagsf_lDown", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_toptagsfUp"] = fs->make<TH1D>("RegB_mtprime_toptagsfUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_toptagsfDown"] = fs->make<TH1D>("RegB_mtprime_toptagsfDown", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_htwtUp"] = fs->make<TH1D>("RegB_mtprime_htwtUp", "M(T);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_htwtDown"] = fs->make<TH1D>("RegB_mtprime_htwtDown", "M(T);M(T) [GeV];;",80,500,2500) ; 

  h1_["RegB_mtprime_corr"] = fs->make<TH1D>("RegB_mtprime_corr", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_wts"] = fs->make<TH1D>("RegB_mtprime_corr_wts", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_btagsf_bcUp"] = fs->make<TH1D>("RegB_mtprime_corr_btagsf_bcUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_btagsf_bcDown"] = fs->make<TH1D>("RegB_mtprime_corr_btagsf_bcDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_btagsf_lUp"] = fs->make<TH1D>("RegB_mtprime_corr_btagsf_lUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_btagsf_lDown"] = fs->make<TH1D>("RegB_mtprime_corr_btagsf_lDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_toptagsfUp"] = fs->make<TH1D>("RegB_mtprime_corr_toptagsfUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_toptagsfDown"] = fs->make<TH1D>("RegB_mtprime_corr_toptagsfDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_htwtUp"] = fs->make<TH1D>("RegB_mtprime_corr_htwtUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 
  h1_["RegB_mtprime_corr_htwtDown"] = fs->make<TH1D>("RegB_mtprime_corr_htwtDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",80,500,2500) ; 

  //h1_["ptak8leading"]  = fs->make<TH1D>("ptak8leading"  ,";p_T(leading AK8 jet) [GeV];;"      , 40, 0., 2000.) ; 
  //h1_["ptak4leading"]  = fs->make<TH1D>("ptak4leading"  ,";p_T(leading AK4 jet) [GeV];;"      , 40, 0., 2000.) ; 
  //h1_["ptbjetleading"]  = fs->make<TH1D>("ptbjetleading"  ,";p_T(leading b jet) [GeV];;"      , 40, 0., 2000.) ; 

  //h1_["etaak8leading"] = fs->make<TH1D>("etaak8leading", ";#eta(leading AK8 jet);;" , 80 ,-4. ,4.) ; 
  //h1_["etaak4leading"] = fs->make<TH1D>("etaak4leading", ";#eta(leading AK4 jet);;" , 80 ,-4. ,4.) ; 
  //h1_["etabjetleading"] = fs->make<TH1D>("etabjetleading", ";#eta(leading b jet);;" , 80 ,-4. ,4.) ; 

  //h1_["ptak82nd"]  = fs->make<TH1D>("ptak82nd"  ,";p_T(2nd AK8 jet) [GeV];;"      , 40, 0., 2000.) ; 
  //h1_["ptak8leadingPlus2nd"]  = fs->make<TH1D>("ptak8leadingPlus2nd"  ,";p_T(leading AK8 jet)+p_T (2nd AK8 jet) [GeV];;"      , 40, 0., 2000.) ; 

  //h1_["csvbjetleading"] = fs->make<TH1D>("csvbjetleading", ";CSV (leading b jet);;" ,50 ,0. ,1.) ; 
  //h1_["csvbjethighestcsv"] = fs->make<TH1D>("csvbjethighestcsv", ";max. CSV b jet;;" ,50 ,0. ,1.) ; 

  //h1_["ak4highestcsv_nocuts"] = fs->make<TH1D>("ak4highestcsv_nocuts", ";max. CSV of AK4 jets;;" , 50, 0., 1.) ; 

  //h1_["ptak4highestcsv"] = fs->make<TH1D>("ptak4highestcsv", ";p_T(highest CSV AK4 jet);;" , 100, 0., 2000.) ; 
  //h1_["etaak4highestcsv"] = fs->make<TH1D>("etaak4highestcsv", ";#eta(highest CSV AK4 jet);;" , 80 ,-4. ,4.) ; 

  //h1_["ptak4forwardmost"] = fs->make<TH1D>("ptak4forwardmost", ";p_T(forwardmost AK4 jet);;" , 100, 0., 2000.) ; 
  //h1_["etaak4forwardmost"] = fs->make<TH1D>("etaak4forwardmost", ";p_T(forwardmost AK4 jet);;" , 80 ,-4. ,4.) ; 

  //h1_["mak8leading"] = fs->make<TH1D>("mak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  //h1_["mak8highestm"] = fs->make<TH1D>("mak8highestm", ";M(most massive AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  //h1_["prunedmak8leading"] = fs->make<TH1D>("prunedmak8leading", ";M(pruned leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  //h1_["trimmedmak8leading"] = fs->make<TH1D>("trimmedmak8leading", ";M(trimmed leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  //h1_["trimmedmak8highesttrimmedm"] = fs->make<TH1D>("trimmedmak8highesttrimmedm", ";M(highest trimmed mass AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  //h1_["softdropmak8leading"] = fs->make<TH1D>("softdropmak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  //h1_["softdropmak8highestsoftdropm"] = fs->make<TH1D>("softdropmak8highestsoftdropm", ";M(highest soft drop mass AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  //h1_["mak82nd"] = fs->make<TH1D>("mak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  //h1_["csvak8leading"] = fs->make<TH1D>("csvak8leading", ";CSV (leading AK8 jet);;" ,50 ,0. ,1.) ;
  //h1_["csvak82nd"] = fs->make<TH1D>("csvak82nd", ";CSV (2nd AK8 jet);;" ,50 ,0. ,1.) ;

  //h2_["pt_ak8_leading_2nd"] = fs->make<TH2D>("pt_ak8_leading_2nd", ";p_T (leading AK8 jet) [GeV];p_T (2nd AK8 jet) [GeV];" ,40, 0., 2000. ,40, 0., 2000.) ; 

  //h2_["m_ak8_leading_2nd"] = fs->make<TH2D>("m_ak8_leading_2nd", ";M(leading AK8 jet) [GeV];M(2nd AK8 jet) [GeV];" ,100, 0., 200. ,100, 0., 200.) ; 

  //h2_["csv_ak8_leading_2nd"] = fs->make<TH2D>("csv_ak8_leading_2nd", ";CSV(leading AK8 jet) ;CSV(2nd AK8 jet) ;" ,50 ,0. ,1. ,50 ,0. ,1.) ;  

  //h1_["nak8_nocuts"] = fs->make<TH1D>("nak8_nocuts", ";AK8 jet multiplicity before cuts;;" , 11, -0.5,10.5) ; 
  //h1_["nak4_nocuts"] = fs->make<TH1D>("nak4_nocuts", ";AK4 jet multiplicity before cuts;;" , 11, -0.5,10.5) ; 
  //h1_["nbloose_nocuts"] = fs->make<TH1D>("nbloose_nocuts", ";b jet multiplicity before cuts;;" , 11, -0.5,10.5) ; 

  //h1_["nak8_presel"] = fs->make<TH1D>("nak8_presel", ";AK8 jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nak4_presel"] = fs->make<TH1D>("nak4_presel", ";AK4 jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nbloose_presel"] = fs->make<TH1D>("nbloose_presel", ";b jet multiplicity (Loose OP);;" , 11, -0.5,10.5) ; 
  //h1_["nbmedium_presel"] = fs->make<TH1D>("nbmedium_presel", ";b jet multiplicity (Medium OP);;" , 11, -0.5,10.5) ; 

  //h1_["nwjet_presel"] = fs->make<TH1D>("nwjet_presel", ";W jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nhjet_presel"] = fs->make<TH1D>("nhjet_presel", ";H jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["ntjet_presel"] = fs->make<TH1D>("ntjet_presel", ";top jet multiplicity;;" , 11, -0.5,10.5) ; 

  //h1_["nwcand_presel"] = fs->make<TH1D>("nwcand_presel", ";W candidate multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nhcand_presel"] = fs->make<TH1D>("nhcand_presel", ";H candidate multiplicity;;" , 11, -0.5,10.5) ; 

  //h1_["ht_presel"] = fs->make<TH1D>("ht_presel" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 

  //h1_["nak8"] = fs->make<TH1D>("nak8", ";AK8 jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nak4"] = fs->make<TH1D>("nak4", ";AK4 jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nbloose"] = fs->make<TH1D>("nbloose", ";b jet multiplicity (Loose OP);;" , 11, -0.5,10.5) ; 
  //h1_["nbmedium"] = fs->make<TH1D>("nbmedium", ";b jet multiplicity (Medium OP);;" , 11, -0.5,10.5) ; 

  //h1_["nwjet"] = fs->make<TH1D>("nwjet", ";W jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nhjet"] = fs->make<TH1D>("nhjet", ";H jet multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["ntjet"] = fs->make<TH1D>("ntjet", ";top jet multiplicity;;" , 11, -0.5,10.5) ; 

  //h1_["nwcand"] = fs->make<TH1D>("nwcand", ";W candidate multiplicity;;" , 11, -0.5,10.5) ; 
  //h1_["nhcand"] = fs->make<TH1D>("nhcand", ";H candidate multiplicity;;" , 11, -0.5,10.5) ; 

  //h1_["ht"] = fs->make<TH1D>("ht" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 

  //h1_["ptleadinghcand"] = fs->make<TH1D>("ptleadinghcand" ,";p_T (leading H cands) [GeV]", 100, 0., 2000.) ; 
  //h1_["ptleadingwcand"] = fs->make<TH1D>("ptleadingwcand" ,";p_T (leading W cands) [GeV]", 100, 0., 2000.) ; 

  //h1_["ptleadinghjet"] = fs->make<TH1D>("ptleadinghjet" ,";p_T (leading H-tagged jets) [GeV]", 100, 0., 2000.) ; 
  //h1_["ptleadingwjet"] = fs->make<TH1D>("ptleadingwjet" ,";p_T (leading W-tagged jets) [GeV]", 100, 0., 2000.) ; 
  //h1_["ptleadingtjet"] = fs->make<TH1D>("ptleadingtjet" ,";p_T (leading top-tagged jets) [GeV]", 100, 0., 2000.) ; 

  //h1_["ht_nwjetGt0"] = fs->make<TH1D>("ht_nwjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  //h1_["ht_nhjetGt0"] = fs->make<TH1D>("ht_nhjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  //h1_["ht_ntjetGt0"] = fs->make<TH1D>("ht_ntjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  //h1_["ht_nwhjetGt0"] = fs->make<TH1D>("ht_nwhjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  //h1_["ht_nhtjetGt0"] = fs->make<TH1D>("ht_nhtjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  //h1_["ht_nwcandGt0"] = fs->make<TH1D>("ht_nwcandGt0" ,";H_T (AK4 cands) [GeV]", 200, 0., 4000.) ; 
  //h1_["ht_nhcandGt0"] = fs->make<TH1D>("ht_nhcandGt0" ,";H_T (AK4 cands) [GeV]", 200, 0., 4000.) ; 

  //h1_["ptak8"]  = fs->make<TH1D>("ptak8"  ,";p_T(AK8 jet) [GeV]"         , 100, 0., 2000.) ; 
  //h1_["pthjets"] = fs->make<TH1D>("pthjets" ,";p_T (H-tagged jets) [GeV]", 100, 0., 2000.) ; 
  //h1_["csvhjets"] = fs->make<TH1D>("csvhjets", ";CSV (H-tagged jets);;" ,50 ,0. ,1.) ;

  //h1_["drwh"] = fs->make<TH1D>("drwh", ";#DeltaR(H,W);;", 40, 0, 4.) ;  

}

// ------------ method called once each job just after ending the event loop  ------------
void VLQAna::endJob() {
  return ; 
}

double VLQAna::getHTReweightingSF(double ht, double err) {
  double wt(1);
  std::unique_ptr<TF1> htReweightFun     = std::unique_ptr<TF1>( new TF1("htReweightFun", "1.25868 - (0.000210855*x)",1000, 10000) ) ; 
  std::unique_ptr<TF1> htReweightFunErr  = std::unique_ptr<TF1>( new TF1("htReweightFunErr", 
        "TMath::Sqrt( (0.00432715*0.00432715) + ((3.27325*x/1000000)*(3.27325*x/1000000)) - (2*x*0.00432715*3.27325*0.97547/1000000) )", 
        1000, 10000) ) ;
  wt = htReweightFun->Eval(ht) + (err*htReweightFunErr->Eval(ht)) ; 
  return wt;
}

DEFINE_FWK_MODULE(VLQAna);
