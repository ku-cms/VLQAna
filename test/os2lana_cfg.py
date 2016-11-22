import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Is data?"
    )
options.register('zdecaymode', 'zmumu',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Z->mumu or Z->elel? Choose: 'zmumu' or 'zelel'"
    )
options.register('lepID', 'TIGHT',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "lepton ID? Choose: 'TIGHT' or 'LOOSE'"
    )
options.register('outFileName', 'os2lana.root',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output file name"
    )
options.register('doPUReweightingOfficial', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Do pileup reweighting using official recipe"
    )
options.register('filterSignal', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Select only tZtt or bZbZ modes"
    )
options.register('signalType', '',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Select one of EvtType_MC_tZtZ, EvtType_MC_tZtH, EvtType_MC_tZbW, EvtType_MC_tHtH, EvtType_MC_tHbW, EvtType_MC_bWbW, EvtType_MC_bZbZ, EvtType_MC_bZbH, EvtType_MC_bZtW, EvtType_MC_bHbH, EvtType_MC_bHtW, EvtType_MC_tWtW" 
    )
options.register('applyLeptonSFs', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Apply lepton SFs to the MC"
    )
options.register('applyBTagSFs', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Apply b-tagging SFs to the MC"
    )
options.register('applyDYNLOCorr', False, ### Set to true only for DY process ### Only EWK NLO k-factor is applied
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Apply DY EWK k-factor to DY MC"
    )
options.register('FileNames', 'FileNames_QCD_HT1000to1500',
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Name of list of input files"
    )
options.register('optimizeReco', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Optimize mass reconstruction"
    )

options.setDefault('maxEvents', -1)
options.parseArguments()
print options

hltpaths = []
if options.isData:
  options.filterSignal = False 
  options.signalType = "" 
  options.optimizeReco = False
  options.applyLeptonSFs = False 
  options.applyBTagSFs   = False 
  options.applyDYNLOCorr = False 
  if options.zdecaymode == "zmumu":
    hltpaths = [
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"
        ]
  elif options.zdecaymode == "zelel":
    hltpaths = [
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
        ]
  else:
    sys.exit("!!!Error: Wrong Z decay mode option chosen. Choose either 'zmumu' or 'zelel'!!!") 

if options.filterSignal == True and len(options.signalType) == 0:
  sys.exit("!!!Error: Cannot keep signalType empty when filterSignal switched on!!!")  

process = cms.Process("OS2LAna")

from inputFiles_cfi import * 

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      FileNames[options.FileNames]
      '/store/user/grauco/B2GAnaFW/B2GAnaFW_80X_V2p1/TT_TuneCUETP8M1_13TeV-powheg-pythia8/B2GAnaFW_80X_V2p1/161021_085128/0000/B2GEDMNtuple_105.root'
    ) 
    )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.load("Analysis.VLQAna.EventCleaner_cff") 
process.evtcleaner.isData = options.isData 
process.evtcleaner.hltPaths = cms.vstring (hltpaths)  
process.evtcleaner.DoPUReweightingOfficial = cms.bool(options.doPUReweightingOfficial)  
#process.evtcleaner.storeLHEWts = options.storeLHEWts

from Analysis.VLQAna.OS2LAna_cfi import * 

### Z candidate and jet selections 
process.ana = ana.clone(
    filterSignal = cms.bool(options.filterSignal),
    signalType = cms.string(options.signalType),
    zdecayMode = cms.string(options.zdecaymode),
    applyLeptonSFs = cms.bool(options.applyLeptonSFs),
    applyBTagSFs = cms.bool(options.applyBTagSFs),
    applyDYNLOCorr = cms.bool(options.applyDYNLOCorr),
    optimizeReco = cms.bool(options.optimizeReco),
    )
process.ana.elselParams.elidtype = cms.string(options.lepID)
process.ana.muselParams.muidtype = cms.string(options.lepID)
process.ana.muselParams.muIsoMax = cms.double(0.15)
process.ana.lepsfsParams.lepidtype = cms.string(options.lepID)
process.ana.lepsfsParams.zdecayMode = cms.string(options.zdecaymode)
process.ana.BoostedZCandParams.ptMin = cms.double(80.)
process.ana.jetAK8selParams.jetPtMin = cms.double(200) 
process.ana.jetAK4BTaggedselParams.jetPtMin = cms.double(50) 
process.ana.STMin = cms.double(1000.)
process.ana.vlqMass = cms.double(1000.) #M=1000
process.ana.bosonMass = cms.double(91.2) #Z

process.TFileService = cms.Service("TFileService",
       fileName = cms.string(
         options.outFileName
         )
       )

## Event counters
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)

process.load("Analysis.VLQAna.VLQCandProducer_cff")

process.p = cms.Path(
    process.allEvents
    *process.evtcleaner
    *process.cleanedEvents
    *cms.ignore(process.ana)
    * process.finalEvents
    )

#process.schedule = cms.Schedule(process.p)

open('dump.py','w').write(process.dumpPython())
