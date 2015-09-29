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

#from infiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_1.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_10.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_11.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_12.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_13.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_14.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_15.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_16.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_17.root',
    '/store/user/devdatta/DoubleMuon/crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075412/0000/B2GEDMNtuple_18.root',

    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_1.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_10.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_11.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_12.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_13.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_14.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_15.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_16.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_17.root',
    #'/store/user/devdatta/DoubleEG/crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns/150926_075907/0000/B2GEDMNtuple_18.root',
    )
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 

from Analysis.VLQAna.OS2LAna_cfi import * 

process.anaelel = ana.clone(
    isData = options.isData,
    hltPaths = cms.vstring (
        "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v", 
        "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v"
        ), 
    )

process.anamumu = ana.clone(
    isData = options.isData, 
    hltPaths = cms.vstring (
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", 
        ), 
    )

process.anaelelBoosted = ana.clone(
    isData = options.isData,
    hltPaths = cms.vstring (
        "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v", 
        "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v"
        ), 
    BoostedZCandParams = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(150.),
        ), 
    )

process.anamumuBoosted = ana.clone(
    isData = options.isData, 
    hltPaths = cms.vstring (
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", 
        ), 
    BoostedZCandParams = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMin = cms.double(150.),
        ), 
    )

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
process.allEvents = eventCounter.clone()
process.selectedEvents = eventCounter.clone()

process.p = cms.Path(
    process.allEvents
    *cms.ignore(process.anaelel)*cms.ignore(process.anaelelBoosted)
    *cms.ignore(process.anamumu)*cms.ignore(process.anamumuBoosted)
    * process.selectedEvents
    )
#process.outpath = cms.EndPath(process.out)

