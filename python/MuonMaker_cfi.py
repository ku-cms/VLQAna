import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Muon_cfi import * 

defaultMuonMakerParameters = cms.PSet(
    defaultMuonParameters, 
    muidtype = cms.string("LOOSE"), 
    muPtMin = cms.double(25),
    muPtMax = cms.double(10000),
    muAbsEtaMax = cms.double(2.1),
    muIsoMin = cms.double(0.00),
    muIsoMax = cms.double(0.30), 
    )
