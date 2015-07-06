import FWCore.ParameterSet.Config as cms

defaultZCandSelectionParameters = cms.PSet(
    massMin = cms.double(60),
    massMax = cms.double(120),
    ptMin = cms.double(150),
    ptMax = cms.double(100000), 
    )


