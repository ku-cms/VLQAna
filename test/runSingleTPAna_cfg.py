import FWCore.ParameterSet.Config as cms

process = cms.Process("SingleTpAna")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
      #'/store/user/devdatta/TprimeJetToTH_allHdecays_M800GeV_Tune4C_13TeV-madgraph-tauola/B2GAnaFW_PHYS14/150310_153716/0000/B2GEDMNtuple_1.root'
      #'/store/user/devdatta/TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/B2GAnaFW_PHYS14/150310_151926/0000/B2GEDMNtuple_1.root'
      '/store/user/eschmitz/b2g/PHYS14/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/TTJets_edmntuples_B2GAnaFW_1/150223_193315/0000/B2GEDMNtuple_1.root'
      #'/store/user/eschmitz/b2g/PHYS14/QCD_HT_1000ToInf_13TeV-madgraph/ext1_v1_edmntuple_B2GAnaFW/150218_154901/0000/B2GEDMNtuple_1.root'
      )
      )

process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(1000) 
    )

from Analysis.VLQAna.JetSelector_cfi import *

process.ana = cms.EDFilter("VLQAna",
    processName                = cms.string  ('@'), 
    trigNameLabel              = cms.InputTag("TriggerUserData", "triggerNameTree"), 
    trigBitLabel               = cms.InputTag("TriggerUserData", "triggerBitTree"), 
    jetAK8PtLabel              = cms.InputTag("jetsAK8", "jetAK8Pt"),
    jetAK8EtaLabel             = cms.InputTag("jetsAK8", "jetAK8Eta"),
    jetAK8PhiLabel             = cms.InputTag("jetsAK8", "jetAK8Phi"),
    jetAK8MassLabel            = cms.InputTag("jetsAK8", "jetAK8Mass"),
    jetAK8FilteredMassLabel    = cms.InputTag("jetsAK8", "jetAK8filteredMass"),
    jetAK8PrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetAK8TrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jetAK8EnergyLabel          = cms.InputTag("jetsAK8", "jetAK8Energy"),
    jetAK8FlavourLabel         = cms.InputTag("jetsAK8", "jetAK8Flavour"),
    jetAK8CSVLabel             = cms.InputTag("jetsAK8", "jetAK8CSV"),
    jetAK8JECLabel             = cms.InputTag("jetsAK8", "jetAK8jecFactor0"),
    jetAK8AreaLabel            = cms.InputTag("jetsAK8", "jetAK8jetArea"),
    jetAK8Tau1Label            = cms.InputTag("jetsAK8", "jetAK8tau1"), 
    jetAK8Tau2Label            = cms.InputTag("jetsAK8", "jetAK8tau2"),  
    jetAK8Tau3Label            = cms.InputTag("jetsAK8", "jetAK8tau3"),  
    jetAK8nSubJetsLabel        = cms.InputTag("jetsAK8", "jetAK8nSubJets"),  
    jetAK8minmassLabel         = cms.InputTag("jetsAK8", "jetAK8minmass"),  
    jetAK8VSubjetIndex0Label   = cms.InputTag("jetsAK8", "jetAK8VSubjetIndex0"),  
    jetAK8VSubjetIndex1Label   = cms.InputTag("jetsAK8", "jetAK8VSubjetIndex1"),  
    jetAK8TopSubjetIndex0Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex0"),
    jetAK8TopSubjetIndex1Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex1"),
    jetAK8TopSubjetIndex2Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex2"),
    jetAK8TopSubjetIndex3Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex3"),
    subjetAK8BDiscLabel        = cms.InputTag("subjetsAK8", "subjetAK8subjetCSV"),
    subjetAK8PtLabel           = cms.InputTag("subjetsAK8", "subjetAK8Pt"),
    subjetAK8EtaLabel          = cms.InputTag("subjetsAK8", "subjetAK8Eta"),
    subjetAK8PhiLabel          = cms.InputTag("subjetsAK8", "subjetAK8Phi"),
    subjetAK8MassLabel         = cms.InputTag("subjetsAK8", "subjetAK8Mass"),
    subjetCmsTopTagBDiscLabel  = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagCSV"),
    subjetCmsTopTagPtLabel     = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagPt"),
    subjetCmsTopTagEtaLabel    = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagEta"),
    subjetCmsTopTagPhiLabel    = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagPhi"),
    subjetCmsTopTagMassLabel   = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagMass"),
    jetAK4PtLabel              = cms.InputTag("jetsAK4", "jetAK4Pt"),
    jetAK4EtaLabel             = cms.InputTag("jetsAK4", "jetAK4Eta"),
    jetAK4PhiLabel             = cms.InputTag("jetsAK4", "jetAK4Phi"),
    jetAK4MassLabel            = cms.InputTag("jetsAK4", "jetAK4Mass"),
    jetAK4EnergyLabel          = cms.InputTag("jetsAK4", "jetAK4Energy"),
    jetAK4FlavourLabel         = cms.InputTag("jetsAK4", "jetAK4Flavour"),
    jetAK4CSVLabel             = cms.InputTag("jetsAK4", "jetAK4CSV"),
    jetAK4JECLabel             = cms.InputTag("jetsAK4", "jetAK4jecFactor0"),
    jetAK4nHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4neutralHadronEnergy"),
    jetAK4nEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4neutralEmEnergy"),
    jetAK4HFHadronEnergyLabel  = cms.InputTag("jetsAK4", "jetAK4HFHadronEnergy"),
    jetAK4cHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4chargedHadronEnergy"),
    jetAK4cEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4chargedEmEnergy"),
    jetAK4numDaughtersLabel    = cms.InputTag("jetsAK4", "jetAK4numberOfDaughters"),
    jetAK4cMultipLabel         = cms.InputTag("jetsAK4", "jetAK4chargedMultiplicity"),
    jetAK4YLabel               = cms.InputTag("jetsAK4", "jetAK4Y"),
    jetAK4AreaLabel            = cms.InputTag("jetsAK4", "jetAK4jetArea"),
    hltPaths                   = cms.vstring ("HLT_PFJet260_v1", "HLT_AK8PFJet360TrimMod_Mass30_v1", "HLT_PFHT900_v1"), 
    AK4JetSelParams            = defaultAK4JetSelectionParameters.clone(), 
    BTaggedAK4JetSelParams     = defaultBTaggedAK4JetSelectionParameters.clone(), 
    AK8JetSelParams            = defaultAK8JetSelectionParameters.clone(
        jetPtMin            = cms.double(30),
        jetMassMin          = cms.double(0) ,
        ), 
    TJetSelParams              = defaultTJetSelectionParameters.clone(), 
    HJetSelParams              = defaultHJetSelectionParameters.clone(), 
    WJetSelParams              = defaultWJetSelectionParameters.clone(), 
    ak8jetsPtMin               = cms.double  (300),
    ak8jetsEtaMax              = cms.double  (2.4),
    ak4jetsPtMin               = cms.double  (30),
    ak4jetsEtaMax              = cms.double  (5.0),
    HTMin                      = cms.double  (700.), 
    )

process.load("Analysis.VLQAna.ResolvedVjjFilter_cfi")
process.vjj.isMC = cms.bool(True)
process.vjj.isSignal = cms.bool(True)

process.sel = cms.EDFilter("TprimeSel",
    jetcoll                    = cms.InputTag("vjj",    "JetCollection"),
    resolvedvjjcoll            = cms.InputTag("vjj",    "ResolvedVjjCollection"),
    ngoodAK4Jets               = cms.InputTag("ana",    "ngoodAK4Jets"),
    ngoodAK8Jets               = cms.InputTag("ana",    "ngoodAK8Jets"),
    ngoodBTaggedAK4Jets        = cms.InputTag("ana",    "ngoodBTaggedAK4Jets"),
    nTJets                     = cms.InputTag("ana",    "nTJets"),
    nHJets                     = cms.InputTag("ana",    "nHJets"),
    nWJets                     = cms.InputTag("ana",    "nWJets"),
    htak4jets                  = cms.InputTag("ana",    "htak4jets"),
    htak8jets                  = cms.InputTag("ana",    "htak8jets"),
    maxetaak4                  = cms.InputTag("ana",    "maxetaak4"),
    MassLeading2AK8            = cms.InputTag("ana",    "MassLeading2AK8"),
    DeltaEtaLeading2AK8        = cms.InputTag("ana",    "DeltaEtaLeading2AK8"),
    pt1stAK8                   = cms.InputTag("ana",    "pt1stAK8"),
    pt2ndAK8                   = cms.InputTag("ana",    "pt2ndAK8"),
    mass1stAK8                 = cms.InputTag("ana",    "mass1stAK8"),
    mass2ndAK8                 = cms.InputTag("ana",    "mass2ndAK8"),
    ak4goodjets                = cms.InputTag("ana",    "ak4goodjets"),
    ak8goodjets                = cms.InputTag("ana",    "ak8goodjets"),
    tjetIdxs                   = cms.InputTag("ana",    "tjetIdxs"),
    hjetIdxs                   = cms.InputTag("ana",    "hjetIdxs"),
    wjetIdxs                   = cms.InputTag("ana",    "wjetIdxs"),
    jetAK8PtLabel              = cms.InputTag("jetsAK8", "jetAK8Pt"),
    jetAK8EtaLabel             = cms.InputTag("jetsAK8", "jetAK8Eta"),
    jetAK8PhiLabel             = cms.InputTag("jetsAK8", "jetAK8Phi"),
    jetAK8MassLabel            = cms.InputTag("jetsAK8", "jetAK8Mass"),
    jetAK8FilteredMassLabel    = cms.InputTag("jetsAK8", "jetAK8filteredMass"),
    jetAK8PrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetAK8TrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jetAK8EnergyLabel          = cms.InputTag("jetsAK8", "jetAK8Energy"),
    jetAK8FlavourLabel         = cms.InputTag("jetsAK8", "jetAK8Flavour"),
    jetAK8CSVLabel             = cms.InputTag("jetsAK8", "jetAK8CSV"),
    jetAK8JECLabel             = cms.InputTag("jetsAK8", "jetAK8jecFactor0"),
    jetAK8AreaLabel            = cms.InputTag("jetsAK8", "jetAK8jetArea"),
    jetAK8Tau1Label            = cms.InputTag("jetsAK8", "jetAK8tau1"), 
    jetAK8Tau2Label            = cms.InputTag("jetsAK8", "jetAK8tau2"),  
    jetAK8Tau3Label            = cms.InputTag("jetsAK8", "jetAK8tau3"),  
    jetAK8nSubJetsLabel        = cms.InputTag("jetsAK8", "jetAK8nSubJets"),  
    jetAK8minmassLabel         = cms.InputTag("jetsAK8", "jetAK8minmass"),  
    jetAK8VSubjetIndex0Label   = cms.InputTag("jetsAK8", "jetAK8VSubjetIndex0"),  
    jetAK8VSubjetIndex1Label   = cms.InputTag("jetsAK8", "jetAK8VSubjetIndex1"),  
    jetAK8TopSubjetIndex0Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex0"),
    jetAK8TopSubjetIndex1Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex1"),
    jetAK8TopSubjetIndex2Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex2"),
    jetAK8TopSubjetIndex3Label = cms.InputTag("jetsAK8", "jetAK8TopSubjetIndex3"),
    subjetAK8BDiscLabel        = cms.InputTag("subjetsAK8", "subjetAK8subjetCSV"),
    subjetAK8PtLabel           = cms.InputTag("subjetsAK8", "subjetAK8Pt"),
    subjetAK8EtaLabel          = cms.InputTag("subjetsAK8", "subjetAK8Eta"),
    subjetAK8PhiLabel          = cms.InputTag("subjetsAK8", "subjetAK8Phi"),
    subjetAK8MassLabel         = cms.InputTag("subjetsAK8", "subjetAK8Mass"),
    subjetCmsTopTagBDiscLabel  = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagCSV"),
    subjetCmsTopTagPtLabel     = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagPt"),
    subjetCmsTopTagEtaLabel    = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagEta"),
    subjetCmsTopTagPhiLabel    = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagPhi"),
    subjetCmsTopTagMassLabel   = cms.InputTag("subjetsCmsTopTag", "subjetsCmsTopTagMass"),
    jetAK4PtLabel              = cms.InputTag("jetsAK4", "jetAK4Pt"),
    jetAK4EtaLabel             = cms.InputTag("jetsAK4", "jetAK4Eta"),
    jetAK4PhiLabel             = cms.InputTag("jetsAK4", "jetAK4Phi"),
    jetAK4MassLabel            = cms.InputTag("jetsAK4", "jetAK4Mass"),
    jetAK4EnergyLabel          = cms.InputTag("jetsAK4", "jetAK4Energy"),
    jetAK4FlavourLabel         = cms.InputTag("jetsAK4", "jetAK4Flavour"),
    jetAK4CSVLabel             = cms.InputTag("jetsAK4", "jetAK4CSV"),
    jetAK4JECLabel             = cms.InputTag("jetsAK4", "jetAK4jecFactor0"),
    jetAK4nHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4neutralHadronEnergy"),
    jetAK4nEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4neutralEmEnergy"),
    jetAK4HFHadronEnergyLabel  = cms.InputTag("jetsAK4", "jetAK4HFHadronEnergy"),
    jetAK4cHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4chargedHadronEnergy"),
    jetAK4cEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4chargedEmEnergy"),
    jetAK4numDaughtersLabel    = cms.InputTag("jetsAK4", "jetAK4numberOfDaughters"),
    jetAK4cMultipLabel         = cms.InputTag("jetsAK4", "jetAK4chargedMultiplicity"),
    jetAK4YLabel               = cms.InputTag("jetsAK4", "jetAK4Y"),
    jetAK4AreaLabel            = cms.InputTag("jetsAK4", "jetAK4jetArea"),
    hltPaths                   = cms.vstring ("HLT_PFJet260_v1", "HLT_AK8PFJet360TrimMod_Mass30_v1", "HLT_PFHT900_v1"), 
    AK4JetSelParams            = defaultAK4JetSelectionParameters.clone(), 
    BTaggedAK4JetSelParams     = defaultBTaggedAK4JetSelectionParameters.clone(), 
    AK8JetSelParams            = defaultAK8JetSelectionParameters.clone(), 
    TJetSelParams              = defaultTJetSelectionParameters.clone(), 
    HJetSelParams              = defaultHJetSelectionParameters.clone(), 
    WJetSelParams              = defaultWJetSelectionParameters.clone(), 
    ak8jetsPtMin               = cms.double  (300),
    ak8jetsEtaMax              = cms.double  (2.4),
    ak4jetsPtMin               = cms.double  (30),
    ak4jetsEtaMax              = cms.double  (5.0),
    HTMin                      = cms.double  (700.), 
    wmassmin                   = cms.double  (50.), 
    wmassmax                   = cms.double  (100.), 
    scaledmassdropmin          = cms.double  (0.), 
    scaledmassdropmax          = cms.double  (0.5), 
    )

process.TFileService = cms.Service("TFileService",
       fileName = cms.string("SingleTprimeAna.root")
       )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("SingleTprimeAnaEvts.root"),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring('p')
      ),
    outputCommands = cms.untracked.vstring(
      "drop *",
      "keep *_genPart_*_*", 
      "keep *_jetsAK4_*_*", 
      "keep *_*_npv_*", 
      "keep *_ana_*_*",
      "keep *_vjj_*_*",
      )
    )

process.p = cms.Path(process.ana 
    *process.vjj
    *process.sel 
    )

process.outpath = cms.EndPath(process.out)
