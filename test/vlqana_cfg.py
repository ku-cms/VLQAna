import FWCore.ParameterSet.Config as cms

process = cms.Process("VLQAna")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      #'file:../../B2GAnaFW/test/B2GEDMNtuple.root'
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_1.root', 
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_2.root', 
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_3.root', 
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_4.root', 
      #'/store/user/devdatta/TprimeBToTH_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Sping15_25ns/150618_090136/0000/B2GEDMNtuple_5.root', 

      '/store/user/rappocc/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_b2ganafw741_ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150521_223353/0000/B2GEDMNtuple_1.root', 
      '/store/user/rappocc/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_b2ganafw741_ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150521_223353/0000/B2GEDMNtuple_2.root', 
      '/store/user/rappocc/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_b2ganafw741_ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150521_223353/0000/B2GEDMNtuple_3.root', 
      '/store/user/rappocc/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_b2ganafw741_ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150521_223353/0000/B2GEDMNtuple_4.root', 
      '/store/user/rappocc/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_b2ganafw741_ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150521_223353/0000/B2GEDMNtuple_5.root', 
      '/store/user/rappocc/ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_b2ganafw741_ZprimeToTT_M-2000_W-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150521_223353/0000/B2GEDMNtuple_6.root', 
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

process.load("Analysis.VLQAna.VLQAna_cfi") 
process.ana.BTaggedAK4JetSelParams.jetCSVDiscMin = cms.double(0.423) 

process.TFileService = cms.Service("TFileService",
       fileName = cms.string("SingleTprimeAna_LooseBJet_Run2Spring15_ZprimeToTT_M-2000_W-200.root")
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
