import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Electron_cfi import * 

defaultElectronSelectionParameters = cms.PSet(
    defaultElectronParameters, 
    elidtype = cms.string("LOOSE"), #Using electron ID coded in VID tool
    elPtMin = cms.double(5),
    elPtMax = cms.double(10000),
    elAbsEtaMax = cms.double(5),
    elCharge = cms.double(0), 
    elIsoMin = cms.double(0.00),
    elIsoMax = cms.double(0.2), # No need to set electron isolation by hand
    useVID = cms.bool(True), 
    )

defaultElPSelectionParameters = defaultElectronSelectionParameters.clone(
    elPtMin = cms.double(25),
    elAbsEtaMax = cms.double(2.4),
    elCharge  = cms.double(1.0),  
    )

defaultElMSelectionParameters = defaultElectronSelectionParameters.clone(
    elPtMin = cms.double(25),
    elAbsEtaMax = cms.double(2.4),
    elCharge  = cms.double(-1.0),  
    )
