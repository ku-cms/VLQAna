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

#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "Analysis/VLQAna/interface/JetSelector.h"
#include "Analysis/VLQAna/interface/HT.h"

#include <TTree.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>


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
    edm::InputTag l_HbbCands                  ; 
    std::vector<std::string> hltPaths_        ; 
    edm::ParameterSet GenHSelParams_          ; 
    edm::ParameterSet AK4JetSelParams_        ; 
    edm::ParameterSet BTaggedAK4JetSelParams_ ; 
    edm::ParameterSet AK8JetSelParams_        ; 
    edm::ParameterSet TJetSelParams_          ; 
    edm::ParameterSet HJetSelParams_          ; 
    edm::ParameterSet WJetSelParams_          ; 
    double ak8jetsPtMin_                      ;
    double ak8jetsEtaMax_                     ; 
    double ak4jetsPtMin_                      ;
    double ak4jetsEtaMax_                     ; 
    double HTMin_                             ; 

    edm::Service<TFileService> fs             ; 
    std::map<std::string, TH1D*> h1_          ; 

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
  l_HbbCands              (iConfig.getParameter<edm::InputTag>     ("HbbCandsLabel")),
  hltPaths_               (iConfig.getParameter<vector<string>>    ("hltPaths")), 
  GenHSelParams_          (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
  AK4JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK4JetSelParams")),
  BTaggedAK4JetSelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedAK4JetSelParams")),
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
  produces<unsigned>("ngoodBTaggedAK4Jets");
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

  hstring h_trigName             ; evt.getByLabel (l_trigName               , h_trigName             );
  hfloat  h_trigBit              ; evt.getByLabel (l_trigBit                , h_trigBit              ); 
  hfloat  h_jetAK8Pt             ; evt.getByLabel (l_jetAK8Pt               , h_jetAK8Pt             );
  hfloat  h_jetAK8Eta            ; evt.getByLabel (l_jetAK8Eta              , h_jetAK8Eta            );
  hfloat  h_jetAK8Phi            ; evt.getByLabel (l_jetAK8Phi              , h_jetAK8Phi            );
  hfloat  h_jetAK8Mass           ; evt.getByLabel (l_jetAK8Mass             , h_jetAK8Mass           );
  hfloat  h_jetAK8FilteredMass   ; evt.getByLabel (l_jetAK8FilteredMass     , h_jetAK8FilteredMass   );
  hfloat  h_jetAK8PrunedMass     ; evt.getByLabel (l_jetAK8PrunedMass       , h_jetAK8PrunedMass     );
  hfloat  h_jetAK8TrimmedMass    ; evt.getByLabel (l_jetAK8TrimmedMass      , h_jetAK8TrimmedMass    );
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

  Handle<vlq::GenParticleWithDaughtersCollection> h_HbbCands ; evt.getByLabel (l_HbbCands , h_HbbCands );
  vlq::GenParticleWithDaughtersCollection::const_iterator ihbb ;

  //// Pre-selection HLT
  // Get all trig names
  //for ( vector<string>::const_iterator it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it) {
  //  cout << *it << endl ; 
  //}
  unsigned int hltdecisions(0) ; 
  for ( const string& myhltpath : hltPaths_ ) {
    vector<string>::const_iterator it = find( (h_trigName.product())->begin(), (h_trigName.product())->end(), myhltpath) ; 
    if ( it != (h_trigName.product())->end() ) {
      hltdecisions |= int((h_trigBit.product())->at(it - (h_trigName.product())->begin())) << (it - (h_trigName.product())->begin()) ; 
    }
  }
  //DMif (hltdecisions == 0) return false ; 

  vlq::JetCollection goodAK8Jets, goodAK4Jets, goodBTaggedAK4Jets ;
  vector<unsigned> ak4seljets, ak8seljets, bjetIdxs;

  //// Store good AK8 jets
  JetSelector ak8jetsel(AK8JetSelParams_) ;
  for ( unsigned ijet = 0; ijet < (h_jetAK8Pt.product())->size(); ++ijet) {
    bool retak8jetsel = false ; 
    if (ak8jetsel(evt, ijet,retak8jetsel) == 0) { 
      LogDebug("VLQAna") << " ak8 jet with pt = " << (h_jetAK8Pt.product())->at(ijet) << " fail jet sel\n" ; 
      continue ;
    }
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK8Pt.product())->at(ijet), 
        (h_jetAK8Eta.product())->at(ijet), 
        (h_jetAK8Phi.product())->at(ijet), 
        (h_jetAK8Mass.product())->at(ijet) ) ;
    vlq::Jet jet;
    jet.setP4(jetP4) ; 
    goodAK8Jets.push_back(jet) ;
    ak8seljets.push_back(ijet);
  }

  //// Pre-selection ak8 jets 
  if (goodAK8Jets.size() < 1) return false; 

  //// Store good AK4 jets 
  JetSelector ak4jetsel(AK4JetSelParams_) ;
  JetSelector btaggedak4jetsel(BTaggedAK4JetSelParams_) ;
  bool retak4jetsel = false ; 
  bool retbtaggedak4jetsel = false ; 
  for ( unsigned ijet = 0; ijet < (h_jetAK4Pt.product())->size(); ++ijet) {
    retak4jetsel = false ;
    retbtaggedak4jetsel = false ;
    if (ak4jetsel(evt, ijet,retak4jetsel) == 0) { 
      LogDebug("VLQAna") << " ak4 jet with pt = " << (h_jetAK4Pt.product())->at(ijet) << " fail jet sel\n" ; 
      continue ;
    }
    TLorentzVector jetP4 ;
    jetP4.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
        (h_jetAK4Eta.product())->at(ijet), 
        (h_jetAK4Phi.product())->at(ijet), 
        (h_jetAK4Mass.product())->at(ijet) ) ;
    vlq::Jet jet;  
    jet.setP4(jetP4) ;
    goodAK4Jets.push_back(jet) ;
    ak4seljets.push_back(ijet);
    if ( btaggedak4jetsel(evt, ijet,retbtaggedak4jetsel) != 0 ) {
      bjetIdxs.push_back(ijet) ; 
      goodBTaggedAK4Jets.push_back(jet) ; 
    }
  }

  //// Pre-selection ak4 jets 
  if (goodAK4Jets.size() < 1 ) return false; 

  HT htak4(goodAK4Jets) ; 

  //// Pre-selection HT
  //DMif ( htak4.getHT() < HTMin_ ) return false; 

  HT htak8(goodAK8Jets) ; 

  //// Make W, top and H jets 
  vector<unsigned> seltjets, selhjets, selwjets;
  vlq::JetCollection tjets, hjets, wjets ; 
  JetSelector tjetsel(TJetSelParams_) ;
  JetSelector hjetsel(HJetSelParams_) ;
  JetSelector wjetsel(WJetSelParams_) ;
  bool rettjetsel = false ;
  bool rethjetsel = false ;
  bool retwjetsel = false ;
  for ( unsigned  &ijet :  ak8seljets) {
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
    rettjetsel = false ;
    if (tjetsel(evt, ijet,rettjetsel) == true ) { tjets.push_back(jet) ; seltjets.push_back(ijet) ; }
    rethjetsel = false ;
    if (hjetsel(evt, ijet,rethjetsel) == true ) { 
      hjets.push_back(jet) ; 
      selhjets.push_back(ijet) ; 
      if ( iminh != drhjet_hpart.end() && iminb != drhjet_bpart.end() && iminbbar != drhjet_bbarpart.end() )
        if ( *iminh < 0.8  && *iminb < 0.8 && *iminbbar < 0.8 ) 
      h1_["pthjet"]->Fill(jetP4.Pt()) ;
    } 
    retwjetsel = false ;
    if (wjetsel(evt, ijet,retwjetsel) == true ) { wjets.push_back(jet) ; selwjets.push_back(ijet) ; } 
  }

  //// Pick forwardmost AK4 jet
  double maxeta(0) ;
  for ( auto& jet : goodAK4Jets ) {
    if ( abs(jet.getP4().Eta()) > abs(maxeta) ) maxeta = jet.getP4().Eta() ; 
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
    detaLeading2AK8 = abs(goodAK8Jets.at(0).getP4().Eta() - goodAK8Jets.at(1).getP4().Eta() ) ;
  }

  std::auto_ptr<unsigned> ngoodAK4Jets ( new unsigned(goodAK4Jets.size()) );
  std::auto_ptr<unsigned> ngoodAK8Jets ( new unsigned(goodAK8Jets.size()) );
  std::auto_ptr<unsigned> nTJets ( new unsigned(tjets.size()) );
  std::auto_ptr<unsigned> nHJets ( new unsigned(hjets.size()) );
  std::auto_ptr<unsigned> nWJets ( new unsigned(wjets.size()) );
  std::auto_ptr<unsigned> ngoodBTaggedAK4Jets ( new unsigned(goodBTaggedAK4Jets.size()) );
  std::auto_ptr<double> htak4jets ( new double(htak4.getHT()) );
  std::auto_ptr<double> htak8jets ( new double(htak8.getHT()) );
  std::auto_ptr<double> maxetaak4 ( new double(maxeta) );
  std::auto_ptr<double> MassLeading2AK8 ( new double(mak8_12) );
  std::auto_ptr<double> DeltaEtaLeading2AK8 ( new double(detaLeading2AK8) );
  std::auto_ptr<double> pt1stAK8   ( new double(ptak8_1) );
  std::auto_ptr<double> pt2ndAK8   ( new double(ptak8_2) );
  std::auto_ptr<double> mass1stAK8 ( new double(mak8_1) );
  std::auto_ptr<double> mass2ndAK8 ( new double(mak8_2) );
  std::auto_ptr<vector<unsigned> > ak4goodjets ( new vector<unsigned>(ak4seljets));
  std::auto_ptr<vector<unsigned> > ak8goodjets ( new vector<unsigned>(ak8seljets));
  std::auto_ptr<vector<unsigned> > bjetIdxsptr ( new vector<unsigned>(bjetIdxs));
  std::auto_ptr<vector<unsigned> > tjetIdxs ( new vector<unsigned>(seltjets));
  std::auto_ptr<vector<unsigned> > hjetIdxs ( new vector<unsigned>(selhjets));
  std::auto_ptr<vector<unsigned> > wjetIdxs ( new vector<unsigned>(selwjets));

  evt.put(ngoodAK4Jets, "ngoodAK4Jets") ; 
  evt.put(ngoodAK8Jets, "ngoodAK8Jets") ; 
  evt.put(nTJets, "nTJets") ; 
  evt.put(nHJets, "nHJets") ; 
  evt.put(nWJets, "nWJets") ; 
  evt.put(ngoodBTaggedAK4Jets, "ngoodBTaggedAK4Jets") ; 
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
  void 
VLQAna::beginJob()
{
  TFileDirectory results = TFileDirectory( fs->mkdir("results") );
  h1_["ptak8"]  = fs->make<TH1D>("ptak8"  ,";p_T{AK8} [GeV]"         , 100, 0., 2000.) ; 
  h1_["pthjet"] = fs->make<TH1D>("pthjet" ,";p_T{H-tagged jet} [GeV]", 100, 0., 2000.) ; 

}

// ------------ method called once each job just after ending the event loop  ------------
void 
VLQAna::endJob() {
  TGraphAsymmErrors* greff = fs->make<TGraphAsymmErrors>(h1_["pthjet"], h1_["ptak8"], "cp") ; 
  greff->SetName("effhtag") ;
  greff->Write() ;
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
