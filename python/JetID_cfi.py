import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Jet_cfi import defaultJetAK4Parameters

defaultJetIDParameters = cms.PSet(
    defaultJetAK4Parameters, 
    version                    = cms.string  ("FIRSTDATA"),
    quality                    = cms.string  ("LOOSE"),
    )
