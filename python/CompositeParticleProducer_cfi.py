import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *

par = cms.EDProducer("CompositeParticleProducer",
    particlename     = cms.string("HbbCandidates"), 
    GenPartParams    = genPartParams.clone(
      ids            = cms.vint32(25), 
      statuses       = cms.vint32(52), 
      checkstatus    = cms.bool(True),
      ), 
    GenDauParams     = cms.VPSet(
      genPartParams.clone(
        ids            = cms.vint32(5), 
        momids         = cms.vint32(25), 
        checkmomid     = cms.bool(True),
        statuses       = cms.vint32(23), 
        checkstatus    = cms.bool(True),
        ), 
      genPartParams.clone(
        ids            = cms.vint32(-5), 
        momids         = cms.vint32(25), 
        checkmomid     = cms.bool(True),
        statuses       = cms.vint32(23), 
        checkstatus    = cms.bool(True),
        ), 
      )
    )
