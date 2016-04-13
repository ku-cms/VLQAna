import FWCore.ParameterSet.Config as cms

process = cms.Process("VLQGen")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.MessageLogger.cerr.FwkReport.reportEvery = 5
process.MessageLogger.cerr.FwkJob.limit=1
process.MessageLogger.cerr.ERROR = cms.untracked.PSet( limit = cms.untracked.int32(0) )

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

###############################
####### Parameters ############
###############################
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('python')
options.register ('TPrime',
                  1,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "if running over TT samples (1) else running over BB samples(0)")
options.parseArguments()

print options

process.load("Analysis.VLQAna.genVLQSel_cfi") 
from Analysis.VLQAna.genVLQSel_cfi import *  

if options.TPrime:
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/user/devdatta/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V3/150703_110007/0000/B2GEDMNtuple_1.root',)
                                )
    process.GenInfo = cms.EDProducer("GenVLQSel",
                                     genParams.clone(momids = cms.vint32(8000001, -8000001))#TPrime 
                                     )
else:
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/group/phys_b2g/vorobiev/BprimeBprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V61/151002_170055/0000/B2GEDMNtuple_1.root',)
                                )
    process.GenInfo = cms.EDProducer("GenVLQSel",
                                     genParams.clone(momids = cms.vint32(8000002, -8000002))#BPrime 
                                     )

process.p0 = cms.Path(process.GenInfo)

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('genVLQInfo.root'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p0') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_GenInfo*_*_*',
                                                                      )
                               )

process.e = cms.EndPath(process.out)
