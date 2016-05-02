import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.ZCandSelector_cfi import *
from Analysis.VLQAna.ApplyLeptonSFs_cfi import *
from Analysis.VLQAna.ElectronMaker_cfi import *
from Analysis.VLQAna.MuonMaker_cfi import *
from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *
from Analysis.VLQAna.METMaker_cfi import *

ana = cms.EDFilter("OS2LAna",
    hltdecision                = cms.InputTag("evtcleaner","hltdecision"),   
    evttype                    = cms.InputTag("evtcleaner","evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner","evtwtPV"),
    npv                        = cms.InputTag("evtcleaner","npv"),
    filterSignal               = cms.bool(False),
    additionalPlots            = cms.bool(False), 
    signalType                 = cms.string(""), 
    zdecayMode                 = cms.string("zelel"),
    optimizeReco               = cms.bool(False),
    vlqMass                    = cms.double(1000.),
    bosMass                    = cms.double(91.2),
    lep                        = cms.string("el"),
    applyLeptonSFs             = cms.bool(True),  
    DoPUReweightingNPV         = cms.bool(False),
    DilepCandParams            = defaultZCandSelectionParameters.clone(
        massMin = cms.double(50),
    ), 
    ZCandParams                = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMaxLeadingLep = cms.double(45),
        ptMin = cms.double(0.),
        ), 
    BoostedZCandParams         = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMaxLeadingLep = cms.double(45),
        ptMin = cms.double(200.),
        ), 
    GenHSelParams              = genPartParams.clone(), 
    STMin                      = cms.double  (500.),
    HTMin                      = cms.double (150.),
    lepsfsParams               = defaultWP.clone(
        lepidtype = cms.string("TIGHT"),
        zdecayMode = cms.string("zelel"),
        ),
    metselParams               = defaultMETMakerParameters,
    muselParams                = defaultMuonMakerParameters, 
    elselParams                = defaultElectronMakerParameters, 
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK4BTaggedselParams     = defaultBTaggedAK4JetSelectionParameters, 
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetWTaggedselParams        = defaultWJetSelectionParameters,
    jetTopTaggedselParams      = defaultTJetSelectionParameters,
    genParams                  = getSelectParams,
    )
