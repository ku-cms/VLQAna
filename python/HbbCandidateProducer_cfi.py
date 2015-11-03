import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *

hbb = cms.EDProducer("HbbCandidateProducer",
    GenHSelParams    = getSelectParams.clone(
      ids            = cms.vint32(25), 
      dau0ids             = cms.vint32(-5,5), 
      dau1ids             = cms.vint32(-5,5), 
      checkstatus    = cms.bool(False),
      ), 
    GenbSelParams    = getSelectParams.clone(
      ids            = cms.vint32(5), 
      mom0ids        = cms.vint32(25,-900), 
      mom1ids        = cms.vint32(25,-900), 
      checkmomid     = cms.bool(True),
      statuses       = cms.vint32(23), 
      checkstatus    = cms.bool(True),
      ), 
    GenbbarSelParams = getSelectParams.clone(
      ids            = cms.vint32(-5), 
      mom0ids        = cms.vint32(25,-900), 
      mom1ids        = cms.vint32(25,-900), 
      checkmomid     = cms.bool(True),
      statuses       = cms.vint32(23), 
      checkstatus    = cms.bool(True),
      ), 
    )
