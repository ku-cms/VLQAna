import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Electron_cfi import * 

defaultElectronMakerParameters = cms.PSet(
    defaultElectronParameters, 
    elidtype = cms.string("LOOSE"), #Using electron ID coded in VID tool
    elPtMin = cms.double(25),
    elPtMax = cms.double(10000),
    elAbsEtaMax = cms.double(2.4),
    )
