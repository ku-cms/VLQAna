import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Jet_cfi import * 

defaultAK4JetIDParameters = cms.PSet(
    defaultAK4JetParameters, 
    version                    = cms.string  ("FIRSTDATA"),
    quality                    = cms.string  ("LOOSE"),
    )

defaultAK8CHSJetIDParameters = cms.PSet(
    defaultAK8CHSJetParameters, 
    version                    = cms.string  ("FIRSTDATA"),
    quality                    = cms.string  ("TIGHT"),
    )

defaultAK8PuppiJetIDParameters = cms.PSet(
    defaultAK8PuppiJetParameters, 
    version                    = cms.string  ("FIRSTDATA"),
    quality                    = cms.string  ("TIGHT"),
    )
