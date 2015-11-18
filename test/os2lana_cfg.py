import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('zdecaymode', '',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Z->mumu or Z->elel? Choose: 'zmumu' or 'zelel'"
    )
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
options.register('filterSignal', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Select only tZtt or bZbZ modes"
    )
options.setDefault('maxEvents', 1000)
options.parseArguments()

hltpaths = []
if options.isData:
  options.filterSignal = False 
  if options.zdecaymode == "zmumu":
    hltpaths = [
        "HLT_DoubleIsoMu17_eta2p1_v"
        ]
  elif options.zdecaymode == "zelel":
    hltpaths = [
        "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v"
        ]
  else:
    sys.exit("Wrong Z decay mode option chosen. Choose either 'zmumu' or 'zelel'") 

process = cms.Process("OS2LAna")

from inputFiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    #'root://grid143.kfki.hu//store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v3/151111_093309/0000/B2GEDMNtuple_37.root'
    #fileNames_TT_M800_Spring15_25ns
    #FileNames
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_1.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_10.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_100.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_101.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_102.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_103.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_104.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_105.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_106.root',
    '/store/user/decosa/ttDM/CMSSW_7_4_15/SingleMuon/SingleMu_Run2015D_miniAODv2_v2_13Nov/151113_155244/0000/B2GEDMNtuple_107.root',
    ) 
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.isData = options.isData 
process.evtcleaner.hltPaths = cms.vstring (hltpaths)  
process.evtcleaner.DoPUReweightingNPV = cms.bool(options.doPUReweightingNPV)  
process.evtcleaner.DoPUReweightingOfficial = cms.bool(options.doPUReweightingOfficial)  

from Analysis.VLQAna.OS2LAna_cfi import * 

### Low pt Z candidate with low pt jets 
process.ana = ana.clone(
    filterSignal = cms.bool(options.filterSignal),
    )
process.ana.elselParams.useVID = cms.bool(options.isData)
process.ana.BoostedZCandParams.ptMin = cms.double(0.)
process.ana.jetAK8selParams.jetPtMin = cms.double(100)
process.ana.jetAK4BTaggedselParams.jetPtMin = cms.double(40)
if not options.isData:
  process.ana.jetAK8selParams.groomedPayloadNames.extend(['Summer15_25nsV6_MC_L2L3Residual_AK8PFchs.txt', 'Summer15_25nsV6_MC_L3Absolute_AK8PFchs.txt']) ,

### Boosted Z candidate
process.anaBoosted = ana.clone(
    filterSignal = cms.bool(options.filterSignal),
    )
process.anaBoosted.elselParams.useVID = cms.bool(options.isData)
if not options.isData:
  process.anaBoosted.jetAK8selParams.groomedPayloadNames.extend(['Summer15_25nsV6_MC_L2L3Residual_AK8PFchs.txt', 'Summer15_25nsV6_MC_L3Absolute_AK8PFchs.txt']) ,



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

process.load("Analysis.VLQAna.VLQCandProducer_cff")

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *cms.ignore(process.ana)
    #*cms.ignore(process.anaBoosted+process.vlqcands)
    *process.anaBoosted
    *process.vlqcands
    * process.finalEvents
    )

#process.schedule = cms.Schedule(process.p)

#open('dump.py','w').write(process.dumpPython())
