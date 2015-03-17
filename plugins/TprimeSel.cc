// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      TprimeSel
// 
/**\class TprimeSel TprimeSel.cc Analysis/VLQAna/plugins/TprimeSel.cc

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

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"

#include <TTree.h>
#include <TLorentzVector.h>

//
// class declaration
//

class TprimeSel : public edm::EDFilter {
  public:
    explicit TprimeSel(const edm::ParameterSet&);
    ~TprimeSel();

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
    edm::InputTag l_jetcoll;
    edm::InputTag l_resolvedvjjcoll; 
    edm::InputTag l_ngoodAK4Jets;
    edm::InputTag l_ngoodAK8Jets;
    edm::InputTag l_ngoodBTaggedAK4Jets;
    edm::InputTag l_nTJets;
    edm::InputTag l_nHJets;
    edm::InputTag l_nWJets;
    edm::InputTag l_htak4jets;
    edm::InputTag l_htak8jets;
    edm::InputTag l_maxetaak4;
    edm::InputTag l_MassLeading2AK8;
    edm::InputTag l_DeltaEtaLeading2AK8;
    edm::InputTag l_pt1stAK8;
    edm::InputTag l_pt2ndAK8;
    edm::InputTag l_mass1stAK8;
    edm::InputTag l_mass2ndAK8;
    edm::InputTag l_ak4goodjets;
    edm::InputTag l_ak8goodjets;
    edm::InputTag l_tjetIdxs;
    edm::InputTag l_hjetIdxs;
    edm::InputTag l_wjetIdxs;
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
    double wmassmin_                          ;
    double wmassmax_                          ;
    double scaledmassdropmin_                 ;
    double scaledmassdropmax_                 ;

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
TprimeSel::TprimeSel(const edm::ParameterSet& iConfig) :
  l_jetcoll               (iConfig.getParameter<edm::InputTag>     ("jetcoll")),
  l_resolvedvjjcoll       (iConfig.getParameter<edm::InputTag>     ("resolvedvjjcoll")),
  l_ngoodAK4Jets          (iConfig.getParameter<edm::InputTag>     ("ngoodAK4Jets")),
  l_ngoodAK8Jets          (iConfig.getParameter<edm::InputTag>     ("ngoodAK8Jets")),
  l_ngoodBTaggedAK4Jets   (iConfig.getParameter<edm::InputTag>     ("ngoodBTaggedAK4Jets")),
  l_nTJets                (iConfig.getParameter<edm::InputTag>     ("nTJets")),
  l_nHJets                (iConfig.getParameter<edm::InputTag>     ("nHJets")),
  l_nWJets                (iConfig.getParameter<edm::InputTag>     ("nWJets")),
  l_htak4jets             (iConfig.getParameter<edm::InputTag>     ("htak4jets")),
  l_htak8jets             (iConfig.getParameter<edm::InputTag>     ("htak8jets")),
  l_maxetaak4             (iConfig.getParameter<edm::InputTag>     ("maxetaak4")),
  l_MassLeading2AK8       (iConfig.getParameter<edm::InputTag>     ("MassLeading2AK8")),
  l_DeltaEtaLeading2AK8   (iConfig.getParameter<edm::InputTag>     ("DeltaEtaLeading2AK8")),
  l_pt1stAK8              (iConfig.getParameter<edm::InputTag>     ("pt1stAK8")),
  l_pt2ndAK8              (iConfig.getParameter<edm::InputTag>     ("pt2ndAK8")),
  l_mass1stAK8            (iConfig.getParameter<edm::InputTag>     ("mass1stAK8")),
  l_mass2ndAK8            (iConfig.getParameter<edm::InputTag>     ("mass2ndAK8")),
  l_ak4goodjets           (iConfig.getParameter<edm::InputTag>     ("ak4goodjets")),
  l_ak8goodjets           (iConfig.getParameter<edm::InputTag>     ("ak8goodjets")),
  l_tjetIdxs              (iConfig.getParameter<edm::InputTag>     ("tjetIdxs")),
  l_hjetIdxs              (iConfig.getParameter<edm::InputTag>     ("hjetIdxs")),
  l_wjetIdxs              (iConfig.getParameter<edm::InputTag>     ("wjetIdxs")),
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
  AK4JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK4JetSelParams")),
  BTaggedAK4JetSelParams_ (iConfig.getParameter<edm::ParameterSet> ("BTaggedAK4JetSelParams")),
  AK8JetSelParams_        (iConfig.getParameter<edm::ParameterSet> ("AK8JetSelParams")),
  TJetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("TJetSelParams")),
  HJetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("HJetSelParams")),
  WJetSelParams_          (iConfig.getParameter<edm::ParameterSet> ("WJetSelParams")),
  ak8jetsPtMin_           (iConfig.getParameter<double>            ("ak8jetsPtMin")),
  ak8jetsEtaMax_          (iConfig.getParameter<double>            ("ak8jetsEtaMax")), 
  ak4jetsPtMin_           (iConfig.getParameter<double>            ("ak4jetsPtMin")),
  ak4jetsEtaMax_          (iConfig.getParameter<double>            ("ak4jetsEtaMax")), 
  HTMin_                  (iConfig.getParameter<double>            ("HTMin")), 
  wmassmin_               (iConfig.getParameter<double>            ("wmassmin")), 
  wmassmax_               (iConfig.getParameter<double>            ("wmassmax")), 
  scaledmassdropmin_      (iConfig.getParameter<double>            ("scaledmassdropmin")), 
  scaledmassdropmax_      (iConfig.getParameter<double>            ("scaledmassdropmax"))
{

  produces<string>("evttype") ; 
  produces<map<int, int>>("resolvedvs") ; 
  produces<vector<vlq::Jet>>("JetCollection") ; 
  produces<vector<vlq::ResolvedVjj>>("ResolvedVjjCollection") ; 

  edm::Service<TFileService> fs; 
  TFileDirectory results = TFileDirectory( fs->mkdir("results") );
  tree_ = new TTree ("tree", "SingleTpAna");

}


TprimeSel::~TprimeSel()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
  bool
TprimeSel::filter(edm::Event& evt, const edm::EventSetup& iSetup)
{
  using namespace edm;

  typedef Handle<int> hint ; 
  typedef Handle <vector<string>> hstring ; 
  typedef Handle <vector<float>> hfloat ; 
  typedef Handle <vector<unsigned>> hunsigned ; 

  Handle<vector<vlq::Jet>> h_jetcoll  ; evt.getByLabel (l_jetcoll      , h_jetcoll) ;
  Handle<vector<vlq::ResolvedVjj>> h_resolvedvjjcoll ; evt.getByLabel(l_resolvedvjjcoll, h_resolvedvjjcoll) ; 

  hint      h_ngoodAK4Jets       ; evt.getByLabel (l_ngoodAK4Jets , h_ngoodAK4Jets) ;
  hint      h_ngoodAK8Jets       ; evt.getByLabel (l_ngoodAK8Jets , h_ngoodAK8Jets) ;
  hint      h_ngoodBTaggedAK4Jets; evt.getByLabel (l_ngoodBTaggedAK4Jets , h_ngoodBTaggedAK4Jets) ;
  hint      h_nTJets             ; evt.getByLabel (l_nTJets , h_nTJets) ;
  hint      h_nHJets             ; evt.getByLabel (l_nHJets , h_nHJets) ;
  hint      h_nWJets             ; evt.getByLabel (l_nWJets , h_nWJets) ;
  hfloat    h_htak4jets          ; evt.getByLabel (l_htak4jets , h_htak4jets) ;
  hfloat    h_htak8jets          ; evt.getByLabel (l_htak8jets , h_htak8jets) ;
  hfloat    h_maxetaak4          ; evt.getByLabel (l_maxetaak4 , h_maxetaak4) ;
  hfloat    h_MassLeading2AK8    ; evt.getByLabel (l_MassLeading2AK8 , h_MassLeading2AK8) ;
  hfloat    h_DeltaEtaLeading2AK8; evt.getByLabel (l_DeltaEtaLeading2AK8 , h_DeltaEtaLeading2AK8) ;
  hfloat    h_pt1stAK8           ; evt.getByLabel (l_pt1stAK8 , h_pt1stAK8) ;
  hfloat    h_pt2ndAK8           ; evt.getByLabel (l_pt2ndAK8 , h_pt2ndAK8) ;
  hfloat    h_mass1stAK8         ; evt.getByLabel (l_mass1stAK8 , h_mass1stAK8) ;
  hfloat    h_mass2ndAK8         ; evt.getByLabel (l_mass2ndAK8 , h_mass2ndAK8) ;
  hunsigned h_ak4goodjets        ; evt.getByLabel (l_ak4goodjets , h_ak4goodjets) ;
  hunsigned h_ak8goodjets        ; evt.getByLabel (l_ak8goodjets , h_ak8goodjets) ;
  hunsigned h_tjetIdxs           ; evt.getByLabel (l_tjetIdxs , h_tjetIdxs) ;
  hunsigned h_hjetIdxs           ; evt.getByLabel (l_hjetIdxs , h_hjetIdxs) ;
  hunsigned h_wjetIdxs           ; evt.getByLabel (l_wjetIdxs , h_wjetIdxs) ;

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

  cout << " jetcoll size = " << h_jetcoll.product()->size() 
    << " resolved vjj size = " << h_resolvedvjjcoll.product()->size() 
    << endl ; 
  int nbjets = *h_ngoodBTaggedAK4Jets.product() ; 
  int ntjets = *h_nTJets.product() ; 
  int nhjets = *h_nHJets.product() ; 
  int nwjets = *h_nWJets.product() ; 

  map<int, int>resolvedvs ; 
  vector<vlq::Jet> v_jetsfromv; ; 
  vector<vlq::ResolvedVjj> v_vjj ; 
  vector<unsigned>ak4idx = *h_ak4goodjets.product() ; 
  for ( unsigned ij = 0; ij < ak4idx.size(); ++ij ) {
    for ( unsigned jj = ij+1; jj < ak4idx.size(); ++jj) {
      TLorentzVector p4j1, p4j2 ; 
      p4j1.SetPtEtaPhiM(h_jetAK4Pt.product()->at(ij), h_jetAK4Eta.product()->at(ij), h_jetAK4Phi.product()->at(ij), h_jetAK4Mass.product()->at(ij)) ; 
      p4j2.SetPtEtaPhiM(h_jetAK4Pt.product()->at(jj), h_jetAK4Eta.product()->at(jj), h_jetAK4Phi.product()->at(jj), h_jetAK4Mass.product()->at(jj)) ; 

      //// Make V candidates 
      std::pair <int, int> jetIndices(ij, jj) ;
      TLorentzVector p4v = p4j1 + p4j2 ; 
      double scaledmassdrop = (max(p4j1.Mag(), p4j2.Mag())/p4v.Mag()) * p4j1.DeltaR(p4j2) ; 
      if ( (p4v).Mag() > wmassmin_ && (p4v).Mag() < wmassmax_ 
          && scaledmassdrop > scaledmassdropmin_ && scaledmassdrop < scaledmassdropmax_ 
          && p4j1.DeltaR(p4j2) < 1.2 ) { 
        resolvedvs.insert( jetIndices ) ; 
        vlq::ResolvedVjj vjj ;
        vjj.setP4( p4v ) ; 
        vjj.setScaledMassDrop( scaledmassdrop ) ;
        vjj.setDrjj( p4j1.DeltaR(p4j2) ) ; 
        vjj.setJetIndices( jetIndices ) ; 
        v_vjj.push_back(vjj) ; 
        vlq::Jet j1 ; 
        vlq::Jet j2;
        j1.setP4(p4j1) ;
        j2.setP4(p4j2) ; 
        j1.setIndex(ij) ;
        j2.setIndex(jj) ;
        v_jetsfromv.push_back(j1) ;
        v_jetsfromv.push_back(j2) ;
      }

    }
  }

  string evttype = "" ; 

  if ( nbjets > 0 ) { 
    if ( ntjets > 0  && nhjets > 0 ) { //// --> type 1 
      evttype = "TYPE1" ; 
    } 
    else if ( ntjets == 0 && nhjets > 0 && nwjets > 0 ) { //// --> type 2
      evttype = "TYPE2" ; 
    } 
    else if ( ntjets == 0 && nhjets > 0 && nwjets == 0 ) { //// --> type 3
      evttype = "TYPE3" ; 
    }
    else if ( nhjets == 0 && nwjets > 0 && nbjets > 1 ) { //// --> type 4 
      evttype = "TYPE4" ; 
    }
  }
  else { //// Define control
  }

  std::auto_ptr<string> evttypeptr( new string(evttype) ) ;
  std::auto_ptr<map<int,int>> resolvedvsptr ( new map<int,int>(resolvedvs) ) ;
  auto_ptr<vector<vlq::ResolvedVjj> > vjjcoll( new vector<vlq::ResolvedVjj> (v_vjj) );
  auto_ptr<vector<vlq::Jet> > jetcoll( new vector<vlq::Jet> (v_jetsfromv) );
  evt.put(evttypeptr, "evttype") ; 
  evt.put(resolvedvsptr, "resolvedvs") ; 
  evt.put(jetcoll, "JetCollection") ; 
  evt.put(vjjcoll, "ResolvedVjjCollection") ; 

  return true ; 

}

// ------------ method called once each job just before starting event loop  ------------
  void 
TprimeSel::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TprimeSel::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
   void
   TprimeSel::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void
   TprimeSel::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void
   TprimeSel::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void
   TprimeSel::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TprimeSel::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TprimeSel);
