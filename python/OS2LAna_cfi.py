import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.ZCandSelector_cfi import *
from Analysis.VLQAna.ElectronMaker_cfi import *
from Analysis.VLQAna.MuonMaker_cfi import *
from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *

ana = cms.EDFilter("OS2LAna", 
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
    met                        = cms.InputTag("metFull", "metFullPt"), 
    metPhi                     = cms.InputTag("metFull", "metFullPhi"), 
    metNoHF                    = cms.InputTag("met", "metPt"), 
    metNoHFPhi                 = cms.InputTag("met", "metPhi"), 
    evtwt                      = cms.InputTag("evtcleaner","evtwt"),
    HbbCandsLabel              = cms.InputTag("hbb", "HbbCandidates"),
    jetAK4AreaLabel            = cms.InputTag("jetsAK4", "jetAK4jetArea"),
    DilepCandParams            = defaultZCandSelectionParameters.clone(), 
    ZCandParams                = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(0.),
        ), 
    BoostedZCandParams         = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(0.),
        ), 
    GenHSelParams              = genPartParams.clone(), 
    AK4JetSelParams            = defaultAK4JetSelectionParameters.clone(), 
    BTaggedMediumAK4SelParams   = defaultBTaggedAK4JetSelectionParameters.clone(), 
    AK8JetSelParams            = defaultAK8JetSelectionParameters.clone(
        jetPtMin   = cms.double(300),
        jetMassMin = cms.double(0) ,
        ), 
    TJetSelParams              = defaultTJetSelectionParameters.clone(), 
    HJetSelParams              = defaultHJetSelectionParameters.clone(), 
    WJetSelParams              = defaultWJetSelectionParameters.clone(), 
    HTMin                      = cms.double  (800.), 
    STMin                      = cms.double  (1200.), 
    isData                     = cms.bool    (False), 
    muselParams                = defaultMuonMakerParameters, 
    elselParams                = defaultElectronMakerParameters, 
    )

