import FWCore.ParameterSet.Config as cms

genPartParams = cms.PSet(
    genPartPt           = cms.InputTag("genPart", "genPartPt"), 
    genPartEta          = cms.InputTag("genPart", "genPartEta"), 
    genPartPhi          = cms.InputTag("genPart", "genPartPhi"), 
    genPartMass         = cms.InputTag("genPart", "genPartMass"), 
    genPartE            = cms.InputTag("genPart", "genPartE"), 
    genPartCharge       = cms.InputTag("genPart", "genPartCharge"), 
    genPartID           = cms.InputTag("genPart", "genPartID"), 
    genPartStatus       = cms.InputTag("genPart", "genPartStatus"),
    genPartMom0ID       = cms.InputTag("genPart", "genPartMom0ID"), 
    genPartMom1ID       = cms.InputTag("genPart", "genPartMom1ID"), 
    genPartDau0ID       = cms.InputTag("genPart", "genPartDau0ID"), 
    genPartDau1ID       = cms.InputTag("genPart", "genPartDau1ID"), 
    genPartMom0Status   = cms.InputTag("genPart", "genPartMom0Status"), 
    genPartMom1Status   = cms.InputTag("genPart", "genPartMom1Status"), 
    genPartDau0Status   = cms.InputTag("genPart", "genPartDau0Status"), 
    genPartDau1Status   = cms.InputTag("genPart", "genPartDau1Status"), 
    debug               = cms.bool(False), 
    )

getSelectParams = cms.PSet(
    genPartParams, 
    ids                 = cms.vint32(-8000001,-8000002,8000001,8000002), 
    statuses            = cms.vint32(22), 
    checkstatus         = cms.bool(False),
    mom0ids             = cms.vint32(-8000001,-8000002,8000001,8000002), 
    mom1ids             = cms.vint32(-8000001,-8000002,8000001,8000002), 
    checkmomid          = cms.bool(False),
    dau0ids             = cms.vint32(-5,5,-6,6,23), 
    dau1ids             = cms.vint32(-5,5,-6,6,23), 
    checkdauid          = cms.bool(False),
    )
