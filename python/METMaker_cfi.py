import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.MET_cfi import *

defaultMETMakerParameters = cms.PSet(
	defaultMETParameters,
	METPtMin = cms.double(0),
	METPtMax = cms.double(100000)
	)
