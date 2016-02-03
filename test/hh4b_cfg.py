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

options.setDefault('maxEvents', -1)
options.parseArguments()

hltpaths = ['HLT_PFHT650']
if options.isData: 
    hltpaths = ['HLT_PFHT650', 'HLT_PFHT800', 'HLT_PFHT650_WideJetMJJ900DEtaJJ1p5', 'HLT_PFHT650_WideJetMJJ950DEtaJJ1p5', 'HLT_AK8PFHT700_TrimR0p1PT0p03Mass50', 'HLT_AK8PFJet360_TrimMass30']
    options.doBTagSFUnc = False 
    options.jerShift = 0 

process = cms.Process("hh4b")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from inputFiles_cfi import * 
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    FileNames_BG1000
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
process.hh4b.jetHTaggedselParams.subjetCSVMin = cms.double(-1000.) 
#process.hh4b.doBTagSFUnc = options.doBTagSFUnc
process.hh4b.jetHTaggedselParams.jecShift = options.jecShift 
process.hh4b.jetHTaggedselParams.jerShift = options.jerShift 
if options.isData:
  process.hh4b.jetHTaggedselParams.jetAK8selParams.newJECPayloadNames.append("Summer15_25nsV7_DATA/Summer15_25nsV7_DATA_L2L3Residual_AK8PFchs.txt")
  process.hh4b.jetHTaggedselParams.jetAK8selParams.jecUncPayloadName = cms.string("Summer15_25nsV7_DATA/Summer15_25nsV7_DATA_Uncertainty_AK8PFchs.txt")
  process.hh4b.jetHTaggedselParams.jecAK8GroomedPayloadNames.append("Summer15_25nsV7_DATA/Summer15_25nsV7_DATA_L2L3Residual_AK8PFchs.txt") 

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
