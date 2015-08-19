import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Electron_cfi import * 

defaultElectronSelectionParameters = cms.PSet(
    defaultElectronParameters, 
    elidtype = cms.string("TIGHT"), 
    elPtMin = cms.double(30),
    elPtMax = cms.double(10000),
    elAbsEtaMax = cms.double(2.4),
    elCharge = cms.double(1.0), 
    elIsoMin = cms.double(-0.1),
    elIsoMax = cms.double(1000), 
    )

defaultElPSelectionParamaters = defaultElectronSelectionParameters.clone(
    elCharge  = cms.double(1.0),  
    )

defaultElMSelectionParamaters = defaultElectronSelectionParameters.clone(
    elCharge  = cms.double(-1.0),  
    )
