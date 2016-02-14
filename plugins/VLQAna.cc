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

    double getBTagEff_CSVv2L (double pt, double hadFl) ; 
    double getBTagSF_CSVv2L (double pt, double hadFl, double err_bc, double err_l) ; 

    // ----------member data ---------------------------
    edm::InputTag l_isData                       ;
    edm::InputTag l_hltdecision                  ;
    edm::InputTag l_evttype                      ;
    edm::InputTag l_evtwtGen                     ;
    edm::InputTag l_evtwtPV                      ;
    edm::InputTag l_npv                          ;

    JetMaker jetAK4maker                         ; 
    JetMaker jetAK8maker                         ; 
    JetMaker jetHTaggedmaker                     ; 
    JetMaker jetTopTaggedmaker                   ; 
    JetMaker jetAntiHTaggedmaker                 ; 

    double HTMin_                                ; 
    bool   doBTagSFUnc_                          ; 

    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    std::map<std::string, TH2D*> h2_             ; 

    TtHEventInfoBranches selectedevt_; 
    TtHJetInfoBranches jets_ ; 
    TTree* tree_ ; 

};

using namespace std; 

VLQAna::VLQAna(const edm::ParameterSet& iConfig) :
  l_isData                (iConfig.getParameter<edm::InputTag>     ("isData")),
  l_hltdecision           (iConfig.getParameter<edm::InputTag>     ("hltdecision")),
  l_evttype               (iConfig.getParameter<edm::InputTag>     ("evttype")),
  l_evtwtGen              (iConfig.getParameter<edm::InputTag>     ("evtwtGen")),
  l_evtwtPV               (iConfig.getParameter<edm::InputTag>     ("evtwtPV")),
  l_npv                   (iConfig.getParameter<edm::InputTag>     ("npv")),
  jetAK4maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK4selParams")), 
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams")), 
  jetTopTaggedmaker       (iConfig.getParameter<edm::ParameterSet> ("jetTopTaggedselParams")),  
  jetAntiHTaggedmaker     (iConfig.getParameter<edm::ParameterSet> ("jetAntiHTaggedselParams")), 
  HTMin_                  (iConfig.getParameter<double>            ("HTMin")), 
  doBTagSFUnc_            (iConfig.getParameter<bool>              ("doBTagSFUnc")) 
{

}

VLQAna::~VLQAna() {
}

bool VLQAna::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<bool>h_isData     ; evt.getByLabel(l_isData     ,  h_isData) ; 
  Handle<bool>h_hltdecision; evt.getByLabel(l_hltdecision,  h_hltdecision) ; 
  Handle<string>h_evttype  ; evt.getByLabel(l_evttype    , h_evttype) ; 
  Handle<double>h_evtwtGen ; evt.getByLabel(l_evtwtGen   , h_evtwtGen) ; 
  Handle<double>h_evtwtPV  ; evt.getByLabel(l_evtwtPV    ,  h_evtwtPV) ; 
  Handle<unsigned>h_npv    ; evt.getByLabel(l_npv        , h_npv) ; 

  const bool isData(*h_isData.product()) ; 
  const bool hltdecision(*h_hltdecision.product()) ; 
  double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 

  h1_["cutflow"] -> Fill(1, evtwt) ; 

  if ( !hltdecision ) return false; 
  
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

  bool isRegionA(false), isRegionB(false), isRegionC(false), isRegionD(false) ; 

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

  }

  if ( !isRegionA && !isRegionB && !isRegionC && !isRegionD ) return false ; 

  bool isOneOfABCD(isRegionA ^ isRegionB ^ isRegionC ^ isRegionD) ;
  if (isOneOfABCD == false) edm::LogInfo("ERROR ABCD") << ">>>> Check ABCD logic: Only one of A, B C, D should be true\n" ; 

  if ( theHiggs != nullptr ) h1_["cutflow"] -> Fill(6, evtwt) ; 
  if ( theHiggs != nullptr && theTop != nullptr ) h1_["cutflow"] -> Fill(7, evtwt) ; 

  TLorentzVector p4_tprime, p4_TprimeDummy ; 
  double Mtprime(0), Mtprime_corr(0), MtprimeDummy(0) ; 

  if (isRegionD) {
    p4_tprime = theTop->getP4() + theHiggs->getP4() ; 
    double Mtprime = p4_tprime.Mag();
    double Mtprime_corr = Mtprime - theTop->getSoftDropMass() - theHiggs->getPrunedMass() + 172.5 + 125. ; 
    h1_["mtprime"] -> Fill(Mtprime, evtwt) ; 
    h1_["mtprime_corr"] -> Fill(Mtprime_corr, evtwt) ; 
  }
  else if (isRegionB) {
    p4_TprimeDummy = theTop->getP4() + theAntiHiggs->getP4() ; 
    MtprimeDummy = p4_TprimeDummy.Mag() ; 
  }

  double toptagsf(1);
  double toptagsfUp(1);
  double toptagsfDown(1);

  double btagsf(1) ; 
  double btagsf_bcUp(1) ; 
  double btagsf_bcDown(1) ; 
  double btagsf_lUp(1) ; 
  double btagsf_lDown(1) ; 

  if ( !isData ) { 

    if ( theTop != nullptr && theTop->getPt() >= 400. && theTop->getPt() < 550.) {
      toptagsf = 0.88 ;
      toptagsfUp = 0.88+0.15 ; 
      toptagsfDown = 0.88-0.15;
    }
    else if ( theTop != nullptr && theTop->getPt() >= 550.)  {
      toptagsf = 0.87 ;
      toptagsfUp = 0.87+0.35 ; 
      toptagsfDown = 0.87-0.35;
    }

    if ( theHiggs != nullptr ) {

      double sj0csv(theHiggs->getCSVSubjet0()) ; 
      double sj0pt (theHiggs->getPtSubjet0()) ; 
      double sj0fl (theHiggs->getHadronFlavourSubjet0()) ; 
      double sj1csv(theHiggs->getCSVSubjet1()) ; 
      double sj1pt (theHiggs->getPtSubjet1()) ; 
      double sj1fl (theHiggs->getHadronFlavourSubjet1()) ; 

      ////// Get btag SFs
      if ( sj0csv > 0.605 ) btagsf *= getBTagSF_CSVv2L(sj0pt, sj0fl, 0, 0) ; 
      else btagsf *= ( 1 - getBTagSF_CSVv2L(sj0pt, sj0fl,0,0)*getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
      if ( sj1csv > 0.605 ) btagsf *= getBTagSF_CSVv2L(sj1pt, sj1fl, 0, 0) ; 
      else btagsf *= ( 1 - getBTagSF_CSVv2L(sj1pt, sj1fl,0,0)*getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

      h1_["mtprime_btagsf"] -> Fill(Mtprime, evtwt*btagsf) ; 
      h1_["mtprime_corr_btagsf"] -> Fill(Mtprime_corr, evtwt*btagsf) ; 

      if (doBTagSFUnc_) {
        //// Get btag SF up bc err
        if ( sj0csv > 0.605 ) btagsf_bcUp *= getBTagSF_CSVv2L(sj0pt, sj0fl,1,0) ; 
        else btagsf_bcUp *= ( 1 - getBTagSF_CSVv2L(sj0pt, sj0fl,1,0)*getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
        if ( sj1csv > 0.605 ) btagsf_bcUp *= getBTagSF_CSVv2L(sj1pt, sj1fl,1,0) ; 
        else btagsf_bcUp *= ( 1 - getBTagSF_CSVv2L(sj1pt, sj1fl,1,0)*getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

        if ( sj0csv > 0.605 ) btagsf_bcDown *= getBTagSF_CSVv2L(sj0pt, sj0fl,-1,0) ; 
        else btagsf_bcDown *= ( 1 - getBTagSF_CSVv2L(sj0pt, sj0fl,-1,0)*getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
        if ( sj1csv > 0.605 ) btagsf_bcDown *= getBTagSF_CSVv2L(sj1pt, sj1fl,-1,0) ; 
        else btagsf_bcDown *= ( 1 - getBTagSF_CSVv2L(sj1pt, sj1fl,-1,0)*getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

        //// Get btag SF up light err
        if ( sj0csv > 0.605 ) btagsf_lUp *= getBTagSF_CSVv2L(sj0pt, sj0fl,0,1) ; 
        else btagsf_lUp *= ( 1 - getBTagSF_CSVv2L(sj0pt, sj0fl,0,1)*getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
        if ( sj1csv > 0.605 ) btagsf_lUp *= getBTagSF_CSVv2L(sj1pt, sj1fl,0,1) ; 
        else btagsf_lUp *= ( 1 - getBTagSF_CSVv2L(sj1pt, sj1fl,0,1)*getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

        if ( sj0csv > 0.605 ) btagsf_lDown *= getBTagSF_CSVv2L(sj0pt, sj0fl,0,-1) ; 
        else btagsf_lDown *= ( 1 - getBTagSF_CSVv2L(sj0pt, sj0fl,0,-1)*getBTagEff_CSVv2L(sj0pt, sj0fl) )/( 1 - getBTagEff_CSVv2L(sj0pt, sj0fl) ); 
        if ( sj1csv > 0.605 ) btagsf_lDown *= getBTagSF_CSVv2L(sj1pt, sj1fl,0,-1) ; 
        else btagsf_lDown *= ( 1 - getBTagSF_CSVv2L(sj1pt, sj1fl,0,-1)*getBTagEff_CSVv2L(sj1pt, sj1fl) )/( 1 - getBTagEff_CSVv2L(sj1pt, sj1fl) ); 

        //  h1_["mtprime_btagsf_bcUp"] -> Fill(Mtprime, evtwt*btagsf_bcUp) ; 
        //  h1_["mtprime_corr_btagsf_bcUp"] -> Fill(Mtprime_corr, evtwt*btagsf_bcUp) ; 

        //  h1_["mtprime_btagsf_bcDown"] -> Fill(Mtprime, evtwt*btagsf_bcDown) ; 
        //  h1_["mtprime_corr_btagsf_bcDown"] -> Fill(Mtprime_corr, evtwt*btagsf_bcDown) ; 

        //  h1_["mtprime_btagsf_lUp"] -> Fill(Mtprime, evtwt*btagsf_lUp) ; 
        //  h1_["mtprime_corr_btagsf_lUp"] -> Fill(Mtprime_corr, evtwt*btagsf_lUp) ; 

        //  h1_["mtprime_btagsf_lDown"] -> Fill(Mtprime, evtwt*btagsf_lDown) ; 
        //  h1_["mtprime_corr_btagsf_lDown"] -> Fill(Mtprime_corr, evtwt*btagsf_lDown) ; 
      }
    }
  }

  selectedevt_.EvtWeight_ = evtwt;
  selectedevt_.npv_ = *h_npv.product() ; 
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
  selectedevt_.isRegionA_ = isRegionA ; 
  selectedevt_.isRegionB_ = isRegionB ; 
  selectedevt_.isRegionC_ = isRegionC ; 
  selectedevt_.isRegionD_ = isRegionD ; 

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

  tree_ = fs->make<TTree>("tree", "TtHT") ; 
  selectedevt_.RegisterTree(tree_,"SelectedEvent") ; 
  jets_.RegisterTree(tree_,"JetInfo") ; 

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 7, 0.5, 7.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1,  "All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2,  "Trig.+PV") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3,  "N(AK4)>=4") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4,  "H_{T}>1000GeV") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5,  "N(AK8)>=1") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6,  "N(H)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7,  "N(top)>0") ; 

  h1_["npv_noreweight"] = fs->make<TH1D>("npv_noreweight", ";N(PV);;", 51, -0.5, 50.5) ; 
  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 

  h1_["mtprime"] = fs->make<TH1D>("mtprime", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled"] = fs->make<TH1D>("mtprime_scaled", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr"] = fs->make<TH1D>("mtprime_corr", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

  h1_["mtprime_btagsf"] = fs->make<TH1D>("mtprime_btagsf", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled_btagsf"] = fs->make<TH1D>("mtprime_scaled_btagsf", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr_btagsf"] = fs->make<TH1D>("mtprime_corr_btagsf", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

  h1_["mtprime_btagsf_bcUp"] = fs->make<TH1D>("mtprime_btagsf_bcUp", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled_btagsf_bcUp"] = fs->make<TH1D>("mtprime_scaled_btagsf_bcUp", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr_btagsf_bcUp"] = fs->make<TH1D>("mtprime_corr_btagsf_bcUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

  h1_["mtprime_btagsf_bcDown"] = fs->make<TH1D>("mtprime_btagsf_bcDown", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled_btagsf_bcDown"] = fs->make<TH1D>("mtprime_scaled_btagsf_bcDown", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr_btagsf_bcDown"] = fs->make<TH1D>("mtprime_corr_btagsf_bcDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

  h1_["mtprime_btagsf_lUp"] = fs->make<TH1D>("mtprime_btagsf_lUp", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled_btagsf_lUp"] = fs->make<TH1D>("mtprime_scaled_btagsf_lUp", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr_btagsf_lUp"] = fs->make<TH1D>("mtprime_corr_btagsf_lUp", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

  h1_["mtprime_btagsf_lDown"] = fs->make<TH1D>("mtprime_btagsf_lDown", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled_btagsf_lDown"] = fs->make<TH1D>("mtprime_scaled_btagsf_lDown", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr_btagsf_lDown"] = fs->make<TH1D>("mtprime_corr_btagsf_lDown", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

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

double VLQAna::getBTagEff_CSVv2L (double pt, double jetFl) {
  double eff(1) ; 
  if (jetFl == 5) eff = 0.8 ; 
  else if (jetFl == 4) eff = 0.3 ; 
  else if (jetFl == 0) eff = 0.1 ; 
  return eff ;
}

double VLQAna::getBTagSF_CSVv2L (double pt, double jetFl, double errbc, double errl) {
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

  return btagsf ; 
}

DEFINE_FWK_MODULE(VLQAna);
