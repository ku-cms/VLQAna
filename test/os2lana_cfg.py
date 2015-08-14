import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')

options.register('maxEvts',
    100,# default value: process all events
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    'Number of events to process')

options.register('outFileName', 'os2lana.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )

options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )

options.register('doHLTEff', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do HLT efficiency plots?"
    )

options.parseArguments()

process = cms.Process("OS2LAna")

from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
     '/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_10Aug/150810_160018/0000/B2GEDMNtuple_1.root',     
     #'/store/user/decosa/ttDM/CMSSW_74X_V6/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_1/150810_135051/0000/B2GEDMNtuple_1.root'
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvts) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

process.load("Analysis.VLQAna.OS2LAna_cfi") 
process.ana.isData = options.isData
process.ana.doHLTEff = options.doHLTEff

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         options.outFileName
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

## Event counter
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone()
process.selectedEvents = eventCounter.clone()

process.p = cms.Path(
    #process.hbb*
    process.allEvents
    *process.ana 
    * process.selectedEvents
    )
process.outpath = cms.EndPath(process.out)
