import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *

hbb = cms.EDProducer("HbbCandidateProducer",
    GenHSelParams    = genPartParams.clone(
      statuses       = cms.vint32(52), 
      checkstatus    = cms.bool(True),
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
