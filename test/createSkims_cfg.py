import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('outFileName', 'os2lana.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('doPUReweightingOfficial', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do pileup reweighting using official recipe"
    )
options.register('doPUReweightingNPV', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do pileup reweighting based on NPV"
    )
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
<<<<<<< HEAD

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

=======
options.register('zdecaymode', '',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Z->mumu or Z->elel? Choose: 'zmumu' or 'zelel'"
    )
options.setDefault('maxEvents', 1000)
>>>>>>> 4ed3460b8c30455260fa4843ac1c0ce3e468beef
options.parseArguments()
print options

postName = ""
if options.runMuon: postName = "_mu"
else: postName = "_ele"

hltpaths = []
if options.isData:
  if options.zdecaymode == "zmumu":
    hltpaths = [
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
        ]
  elif options.zdecaymode == "zelel":
    hltpaths = [
        "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v",
        "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v"
        ]
  else:
    sys.exit("Wrong Z decay mode option chosen. Choose either 'zmumu' or 'zelel'") 

process = cms.Process("OS2LAna")

<<<<<<< HEAD
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
=======
from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    'root://eoscms.cern.ch//eos/cms/store/group/phys_b2g/B2GAnaFW/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/B2GAnaFW_v74x_v6p1_25ns/150930_172851/0000/B2GEDMNtuple_8.root'
    #fileNamess_TT_M800_Spring15_25ns
    #files_DY_M50
    #files_doubleMuon_Run2015D
    ) 
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.isData = options.isData 
process.evtcleaner.hltPaths = cms.vstring (hltpaths)  
process.evtcleaner.DoPUReweightingNPV = cms.bool(options.doPUReweightingNPV)  

from Analysis.VLQAna.OS2LAna_cfi import * 
process.anaBoosted = ana.clone(
    DoPUReweightingNPV = cms.bool(options.doPUReweightingNPV),
>>>>>>> 4ed3460b8c30455260fa4843ac1c0ce3e468beef
    )

process.ana = process.anaBoosted.clone()
process.ana.BoostedZCandParams.ptMin = cms.double(0.)

<<<<<<< HEAD
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
=======
if not options.isData:
  process.anaBoosted.elselParams.useVID = cms.bool(False)
  process.ana.elselParams.useVID = cms.bool(False)

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         options.outFileName
         )
       )

## Event counters
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *cms.ignore(process.ana)
    *cms.ignore(process.anaBoosted)
    * process.finalEvents
    )

#open('dump.py','w').write(process.dumpPython())
>>>>>>> 4ed3460b8c30455260fa4843ac1c0ce3e468beef
