import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')

options.register('outFileName', 'os2lana.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )

options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )

options.setDefault('maxEvents', 1000)

options.parseArguments()

process = cms.Process("OS2LAna")

from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    #fileNamess_TT_M800_Spring15_25ns
    files_DY_M50
    ) 
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.isData = options.isData 
process.evtcleaner.hltPaths = cms.vstring (
        #"HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v", 
        #"HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v"
        #"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", 
        )  

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

from Analysis.VLQAna.OS2LAna_cfi import * 

process.anaelel = ana.clone(
    isData = options.isData,
    )

process.anamumu = ana.clone(
    isData = options.isData, 
    )

process.anaelelBoosted = ana.clone(
    isData = options.isData,
    BoostedZCandParams = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(250.),
        ), 
    )

process.anamumuBoosted = ana.clone(
    isData = options.isData, 
    BoostedZCandParams = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(250.),
        ), 
    )

if not options.isData:
  process.anamumu.elselParams.useVID = cms.bool(False)
  process.anaelel.elselParams.useVID = cms.bool(False)
  process.anamumuBoosted.elselParams.useVID = cms.bool(False)
  process.anaelelBoosted.elselParams.useVID = cms.bool(False)

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         options.outFileName
         )
       )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("OS2LAnaEvts.root"),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      "drop *",
      )
    )

## Event counter
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *cms.ignore(process.anaelel)*cms.ignore(process.anaelelBoosted)
    *cms.ignore(process.anamumu)*cms.ignore(process.anamumuBoosted)
    * process.finalEvents
    )
#process.outpath = cms.EndPath(process.out)

