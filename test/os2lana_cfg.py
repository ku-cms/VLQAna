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

options.register('runMuon', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "If running on muon channel (1), else on electron (0)"
    )

options.register ('TPrime', 1,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "if running over TT samples ")

options.register ('BPrime', 0,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "if running over BB samples ")

options.setDefault('maxEvents', 5000)

options.parseArguments()
print options

postName = ""
if options.runMuon: postName = "_mu"
else: postName = "_ele"

process = cms.Process("OS2LAna")

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkJob.limit=1
process.MessageLogger.cerr.ERROR = cms.untracked.PSet( limit = cms.untracked.int32(0) )

# VLQGenFilter
process.load("Analysis.VLQAna.genVLQSel_cfi")
from Analysis.VLQAna.genVLQSel_cfi import *

if not options.isData:
    if options.TPrime:
        process.GenInfo = cms.EDProducer("GenVLQSel", genParams.clone(momids = cms.vint32(8000001, -8000001))#TPrime 
                                         )
        process.source = cms.Source("PoolSource",
                                    fileNames = cms.untracked.vstring(
                'root://cms-xrd-global.cern.ch//store/user/devdatta/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V3/150703_110007/0000/B2GEDMNtuple_1.root',)
                                    )                                    
    elif options.BPrime:
        process.GenInfo = cms.EDProducer("GenVLQSel", genParams.clone(momids = cms.vint32(8000002, -8000002))#BPrime 
                                         )
        process.source = cms.Source("PoolSource", 
                                    fileNames = cms.untracked.vstring(
                'root://cms-xrd-global.cern.ch//store/group/phys_b2g/vorobiev/BprimeBprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V61/151002_170055/0000/B2GEDMNtuple_1.root',)
                                    ) 
    else:    
        process.source = cms.Source("PoolSource",
                                    fileNames = cms.untracked.vstring(
                #'root://cms-xrd-global.cern.ch//store/group/phys_b2g/vorobiev/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V3_1/150819_140856/0000/B2GEDMNtuple_3.root',
                'root://cms-xrd-global.cern.ch//store/user/devdatta/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V3/150703_105335/0000/B2GEDMNtuple_1.root', 
                )
            )
else:#running over data
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
            #'root://cms-xrd-global.cern.ch//store/group/phys_b2g/vorobiev/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V3_1/150819_140856/0000/B2GEDMNtuple_3.root',
           
            )
                                )     

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from Analysis.VLQAna.OS2LAna_cfi import ana

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         options.outFileName
         )
       )

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

## Event counter
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone()
process.selectedEvents = eventCounter.clone()

##processes to run
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("OS2LAnaEvts"+postName+".root"),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      #"drop *",
      "keep *",
      "drop *_generator_*_*",
      "drop *_genPart_*_*",
      "drop *_TriggerResults_*_*",
      "drop *_TriggerUserData_*_*",
      "drop *_eventShape*_*_*",
      "drop *_centrality_*_*", 
      "keep *_GenInfo_*_*",
      #"keep *_*_puBX_*", 
      #"keep *_*_puNInt_*",
      #"keep *_eventInfo_*_*",
      #"keep *_eventUserData_*_*",
      )
    )
if options.runMuon:
    process.out.outputCommands += [
        "drop *_electrons_*_*",# sometimes gives LogicError
        "drop *_anaelel_*_*",
        "drop *_*_goodElectronsIdxs_*",
        "drop *_*_goodElectrons_*",
        ]
    process.p = cms.Path(
        process.allEvents
        *cms.ignore(process.anaelel)
        *process.anamumu
        *process.GenInfo
        *process.selectedEvents
        )
else:
    process.out.outputCommands += [
        "drop *_muons_*_*", 
        "drop *_anamumu_*_*",
        "drop *_*_goodMuonsIdxs_*",
        "drop *_*_goodMuons_*",
        ]
    process.p = cms.Path(
        process.allEvents
        *cms.ignore(process.anamumu)
        *process.anaelel
        *process.GenInfo
        *process.selectedEvents
        )

process.outpath = cms.EndPath(process.out)
