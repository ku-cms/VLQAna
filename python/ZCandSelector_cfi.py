import FWCore.ParameterSet.Config as cms

defaultZCandSelectionParameters = cms.PSet(
    massMin = cms.double(50),
    massMax = cms.double(100000),
    ptMin = cms.double(0),
    ptMax = cms.double(100000),
    ptMaxLeadingLep = cms.double(25),
    ptMax2ndLeadingLep = cms.double(25)
    )


