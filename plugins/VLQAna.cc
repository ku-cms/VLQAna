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

};

using namespace std; 

VLQAna::VLQAna(const edm::ParameterSet& iConfig) :
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

  Handle<string>h_evttype  ; evt.getByLabel(l_evttype  , h_evttype  ) ; 
  Handle<double>h_evtwtGen ; evt.getByLabel(l_evtwtGen, h_evtwtGen) ; 
  Handle<double>h_evtwtPV  ; evt.getByLabel(l_evtwtPV,  h_evtwtPV ) ; 
  Handle<unsigned>h_npv    ; evt.getByLabel(l_npv, h_npv) ; 

  double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 

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

  if ( theHiggs != nullptr ) h1_["cutflow"] -> Fill(6, evtwt) ; 
  if ( theHiggs != nullptr && theTop != nullptr ) h1_["cutflow"] -> Fill(7, evtwt) ; 

  bool isOneOfABCD(isRegionA ^ isRegionB ^ isRegionC ^ isRegionD) ;
  if (isOneOfABCD == true) edm::LogInfo("ERROR ABCD") << ">>>> Check ABCD logic: Only one of A, B C, D should be true\n" ; 
  //if (isOneOfABCD == false) return false ; 
  //std::cout << " isRegionA " << isRegionA << std::endl ; 
  //std::cout << " isRegionB " << isRegionB << std::endl ; 
  //std::cout << " isRegionC " << isRegionC << std::endl ; 
  //std::cout << " isRegionD " << isRegionD << std::endl ; 

  TLorentzVector p4_tprime, p4_TprimeDummy ; 
  double Mtprime(0), Mtprime_corr(0) ; 

  if (isRegionD) {
    p4_tprime = theTop->getP4() + theHiggs->getP4() ; 
    double Mtprime = p4_tprime.Mag();
    double Mtprime_corr = Mtprime - theTop->getSoftDropMass() - theHiggs->getPrunedMass() + 172.5 + 125. ; 
    h1_["mtprime"] -> Fill(Mtprime, evtwt) ; 
    h1_["mtprime_corr"] -> Fill(Mtprime_corr, evtwt) ; 
  }
  else if (isRegionB) p4_TprimeDummy = theTop->getP4() + theAntiHiggs->getP4() ; 

  return true;


  double btagsf(1) ; 
  double btagsf_bcUp(1) ; 
  double btagsf_bcDown(1) ; 
  double btagsf_lUp(1) ; 
  double btagsf_lDown(1) ; 

  double sj0csv(theHiggs->getCSVSubjet0()) ; 
  double sj0pt (theHiggs->getPtSubjet0()) ; 
  double sj0fl (theHiggs->getHadronFlavourSubjet0()) ; 
  double sj1csv(theHiggs->getCSVSubjet1()) ; 
  double sj1pt (theHiggs->getPtSubjet1()) ; 
  double sj1fl (theHiggs->getHadronFlavourSubjet1()) ; 

  //// Get btag SFs
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

    h1_["mtprime_btagsf_bcUp"] -> Fill(Mtprime, evtwt*btagsf_bcUp) ; 
    h1_["mtprime_corr_btagsf_bcUp"] -> Fill(Mtprime_corr, evtwt*btagsf_bcUp) ; 

    h1_["mtprime_btagsf_bcDown"] -> Fill(Mtprime, evtwt*btagsf_bcDown) ; 
    h1_["mtprime_corr_btagsf_bcDown"] -> Fill(Mtprime_corr, evtwt*btagsf_bcDown) ; 

    h1_["mtprime_btagsf_lUp"] -> Fill(Mtprime, evtwt*btagsf_lUp) ; 
    h1_["mtprime_corr_btagsf_lUp"] -> Fill(Mtprime_corr, evtwt*btagsf_lUp) ; 

    h1_["mtprime_btagsf_lDown"] -> Fill(Mtprime, evtwt*btagsf_lDown) ; 
    h1_["mtprime_corr_btagsf_lDown"] -> Fill(Mtprime_corr, evtwt*btagsf_lDown) ; 
  }

  return true ; 

}

// ------------ method called once each job just before starting event loop  ------------
void VLQAna::beginJob() {

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
