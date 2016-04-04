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

#include "Analysis/VLQAna/interface/JetMaker.h"
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
    edm::InputTag l_jetcoll                   ;
    edm::InputTag l_resolvedvjjcoll           ; 
    edm::InputTag l_ngoodAK4Jets              ;
    edm::InputTag l_ngoodAK8Jets              ;
    edm::InputTag l_ngoodBTaggedAK4Jets       ;
    edm::InputTag l_nTJets                    ;
    edm::InputTag l_nHJets                    ;
    edm::InputTag l_nWJets                    ;
    edm::InputTag l_htak4jets                 ;
    edm::InputTag l_htak8jets                 ;
    edm::InputTag l_maxetaak4                 ;
    edm::InputTag l_MassLeading2AK8           ;
    edm::InputTag l_DeltaEtaLeading2AK8       ;
    edm::InputTag l_pt1stAK8                  ;
    edm::InputTag l_pt2ndAK8                  ;
    edm::InputTag l_mass1stAK8                ;
    edm::InputTag l_mass2ndAK8                ;
    edm::InputTag l_ak4goodjets               ;
    edm::InputTag l_ak8goodjets               ;
    edm::InputTag l_bjetIdxs                  ;
    edm::InputTag l_tjetIdxs                  ;
    edm::InputTag l_hjetIdxs                  ;
    edm::InputTag l_wjetIdxs                  ;
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
  l_bjetIdxs              (iConfig.getParameter<edm::InputTag>     ("bjetIdxs")),
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

  produces<int>("evttype") ; 
  produces<double>("pttjet") ; 
  produces<double>("mtjet") ;
  produces<double>("ptwjet") ;
  produces<double>("mwjet") ;
  produces<double>("pthjet") ;
  produces<double>("mhjet") ;
  produces<double>("ptth") ;
  produces<double>("mth") ;
  produces<double>("ptbleading") ;
  produces<double>("etableading") ;
  produces<double>("ptjforward") ;
  produces<double>("etajforward") ;
  produces<double>("nak4") ;
  produces<double>("nak8") ; 
  produces<double>("nbj") ; 
  produces<double>("detath") ; 
  produces<double>("detawh") ; 
  produces<double>("drwb") ; 
  produces<double>("mwhb") ; 

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

  typedef Handle<unsigned> hunsigned ; 
  typedef Handle <vector<string>> hvstring ; 
  typedef Handle <vector<float>> hvfloat ; 
  typedef Handle <vector<unsigned>> hvunsigned ; 

  Handle<vector<vlq::Jet>> h_jetcoll  ; evt.getByLabel (l_jetcoll      , h_jetcoll) ;
  Handle<vector<vlq::ResolvedVjj>> h_resolvedvjjcoll ; evt.getByLabel(l_resolvedvjjcoll, h_resolvedvjjcoll) ; 

  hunsigned  h_ngoodAK4Jets       ; evt.getByLabel (l_ngoodAK4Jets , h_ngoodAK4Jets) ;
  hunsigned  h_ngoodAK8Jets       ; evt.getByLabel (l_ngoodAK8Jets , h_ngoodAK8Jets) ;
  hunsigned  h_ngoodBTaggedAK4Jets; evt.getByLabel (l_ngoodBTaggedAK4Jets , h_ngoodBTaggedAK4Jets) ;
  hunsigned  h_nTJets             ; evt.getByLabel (l_nTJets , h_nTJets) ;
  hunsigned  h_nHJets             ; evt.getByLabel (l_nHJets , h_nHJets) ;
  hunsigned  h_nWJets             ; evt.getByLabel (l_nWJets , h_nWJets) ;
  hvfloat    h_htak4jets          ; evt.getByLabel (l_htak4jets , h_htak4jets) ;
  hvfloat    h_htak8jets          ; evt.getByLabel (l_htak8jets , h_htak8jets) ;
  hvfloat    h_maxetaak4          ; evt.getByLabel (l_maxetaak4 , h_maxetaak4) ;
  hvfloat    h_MassLeading2AK8    ; evt.getByLabel (l_MassLeading2AK8 , h_MassLeading2AK8) ;
  hvfloat    h_DeltaEtaLeading2AK8; evt.getByLabel (l_DeltaEtaLeading2AK8 , h_DeltaEtaLeading2AK8) ;
  hvfloat    h_pt1stAK8           ; evt.getByLabel (l_pt1stAK8 , h_pt1stAK8) ;
  hvfloat    h_pt2ndAK8           ; evt.getByLabel (l_pt2ndAK8 , h_pt2ndAK8) ;
  hvfloat    h_mass1stAK8         ; evt.getByLabel (l_mass1stAK8 , h_mass1stAK8) ;
  hvfloat    h_mass2ndAK8         ; evt.getByLabel (l_mass2ndAK8 , h_mass2ndAK8) ;
  hvunsigned h_ak4goodjets        ; evt.getByLabel (l_ak4goodjets , h_ak4goodjets) ;
  hvunsigned h_ak8goodjets        ; evt.getByLabel (l_ak8goodjets , h_ak8goodjets) ;
  hvunsigned h_bjetIdxs           ; evt.getByLabel (l_bjetIdxs , h_bjetIdxs) ;
  hvunsigned h_tjetIdxs           ; evt.getByLabel (l_tjetIdxs , h_tjetIdxs) ;
  hvunsigned h_hjetIdxs           ; evt.getByLabel (l_hjetIdxs , h_hjetIdxs) ;
  hvunsigned h_wjetIdxs           ; evt.getByLabel (l_wjetIdxs , h_wjetIdxs) ;

  hvfloat  h_jetAK8Pt             ; evt.getByLabel (l_jetAK8Pt               , h_jetAK8Pt             );
  hvfloat  h_jetAK8Eta            ; evt.getByLabel (l_jetAK8Eta              , h_jetAK8Eta            );
  hvfloat  h_jetAK8Phi            ; evt.getByLabel (l_jetAK8Phi              , h_jetAK8Phi            );
  hvfloat  h_jetAK8Mass           ; evt.getByLabel (l_jetAK8Mass             , h_jetAK8Mass           );
  hvfloat  h_jetAK8FilteredMass   ; evt.getByLabel (l_jetAK8FilteredMass     , h_jetAK8FilteredMass   );
  hvfloat  h_jetAK8PrunedMass     ; evt.getByLabel (l_jetAK8PrunedMass       , h_jetAK8PrunedMass     );
  hvfloat  h_jetAK8TrimmedMass    ; evt.getByLabel (l_jetAK8TrimmedMass      , h_jetAK8TrimmedMass    );
  hvfloat  h_jetAK8Energy         ; evt.getByLabel (l_jetAK8Energy           , h_jetAK8Energy         );
  hvfloat  h_jetAK8Flavour        ; evt.getByLabel (l_jetAK8Flavour          , h_jetAK8Flavour        );
  hvfloat  h_jetAK8CSV            ; evt.getByLabel (l_jetAK8CSV              , h_jetAK8CSV            );
  hvfloat  h_jetAK8JEC            ; evt.getByLabel (l_jetAK8JEC              , h_jetAK8JEC            );
  hvfloat  h_jetAK8Area           ; evt.getByLabel (l_jetAK8Area             , h_jetAK8Area           );
  hvfloat  h_jetAK8Tau1           ; evt.getByLabel (l_jetAK8Tau1             , h_jetAK8Tau1           ); 
  hvfloat  h_jetAK8Tau2           ; evt.getByLabel (l_jetAK8Tau2             , h_jetAK8Tau2           ); 
  hvfloat  h_jetAK8Tau3           ; evt.getByLabel (l_jetAK8Tau3             , h_jetAK8Tau3           ); 
  hvfloat  h_jetAK8nSubJets       ; evt.getByLabel (l_jetAK8nSubJets         , h_jetAK8nSubJets       ); 
  hvfloat  h_jetAK8minmass        ; evt.getByLabel (l_jetAK8minmass          , h_jetAK8minmass        ); 
  hvfloat  h_jetAK8VSubjetIndex0  ; evt.getByLabel (l_jetAK8VSubjetIndex0    , h_jetAK8VSubjetIndex0  );  
  hvfloat  h_jetAK8VSubjetIndex1  ; evt.getByLabel (l_jetAK8VSubjetIndex1    , h_jetAK8VSubjetIndex1  );  
  hvfloat  h_jetAK8TopSubjetIndex0; evt.getByLabel (l_jetAK8TopSubjetIndex0  , h_jetAK8TopSubjetIndex0); 
  hvfloat  h_jetAK8TopSubjetIndex1; evt.getByLabel (l_jetAK8TopSubjetIndex1  , h_jetAK8TopSubjetIndex1); 
  hvfloat  h_jetAK8TopSubjetIndex2; evt.getByLabel (l_jetAK8TopSubjetIndex2  , h_jetAK8TopSubjetIndex2); 
  hvfloat  h_jetAK8TopSubjetIndex3; evt.getByLabel (l_jetAK8TopSubjetIndex3  , h_jetAK8TopSubjetIndex3); 
  hvfloat  h_subjetAK8BDisc       ; evt.getByLabel (l_subjetAK8BDisc         , h_subjetAK8BDisc       ); 
  hvfloat  h_subjetAK8Pt          ; evt.getByLabel (l_subjetAK8Pt            , h_subjetAK8Pt          ); 
  hvfloat  h_subjetAK8Eta         ; evt.getByLabel (l_subjetAK8Eta           , h_subjetAK8Eta         ); 
  hvfloat  h_subjetAK8Phi         ; evt.getByLabel (l_subjetAK8Phi           , h_subjetAK8Phi         ); 
  hvfloat  h_subjetAK8Mass        ; evt.getByLabel (l_subjetAK8Mass          , h_subjetAK8Mass        ); 
  hvfloat  h_subjetCmsTopTagBDisc ; evt.getByLabel (l_subjetCmsTopTagBDisc   , h_subjetCmsTopTagBDisc ); 
  hvfloat  h_subjetCmsTopTagPt    ; evt.getByLabel (l_subjetCmsTopTagPt      , h_subjetCmsTopTagPt    ); 
  hvfloat  h_subjetCmsTopTagEta   ; evt.getByLabel (l_subjetCmsTopTagEta     , h_subjetCmsTopTagEta   ); 
  hvfloat  h_subjetCmsTopTagPhi   ; evt.getByLabel (l_subjetCmsTopTagPhi     , h_subjetCmsTopTagPhi   ); 
  hvfloat  h_subjetCmsTopTagMass  ; evt.getByLabel (l_subjetCmsTopTagMass    , h_subjetCmsTopTagMass  ); 
  hvfloat  h_jetAK4Pt             ; evt.getByLabel (l_jetAK4Pt               , h_jetAK4Pt             );
  hvfloat  h_jetAK4Eta            ; evt.getByLabel (l_jetAK4Eta              , h_jetAK4Eta            );
  hvfloat  h_jetAK4Phi            ; evt.getByLabel (l_jetAK4Phi              , h_jetAK4Phi            );
  hvfloat  h_jetAK4Mass           ; evt.getByLabel (l_jetAK4Mass             , h_jetAK4Mass           );
  hvfloat  h_jetAK4Energy         ; evt.getByLabel (l_jetAK4Energy           , h_jetAK4Energy         );
  hvfloat  h_jetAK4Flavour        ; evt.getByLabel (l_jetAK4Flavour          , h_jetAK4Flavour        );
  hvfloat  h_jetAK4CSV            ; evt.getByLabel (l_jetAK4CSV              , h_jetAK4CSV            );
  hvfloat  h_jetAK4JEC            ; evt.getByLabel (l_jetAK4JEC              , h_jetAK4JEC            );
  hvfloat  h_jetAK4nHadEnergy     ; evt.getByLabel (l_jetAK4nHadEnergy       , h_jetAK4nHadEnergy     );
  hvfloat  h_jetAK4nEMEnergy      ; evt.getByLabel (l_jetAK4nEMEnergy        , h_jetAK4nEMEnergy      );
  hvfloat  h_jetAK4HFHadronEnergy ; evt.getByLabel (l_jetAK4HFHadronEnergy   , h_jetAK4HFHadronEnergy );
  hvfloat  h_jetAK4cHadEnergy     ; evt.getByLabel (l_jetAK4cHadEnergy       , h_jetAK4cHadEnergy     );
  hvfloat  h_jetAK4cEMEnergy      ; evt.getByLabel (l_jetAK4cEMEnergy        , h_jetAK4cEMEnergy      );
  hvfloat  h_jetAK4numDaughters   ; evt.getByLabel (l_jetAK4numDaughters     , h_jetAK4numDaughters   );
  hvfloat  h_jetAK4cMultip        ; evt.getByLabel (l_jetAK4cMultip          , h_jetAK4cMultip        );
  hvfloat  h_jetAK4Y              ; evt.getByLabel (l_jetAK4Y                , h_jetAK4Y              );
  hvfloat  h_jetAK4Area           ; evt.getByLabel (l_jetAK4Area             , h_jetAK4Area           );

  unsigned nbjets = *h_ngoodBTaggedAK4Jets.product() ; 
  unsigned ntjets = *h_nTJets.product() ; 
  unsigned nhjets = *h_nHJets.product() ; 
  unsigned nwjets = *h_nWJets.product() ; 

  int    evttype(-1) ; 
  double pttjet(-1) ;
  double mtjet(-1) ;
  double ptwjet(-1) ;
  double mwjet(-1) ;
  double pthjet(-1) ;
  double mhjet(-1) ;
  double ptth(-1) ;
  double mth(-1) ;
  double ptbleading(-1) ;
  double etableading(0) ;
  double ptjforward(-1) ;
  double etajforward(-1) ;
  double detath(-1) ; 
  double detawh(-1) ; 
  double drwb(-1) ;
  double mwhb(-1) ; 

  vector<unsigned>ak4idx = *h_ak4goodjets.product() ; 
  for ( unsigned ij = 0; ij < ak4idx.size(); ++ij ) {
    if ( abs(h_jetAK4Eta.product()->at(ij)) > etajforward ) {
      etajforward = abs(h_jetAK4Eta.product()->at(ij)) ; 
      ptjforward = h_jetAK4Pt.product()->at(ij) ; 
    }
  }

  if ( nbjets > 0 ) { 
    ptbleading = h_jetAK4Pt.product()->at( (h_bjetIdxs.product()->at(0)) ) ;
    etableading = h_jetAK4Eta.product()->at( (h_bjetIdxs.product()->at(0)) ) ;
    if ( ntjets > 0  && nhjets == 0 ) { //// --> type 0
      evttype = 0 ; 
      pttjet = h_jetAK8Pt.product()->at( (h_tjetIdxs.product()->at(0)) ) ; 
      mtjet = h_jetAK8Mass.product()->at( (h_tjetIdxs.product()->at(0)) ) ; 
    }
    if ( ntjets > 0  && nhjets > 0 ) { //// --> type 1 
      evttype = 1 ; 
      pttjet = h_jetAK8Pt.product()->at( (h_tjetIdxs.product()->at(0)) ) ; 
      mtjet = h_jetAK8Mass.product()->at( (h_tjetIdxs.product()->at(0)) ) ; 
      pthjet = h_jetAK8Pt.product()->at( (h_hjetIdxs.product()->at(0)) ) ; 
      mhjet = h_jetAK8Mass.product()->at( (h_hjetIdxs.product()->at(0)) ) ; 
      TLorentzVector p4t, p4h;
      p4t.SetPtEtaPhiM( 
          h_jetAK8Pt.product()->at( (h_tjetIdxs.product()->at(0)) ), 
          h_jetAK8Eta.product()->at( (h_tjetIdxs.product()->at(0)) ),
          h_jetAK8Phi.product()->at( (h_tjetIdxs.product()->at(0)) ),
          h_jetAK8Mass.product()->at( (h_tjetIdxs.product()->at(0)) ) 
          ) ; 
      p4h.SetPtEtaPhiM( 
          h_jetAK8Pt.product()->at( (h_hjetIdxs.product()->at(0)) ), 
          h_jetAK8Eta.product()->at( (h_hjetIdxs.product()->at(0)) ),
          h_jetAK8Phi.product()->at( (h_hjetIdxs.product()->at(0)) ),
          h_jetAK8Mass.product()->at( (h_hjetIdxs.product()->at(0)) ) 
          ) ; 
      ptth = (p4t+p4h).Pt() ; 
      mth = (p4t+p4h).Mag() ; 
      detath = abs(p4t.Eta() - p4h.Eta()) ; 
    } 
    else if ( ntjets == 0 && nhjets > 0 && nwjets > 0 ) { //// --> type 2
      evttype = 2 ; 
      ptwjet = h_jetAK8Pt.product()->at( (h_wjetIdxs.product()->at(0)) ) ; 
      mwjet = h_jetAK8Mass.product()->at( (h_wjetIdxs.product()->at(0)) ) ; 
      pthjet = h_jetAK8Pt.product()->at( (h_hjetIdxs.product()->at(0)) ) ; 
      mhjet = h_jetAK8Mass.product()->at( (h_hjetIdxs.product()->at(0)) ) ; 
      TLorentzVector p4w, p4h, p4b;
      p4w.SetPtEtaPhiM( 
          h_jetAK8Pt.product()->at( (h_wjetIdxs.product()->at(0)) ), 
          h_jetAK8Eta.product()->at( (h_wjetIdxs.product()->at(0)) ),
          h_jetAK8Phi.product()->at( (h_wjetIdxs.product()->at(0)) ),
          h_jetAK8Mass.product()->at( (h_wjetIdxs.product()->at(0)) ) 
          ) ; 
      p4h.SetPtEtaPhiM( 
          h_jetAK8Pt.product()->at( (h_hjetIdxs.product()->at(0)) ), 
          h_jetAK8Eta.product()->at( (h_hjetIdxs.product()->at(0)) ),
          h_jetAK8Phi.product()->at( (h_hjetIdxs.product()->at(0)) ),
          h_jetAK8Mass.product()->at( (h_hjetIdxs.product()->at(0)) ) 
          ) ; 
      p4b.SetPtEtaPhiM( 
          h_jetAK4Pt.product()->at( (h_bjetIdxs.product()->at(0)) ), 
          h_jetAK4Eta.product()->at( (h_bjetIdxs.product()->at(0)) ),
          h_jetAK4Phi.product()->at( (h_bjetIdxs.product()->at(0)) ),
          h_jetAK4Mass.product()->at( (h_bjetIdxs.product()->at(0)) ) 
          ) ; 
      detawh = abs(p4w.Eta() - p4h.Eta()) ; 
      drwb = p4w.DeltaR(p4b) ;
      mwhb = (p4w + p4h + p4b).Mag() ; 
    } 
    else if ( ntjets == 0 && nwjets == 0 && nhjets > 0 ) { //// --> type 3 
      evttype = 3 ; 
      pthjet = h_jetAK8Pt.product()->at( (h_hjetIdxs.product()->at(0)) ) ; 
      mhjet = h_jetAK8Mass.product()->at( (h_hjetIdxs.product()->at(0)) ) ; 
    }
    else if ( ntjets == 0 && nhjets == 0 && nwjets > 0 && nbjets > 1 ) { //// --> type 4
      evttype = 4 ; 
      ptwjet = h_jetAK8Pt.product()->at( (h_wjetIdxs.product()->at(0)) ) ; 
      mwjet = h_jetAK8Mass.product()->at( (h_wjetIdxs.product()->at(0)) ) ; 
    }
  }
  else { //// Define control
  }

  auto_ptr<int> evttypeptr( new int(evttype) ) ;
  evt.put(evttypeptr, "evttype") ; 
  auto_ptr<double> pttjetptr( new double(pttjet) ) ; 
  evt.put(pttjetptr, "pttjet") ; 
  auto_ptr<double> mtjetptr( new double(mtjet) ) ; 
  evt.put(mtjetptr, "mtjet") ; 
  auto_ptr<double> ptwjetptr( new double(ptwjet) ) ; 
  evt.put(ptwjetptr, "ptwjet") ; 
  auto_ptr<double> mwjetptr( new double(mwjet) ) ; 
  evt.put(mwjetptr, "mwjet") ; 
  auto_ptr<double> pthjetptr( new double(pthjet) ) ; 
  evt.put(pthjetptr, "pthjet") ; 
  auto_ptr<double> mhjetptr( new double(mhjet) ) ; 
  evt.put(mhjetptr, "mhjet") ; 
  auto_ptr<double> ptthptr( new double(ptth) ) ; 
  evt.put(ptthptr, "ptth") ; 
  auto_ptr<double> mthptr( new double(mth) ) ; 
  evt.put(mthptr, "mth") ; 
  auto_ptr<double> ptjforwardptr( new double(ptjforward) ) ; 
  evt.put(ptjforwardptr, "ptjforward") ; 
  auto_ptr<double> etajforwardptr( new double(etajforward) ) ; 
  evt.put(etajforwardptr, "etajforward") ; 
  auto_ptr<double> ptbleadingptr( new double(ptbleading) ) ; 
  evt.put(ptbleadingptr, "ptbleading") ; 
  auto_ptr<double> etableadingptr( new double(etableading) ) ; 
  evt.put(etableadingptr, "etableading") ; 
  auto_ptr<double> detathptr( new double(detath) ) ; 
  evt.put(detathptr, "detath") ; 
  auto_ptr<double> detawhptr( new double(detawh) ) ; 
  evt.put(detawhptr, "detawh") ; 
  auto_ptr<double> drwbptr( new double(drwb) ) ; 
  evt.put(drwbptr, "drwb") ; 
  auto_ptr<double> mwhbptr( new double(mwhb) ) ; 
  evt.put(mwhbptr, "mwhb") ; 

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
