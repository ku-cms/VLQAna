import FWCore.ParameterSet.Config as cms

vlqcands = cms.EDFilter("VLQCandProducer", 
    tjetsLabel   = cms.InputTag("anaBoosted", "tjets"),
    wjetsLabel   = cms.InputTag("anaBoosted", "wjets"),
    bjetsLabel   = cms.InputTag("anaBoosted", "bjets"),
    jetsLabel    = cms.InputTag("anaBoosted", "jets"),
    zllLabel     = cms.InputTag("anaBoosted", "zllcands"),
    mass_t      = cms.double(173.5),
    mass_w      = cms.double(80.4),
    mass_z      = cms.double(91),
    sigma_t      = cms.double(82),
    sigma_w      = cms.double(9.1),
    sigma_z      = cms.double(9.1),
    sigma_hadvlq = cms.double(120),
    sigma_lepvlq = cms.double(120),
    )

