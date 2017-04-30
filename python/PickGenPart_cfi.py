import FWCore.ParameterSet.Config as cms

genPartParams = cms.PSet(
    genParticles        = cms.InputTag("filteredPrunedGenParticles"),
    debug               = cms.bool(False), 
    )

getSelectParams = cms.PSet(
    genPartParams, 
    ids                 = cms.vint32(-8000001,-8000002,8000001,8000002,23,-24,24,25,-6,6,-5,5,-11,11,-12,12,-13,13,-14,14,-15,15,-16,16), 
    statuses            = cms.vint32(22), 
    checkstatus         = cms.bool(False),
    mom0ids             = cms.vint32(-8000001,-8000002,8000001,8000002,23,-24,24,25,-6,6,-5,5,-11,11,-12,12,-13,13,-14,14,-15,15,-16,16), 
    mom1ids             = cms.vint32(-8000001,-8000002,8000001,8000002,23,-24,24,25,-6,6,-5,5,-11,11,-12,12,-13,13,-14,14,-15,15,-16,16), 
    checkmomid          = cms.bool(False),
    dau0ids             = cms.vint32(23,-24,24,25,-6,6,-5,5,-11,11,-12,12,-13,13,-14,14,-15,15,-16,16), 
    dau1ids             = cms.vint32(23,-24,24,25,-6,6,-5,5,-11,11,-12,12,-13,13,-14,14,-15,15,-16,16), 
    checkdauid          = cms.bool(False),
    )
