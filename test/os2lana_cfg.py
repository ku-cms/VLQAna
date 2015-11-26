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
    sys.exit("Wrong Z decay mode option chosen. Choose either 'zmumu' or 'zelel'") 

process = cms.Process("OS2LAna")

from inputFiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    #FileNames
    Filenames_DoubleEle_CR_Zelel 
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
