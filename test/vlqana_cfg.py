from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')

options.register('outFileName', 'singleT.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )

options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )

options.setDefault('maxEvents', 100)

options.parseArguments()

import FWCore.ParameterSet.Config as cms

process = cms.Process("VLQAna")

from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      #files_TprimeBToTH_M800_LH
      files_TprimeBToTH_M1200_LH
      #files_QCD_HT2000toInf
      ) 
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from Analysis.VLQAna.VLQAna_cfi import *
process.anaA = ana.clone()
process.anaB = ana.clone(
    TJetSelParams = defaultTJetSelectionParameters.clone(
      jettau3Bytau2Min    = cms.double(0.70) ,
      jettau3Bytau2Max    = cms.double(1.00) ,
      jetMinMassMin       = cms.double(0.0) ,
      jetMinMassMax       = cms.double(50.) ,
      jetMassMin          = cms.double(0) ,
      jetMassMax          = cms.double(140) ,
      ), 
    )
process.anaC = ana.clone(
    HJetSelParams = defaultHJetSelectionParameters.clone(
      subjetCSVMin        = cms.double(-10000000) ,
      subjetCSVMax        = cms.double(0.605) ,
      ), 
    )
process.anaD = process.anaB.clone(
      HJetSelParams = defaultHJetSelectionParameters.clone(
        subjetCSVMin        = cms.double(-10000000) ,
        subjetCSVMax        = cms.double(0.605) ,
        ), 
    )

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(options.outFileName)
       )

process.p = cms.Path(
    cms.ignore(process.anaA) *
    cms.ignore(process.anaB) *
    cms.ignore(process.anaC) *
    cms.ignore(process.anaD) 
    )
