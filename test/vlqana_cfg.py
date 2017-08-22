import sys, os
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
options.register('hltORAND', 'OR',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "OR or AND HLT paths?"
    )
options.register('cleanEvents', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Clean events using EventCleaner?"
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
options.register('HTMin', 900,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "Minimum HT"
    )
options.register('storePreselEvts', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Store pre-selected events after pre-selection", 
    )
options.register('applyBTagSFs', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Apply b-tagging SFs to the MC"
    )
options.register('btageffmap', "btagEff_TtH_1200_loose.root",#until new SFs arrive
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "ROOT file with Th2D histos of b tag effs for b,c, and light flavoured jets"
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
options.register('FileNames', 'test',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Name of list of input files"
    )

options.setDefault('maxEvents', -1000)
options.parseArguments()


#hltpaths = ["HLT_PFJet320_v"]
#Run2016B-G
#hltpathsOr = [
#               "HLT_AK8PFJet360_TrimMass30_v", 
#              "HLT_AK8DiPFJet280_200_TrimMass30_v",
#              "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v",
#              "HLT_AK8PFJet450_v",
#             ]
#Run2016H
#hltpathsOr = ["HLT_AK8PFJet360_TrimMass30_v", 
#              "HLT_AK8DiPFJet300_200_TrimMass30_v",
#              "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v",
#              "HLT_AK8PFJet450_v",
#             ]

hltpathsOr = ["HLT_AK8PFJet360_TrimMass30_v", 
              "HLT_AK8DiPFJet300_200_TrimMass30_v",
              "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v",
              "HLT_AK8PFJet450_v",
              "HLT_AK8DiPFJet280_200_TrimMass30_v",
              "HLT_PFHT800_v",
              "HLT_PFHT900_v",
             ]
if options.isData:
    options.doBTagSFUnc = False 
    options.jerShift = 0 
    options.doPUReweightingOfficial=False 
    options.storeLHEWts=False
    options.applyBTagSFs = False
HTMin=1100
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
#dataFilePath = "$CMSSW_BASE/src/Analysis/VLQAna/data/"
dataFilePath = '../data/'
process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.hltORAND = cms.string (options.hltORAND)  
process.evtcleaner.hltPaths = cms.vstring (hltpathsOr)  
process.evtcleaner.cleanEvents = cms.bool(options.cleanEvents)
process.evtcleaner.isData = options.isData 
process.evtcleaner.DoPUReweightingOfficial = options.doPUReweightingOfficial
process.evtcleaner.storeLHEWts = options.storeLHEWts
process.evtcleaner.File_PUDistData      = cms.string(os.path.join(dataFilePath,'RunII2016Rereco_25ns_PUXsec69000nb.root'))
process.evtcleaner.File_PUDistDataLow   = cms.string(os.path.join(dataFilePath,'RunII2016Rereco_25ns_PUXsec65550nb.root'))
process.evtcleaner.File_PUDistDataHigh  = cms.string(os.path.join(dataFilePath,'RunII2016Rereco_25ns_PUXsec72450nb.root'))
process.evtcleaner.File_PUDistMC        = cms.string(os.path.join(dataFilePath,'PUDistMC_Summer2016_25ns_Moriond17MC_PoissonOOTPU.root'))

process.evtcleanerBG = process.evtcleaner.clone()
process.evtcleanerBG.File_PUDistData = cms.string(os.path.join(dataFilePath, 'RunII2016Rereco_25ns_RunsBtoG_PUXsec69000nb.root'))
process.evtcleanerH = process.evtcleaner.clone()
process.evtcleanerH.File_PUDistData = cms.string(os.path.join(dataFilePath,'RunII2016Rereco_25ns_RunH_PUXsec69000nb.root'))

from Analysis.VLQAna.VLQAna_cfi import *

if options.isData == False: ### Careful, to be reset when B2GAnaFW_v80X_v2.4 MC are used
  for par in ['jetAK4selParams', 'jetAK8selParams', 'jetHTaggedselParams', 'jetAntiHTaggedselParams', 'jetTopTaggedselParams', 'jetAntiTopTaggedselParams']:
    if 'AK4' in par:
        jetType = 'AK4PFchs'
    else:
        jetType = 'AK8PFchs'
        payLoadTypes = ['L2Relative', 'L3Absolute']
        payLoadFiles = []
        for payLoadType in payLoadTypes: payLoadFiles.append(os.path.join(dataFilePath,'Summer16_23Sep2016V4_MC_'+payLoadType+'_'+jetType+'.txt'))   
        setattr(getattr(ana, par), 'jecAK8GroomedPayloadNames', cms.vstring(payLoadFiles))

        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jettau1Label'         ,cms.InputTag("jetsAK8CHS", "jetAK8CHStau1CHS"))
        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jettau2Label'         ,cms.InputTag("jetsAK8CHS", "jetAK8CHStau2CHS"))
        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jettau3Label'         ,cms.InputTag("jetsAK8CHS", "jetAK8CHStau3CHS"))
        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jetPrunedMassLabel'   ,cms.InputTag("jetsAK8CHS", "jetAK8CHSprunedMassCHS"))
        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jetTrimmedMassLabel'  ,cms.InputTag("jetsAK8CHS", "jetAK8CHStrimmedMassCHS"))
        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jetFilteredMassLabel' ,cms.InputTag("jetsAK8CHS", "jetAK8CHSfilteredMassCHS"))
        setattr(getattr(getattr(ana, par), 'JetSubstrParams'), 'jetSoftDropMassLabel' ,cms.InputTag("jetsAK8CHS", "jetAK8CHSsoftDropMassCHS"))
    setattr(getattr(ana,par), 'jecUncPayloadName', cms.string(os.path.join(dataFilePath, 'Summer16_23Sep2016V4_MC_Uncertainty_'+jetType+'.txt')))

 
process.ana = ana.clone()
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
#process.ana.jetTopTaggedselParams.jettau3Bytau2Max = options.topTagtau32
#process.ana.jetTopTaggedselParams.subjetHighestCSVMin = options.topTagBDisc
process.ana.storePreselEvts = options.storePreselEvts
process.ana.doPreselOnly = options.doPreselOnly
process.ana.HTMin = HTMin
process.ana.applyBTagSFs = options.applyBTagSFs
process.ana.btageffmap = cms.string(os.path.join(dataFilePath,options.btageffmap)) 
process.ana.sjbtagSFcsv = cms.string(os.path.join(dataFilePath,"subjet_CSVv2_Moriond17_B_H.csv")) 


process.anaCHS = process.ana.clone()

from Analysis.VLQAna.JetMaker_cfi import *
            

process.anaPuppi = process.ana.clone(
    jetAK8selParams = defaultAK8PuppiJetSelectionParameters,
    jetHTaggedselParams = defaultPuppiHJetSelectionParameters,
    jetAntiHtaggedSelParams = defaultPuppiHJetSelectionParameters.clone(
                                  subjetCSVMin = cms.double(-1000000),
                                  subjetCSVMax = defaultPuppiHJetSelectionParameters.subjetCSVMin,
                                  ),
    jetTopTaggedselParams = defaultPuppiTJetSelectionParameters.clone(),
    
    )

process.anaDoubleB = process.ana.clone(
    jetHTaggedselParams = defaultCHSHJetSelectionParameters.clone(
                                  subjetCSVMin = cms.double(-1000000),
                                  subjetCSVMax = cms.double(1000000),
                                  jetDoubleBMin = cms.double(0.8),
                                  ),
    jetAntiHTaggedSelParams = defaultCHSHJetSelectionParameters.clone(
                                  subjetCSVMin = cms.double(-1000000),
                                  subjetCSVMax = cms.double(1000000),
                                  jetDoubleBMax = cms.double(0.8),
                                  ),
    )
 
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)
process.finalEventsPuppi = eventCounter.clone(isData=options.isData)
process.finalEventsDoubleB = eventCounter.clone(isData=options.isData)

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.evtcleanerBG
    *process.evtcleanerH
    *process.cleanedEvents
    *process.anaCHS 
    *process.finalEvents
    )

process.pPuppi = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.anaPuppi
    *process.finalEventsPuppi
    )

process.pDoubleB = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.anaDoubleB
    *process.finalEventsDoubleB
    )

process.out = cms.OutputModule("PoolOutputModule",
        SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('evtcleaner')),
            )

process.schedule = cms.Schedule(process.p)

#process.outpath = cms.EndPath(process.out)

open('dump.py','w').write(process.dumpPython())
