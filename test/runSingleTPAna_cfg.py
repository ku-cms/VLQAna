import FWCore.ParameterSet.Config as cms

process = cms.Process("SingleTpAna")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      #'/store/user/devdatta/TprimeJetToTH_allHdecays_M800GeV_Tune4C_13TeV-madgraph-tauola/B2GAnaFW_PHYS14/150310_153716/0000/B2GEDMNtuple_1.root'
      #'/store/user/devdatta/TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/B2GAnaFW_PHYS14/150310_151926/0000/B2GEDMNtuple_1.root'
      #'/store/user/eschmitz/b2g/PHYS14/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/TTJets_edmntuples_B2GAnaFW_1/150223_193315/0000/B2GEDMNtuple_1.root'
      #'/store/user/devdatta/QCD_HT_1000ToInf_13TeV-madgraph/B2GAnaFW_PHYS14/150323_203541/0000/B2GEDMNtuple_1.root'
      #/Rad_HHto4b_M1600_13TeV_PHYS14_25_V1/cvernier-miniAOD-b7ec9eab226684f647ba3bf663cdb8b0/USER
      'file:/afs/cern.ch/work/d/devdatta/CMSREL/CMSSW_7_3_2_patch4/src/Analysis/B2GAnaFW/test/B2GEDMNtuple_74X.root'
      )
      )

process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(200) 
    )

process.load("Analysis.VLQAna.HbbCandidateProducer_cfi") 
#process.load("Analysis.VLQAna.CompositeParticleProducer_cfi") 

from Analysis.VLQAna.VLQAna_cfi import *
process.ana1 = ana.clone(
    HJetSelParams = defaultHJetSelectionParameters.clone(
      jettype             = cms.string('HTAGGEDAK8JET'),
      jettau2Bytau1Min    = cms.double(0.0) ,
      jettau2Bytau1Max    = cms.double(0.5) ,
      jetPrunedMassMin    = cms.double(0) ,
      jetPrunedMassMax    = cms.double(1000000) ,
      jetMassMin          = cms.double(100.) ,
      jetMassMax          = cms.double(150.) ,
      subjetCSVMin        = cms.double(0.0) ,
      jetnSubJetsMin      = cms.double(2) ,
      jetnSubJetsMax      = cms.double(2) ,
      )
    ) 
process.ana2 = ana.clone(
    HJetSelParams = defaultHJetSelectionParameters.clone(
      jettype             = cms.string('HTAGGEDAK8JET'),
      jettau2Bytau1Min    = cms.double(0.0) ,
      jettau2Bytau1Max    = cms.double(0.5) ,
      jetPrunedMassMin    = cms.double(0) ,
      jetPrunedMassMax    = cms.double(1000000) ,
      jetMassMin          = cms.double(100.) ,
      jetMassMax          = cms.double(150.) ,
      subjetCSVMin        = cms.double(0.423) ,
      jetnSubJetsMin      = cms.double(2) ,
      jetnSubJetsMax      = cms.double(2) ,
      )
    ) 
process.ana = ana.clone() 

from Analysis.VLQAna.TprimeSel_cfi import *
from Analysis.VLQAna.TprimeMVA_cfi import *
process.sel = sel.clone() 
process.mva = mva.clone() 

#process.load("Analysis.VLQAna.ResolvedVjjFilter_cfi")
#process.vjj.isMC = cms.bool(True)
#process.vjj.isSignal = cms.bool(True)

process.TFileService = cms.Service("TFileService",
       fileName = cms.string("SingleTprimeAnaMVA.root")
       )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("SingleTprimeAnaEvtsMVA.root"),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      "drop *",
      "keep *_eventShape*_*_*", 
      "keep *_centrality_*_*", 
      "keep *_genPart_*_*", 
      "keep *_jetsAK4_*_*", 
      "keep *_jetsAK8_*_*", 
      "keep *_subjetsAK8_*_*", 
      "keep *_subjetsCmsTopTag_*_*", 
      #"keep *_*_npv_*", 
      #"keep *_par_*_*",
      #"keep *_hbb_*_*",
      "keep *_ana_*_*",
      #"keep *_vjj_*_*",
      "keep *_sel_*_*", 
      "keep *_mva_*_*", 
      )
    )

process.p = cms.Path(
    #process.par
    process.hbb
    *process.ana1 
    *process.ana2 
    *process.ana 
    #*process.vjj
    *process.mva 
    )
process.outpath = cms.EndPath(process.out)
