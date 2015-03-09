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


// system include files
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

#include "Analysis/VLQAna/interface/JetSelector.h"
#include "Analysis/VLQAna/interface/HT.h"

#include <TTree.h>
#include <TLorentzVector.h>


//
// class declaration
//

class VLQAna : public edm::EDFilter {
   public:
      explicit VLQAna(const edm::ParameterSet&);
      ~VLQAna();

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
    edm::InputTag l_trigName                  ; 
    edm::InputTag l_trigBit                   ; 
    edm::InputTag l_jetAK8Pt                  ; 
    edm::InputTag l_jetAK8Eta                 ; 
    edm::InputTag l_jetAK8Phi                 ; 
    edm::InputTag l_jetAK8Mass                ; 
    edm::InputTag l_jetAK8FilteredMass        ; 
    edm::InputTag l_jetAK8PrunedMass          ; 
    edm::InputTag l_jetAK8TrimmedMass         ; 
    edm::InputTag l_jetAK8Energy              ; 
    edm::InputTag l_jetAK8Flavour             ; 
    edm::InputTag l_jetAK8CSV                 ; 
    edm::InputTag l_jetAK8JEC                 ; 
    edm::InputTag l_jetAK8Area                ; 
    edm::InputTag l_jetAK8Tau1                ;  
    edm::InputTag l_jetAK8Tau2                ;  
    edm::InputTag l_jetAK8Tau3                ;  
    edm::InputTag l_jetAK8nSubJets            ;  
    edm::InputTag l_jetAK8minmass             ;  
    edm::InputTag l_jetAK8VSubjetIndex0       ;  
    edm::InputTag l_jetAK8VSubjetIndex1       ;  
    edm::InputTag l_jetAK8TopSubjetIndex0     ; 
    edm::InputTag l_jetAK8TopSubjetIndex1     ; 
    edm::InputTag l_jetAK8TopSubjetIndex2     ; 
    edm::InputTag l_jetAK8TopSubjetIndex3     ; 
    edm::InputTag l_subjetAK8BDisc            ; 
    edm::InputTag l_subjetAK8Pt               ; 
    edm::InputTag l_subjetAK8Eta              ; 
    edm::InputTag l_subjetAK8Phi              ; 
    edm::InputTag l_subjetAK8Mass             ; 
    edm::InputTag l_subjetCmsTopTagBDisc      ; 
    edm::InputTag l_subjetCmsTopTagPt         ; 
    edm::InputTag l_subjetCmsTopTagEta        ; 
    edm::InputTag l_subjetCmsTopTagPhi        ; 
    edm::InputTag l_subjetCmsTopTagMass       ; 
    edm::InputTag l_jetAK4Pt                  ; 
    edm::InputTag l_jetAK4Eta                 ; 
    edm::InputTag l_jetAK4Phi                 ; 
    edm::InputTag l_jetAK4Mass                ; 
    edm::InputTag l_jetAK4Energy              ; 
    edm::InputTag l_jetAK4Flavour             ; 
    edm::InputTag l_jetAK4CSV                 ; 
    edm::InputTag l_jetAK4JEC                 ; 
    edm::InputTag l_jetAK4nHadEnergy          ;
    edm::InputTag l_jetAK4nEMEnergy           ;
    edm::InputTag l_jetAK4HFHadronEnergy      ;
    edm::InputTag l_jetAK4cHadEnergy          ;
    edm::InputTag l_jetAK4cEMEnergy           ;
    edm::InputTag l_jetAK4numDaughters        ;
    edm::InputTag l_jetAK4cMultip             ;
    edm::InputTag l_jetAK4Y                   ;
    edm::InputTag l_jetAK4Area                ; 
    std::vector<std::string> hltPaths_        ; 
    edm::ParameterSet AK4JetSelParams_        ; 
    edm::ParameterSet BTaggedAK4JetSelParams_ ; 
    edm::ParameterSet AK8JetSelParams_        ; 
    edm::ParameterSet HJetSelParams_          ; 
    edm::ParameterSet WJetSelParams_          ; 
    double ak8jetsPtMin_                      ;
    double ak8jetsEtaMax_                     ; 
    double ak4jetsPtMin_                      ;
    double ak4jetsEtaMax_                     ; 
    double HTMin_                             ; 

    TTree *tree_;

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
VLQAna::VLQAna(const edm::ParameterSet& iConfig) :
  pn_                     (iConfig.getParameter<string>            ("processName")),
  l_trigName              (iConfig.getParameter<edm::InputTag>     ("trigNameLabel")),
  l_trigBit               (iConfig.getParameter<edm::InputTag>     ("trigBitLabel")),
  l_jetAK8Pt              (iConfig.getParameter<edm::InputTag>     ("jetAK8PtLabel")),  
  l_jetAK8Eta             (iConfig.getParameter<edm::InputTag>     ("jetAK8EtaLabel")),  
  l_jetAK8Phi             (iConfig.getParameter<edm::InputTag>     ("jetAK8PhiLabel")),  
  l_jetAK8Mass            (iConfig.getParameter<edm::InputTag>     ("jetAK8MassLabel")),  
  l_jetAK8FilteredMass    (iConfig.getParameter<edm::InputTag>     ("jetAK8FilteredMassLabel")),  
  l_jetAK8PrunedMass      (iConfig.getParameter<edm::InputTag>     ("jetAK8PrunedMassLabel")),  
  l_jetAK8TrimmedMass     (iConfig.getParameter<edm::InputTag>     ("jetAK8TrimmedMassLabel")),  
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
  hltPaths_               (iConfig.getParameter<vector<string>>    ("hltPaths")), 
  AK4JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK4JetSelParams")),
  BTaggedAK4JetSelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedAK4JetSelParams")),
  AK8JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK8JetSelParams")),
  HJetSelParams_          (iConfig.getParameter<edm::ParameterSet>  ("HJetSelParams")),
  WJetSelParams_          (iConfig.getParameter<edm::ParameterSet>  ("WJetSelParams")),
  ak8jetsPtMin_           (iConfig.getParameter<double>            ("ak8jetsPtMin")),
  ak8jetsEtaMax_          (iConfig.getParameter<double>            ("ak8jetsEtaMax")), 
  ak4jetsPtMin_           (iConfig.getParameter<double>            ("ak4jetsPtMin")),
  ak4jetsEtaMax_          (iConfig.getParameter<double>            ("ak4jetsEtaMax")), 
  HTMin_                  (iConfig.getParameter<double>            ("HTMin"))
{
  produces<int>("ngoodAK4Jets");
  produces<int>("ngoodAK8Jets");
  produces<int>("ngoodBTaggedAK4Jets");
  produces<int>("nWJets");
  produces<int>("nHJets");
  produces<double>("htak4jets");
  produces<double>("htak8jets");
  produces<double>("maxetaak4");
  produces<double>("MassLeading2AK8");
  produces<double>("DeltaEtaLeading2AK8");
  produces<double>("pt1stAK8");
  produces<double>("pt2ndAK8");
  produces<double>("mass1stAK8");
  produces<double>("mass2ndAK8");

  edm::Service<TFileService> fs; 
  TFileDirectory results = TFileDirectory( fs->mkdir("results") );
  tree_ = new TTree ("tree", "SingleTpAna");

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


VLQAna::~VLQAna()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
bool
VLQAna::filter(edm::Event& evt, const edm::EventSetup& iSetup)
{
  using namespace edm;

  typedef Handle <vector<string>> hstring ; 
  typedef Handle <vector<float>> hfloat ; 

  Handle <vector<string>> h_trigName             ; evt.getByLabel (l_trigName               , h_trigName             );
  Handle <vector<float>>  h_trigBit              ; evt.getByLabel (l_trigBit                , h_trigBit              ); 
  Handle <vector<float>>  h_jetAK8Pt             ; evt.getByLabel (l_jetAK8Pt               , h_jetAK8Pt             );
  Handle <vector<float>>  h_jetAK8Eta            ; evt.getByLabel (l_jetAK8Eta              , h_jetAK8Eta            );
  Handle <vector<float>>  h_jetAK8Phi            ; evt.getByLabel (l_jetAK8Phi              , h_jetAK8Phi            );
  Handle <vector<float>>  h_jetAK8Mass           ; evt.getByLabel (l_jetAK8Mass             , h_jetAK8Mass           );
  Handle <vector<float>>  h_jetAK8FilteredMass   ; evt.getByLabel (l_jetAK8FilteredMass     , h_jetAK8FilteredMass   );
  Handle <vector<float>>  h_jetAK8PrunedMass     ; evt.getByLabel (l_jetAK8PrunedMass       , h_jetAK8PrunedMass     );
  Handle <vector<float>>  h_jetAK8TrimmedMass    ; evt.getByLabel (l_jetAK8TrimmedMass      , h_jetAK8TrimmedMass    );
  Handle <vector<float>>  h_jetAK8Energy         ; evt.getByLabel (l_jetAK8Energy           , h_jetAK8Energy         );
  Handle <vector<float>>  h_jetAK8Flavour        ; evt.getByLabel (l_jetAK8Flavour          , h_jetAK8Flavour        );
  Handle <vector<float>>  h_jetAK8CSV            ; evt.getByLabel (l_jetAK8CSV              , h_jetAK8CSV            );
  Handle <vector<float>>  h_jetAK8JEC            ; evt.getByLabel (l_jetAK8JEC              , h_jetAK8JEC            );
  Handle <vector<float>>  h_jetAK8Area           ; evt.getByLabel (l_jetAK8Area             , h_jetAK8Area           );
  Handle <vector<float>>  h_jetAK8Tau1           ; evt.getByLabel (l_jetAK8Tau1             , h_jetAK8Tau1           ); 
  Handle <vector<float>>  h_jetAK8Tau2           ; evt.getByLabel (l_jetAK8Tau2             , h_jetAK8Tau2           ); 
  Handle <vector<float>>  h_jetAK8Tau3           ; evt.getByLabel (l_jetAK8Tau3             , h_jetAK8Tau3           ); 
  Handle <vector<float>>  h_jetAK8nSubJets       ; evt.getByLabel (l_jetAK8nSubJets         , h_jetAK8nSubJets       ); 
  Handle <vector<float>>  h_jetAK8minmass        ; evt.getByLabel (l_jetAK8minmass          , h_jetAK8minmass        ); 
  Handle <vector<float>>  h_jetAK8VSubjetIndex0  ; evt.getByLabel (l_jetAK8VSubjetIndex0    , h_jetAK8VSubjetIndex0  );  
  Handle <vector<float>>  h_jetAK8VSubjetIndex1  ; evt.getByLabel (l_jetAK8VSubjetIndex1    , h_jetAK8VSubjetIndex1  );  
  Handle <vector<float>>  h_jetAK8TopSubjetIndex0; evt.getByLabel (l_jetAK8TopSubjetIndex0  , h_jetAK8TopSubjetIndex0); 
  Handle <vector<float>>  h_jetAK8TopSubjetIndex1; evt.getByLabel (l_jetAK8TopSubjetIndex1  , h_jetAK8TopSubjetIndex1); 
  Handle <vector<float>>  h_jetAK8TopSubjetIndex2; evt.getByLabel (l_jetAK8TopSubjetIndex2  , h_jetAK8TopSubjetIndex2); 
  Handle <vector<float>>  h_jetAK8TopSubjetIndex3; evt.getByLabel (l_jetAK8TopSubjetIndex3  , h_jetAK8TopSubjetIndex3); 
  Handle <vector<float>>  h_subjetAK8BDisc       ; evt.getByLabel (l_subjetAK8BDisc         , h_subjetAK8BDisc       ); 
  Handle <vector<float>>  h_subjetAK8Pt          ; evt.getByLabel (l_subjetAK8Pt            , h_subjetAK8Pt          ); 
  Handle <vector<float>>  h_subjetAK8Eta         ; evt.getByLabel (l_subjetAK8Eta           , h_subjetAK8Eta         ); 
  Handle <vector<float>>  h_subjetAK8Phi         ; evt.getByLabel (l_subjetAK8Phi           , h_subjetAK8Phi         ); 
  Handle <vector<float>>  h_subjetAK8Mass        ; evt.getByLabel (l_subjetAK8Mass          , h_subjetAK8Mass        ); 
  Handle <vector<float>>  h_subjetCmsTopTagBDisc ; evt.getByLabel (l_subjetCmsTopTagBDisc   , h_subjetCmsTopTagBDisc ); 
  Handle <vector<float>>  h_subjetCmsTopTagPt    ; evt.getByLabel (l_subjetCmsTopTagPt      , h_subjetCmsTopTagPt    ); 
  Handle <vector<float>>  h_subjetCmsTopTagEta   ; evt.getByLabel (l_subjetCmsTopTagEta     , h_subjetCmsTopTagEta   ); 
  Handle <vector<float>>  h_subjetCmsTopTagPhi   ; evt.getByLabel (l_subjetCmsTopTagPhi     , h_subjetCmsTopTagPhi   ); 
  Handle <vector<float>>  h_subjetCmsTopTagMass  ; evt.getByLabel (l_subjetCmsTopTagMass    , h_subjetCmsTopTagMass  ); 
  Handle <vector<float>>  h_jetAK4Pt             ; evt.getByLabel (l_jetAK4Pt               , h_jetAK4Pt             );
  Handle <vector<float>>  h_jetAK4Eta            ; evt.getByLabel (l_jetAK4Eta              , h_jetAK4Eta            );
  Handle <vector<float>>  h_jetAK4Phi            ; evt.getByLabel (l_jetAK4Phi              , h_jetAK4Phi            );
  Handle <vector<float>>  h_jetAK4Mass           ; evt.getByLabel (l_jetAK4Mass             , h_jetAK4Mass           );
  Handle <vector<float>>  h_jetAK4Energy         ; evt.getByLabel (l_jetAK4Energy           , h_jetAK4Energy         );
  Handle <vector<float>>  h_jetAK4Flavour        ; evt.getByLabel (l_jetAK4Flavour          , h_jetAK4Flavour        );
  Handle <vector<float>>  h_jetAK4CSV            ; evt.getByLabel (l_jetAK4CSV              , h_jetAK4CSV            );
  Handle <vector<float>>  h_jetAK4JEC            ; evt.getByLabel (l_jetAK4JEC              , h_jetAK4JEC            );
  Handle <vector<float>>  h_jetAK4nHadEnergy     ; evt.getByLabel (l_jetAK4nHadEnergy       , h_jetAK4nHadEnergy     );
  Handle <vector<float>>  h_jetAK4nEMEnergy      ; evt.getByLabel (l_jetAK4nEMEnergy        , h_jetAK4nEMEnergy      );
  Handle <vector<float>>  h_jetAK4HFHadronEnergy ; evt.getByLabel (l_jetAK4HFHadronEnergy   , h_jetAK4HFHadronEnergy );
  Handle <vector<float>>  h_jetAK4cHadEnergy     ; evt.getByLabel (l_jetAK4cHadEnergy       , h_jetAK4cHadEnergy     );
  Handle <vector<float>>  h_jetAK4cEMEnergy      ; evt.getByLabel (l_jetAK4cEMEnergy        , h_jetAK4cEMEnergy      );
  Handle <vector<float>>  h_jetAK4numDaughters   ; evt.getByLabel (l_jetAK4numDaughters     , h_jetAK4numDaughters   );
  Handle <vector<float>>  h_jetAK4cMultip        ; evt.getByLabel (l_jetAK4cMultip          , h_jetAK4cMultip        );
  Handle <vector<float>>  h_jetAK4Y              ; evt.getByLabel (l_jetAK4Y                , h_jetAK4Y              );
  Handle <vector<float>>  h_jetAK4Area           ; evt.getByLabel (l_jetAK4Area             , h_jetAK4Area           );

  //// Pre-selection HLT
  unsigned int hltdecisions(0) ; 
  for ( const string& myhltpath : hltPaths_ ) {
    vector<string>::const_iterator it = find( (h_trigName.product())->begin(), (h_trigName.product())->end(), myhltpath) ; 
    if ( it != (h_trigName.product())->end() ) {
      hltdecisions |= int((h_trigBit.product())->at(it - (h_trigName.product())->begin())) << (it - (h_trigName.product())->begin()) ; 
    }
  }
  if (hltdecisions == 0) return false ; 

  JetCollection goodAK8Jets, goodAK4Jets, goodBTaggedAK4Jets ;

  //// Store good AK8 jets
  JetSelector ak8jetsel(AK8JetSelParams_) ;
  pat::strbitset retak8jetsel = ak8jetsel.getBitTemplate() ;
  for ( unsigned ijet = 0; ijet < (h_jetAK8Pt.product())->size(); ++ijet) {
    retak8jetsel.set(false) ;
    if (ak8jetsel(evt, ijet,retak8jetsel) == 0) { 
      LogDebug("VLQAna") << " ak8 jet with pt = " << (h_jetAK8Pt.product())->at(ijet) << " fail jet sel\n" ; 
      continue ;
    }
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
        (h_jetAK8Eta.product())->at(ijet), 
        (h_jetAK8Phi.product())->at(ijet), 
        (h_jetAK8Mass.product())->at(ijet) ) ;
    Jet jet(jetP4) ;
    goodAK8Jets.push_back(jet) ;
  }

  //// Pre-selection ak8 jets 
  if (goodAK8Jets.size() < 1) return false; 

  //// Store good AK4 jets 
  JetSelector ak4jetsel(AK4JetSelParams_) ;
  JetSelector btaggedak4jetsel(BTaggedAK4JetSelParams_) ;
  pat::strbitset retak4jetsel = ak4jetsel.getBitTemplate() ;
  pat::strbitset retbtaggedak4jetsel = btaggedak4jetsel.getBitTemplate() ;
  for ( unsigned ijet = 0; ijet < (h_jetAK4Pt.product())->size(); ++ijet) {
    retak4jetsel.set(false) ;
    retbtaggedak4jetsel.set(false) ;
    if (ak4jetsel(evt, ijet,retak4jetsel) == 0) { 
      LogDebug("VLQAna") << " ak4 jet with pt = " << (h_jetAK4Pt.product())->at(ijet) << " fail jet sel\n" ; 
      continue ;
    }
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
        (h_jetAK4Eta.product())->at(ijet), 
        (h_jetAK4Phi.product())->at(ijet), 
        (h_jetAK4Mass.product())->at(ijet) ) ;
    Jet jet(jetP4) ;
    goodAK4Jets.push_back(jet) ;
    if ( btaggedak4jetsel(evt, ijet,retbtaggedak4jetsel) != 0 ) goodBTaggedAK4Jets.push_back(jet) ; 
  }

  //// Pre-selection ak4 jets 
  if (goodAK4Jets.size() < 1 ) return false; 

  HT htak4(goodAK4Jets) ; 

  //// Pre-selection HT
  if ( htak4.getHT() < HTMin_ ) return false; 

  HT htak8(goodAK8Jets) ; 

  //// Make W and H jets 
  JetCollection wjets, hjets ; 
  JetSelector wjetsel(WJetSelParams_) ;
  JetSelector hjetsel(HJetSelParams_) ;
  pat::strbitset retwjetsel = wjetsel.getBitTemplate() ;
  pat::strbitset rethjetsel = hjetsel.getBitTemplate() ;
  for ( unsigned ijet = 0; ijet < (h_jetAK8Pt.product())->size(); ++ijet) {
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
        (h_jetAK4Eta.product())->at(ijet), 
        (h_jetAK4Phi.product())->at(ijet), 
        (h_jetAK4Mass.product())->at(ijet) ) ;
    Jet jet(jetP4) ;
    retwjetsel.set(false) ;
    if (wjetsel(evt, ijet,retwjetsel) == true ) wjets.push_back(jet) ; 
    rethjetsel.set(false) ;
    if (hjetsel(evt, ijet,rethjetsel) == true ) hjets.push_back(jet) ; 
  }

  //// Pick forwardmost AK4 jet
  double maxeta(0) ;
  for ( auto& jet : goodAK4Jets ) {
    if ( abs(jet.p4().Eta()) > abs(maxeta) ) maxeta = jet.p4().Eta() ; 
  }

  double ptak8_1 = goodAK8Jets.at(0).p4().Pt() ;
  double ptak8_2(0) ; 
  goodAK8Jets.size() > 1 ?  ptak8_2 = goodAK8Jets.at(1).p4().Pt() : 0 ; 
  double mak8_1 = goodAK8Jets.at(0).p4().Mag() ;
  double mak8_2(0) ; 
  goodAK8Jets.size() > 1 ?  mak8_2 = goodAK8Jets.at(1).p4().Mag() : 0 ; 
  double mak8_12(0) ; 
  double detaLeading2AK8(-1) ; 
  if (goodAK8Jets.size() > 1) {
    TLorentzVector p4_ak8_12(goodAK8Jets.at(0).p4() + goodAK8Jets.at(1).p4()) ;
    mak8_12 = p4_ak8_12.Mag() ; 
    detaLeading2AK8 = abs(goodAK8Jets.at(0).p4().Eta() - goodAK8Jets.at(1).p4().Eta() ) ;
  }

  std::auto_ptr<int> ngoodAK4Jets ( new int(goodAK4Jets.size()) );
  std::auto_ptr<int> ngoodAK8Jets ( new int(goodAK8Jets.size()) );
  std::auto_ptr<int> nWJets ( new int(wjets.size()) );
  std::auto_ptr<int> nHJets ( new int(hjets.size()) );
  std::auto_ptr<int> ngoodBTaggedAK4Jets ( new int(goodBTaggedAK4Jets.size()) );
  std::auto_ptr<double> htak4jets ( new double(htak4.getHT()) );
  std::auto_ptr<double> htak8jets ( new double(htak8.getHT()) );
  std::auto_ptr<double> maxetaak4 ( new double(maxeta) );
  std::auto_ptr<double> MassLeading2AK8 ( new double(mak8_12) );
  std::auto_ptr<double> DeltaEtaLeading2AK8 ( new double(detaLeading2AK8) );
  std::auto_ptr<double> pt1stAK8   ( new double(ptak8_1) );
  std::auto_ptr<double> pt2ndAK8   ( new double(ptak8_2) );
  std::auto_ptr<double> mass1stAK8 ( new double(mak8_1) );
  std::auto_ptr<double> mass2ndAK8 ( new double(mak8_2) );

  evt.put(ngoodAK4Jets, "ngoodAK4Jets") ; 
  evt.put(ngoodAK8Jets, "ngoodAK8Jets") ; 
  evt.put(nWJets, "nWJets") ; 
  evt.put(nHJets, "nHJets") ; 
  evt.put(ngoodBTaggedAK4Jets, "ngoodBTaggedAK4Jets") ; 
  evt.put(htak4jets, "htak4jets") ; 
  evt.put(htak8jets, "htak8jets") ; 
  evt.put(maxetaak4, "maxetaak4") ; 
  evt.put(MassLeading2AK8, "MassLeading2AK8") ; 
  evt.put(DeltaEtaLeading2AK8, "DeltaEtaLeading2AK8") ; 
  evt.put(pt1stAK8  , "pt1stAK8") ; 
  evt.put(pt2ndAK8  , "pt2ndAK8") ; 
  evt.put(mass1stAK8, "mass1stAK8") ; 
  evt.put(mass2ndAK8, "mass2ndAK8") ; 

  return true ; 

  /* This is an event example
  //Read 'ExampleData' from the Event
  Handle<ExampleData> pIn;
  evt.getByLabel("example",pIn);

  //Use the ExampleData to create an ExampleData2 which 
  // is put into the Event
  std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
  evt.put(std::move(pOut));
  */

  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
  */

}

// ------------ method called once each job just before starting event loop  ------------
  void 
VLQAna::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VLQAna::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
   void
   VLQAna::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void
   VLQAna::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void
   VLQAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void
   VLQAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
VLQAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(VLQAna);
