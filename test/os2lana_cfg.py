import FWCore.ParameterSet.Config as cms

process = cms.Process("OS2LAna")

from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      #'file:../../B2GAnaFW/test/B2GEDMNtuple.root'
#/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/devdatta-B2GAnaFW_Run2Sping15_25ns-93296e97710faac6591502ff11c71e47/USER
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_1.root', 
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_2.root'
#/TprimeBToTH_M-1200_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/devdatta-B2GAnaFW_Run2Sping15_25ns-71ae93134bf811066d2681edbf0174df/USER
      #'/store/user/devdatta/TprimeBToTH_M-1200_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150623_161611/0000/B2GEDMNtuple_2.root', 
      #'/store/user/devdatta/TprimeBToTH_M-1200_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150623_161611/0000/B2GEDMNtuple_5.root' 
      files_TprimeTprimeM700
      #files_qcd
      #files_DYM50
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50000) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

process.load("Analysis.VLQAna.OS2LAna_cfi") 

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         "test_os2lana.root" 
         )
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
