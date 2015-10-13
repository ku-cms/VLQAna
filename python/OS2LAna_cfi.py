import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.ZCandSelector_cfi import *
from Analysis.VLQAna.ElectronMaker_cfi import *
from Analysis.VLQAna.MuonMaker_cfi import *
from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *

ana = cms.EDFilter("OS2LAna", 
    evttype                    = cms.InputTag("evtcleaner","evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner","evtwtPV"),
    npv                        = cms.InputTag("evtcleaner","npv"),
    DoPUReweightingNPV         = cms.bool(False),
    DilepCandParams            = defaultZCandSelectionParameters.clone(), 
    ZCandParams                = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(0.),
        ), 
    BoostedZCandParams         = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(250.),
        ), 
    GenHSelParams              = genPartParams.clone(), 
    HTMin                      = cms.double  (800.), 
    STMin                      = cms.double  (1200.), 
    muselParams                = defaultMuonMakerParameters, 
    elselParams                = defaultElectronMakerParameters, 
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK4BTaggedselParams     = defaultBTaggedAK4JetSelectionParameters, 
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetWTaggedselParams        = defaultWJetSelectionParameters,
    jetTopTaggedselParams      = defaultTJetSelectionParameters, 
    )
