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
      files_TprimeBToTH_M1200_LH
      #files_QCD_HT2000toInf
      ) 
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from Analysis.VLQAna.VLQAna_cfi import *
process.anaA = ana.clone()
process.anaB = ana.clone(
    TJetSelParams = defaultTJetSelectionParameters.clone(
      jetMassMax          = cms.double(140) ,
      ), 
    )
process.anaC = ana.clone(
    TJetSelParams = defaultTJetSelectionParameters.clone(
      jetMassMax          = cms.double(140) ,
      ), 
      HJetSelParams = defaultHJetSelectionParameters.clone(
        subjetCSVMin        = cms.double(-10000000) ,
        subjetCSVMax        = cms.double(0.605) ,
        ), 
    )
process.anaD = ana.clone(
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
