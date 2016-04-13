import FWCore.ParameterSet.Config as cms

genParams = cms.PSet(
    genPartCharge  = cms.InputTag("genPart", "genPartCharge"),
    genPartE       = cms.InputTag("genPart", "genPartE"),
    genPartEta     = cms.InputTag("genPart", "genPartEta"),
    genPartID      = cms.InputTag("genPart", "genPartID"),
    genPartMass    = cms.InputTag("genPart", "genPartMass"),
    genPartMomID   = cms.InputTag("genPart", "genPartMomID"),
    genPartPhi     = cms.InputTag("genPart", "genPartPhi"),
    genPartPt      = cms.InputTag("genPart", "genPartPt"),
    genPartStatus  = cms.InputTag("genPart", "genPartStatus"),
    ids            = cms.vint32(25,24,23,6,5,-25,-24,-23,-6,-5), #H, W, Z, t, b
    momids         = cms.vint32(8000001, -8000001),#TPrime
    checkmomid     = cms.bool(True),
    statuses       = cms.vint32(23,22),#on shell decaying particles
    checkstatus    = cms.bool(True),
    verbose        = cms.bool(False),
)
