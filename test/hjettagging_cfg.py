import FWCore.ParameterSet.Config as cms

process = cms.Process("HJetTagging")
from inputFiles_cfi import * 
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      fileNames_TprimeBToTH_M1200
      )
    )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 
process.load("Analysis.VLQAna.HJetTagging_cfi") 

process.TFileService = cms.Service("TFileService",
    fileName = cms.string(
      "hjettagging.root"
      )
    )

process.p = cms.Path(
    process.hbb
    *process.hjets
    )
