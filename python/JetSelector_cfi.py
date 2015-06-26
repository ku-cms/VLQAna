import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.JetID_cfi import * 

defaultAK4JetSelectionParameters = cms.PSet(
    JetIDParams         = defaultAK4JetIDParameters.clone(), 
    JetSubstrParams     = cms.PSet(), 
    SubjetParams        = cms.PSet(),
    jettype             = cms.string('AK4JET'),
    jetPtMin            = cms.double(30),
    jetPtMax            = cms.double(1000000),
    jetAbsEtaMax        = cms.double(5.0),
    jetCSVDiscMin       = cms.double(-10000),
    jetCSVDiscMax       = cms.double(1.000),
    IsJetIDLoose        = cms.bool(True),
    IsJetIDTight        = cms.bool(False),
    )

defaultBTaggedAK4JetSelectionParameters = defaultAK4JetSelectionParameters.clone(
    jettype             = cms.string('BTAGGEDAK4JET'),
    jetAbsEtaMax        = cms.double(2.4),
    jetCSVDiscMin       = cms.double(0.814),
    jetCSVDiscMax       = cms.double(1.000),
    )

defaultAK8JetSelectionParameters = defaultAK4JetSelectionParameters.clone( 
    JetIDParams         = defaultAK8JetIDParameters.clone(), 
    JetSubstrParams     = defaultJetSubstructureParameters.clone(),
    SubjetParams        = defaultSubjetParameters.clone(), 
    jettype             = cms.string('AK8JET'),
    jetPtMin            = cms.double(300),
    jetAbsEtaMax        = cms.double(2.4),
    jetPtMax            = cms.double(1000000),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(1.0) ,
    jettau3Bytau2Min    = cms.double(0.0) ,
    jettau3Bytau2Max    = cms.double(1.0) ,
    jetMassMin          = cms.double(00) ,
    jetMassMax          = cms.double(1000000) ,
    jetPrunedMassMin    = cms.double(0.0) ,
    jetPrunedMassMax    = cms.double(1000000) ,
    jetTrimmedMassMin   = cms.double(0.0) ,
    jetTrimmedMassMax   = cms.double(1000000) ,
    jetWMassMin         = cms.double(0.0) ,
    jetWMassMax         = cms.double(1000000) ,
    jetTopMassMin       = cms.double(0.0) ,
    jetTopMassMax       = cms.double(1000000.) ,
    jetMinMassMin       = cms.double(0.0) ,
    jetMinMassMax       = cms.double(1000000) ,
    jetnSubJetsMin      = cms.double(-10) ,
    jetnSubJetsMax      = cms.double(1000000) ,
    subjetMassMin       = cms.double(0.0) ,
    subjetCSVMin        = cms.double(-1000000) ,
    )

defaultTJetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jettype             = cms.string('CMSTOPTAGGEDAK8JET'),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(1.0) ,
    jettau3Bytau2Min    = cms.double(0.55) ,
    jettau3Bytau2Max    = cms.double(1.0) ,
    jetMinMassMin       = cms.double(50.) ,
    jetMassMin          = cms.double(140) ,
    jetMassMax          = cms.double(250) ,
    jetnSubJetsMin      = cms.double(3) ,
    jetnSubJetsMax      = cms.double(3) ,
    )

defaultHJetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jettype             = cms.string('HTAGGEDAK8JET'),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(0.5) ,
    jetPrunedMassMin    = cms.double(100) ,
    jetPrunedMassMax    = cms.double(140) ,
    jetMassMin          = cms.double(120.) ,
    jetMassMax          = cms.double(150) ,
    subjetCSVMin        = cms.double(0.423) ,
    jetnSubJetsMin      = cms.double(2) ,
    jetnSubJetsMax      = cms.double(2) ,
    )

defaultWJetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(0.5) ,
    jetPrunedMassMin    = cms.double(50) ,
    jetPrunedMassMax    = cms.double(90) ,
    jetMassMin          = cms.double(70.) ,
    jetMassMax          = cms.double(100) ,
    subjetCSVMin        = cms.double(0.000) ,
    jetnSubJetsMin      = cms.double(2) ,
    jetnSubJetsMax      = cms.double(2) ,
    )

defaultBTaggedAK8JetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jettype             = cms.string('BTAGGEDAK8JET'),
    jetCSVDiscMin       = cms.double(0.814),
    jetCSVDiscMax       = cms.double(1.000),
    )

