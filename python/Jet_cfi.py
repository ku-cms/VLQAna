import FWCore.ParameterSet.Config as cms

defaultAK4JetParameters = cms.PSet(
    jetPtLabel              = cms.InputTag("jetsAK4", "jetAK4Pt"),
    jetEtaLabel             = cms.InputTag("jetsAK4", "jetAK4Eta"),
    jetPhiLabel             = cms.InputTag("jetsAK4", "jetAK4Phi"),
    jetMassLabel            = cms.InputTag("jetsAK4", "jetAK4Mass"),
    jetEnergyLabel          = cms.InputTag("jetsAK4", "jetAK4Energy"),
    jetFlavourLabel         = cms.InputTag("jetsAK4", "jetAK4Flavour"),
    jetCSVLabel             = cms.InputTag("jetsAK4", "jetAK4CSV"),
    jetJECLabel             = cms.InputTag("jetsAK4", "jetAK4jecFactor0"),
    jetnHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4neutralHadronEnergy"),
    jetnEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4neutralEmEnergy"),
    jetHFHadronEnergyLabel  = cms.InputTag("jetsAK4", "jetAK4HFHadronEnergy"),
    jetcHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4chargedHadronEnergy"),
    jetcEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4chargedEmEnergy"),
    jetnumDaughtersLabel    = cms.InputTag("jetsAK4", "jetAK4numberOfDaughters"),
    jetcMultipLabel         = cms.InputTag("jetsAK4", "jetAK4chargedMultiplicity"),
    jetYLabel               = cms.InputTag("jetsAK4", "jetAK4Y"),
    jetAreaLabel            = cms.InputTag("jetsAK4", "jetAK4jetArea"),
    )

defaultAK8JetParameters = defaultAK4JetParameters.clone( 
    jetPtLabel              = cms.InputTag("jetsAK8", "jetAK8Pt"),
    jetEtaLabel             = cms.InputTag("jetsAK8", "jetAK8Eta"),
    jetPhiLabel             = cms.InputTag("jetsAK8", "jetAK8Phi"),
    jetMassLabel            = cms.InputTag("jetsAK8", "jetAK8Mass"),
    jetPrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetTrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jetEnergyLabel          = cms.InputTag("jetsAK8", "jetAK8Energy"),
    jetFlavourLabel         = cms.InputTag("jetsAK8", "jetAK8Flavour"),
    jetCSVLabel             = cms.InputTag("jetsAK8", "jetAK8CSV"),
    jetJECLabel             = cms.InputTag("jetsAK8", "jetAK8jecFactor0"),
    jetnHadEnergyLabel      = cms.InputTag("jetsAK8", "jetAK8neutralHadronEnergy"),
    jetnEMEnergyLabel       = cms.InputTag("jetsAK8", "jetAK8neutralEmEnergy"),
    jetHFHadronEnergyLabel  = cms.InputTag("jetsAK8", "jetAK8HFHadronEnergy"),
    jetcHadEnergyLabel      = cms.InputTag("jetsAK8", "jetAK8chargedHadronEnergy"),
    jetcEMEnergyLabel       = cms.InputTag("jetsAK8", "jetAK8chargedEmEnergy"),
    jetnumDaughtersLabel    = cms.InputTag("jetsAK8", "jetAK8numberOfDaughters"),
    jetcMultipLabel         = cms.InputTag("jetsAK8", "jetAK8chargedMultiplicity"),
    jetYLabel               = cms.InputTag("jetsAK8", "jetAK8Y"),
    jetAreaLabel            = cms.InputTag("jetsAK8", "jetAK8jetArea"),
    )

defaultJetSubstructureParameters = cms.PSet( 
    jettau1Label            = cms.InputTag("jetsAK8", "jetAK8tau1"), 
    jettau2Label            = cms.InputTag("jetsAK8", "jetAK8tau2"),  
    jettau3Label            = cms.InputTag("jetsAK8", "jetAK8tau3"),  
    jetPrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetTrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jettopMassLabel         = cms.InputTag("jetsAK8", "jetAK8topMass"),
    jetWMassLabel           = cms.InputTag("jetsAK8", "jetAK8wMass"),
    jetminMassLabel         = cms.InputTag("jetsAK8", "jetAK8minmass"),  
    jetnSubJetsLabel        = cms.InputTag("jetsAK8", "jetAK8nSubJets"),  
    jetsubjetIndex0Label    = cms.InputTag("jetsAK8", "jetAK8subjetIndex0"),  
    jetsubjetIndex1Label    = cms.InputTag("jetsAK8", "jetAK8subjetIndex1"),  
    jetsubjetIndex2Label    = cms.InputTag("jetsAK8", "jetAK8subjetIndex2"),  
    jetsubjetIndex3Label    = cms.InputTag("jetsAK8", "jetAK8subjetIndex3"),  
    #jetTopSubjetIndex0Label = cms.InputTag("jetsCmsTopTag", "jetsCmsTopTagsubjetIndex0"),
    #jetTopSubjetIndex1Label = cms.InputTag("jetsCmsTopTag", "jetsCmsTopTagsubjetIndex1"),
    #jetTopSubjetIndex2Label = cms.InputTag("jetsCmsTopTag", "jetsCmsTopTagsubjetIndex2"),
    #jetTopSubjetIndex3Label = cms.InputTag("jetsCmsTopTag", "jetsCmsTopTagsubjetIndex3"),
    )

#defaultHJetParameters = defaultAK8JetParameters.clone().extend(defaultJetSubstructureParameters)

defaultSubjetParameters = cms.PSet(
    jetPtLabel         = cms.InputTag("subjetsAK8", "subjetAK8Pt"),
    jetEtaLabel        = cms.InputTag("subjetsAK8", "subjetAK8Eta"),
    jetPhiLabel        = cms.InputTag("subjetsAK8", "subjetAK8Phi"),
    jetMassLabel       = cms.InputTag("subjetsAK8", "subjetAK8Mass"),
    jetCSVLabel        = cms.InputTag("subjetsAK8", "subjetAK8subjetCSV"),
    )
