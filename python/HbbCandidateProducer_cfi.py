import FWCore.ParameterSet.Config as cms

from MyAnalysis.VLQAna.PickGenPart_cfi import *

hbb = cms.EDProducer("HbbCandidateProducer",
    GenHSelParams    = genPartParams.clone(
      ids            = cms.vint32(25), 
      statuses       = cms.vint32(21,22,23,24,25,26,27,28,29,52), 
      checkstatus    = cms.bool(False),
      ), 
    GenbSelParams    = genPartParams.clone(
      ids            = cms.vint32(5), 
      momids         = cms.vint32(25), 
      checkmomid     = cms.bool(True),
      statuses       = cms.vint32(23), 
      checkstatus    = cms.bool(True),
      ), 
    GenbbarSelParams = genPartParams.clone(
      ids            = cms.vint32(-5), 
      momids         = cms.vint32(25), 
      checkmomid     = cms.bool(True),
      statuses       = cms.vint32(23), 
      checkstatus    = cms.bool(True),
      ), 
    )
