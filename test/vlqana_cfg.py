import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('outFileName', 'singleT.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('doPUReweightingOfficial', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do pileup reweighting using official recipe"
    )
options.setDefault('maxEvents', 1000)
options.parseArguments()

hltpaths = []
if options.isData:
    hltpaths = [
        "HLT_PFHT800_v"
        ]

process = cms.Process("VLQAna")

from inputFiles_cfi import * 
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      FileNames_TprimeBToTH_M1200
      )
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string(
      options.outFileName
      )
    )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("SingleTEvts.root"),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      "drop *",
      )
    )

from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.isData = options.isData 
process.evtcleaner.hltPaths = cms.vstring (hltpaths)  
process.evtcleaner.DoPUReweightingOfficial = cms.bool(options.doPUReweightingOfficial)  

process.load("Analysis.VLQAna.VLQAna_cfi") 

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *process.ana 
    *process.finalEvents
    )

process.outpath = cms.EndPath(process.out)

#open('dump.py','w').write(process.dumpPython())
