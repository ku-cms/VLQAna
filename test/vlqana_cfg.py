import FWCore.ParameterSet.Config as cms

process = cms.Process("VLQAna")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      'file:../../B2GAnaFW/test/B2GEDMNtuple.root'
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

process.load("Analysis.VLQAna.VLQAna_cfi") 

process.TFileService = cms.Service("TFileService",
       fileName = cms.string("SingleTprimeAnaMVA.root")
       )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("SingleTprimeAnaEvtsMVA.root"),
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
