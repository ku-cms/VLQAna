import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.JetID_cfi import defaultJetIDParameters

defaultJetSelectionParameters = cms.PSet(
    JetIDParams         = defaultJetIDParameters.clone(), 
    jettype             = cms.string('AK4JET'),
    jetPtMin            = cms.double(30),
    jetPtMax            = cms.double(100000),
    jetAbsEtaMax        = cms.double(2.4),
    jetCSVDiscMin       = cms.double(-10000.),
    jetCSVDiscMax       = cms.double(1.000),
    IsJetIDLoose        = cms.bool(True),
    IsJetIDTight        = cms.bool(False),
    )

