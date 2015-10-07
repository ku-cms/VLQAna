import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *
ana = cms.EDFilter("VLQAna", 
    trigNameLabel              = cms.InputTag("TriggerUserData", "triggerNameTree"), 
    trigBitLabel               = cms.InputTag("TriggerUserData", "triggerBitTree"), 
    jetAK8PtLabel              = cms.InputTag("jetsAK8", "jetAK8Pt"),
    jetAK8EtaLabel             = cms.InputTag("jetsAK8", "jetAK8Eta"),
    jetAK8PhiLabel             = cms.InputTag("jetsAK8", "jetAK8Phi"),
    jetAK8MassLabel            = cms.InputTag("jetsAK8", "jetAK8Mass"),
    jetAK8FilteredMassLabel    = cms.InputTag("jetsAK8", "jetAK8filteredMass"),
    jetAK8TrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jetAK8PrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetAK8SoftDropMassLabel    = cms.InputTag("jetsAK8", "jetAK8softDropMass"),
    jetAK8CSVLabel             = cms.InputTag("jetsAK8", "jetAK8CSV"),
    jetAK4PtLabel              = cms.InputTag("jetsAK4", "jetAK4Pt"),
    jetAK4EtaLabel             = cms.InputTag("jetsAK4", "jetAK4Eta"),
    jetAK4PhiLabel             = cms.InputTag("jetsAK4", "jetAK4Phi"),
    jetAK4MassLabel            = cms.InputTag("jetsAK4", "jetAK4Mass"),
    jetAK4CSVLabel             = cms.InputTag("jetsAK4", "jetAK4CSV"),
    hltPaths                   = cms.vstring (
        "HLT_PFHT650_v", 
        "HLT_PFHT800_v", 
        "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v", 
        "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v", 
        ), 
    AK4JetSelParams            = defaultAK4JetSelectionParameters.clone(), 
    BTaggedMediumAK4SelParams  = defaultBTaggedAK4JetSelectionParameters.clone(), 
    AK8JetSelParams            = defaultAK8JetSelectionParameters.clone(
        jetPtMin     = cms.double(400),
        jetAbsEtaMax = cms.double(1.5),
        jetMassMin   = cms.double(0) ,
        ), 
    HJetSelParams              = defaultHJetSelectionParameters.clone(), 
    TJetSelParams              = defaultTJetSelectionParameters.clone(), 
    minForwardEtaJet           = cms.double  (2.4), 
    HTMin                      = cms.double  (1050.), 
    )
