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
    npvLabel                   = cms.InputTag("eventUserData", "npv"),
    puNtrueIntLabel            = cms.InputTag("eventUserData", "puNtrueInt"),
    hltPaths                   = cms.vstring (
        ), 
    metFilters                 = cms.vstring (
        "Flag_goodVertices",
        "Flag_CSCTightHaloFilter",
        "Flag_HBHENoiseFilter", 
        "Flag_eeBadScFilter",
        ), 
    isData                     = cms.bool(False), 
    DoPUReweightingOfficial    = cms.bool(False),
    DoPUReweightingNPV         = cms.bool(False),
    File_PVWt                  = cms.string('hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root'),
    File_PUDistData            = cms.string('PUDistData_Run2015ABCD.root'),
    File_PUDistMC              = cms.string('PUDistMC_2015_25ns_Startup_PoissonOOTPU.root'),
    Hist_PVWt                  = cms.string('hpvwt_data_mc'),
    Hist_PUDistData            = cms.string('pileup'),
    Hist_PUDistMC              = cms.string('pileup'),
    vlqParams                  = cms.PSet(genPartParams,vlqParams)
    )
