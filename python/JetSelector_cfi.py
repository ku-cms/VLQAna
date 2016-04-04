import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.JetID_cfi import * 

CSVv2L = 0.460 
CSVv2M = 0.800 
CSVv2T = 0.935 

defaultAK4JetSelectionParameters = cms.PSet(
    jettype                   = cms.string('AK4JET'),
    JetIDParams               = defaultAK4JetIDParameters, 
    JetSubstrParams           = cms.PSet(), 
    SubjetParams              = cms.PSet(),
    scaleJetP4                = cms.bool(False),
    scaledJetMass             = cms.double(125.0), 
    newJECPayloadNames        = cms.vstring(), 
    jecUncPayloadName         = cms.string(""), 
    jecAK8GroomedPayloadNames = cms.vstring(), 
    jecShift                  = cms.double(0), 
    jerShift                  = cms.int32(1), 
    jetPtMin                  = cms.double(30),
    jetPtMax                  = cms.double(1000000),
    jetAbsEtaMax              = cms.double(5.0),
    jetCSVDiscMin             = cms.double(-10000),
    jetCSVDiscMax             = cms.double(10000),
    btaggedcsvlOP             = cms.double(CSVv2L) , 
    btaggedcsvmOP             = cms.double(CSVv2M) , 
    btaggedcsvtOP             = cms.double(CSVv2T) , 
    IsJetIDLoose              = cms.bool(True),
    IsJetIDTight              = cms.bool(False),
    )

defaultBTaggedAK4JetSelectionParameters = defaultAK4JetSelectionParameters.clone(
    jetPtMin            = cms.double(30),
    jetAbsEtaMax        = cms.double(2.4),
    jetCSVDiscMin       = cms.double(0.890),
    )

defaultAK8JetSelectionParameters = defaultAK4JetSelectionParameters.clone( 
    jettype                   = cms.string('AK8JET'),
    JetIDParams               = defaultAK8JetIDParameters.clone(), 
    JetSubstrParams           = defaultJetSubstructureParameters.clone(),
    SubjetParams              = defaultSubjetParameters.clone(), 
    scaleJetP4                = cms.bool(False),
    scaledJetMass             = cms.double(125.0), 
    newJECPayloadNames        = cms.vstring(), 
    jecUncPayloadName         = cms.string(""),
    jecAK8GroomedPayloadNames = cms.vstring(
      "Fall15_25nsV2_MC_L2Relative_AK8PFchs.txt", 
      "Fall15_25nsV2_MC_L3Absolute_AK8PFchs.txt"), 
    jecShift                  = cms.double(0), 
    jerShift                  = cms.int32(1), 
    jetPtMin                  = cms.double(200),
    jetAbsEtaMax              = cms.double(2.4),
    jetPtMax                  = cms.double(1000000),
    jettau2Bytau1Min          = cms.double(0.0) ,
    jettau2Bytau1Max          = cms.double(1.0) ,
    jettau3Bytau2Min          = cms.double(0.0) ,
    jettau3Bytau2Max          = cms.double(1.0) ,
    jetMassMin                = cms.double(-1000000) ,
    jetMassMax                = cms.double(1000000) ,
    jetPrunedMassMin          = cms.double(0.0) ,
    jetPrunedMassMax          = cms.double(1000000) ,
    jetTrimmedMassMin         = cms.double(0.0) ,
    jetTrimmedMassMax         = cms.double(1000000) ,
    jetSoftDropMassMin        = cms.double(0.0) ,
    jetSoftDropMassMax        = cms.double(1000000) ,
    subjetMassMin             = cms.double(-1000000) ,
    subjetCSVMin              = cms.double(-1000000) ,
    subjetCSVMax              = cms.double(1000000) ,
    subjetHighestCSVMin       = cms.double(-1000000) ,
    subjetHighestCSVMax       = cms.double(1000000) ,
    btaggedcsvlOP             = cms.double(CSVv2L) , 
    btaggedcsvmOP             = cms.double(CSVv2M) , 
    btaggedcsvtOP             = cms.double(CSVv2T) , 
    )

### Corresponds to e(B) = 0.1% SD WP1 plus subjet b-tagging loose OP
### From https://twiki.cern.ch/twiki/bin/view/CMS/JetTopTagging#13_TeV_working_points
defaultTJetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jetPtMin            = cms.double(400),
    jettau3Bytau2Min    = cms.double(0.0) ,
    jettau3Bytau2Max    = cms.double(0.61) ,
    jetSoftDropMassMin  = cms.double(110) ,
    jetSoftDropMassMax  = cms.double(210) ,
    subjetHighestCSVMin = cms.double(0.760) ,
    )

defaultHJetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jetPtMin            = cms.double(300),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(0.6) ,
    jetPrunedMassMin    = cms.double(105) ,
    jetPrunedMassMax    = cms.double(135) ,
    subjetCSVMin        = cms.double(CSVv2L) ,
    )

defaultWJetSelectionParameters = defaultHJetSelectionParameters.clone(
    jetPtMin            = cms.double(200),
    jetPrunedMassMin    = cms.double(65) ,
    jetPrunedMassMax    = cms.double(105) ,
    )

defaultBTaggedAK8JetSelectionParameters = defaultAK8JetSelectionParameters.clone(
    jetCSVDiscMin       = cms.double(CSVv2M),
    )

