import FWCore.ParameterSet.Config as cms

genPartParams = cms.PSet(
    genPartCharge  = cms.InputTag("genPart", "genPartCharge"), 
    genPartE       = cms.InputTag("genPart", "genPartE"), 
    genPartEta     = cms.InputTag("genPart", "genPartEta"), 
    genPartID      = cms.InputTag("genPart", "genPartID"), 
    genPartMass    = cms.InputTag("genPart", "genPartMass"), 
    genPartMomID   = cms.InputTag("genPart", "genPartMomID"), 
    genPartPhi     = cms.InputTag("genPart", "genPartPhi"), 
    genPartPt      = cms.InputTag("genPart", "genPartPt"), 
    genPartStatus  = cms.InputTag("genPart", "genPartStatus"),
    id             = cms.int32(25), 
    status         = cms.int32(22), 
    )
