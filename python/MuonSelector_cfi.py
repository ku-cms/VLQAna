import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Muon_cfi import * 

defaultMuonSelectionParameters = cms.PSet(
    defaultMuonParameters, 
    muidtype = cms.string("LOOSE"), 
    muPtMin = cms.double(5),
    muPtMax = cms.double(10000),
    muAbsEtaMax = cms.double(5),
    muCharge = cms.double(0), 
    muIsoMin = cms.double(0.00),
    muIsoMax = cms.double(0.30), 
    )

defaultMuPSelectionParameters = defaultMuonSelectionParameters.clone(
    muPtMin = cms.double(25),
    muAbsEtaMax = cms.double(2.1),
    muCharge  = cms.double(1.0),  
    )

defaultMuMSelectionParameters = defaultMuonSelectionParameters.clone(
    muPtMin = cms.double(25),
    muAbsEtaMax = cms.double(2.1),
    muCharge  = cms.double(-1.0),  
    )
