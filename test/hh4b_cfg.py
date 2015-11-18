import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')

options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('outFileName', 'hh4b.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.setDefault('maxEvents', -1)
options.parseArguments()

hltpaths = ['HLT_PFHT650']
if options.isData: 
  hltpaths = ['HLT_PFHT800']

process = cms.Process("hh4b")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from inputFiles_cfi import * 
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    FileNames_Radion1200
    #FileNames
    ) 
    )

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         options.outFileName
         )
       )

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.hltPaths = cms.vstring (hltpaths)  
process.evtcleaner.isData = options.isData 

process.load('Analysis.VLQAna.HH4b_cff') 
process.hh4b.jetHTaggedselParams.scaleJetP4 = cms.bool(False)
process.hh4b.jetHTaggedselParams.jettau2Bytau1Max = cms.double(0.75)
process.hh4b.jetHTaggedselParams.subjetCSVMin = cms.double(0.0) 

from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *process.hh4b
    * process.finalEvents
    )
