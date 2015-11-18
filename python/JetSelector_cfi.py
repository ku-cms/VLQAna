import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.JetID_cfi import * 

defaultAK4JetSelectionParameters = cms.PSet(
    JetIDParams         = defaultAK4JetIDParameters, 
    JetSubstrParams     = cms.PSet(), 
    SubjetParams        = cms.PSet(),
    scaleJetP4          = cms.bool(False),
    scaledJetMass       = cms.double(125.0), 
    groomedPayloadNames = cms.vstring(), #Keep empty unless want to do groomed mass correction
    jettype             = cms.string('AK4JET'),
    jetPtMin            = cms.double(30),
    jetPtMax            = cms.double(1000000),
    jetAbsEtaMax        = cms.double(5.0),
    jetCSVDiscMin       = cms.double(-10000),
    jetCSVDiscMax       = cms.double(1.000),
    btaggedcsvlOP       = cms.double(0.605) , 
    btaggedcsvmOP       = cms.double(0.890) , 
    btaggedcsvtOP       = cms.double(0.970) , 
    IsJetIDLoose        = cms.bool(True),
    IsJetIDTight        = cms.bool(False),
    )

defaultBTaggedAK4JetSelectionParameters = defaultAK4JetSelectionParameters.clone(
    jettype             = cms.string('AK4JET'),
    jetPtMin            = cms.double(100),
    jetAbsEtaMax        = cms.double(2.4),
    jetCSVDiscMin       = cms.double(0.890),
    jetCSVDiscMax       = cms.double(1.000),
    )

defaultAK8JetSelectionParameters = defaultAK4JetSelectionParameters.clone( 
    JetIDParams         = defaultAK8JetIDParameters.clone(), 
    JetSubstrParams     = defaultJetSubstructureParameters.clone(),
    SubjetParams        = defaultSubjetParameters.clone(), 
    scaleJetP4          = cms.bool(False),
    scaledJetMass       = cms.double(125.0), 
    groomedPayloadNames = cms.vstring(),#'Summer15_25nsV6_MC_L2L3Residual_AK8PFchs.txt', 'Summer15_25nsV6_MC_L3Absolute_AK8PFchs.txt') , 
    jettype             = cms.string('AK8JET'),
    jetPtMin            = cms.double(300),
    jetAbsEtaMax        = cms.double(2.4),
    jetPtMax            = cms.double(1000000),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(1.0) ,
    jettau3Bytau2Min    = cms.double(0.0) ,
    jettau3Bytau2Max    = cms.double(1.0) ,
    jetMassMin          = cms.double(0.0) ,
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
    btaggedcsvlOP       = cms.double(0.605) , 
    btaggedcsvmOP       = cms.double(0.890) , 
    btaggedcsvtOP       = cms.double(0.970) , 
    )

defaultTJetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jettype             = cms.string('CMSTOPTAGGEDAK8JET'),
    jetPtMin            = cms.double(300),
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
    jetPtMin            = cms.double(300),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(0.5) ,
    jetPrunedMassMin    = cms.double(105) ,
    jetPrunedMassMax    = cms.double(145) ,
    jetMassMin          = cms.double(0.) ,
    jetMassMax          = cms.double(10000) ,
    subjetCSVMin        = cms.double(0.605) ,
    jetnSubJetsMin      = cms.double(2) ,
    jetnSubJetsMax      = cms.double(2) ,
    scaleJetP4          = cms.bool(False),
    scaledJetMass       = cms.double(125.0), 
    )

defaultWJetSelectionParameters = defaultHJetSelectionParameters.clone(
    jetPtMin            = cms.double(200),
    jetPrunedMassMin    = cms.double(65) ,
    jetPrunedMassMax    = cms.double(105) ,
    subjetCSVMin        = cms.double(0.000) ,
    )

defaultBTaggedAK8JetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jetCSVDiscMin       = cms.double(0.814),
    jetCSVDiscMax       = cms.double(1.000),
    )

