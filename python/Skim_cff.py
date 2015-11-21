import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.ZCandSelector_cfi import *
from Analysis.VLQAna.ElectronMaker_cfi import *
from Analysis.VLQAna.MuonMaker_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *

skim = cms.EDFilter("Skim",
    genEvtInfoProdName         = cms.string('generator'),
    ZCandParams                = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(0.),
        ptMax = cms.double(10000000.),
        ), 
    muselParams                = defaultMuonMakerParameters, 
    elselParams                = defaultElectronMakerParameters, 
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    isData                     = cms.bool(False),
    nzelel                     = cms.int32(0),
    nzmumu                     = cms.int32(0),
    nak4jets                   = cms.int32(0),
    nak8jets                   = cms.int32(0), 
    )
