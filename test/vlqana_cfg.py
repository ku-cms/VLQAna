import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('outFileName', 'singleT',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('doPUReweightingOfficial', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do pileup reweighting using official recipe"
    )
options.register('doBTagSFUnc', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Apply b-tag SF uncertainties"
    )
options.register('jecShift', 0,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "JEC shift"
    )
options.register('jerShift', 1,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "JER shift"
    )
options.register('topTagtau32', 0.54,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "Top-tagging tau32 cut"
    )
options.register('topTagBDisc', 0.79,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "Top-tagging b-discriminator cut"
    )
options.register('HTMin', 1000,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "Minimum HT"
    )
options.register('storePreselEvts', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Store pre-selected events after pre-selection", 
    )
options.register('doPreselOnly', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Only run pre-selections"
    )
options.register('storeLHEWts', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Store LHE wts?"
    )
options.register('FileNames', 'FileNames_BG2000',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Name of list of input files"
    )

options.setDefault('maxEvents', -1000)
options.parseArguments()

hltpaths = ["HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v"]
hltpaths_PFHT800 = ["HLT_PFHT800_v"]
hltpaths_test = ["HLT_PFHT800_v","HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v"]
hltpaths_loose = ["HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v"]
if options.isData:
    options.doBTagSFUnc = False 
    options.jerShift = 0 
    options.doPUReweightingOfficial=False 
    options.storeLHEWts=False

HTMin=1000
if options.storePreselEvts:
  HTMin = options.HTMin

process = cms.Process("VLQAna")

from inputFiles_cfi import * 
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      FileNames[options.FileNames]
      )
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string(
      options.outFileName+".root"
      )
    )

#process.out = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string("Events_"+options.outFileName+".root"),
#    SelectEvents = cms.untracked.PSet(
#      SelectEvents = cms.vstring('p')
#      ),
#    outputCommands = cms.untracked.vstring(
#      "drop *",
#      )
#    )

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.hltPaths = cms.vstring (hltpaths_loose)  
process.evtcleaner.isData = options.isData 
process.evtcleaner.DoPUReweightingOfficial = options.doPUReweightingOfficial
process.evtcleaner.storeLHEWts = options.storeLHEWts

process.evtcleanerPFHT800.hltPaths = cms.vstring (hltpaths_test)  
process.evtcleanerPFHT800.isData = options.isData 
process.evtcleanerPFHT800.DoPUReweightingOfficial = options.doPUReweightingOfficial
process.evtcleanerPFHT800.storeLHEWts = options.storeLHEWts

process.load("Analysis.VLQAna.VLQAna_cfi") 
process.ana.doBTagSFUnc = options.doBTagSFUnc
process.ana.jetAK4selParams.jecShift = options.jecShift 
process.ana.jetAK4selParams.jerShift = options.jerShift 
process.ana.jetAK8selParams.jecShift = options.jecShift 
process.ana.jetAK8selParams.jerShift = options.jerShift 
process.ana.jetHTaggedselParams.jecShift = options.jecShift 
process.ana.jetHTaggedselParams.jerShift = options.jerShift 
process.ana.jetTopTaggedselParams.jecShift = options.jecShift 
process.ana.jetTopTaggedselParams.jerShift = options.jerShift 
process.ana.jetAntiHTaggedselParams.jecShift = options.jecShift 
process.ana.jetAntiHTaggedselParams.jerShift = options.jerShift 
process.ana.jetTopTaggedselParams.jettau3Bytau2Max = options.topTagtau32
process.ana.jetTopTaggedselParams.subjetHighestCSVMin = options.topTagBDisc
process.ana.storePreselEvts = options.storePreselEvts
process.ana.doPreselOnly = options.doPreselOnly
process.ana.HTMin = HTMin

process.anaPFHT800.doBTagSFUnc = options.doBTagSFUnc
process.anaPFHT800.jetAK4selParams.jecShift = options.jecShift 
process.anaPFHT800.jetAK4selParams.jerShift = options.jerShift 
process.anaPFHT800.jetAK8selParams.jecShift = options.jecShift 
process.anaPFHT800.jetAK8selParams.jerShift = options.jerShift 
process.anaPFHT800.jetHTaggedselParams.jecShift = options.jecShift 
process.anaPFHT800.jetHTaggedselParams.jerShift = options.jerShift 
process.anaPFHT800.jetTopTaggedselParams.jecShift = options.jecShift 
process.anaPFHT800.jetTopTaggedselParams.jerShift = options.jerShift 
process.anaPFHT800.jetAntiHTaggedselParams.jecShift = options.jecShift 
process.anaPFHT800.jetAntiHTaggedselParams.jerShift = options.jerShift 
process.anaPFHT800.jetTopTaggedselParams.jettau3Bytau2Max = options.topTagtau32
process.anaPFHT800.jetTopTaggedselParams.subjetHighestCSVMin = options.topTagBDisc
process.anaPFHT800.storePreselEvts = options.storePreselEvts
process.anaPFHT800.doPreselOnly = options.doPreselOnly
process.anaPFHT800.HTMin = HTMin

from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)
process.allEventsTestHLT = eventCounter.clone(isData=options.isData)
process.cleanedEventsTestHLT = eventCounter.clone(isData=options.isData)
process.finalEventsTestHLT = eventCounter.clone(isData=options.isData)


process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *process.ana 
    *process.finalEvents
    )
process.p2 = cms.Path(
    process.evtcleanerPFHT800
    *process.anaPFHT800
    *process.finalEventsTestHLT
    ) 
#process.outpath = cms.EndPath(process.out)

open('dump.py','w').write(process.dumpPython())
