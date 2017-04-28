import FWCore.ParameterSet.Config as cms

massReco = cms.EDFilter("MassReco",
    elPt     = cms.InputTag("electrons", "elPt"),
    elEta    = cms.InputTag("electrons", "elEta"),
    elPhi    = cms.InputTag("electrons", "elPhi"),
    elE      = cms.InputTag("electrons", "elE"),
    muPt     = cms.InputTag("muons", "muPt"),
    muEta    = cms.InputTag("muons", "muEta"),
    muPhi    = cms.InputTag("muons", "muPhi"),
    muE      = cms.InputTag("muons", "muE"),
    jets     = cms.InputTag("ana", "jets"),
    bjets    = cms.InputTag("ana", "bjets"),
    zjets    = cms.InputTag("ana", "wjets"),
    hjets    = cms.InputTag("ana", "hjets"),
    zllcands = cms.InputTag("ana", "zllcands"),
    evtwt    = cms.InputTag("ana", "PreWeight"),
    ptMin    = cms.double(0.),
    zdecaymode = cms.string('zmumu'),
    signalType = cms.string('')
    )
