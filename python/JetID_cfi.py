import FWCore.ParameterSet.Config as cms

from MyAnalysis.VLQAna.Jet_cfi import * 

defaultAK4JetIDParameters = cms.PSet(
    defaultAK4JetParameters, 
    version                    = cms.string  ("FIRSTDATA"),
    quality                    = cms.string  ("LOOSE"),
    )

defaultAK8JetIDParameters = cms.PSet(
    defaultAK8JetParameters, 
    version                    = cms.string  ("FIRSTDATA"),
    quality                    = cms.string  ("TIGHT"),
    )
