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

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "Analysis/VLQAna/interface/JetSelector.h"
#include "Analysis/VLQAna/interface/HT.h"
#include "Analysis/VLQAna/interface/Utilities.h"

#include <TH1D.h>
#include <TLorentzVector.h>

class VLQAna : public edm::EDFilter {
  public:
    explicit VLQAna(const edm::ParameterSet&);
    ~VLQAna();

  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    edm::InputTag l_trigName                     ; 
    edm::InputTag l_trigBit                      ; 
    edm::InputTag l_jetAK8Pt                     ; 
    edm::InputTag l_jetAK8Eta                    ; 
    edm::InputTag l_jetAK8Phi                    ; 
    edm::InputTag l_jetAK8Mass                   ; 
    edm::InputTag l_jetAK8FilteredMass           ; 
    edm::InputTag l_jetAK8TrimmedMass            ; 
    edm::InputTag l_jetAK8PrunedMass             ; 
    edm::InputTag l_jetAK8SoftDropMass           ; 
    edm::InputTag l_jetAK8CSV                    ; 
    edm::InputTag l_jetAK4Pt                     ; 
    edm::InputTag l_jetAK4Eta                    ; 
    edm::InputTag l_jetAK4Phi                    ; 
    edm::InputTag l_jetAK4Mass                   ; 
    edm::InputTag l_jetAK4CSV                    ; 
    std::vector<std::string> hltPaths_           ; 
    edm::ParameterSet AK4JetSelParams_           ; 
    edm::ParameterSet BTaggedMediumAK4SelParams_ ; 
    edm::ParameterSet AK8JetSelParams_           ; 
    edm::ParameterSet TJetSelParams_             ; 
    edm::ParameterSet HJetSelParams_             ; 
    double minForwardEtaJet_                     ; 
    double HTMin_                                ; 

    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
};

using namespace std; 

VLQAna::VLQAna(const edm::ParameterSet& iConfig) :
  l_trigName                (iConfig.getParameter<edm::InputTag>     ("trigNameLabel")),
  l_trigBit                 (iConfig.getParameter<edm::InputTag>     ("trigBitLabel")),
  l_jetAK8Pt                (iConfig.getParameter<edm::InputTag>     ("jetAK8PtLabel")),  
  l_jetAK8Eta               (iConfig.getParameter<edm::InputTag>     ("jetAK8EtaLabel")),  
  l_jetAK8Phi               (iConfig.getParameter<edm::InputTag>     ("jetAK8PhiLabel")),  
  l_jetAK8Mass              (iConfig.getParameter<edm::InputTag>     ("jetAK8MassLabel")),  
  l_jetAK8FilteredMass      (iConfig.getParameter<edm::InputTag>     ("jetAK8FilteredMassLabel")),  
  l_jetAK8TrimmedMass       (iConfig.getParameter<edm::InputTag>     ("jetAK8TrimmedMassLabel")),  
  l_jetAK8PrunedMass        (iConfig.getParameter<edm::InputTag>     ("jetAK8PrunedMassLabel")),  
  l_jetAK8SoftDropMass      (iConfig.getParameter<edm::InputTag>     ("jetAK8SoftDropMassLabel")),  
  l_jetAK8CSV               (iConfig.getParameter<edm::InputTag>     ("jetAK8CSVLabel")),  
  l_jetAK4Pt                (iConfig.getParameter<edm::InputTag>     ("jetAK4PtLabel")),  
  l_jetAK4Eta               (iConfig.getParameter<edm::InputTag>     ("jetAK4EtaLabel")),  
  l_jetAK4Phi               (iConfig.getParameter<edm::InputTag>     ("jetAK4PhiLabel")),  
  l_jetAK4Mass              (iConfig.getParameter<edm::InputTag>     ("jetAK4MassLabel")),  
  l_jetAK4CSV               (iConfig.getParameter<edm::InputTag>     ("jetAK4CSVLabel")),  
  hltPaths_                 (iConfig.getParameter<vector<string>>    ("hltPaths")), 
  AK4JetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("AK4JetSelParams")),
  BTaggedMediumAK4SelParams_(iConfig.getParameter<edm::ParameterSet> ("BTaggedMediumAK4SelParams")),
  AK8JetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("AK8JetSelParams")),
  TJetSelParams_            (iConfig.getParameter<edm::ParameterSet> ("TJetSelParams")),
  HJetSelParams_            (iConfig.getParameter<edm::ParameterSet> ("HJetSelParams")),
  minForwardEtaJet_         (iConfig.getParameter<double>            ("minForwardEtaJet")), 
  HTMin_                    (iConfig.getParameter<double>            ("HTMin"))
{

}


VLQAna::~VLQAna() {
}

bool VLQAna::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  h1_["cutflow"] -> Fill(1) ; 

  typedef Handle <vector<string>> hstring ; 
  typedef Handle <vector<float>> hfloat ; 
  hstring h_trigName             ; evt.getByLabel (l_trigName               , h_trigName             );
  hfloat  h_trigBit              ; evt.getByLabel (l_trigBit                , h_trigBit              ); 
  hfloat  h_jetAK8Pt             ; evt.getByLabel (l_jetAK8Pt               , h_jetAK8Pt             );
  hfloat  h_jetAK8Eta            ; evt.getByLabel (l_jetAK8Eta              , h_jetAK8Eta            );
  hfloat  h_jetAK8Phi            ; evt.getByLabel (l_jetAK8Phi              , h_jetAK8Phi            );
  hfloat  h_jetAK8Mass           ; evt.getByLabel (l_jetAK8Mass             , h_jetAK8Mass           );
  hfloat  h_jetAK8FilteredMass   ; evt.getByLabel (l_jetAK8FilteredMass     , h_jetAK8FilteredMass   );
  hfloat  h_jetAK8TrimmedMass    ; evt.getByLabel (l_jetAK8TrimmedMass      , h_jetAK8TrimmedMass    );
  hfloat  h_jetAK8PrunedMass     ; evt.getByLabel (l_jetAK8PrunedMass       , h_jetAK8PrunedMass     );
  hfloat  h_jetAK8SoftDropMass   ; evt.getByLabel (l_jetAK8SoftDropMass     , h_jetAK8SoftDropMass   );
  hfloat  h_jetAK8CSV            ; evt.getByLabel (l_jetAK8CSV              , h_jetAK8CSV            );
  hfloat  h_jetAK4Pt             ; evt.getByLabel (l_jetAK4Pt               , h_jetAK4Pt             );
  hfloat  h_jetAK4Eta            ; evt.getByLabel (l_jetAK4Eta              , h_jetAK4Eta            );
  hfloat  h_jetAK4Phi            ; evt.getByLabel (l_jetAK4Phi              , h_jetAK4Phi            );
  hfloat  h_jetAK4Mass           ; evt.getByLabel (l_jetAK4Mass             , h_jetAK4Mass           );
  hfloat  h_jetAK4CSV            ; evt.getByLabel (l_jetAK4CSV              , h_jetAK4CSV            );

  unsigned int hltdecisions(0) ; 
  for ( const string& myhltpath : hltPaths_ ) {
    for (vector<string>::const_iterator it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it ) {
      if ( it->find(myhltpath) < std::string::npos) 
        hltdecisions |= int((h_trigBit.product())->at(it - (h_trigName.product())->begin())) << (it - (h_trigName.product())->begin()) ; 
    }
  }

  if (hltdecisions == 0) return false ; 
  h1_["cutflow"] -> Fill(2) ; 
  
  vlq::JetCollection goodAK8Jets, goodHJets, goodTJets; 
  JetSelector ak8jetsel(AK8JetSelParams_), hjetsel(HJetSelParams_), tjetsel(TJetSelParams_) ;
  for ( unsigned ijet = 0; ijet < (h_jetAK8Pt.product())->size(); ++ijet) {
    bool retak8jetsel(false), rethjetsel(false), rettjetsel(false) ;
    if (ak8jetsel(evt, ijet,retak8jetsel) == 0) continue ;
    vlq::Jet jet;
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
        (h_jetAK8Eta.product())->at(ijet), 
        (h_jetAK8Phi.product())->at(ijet), 
        (h_jetAK8Mass.product())->at(ijet) ) ;
    jet.setP4(jetP4) ; 
    jet.setFilteredMass((h_jetAK8FilteredMass.product())->at(ijet)) ; 
    jet.setTrimmedMass((h_jetAK8TrimmedMass.product())->at(ijet)) ; 
    jet.setPrunedMass((h_jetAK8PrunedMass.product())->at(ijet)) ; 
    jet.setSoftDropMass((h_jetAK8SoftDropMass.product())->at(ijet)) ; 
    jet.setCSV((h_jetAK8CSV.product())->at(ijet)) ;
    goodAK8Jets.push_back(jet) ;
    if (hjetsel(evt, ijet,rethjetsel) == true ) goodHJets.push_back(jet) ; 
    if (tjetsel(evt, ijet,rettjetsel) == true ) goodTJets.push_back(jet) ; 
  }

  if ( goodAK8Jets.size() < 2 ) return false ; 
  h1_["cutflow"] -> Fill(3) ; 

  vlq::JetCollection  goodAK4Jets, googBTaggedJets;
  JetSelector ak4jetsel(AK4JetSelParams_), btaggedmediumak4sel(BTaggedMediumAK4SelParams_) ;
  bool retak4jetsel(false), retbtaggedmediumak4sel(false) ; 
  for ( unsigned ijet = 0; ijet < (h_jetAK4Pt.product())->size(); ++ijet) {
    retak4jetsel = false ; retbtaggedmediumak4sel = false ;
    if (ak4jetsel(evt, ijet,retak4jetsel) == 0) continue ;
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
        (h_jetAK4Eta.product())->at(ijet), 
        (h_jetAK4Phi.product())->at(ijet), 
        (h_jetAK4Mass.product())->at(ijet) ) ;
    vlq::Jet jet;  
    jet.setP4(jetP4) ;
    jet.setCSV((h_jetAK4CSV.product())->at(ijet)) ;
    goodAK4Jets.push_back(jet) ;
    if ( btaggedmediumak4sel(evt, ijet,retbtaggedmediumak4sel) != 0 ) googBTaggedJets.push_back(jet) ; 
  }

  if ( goodAK4Jets.size() < 1 ) return false ; 
  HT htak4(goodAK4Jets) ; 
  if ( htak4.getHT() < HTMin_ ) return false; 
  h1_["cutflow"] -> Fill(4) ; 

  std::sort(goodAK4Jets.begin(), goodAK4Jets.end(), Utilities::sortByEta<vlq::Jet>) ; 

  if ( abs(goodAK4Jets.at(0).getEta()) < minForwardEtaJet_ ) return false ; 
  h1_["cutflow"] -> Fill(5) ; 

  if ( googBTaggedJets.size() < 1 ) return false ; 
  h1_["cutflow"] -> Fill(6) ; 

  if (goodHJets.size() < 1) return false ;
  h1_["cutflow"] -> Fill(7) ;

  if (goodTJets.size() < 1) return false ;
  h1_["cutflow"] -> Fill(8) ;

  return true ; 

}

// ------------ method called once each job just before starting event loop  ------------
void VLQAna::beginJob() {

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 8, 0.5, 8.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2, "Trigger") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3, "N(AK8)>1") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4, "H_{T} > 850 GeV") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5, "N(forward jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6, "N(b jet medium)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7, "N(H jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8, "N(top jet)>0") ; 

}

void VLQAna::endJob() {
  return ; 
}

DEFINE_FWK_MODULE(VLQAna);
