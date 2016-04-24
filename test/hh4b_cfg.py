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
options.register('doPUReweightingOfficial', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do pileup reweighting using official recipe"
    )
options.register('storeLHEWts', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Store LHE wts?"
    )
options.register('FileNames', 'FileNames_QCD_HT1000to1500',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Name of list of input files"
    )
options.register('printEvtNo', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Print event numbers"
    )

options.setDefault('maxEvents', -1)
options.parseArguments()

hltpaths = ['HLT_PFHT650', 'HLT_PFHT800', 'HLT_PFHT650_WideJetMJJ900DEtaJJ1p5', 'HLT_PFHT650_WideJetMJJ950DEtaJJ1p5', 'HLT_AK8PFHT700_TrimR0p1PT0p03Mass50', 'HLT_AK8PFJet360_TrimMass30']
#hltpaths = ['HLT_PFHT800', 'HLT_PFHT650_WideJetMJJ900DEtaJJ1p5', 'HLT_PFHT650_WideJetMJJ950DEtaJJ1p5', 'HLT_AK8PFHT700_TrimR0p1PT0p03Mass50', 'HLT_AK8PFJet360_TrimMass30']
if options.isData: 
    options.doBTagSFUnc = False 
    options.jerShift = 0 
    options.doPUReweightingOfficial=False 
    options.storeLHEWts=False

process = cms.Process("hh4b")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

from inputFiles_cfi import * 
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      FileNames[options.FileNames]
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
process.evtcleaner.DoPUReweightingOfficial = options.doPUReweightingOfficial
process.evtcleaner.storeLHEWts = options.storeLHEWts

process.load('Analysis.VLQAna.HH4b_cff') 
process.hh4b.printEvtNo = cms.bool(options.printEvtNo)
process.hh4b.jetAK8selParams.scaleJetP4 = cms.bool(False)
process.hh4b.jetAK8selParams.jettau2Bytau1Max = cms.double(1.00)
process.hh4b.jetAK8selParams.subjetCSVMin = cms.double(-1000.) 
#process.hh4b.doBTagSFUnc = options.doBTagSFUnc
process.hh4b.jetAK8selParams.jecShift = options.jecShift 
process.hh4b.jetAK8selParams.jerShift = options.jerShift 
process.hh4b.jetHTaggedselParams.scaleJetP4 = cms.bool(False)
process.hh4b.jetHTaggedselParams.jettau2Bytau1Max = cms.double(1.00)
process.hh4b.jetHTaggedselParams.subjetCSVMin = cms.double(-1000.) 
#process.hh4b.doBTagSFUnc = options.doBTagSFUnc
process.hh4b.jetHTaggedselParams.jecShift = options.jecShift 
process.hh4b.jetHTaggedselParams.jerShift = options.jerShift 
if options.isData:
  #process.hh4b.jetAK8selParams.newJECPayloadNames.append("Fall15_25nsV2_DATA_L2L3Residual_AK8PFchs.txt") #
  process.hh4b.jetAK8selParams.jecUncPayloadName = cms.string("Fall15_25nsV2_DATA_Uncertainty_AK8PFchs.txt")
  process.hh4b.jetAK8selParams.jecAK8GroomedPayloadNames = cms.vstring(
      "Fall15_25nsV2_DATA_L2Relative_AK8PFchs.txt", 
      "Fall15_25nsV2_DATA_L3Absolute_AK8PFchs.txt",
      "Fall15_25nsV2_DATA_L2L3Residual_AK8PFchs.txt")  
  #process.hh4b.jetHTaggedselParams.newJECPayloadNames.append("Fall15_25nsV2_DATA_L2L3Residual_AK8PFchs.txt") #
  process.hh4b.jetHTaggedselParams.jecUncPayloadName = cms.string("Fall15_25nsV2_DATA_Uncertainty_AK8PFchs.txt")
  process.hh4b.jetHTaggedselParams.jecAK8GroomedPayloadNames = cms.vstring(
      "Fall15_25nsV2_DATA_L2Relative_AK8PFchs.txt", 
      "Fall15_25nsV2_DATA_L3Absolute_AK8PFchs.txt",
      "Fall15_25nsV2_DATA_L2L3Residual_AK8PFchs.txt")  

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

open('dump.py','w').write(process.dumpPython())
