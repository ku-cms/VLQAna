import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')

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

options.setDefault('maxEvents', 100)

options.parseArguments()

process = cms.Process("OS2LAna")

from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_1.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_10.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_11.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_12.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_13.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_14.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_15.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_16.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_17.root', 
      '/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_18.root', 

      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_1.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_10.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_100.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_101.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_102.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_103.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_104.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_105.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_106.root', 
      #'/store/user/oiorio/ttDM/samples/Aug2015/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/EDMNTUPLE_13Aug/150814_173628/0000/B2GEDMNtuple_107.root', 
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

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
