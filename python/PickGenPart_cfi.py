import FWCore.ParameterSet.Config as cms

genPartParams = cms.PSet(
    genParticles        = cms.InputTag("filteredPrunedGenParticles"),
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
