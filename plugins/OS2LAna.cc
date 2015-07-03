// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      OS2LAna
// 
/**\class VLQAna OS2LAna.cc Analysis/VLQAna/plugins/OS2LAna.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Devdatta Majumder
//         Created:  Fri, 27 Feb 2015 16:09:10 GMT
//
//


// system include files
#include <iostream>
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Muon.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Electron.h"
#include "Analysis/VLQAna/interface/JetSelector.h"
#include "Analysis/VLQAna/interface/HT.h"
#include "Analysis/VLQAna/interface/VCandProducer.h"
#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/MuonSelector.h"
#include "Analysis/VLQAna/interface/ElectronSelector.h"
#include "Analysis/VLQAna/interface/ZCandidateProducer.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>

#include <sstream>

//
// class declaration
//

class OS2LAna : public edm::EDFilter {
  public:
    explicit OS2LAna(const edm::ParameterSet&);
    ~OS2LAna();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
    std::string pn_;
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
    edm::InputTag l_jetAK8Energy                 ; 
    edm::InputTag l_jetAK8Flavour                ; 
    edm::InputTag l_jetAK8CSV                    ; 
    edm::InputTag l_jetAK8JEC                    ; 
    edm::InputTag l_jetAK8Area                   ; 
    edm::InputTag l_jetAK8Tau1                   ;  
    edm::InputTag l_jetAK8Tau2                   ;  
    edm::InputTag l_jetAK8Tau3                   ;  
    edm::InputTag l_jetAK8nSubJets               ;  
    edm::InputTag l_jetAK8minmass                ;  
    edm::InputTag l_jetAK8VSubjetIndex0          ;  
    edm::InputTag l_jetAK8VSubjetIndex1          ;  
    edm::InputTag l_jetAK8TopSubjetIndex0        ; 
    edm::InputTag l_jetAK8TopSubjetIndex1        ; 
    edm::InputTag l_jetAK8TopSubjetIndex2        ; 
    edm::InputTag l_jetAK8TopSubjetIndex3        ; 
    edm::InputTag l_subjetAK8BDisc               ; 
    edm::InputTag l_subjetAK8Pt                  ; 
    edm::InputTag l_subjetAK8Eta                 ; 
    edm::InputTag l_subjetAK8Phi                 ; 
    edm::InputTag l_subjetAK8Mass                ; 
    edm::InputTag l_subjetCmsTopTagBDisc         ; 
    edm::InputTag l_subjetCmsTopTagPt            ; 
    edm::InputTag l_subjetCmsTopTagEta           ; 
    edm::InputTag l_subjetCmsTopTagPhi           ; 
    edm::InputTag l_subjetCmsTopTagMass          ; 
    edm::InputTag l_jetAK4Pt                     ; 
    edm::InputTag l_jetAK4Eta                    ; 
    edm::InputTag l_jetAK4Phi                    ; 
    edm::InputTag l_jetAK4Mass                   ; 
    edm::InputTag l_jetAK4Energy                 ; 
    edm::InputTag l_jetAK4Flavour                ; 
    edm::InputTag l_jetAK4CSV                    ; 
    edm::InputTag l_jetAK4JEC                    ; 
    edm::InputTag l_jetAK4nHadEnergy             ;
    edm::InputTag l_jetAK4nEMEnergy              ;
    edm::InputTag l_jetAK4HFHadronEnergy         ;
    edm::InputTag l_jetAK4cHadEnergy             ;
    edm::InputTag l_jetAK4cEMEnergy              ;
    edm::InputTag l_jetAK4numDaughters           ;
    edm::InputTag l_jetAK4cMultip                ;
    edm::InputTag l_jetAK4Y                      ;
    edm::InputTag l_jetAK4Area                   ; 
    edm::InputTag l_muPt                         ;
    edm::InputTag l_muEta                        ;
    edm::InputTag l_muY                          ;
    edm::InputTag l_muPhi                        ;
    edm::InputTag l_muMass                       ;
    edm::InputTag l_muE                          ;
    edm::InputTag l_muCharge                     ;
    edm::InputTag l_elPt                         ;
    edm::InputTag l_elEta                        ;
    edm::InputTag l_elY                          ;
    edm::InputTag l_elPhi                        ;
    edm::InputTag l_elMass                       ;
    edm::InputTag l_elE                          ;
    edm::InputTag l_elCharge                     ;
    edm::InputTag l_HbbCands                     ; 
    std::vector<std::string> hltPaths_           ; 
    edm::ParameterSet GenHSelParams_             ; 
    edm::ParameterSet AK4JetSelParams_           ; 
    edm::ParameterSet BTaggedLooseAK4SelParams_  ; 
    edm::ParameterSet BTaggedMediumAK4SelParams_ ; 
    edm::ParameterSet mupselParams_              ; 
    edm::ParameterSet mumselParams_              ; 
    edm::ParameterSet elpselParams_              ; 
    edm::ParameterSet elmselParams_              ; 
    edm::ParameterSet AK8JetSelParams_           ; 
    edm::ParameterSet TJetSelParams_             ; 
    edm::ParameterSet HJetSelParams_             ; 
    edm::ParameterSet WJetSelParams_             ; 
    double ak8jetsPtMin_                         ;
    double ak8jetsEtaMax_                        ; 
    double ak4jetsPtMin_                         ;
    double ak4jetsEtaMax_                        ; 
    double HTMin_                                ; 

    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    std::map<std::string, TH2D*> h2_             ; 

};

using namespace std; 

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
OS2LAna::OS2LAna(const edm::ParameterSet& iConfig) :
  pn_                     (iConfig.getParameter<string>            ("processName")),
  l_trigName              (iConfig.getParameter<edm::InputTag>     ("trigNameLabel")),
  l_trigBit               (iConfig.getParameter<edm::InputTag>     ("trigBitLabel")),
  l_jetAK8Pt              (iConfig.getParameter<edm::InputTag>     ("jetAK8PtLabel")),  
  l_jetAK8Eta             (iConfig.getParameter<edm::InputTag>     ("jetAK8EtaLabel")),  
  l_jetAK8Phi             (iConfig.getParameter<edm::InputTag>     ("jetAK8PhiLabel")),  
  l_jetAK8Mass            (iConfig.getParameter<edm::InputTag>     ("jetAK8MassLabel")),  
  l_jetAK8FilteredMass    (iConfig.getParameter<edm::InputTag>     ("jetAK8FilteredMassLabel")),  
  l_jetAK8TrimmedMass     (iConfig.getParameter<edm::InputTag>     ("jetAK8TrimmedMassLabel")),  
  l_jetAK8PrunedMass      (iConfig.getParameter<edm::InputTag>     ("jetAK8PrunedMassLabel")),  
  l_jetAK8SoftDropMass    (iConfig.getParameter<edm::InputTag>     ("jetAK8SoftDropMassLabel")),  
  l_jetAK8Energy          (iConfig.getParameter<edm::InputTag>     ("jetAK8EnergyLabel")),  
  l_jetAK8Flavour         (iConfig.getParameter<edm::InputTag>     ("jetAK8FlavourLabel")),  
  l_jetAK8CSV             (iConfig.getParameter<edm::InputTag>     ("jetAK8CSVLabel")),  
  l_jetAK8JEC             (iConfig.getParameter<edm::InputTag>     ("jetAK8JECLabel")), 
  l_jetAK8Area            (iConfig.getParameter<edm::InputTag>     ("jetAK8AreaLabel")),
  l_jetAK8Tau1            (iConfig.getParameter<edm::InputTag>     ("jetAK8Tau1Label")),  
  l_jetAK8Tau2            (iConfig.getParameter<edm::InputTag>     ("jetAK8Tau2Label")),  
  l_jetAK8Tau3            (iConfig.getParameter<edm::InputTag>     ("jetAK8Tau3Label")),  
  l_jetAK8nSubJets        (iConfig.getParameter<edm::InputTag>     ("jetAK8nSubJetsLabel")),  
  l_jetAK8minmass         (iConfig.getParameter<edm::InputTag>     ("jetAK8minmassLabel")),  
  l_jetAK8VSubjetIndex0   (iConfig.getParameter<edm::InputTag>     ("jetAK8VSubjetIndex0Label")),  
  l_jetAK8VSubjetIndex1   (iConfig.getParameter<edm::InputTag>     ("jetAK8VSubjetIndex1Label")),  
  l_jetAK8TopSubjetIndex0 (iConfig.getParameter<edm::InputTag>     ("jetAK8TopSubjetIndex0Label")), 
  l_jetAK8TopSubjetIndex1 (iConfig.getParameter<edm::InputTag>     ("jetAK8TopSubjetIndex1Label")), 
  l_jetAK8TopSubjetIndex2 (iConfig.getParameter<edm::InputTag>     ("jetAK8TopSubjetIndex2Label")), 
  l_jetAK8TopSubjetIndex3 (iConfig.getParameter<edm::InputTag>     ("jetAK8TopSubjetIndex3Label")), 
  l_subjetAK8BDisc        (iConfig.getParameter<edm::InputTag>     ("subjetAK8BDiscLabel")), 
  l_subjetAK8Pt           (iConfig.getParameter<edm::InputTag>     ("subjetAK8PtLabel")), 
  l_subjetAK8Eta          (iConfig.getParameter<edm::InputTag>     ("subjetAK8EtaLabel")), 
  l_subjetAK8Phi          (iConfig.getParameter<edm::InputTag>     ("subjetAK8PhiLabel")), 
  l_subjetAK8Mass         (iConfig.getParameter<edm::InputTag>     ("subjetAK8MassLabel")), 
  l_subjetCmsTopTagBDisc  (iConfig.getParameter<edm::InputTag>     ("subjetCmsTopTagBDiscLabel")), 
  l_subjetCmsTopTagPt     (iConfig.getParameter<edm::InputTag>     ("subjetCmsTopTagPtLabel")), 
  l_subjetCmsTopTagEta    (iConfig.getParameter<edm::InputTag>     ("subjetCmsTopTagEtaLabel")), 
  l_subjetCmsTopTagPhi    (iConfig.getParameter<edm::InputTag>     ("subjetCmsTopTagPhiLabel")), 
  l_subjetCmsTopTagMass   (iConfig.getParameter<edm::InputTag>     ("subjetCmsTopTagMassLabel")), 
  l_jetAK4Pt              (iConfig.getParameter<edm::InputTag>     ("jetAK4PtLabel")),  
  l_jetAK4Eta             (iConfig.getParameter<edm::InputTag>     ("jetAK4EtaLabel")),  
  l_jetAK4Phi             (iConfig.getParameter<edm::InputTag>     ("jetAK4PhiLabel")),  
  l_jetAK4Mass            (iConfig.getParameter<edm::InputTag>     ("jetAK4MassLabel")),  
  l_jetAK4Energy          (iConfig.getParameter<edm::InputTag>     ("jetAK4EnergyLabel")),  
  l_jetAK4Flavour         (iConfig.getParameter<edm::InputTag>     ("jetAK4FlavourLabel")),  
  l_jetAK4CSV             (iConfig.getParameter<edm::InputTag>     ("jetAK4CSVLabel")),  
  l_jetAK4JEC             (iConfig.getParameter<edm::InputTag>     ("jetAK4JECLabel")),
  l_jetAK4nHadEnergy      (iConfig.getParameter<edm::InputTag>     ("jetAK4nHadEnergyLabel")),
  l_jetAK4nEMEnergy       (iConfig.getParameter<edm::InputTag>     ("jetAK4nEMEnergyLabel")),
  l_jetAK4HFHadronEnergy  (iConfig.getParameter<edm::InputTag>     ("jetAK4HFHadronEnergyLabel")),
  l_jetAK4cHadEnergy      (iConfig.getParameter<edm::InputTag>     ("jetAK4cHadEnergyLabel")),
  l_jetAK4cEMEnergy       (iConfig.getParameter<edm::InputTag>     ("jetAK4cEMEnergyLabel")),
  l_jetAK4numDaughters    (iConfig.getParameter<edm::InputTag>     ("jetAK4numDaughtersLabel")),
  l_jetAK4cMultip         (iConfig.getParameter<edm::InputTag>     ("jetAK4cMultipLabel")),
  l_jetAK4Y               (iConfig.getParameter<edm::InputTag>     ("jetAK4YLabel")),
  l_jetAK4Area            (iConfig.getParameter<edm::InputTag>     ("jetAK4AreaLabel")),
  l_muPt                  (iConfig.getParameter<edm::InputTag>     ("muPt")), 
  l_muEta                 (iConfig.getParameter<edm::InputTag>     ("muEta")), 
  l_muY                   (iConfig.getParameter<edm::InputTag>     ("muY")),
  l_muPhi                 (iConfig.getParameter<edm::InputTag>     ("muPhi")), 
  l_muMass                (iConfig.getParameter<edm::InputTag>     ("muMass")), 
  l_muE                   (iConfig.getParameter<edm::InputTag>     ("muE")), 
  l_muCharge              (iConfig.getParameter<edm::InputTag>     ("muCharge")), 
  l_elPt                  (iConfig.getParameter<edm::InputTag>     ("elPt")), 
  l_elEta                 (iConfig.getParameter<edm::InputTag>     ("elEta")), 
  l_elY                   (iConfig.getParameter<edm::InputTag>     ("elY")),
  l_elPhi                 (iConfig.getParameter<edm::InputTag>     ("elPhi")), 
  l_elMass                (iConfig.getParameter<edm::InputTag>     ("elMass")), 
  l_elE                   (iConfig.getParameter<edm::InputTag>     ("elE")), 
  l_elCharge              (iConfig.getParameter<edm::InputTag>     ("elCharge")), 
  l_HbbCands              (iConfig.getParameter<edm::InputTag>     ("HbbCandsLabel")),
  hltPaths_               (iConfig.getParameter<vector<string>>    ("hltPaths")), 
  GenHSelParams_          (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
  AK4JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK4JetSelParams")),
  BTaggedLooseAK4SelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedLooseAK4SelParams")),
  BTaggedMediumAK4SelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedMediumAK4SelParams")),
  mupselParams_           (iConfig.getParameter<edm::ParameterSet> ("mupselParams")),
  mumselParams_           (iConfig.getParameter<edm::ParameterSet> ("mumselParams")),
  elpselParams_           (iConfig.getParameter<edm::ParameterSet> ("elpselParams")),
  elmselParams_           (iConfig.getParameter<edm::ParameterSet> ("elmselParams")),
  AK8JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK8JetSelParams")),
  TJetSelParams_          (iConfig.getParameter<edm::ParameterSet>  ("TJetSelParams")),
  HJetSelParams_          (iConfig.getParameter<edm::ParameterSet>  ("HJetSelParams")),
  WJetSelParams_          (iConfig.getParameter<edm::ParameterSet>  ("WJetSelParams")),
  ak8jetsPtMin_           (iConfig.getParameter<double>            ("ak8jetsPtMin")),
  ak8jetsEtaMax_          (iConfig.getParameter<double>            ("ak8jetsEtaMax")), 
  ak4jetsPtMin_           (iConfig.getParameter<double>            ("ak4jetsPtMin")),
  ak4jetsEtaMax_          (iConfig.getParameter<double>            ("ak4jetsEtaMax")), 
  HTMin_                  (iConfig.getParameter<double>            ("HTMin"))
{
  produces<unsigned>("ngoodAK4Jets");
  produces<unsigned>("ngoodAK8Jets");
  produces<unsigned>("nbtaggedlooseAK4");
  produces<unsigned>("nTJets");
  produces<unsigned>("nHJets");
  produces<unsigned>("nWJets");
  produces<double>("htak4jets");
  produces<double>("htak8jets");
  produces<double>("maxetaak4");
  produces<double>("MassLeading2AK8");
  produces<double>("DeltaEtaLeading2AK8");
  produces<double>("pt1stAK8");
  produces<double>("pt2ndAK8");
  produces<double>("mass1stAK8");
  produces<double>("mass2ndAK8");
  produces<vector<unsigned> >("ak4goodjets");
  produces<vector<unsigned> >("ak8goodjets");
  produces<vector<unsigned>>("bjetIdxs");
  produces<vector<unsigned>>("tjetIdxs");
  produces<vector<unsigned>>("hjetIdxs");
  produces<vector<unsigned>>("wjetIdxs");

  //register your products
  /* Examples
     produces<ExampleData2>();

  //if do put with a label
  produces<ExampleData2>("label");

  //if you want to put into the Run
  produces<ExampleData2,InRun>();
  */
  //now do what ever other initialization is needed

}


OS2LAna::~OS2LAna() {
}


//
// member functions
//

// ------------ method called to produce the data  ------------
bool OS2LAna::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

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
  hfloat  h_jetAK8Energy         ; evt.getByLabel (l_jetAK8Energy           , h_jetAK8Energy         );
  hfloat  h_jetAK8Flavour        ; evt.getByLabel (l_jetAK8Flavour          , h_jetAK8Flavour        );
  hfloat  h_jetAK8CSV            ; evt.getByLabel (l_jetAK8CSV              , h_jetAK8CSV            );
  hfloat  h_jetAK8JEC            ; evt.getByLabel (l_jetAK8JEC              , h_jetAK8JEC            );
  hfloat  h_jetAK8Area           ; evt.getByLabel (l_jetAK8Area             , h_jetAK8Area           );
  hfloat  h_jetAK8Tau1           ; evt.getByLabel (l_jetAK8Tau1             , h_jetAK8Tau1           ); 
  hfloat  h_jetAK8Tau2           ; evt.getByLabel (l_jetAK8Tau2             , h_jetAK8Tau2           ); 
  hfloat  h_jetAK8Tau3           ; evt.getByLabel (l_jetAK8Tau3             , h_jetAK8Tau3           ); 
  hfloat  h_jetAK8nSubJets       ; evt.getByLabel (l_jetAK8nSubJets         , h_jetAK8nSubJets       ); 
  hfloat  h_jetAK8minmass        ; evt.getByLabel (l_jetAK8minmass          , h_jetAK8minmass        ); 
  hfloat  h_jetAK8VSubjetIndex0  ; evt.getByLabel (l_jetAK8VSubjetIndex0    , h_jetAK8VSubjetIndex0  );  
  hfloat  h_jetAK8VSubjetIndex1  ; evt.getByLabel (l_jetAK8VSubjetIndex1    , h_jetAK8VSubjetIndex1  );  
  hfloat  h_jetAK8TopSubjetIndex0; evt.getByLabel (l_jetAK8TopSubjetIndex0  , h_jetAK8TopSubjetIndex0); 
  hfloat  h_jetAK8TopSubjetIndex1; evt.getByLabel (l_jetAK8TopSubjetIndex1  , h_jetAK8TopSubjetIndex1); 
  hfloat  h_jetAK8TopSubjetIndex2; evt.getByLabel (l_jetAK8TopSubjetIndex2  , h_jetAK8TopSubjetIndex2); 
  hfloat  h_jetAK8TopSubjetIndex3; evt.getByLabel (l_jetAK8TopSubjetIndex3  , h_jetAK8TopSubjetIndex3); 
  hfloat  h_subjetAK8BDisc       ; evt.getByLabel (l_subjetAK8BDisc         , h_subjetAK8BDisc       ); 
  hfloat  h_subjetAK8Pt          ; evt.getByLabel (l_subjetAK8Pt            , h_subjetAK8Pt          ); 
  hfloat  h_subjetAK8Eta         ; evt.getByLabel (l_subjetAK8Eta           , h_subjetAK8Eta         ); 
  hfloat  h_subjetAK8Phi         ; evt.getByLabel (l_subjetAK8Phi           , h_subjetAK8Phi         ); 
  hfloat  h_subjetAK8Mass        ; evt.getByLabel (l_subjetAK8Mass          , h_subjetAK8Mass        ); 
  hfloat  h_subjetCmsTopTagBDisc ; evt.getByLabel (l_subjetCmsTopTagBDisc   , h_subjetCmsTopTagBDisc ); 
  hfloat  h_subjetCmsTopTagPt    ; evt.getByLabel (l_subjetCmsTopTagPt      , h_subjetCmsTopTagPt    ); 
  hfloat  h_subjetCmsTopTagEta   ; evt.getByLabel (l_subjetCmsTopTagEta     , h_subjetCmsTopTagEta   ); 
  hfloat  h_subjetCmsTopTagPhi   ; evt.getByLabel (l_subjetCmsTopTagPhi     , h_subjetCmsTopTagPhi   ); 
  hfloat  h_subjetCmsTopTagMass  ; evt.getByLabel (l_subjetCmsTopTagMass    , h_subjetCmsTopTagMass  ); 
  hfloat  h_jetAK4Pt             ; evt.getByLabel (l_jetAK4Pt               , h_jetAK4Pt             );
  hfloat  h_jetAK4Eta            ; evt.getByLabel (l_jetAK4Eta              , h_jetAK4Eta            );
  hfloat  h_jetAK4Phi            ; evt.getByLabel (l_jetAK4Phi              , h_jetAK4Phi            );
  hfloat  h_jetAK4Mass           ; evt.getByLabel (l_jetAK4Mass             , h_jetAK4Mass           );
  hfloat  h_jetAK4Energy         ; evt.getByLabel (l_jetAK4Energy           , h_jetAK4Energy         );
  hfloat  h_jetAK4Flavour        ; evt.getByLabel (l_jetAK4Flavour          , h_jetAK4Flavour        );
  hfloat  h_jetAK4CSV            ; evt.getByLabel (l_jetAK4CSV              , h_jetAK4CSV            );
  hfloat  h_jetAK4JEC            ; evt.getByLabel (l_jetAK4JEC              , h_jetAK4JEC            );
  hfloat  h_jetAK4nHadEnergy     ; evt.getByLabel (l_jetAK4nHadEnergy       , h_jetAK4nHadEnergy     );
  hfloat  h_jetAK4nEMEnergy      ; evt.getByLabel (l_jetAK4nEMEnergy        , h_jetAK4nEMEnergy      );
  hfloat  h_jetAK4HFHadronEnergy ; evt.getByLabel (l_jetAK4HFHadronEnergy   , h_jetAK4HFHadronEnergy );
  hfloat  h_jetAK4cHadEnergy     ; evt.getByLabel (l_jetAK4cHadEnergy       , h_jetAK4cHadEnergy     );
  hfloat  h_jetAK4cEMEnergy      ; evt.getByLabel (l_jetAK4cEMEnergy        , h_jetAK4cEMEnergy      );
  hfloat  h_jetAK4numDaughters   ; evt.getByLabel (l_jetAK4numDaughters     , h_jetAK4numDaughters   );
  hfloat  h_jetAK4cMultip        ; evt.getByLabel (l_jetAK4cMultip          , h_jetAK4cMultip        );
  hfloat  h_jetAK4Y              ; evt.getByLabel (l_jetAK4Y                , h_jetAK4Y              );
  hfloat  h_jetAK4Area           ; evt.getByLabel (l_jetAK4Area             , h_jetAK4Area           );

  hfloat h_muPt                  ; evt.getByLabel (l_muPt                    ,h_muPt                  );
  hfloat h_muEta                 ; evt.getByLabel (l_muEta                   ,h_muEta                 );
  hfloat h_muY                   ; evt.getByLabel (l_muY                     ,h_muY                   );
  hfloat h_muPhi                 ; evt.getByLabel (l_muPhi                   ,h_muPhi                 );
  hfloat h_muMass                ; evt.getByLabel (l_muMass                  ,h_muMass                );
  hfloat h_muE                   ; evt.getByLabel(l_muE                      ,h_muE                   );
  hfloat h_muCharge              ; evt.getByLabel (l_muCharge                ,h_muCharge              );

  hfloat h_elPt                  ; evt.getByLabel(l_elPt                     , h_elPt                 ); 
  hfloat h_elEta                 ; evt.getByLabel(l_elEta                    , h_elEta                ); 
  hfloat h_elY                   ; evt.getByLabel(l_elY                      , h_elY                  ); 
  hfloat h_elPhi                 ; evt.getByLabel(l_elPhi                    , h_elPhi                ); 
  hfloat h_elMass                ; evt.getByLabel(l_elMass                   , h_elMass               ); 
  hfloat h_elE                   ; evt.getByLabel(l_elE                      , h_elE                  ); 
  hfloat h_elCharge              ; evt.getByLabel(l_elCharge                 , h_elCharge             ); 

  Handle<vlq::GenParticleWithDaughtersCollection> h_HbbCands ; evt.getByLabel (l_HbbCands , h_HbbCands );
  vlq::GenParticleWithDaughtersCollection::const_iterator ihbb ;

  h1_["cutflow"] -> AddBinContent(1) ; 

  //// Preselection HLT
  unsigned int hltdecisions(0) ; 
  for ( const string& myhltpath : hltPaths_ ) {
    vector<string>::const_iterator it ;
    for (it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it ) {
      if ( it->find(myhltpath) ) {
         std::string hltname = (h_trigName.product()) -> at (it - (h_trigName.product())->begin()) ; 
         hltdecisions |= int((h_trigBit.product())->at(it - (h_trigName.product())->begin())) << (it - (h_trigName.product())->begin()) ;  
      }
    }
  }
  if (hltPaths_.size() > 0 && hltdecisions == 0) return false ; 

  h1_["cutflow"] -> AddBinContent(2) ; 

  vlq::MuonCollection goodMuPs, goodMuMs ; 
  MuonSelector mupsel(mupselParams_) ; 
  MuonSelector mumsel(mumselParams_) ; 
  for (unsigned imu = 0; imu < (h_muPt.product())->size(); ++imu) {
    bool retmupsel(false) ;
    if (mupsel(evt, imu, retmupsel) == 1) {
      TLorentzVector  muP4;
      muP4.SetPtEtaPhiM( (h_muPt.product())->at(imu), (h_muEta.product())->at(imu), (h_muPhi.product())->at(imu), (h_muMass.product())->at(imu) ) ;
      vlq::Muon mu ; 
      mu.setP4(muP4) ; 
      mu.setIndex(imu) ;
      mu.setPt((h_muPt.product())->at(imu)) ; 
      mu.setEta((h_muEta.product())->at(imu)) ; 
      mu.setPhi((h_muPhi.product())->at(imu)) ; 
      mu.setMass((h_muMass.product())->at(imu)) ; 
      mu.setCharge((h_muCharge.product()->at(imu))) ; 
      h1_["mu_pt"] -> Fill(mu.getPt()) ; 
      h1_["mu_eta"] -> Fill((h_muEta.product())->at(imu)) ; 
      if ( mu.getPt() > 20 ) goodMuPs.push_back(mu) ; 
    }
    bool retmumsel(false) ;
    if (mumsel(evt, imu, retmumsel) == 1) {
      TLorentzVector  muP4;
      muP4.SetPtEtaPhiM( (h_muPt.product())->at(imu), (h_muEta.product())->at(imu), (h_muPhi.product())->at(imu), (h_muMass.product())->at(imu) ) ;
      vlq::Muon mu ; 
      mu.setP4(muP4) ; 
      mu.setIndex(imu) ;
      mu.setPt((h_muPt.product())->at(imu)) ; 
      mu.setEta((h_muEta.product())->at(imu)) ; 
      mu.setPhi((h_muPhi.product())->at(imu)) ; 
      mu.setMass((h_muMass.product())->at(imu)) ; 
      mu.setCharge((h_muCharge.product()->at(imu))) ; 
      h1_["mu_pt"] -> Fill(mu.getPt()) ; 
      h1_["mu_eta"] -> Fill((h_muEta.product())->at(imu)) ; 
      if ( mu.getPt() > 20 ) goodMuMs.push_back(mu) ; 
    }
  }

  vlq::ElectronCollection goodElPs, goodElMs ; 
  ElectronSelector elpsel(elpselParams_) ; 
  ElectronSelector elmsel(elmselParams_) ; 
  for (unsigned iel = 0; iel < (h_elPt.product())->size(); ++iel) {
    bool retelpsel(false) ;
    if (elpsel(evt, iel, retelpsel) == 1) {
      TLorentzVector  elP4;
      elP4.SetPtEtaPhiM( (h_elPt.product())->at(iel), (h_elEta.product())->at(iel), (h_elPhi.product())->at(iel), (h_elMass.product())->at(iel) ) ;
      vlq::Electron el ; 
      el.setP4(elP4) ; 
      el.setIndex(iel) ;
      el.setPt((h_elPt.product())->at(iel)) ; 
      el.setEta((h_elEta.product())->at(iel)) ; 
      el.setPhi((h_elPhi.product())->at(iel)) ; 
      el.setMass((h_elMass.product())->at(iel)) ; 
      el.setCharge((h_elCharge.product()->at(iel))) ; 
      h1_["el_pt"] -> Fill(el.getPt()) ; 
      h1_["el_eta"] -> Fill(el.getEta()) ; 
      if ( el.getPt() > 20 ) goodElPs.push_back(el) ; 
    }
    bool retelmsel(false) ;
    if (elmsel(evt, iel, retelmsel) == 1) {
      TLorentzVector  elP4;
      elP4.SetPtEtaPhiM( (h_elPt.product())->at(iel), (h_elEta.product())->at(iel), (h_elPhi.product())->at(iel), (h_elMass.product())->at(iel) ) ;
      vlq::Electron el ; 
      el.setP4(elP4) ; 
      el.setIndex(iel) ;
      el.setPt((h_elPt.product())->at(iel)) ; 
      el.setEta((h_elEta.product())->at(iel)) ; 
      el.setPhi((h_elPhi.product())->at(iel)) ; 
      el.setMass((h_elMass.product())->at(iel)) ; 
      el.setCharge((h_elCharge.product()->at(iel))) ; 
      h1_["el_pt"] -> Fill(el.getPt()) ; 
      h1_["el_eta"] -> Fill(el.getEta()) ; 
      if ( el.getPt() > 20 ) goodElMs.push_back(el) ; 
    }
  }

  ZCandidateProducer<vlq::MuonCollection> zmumuprod(goodMuPs, goodMuMs) ; 
  vlq::CandidateCollection zmumu ;
  zmumuprod(zmumu, h1_["zmumu_mass"], h1_["zmumu_pt"], h1_["zmumu_eta"], h1_["dr_mumu"]) ; 

  ZCandidateProducer<vlq::ElectronCollection> zelelprod(goodElPs, goodElMs) ; 
  vlq::CandidateCollection zelel ;
  zelelprod(zelel, h1_["zelel_mass"], h1_["zelel_pt"], h1_["zelel_eta"], h1_["dr_elel"]) ; 

  vlq::JetCollection goodAK8Jets, goodAK4Jets, btaggedlooseAK4, btaggedmediumAK4 ;
  vector<unsigned> ak4selIdxs, ak8selIdxs, bjetIdxs;

  //// Store good AK8 jets
  JetSelector ak8jetsel(AK8JetSelParams_) ;
  for ( unsigned ijet = 0; ijet < (h_jetAK8Pt.product())->size(); ++ijet) {
    bool retak8jetsel = false ; 
    if (ak8jetsel(evt, ijet,retak8jetsel) == 0) { 
      LogDebug("OS2LAna") << " ak8 jet with pt = " << (h_jetAK8Pt.product())->at(ijet) << " fail jet sel\n" ; 
      continue ;
    }
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
        (h_jetAK8Eta.product())->at(ijet), 
        (h_jetAK8Phi.product())->at(ijet), 
        (h_jetAK8Mass.product())->at(ijet) ) ;
    vlq::Jet jet;
    jet.setP4(jetP4) ; 
    jet.setFilteredMass((h_jetAK8FilteredMass.product())->at(ijet)) ; 
    jet.setTrimmedMass((h_jetAK8TrimmedMass.product())->at(ijet)) ; 
    jet.setPrunedMass((h_jetAK8PrunedMass.product())->at(ijet)) ; 
    jet.setSoftDropMass((h_jetAK8SoftDropMass.product())->at(ijet)) ; 
    jet.setCSV((h_jetAK8CSV.product())->at(ijet)) ;
    goodAK8Jets.push_back(jet) ;
    ak8selIdxs.push_back(ijet);
  }

  //// Preselection 2 AK8 jets 
  if ( goodAK8Jets.size() < 1 ) return false ; 
  if ( goodAK8Jets.size() > 1 && ( goodAK8Jets.at(0).getPt() < 300 || goodAK8Jets.at(1).getPt() < 220.) )  return false ; 

  //// Store good AK4 jets 
  JetSelector ak4jetsel(AK4JetSelParams_) ;
  JetSelector btaggedlooseak4sel(BTaggedLooseAK4SelParams_) ;
  JetSelector btaggedmediumak4sel(BTaggedMediumAK4SelParams_) ;
  bool retak4jetsel = false ; 
  bool retbtaggedlooseak4sel = false ; 
  bool retbtaggedmediumak4sel = false ; 
  for ( unsigned ijet = 0; ijet < (h_jetAK4Pt.product())->size(); ++ijet) {
    retak4jetsel = false ;
    retbtaggedlooseak4sel = false ;
    retbtaggedmediumak4sel = false ;
    if (ak4jetsel(evt, ijet,retak4jetsel) == 0) { 
      LogDebug("OS2LAna") << " ak4 jet with pt = " << (h_jetAK4Pt.product())->at(ijet) << " fail jet sel\n" ; 
      continue ;
    }
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
        (h_jetAK4Eta.product())->at(ijet), 
        (h_jetAK4Phi.product())->at(ijet), 
        (h_jetAK4Mass.product())->at(ijet) ) ;
    vlq::Jet jet;  
    jet.setP4(jetP4) ;
    jet.setCSV((h_jetAK4CSV.product())->at(ijet)) ;
    goodAK4Jets.push_back(jet) ;
    ak4selIdxs.push_back(ijet);
    if ( btaggedlooseak4sel(evt, ijet,retbtaggedlooseak4sel) != 0 ) {
      bjetIdxs.push_back(ijet) ; 
      btaggedlooseAK4.push_back(jet) ; 
    }
    if ( btaggedmediumak4sel(evt, ijet,retbtaggedmediumak4sel) != 0 ) {
      btaggedmediumAK4.push_back(jet) ; 
    }
  }

  //// Preselection at least one b-tagged AK4 jet 
  if ( btaggedlooseAK4.size() < 1 ) return false; 

  //h1_["nak8_nocuts"] -> Fill(goodAK8Jets.size()) ; 
  //h1_["nak4_nocuts"] -> Fill(goodAK4Jets.size()) ; 
  //h1_["nbloose_nocuts"] -> Fill(btaggedlooseAK4.size()) ; 

  //// Make W, top and H jets 
  vector<unsigned> seltjets, selhjets, selwjets;
  vlq::JetCollection tjets, hjets, wjets ; 
  JetSelector tjetsel(TJetSelParams_) ;
  JetSelector hjetsel(HJetSelParams_) ;
  JetSelector wjetsel(WJetSelParams_) ;
  bool rettjetsel = false ;
  bool rethjetsel = false ;
  bool retwjetsel = false ;
  for ( unsigned  &ijet :  ak8selIdxs) {
    TLorentzVector jetP4 ;
    vector<float>drhjet_hpart, drhjet_bpart, drhjet_bbarpart ; 
    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
        (h_jetAK8Eta.product())->at(ijet), 
        (h_jetAK8Phi.product())->at(ijet), 
        (h_jetAK8Mass.product())->at(ijet) ) ;
    for ( ihbb = h_HbbCands.product()->begin(); ihbb != h_HbbCands.product()->end(); ++ihbb ) {
      TLorentzVector hp4 = (ihbb->getMom()).getP4() ; 
      drhjet_hpart.push_back(hp4.DeltaR(jetP4)) ; 
      vlq::GenParticleCollection bs =  ( ihbb->getDaughters() ) ; 
      for ( vlq::GenParticle& b : bs ) {
        TLorentzVector bp4 = b.getP4() ; 
        if ( b.getPdgID() == 5 ) {
          drhjet_bpart.push_back(bp4.DeltaR(jetP4)) ; 
        }
        if ( b.getPdgID() == -5 ) {
          drhjet_bbarpart.push_back(bp4.DeltaR(jetP4)) ; 
        }
      }
    }
    std::vector<float>::iterator iminh    = std::min_element(drhjet_hpart.begin(), drhjet_hpart.end());
    std::vector<float>::iterator iminb    = std::min_element(drhjet_bpart.begin(), drhjet_bpart.end());
    std::vector<float>::iterator iminbbar = std::min_element(drhjet_bbarpart.begin(), drhjet_bbarpart.end());
    if ( iminh != drhjet_hpart.end() && iminb != drhjet_bpart.end() && iminbbar != drhjet_bbarpart.end() )
      if ( *iminh < 0.8 && *iminb < 0.8 && *iminbbar < 0.8 ) 
        h1_["ptak8"]->Fill(jetP4.Pt()) ; 
    vlq::Jet jet; 
    jet.setP4(jetP4) ;
    jet.setCSV((h_jetAK8CSV.product())->at(ijet)) ;
    rettjetsel = false ;
    if (tjetsel(evt, ijet,rettjetsel) == true ) { 
      tjets.push_back(jet) ; 
      seltjets.push_back(ijet) ; 
    }
    rethjetsel = false ;
    if (hjetsel(evt, ijet,rethjetsel) == true ) { 
      hjets.push_back(jet) ; 
      selhjets.push_back(ijet) ; 
      h1_["csvhjets"] -> Fill((h_jetAK8CSV.product())->at(ijet)) ; 
      if ( iminh != drhjet_hpart.end() && iminb != drhjet_bpart.end() && iminbbar != drhjet_bbarpart.end() )
        if ( *iminh < 0.8  && *iminb < 0.8 && *iminbbar < 0.8 ) 
          h1_["pthjets"]->Fill(jetP4.Pt()) ;
    } 
    retwjetsel = false ;
    if (wjetsel(evt, ijet,retwjetsel) == true ) { 
      wjets.push_back(jet) ; 
      selwjets.push_back(ijet) ; 
    } 
  }

  HT htak4(goodAK4Jets) ; 
  //// Preselection HT
  if ( htak4.getHT() < HTMin_ ) return false; 

  h1_["cutflow"] -> AddBinContent(3) ; 

  if (goodAK4Jets.size() > 0) {
    std::sort(goodAK4Jets.begin(), goodAK4Jets.end(), Utilities::sortByCSV) ; 
    h1_["ak4highestcsv_nocuts"] -> Fill((goodAK4Jets.at(0)).getCSV()) ;
    std::sort(goodAK4Jets.begin(), goodAK4Jets.end(), Utilities::sortByPt) ; 
  }

  HT htak8(goodAK8Jets) ; 

  //// Selection H-tagged AK8 jet 
  //if (hjets.size() < 1 ) return false; 

  //double csvhleading(-1) ; 
  //if (hjets.size() > 0 ) csvhleading = hjets.at(0).getCSV() ; 

  //// Pick forwardmost AK4 jet
  double maxeta(0) ;
  vlq::Jet forwardestjet ; 
  for ( auto& jet : goodAK4Jets ) {
    if ( abs(jet.getEta()) > abs(maxeta) ) { 
      forwardestjet = jet ; 
      maxeta = jet.getEta() ; 
    }
  }

  double ptak8_1 = goodAK8Jets.at(0).getP4().Pt() ;
  double ptak8_2(0) ; 
  goodAK8Jets.size() > 1 ?  ptak8_2 = goodAK8Jets.at(1).getP4().Pt() : 0 ; 
  double mak8_1 = goodAK8Jets.at(0).getP4().Mag() ;
  double mak8_2(0) ; 
  goodAK8Jets.size() > 1 ?  mak8_2 = goodAK8Jets.at(1).getP4().Mag() : 0 ; 
  double mak8_12(0) ; 
  double detaLeading2AK8(-1) ; 
  if (goodAK8Jets.size() > 1) {
    TLorentzVector p4_ak8_12(goodAK8Jets.at(0).getP4() + goodAK8Jets.at(1).getP4()) ;
    mak8_12 = p4_ak8_12.Mag() ; 
    detaLeading2AK8 = abs(goodAK8Jets.at(0).getEta() - goodAK8Jets.at(1).getEta() ) ;
  }

  double ptak8leading ((goodAK8Jets.at(0)).getPt()) ; 
  double mak8leading ((goodAK8Jets.at(0)).getMass()) ; 
  double csvak8leading ((goodAK8Jets.at(0)).getCSV()) ; 

  h1_["ptak8leading"] -> Fill(ptak8leading) ; 
  h1_["etaak8leading"] -> Fill((goodAK8Jets.at(0)).getEta()) ;
  h1_["mak8leading"] -> Fill(mak8leading) ; 
  h1_["trimmedmak8leading"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass()) ;
  h1_["softdropmak8leading"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass()) ;
  h1_["csvak8leading"] -> Fill(csvak8leading) ;

  double ptak82nd (0) ;
  double mak82nd (0) ;
  double csvak82nd (0) ; 
  if (goodAK8Jets.size() > 1) {
    ptak82nd = (goodAK8Jets.at(1)).getPt() ; 
    mak82nd = (goodAK8Jets.at(1)).getMass() ; 
    csvak82nd = (goodAK8Jets.at(1)).getCSV() ; 
  }

  h1_["ptak82nd"] -> Fill(ptak82nd) ; 
  h1_["mak82nd"] -> Fill(mak82nd) ; 
  h1_["csvak82nd"] -> Fill(csvak82nd) ;

  h1_["ptak8leadingPlus2nd"] -> Fill(ptak8leading+ptak82nd) ; 

  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortByMass) ; 
  h1_["mak8highestm"] -> Fill((goodAK8Jets.at(0)).getMass()) ; 

  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortByTrimmedMass) ; 
  h1_["trimmedmak8highesttrimmedm"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass()) ; 

  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortBySoftDropMass) ; 
  h1_["softdropmak8highestsoftdropm"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass()) ; 

  std::sort(goodAK8Jets.begin(), goodAK8Jets.end(), Utilities::sortByPt) ; 

  double ptak4leading ((h_jetAK4Pt.product())->at(ak4selIdxs.at(0))) ;   
  h1_["ptak4leading"] -> Fill(ptak4leading) ; 
  h1_["etaak4leading"] -> Fill((h_jetAK4Eta.product())->at(ak4selIdxs.at(0))) ; 

  double ptbjetleading (-1);
  double csvbjetleading (-1);
  double csvbjethighestcsv(-1); 
  if ( bjetIdxs.size() > 0 ) {
    ptbjetleading = (h_jetAK4Pt.product())->at(bjetIdxs.at(0)) ; 
    csvbjetleading = (h_jetAK4CSV.product())->at(bjetIdxs.at(0)) ; 
    h1_["ptbjetleading"] -> Fill(ptbjetleading) ; 
    h1_["etabjetleading"] -> Fill((h_jetAK4Eta.product())->at(bjetIdxs.at(0))) ; 
    h1_["csvbjetleading"] -> Fill(csvbjetleading) ; 

    std::sort(btaggedlooseAK4.begin(), btaggedlooseAK4.end(), Utilities::sortByCSV) ; 
    csvbjethighestcsv = (btaggedlooseAK4.at(0)).getCSV() ; 
    h1_["csvbjethighestcsv"] -> Fill(csvbjethighestcsv) ; 
    h1_["ptak4highestcsv"] -> Fill((btaggedlooseAK4.at(0)).getPt()) ;
    h1_["etaak4highestcsv"] -> Fill((btaggedlooseAK4.at(0)).getEta()) ;
  }

  h1_["ptak4forwardmost"] -> Fill(forwardestjet.getPt()) ; 
  h1_["etaak4forwardmost"] -> Fill(forwardestjet.getEta()) ; 

  h2_["pt_ak8_leading_2nd"] -> Fill(ptak8leading, ptak82nd) ; 
  h2_["m_ak8_leading_2nd"] -> Fill(mak8leading, mak82nd) ; 
  h2_["csv_ak8_leading_2nd"] -> Fill(csvak8leading, csvak82nd) ; 

  h1_["nak8_presel"] -> Fill(goodAK8Jets.size()) ; 
  h1_["nak4_presel"] -> Fill(goodAK4Jets.size()) ; 
  h1_["nbloose_presel"] -> Fill(btaggedlooseAK4.size()) ; 
  h1_["nbmedium_presel"] -> Fill(btaggedmediumAK4.size()) ; 

  h1_["nwjet_presel"] -> Fill(wjets.size()) ; 
  h1_["nhjet_presel"] -> Fill(hjets.size()) ; 
  h1_["ntjet_presel"] -> Fill(tjets.size()) ; 

  h1_["ht_presel"] ->Fill(htak4.getHT()) ; 

  // Make H cands
  std::vector<vlq::ResolvedVjj> wcands, hcands ; 
  if (goodAK4Jets.size() > 1 && wjets.size() == 0) {
    double mmin (60), mmax(100), drmax(1.2), smdmin(0.0), smdmax(0.5) ;  
    VCandProducer WCandProducer(goodAK4Jets, mmin, mmax,drmax, smdmin, smdmax) ;  
    WCandProducer.getCands(wcands) ; 
  }
  if (btaggedmediumAK4.size() > 1 && hjets.size() == 0) {
    double mmin (100), mmax(140), drmax(1.2), smdmin(0.0), smdmax(0.5) ;  
    VCandProducer HCandProducer(btaggedmediumAK4, mmin, mmax,drmax, smdmin, smdmax) ;  
    HCandProducer.getCands(hcands) ; 
  }

  h1_["nwcand_presel"] -> Fill(hcands.size()) ; 
  h1_["nhcand_presel"] -> Fill(hcands.size()) ; 

  //// Event selection
  if ( goodAK4Jets.size() < 6 ) return false ; 
  h1_["cutflow"] -> AddBinContent(4) ; 

  //// Event selection
  if ( btaggedmediumAK4.size() < 1 || btaggedlooseAK4.size() < 3 ) return false ; 
  h1_["cutflow"] -> AddBinContent(5) ; 

  //// Event selection
  if ( abs(forwardestjet.getEta()) < 2.5) return false ; 
  h1_["cutflow"] -> AddBinContent(6) ; 

  if (wcands.size() > 0) h1_["ptleadingwcand"] -> Fill((wcands.at(0)).getPt()) ; 
  if (hcands.size() > 0) h1_["ptleadinghcand"] -> Fill((hcands.at(0)).getPt()) ; 
  if (wjets.size() > 0) h1_["ptleadingwjet"] -> Fill((wjets.at(0)).getPt()) ; 
  if (hjets.size() > 0) h1_["ptleadinghjet"] -> Fill((hjets.at(0)).getPt()) ; 
  if (tjets.size() > 0) h1_["ptleadingtjet"] -> Fill((tjets.at(0)).getPt()) ; 

  double drwh(-1) ;
  if (hjets.size()>0 && wjets.size()>0) {
    drwh = ((hjets.at(0)).getP4()).DeltaR((wjets.at(0)).getP4()) ; 
  }
  else if (hjets.size()>0 && wcands.size()>0) {
    drwh = ((hjets.at(0)).getP4()).DeltaR((wcands.at(0)).getP4()) ; 
  }
  else if (hcands.size()>0 && wjets.size()>0) {
    drwh = ((hcands.at(0)).getP4()).DeltaR((wjets.at(0)).getP4()) ; 
  }
  else if (hcands.size()>0 && wcands.size()>0) {
    drwh = ((hcands.at(0)).getP4()).DeltaR((wcands.at(0)).getP4()) ; 
  } 

  h1_["drwh"] -> Fill(drwh) ; 

  if (wjets.size()>0) h1_["cutflow"] -> AddBinContent(7) ;  
  if (hjets.size()>0) h1_["cutflow"] -> AddBinContent(8) ;  
  if (tjets.size()>0) h1_["cutflow"] -> AddBinContent(9) ;  

  if (wjets.size()>0&&hjets.size()>0) h1_["cutflow"] -> AddBinContent(10) ;  
  if (hjets.size()>0&&tjets.size()>0) h1_["cutflow"] -> AddBinContent(11) ;  

  if (wjets.size()==0&&wcands.size()>0) h1_["cutflow"] -> AddBinContent(12) ;  
  if (hjets.size()==0&&hcands.size()>0) h1_["cutflow"] -> AddBinContent(13) ;  

  if ( (wjets.size()>0 || wcands.size()>0 ) && (hjets.size()>0 || hcands.size()>0) ) h1_["cutflow"] -> AddBinContent(14) ;  

  h1_["nak8"] -> Fill(goodAK8Jets.size()) ; 
  h1_["nak4"] -> Fill(goodAK4Jets.size()) ; 
  h1_["nbloose"] -> Fill(btaggedlooseAK4.size()) ; 
  h1_["nbmedium"] -> Fill(btaggedmediumAK4.size()) ; 

  h1_["nwjet"] -> Fill(wjets.size()) ; 
  h1_["nhjet"] -> Fill(hjets.size()) ; 
  h1_["ntjet"] -> Fill(tjets.size()) ; 

  h1_["nwcand_presel"] -> Fill(hcands.size()) ; 
  h1_["nhcand_presel"] -> Fill(hcands.size()) ; 

  h1_["ht"] ->Fill(htak4.getHT()) ; 

  if (wjets.size()>0) h1_["ht_nwjetGt0"] ->Fill(htak4.getHT()) ; 
  if (hjets.size()>0) h1_["ht_nhjetGt0"] ->Fill(htak4.getHT()) ; 
  if (tjets.size()>0) h1_["ht_ntjetGt0"] ->Fill(htak4.getHT()) ; 
  if (wjets.size()>0&&hjets.size()>0) h1_["ht_nwhjetGt0"] ->Fill(htak4.getHT()) ; 
  if (hjets.size()>0&&tjets.size()>0) h1_["ht_nhtjetGt0"] ->Fill(htak4.getHT()) ; 
  if (wjets.size()==0&&wcands.size()>0) h1_["ht_nwcandGt0"] ->Fill(htak4.getHT()) ; 
  if (hjets.size()==0&&hcands.size()>0) h1_["ht_nhcandGt0"] ->Fill(htak4.getHT()) ; 

  std::auto_ptr<unsigned> ngoodAK4Jets ( new unsigned(goodAK4Jets.size()) );
  std::auto_ptr<unsigned> ngoodAK8Jets ( new unsigned(goodAK8Jets.size()) );
  std::auto_ptr<unsigned> nTJets ( new unsigned(tjets.size()) );
  std::auto_ptr<unsigned> nHJets ( new unsigned(hjets.size()) );
  std::auto_ptr<unsigned> nWJets ( new unsigned(wjets.size()) );
  std::auto_ptr<unsigned> nbtaggedlooseAK4 ( new unsigned(btaggedlooseAK4.size()) );
  std::auto_ptr<double> htak4jets ( new double(htak4.getHT()) );
  std::auto_ptr<double> htak8jets ( new double(htak8.getHT()) );
  std::auto_ptr<double> maxetaak4 ( new double(maxeta) );
  std::auto_ptr<double> MassLeading2AK8 ( new double(mak8_12) );
  std::auto_ptr<double> DeltaEtaLeading2AK8 ( new double(detaLeading2AK8) );
  std::auto_ptr<double> pt1stAK8   ( new double(ptak8_1) );
  std::auto_ptr<double> pt2ndAK8   ( new double(ptak8_2) );
  std::auto_ptr<double> mass1stAK8 ( new double(mak8_1) );
  std::auto_ptr<double> mass2ndAK8 ( new double(mak8_2) );
  std::auto_ptr<vector<unsigned> > ak4goodjets ( new vector<unsigned>(ak4selIdxs));
  std::auto_ptr<vector<unsigned> > ak8goodjets ( new vector<unsigned>(ak8selIdxs));
  std::auto_ptr<vector<unsigned> > bjetIdxsptr ( new vector<unsigned>(bjetIdxs));
  std::auto_ptr<vector<unsigned> > tjetIdxs ( new vector<unsigned>(seltjets));
  std::auto_ptr<vector<unsigned> > hjetIdxs ( new vector<unsigned>(selhjets));
  std::auto_ptr<vector<unsigned> > wjetIdxs ( new vector<unsigned>(selwjets));

  evt.put(ngoodAK4Jets, "ngoodAK4Jets") ; 
  evt.put(ngoodAK8Jets, "ngoodAK8Jets") ; 
  evt.put(nTJets, "nTJets") ; 
  evt.put(nHJets, "nHJets") ; 
  evt.put(nWJets, "nWJets") ; 
  evt.put(nbtaggedlooseAK4, "nbtaggedlooseAK4") ; 
  evt.put(maxetaak4, "maxetaak4") ; 
  evt.put(MassLeading2AK8, "MassLeading2AK8") ; 
  evt.put(DeltaEtaLeading2AK8, "DeltaEtaLeading2AK8") ; 
  evt.put(pt1stAK8  , "pt1stAK8") ; 
  evt.put(pt2ndAK8  , "pt2ndAK8") ; 
  evt.put(mass1stAK8, "mass1stAK8") ; 
  evt.put(mass2ndAK8, "mass2ndAK8") ; 
  evt.put(htak4jets, "htak4jets") ; 
  evt.put(htak8jets, "htak8jets") ; 
  evt.put(ak4goodjets, "ak4goodjets");
  evt.put(ak8goodjets, "ak8goodjets");
  evt.put(bjetIdxsptr, "bjetIdxs");
  evt.put(tjetIdxs, "tjetIdxs");
  evt.put(hjetIdxs, "hjetIdxs");
  evt.put(wjetIdxs, "wjetIdxs");

  return true ; 

}

// ------------ method called once each job just before starting event loop  ------------
void OS2LAna::beginJob() {

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

  h1_["ptak8leading"]  = fs->make<TH1D>("ptak8leading"  ,";p_T(leading AK8 jet) [GeV];;"      , 40, 0., 2000.) ; 
  h1_["ptak4leading"]  = fs->make<TH1D>("ptak4leading"  ,";p_T(leading AK4 jet) [GeV];;"      , 40, 0., 2000.) ; 
  h1_["ptbjetleading"]  = fs->make<TH1D>("ptbjetleading"  ,";p_T(leading b jet) [GeV];;"      , 40, 0., 2000.) ; 

  h1_["etaak8leading"] = fs->make<TH1D>("etaak8leading", ";#eta(leading AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["etaak4leading"] = fs->make<TH1D>("etaak4leading", ";#eta(leading AK4 jet);;" , 80 ,-4. ,4.) ; 
  h1_["etabjetleading"] = fs->make<TH1D>("etabjetleading", ";#eta(leading b jet);;" , 80 ,-4. ,4.) ; 

  h1_["ptak82nd"]  = fs->make<TH1D>("ptak82nd"  ,";p_T(2nd AK8 jet) [GeV];;"      , 40, 0., 2000.) ; 
  h1_["ptak8leadingPlus2nd"]  = fs->make<TH1D>("ptak8leadingPlus2nd"  ,";p_T(leading AK8 jet)+p_T (2nd AK8 jet) [GeV];;"      , 40, 0., 2000.) ; 

  h1_["csvbjetleading"] = fs->make<TH1D>("csvbjetleading", ";CSV (leading b jet);;" ,50 ,0. ,1.) ; 
  h1_["csvbjethighestcsv"] = fs->make<TH1D>("csvbjethighestcsv", ";max. CSV b jet;;" ,50 ,0. ,1.) ; 

  h1_["ak4highestcsv_nocuts"] = fs->make<TH1D>("ak4highestcsv_nocuts", ";max. CSV of AK4 jets;;" , 50, 0., 1.) ; 

  h1_["ptak4highestcsv"] = fs->make<TH1D>("ptak4highestcsv", ";p_T(highest CSV AK4 jet);;" , 100, 0., 2000.) ; 
  h1_["etaak4highestcsv"] = fs->make<TH1D>("etaak4highestcsv", ";#eta(highest CSV AK4 jet);;" , 80 ,-4. ,4.) ; 

  h1_["ptak4forwardmost"] = fs->make<TH1D>("ptak4forwardmost", ";p_T(forwardmost AK4 jet);;" , 100, 0., 2000.) ; 
  h1_["etaak4forwardmost"] = fs->make<TH1D>("etaak4forwardmost", ";p_T(forwardmost AK4 jet);;" , 80 ,-4. ,4.) ; 

  h1_["mak8leading"] = fs->make<TH1D>("mak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["mak8highestm"] = fs->make<TH1D>("mak8highestm", ";M(most massive AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  h1_["prunedmak8leading"] = fs->make<TH1D>("prunedmak8leading", ";M(pruned leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  h1_["trimmedmak8leading"] = fs->make<TH1D>("trimmedmak8leading", ";M(trimmed leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak8highesttrimmedm"] = fs->make<TH1D>("trimmedmak8highesttrimmedm", ";M(highest trimmed mass AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  h1_["softdropmak8leading"] = fs->make<TH1D>("softdropmak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak8highestsoftdropm"] = fs->make<TH1D>("softdropmak8highestsoftdropm", ";M(highest soft drop mass AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  h1_["mak82nd"] = fs->make<TH1D>("mak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 

  h1_["csvak8leading"] = fs->make<TH1D>("csvak8leading", ";CSV (leading AK8 jet);;" ,50 ,0. ,1.) ;
  h1_["csvak82nd"] = fs->make<TH1D>("csvak82nd", ";CSV (2nd AK8 jet);;" ,50 ,0. ,1.) ;

  h2_["pt_ak8_leading_2nd"] = fs->make<TH2D>("pt_ak8_leading_2nd", ";p_T (leading AK8 jet) [GeV];p_T (2nd AK8 jet) [GeV];" ,40, 0., 2000. ,40, 0., 2000.) ; 

  h2_["m_ak8_leading_2nd"] = fs->make<TH2D>("m_ak8_leading_2nd", ";M(leading AK8 jet) [GeV];M(2nd AK8 jet) [GeV];" ,100, 0., 200. ,100, 0., 200.) ; 

  h2_["csv_ak8_leading_2nd"] = fs->make<TH2D>("csv_ak8_leading_2nd", ";CSV(leading AK8 jet) ;CSV(2nd AK8 jet) ;" ,50 ,0. ,1. ,50 ,0. ,1.) ;  

  h1_["nak8_nocuts"] = fs->make<TH1D>("nak8_nocuts", ";AK8 jet multiplicity before cuts;;" , 11, -0.5,10.5) ; 
  h1_["nak4_nocuts"] = fs->make<TH1D>("nak4_nocuts", ";AK4 jet multiplicity before cuts;;" , 11, -0.5,10.5) ; 
  h1_["nbloose_nocuts"] = fs->make<TH1D>("nbloose_nocuts", ";b jet multiplicity before cuts;;" , 11, -0.5,10.5) ; 

  h1_["nak8_presel"] = fs->make<TH1D>("nak8_presel", ";AK8 jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nak4_presel"] = fs->make<TH1D>("nak4_presel", ";AK4 jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nbloose_presel"] = fs->make<TH1D>("nbloose_presel", ";b jet multiplicity (Loose OP);;" , 11, -0.5,10.5) ; 
  h1_["nbmedium_presel"] = fs->make<TH1D>("nbmedium_presel", ";b jet multiplicity (Medium OP);;" , 11, -0.5,10.5) ; 

  h1_["nwjet_presel"] = fs->make<TH1D>("nwjet_presel", ";W jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nhjet_presel"] = fs->make<TH1D>("nhjet_presel", ";H jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["ntjet_presel"] = fs->make<TH1D>("ntjet_presel", ";top jet multiplicity;;" , 11, -0.5,10.5) ; 

  h1_["nwcand_presel"] = fs->make<TH1D>("nwcand_presel", ";W candidate multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nhcand_presel"] = fs->make<TH1D>("nhcand_presel", ";H candidate multiplicity;;" , 11, -0.5,10.5) ; 

  h1_["ht_presel"] = fs->make<TH1D>("ht_presel" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 

  h1_["nak8"] = fs->make<TH1D>("nak8", ";AK8 jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nak4"] = fs->make<TH1D>("nak4", ";AK4 jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nbloose"] = fs->make<TH1D>("nbloose", ";b jet multiplicity (Loose OP);;" , 11, -0.5,10.5) ; 
  h1_["nbmedium"] = fs->make<TH1D>("nbmedium", ";b jet multiplicity (Medium OP);;" , 11, -0.5,10.5) ; 

  h1_["nwjet"] = fs->make<TH1D>("nwjet", ";W jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nhjet"] = fs->make<TH1D>("nhjet", ";H jet multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["ntjet"] = fs->make<TH1D>("ntjet", ";top jet multiplicity;;" , 11, -0.5,10.5) ; 

  h1_["nwcand"] = fs->make<TH1D>("nwcand", ";W candidate multiplicity;;" , 11, -0.5,10.5) ; 
  h1_["nhcand"] = fs->make<TH1D>("nhcand", ";H candidate multiplicity;;" , 11, -0.5,10.5) ; 

  h1_["ht"] = fs->make<TH1D>("ht" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 

  h1_["ptleadinghcand"] = fs->make<TH1D>("ptleadinghcand" ,";p_T (leading H cands) [GeV]", 100, 0., 2000.) ; 
  h1_["ptleadingwcand"] = fs->make<TH1D>("ptleadingwcand" ,";p_T (leading W cands) [GeV]", 100, 0., 2000.) ; 

  h1_["ptleadinghjet"] = fs->make<TH1D>("ptleadinghjet" ,";p_T (leading H-tagged jets) [GeV]", 100, 0., 2000.) ; 
  h1_["ptleadingwjet"] = fs->make<TH1D>("ptleadingwjet" ,";p_T (leading W-tagged jets) [GeV]", 100, 0., 2000.) ; 
  h1_["ptleadingtjet"] = fs->make<TH1D>("ptleadingtjet" ,";p_T (leading top-tagged jets) [GeV]", 100, 0., 2000.) ; 

  h1_["ht_nwjetGt0"] = fs->make<TH1D>("ht_nwjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["ht_nhjetGt0"] = fs->make<TH1D>("ht_nhjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["ht_ntjetGt0"] = fs->make<TH1D>("ht_ntjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["ht_nwhjetGt0"] = fs->make<TH1D>("ht_nwhjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["ht_nhtjetGt0"] = fs->make<TH1D>("ht_nhtjetGt0" ,";H_T (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["ht_nwcandGt0"] = fs->make<TH1D>("ht_nwcandGt0" ,";H_T (AK4 cands) [GeV]", 200, 0., 4000.) ; 
  h1_["ht_nhcandGt0"] = fs->make<TH1D>("ht_nhcandGt0" ,";H_T (AK4 cands) [GeV]", 200, 0., 4000.) ; 

  h1_["ptak8"]  = fs->make<TH1D>("ptak8"  ,";p_T(AK8 jet) [GeV]"         , 100, 0., 2000.) ; 
  h1_["pthjets"] = fs->make<TH1D>("pthjets" ,";p_T (H-tagged jets) [GeV]", 100, 0., 2000.) ; 
  h1_["csvhjets"] = fs->make<TH1D>("csvhjets", ";CSV (H-tagged jets);;" ,50 ,0. ,1.) ;

  h1_["drwh"] = fs->make<TH1D>("drwh", ";#DeltaR(H,W);;", 40, 0, 4.) ;  

  h1_["mu_pt"] = fs->make<TH1D>("mu_pt", ";p_T (mu) [GeV]", 100, 0., 2000.) ; 
  h1_["el_pt"] = fs->make<TH1D>("el_pt", ";p_T (el) [GeV]", 100, 0., 2000.) ; 

  h1_["mu_eta"] = fs->make<TH1D>("mu_eta", ";#eta (mu) [GeV]", 80, -4., 4.) ; 
  h1_["el_eta"] = fs->make<TH1D>("el_eta", ";#eta (el) [GeV]", 80, -4., 4.) ; 

  h1_["zmumu_mass"] = fs->make<TH1D>("zmumu_mass", ";M(mumu) [GeV]", 60, 60., 120.) ; 
  h1_["zelel_mass"] = fs->make<TH1D>("zelel_mass", ";M(elel) [GeV]", 60, 60., 120.) ; 
  h1_["zmumu_pt"] = fs->make<TH1D>("zmumu_pt", ";p_T (Zmumu) [GeV]", 100, 0., 2000.) ; 
  h1_["zelel_pt"] = fs->make<TH1D>("zelel_pt", ";p_T (Zelel) [GeV]", 100, 0., 2000.) ; 
  h1_["zmumu_eta"] = fs->make<TH1D>("zmumu_eta", ";#eta (Zmumu) [GeV]", 80, -4., 4.) ; 
  h1_["zelel_eta"] = fs->make<TH1D>("zelel_eta", ";#eta (Zelel) [GeV]", 80, -4., 4.) ; 
  h1_["dr_mumu"] = fs->make<TH1D>("dr_mumu", ";#DeltaR(#mu^{+}#mu^{-});;", 40, 0., 4.) ; 
  h1_["dr_elel"] = fs->make<TH1D>("dr_elel", ";#DeltaR(e^{+}e^{-});;", 40, 0., 4.) ; 

}

// ------------ method called once each job just after ending the event loop  ------------
void OS2LAna::endJob() {
  return ; 
}

// ------------ method called when starting to processes a run  ------------
/*
   void
   OS2LAna::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void
   OS2LAna::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void
   OS2LAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void
   OS2LAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
OS2LAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(OS2LAna);
