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

    // ----------member data ---------------------------
    edm::InputTag l_evttype                      ;
    edm::InputTag l_evtwtGen                     ;
    edm::InputTag l_evtwtPV                      ;
    edm::InputTag l_npv                          ;

    JetMaker jetAK4maker                         ; 
    JetMaker jetAK4BTaggedmaker                  ; 
    JetMaker jetAK8maker                         ; 
    JetMaker jetHTaggedmaker                     ; 
    JetMaker jetWTaggedmaker                     ; 
    JetMaker jetTopTaggedmaker                   ; 

    double HTMin_                                ; 

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
  jetAK4BTaggedmaker      (iConfig.getParameter<edm::ParameterSet> ("jetAK4BTaggedselParams")), 
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams")), 
  jetWTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetWTaggedselParams")), 
  jetTopTaggedmaker       (iConfig.getParameter<edm::ParameterSet> ("jetTopTaggedselParams")),  
  HTMin_                  (iConfig.getParameter<double>            ("HTMin"))
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

  h1_["cutflow"] -> Fill(1, evtwt) ; 

  h1_["npv_noreweight"] -> Fill(*h_npv.product(), *h_evtwtGen.product()); 
  h1_["npv"] -> Fill(*h_npv.product(), evtwt); 

  vlq::JetCollection goodAK4Jets, goodBTaggedAK4Jets, goodAK8Jets, goodHTaggedJets, goodWTaggedJets, goodTopTaggedJets;

  jetAK4maker(evt, goodAK4Jets) ;
  jetAK4BTaggedmaker(evt, goodBTaggedAK4Jets) ; 
  jetAK8maker(evt, goodAK8Jets); 
  jetHTaggedmaker(evt, goodHTaggedJets);
  jetWTaggedmaker(evt, goodWTaggedJets);
  jetTopTaggedmaker(evt, goodTopTaggedJets);

  if (goodAK4Jets.size() < 1) return false ; 

  //std::cout << " goodBTaggedAK4Jets size = " << goodBTaggedAK4Jets.size() << " goodWTaggedJets size = " << goodWTaggedJets.size() << " goodHTaggedJets size = " << goodHTaggedJets.size() << " goodTopTaggedJets size = " << goodTopTaggedJets.size() << std::endl ; 

  //vlq::JetCollection cleanedBJets ;
  //CandidateCleaner<vlq::JetCollection, vlq::JetCollection>cleanbjets ; 
  //cleanbjets.clean(cleanedBJets, goodBTaggedAK4Jets, goodHTaggedJets) ; 
  //goodBTaggedAK4Jets = cleanedBJets ; 
  //cleanedBJets.clear(); 
  //cleanbjets.clean(cleanedBJets, goodBTaggedAK4Jets, goodTopTaggedJets) ; 

  //std::cout << " /////////  goodBTaggedAK4Jets size = " << goodBTaggedAK4Jets.size() << " cleanedBJets size = " << cleanedBJets.size() << " goodWTaggedJets size = " << goodWTaggedJets.size() << " goodHTaggedJets size = " << goodHTaggedJets.size() << " goodTopTaggedJets size = " << goodTopTaggedJets.size() << std::endl ; 

  HT htak4(goodAK4Jets) ; 

  if (htak4.getHT() < HTMin_) return false ; 

  if (goodHTaggedJets.size() < 1 || goodTopTaggedJets.size() < 1) return 0 ; 

  if ( ((goodHTaggedJets.at(0)).getP4()).DeltaPhi((goodTopTaggedJets.at(0)).getP4()) < 1.2 ) return false ; 

  double Mtprime = ( ((goodHTaggedJets.at(0)).getP4()) + ((goodTopTaggedJets.at(0)).getP4()) ).Mag();  

  double Mtprime_scaled = ( ( ((goodHTaggedJets.at(0)).getP4())*(125./((goodHTaggedJets.at(0)).getPrunedMass())) ) + 
    ( ((goodTopTaggedJets.at(0)).getP4())*(172.5/((goodTopTaggedJets.at(0)).getPrunedMass())) ) ).Mag() ;  

  double Mtprime_corr = Mtprime - ((goodHTaggedJets.at(0)).getP4()).Mag() - ((goodTopTaggedJets.at(0)).getP4()).Mag() + 125. + 172.5 ; 

  h1_["mtprime"] -> Fill(Mtprime, evtwt) ; 
  h1_["mtprime_scaled"] -> Fill(Mtprime_scaled, evtwt) ; 
  h1_["mtprime_corr"] -> Fill(Mtprime_corr, evtwt) ; 

  return true ; 

  ////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////

  ////  vector<unsigned> ak4selIdxs, ak8selIdxs, bjetIdxs;
  ////
  ////  //// Store good AK8 jets
  ////  JetSelector ak8jetsel(AK8JetSelParams_) ;
  ////  for ( unsigned ijet = 0; ijet < (h_jetAK8Pt.product())->size(); ++ijet) {
  ////    bool retak8jetsel = false ; 
  ////    if (ak8jetsel(evt, ijet,retak8jetsel) == 0) { 
  ////      LogDebug("VLQAna") << " ak8 jet with pt = " << (h_jetAK8Pt.product())->at(ijet) << " fail jet sel\n" ; 
  ////      continue ;
  ////    }
  ////    TLorentzVector jetP4 ;
  ////    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
  ////        (h_jetAK8Eta.product())->at(ijet), 
  ////        (h_jetAK8Phi.product())->at(ijet), 
  ////        (h_jetAK8Mass.product())->at(ijet) ) ;
  ////    vlq::Jet jet;
  ////    jet.setP4(jetP4) ; 
  ////    jet.setFilteredMass((h_jetAK8FilteredMass.product())->at(ijet)) ; 
  ////    jet.setTrimmedMass((h_jetAK8TrimmedMass.product())->at(ijet)) ; 
  ////    jet.setPrunedMass((h_jetAK8PrunedMass.product())->at(ijet)) ; 
  ////    jet.setSoftDropMass((h_jetAK8SoftDropMass.product())->at(ijet)) ; 
  ////    jet.setCSV((h_jetAK8CSV.product())->at(ijet)) ;
  ////    goodAK8Jets.push_back(jet) ;
  ////    ak8selIdxs.push_back(ijet);
  ////  }
  ////
  ////  //// Preselection 2 AK8 jets 
  ////  if ( goodAK8Jets.size() < 1 ) return false ; 
  ////  if ( goodAK8Jets.size() > 1 && ( goodAK8Jets.at(0).getPt() < 300 || goodAK8Jets.at(1).getPt() < 220.) )  return false ; 
  ////
  ////  //// Store good AK4 jets 
  ////  JetSelector ak4jetsel(AK4JetSelParams_) ;
  ////  JetSelector btaggedlooseak4sel(BTaggedLooseAK4SelParams_) ;
  ////  JetSelector btaggedmediumak4sel(BTaggedMediumAK4SelParams_) ;
  ////  bool retak4jetsel = false ; 
  ////  bool retbtaggedlooseak4sel = false ; 
  ////  bool retbtaggedmediumak4sel = false ; 
  ////  for ( unsigned ijet = 0; ijet < (h_jetAK4Pt.product())->size(); ++ijet) {
  ////    retak4jetsel = false ;
  ////    retbtaggedlooseak4sel = false ;
  ////    retbtaggedmediumak4sel = false ;
  ////    if (ak4jetsel(evt, ijet,retak4jetsel) == 0) { 
  ////      LogDebug("VLQAna") << " ak4 jet with pt = " << (h_jetAK4Pt.product())->at(ijet) << " fail jet sel\n" ; 
  ////      continue ;
  ////    }
  ////    TLorentzVector jetP4 ;
  ////    jetP4.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
  ////        (h_jetAK4Eta.product())->at(ijet), 
  ////        (h_jetAK4Phi.product())->at(ijet), 
  ////        (h_jetAK4Mass.product())->at(ijet) ) ;
  ////    vlq::Jet jet;  
  ////    jet.setP4(jetP4) ;
  ////    jet.setCSV((h_jetAK4CSV.product())->at(ijet)) ;
  ////    goodAK4Jets.push_back(jet) ;
  ////    ak4selIdxs.push_back(ijet);
  ////    if ( btaggedlooseak4sel(evt, ijet,retbtaggedlooseak4sel) != 0 ) {
  ////      bjetIdxs.push_back(ijet) ; 
  ////      btaggedlooseAK4.push_back(jet) ; 
  ////    }
  ////    if ( btaggedmediumak4sel(evt, ijet,retbtaggedmediumak4sel) != 0 ) {
  ////      btaggedmediumAK4.push_back(jet) ; 
  ////    }
  ////  }
  ////
  ////  //// Preselection at least one b-tagged AK4 jet 
  ////  if ( btaggedlooseAK4.size() < 1 ) return false; 
  ////
  ////  //h1_["nak8_nocuts"] -> Fill(goodAK8Jets.size()) ; 
  ////  //h1_["nak4_nocuts"] -> Fill(goodAK4Jets.size()) ; 
  ////  //h1_["nbloose_nocuts"] -> Fill(btaggedlooseAK4.size()) ; 
  ////
  ////  //// Make W, top and H jets 
  ////  vector<unsigned> seltjets, selhjets, selwjets;
  ////  vlq::JetCollection tjets, hjets, wjets ; 
  ////  JetSelector tjetsel(TJetSelParams_) ;
  ////  JetSelector hjetsel(HJetSelParams_) ;
  ////  JetSelector wjetsel(WJetSelParams_) ;
  ////  bool rettjetsel = false ;
  ////  bool rethjetsel = false ;
  ////  bool retwjetsel = false ;
  ////  for ( unsigned  &ijet :  ak8selIdxs) {
  ////    TLorentzVector jetP4 ;
  ////    vector<float>drhjet_hpart, drhjet_bpart, drhjet_bbarpart ; 
  ////    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
  ////        (h_jetAK8Eta.product())->at(ijet), 
  ////        (h_jetAK8Phi.product())->at(ijet), 
  ////        (h_jetAK8Mass.product())->at(ijet) ) ;
  ////    for ( ihbb = h_HbbCands.product()->begin(); ihbb != h_HbbCands.product()->end(); ++ihbb ) {
  ////      TLorentzVector hp4 = (ihbb->getMothers().at(0)).getP4() ; 
  ////      drhjet_hpart.push_back(hp4.DeltaR(jetP4)) ; 
  ////      vlq::GenParticleCollection bs =  ( ihbb->getDaughters() ) ; 
  ////      for ( vlq::GenParticle& b : bs ) {
  ////        TLorentzVector bp4 = b.getP4() ; 
  ////        if ( b.getPdgID() == 5 ) {
  ////          drhjet_bpart.push_back(bp4.DeltaR(jetP4)) ; 
  ////        }
  ////        if ( b.getPdgID() == -5 ) {
  ////          drhjet_bbarpart.push_back(bp4.DeltaR(jetP4)) ; 
  ////        }
  ////      }
  ////    }
  ////    std::vector<float>::iterator iminh    = std::min_element(drhjet_hpart.begin(), drhjet_hpart.end());
  ////    std::vector<float>::iterator iminb    = std::min_element(drhjet_bpart.begin(), drhjet_bpart.end());
  ////    std::vector<float>::iterator iminbbar = std::min_element(drhjet_bbarpart.begin(), drhjet_bbarpart.end());
  ////    if ( iminh != drhjet_hpart.end() && iminb != drhjet_bpart.end() && iminbbar != drhjet_bbarpart.end() )
  ////      if ( *iminh < 0.8 && *iminb < 0.8 && *iminbbar < 0.8 ) 
  ////        h1_["ptak8"]->Fill(jetP4.Pt()) ; 
  ////    vlq::Jet jet; 
  ////    jet.setP4(jetP4) ;
  ////    jet.setCSV((h_jetAK8CSV.product())->at(ijet)) ;
  ////    rettjetsel = false ;
  ////    if (tjetsel(evt, ijet,rettjetsel) == true ) { 
  ////      tjets.push_back(jet) ; 
  ////      seltjets.push_back(ijet) ; 
  ////    }
  ////    rethjetsel = false ;
  ////    if (hjetsel(evt, ijet,rethjetsel) == true ) { 
  ////     hjets.push_back(jet) ; 
  ////     selhjets.push_back(ijet) ; 
  ////     h1_["csvhjets"] -> Fill((h_jetAK8CSV.product())->at(ijet)) ; 
  ////     if ( iminh != drhjet_hpart.end() && iminb != drhjet_bpart.end() && iminbbar != drhjet_bbarpart.end() )
  ////       if ( *iminh < 0.8  && *iminb < 0.8 && *iminbbar < 0.8 ) 
  ////         h1_["pthjets"]->Fill(jetP4.Pt()) ;
  ////    } 
  ////    retwjetsel = false ;
  ////    if (wjetsel(evt, ijet,retwjetsel) == true ) { 
  ////      wjets.push_back(jet) ; 
  ////      selwjets.push_back(ijet) ; 
  ////    } 
  ////  }
  ////
  ////  HT htak4(goodAK4Jets) ; 
  ////  //// Preselection HT
  ////  if ( htak4.getHT() < HTMin_ ) return false; 
  ////
  ////  h1_["cutflow"] -> AddBinContent(3) ; 
  ////
  ////  if (goodAK4Jets.size() > 0) {
  ////    std::sort(goodAK4Jets.begin(), goodAK4Jets.end(), Utilities::sortByCSV) ; 
  ////    h1_["ak4highestcsv_nocuts"] -> Fill((goodAK4Jets.at(0)).getCSV()) ;
  ////    std::sort(goodAK4Jets.begin(), goodAK4Jets.end(), Utilities::sortByPt<vlq::Jet>) ; 
  ////  }
  ////
  ////  HT htak8(goodAK8Jets) ; 
  ////
  ////  //// Selection H-tagged AK8 jet 
  ////  //if (hjets.size() < 1 ) return false; 
  ////
  ////  //double csvhleading(-1) ; 
  ////  //if (hjets.size() > 0 ) csvhleading = hjets.at(0).getCSV() ; 
  ////
  ////  //// Pick forwardmost AK4 jet
  ////  double maxeta(0) ;
  ////  vlq::Jet forwardestjet ; 
  ////  for ( auto& jet : goodAK4Jets ) {
  ////    if ( abs(jet.getEta()) > abs(maxeta) ) { 
  ////      forwardestjet = jet ; 
  ////      maxeta = jet.getEta() ; 
  ////    }
  ////  }
  ////
  ////  double ptak8_1 = goodAK8Jets.at(0).getP4().Pt() ;
  ////  double ptak8_2(0) ; 
  ////  goodAK8Jets.size() > 1 ?  ptak8_2 = goodAK8Jets.at(1).getP4().Pt() : 0 ; 
  ////  double mak8_1 = goodAK8Jets.at(0).getP4().Mag() ;
  ////  double mak8_2(0) ; 
  ////  goodAK8Jets.size() > 1 ?  mak8_2 = goodAK8Jets.at(1).getP4().Mag() : 0 ; 
  ////  double mak8_12(0) ; 
  ////  double detaLeading2AK8(-1) ; 
  ////  if (goodAK8Jets.size() > 1) {
  ////    TLorentzVector p4_ak8_12(goodAK8Jets.at(0).getP4() + goodAK8Jets.at(1).getP4()) ;
  ////    mak8_12 = p4_ak8_12.Mag() ; 
  ////    detaLeading2AK8 = abs(goodAK8Jets.at(0).getEta() - goodAK8Jets.at(1).getEta() ) ;
  ////  }
  ////
  ////  double ptak8leading ((goodAK8Jets.at(0)).getPt()) ; 
  ////  double mak8leading ((goodAK8Jets.at(0)).getMass()) ; 
  ////  double csvak8leading ((goodAK8Jets.at(0)).getCSV()) ; 
  ////
  ////  h1_["ptak8leading"] -> Fill(ptak8leading) ; 
  ////  h1_["etaak8leading"] -> Fill((goodAK8Jets.at(0)).getEta()) ;
  ////  h1_["mak8leading"] -> Fill(mak8leading) ; 
  ////  h1_["trimmedmak8leading"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass()) ;
  ////  h1_["softdropmak8leading"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass()) ;
  ////  h1_["csvak8leading"] -> Fill(csvak8leading) ;
  ////
  ////  double ptak82nd (0) ;
  ////  double mak82nd (0) ;
  ////  double csvak82nd (0) ; 
  ////  if (goodAK8Jets.size() > 1) {
  ////    ptak82nd = (goodAK8Jets.at(1)).getPt() ; 
  ////    mak82nd = (goodAK8Jets.at(1)).getMass() ; 
  ////    csvak82nd = (goodAK8Jets.at(1)).getCSV() ; 
  ////  }
  ////
  ////  h1_["ptak82nd"] -> Fill(ptak82nd) ; 
  ////  h1_["mak82nd"] -> Fill(mak82nd) ; 
  ////  h1_["csvak82nd"] -> Fill(csvak82nd) ;
  ////
  ////  h1_["ptak8leadingPlus2nd"] -> Fill(ptak8leading+ptak82nd) ; 
  ////
  ////  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortByMass<vlq::Jet>) ; 
  ////  h1_["mak8highestm"] -> Fill((goodAK8Jets.at(0)).getMass()) ; 
  ////
  ////  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortByTrimmedMass) ; 
  ////  h1_["trimmedmak8highesttrimmedm"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass()) ; 
  ////
  ////  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortBySoftDropMass) ; 
  ////  h1_["softdropmak8highestsoftdropm"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass()) ; 
  ////
  ////  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortByPt<vlq::Jet>) ; 
  ////
  ////  double ptak4leading ((h_jetAK4Pt.product())->at(ak4selIdxs.at(0))) ;   
  ////  h1_["ptak4leading"] -> Fill(ptak4leading) ; 
  ////  h1_["etaak4leading"] -> Fill((h_jetAK4Eta.product())->at(ak4selIdxs.at(0))) ; 
  ////
  ////  double ptbjetleading (-1);
  ////  double csvbjetleading (-1);
  ////  double csvbjethighestcsv(-1); 
  ////  if ( bjetIdxs.size() > 0 ) {
  ////    ptbjetleading = (h_jetAK4Pt.product())->at(bjetIdxs.at(0)) ; 
  ////    csvbjetleading = (h_jetAK4CSV.product())->at(bjetIdxs.at(0)) ; 
  ////    h1_["ptbjetleading"] -> Fill(ptbjetleading) ; 
  ////    h1_["etabjetleading"] -> Fill((h_jetAK4Eta.product())->at(bjetIdxs.at(0))) ; 
  ////    h1_["csvbjetleading"] -> Fill(csvbjetleading) ; 
  ////
  ////    std::sort(btaggedlooseAK4.begin(), btaggedlooseAK4.end(), Utilities::sortByCSV) ; 
  ////    csvbjethighestcsv = (btaggedlooseAK4.at(0)).getCSV() ; 
  ////    h1_["csvbjethighestcsv"] -> Fill(csvbjethighestcsv) ; 
  ////    h1_["ptak4highestcsv"] -> Fill((btaggedlooseAK4.at(0)).getPt()) ;
  ////    h1_["etaak4highestcsv"] -> Fill((btaggedlooseAK4.at(0)).getEta()) ;
  ////  }
  ////
  ////  h1_["ptak4forwardmost"] -> Fill(forwardestjet.getPt()) ; 
  ////  h1_["etaak4forwardmost"] -> Fill(forwardestjet.getEta()) ; 
  ////
  ////  h2_["pt_ak8_leading_2nd"] -> Fill(ptak8leading, ptak82nd) ; 
  ////  h2_["m_ak8_leading_2nd"] -> Fill(mak8leading, mak82nd) ; 
  ////  h2_["csv_ak8_leading_2nd"] -> Fill(csvak8leading, csvak82nd) ; 
  ////
  ////  h1_["nak8_presel"] -> Fill(goodAK8Jets.size()) ; 
  ////  h1_["nak4_presel"] -> Fill(goodAK4Jets.size()) ; 
  ////  h1_["nbloose_presel"] -> Fill(btaggedlooseAK4.size()) ; 
  ////  h1_["nbmedium_presel"] -> Fill(btaggedmediumAK4.size()) ; 
  ////
  ////  h1_["nwjet_presel"] -> Fill(wjets.size()) ; 
  ////  h1_["nhjet_presel"] -> Fill(hjets.size()) ; 
  ////  h1_["ntjet_presel"] -> Fill(tjets.size()) ; 
  ////
  ////  h1_["ht_presel"] ->Fill(htak4.getHT()) ; 
  ////
  ////  // Make H cands
  ////  std::vector<vlq::ResolvedVjj> wcands, hcands ; 
  ////  if (goodAK4Jets.size() > 1 && wjets.size() == 0) {
  ////    double mmin (60), mmax(100), drmax(1.2), smdmin(0.0), smdmax(0.5) ;  
  ////    VCandProducer WCandProducer(goodAK4Jets, mmin, mmax,drmax, smdmin, smdmax) ;  
  ////    WCandProducer.getCands(wcands) ; 
  ////  }
  ////  if (btaggedmediumAK4.size() > 1 && hjets.size() == 0) {
  ////    double mmin (100), mmax(140), drmax(1.2), smdmin(0.0), smdmax(0.5) ;  
  ////    VCandProducer HCandProducer(btaggedmediumAK4, mmin, mmax,drmax, smdmin, smdmax) ;  
  ////    HCandProducer.getCands(hcands) ; 
  ////  }
  ////
  ////  h1_["nwcand_presel"] -> Fill(hcands.size()) ; 
  ////  h1_["nhcand_presel"] -> Fill(hcands.size()) ; 
  ////
  ////  //// Event selection
  ////  if ( goodAK4Jets.size() < 6 ) return false ; 
  ////  h1_["cutflow"] -> AddBinContent(4) ; 
  ////
  ////  //// Event selection
  ////  if ( btaggedmediumAK4.size() < 1 || btaggedlooseAK4.size() < 3 ) return false ; 
  ////  h1_["cutflow"] -> AddBinContent(5) ; 
  ////
  ////  //// Event selection
  ////  if ( abs(forwardestjet.getEta()) < 2.5) return false ; 
  ////  h1_["cutflow"] -> AddBinContent(6) ; 
  ////
  ////  if (wcands.size() > 0) h1_["ptleadingwcand"] -> Fill((wcands.at(0)).getPt()) ; 
  ////  if (hcands.size() > 0) h1_["ptleadinghcand"] -> Fill((hcands.at(0)).getPt()) ; 
  ////  if (wjets.size() > 0) h1_["ptleadingwjet"] -> Fill((wjets.at(0)).getPt()) ; 
  ////  if (hjets.size() > 0) h1_["ptleadinghjet"] -> Fill((hjets.at(0)).getPt()) ; 
  ////  if (tjets.size() > 0) h1_["ptleadingtjet"] -> Fill((tjets.at(0)).getPt()) ; 
  ////
  ////  double drwh(-1) ;
  ////  if (hjets.size()>0 && wjets.size()>0) {
  ////    drwh = ((hjets.at(0)).getP4()).DeltaR((wjets.at(0)).getP4()) ; 
  ////  }
  ////  else if (hjets.size()>0 && wcands.size()>0) {
  ////    drwh = ((hjets.at(0)).getP4()).DeltaR((wcands.at(0)).getP4()) ; 
  ////  }
  ////  else if (hcands.size()>0 && wjets.size()>0) {
  ////    drwh = ((hcands.at(0)).getP4()).DeltaR((wjets.at(0)).getP4()) ; 
  ////  }
  ////  else if (hcands.size()>0 && wcands.size()>0) {
  ////    drwh = ((hcands.at(0)).getP4()).DeltaR((wcands.at(0)).getP4()) ; 
  ////  } 
  ////
  ////  h1_["drwh"] -> Fill(drwh) ; 
  ////
  ////  if (wjets.size()>0) h1_["cutflow"] -> AddBinContent(7) ;  
  ////  if (hjets.size()>0) h1_["cutflow"] -> AddBinContent(8) ;  
  ////  if (tjets.size()>0) h1_["cutflow"] -> AddBinContent(9) ;  
  ////
  ////  if (wjets.size()>0&&hjets.size()>0) h1_["cutflow"] -> AddBinContent(10) ;  
  ////  if (hjets.size()>0&&tjets.size()>0) h1_["cutflow"] -> AddBinContent(11) ;  
  ////
  ////  if (wjets.size()==0&&wcands.size()>0) h1_["cutflow"] -> AddBinContent(12) ;  
  ////  if (hjets.size()==0&&hcands.size()>0) h1_["cutflow"] -> AddBinContent(13) ;  
  ////
  ////  if ( (wjets.size()>0 || wcands.size()>0 ) && (hjets.size()>0 || hcands.size()>0) ) h1_["cutflow"] -> AddBinContent(14) ;  
  ////
  ////  h1_["nak8"] -> Fill(goodAK8Jets.size()) ; 
  ////  h1_["nak4"] -> Fill(goodAK4Jets.size()) ; 
  ////  h1_["nbloose"] -> Fill(btaggedlooseAK4.size()) ; 
  ////  h1_["nbmedium"] -> Fill(btaggedmediumAK4.size()) ; 
  ////
  ////  h1_["nwjet"] -> Fill(wjets.size()) ; 
  ////  h1_["nhjet"] -> Fill(hjets.size()) ; 
  ////  h1_["ntjet"] -> Fill(tjets.size()) ; 
  ////
  ////  h1_["nwcand_presel"] -> Fill(hcands.size()) ; 
  ////  h1_["nhcand_presel"] -> Fill(hcands.size()) ; 
  ////
  ////  h1_["ht"] ->Fill(htak4.getHT()) ; 
  ////
  ////  if (wjets.size()>0) h1_["ht_nwjetGt0"] ->Fill(htak4.getHT()) ; 
  ////  if (hjets.size()>0) h1_["ht_nhjetGt0"] ->Fill(htak4.getHT()) ; 
  ////  if (tjets.size()>0) h1_["ht_ntjetGt0"] ->Fill(htak4.getHT()) ; 
  ////  if (wjets.size()>0&&hjets.size()>0) h1_["ht_nwhjetGt0"] ->Fill(htak4.getHT()) ; 
  ////  if (hjets.size()>0&&tjets.size()>0) h1_["ht_nhtjetGt0"] ->Fill(htak4.getHT()) ; 
  ////  if (wjets.size()==0&&wcands.size()>0) h1_["ht_nwcandGt0"] ->Fill(htak4.getHT()) ; 
  ////  if (hjets.size()==0&&hcands.size()>0) h1_["ht_nhcandGt0"] ->Fill(htak4.getHT()) ; 
  ////
  ////  std::auto_ptr<unsigned> ngoodAK4Jets ( new unsigned(goodAK4Jets.size()) );
  ////  std::auto_ptr<unsigned> ngoodAK8Jets ( new unsigned(goodAK8Jets.size()) );
  ////  std::auto_ptr<unsigned> nTJets ( new unsigned(tjets.size()) );
  ////  std::auto_ptr<unsigned> nHJets ( new unsigned(hjets.size()) );
  ////  std::auto_ptr<unsigned> nWJets ( new unsigned(wjets.size()) );
  ////  std::auto_ptr<unsigned> nbtaggedlooseAK4 ( new unsigned(btaggedlooseAK4.size()) );
  ////  std::auto_ptr<double> htak4jets ( new double(htak4.getHT()) );
  ////  std::auto_ptr<double> htak8jets ( new double(htak8.getHT()) );
  ////  std::auto_ptr<double> maxetaak4 ( new double(maxeta) );
  ////  std::auto_ptr<double> MassLeading2AK8 ( new double(mak8_12) );
  ////  std::auto_ptr<double> DeltaEtaLeading2AK8 ( new double(detaLeading2AK8) );
  ////  std::auto_ptr<double> pt1stAK8   ( new double(ptak8_1) );
  ////  std::auto_ptr<double> pt2ndAK8   ( new double(ptak8_2) );
  ////  std::auto_ptr<double> mass1stAK8 ( new double(mak8_1) );
  ////  std::auto_ptr<double> mass2ndAK8 ( new double(mak8_2) );
  ////  std::auto_ptr<vector<unsigned> > ak4goodjets ( new vector<unsigned>(ak4selIdxs));
  ////  std::auto_ptr<vector<unsigned> > ak8goodjets ( new vector<unsigned>(ak8selIdxs));
  ////  std::auto_ptr<vector<unsigned> > bjetIdxsptr ( new vector<unsigned>(bjetIdxs));
  ////  std::auto_ptr<vector<unsigned> > tjetIdxs ( new vector<unsigned>(seltjets));
  ////  std::auto_ptr<vector<unsigned> > hjetIdxs ( new vector<unsigned>(selhjets));
  ////  std::auto_ptr<vector<unsigned> > wjetIdxs ( new vector<unsigned>(selwjets));
  ////
  ////  evt.put(ngoodAK4Jets, "ngoodAK4Jets") ; 
  ////  evt.put(ngoodAK8Jets, "ngoodAK8Jets") ; 
  ////  evt.put(nTJets, "nTJets") ; 
  ////  evt.put(nHJets, "nHJets") ; 
  ////  evt.put(nWJets, "nWJets") ; 
  ////  evt.put(nbtaggedlooseAK4, "nbtaggedlooseAK4") ; 
  ////  evt.put(maxetaak4, "maxetaak4") ; 
  ////  evt.put(MassLeading2AK8, "MassLeading2AK8") ; 
  ////  evt.put(DeltaEtaLeading2AK8, "DeltaEtaLeading2AK8") ; 
  ////  evt.put(pt1stAK8  , "pt1stAK8") ; 
  ////  evt.put(pt2ndAK8  , "pt2ndAK8") ; 
  ////  evt.put(mass1stAK8, "mass1stAK8") ; 
  ////  evt.put(mass2ndAK8, "mass2ndAK8") ; 
  ////  evt.put(htak4jets, "htak4jets") ; 
  ////  evt.put(htak8jets, "htak8jets") ; 
  ////  evt.put(ak4goodjets, "ak4goodjets");
  ////  evt.put(ak8goodjets, "ak8goodjets");
  ////  evt.put(bjetIdxsptr, "bjetIdxs");
  ////  evt.put(tjetIdxs, "tjetIdxs");
  ////  evt.put(hjetIdxs, "hjetIdxs");
  ////  evt.put(wjetIdxs, "wjetIdxs");

  return true ; 

}

// ------------ method called once each job just before starting event loop  ------------
void VLQAna::beginJob() {

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 14, 0, 14) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2, "Trigger") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3, "Presel") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4, "N(AK4)>5") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5, "N(b jet medium)>0 && N(b jet loose)>2") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6, "Forward jet") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7, "N(W jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8, "N(H jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9, "N(top jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(10, "N(W jet)>0 and N(H jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(11, "N(H jet)>0 and N(top jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(12, "N(W cand)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(13, "N(H cand)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(14, "N(W jet or cand)>0 and N(H jet or cand)>0") ; 

  h1_["npv_noreweight"] = fs->make<TH1D>("npv_noreweight", ";N(PV);;", 51, -0.5, 50.5) ; 
  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 
  
  h1_["mtprime"] = fs->make<TH1D>("mtprime", "M(T) without any correction;M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_scaled"] = fs->make<TH1D>("mtprime_scaled", "M(T) with Higgs and top p4 scaled to M(H) and M(top);M(T) [GeV];;",40,500,2500) ; 
  h1_["mtprime_corr"] = fs->make<TH1D>("mtprime_corr", "M(T) - M(H-jet) - M(top-jet) + M(H) + M(top);M(T) [GeV];;",40,500,2500) ; 

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

DEFINE_FWK_MODULE(VLQAna);
