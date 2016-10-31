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
options.register('FileNames', 'FileNames_BG2000',
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

hltpaths = ['HLT_PFHT650_v', 'HLT_PFHT800_v', 'HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v', 'HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v', 'HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v', 'HLT_AK8PFJet360_TrimMass30_v']
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

from Analysis.VLQAna.HH4b_cff import *
process.hh4bchs = hh4b.clone(
    jetAK8selParams  = defaultAK8CHSJetSelectionParameters.clone(
      jetPtMin                  = cms.double(0),
      JetIDParams  = defaultAK8CHSJetIDParameters.clone(
        quality = cms.string  ("TIGHTLEPVETO"),
        ), 
      jetAbsEtaMax = cms.double(100), 
      ),
    jetHTaggedselParams = defaultCHSHJetSelectionParameters.clone(
      JetIDParams  = defaultAK8CHSJetIDParameters.clone(
      jetPtMin                  = cms.double(0),
        quality = cms.string  ("TIGHTLEPVETO"),
        ), 
      jetAbsEtaMax = cms.double(100), 
      #jetSoftDropMassMin    = cms.double(90) ,
      #jetSoftDropMassMax    = cms.double(145) ,
      ),
    )
process.hh4bchs.printEvtNo = cms.bool(options.printEvtNo)
process.hh4bchs.jetAK8selParams.scaleJetP4 = cms.bool(False)
process.hh4bchs.jetAK8selParams.jettau2Bytau1Max = cms.double(1.00)
process.hh4bchs.jetAK8selParams.subjetCSVMin = cms.double(-1000.) 
process.hh4bchs.jetAK8selParams.jecShift = options.jecShift 
process.hh4bchs.jetAK8selParams.jerShift = options.jerShift 
process.hh4bchs.jetHTaggedselParams.scaleJetP4 = cms.bool(False)
process.hh4bchs.jetHTaggedselParams.jettau2Bytau1Max = cms.double(1.00)
process.hh4bchs.jetHTaggedselParams.subjetCSVMin = cms.double(-1000.) 
process.hh4bchs.jetHTaggedselParams.jecShift = options.jecShift 
process.hh4bchs.jetHTaggedselParams.jerShift = options.jerShift 
if options.isData:
  process.hh4bchs.jetAK8selParams.jecUncPayloadName = cms.string("Spring16_25nsV6_DATA_Uncertainty_AK8PFchs.txt")
  process.hh4bchs.jetAK8selParams.jecAK8GroomedPayloadNames = cms.vstring(
      "Spring16_25nsV6_DATA_L2Relative_AK8PFchs.txt", 
      "Spring16_25nsV6_DATA_L3Absolute_AK8PFchs.txt",
      "Spring16_25nsV6_DATA_L2L3Residual_AK8PFchs.txt")  
  process.hh4bchs.jetHTaggedselParams.jecUncPayloadName = cms.string("Spring16_25nsV6_DATA_Uncertainty_AK8PFchs.txt")
  process.hh4bchs.jetHTaggedselParams.jecAK8GroomedPayloadNames = cms.vstring(
      "Spring16_25nsV6_DATA_L2Relative_AK8PFchs.txt", 
      "Spring16_25nsV6_DATA_L3Absolute_AK8PFchs.txt",
      "Spring16_25nsV6_DATA_L2L3Residual_AK8PFchs.txt")  

process.hh4bpuppi = process.hh4bchs.clone(
    jetAK8selParams  = defaultAK8PuppiJetSelectionParameters.clone(
      jetPtMin                  = cms.double(200),
      JetIDParams  = defaultAK8PuppiJetIDParameters.clone(
        quality = cms.string  ("TIGHTLEPVETO"),
        ), 
      jetAbsEtaMax = cms.double(100), 
      ),
    jetHTaggedselParams = defaultPuppiHJetSelectionParameters.clone(
      JetIDParams  = defaultAK8PuppiJetIDParameters.clone(
        quality = cms.string  ("TIGHTLEPVETO"),
        ), 
      ),
    )

from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *process.hh4bchs
    *process.hh4bpuppi
    * process.finalEvents
    )

open('dump.py','w').write(process.dumpPython())
