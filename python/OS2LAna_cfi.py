import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.ZCandSelector_cfi import *
from Analysis.VLQAna.ApplyLeptonSFs_cfi import *
from Analysis.VLQAna.ElectronMaker_cfi import *
from Analysis.VLQAna.MuonMaker_cfi import *
from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *

ana = cms.EDFilter("OS2LAna", 
    evttype                    = cms.InputTag("evtcleaner","evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner","evtwtPV"),
    npv                        = cms.InputTag("evtcleaner","npv"),
    filterSignal               = cms.bool(False), 
    signalType                 = cms.string("EvtType_MC_tZtZ"), 
    zdecayMode                 = cms.string("zelele"),
    applyLeptonSFs             = cms.bool(True),  
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
        ptMin = cms.double(200.),
        ), 
    GenHSelParams              = genPartParams.clone(), 
    HTMin                      = cms.double  (800.), #dummy varaible not used in analysis
    STMin                      = cms.double  (400.), 
    lepsfsParams               = defaultWP,
    muselParams                = defaultMuonMakerParameters, 
    elselParams                = defaultElectronMakerParameters, 
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK4BTaggedselParams     = defaultBTaggedAK4JetSelectionParameters, 
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetWTaggedselParams        = defaultWJetSelectionParameters,
    jetTopTaggedselParams      = defaultTJetSelectionParameters, 
    )
