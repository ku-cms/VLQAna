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

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

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
#include "Analysis/VLQAna/interface/DileptonCandsProducer.h"
#include "Analysis/VLQAna/interface/CandidateFilter.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>

#include <sstream>

#include <boost/range/irange.hpp>

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
    edm::InputTag l_trigName                     ; 
    edm::InputTag l_trigBit                      ; 
   // edm::InputTag l_metFiltersName               ; 
   // edm::InputTag l_metFiltersBit                ; 
   // edm::InputTag l_hbheNoiseFilter              ; 
    std::string   l_genEvtInfoProd               ; 
   // edm::InputTag l_vtxRho                       ; 
   // edm::InputTag l_vtxZ                         ; 
   // edm::InputTag l_vtxNdf                       ; 
    edm::InputTag l_npv                          ; 
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
    edm::InputTag l_met                          ; 
    edm::InputTag l_metPhi                       ; 
   //edm::InputTag l_metNoHF                      ; 
   //edm::InputTag l_metNoHFPhi                   ; 
   //edm::InputTag l_HbbCands                     ; 
    std::vector<std::string> hltPaths_           ; 
    std::vector<std::string> metFilters_         ; 
    edm::ParameterSet DilepCandParams_           ; 
    edm::ParameterSet ZCandParams_               ; 
    edm::ParameterSet BoostedZCandParams_        ; 
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
    double HTMin_                                ; 
    bool   isData_                               ; 

    edm::EDGetTokenT<GenEventInfoProduct> t_genEvtInfoProd ; 

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
  l_trigName              (iConfig.getParameter<edm::InputTag>     ("trigNameLabel")),
  l_trigBit               (iConfig.getParameter<edm::InputTag>     ("trigBitLabel")),
  //l_metFiltersName        (iConfig.getParameter<edm::InputTag>     ("metFiltersNameLabel")),
  //l_metFiltersBit         (iConfig.getParameter<edm::InputTag>     ("metFiltersBitLabel")),
  //l_hbheNoiseFilter       (iConfig.getParameter<edm::InputTag>     ("hbheNoiseFilterLabel")),
  l_genEvtInfoProd        (iConfig.getParameter<std::string>       ("genEvtInfoProdName")),
  //l_vtxRho                (iConfig.getParameter<edm::InputTag>     ("vtxRhoLabel")),  
  //l_vtxZ                  (iConfig.getParameter<edm::InputTag>     ("vtxZLabel")),  
  //l_vtxNdf                (iConfig.getParameter<edm::InputTag>     ("vtxNdfLabel")),  
  l_npv                   (iConfig.getParameter<edm::InputTag>     ("npvLabel")), 
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
  l_met                   (iConfig.getParameter<edm::InputTag>     ("met")),
  l_metPhi                (iConfig.getParameter<edm::InputTag>     ("metPhi")),
  //l_metNoHF               (iConfig.getParameter<edm::InputTag>     ("metNoHF")),
  //l_metNoHFPhi            (iConfig.getParameter<edm::InputTag>     ("metNoHFPhi")),
  //l_HbbCands              (iConfig.getParameter<edm::InputTag>     ("HbbCandsLabel")),
  hltPaths_               (iConfig.getParameter<vector<string>>    ("hltPaths")), 
  metFilters_             (iConfig.getParameter<vector<string>>    ("metFilters")), 
  DilepCandParams_        (iConfig.getParameter<edm::ParameterSet> ("DilepCandParams")),
  ZCandParams_            (iConfig.getParameter<edm::ParameterSet> ("ZCandParams")),
  BoostedZCandParams_     (iConfig.getParameter<edm::ParameterSet> ("BoostedZCandParams")),
  GenHSelParams_          (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
  AK4JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK4JetSelParams")),
  BTaggedLooseAK4SelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedLooseAK4SelParams")),
  BTaggedMediumAK4SelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedMediumAK4SelParams")),
  mupselParams_           (iConfig.getParameter<edm::ParameterSet> ("mupselParams")),
  mumselParams_           (iConfig.getParameter<edm::ParameterSet> ("mumselParams")),
  elpselParams_           (iConfig.getParameter<edm::ParameterSet> ("elpselParams")),
  elmselParams_           (iConfig.getParameter<edm::ParameterSet> ("elmselParams")),
  AK8JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK8JetSelParams")),
  TJetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("TJetSelParams")),
  HJetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("HJetSelParams")),
  WJetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("WJetSelParams")),
  HTMin_                  (iConfig.getParameter<double>            ("HTMin")), 
  isData_                 (iConfig.getParameter<bool>              ("isData"))
{
  t_genEvtInfoProd = consumes<GenEventInfoProduct>(l_genEvtInfoProd) ; 

  produces<unsigned>("ngoodAK4Jets");
  produces<unsigned>("ngoodAK8Jets");
  produces<unsigned>("nbtaggedlooseAK4");
  produces<unsigned>("nTJets");
  produces<unsigned>("nHJets");
  produces<unsigned>("nWJets");
  produces<double>("weight");
  produces<double>("htak4jets");
  produces<double>("htak8jets");
  produces<double>("maxetaak4");
  produces<double>("MassLeading2AK8");
  produces<double>("DeltaEtaLeading2AK8");
  produces<double>("pt1stAK8");
  produces<double>("pt2ndAK8");
  produces<double>("mass1stAK8");
  produces<double>("mass2ndAK8");
  produces<vector<unsigned> >("goodMuonsIdxs");
  produces<vector<unsigned> >("goodElectronsIdxs");
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
  typedef Handle <vector<int>> hint ; 

  hstring h_trigName             ; evt.getByLabel (l_trigName               , h_trigName             );
  hfloat  h_trigBit              ; evt.getByLabel (l_trigBit                , h_trigBit              ); 
  //hstring h_metFiltersName       ; evt.getByLabel (l_metFiltersName         , h_metFiltersName       );
  //hfloat  h_metFiltersBit        ; evt.getByLabel (l_metFiltersBit          , h_metFiltersBit        ); 
  //hfloat  h_vtxRho               ; evt.getByLabel (l_vtxRho                 , h_vtxRho               );
  //hfloat  h_vtxZ                 ; evt.getByLabel (l_vtxZ                   , h_vtxZ                 );
  //hint    h_vtxNdf               ; evt.getByLabel (l_vtxNdf                 , h_vtxNdf               );
  Handle <int> h_npv             ; evt.getByLabel (l_npv                    , h_npv                  );
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

  hfloat h_met                   ; evt.getByLabel(l_met                      , h_met                  ); 
  hfloat h_metPhi                ; evt.getByLabel(l_metPhi                   , h_metPhi               ); 
  //hfloat h_metNoHF               ; evt.getByLabel(l_metNoHF                  , h_metNoHF              ); 
  //hfloat h_metNoHFPhi            ; evt.getByLabel(l_metNoHFPhi               , h_metNoHFPhi           ); 

  //Handle <bool> h_hbheNoiseFilter ; evt.getByLabel (l_hbheNoiseFilter, h_hbheNoiseFilter);

  //// Event variables 
  double evtwt(1.0) ; 
  bool isemu(false)  ; 

  //// Get event weight if not data
  if ( !isData_ ) {
    Handle<GenEventInfoProduct> h_genEvtInfoProd; 
    evt.getByToken(t_genEvtInfoProd, h_genEvtInfoProd);
    evtwt = h_genEvtInfoProd->weight() ; 
    evtwt /= abs(evtwt) ; 
  }

  h1_["cutflow"] -> AddBinContent(1, evtwt) ; 
  h1_["cutflow_nowt"] -> AddBinContent(1) ; 

  //// Presel: HLT 
  unsigned int hltdecisions(0) ; 
  for ( const string& myhltpath : hltPaths_ ) {
    vector<string>::const_iterator it ;
    for (it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it ) {
      if ( it->find(myhltpath) < std::string::npos) {
        hltdecisions |= int((h_trigBit.product())->at( it - (h_trigName.product())->begin() )) << ( it - (h_trigName.product())->begin() ) ;  
      }
    }
  }
  if (hltPaths_.size() > 0 && hltdecisions == 0) return false ; 

  h1_["cutflow"] -> AddBinContent(2, evtwt) ; 
  h1_["cutflow_nowt"] -> AddBinContent(2) ; 

  //// Pre-sel: Good primary vertices
/* 
 unsigned npv(0) ; 
  for ( unsigned ipv = 0; ipv < (h_vtxRho.product())->size(); ++ipv) {
    double vtxRho = (h_vtxRho.product())->at(ipv) ; 
    double vtxZ = (h_vtxZ.product())->at(ipv) ; 
    double vtxNdf = (h_vtxNdf.product())->at(ipv) ; 
    if ( abs(vtxRho) < 2. && abs(vtxZ) <= 24. && vtxNdf > 4 ) ++npv ; 
  }
*/
  int npv = (h_npv.product())[0];
  if ( npv < 1 ) return false ; 

  h1_["cutflow"] -> AddBinContent(3, evtwt) ; 
  h1_["cutflow_nowt"] -> AddBinContent(3) ; 
/*
  //// Pre-sel: MET filters: CSC beam halo and HBHE noise filters
  bool hbheNoiseFilter = h_hbheNoiseFilter.product() ; 
  if ( !hbheNoiseFilter ) return false ; 

  bool metfilterdecision(1) ; 
  //if ( isData_ ) {
  for ( const string& metfilter : metFilters_ ) {
    vector<string>::const_iterator it ; 
    for (it = (h_metFiltersName.product())->begin(); it != (h_metFiltersName.product())->end(); ++it) {
      if ( it->find(metfilter) < std::string::npos) {
        metfilterdecision *= (h_metFiltersBit.product())->at( it - (h_metFiltersName.product())->begin() ) ; 
      }
    }
  }
  //}
  if ( !metfilterdecision ) return false ; 
*/
  h1_["cutflow"] -> AddBinContent(4, evtwt) ; 
  h1_["cutflow_nowt"] -> AddBinContent(4) ; 

  vlq::MuonCollection goodMuPs, goodMuMs ;
  vector<unsigned> muSelIdxs; 
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
      goodMuPs.push_back(mu) ; 
      muSelIdxs.push_back(imu);
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
      goodMuMs.push_back(mu) ; 
      muSelIdxs.push_back(imu);
    }
  }
  vlq::ElectronCollection goodElPs, goodElMs ; 
  vector<unsigned> eleSelIdxs;
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
      goodElPs.push_back(el) ; 
      eleSelIdxs.push_back(iel);
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
      goodElMs.push_back(el) ; 
      eleSelIdxs.push_back(iel);
    }
  }

  //// Presel: l+l- pairs 

  vlq::CandidateCollection dimu, zmumu, zmumuBoosted, diel, zelel, zelelBoosted ; 

  //// Do e+e- or mu+mu - 
  if ( goodMuPs.size()*goodMuMs.size() > 0 || goodElPs.size()*goodElMs.size() > 0 ) { 
    h1_["cutflow"] -> AddBinContent(5, evtwt) ; 
    h1_["cutflow_nowt"] -> AddBinContent(5) ; 

    DileptonCandsProducer<vlq::MuonCollection> dimuprod(DilepCandParams_, goodMuPs, goodMuMs) ; 
    dimuprod(dimu); 

    DileptonCandsProducer<vlq::ElectronCollection> dielprod(DilepCandParams_, goodElPs, goodElMs) ; 
    dielprod(diel) ; 

    CandidateFilter zllfilter(ZCandParams_) ; 
    zllfilter(dimu, zmumu) ; 
    zllfilter(diel, zelel) ; 

    CandidateFilter boostedzllfilter(BoostedZCandParams_) ; 
    boostedzllfilter(zmumu, zmumuBoosted) ; 
    boostedzllfilter(zelel, zelelBoosted) ; 

    for (auto idimu : dimu) {
      h1_["mass_mumu"] -> Fill(idimu.getMass(), evtwt) ; 
      h1_["mass_mumu_nowt"] -> Fill(idimu.getMass()) ; 
    }

    for (auto idiel : diel) {
      h1_["mass_elel"] -> Fill(idiel.getMass(), evtwt) ; 
      h1_["mass_elel_nowt"] -> Fill(idiel.getMass()) ; 
    }

    h1_["nzmumu"] -> Fill (zmumu.size(), evtwt) ; 
    h1_["nzmumu_nowt"] -> Fill (zmumu.size()) ; 
    h1_["nzelel"] -> Fill (zelel.size(), evtwt) ; 
    h1_["nzelel_nowt"] -> Fill (zelel.size()) ; 

    //// Preselection  Z candidates 
    if ( zmumu.size() > 0 || zelel.size() > 0 ) {
      h1_["cutflow"] -> AddBinContent(6, evtwt) ; 
      h1_["cutflow_nowt"] -> AddBinContent(6) ; 

      for (auto izmumu : zmumu) {
        h1_["mass_zmumu"] -> Fill(izmumu.getMass(), evtwt) ; 
        h1_["mass_zmumu_nowt"] -> Fill(izmumu.getMass()) ; 
        h1_["pt_zmumu"] -> Fill(izmumu.getPt(), evtwt) ; 
        h1_["pt_zmumu_nowt"] -> Fill(izmumu.getPt()) ; 
        h1_["eta_zmumu"] -> Fill(izmumu.getEta(), evtwt) ; 
        h1_["eta_zmumu_nowt"] -> Fill(izmumu.getEta()) ; 
      }

      for (auto izelel : zelel) {
        h1_["mass_zelel"] -> Fill(izelel.getMass(), evtwt) ; 
        h1_["mass_zelel_nowt"] -> Fill(izelel.getMass()) ; 
        h1_["pt_zelel"] -> Fill(izelel.getPt(), evtwt) ; 
        h1_["pt_zelel_nowt"] -> Fill(izelel.getPt()) ; 
        h1_["eta_zelel"] -> Fill(izelel.getEta(), evtwt) ; 
        h1_["eta_zelel_nowt"] -> Fill(izelel.getEta()) ; 
      }

      //// Selection: Z pT
      if ( zmumuBoosted.size() > 0 || zelelBoosted.size() > 0 ) {
        h1_["cutflow"] -> AddBinContent(7, evtwt) ;
        h1_["cutflow_nowt"] -> AddBinContent(7) ; 
      }

    }

  } 

  //// Do emu 
  if ( (goodMuPs.size() > 0 && goodElMs.size() > 0) || (goodMuMs.size() > 0 && goodElPs.size() > 0) ) isemu = true ; 

  double met = (h_met.product())->at(0) ; 
  double metPhi = (h_metPhi.product())->at(0) ; 

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

  if ( btaggedlooseAK4.size() > 0 ) {
    h1_["cutflow"] -> AddBinContent(8, evtwt) ;  
    h1_["cutflow_nowt"] -> AddBinContent(8) ; 
  }

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
    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
        (h_jetAK8Eta.product())->at(ijet), 
        (h_jetAK8Phi.product())->at(ijet), 
        (h_jetAK8Mass.product())->at(ijet) ) ;
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
    } 
    retwjetsel = false ;
    if (wjetsel(evt, ijet,retwjetsel) == true ) { 
      wjets.push_back(jet) ; 
      selwjets.push_back(ijet) ; 
    } 
  }

  HT htak4(goodAK4Jets) ; 

  if ( (isemu || (dimu.size() > 0 && zmumu.size() ==0) || (diel.size() > 0 && zelel.size() == 0))
      && btaggedmediumAK4.size() > 0) {

    h1_["met_ttbaremu"] ->Fill(met, evtwt) ; 
    h1_["metPhi_ttbaremu"] ->Fill(metPhi, evtwt) ; 
    h1_["ht_ttbaremu"] ->Fill(htak4.getHT(), evtwt) ; 
    h1_["nak8_ttbaremu"] -> Fill(goodAK8Jets.size(), evtwt) ; 
    h1_["nak4_ttbaremu"] -> Fill(goodAK4Jets.size(), evtwt) ; 
    h1_["nbloose_ttbaremu"] -> Fill(btaggedlooseAK4.size(), evtwt) ; 
    h1_["nbmedium_ttbaremu"] -> Fill(btaggedmediumAK4.size(), evtwt) ; 

    for ( auto mu : goodMuPs ) {
      h1_["pt_mu_ttbaremu"] -> Fill (mu.getPt()) ; 
      h1_["eta_mu_ttbaremu"] -> Fill (mu.getEta()) ; 
      TLorentzVector p4_mu, p4_el ; 
      p4_mu.SetPtEtaPhiM(mu.getPt(), mu.getEta(), mu.getPhi(), mu.getMass() ) ; 
      for ( auto el : goodElMs ) {
        p4_el.SetPtEtaPhiM(el.getPt(), el.getEta(), el.getPhi(), el.getMass() ) ; 
        //h1_["dr_elmu_ttbaremu"] -> Fill(p4_mu.DeltaR(p4_el)) ; 
        h1_["mass_elmu_ttbaremu"] -> Fill((p4_mu+p4_el).Mag()) ; 
      }
    }

    for ( auto mu : goodMuMs ) {
      h1_["pt_mu_ttbaremu"] -> Fill (mu.getPt()) ; 
      h1_["eta_mu_ttbaremu"] -> Fill (mu.getEta()) ; 
      TLorentzVector p4_mu, p4_el ; 
      p4_mu.SetPtEtaPhiM(mu.getPt(), mu.getEta(), mu.getPhi(), mu.getMass() ) ; 
      for ( auto el : goodElPs ) {
        p4_el.SetPtEtaPhiM(el.getPt(), el.getEta(), el.getPhi(), el.getMass() ) ; 
        //h1_["dr_elmu_ttbaremu"] -> Fill(p4_mu.DeltaR(p4_el)) ; 
        h1_["mass_elmu_ttbaremu"] -> Fill((p4_mu+p4_el).Mag()) ; 
      }
    } 

    for ( auto el : goodElPs ) {
      h1_["pt_el_ttbaremu"] -> Fill (el.getPt()) ; 
      h1_["eta_el_ttbaremu"] -> Fill (el.getEta()) ; 
    }

    for ( auto el : goodElMs ) {
      h1_["pt_el_ttbaremu"] -> Fill (el.getPt()) ; 
      h1_["eta_el_ttbaremu"] -> Fill (el.getEta()) ; 
    }

  }
  else if ( (goodMuPs.size() > 0 || goodMuMs.size() > 0 || goodElPs.size() > 0 || goodElMs.size() > 0) 
       && btaggedmediumAK4.size() > 1 ) { //// Fill ttbar1lep plots 

    h1_["met_ttbar1lep"] ->Fill(met, evtwt) ; 
    h1_["metPhi_ttbar1lep"] ->Fill(metPhi, evtwt) ; 
    h1_["ht_ttbar1lep"] ->Fill(htak4.getHT(), evtwt) ; 
    h1_["nak8_ttbar1lep"] -> Fill(goodAK8Jets.size(), evtwt) ; 
    h1_["nak4_ttbar1lep"] -> Fill(goodAK4Jets.size(), evtwt) ; 
    h1_["nbloose_ttbar1lep"] -> Fill(btaggedlooseAK4.size(), evtwt) ; 
    h1_["nbmedium_ttbar1lep"] -> Fill(btaggedmediumAK4.size(), evtwt) ; 

    for ( auto mu : goodMuPs ) {
      h1_["pt_mu_ttbar1lep"] -> Fill (mu.getPt()) ; 
      h1_["eta_mu_ttbar1lep"] -> Fill (mu.getEta()) ; 
    }

    for ( auto mu : goodMuMs ) {
      h1_["pt_mu_ttbar1lep"] -> Fill (mu.getPt()) ; 
      h1_["eta_mu_ttbar1lep"] -> Fill (mu.getEta()) ; 
    } 

    for ( auto el : goodElPs ) {
      h1_["pt_el_ttbar1lep"] -> Fill (el.getPt()) ; 
      h1_["eta_el_ttbar1lep"] -> Fill (el.getEta()) ; 
    }

    for ( auto el : goodElMs ) {
      h1_["pt_el_ttbar1lep"] -> Fill (el.getPt()) ; 
      h1_["eta_el_ttbar1lep"] -> Fill (el.getEta()) ; 
    }

  }

  //// Preselection HT
  if ( htak4.getHT() < HTMin_ ) return false; 

  if ( wjets.size() > 0 ) h1_["cutflow"] -> AddBinContent(9, evtwt) ;  
  if ( wjets.size() > 0 ) h1_["cutflow_nowt"] -> AddBinContent(9) ;  

  if ( hjets.size() > 0 ) h1_["cutflow"] -> AddBinContent(10, evtwt) ;  
  if ( hjets.size() > 0 ) h1_["cutflow_nowt"] -> AddBinContent(10) ;  

  if ( tjets.size() > 0 ) h1_["cutflow"] -> AddBinContent(11, evtwt) ;  
  if ( tjets.size() > 0 ) h1_["cutflow_nowt"] -> AddBinContent(11) ;  

  //// Pick forwardmost AK4 jet
  double maxeta(0) ;
  vlq::Jet forwardestjet ; 
  for ( auto& jet : goodAK4Jets ) {
    if ( abs(jet.getEta()) > abs(maxeta) ) { 
      forwardestjet = jet ; 
      maxeta = jet.getEta() ; 
    }
  }

  //// Selection: fat jet
  if ( goodAK8Jets.size() < 1 ) return false ; 

  HT htak8(goodAK8Jets) ; 

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
  //double csvak8leading ((goodAK8Jets.at(0)).getCSV()) ; 

  h1_["ptak8leading"] -> Fill(ptak8leading, evtwt) ; 
  h1_["etaak8leading"] -> Fill((goodAK8Jets.at(0)).getEta(), evtwt) ;
  h1_["mak8leading"] -> Fill(mak8leading, evtwt) ; 
  h1_["trimmedmak8leading"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass(), evtwt) ;
  h1_["prunedmak8leading"] -> Fill((goodAK8Jets.at(0)).getPrunedMass(), evtwt) ;
  h1_["softdropmak8leading"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass(), evtwt) ;

  double ptak82nd (0) ;
  double mak82nd (0) ;
/*
  double csvak82nd (0) ; 
  if (goodAK8Jets.size() > 1) {
    ptak82nd = (goodAK8Jets.at(1)).getPt() ; 
    mak82nd = (goodAK8Jets.at(1)).getMass() ; 
    csvak82nd = (goodAK8Jets.at(1)).getCSV() ; 
  }
*/
  h1_["ptak82nd"] -> Fill(ptak82nd) ; 
  h1_["mak82nd"] -> Fill(mak82nd) ; 

  double ptak4leading ((h_jetAK4Pt.product())->at(ak4selIdxs.at(0))) ;   
  h1_["ptak4leading"] -> Fill(ptak4leading) ; 
  h1_["etaak4leading"] -> Fill((h_jetAK4Eta.product())->at(ak4selIdxs.at(0))) ; 

  double ptbjetleading (-1);
  double csvbjetleading (-1);
  //double csvbjethighestcsv(-1); 
  if ( bjetIdxs.size() > 0 ) {
    ptbjetleading = (h_jetAK4Pt.product())->at(bjetIdxs.at(0)) ; 
    csvbjetleading = (h_jetAK4CSV.product())->at(bjetIdxs.at(0)) ; 
    h1_["ptbjetleading"] -> Fill(ptbjetleading) ; 
    h1_["etabjetleading"] -> Fill((h_jetAK4Eta.product())->at(bjetIdxs.at(0))) ; 
    h1_["csvbjetleading"] -> Fill(csvbjetleading) ; 

  }

  //// Make H cands
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

  h1_["nak8"] -> Fill(goodAK8Jets.size(), evtwt) ; 
  h1_["nak4"] -> Fill(goodAK4Jets.size(), evtwt) ; 
  h1_["nbloose"] -> Fill(btaggedlooseAK4.size(), evtwt) ; 
  h1_["nbmedium"] -> Fill(btaggedmediumAK4.size(), evtwt) ; 
  h1_["nwjet"] -> Fill(wjets.size(), evtwt) ; 
  h1_["nhjet"] -> Fill(hjets.size(), evtwt) ; 
  h1_["ntjet"] -> Fill(tjets.size(), evtwt) ; 

  h1_["ht"] ->Fill(htak4.getHT(), evtwt) ; 
  h1_["ht_nowt"] ->Fill(htak4.getHT()) ; 

  h1_["met"] ->Fill(met, evtwt) ; 
  h1_["met_nowt"] ->Fill(metPhi) ; 
  h1_["metPhi"] ->Fill(metPhi, evtwt) ; 
  h1_["metPhi_nowt"] ->Fill(metPhi) ; 

  vlq::MuonCollection goodMus; 
  vlq::ElectronCollection goodEls ;

  if (goodMuPs.size()+goodMuMs.size() > 0) { 
    goodMus.reserve(goodMuPs.size()+goodMuMs.size()) ; 
    for ( auto mup : goodMuPs ) {
      goodMus.push_back(mup) ; 
    }
    for ( auto mum : goodMuMs ) {
      goodMus.push_back(mum) ; 
    }
  }

  if (goodElPs.size()+goodElMs.size() > 0) {
    goodEls.reserve(goodElPs.size()+goodElMs.size()) ; 
    for ( auto elp : goodElPs ) {
      goodEls.push_back(elp) ; 
    }
    for ( auto elm : goodElMs ) {
      goodEls.push_back(elm) ; 
    }
  }

  if (goodMus.size() > 0) std::sort(goodMus.begin(), goodMus.end(), Utilities::sortByPt<vlq::Muon>) ;
  if (goodEls.size() > 0) std::sort(goodEls.begin(), goodEls.end(), Utilities::sortByPt<vlq::Electron>) ;

  //loop over good

  std::auto_ptr<unsigned> ngoodAK4Jets ( new unsigned(goodAK4Jets.size()) );
  std::auto_ptr<unsigned> ngoodAK8Jets ( new unsigned(goodAK8Jets.size()) );
  std::auto_ptr<unsigned> nbtaggedlooseAK4 ( new unsigned(btaggedlooseAK4.size()) );
  std::auto_ptr<unsigned> nTJets ( new unsigned(tjets.size()) );
  std::auto_ptr<unsigned> nHJets ( new unsigned(hjets.size()) );
  std::auto_ptr<unsigned> nWJets ( new unsigned(wjets.size()) );
  std::auto_ptr<double> weight ( new double(evtwt) );
  std::auto_ptr<double> htak4jets ( new double(htak4.getHT()) );
  std::auto_ptr<double> htak8jets ( new double(htak8.getHT()) );
  std::auto_ptr<double> maxetaak4 ( new double(maxeta) );
  std::auto_ptr<double> MassLeading2AK8 ( new double(mak8_12) );
  std::auto_ptr<double> DeltaEtaLeading2AK8 ( new double(detaLeading2AK8) );
  std::auto_ptr<double> pt1stAK8   ( new double(ptak8_1) );
  std::auto_ptr<double> pt2ndAK8   ( new double(ptak8_2) );
  std::auto_ptr<double> mass1stAK8 ( new double(mak8_1) );
  std::auto_ptr<double> mass2ndAK8 ( new double(mak8_2) );
  std::auto_ptr<vector<unsigned> > goodMuonsIdxs ( new vector<unsigned>(muSelIdxs));
  std::auto_ptr<vector<unsigned> > goodElectronsIdxs ( new vector<unsigned>(eleSelIdxs));
  std::auto_ptr<vector<unsigned> > ak4goodjets ( new vector<unsigned>(ak4selIdxs));
  std::auto_ptr<vector<unsigned> > ak8goodjets ( new vector<unsigned>(ak8selIdxs));
  std::auto_ptr<vector<unsigned> > bjetIdxsptr ( new vector<unsigned>(bjetIdxs));
  std::auto_ptr<vector<unsigned> > tjetIdxs ( new vector<unsigned>(seltjets));
  std::auto_ptr<vector<unsigned> > hjetIdxs ( new vector<unsigned>(selhjets));
  std::auto_ptr<vector<unsigned> > wjetIdxs ( new vector<unsigned>(selwjets));

  evt.put(ngoodAK4Jets, "ngoodAK4Jets") ; 
  evt.put(ngoodAK8Jets, "ngoodAK8Jets") ; 
  evt.put(nbtaggedlooseAK4, "nbtaggedlooseAK4") ; 
  evt.put(nTJets, "nTJets") ; 
  evt.put(nHJets, "nHJets") ; 
  evt.put(nWJets, "nWJets") ;
  evt.put(weight, "weight") ; 
  evt.put(htak4jets, "htak4jets") ; 
  evt.put(htak8jets, "htak8jets") ; 
  evt.put(maxetaak4, "maxetaak4") ; 
  evt.put(MassLeading2AK8, "MassLeading2AK8") ; 
  evt.put(DeltaEtaLeading2AK8, "DeltaEtaLeading2AK8") ; 
  evt.put(pt1stAK8  , "pt1stAK8") ; 
  evt.put(pt2ndAK8  , "pt2ndAK8") ; 
  evt.put(mass1stAK8, "mass1stAK8") ; 
  evt.put(mass2ndAK8, "mass2ndAK8") ;
  evt.put(goodMuonsIdxs, "goodMuonsIdxs");
  evt.put(goodElectronsIdxs, "goodElectronsIdxs");
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

  h1_["cutflow_nowt"] = fs->make<TH1D>("cutflow_nowt", "cut flow", 11, 0, 11) ;  
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(2, "Trigger") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(3, "Nvtx") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(4, "MET filters") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(5, "l^{+}l^{-} pairs") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(6, "Z(l^{+}l^{-})") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(7, "p_{T}(Z)") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(8, "N(b jet)>0") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(9, "N(W jet)>0") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(10, "N(H jet)>0") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(11, "N(top jet)>0") ; 

  h1_["cutflow_nowt"] -> Sumw2() ; 

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 11, 0, 11) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2, "Trigger") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3, "Nvtx") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4, "MET filters") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5, "l^{+}l^{-} pairs") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6, "Z(l^{+}l^{-})") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7, "p_{T}(Z)") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8, "N(b jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9, "N(W jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(10, "N(H jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(11, "N(top jet)>0") ; 

  h1_["cutflow"] -> Sumw2() ; 

  h1_["pt_leading_mu"] = fs->make<TH1D>("pt_leading_mu", ";p_{T} (leading #mu^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_leading_mu"] = fs->make<TH1D>("eta_leading_mu", ";#eta (leading #mu^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["pt_2nd_mu"] = fs->make<TH1D>("pt_2nd_mu", ";p_{T} (2nd #mu^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_2nd_mu"] = fs->make<TH1D>("eta_2nd_mu", ";#eta (2nd #mu^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["dr_mumu"] = fs->make<TH1D>("dr_mumu", ";#DeltaR(#mu^{+}#mu^{-});;", 40, 0., 4.) ; 
  h1_["mass_mumu"] = fs->make<TH1D>("mass_mumu", ";M(#mu^{+}#mu^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["mass_zmumu"] = fs->make<TH1D>("mass_zmumu", ";M(Z#rightarrow#mu^{+}#mu^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["pt_zmumu"] = fs->make<TH1D>("pt_zmumu", ";p_{T} (Z#rightarrow#mu^{+}#mu^{-}) [GeV]", 100, 0., 2000.) ; 
  h1_["eta_zmumu"] = fs->make<TH1D>("eta_zmumu", ";#eta (Z#rightarrow#mu^{+}#mu^{-}) [GeV]", 80, -4., 4.) ; 
  h1_["nzmumu"] = fs->make<TH1D>("nzmumu", "N (Z#rightarrow#mu^{+}#mu^{-})", 5, -0.5, 4.5) ; 

  h1_["pt_leading_el"] = fs->make<TH1D>("pt_leading_el", ";p_{T} (leading e^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_leading_el"] = fs->make<TH1D>("eta_leading_el", ";#eta (leading e^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["pt_2nd_el"] = fs->make<TH1D>("pt_2nd_el", ";p_{T} (2nd e^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_2nd_el"] = fs->make<TH1D>("eta_2nd_el", ";#eta (2nd e^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["dr_elel"] = fs->make<TH1D>("dr_elel", ";#DeltaR(e^{+}e^{-});;", 40, 0., 4.) ; 
  h1_["mass_elel"] = fs->make<TH1D>("mass_elel", ";M(e^{+}e^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["mass_zelel"] = fs->make<TH1D>("mass_zelel", ";M(Z#rightarrow e^{+}e^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["pt_zelel"] = fs->make<TH1D>("pt_zelel", ";p_{T} (Z#rightarrow e^{+}e^{-}) [GeV]", 100, 0., 2000.) ; 
  h1_["eta_zelel"] = fs->make<TH1D>("eta_zelel", ";#eta (Z#rightarrow e^{+}e^{-}) [GeV]", 80, -4., 4.) ; 
  h1_["nzelel"] = fs->make<TH1D>("nzelel", "N (Z#rightarrow e^{+}e^{-})", 5, -0.5, 4.5) ; 

  h1_["nak8"] = fs->make<TH1D>("nak8", ";N(AK8 jets);;" , 11, -0.5,10.5) ; 
  h1_["nak4"] = fs->make<TH1D>("nak4", ";N(AK4 jets);;" , 11, -0.5,10.5) ; 
  h1_["nbloose"] = fs->make<TH1D>("nbloose", ";N(b jets, loose OP);;" , 11, -0.5,10.5) ; 
  h1_["nbmedium"] = fs->make<TH1D>("nbmedium", ";N(b jets, medium OP);;" , 11, -0.5,10.5) ; 
  h1_["nwjet"] = fs->make<TH1D>("nwjet", ";N(W jets );;" , 6, -0.5,5.5) ; 
  h1_["nhjet"] = fs->make<TH1D>("nhjet", ";N(H jets );;" , 6, -0.5,5.5) ; 
  h1_["ntjet"] = fs->make<TH1D>("ntjet", ";N(top jets);;" , 6, -0.5,5.5) ; 

  h1_["ptak8leading"]  = fs->make<TH1D>("ptak8leading", ";p_{T}(leading AK8 jet) [GeV];;" , 40, 0., 2000.) ; 
  h1_["etaak8leading"] = fs->make<TH1D>("etaak8leading", ";#eta(leading AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak8leading"] = fs->make<TH1D>("mak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak8leading"] = fs->make<TH1D>("prunedmak8leading", ";M(pruned leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak8leading"] = fs->make<TH1D>("trimmedmak8leading", ";M(trimmed leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak8leading"] = fs->make<TH1D>("softdropmak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak82nd"]  = fs->make<TH1D>("ptak82nd", ";p_{T}(2nd AK8 jet) [GeV];;" , 40, 0., 2000.) ; 
  h1_["etaak82nd"] = fs->make<TH1D>("etaak82nd", ";#eta(2nd AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak82nd"] = fs->make<TH1D>("mak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak82nd"] = fs->make<TH1D>("prunedmak82nd", ";M(pruned 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak82nd"] = fs->make<TH1D>("trimmedmak82nd", ";M(trimmed 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak82nd"] = fs->make<TH1D>("softdropmak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak4leading"] = fs->make<TH1D>("ptak4leading", ";p_{T}(leading AK4 jet);;" , 40, 0., 2000.) ;
  h1_["etaak4leading"] = fs->make<TH1D>("etaak4leading", ";#eta(leading AK4 jet);;" , 80 ,-4. ,4.) ; 
  h1_["ptbjetleading"]  = fs->make<TH1D>("ptbjetleading", ";p_{T}(leading b jet) [GeV];;" , 40, 0., 2000.) ; 
  h1_["etabjetleading"] = fs->make<TH1D>("etabjetleading", ";#eta(leading b jet);;" , 80 ,-4. ,4.) ; 
  h1_["csvbjetleading"] = fs->make<TH1D>("csvbjetleading", ";CSV (leading b jet);;" ,50 ,0. ,1.) ; 

  h1_["ht"] = fs->make<TH1D>("ht" ,";H_{T} (AK4 jets) [GeV]", 200, 0., 4000.) ; 

  h1_["met"] = fs->make<TH1D>("met", ";E_{T}^{miss} [GeV];;", 40, 0., 400.) ; 
  h1_["metPhi"] = fs->make<TH1D>("metPhi", ";#phi(E_{T}^{miss});;", 80, -4., 4.) ; 

  h1_["pt_leading_mu_nowt"] = fs->make<TH1D>("pt_leading_mu_nowt", ";p_{T} (leading #mu^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_leading_mu_nowt"] = fs->make<TH1D>("eta_leading_mu_nowt", ";#eta (leading #mu^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["pt_2nd_mu_nowt"] = fs->make<TH1D>("pt_2nd_mu_nowt", ";p_{T} (2nd #mu^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_2nd_mu_nowt"] = fs->make<TH1D>("eta_2nd_mu_nowt", ";#eta (2nd #mu^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["dr_mumu_nowt"] = fs->make<TH1D>("dr_mumu_nowt", ";#DeltaR(#mu^{+}#mu^{-});;", 40, 0., 4.) ; 
  h1_["mass_mumu_nowt"] = fs->make<TH1D>("mass_mumu_nowt", ";M(#mu^{+}#mu^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["mass_zmumu_nowt"] = fs->make<TH1D>("mass_zmumu_nowt", ";M(Z#rightarrow#mu^{+}#mu^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["pt_zmumu_nowt"] = fs->make<TH1D>("pt_zmumu_nowt", ";p_{T} (Z#rightarrow#mu^{+}#mu^{-}) [GeV]", 100, 0., 2000.) ; 
  h1_["eta_zmumu_nowt"] = fs->make<TH1D>("eta_zmumu_nowt", ";#eta (Z#rightarrow#mu^{+}#mu^{-}) [GeV]", 80, -4., 4.) ; 
  h1_["nzmumu_nowt"] = fs->make<TH1D>("nzmumu_nowt", "N (Z#rightarrow#mu^{+}#mu^{-})", 5, -0.5, 4.5) ; 

  h1_["pt_leading_el_nowt"] = fs->make<TH1D>("pt_leading_el_nowt", ";p_{T} (leading e^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_leading_el_nowt"] = fs->make<TH1D>("eta_leading_el_nowt", ";#eta (leading e^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["pt_2nd_el_nowt"] = fs->make<TH1D>("pt_2nd_el_nowt", ";p_{T} (2nd e^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_2nd_el_nowt"] = fs->make<TH1D>("eta_2nd_el_nowt", ";#eta (2nd e^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["dr_elel_nowt"] = fs->make<TH1D>("dr_elel_nowt", ";#DeltaR(e^{+}e^{-});;", 40, 0., 4.) ; 
  h1_["mass_elel_nowt"] = fs->make<TH1D>("mass_elel_nowt", ";M(e^{+}e^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["mass_zelel_nowt"] = fs->make<TH1D>("mass_zelel_nowt", ";M(Z#rightarrow e^{+}e^{-}) [GeV]", 100, 20., 220.) ; 
  h1_["pt_zelel_nowt"] = fs->make<TH1D>("pt_zelel_nowt", ";p_{T} (Z#rightarrow e^{+}e^{-}) [GeV]", 100, 0., 2000.) ; 
  h1_["eta_zelel_nowt"] = fs->make<TH1D>("eta_zelel_nowt", ";#eta (Z#rightarrow e^{+}e^{-}) [GeV]", 80, -4., 4.) ; 
  h1_["nzelel_nowt"] = fs->make<TH1D>("nzelel_nowt", "N (Z#rightarrow e^{+}e^{-})", 5, -0.5, 4.5) ; 

  h1_["nak8_nowt"] = fs->make<TH1D>("nak8_nowt", ";N(AK8 jets);;" , 11, -0.5,10.5) ; 
  h1_["nak4_nowt"] = fs->make<TH1D>("nak4_nowt", ";N(AK4 jets);;" , 11, -0.5,10.5) ; 
  h1_["nbloose_nowt"] = fs->make<TH1D>("nbloose_nowt", ";N(b jets, loose OP);;" , 11, -0.5,10.5) ; 
  h1_["nbmedium_nowt"] = fs->make<TH1D>("nbmedium_nowt", ";N(b jets, medium OP);;" , 11, -0.5,10.5) ; 
  h1_["nwjet_nowt"] = fs->make<TH1D>("nwjet_nowt", ";N(W jets );;" , 6, -0.5,5.5) ; 
  h1_["nhjet_nowt"] = fs->make<TH1D>("nhjet_nowt", ";N(H jets );;" , 6, -0.5,5.5) ; 
  h1_["ntjet_nowt"] = fs->make<TH1D>("ntjet_nowt", ";N(top jets);;" , 6, -0.5,5.5) ; 

  h1_["ptak8leading_nowt"]  = fs->make<TH1D>("ptak8leading_nowt", ";p_{T}(leading AK8 jet) [GeV];;" , 40, 0., 2000.) ; 
  h1_["etaak8leading_nowt"] = fs->make<TH1D>("etaak8leading_nowt", ";#eta(leading AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak8leading_nowt"] = fs->make<TH1D>("mak8leading_nowt", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak8leading_nowt"] = fs->make<TH1D>("prunedmak8leading_nowt", ";M(pruned leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak8leading_nowt"] = fs->make<TH1D>("trimmedmak8leading_nowt", ";M(trimmed leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak8leading_nowt"] = fs->make<TH1D>("softdropmak8leading_nowt", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak82nd_nowt"]  = fs->make<TH1D>("ptak82nd_nowt", ";p_{T}(2nd AK8 jet) [GeV];;" , 40, 0., 2000.) ; 
  h1_["etaak82nd_nowt"] = fs->make<TH1D>("etaak82nd_nowt", ";#eta(2nd AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak82nd_nowt"] = fs->make<TH1D>("mak82nd_nowt", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak82nd_nowt"] = fs->make<TH1D>("prunedmak82nd_nowt", ";M(pruned 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak82nd_nowt"] = fs->make<TH1D>("trimmedmak82nd_nowt", ";M(trimmed 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak82nd_nowt"] = fs->make<TH1D>("softdropmak82nd_nowt", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak4leading_nowt"] = fs->make<TH1D>("ptak4leading_nowt", ";p_{T}(leading AK4 jet);;" , 40, 0., 2000.) ;
  h1_["etaak4leading_nowt"] = fs->make<TH1D>("etaak4leading_nowt", ";#eta(leading AK4 jet);;" , 80 ,-4. ,4.) ; 
  h1_["ptbjetleading_nowt"]  = fs->make<TH1D>("ptbjetleading_nowt", ";p_{T}(leading b jet) [GeV];;" , 40, 0., 2000.) ; 
  h1_["etabjetleading_nowt"] = fs->make<TH1D>("etabjetleading_nowt", ";#eta(leading b jet);;" , 80 ,-4. ,4.) ; 
  h1_["csvbjetleading_nowt"] = fs->make<TH1D>("csvbjetleading_nowt", ";CSV (leading b jet);;" ,50 ,0. ,1.) ; 

  h1_["ht_nowt"] = fs->make<TH1D>("ht_nowt", ";H_{T} (AK4 jets) [GeV]", 200, 0., 4000.) ; 

  h1_["met_nowt"] = fs->make<TH1D>("met_nowt", ";E_{T}^{miss} [GeV];;", 40, 0., 400.) ; 
  h1_["metPhi_nowt"] = fs->make<TH1D>("metPhi_nowt", ";#phi(E_{T}^{miss});;", 80, -4., 4.) ; 

  h1_["met_ttbar1lep"] = fs->make<TH1D>("met_ttbar1lep", ";E_{T}^{miss} [GeV];;", 20, 0., 400.) ; 
  h1_["metPhi_ttbar1lep"] = fs->make<TH1D>("metPhi_ttbar1lep", ";#phi(E_{T}^{miss});;", 80, -4., 4.) ; 
  h1_["ht_ttbar1lep"] = fs->make<TH1D>("ht_ttbar1lep", ";H_{T} (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["nak8_ttbar1lep"] = fs->make<TH1D>("nak8_ttbar1lep", ";N(AK8 jets);;" , 11, -0.5,10.5) ; 
  h1_["nak4_ttbar1lep"] = fs->make<TH1D>("nak4_ttbar1lep", ";N(AK4 jets);;" , 11, -0.5,10.5) ; 
  h1_["nbloose_ttbar1lep"] = fs->make<TH1D>("nbloose_ttbar1lep", ";N(b jets, loose OP);;" , 11, -0.5,10.5) ; 
  h1_["nbmedium_ttbar1lep"] = fs->make<TH1D>("nbmedium_ttbar1lep", ";N(b jets, medium OP);;" , 11, -0.5,10.5) ; 
  h1_["pt_mu_ttbar1lep"] = fs->make<TH1D>("pt_mu_ttbar1lep", ";p_{T} (#mu^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_mu_ttbar1lep"] = fs->make<TH1D>("eta_mu_ttbar1lep", ";#eta (mu^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["pt_el_ttbar1lep"] = fs->make<TH1D>("pt_el_ttbar1lep", ";p_{T} (e^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_el_ttbar1lep"] = fs->make<TH1D>("eta_el_ttbar1lep", ";#eta (e^{#pm}) [GeV]", 80, -4., 4.) ;

  h1_["met_ttbaremu"] = fs->make<TH1D>("met_ttbaremu", ";E_{T}^{miss} [GeV];;", 40, 0., 400.) ; 
  h1_["metPhi_ttbaremu"] = fs->make<TH1D>("metPhi_ttbaremu", ";#phi(E_{T}^{miss});;", 80, -4., 4.) ; 
  h1_["ht_ttbaremu"] = fs->make<TH1D>("ht_ttbaremu", ";H_{T} (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["nak8_ttbaremu"] = fs->make<TH1D>("nak8_ttbaremu", ";N(AK8 jets);;" , 11, -0.5,10.5) ; 
  h1_["nak4_ttbaremu"] = fs->make<TH1D>("nak4_ttbaremu", ";N(AK4 jets);;" , 11, -0.5,10.5) ; 
  h1_["nbloose_ttbaremu"] = fs->make<TH1D>("nbloose_ttbaremu", ";N(b jets, loose OP);;" , 11, -0.5,10.5) ; 
  h1_["nbmedium_ttbaremu"] = fs->make<TH1D>("nbmedium_ttbaremu", ";N(b jets, medium OP);;" , 11, -0.5,10.5) ; 
  h1_["pt_mu_ttbaremu"] = fs->make<TH1D>("pt_mu_ttbaremu", ";p_{T} (#mu^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_mu_ttbaremu"] = fs->make<TH1D>("eta_mu_ttbaremu", ";#eta (mu^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["pt_el_ttbaremu"] = fs->make<TH1D>("pt_el_ttbaremu", ";p_{T} (e^{#pm}) [GeV]", 50, 0., 1000.) ;
  h1_["eta_el_ttbaremu"] = fs->make<TH1D>("eta_el_ttbaremu", ";#eta (e^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_["dr_elmu_ttbaremu"] = fs->make<TH1D>("dr_elmu_ttbaremu", ";#DeltaR(e^{#pm}#mu^{#mp});;", 40, 0., 4.) ; 
  h1_["mass_elmu_ttbaremu"] = fs->make<TH1D>("mass_elmu_ttbaremu", ";M(e^{#pm}#mu^{#mp}) [GeV]", 100, 20., 220.) ; 

}

// ------------ method called once each job just after ending the event loop  ------------
void OS2LAna::endJob() {
  return ; 
}

// ------------ method called when starting to processes a run  ------------
/*
   void OS2LAna::beginRun(edm::Run const&, edm::EventSetup const&) {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void OS2LAna::endRun(edm::Run const&, edm::EventSetup const&) {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void OS2LAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void OS2LAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
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
