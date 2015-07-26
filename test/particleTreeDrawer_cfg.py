import FWCore.ParameterSet.Config as cms

process = cms.Process('LIST')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
     'file:/afs/cern.ch/work/d/devdatta/CMSREL/CMSSW_7_4_6_patch6/src/HLTrigger/Configuration/test/GENSIMRAWHLT.root' 
      #'root://cmsxrootd.fnal.gov///store/mc/Phys14DR/TprimeJetToTH_M1200GeV_Tune4C_13TeV-madgraph-tauola/AODSIM/PU20bx25_PHYS14_25_V1-v1/10000/022C772D-BD6B-E411-A63D-485B39800BB4.root'
      #'root://cmsxrootd.fnal.gov///store/mc/Phys14DR/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/AODSIM/PU20bx25_PHYS14_25_V1-v1/00000/000470E0-3B75-E411-8B90-00266CFFA604.root'
        )
    ) 

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.printTree = cms.EDAnalyzer("ParticleTreeDrawer",
    src = cms.InputTag("genParticles"),                                                                 
    printP4 = cms.untracked.bool(False),
    printPtEtaPhi = cms.untracked.bool(False),
    printVertex = cms.untracked.bool(False),
    printStatus = cms.untracked.bool(False),
    printIndex = cms.untracked.bool(False),
    #status = cms.untracked.vint32( 3 )
    )

process.printDecay = cms.EDAnalyzer("ParticleDecayDrawer",
    src = cms.InputTag("genParticles"),
    printP4 = cms.untracked.bool(False),
    printPtEtaPhi = cms.untracked.bool(False),
    printVertex = cms.untracked.bool(False)
    )

process.printList = cms.EDAnalyzer("ParticleListDrawer",
    maxEventsToPrint = cms.untracked.int32(1),
    printVertex = cms.untracked.bool(False),
    src = cms.InputTag("genParticles")
    )

process.genTree = cms.EDAnalyzer("ParticleListDumper",
    maxEventsToPrint = cms.untracked.int32(-1),
    printVertex = cms.untracked.bool(False),
    src = cms.InputTag("genParticles")
    )

process.TFileService = cms.Service("TFileService",
       fileName = cms.string("TprimeBToTH_M-800_LH_GEN.root")
       #fileName = cms.string("TprimeJetToTH_M1200_Tune4C_13TeV-madgraph-tauola_GEN.root")
       #fileName = cms.string("TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola_GEN.root")
       )

process.p = cms.Path(process.printDecay)
