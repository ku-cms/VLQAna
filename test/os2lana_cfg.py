import FWCore.ParameterSet.Config as cms

process = cms.Process("OS2LAna")

from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      files_TprimeTprimeM700
      #files_qcd
      #files_DYM50
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(60000) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

process.load("Analysis.VLQAna.OS2LAna_cfi") 

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         "test_os2lana.root" 
         )
       )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("OS2LAnaEvts.root"),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      "drop *",
      )
    )

process.p = cms.Path(
    process.hbb
    *process.ana 
    )
process.outpath = cms.EndPath(process.out)
