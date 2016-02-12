import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('zdecaymode', 'zmumu',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Z->mumu or Z->elel? Choose: 'zmumu' or 'zelel'"
    )
options.register('outFileName', 'os2lana.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('doPUReweightingOfficial', True,
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
options.register('signalType', '',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Select one of EvtType_MC_tZtZ, EvtType_MC_tZtH, EvtType_MC_tZbW, EvtType_MC_tHtH, EvtType_MC_tHbW, EvtType_MC_bWbW, EvtType_MC_bZbZ, EvtType_MC_bZbH, EvtType_MC_bZtW, EvtType_MC_bHbH, EvtType_MC_bHtW, EvtType_MC_tWtW" 
    )
options.register('applyLeptonSFs', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Apply lepton SFs to the MC"
    )
options.setDefault('maxEvents', 50)
options.parseArguments()
print options

hltpaths = []
if options.isData:
  options.filterSignal = False 
  options.signalType = "" 
  options.applyLeptonSFs = False 
  if options.zdecaymode == "zmumu":
    hltpaths = [
        "HLT_DoubleIsoMu17_eta2p1_v", 
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
        "HLT_DoubleMu8_Mass8_PFHT300_v",
        ]
  elif options.zdecaymode == "zelel":
    hltpaths = [
        "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v",
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v",
        "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v"
        ]
  else:
    sys.exit("!!!Error: Wrong Z decay mode option chosen. Choose either 'zmumu' or 'zelel'!!!") 

if options.filterSignal == True and len(options.signalType) == 0:
  sys.exit("!!!Error: Cannot keep signalType empty when filterSignal switched on!!!")  

process = cms.Process("OS2LAna")

from inputFiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
   '/store/group/lpcbprime/noreplica/skhalil/B2GEDMNtuplesSkim_CR_Zmumu_20Nov/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_powheg-pythia8_ext3_25ns_CR_Zmumu/151126_084215/0000/SkimmedB2GEdmNtuples_1.root',
    #FileNames
    #FileNames_TT_M1200
    #'root://grid143.kfki.hu//store/group/phys_b2g/B2GAnaFW/Skims/CR_Zelel/DoubleEG/Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zelel_24Nov2015/151124_141440/0000/SkimmedB2GEdmNtuples_1.root'
    ) 
    )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
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
    signalType = cms.string(options.signalType),
    applyLeptonSFs = cms.bool(options.applyLeptonSFs),
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
    signalType = cms.string(options.signalType),
    applyLeptonSFs = cms.bool(options.applyLeptonSFs),
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
    #*process.anaBoosted ##comment it
    #*process.vlqcands
    * process.finalEvents
    )

#process.schedule = cms.Schedule(process.p)

#open('dump.py','w').write(process.dumpPython())
