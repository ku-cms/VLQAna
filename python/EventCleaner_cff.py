import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.VLQParams_cfi import * 

evtcleaner = cms.EDFilter("EventCleaner",
    trigNameLabel              = cms.InputTag("TriggerUserData", "triggerNameTree"), 
    trigBitLabel               = cms.InputTag("TriggerUserData", "triggerBitTree"), 
    metFiltersNameLabel        = cms.InputTag("METUserData", "triggerNameTree"), 
    metFiltersBitLabel         = cms.InputTag("METUserData", "triggerBitTree"), 
    hbheNoiseFilterLabel       = cms.InputTag("HBHENoiseFilterResultProducer", "HBHENoiseFilterResultRun1"), 
    genEvtInfoProdName         = cms.string('generator'),
    vtxRhoLabel                = cms.InputTag("vertexInfo", "rho"),
    vtxZLabel                  = cms.InputTag("vertexInfo", "z"),
    vtxNdfLabel                = cms.InputTag("vertexInfo", "ndof"),
    hltPaths                   = cms.vstring (
        ), 
    metFilters                 = cms.vstring (
        "Flag_goodVertices",
        "Flag_CSCTightHaloFilter",
        "Flag_HBHENoiseFilter", 
        "Flag_eeBadScFilter",
        ), 
    isData                     = cms.bool(False), 
    DoPUReweightingNPV         = cms.bool(False),
    File_PVWt                  = cms.string('hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root'),
    Hist_PVWt                  = cms.string('hpvwt_data_mc'),
    vlqParams                  = cms.PSet(genPartParams,vlqParams)
    )
