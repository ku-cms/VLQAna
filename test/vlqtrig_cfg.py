import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('outFileName', 'singleT_Trig',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('hltORAND', 'AND',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "OR or AND HLT paths?"
    )
options.register('cleanEvents', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Clean events using EventCleaner?"
    )
options.register('doPUReweightingOfficial', False,
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
options.register('HTMin', 500,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "Minimum HT"
    )
options.register('storePreselEvts', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Store pre-selected events after pre-selection", 
    )
options.register('doPreselOnly', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Only run pre-selections"
    )
options.register('storeLHEWts', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Store LHE wts?"
    )
options.register('FileNames', 'FileNames',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Name of list of input files"
    )

options.setDefault('maxEvents', -1000)
options.parseArguments()

hltpaths = ["HLT_PFHT650_v"]
hltpathstest = ["HLT_PFHT650_v","HLT_PFHT800_v"]

if options.isData:
    options.doBTagSFUnc = False 
    options.jerShift = 0 
    options.doPUReweightingOfficial=False 
    options.storeLHEWts=False

HTMin=500
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

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.hltORAND = cms.string (options.hltORAND)  
process.evtcleaner.hltPaths = cms.vstring (hltpaths)  
process.evtcleaner.cleanEvents = cms.bool(options.cleanEvents)
process.evtcleaner.isData = options.isData 
process.evtcleaner.DoPUReweightingOfficial = options.doPUReweightingOfficial
process.evtcleaner.storeLHEWts = options.storeLHEWts

process.evtcleanertest = process.evtcleaner.clone(
    hltPaths = cms.vstring (hltpathstest)
    )

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

process.anatest = process.ana.clone(
    runno                      = cms.InputTag("evtcleanertest","runno"), 
    lumisec                    = cms.InputTag("evtcleanertest","lumisec"), 
    evtno                      = cms.InputTag("evtcleanertest","evtno"), 
    isData                     = cms.InputTag("evtcleanertest","isData"), 
    hltdecision                = cms.InputTag("evtcleanertest","hltdecision"), 
    evttype                    = cms.InputTag("evtcleanertest","evttype"),
    evtwtGen                   = cms.InputTag("evtcleanertest","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleanertest","evtwtPV"),
    evtwtPVLow                 = cms.InputTag("evtcleanertest","evtwtPVLow"),
    evtwtPVHigh                = cms.InputTag("evtcleanertest","evtwtPVHigh"),
    npv                        = cms.InputTag("evtcleanertest","npv"),
    npuTrue                    = cms.InputTag("evtcleanertest","npuTrue"),
    htHat                      = cms.InputTag("evtcleanertest","htHat"),
    lhewtids                   = cms.InputTag("evtcleanertest","lhewtids"),
    lhewts                     = cms.InputTag("evtcleanertest","lhewts"), 
    )

from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.cleanedEventstest = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)
process.finalEventstest = eventCounter.clone(isData=options.isData)

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *process.ana 
    *process.finalEvents
    )

process.ptest = cms.Path(
    process.allEvents
    *process.evtcleanertest
    *process.cleanedEventstest
    *process.anatest
    *process.finalEventstest
    )

process.out = cms.OutputModule("PoolOutputModule",
        SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('evtcleaner')),
            )

process.schedule = cms.Schedule(process.p,process.ptest)

#process.outpath = cms.EndPath(process.out)

open('dump.py','w').write(process.dumpPython())
