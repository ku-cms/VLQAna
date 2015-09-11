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

options.setDefault('maxEvents', 100)

options.parseArguments()

process = cms.Process("OS2LAna")

#from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_1.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_10.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_11.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_12.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_13.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_14.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_15.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_16.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_17.root', 
      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleMuon/SingleMuon_Run2015B-PromptReco-v74x_V5_v2/150813_191142/0000/B2GEDMNtuple_18.root', 

      #'/store/user/decosa/ttDM/CMSSW_74X_V5/SingleElectron/SingleElectron_Run2015B-PromptReco-v1_13Aug15/150813_204236/0000/B2GEDMNtuple_1.root'

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

      #/TT_TuneCUETP8M1_13TeV-powheg-pythia8/decosa-TT_Spring15DR74-Asympt50ns_13Aug_v2-209c08bb87cc8fc49a5fba4f844ae589/USER
      '/store/user/decosa/ttDM/CMSSW_74X_V5/TT_TuneCUETP8M1_13TeV-powheg-pythia8/TT_Spring15DR74-Asympt50ns_13Aug_v2/150814_041143/0000/B2GEDMNtuple_1.root'
      )
      )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.load("MyAnalysis.VLQAna.HbbCandidateProducer_cfi") 

from MyAnalysis.VLQAna.OS2LAna_cfi import ana

process.anaelel = ana.clone(
    isData = options.isData,
    hltPaths = cms.vstring (
        "HLT_Ele27_eta2p1_WP75_Gsf_v", 
        "HLT_Ele27_eta2p1_WPLoose_Gsf_v", 
        ), 
    )

process.anamumu = ana.clone(
    isData = options.isData, 
    hltPaths = cms.vstring (
        "HLT_IsoMu20_eta2p1_v",
        "HLT_Mu30_TkMu11_v", 
        "HLT_Mu45_eta2p1_v", 
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", 
        ), 
    )

process.ana = ana.clone(
    isData = options.isData, 
    hltPaths = cms.vstring (
        ""
        ), 
    )

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
from MyAnalysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone()
process.selectedEvents = eventCounter.clone()

process.p = cms.Path(
    process.allEvents
    *cms.ignore(process.ana) 
    *cms.ignore(process.anaelel)
    *cms.ignore(process.anamumu)
    * process.selectedEvents
    )
process.outpath = cms.EndPath(process.out)
