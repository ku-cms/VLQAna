from Analysis.VLQAna.PickGenPart_cfi import * 

vlqParams = cms.PSet(
    ids                 = cms.vint32(-8000001,-8000002,8000001,8000002), 
    statuses            = cms.vint32(22), 
    checkstatus         = cms.bool(False),
    mom0ids             = cms.vint32(-8000001,-8000002,8000001,8000002), 
    mom1ids             = cms.vint32(-8000001,-8000002,8000001,8000002), 
    checkmomid          = cms.bool(False),
    dau0ids             = cms.vint32(-5,5,-6,6,23), 
    dau1ids             = cms.vint32(-5,5,-6,6,23), 
    checkdauid          = cms.bool(True),
    )

TtZParams = vlqParams.clone(
    ids                 = cms.vint32(-8000001,8000001), 
    mom0ids             = cms.vint32(-8000001,8000001), 
    mom1ids             = cms.vint32(-8000001,8000001), 
    dau0ids             = cms.vint32(-6,6,23), 
    dau1ids             = cms.vint32(-6,6,23), 
    )

TtHParams = vlqParams.clone(
    ids                 = cms.vint32(-8000001,8000001), 
    mom0ids             = cms.vint32(-8000001,8000001), 
    mom1ids             = cms.vint32(-8000001,8000001), 
    dau0ids             = cms.vint32(-6,6,25), 
    dau1ids             = cms.vint32(-6,6,25), 
    )

TbWParams = vlqParams.clone(
    ids                 = cms.vint32(-8000001,8000001), 
    mom0ids             = cms.vint32(-8000001,8000001), 
    mom1ids             = cms.vint32(-8000001,8000001), 
    dau0ids             = cms.vint32(-5,5,-24,24), 
    dau1ids             = cms.vint32(-5,5,-24,24), 
    )

BbZParams = vlqParams.clone(
    ids                 = cms.vint32(-8000002,8000002), 
    mom0ids             = cms.vint32(-8000002,8000002), 
    mom1ids             = cms.vint32(-8000002,8000002), 
    dau0ids             = cms.vint32(-5,5,23), 
    dau1ids             = cms.vint32(-5,5,23), 
    )

BbHParams = vlqParams.clone(
    ids                 = cms.vint32(-8000002,8000002), 
    mom0ids             = cms.vint32(-8000002,8000002), 
    mom1ids             = cms.vint32(-8000002,8000002), 
    dau0ids             = cms.vint32(-5,5,25), 
    dau1ids             = cms.vint32(-5,5,25), 
    )

BtWParams = vlqParams.clone(
    ids                 = cms.vint32(-8000002,8000002), 
    mom0ids             = cms.vint32(-8000002,8000002), 
    mom1ids             = cms.vint32(-8000002,8000002), 
    dau0ids             = cms.vint32(-6,6,-24,24), 
    dau1ids             = cms.vint32(-6,6,-24,24), 
    )
