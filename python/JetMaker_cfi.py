import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.JetID_cfi import * 

###https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X#Supported_Algorithms_and_Operati
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
    jecUncPayloadName         = cms.string("Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt"), 
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
    )

defaultBTaggedAK4JetSelectionParameters = defaultAK4JetSelectionParameters.clone(
    jetPtMin            = cms.double(30),
    jetAbsEtaMax        = cms.double(2.4),
    jetCSVDiscMin       = cms.double(CSVv2M),
    )

defaultAK8CHSJetSelectionParameters = defaultAK4JetSelectionParameters.clone( 
    jettype                   = cms.string('AK8JET'),
    JetIDParams               = defaultAK8CHSJetIDParameters.clone(), 
    JetSubstrParams           = defaultCHSJetSubstructureParameters.clone(),
    SubjetParams              = defaultCHSSubjetParameters.clone(), 
    scaleJetP4                = cms.bool(False),
    scaledJetMass             = cms.double(125.0), 
    newJECPayloadNames        = cms.vstring(), 
    jecUncPayloadName         = cms.string("Spring16_25nsV6_MC_Uncertainty_AK8PFchs.txt"),
    jecAK8GroomedPayloadNames = cms.vstring(
      "Spring16_25nsV6_MC_L2Relative_AK8PFchs.txt", 
      "Spring16_25nsV6_MC_L3Absolute_AK8PFchs.txt"), 
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
    jetDoubleBMin             = cms.double(-100000) ,
    jetDoubleBMax             = cms.double(100000) ,
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
### From https://twiki.cern.ch/twiki/bin/view/CMS/JetTopTagging#13_TeV_working_points_CMSSW_7_6
defaultCHSTJetSelectionParameters = defaultAK8CHSJetSelectionParameters.clone(
    jetPtMin            = cms.double(400),
    jettau3Bytau2Min    = cms.double(0.0) ,
    jettau3Bytau2Max    = cms.double(0.50) ,
    jetSoftDropMassMin  = cms.double(105) ,
    jetSoftDropMassMax  = cms.double(220) ,
    subjetHighestCSVMin = cms.double(CSVv2L) ,
    )

defaultCHSHJetSelectionParameters = defaultAK8CHSJetSelectionParameters.clone(
    jetPtMin            = cms.double(300),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(0.6) ,
    jetPrunedMassMin    = cms.double(105) ,
    jetPrunedMassMax    = cms.double(135) ,
    subjetCSVMin        = cms.double(CSVv2L) ,
    )

defaultCHSWJetSelectionParameters = defaultCHSHJetSelectionParameters.clone(
    jetPtMin            = cms.double(200),
    jetPrunedMassMin    = cms.double(65) ,
    jetPrunedMassMax    = cms.double(105) ,
    )

defaultBTaggedCHSAK8JetSelectionParameters = defaultAK8CHSJetSelectionParameters.clone(
    jetCSVDiscMin       = cms.double(CSVv2M),
    )

defaultAK8PuppiJetSelectionParameters = defaultAK4JetSelectionParameters.clone( 
    jettype                   = cms.string('AK8JET'),
    JetIDParams               = defaultAK8PuppiJetIDParameters.clone(), 
    JetSubstrParams           = defaultPuppiJetSubstructureParameters.clone(),
    SubjetParams              = defaultPuppiSubjetParameters.clone(), 
    scaleJetP4                = cms.bool(False),
    scaledJetMass             = cms.double(125.0), 
    newJECPayloadNames        = cms.vstring(), 
    jecUncPayloadName         = cms.string("Spring16_25nsV6_MC_Uncertainty_AK8PFPuppi.txt"),
    jecAK8GroomedPayloadNames = cms.vstring(
      "Spring16_25nsV6_MC_L2Relative_AK8PFPuppi.txt", 
      "Spring16_25nsV6_MC_L3Absolute_AK8PFPuppi.txt"), 
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
    jetDoubleBMin             = cms.double(-100000) ,
    jetDoubleBMax             = cms.double(100000) ,
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
### From https://twiki.cern.ch/twiki/bin/view/CMS/JetTopTagging#13_TeV_working_points_CMSSW_7_6
defaultPuppiTJetSelectionParameters = defaultAK8PuppiJetSelectionParameters.clone(
    jetPtMin            = cms.double(400),
    jettau3Bytau2Min    = cms.double(0.0) ,
    jettau3Bytau2Max    = cms.double(0.46) ,
    jetSoftDropMassMin  = cms.double(105) ,
    jetSoftDropMassMax  = cms.double(210) ,
    subjetHighestCSVMin = cms.double(CSVv2L) ,
    )

defaultPuppiHJetSelectionParameters = defaultAK8PuppiJetSelectionParameters.clone(
    jetPtMin            = cms.double(300),
    jettau2Bytau1Min    = cms.double(0.0) ,
    jettau2Bytau1Max    = cms.double(0.6) ,
    jetSoftDropMassMin  = cms.double(105) ,
    jetSoftDropMassMax  = cms.double(135) ,
    subjetCSVMin        = cms.double(CSVv2L) ,
    )

defaultPuppiWJetSelectionParameters = defaultPuppiHJetSelectionParameters.clone(
    jetPtMin            = cms.double(200),
    jetPrunedMassMin    = cms.double(65) ,
    jetPrunedMassMax    = cms.double(105) ,
    )

defaultBTaggedPuppiAK8JetSelectionParameters = defaultAK8PuppiJetSelectionParameters.clone(
    jetCSVDiscMin       = cms.double(CSVv2M),
    )

