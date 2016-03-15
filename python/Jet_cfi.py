import FWCore.ParameterSet.Config as cms

defaultAK4JetParameters = cms.PSet(
    npvLabel                = cms.InputTag("eventUserData", "npv"),
    rhoLabel                = cms.InputTag("fixedGridRhoFastjetAll", ""),
    jetPtLabel              = cms.InputTag("jetsAK4", "jetAK4Pt"),
    jetEtaLabel             = cms.InputTag("jetsAK4", "jetAK4Eta"),
    jetPhiLabel             = cms.InputTag("jetsAK4", "jetAK4Phi"),
    jetMassLabel            = cms.InputTag("jetsAK4", "jetAK4Mass"),
    jetEnergyLabel          = cms.InputTag("jetsAK4", "jetAK4E"),
    jetPartonFlavourLabel   = cms.InputTag("jetsAK4", "jetAK4PartonFlavour"),
    jetHadronFlavourLabel   = cms.InputTag("jetsAK4", "jetAK4HadronFlavour"),
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
    jetGenJetPtLabel        = cms.InputTag("jetsAK4", "jetAK4GenJetPt"),
    jetGenJetEtaLabel       = cms.InputTag("jetsAK4", "jetAK4GenJetEta"),
    jetGenJetPhiLabel       = cms.InputTag("jetsAK4", "jetAK4GenJetPhi"),
    )

defaultAK8JetParameters = defaultAK4JetParameters.clone( 
    npvLabel                = cms.InputTag("eventUserData", "npv"),
    rhoLabel                = cms.InputTag("fixedGridRhoFastjetAll", ""),
    jetPtLabel              = cms.InputTag("jetsAK8", "jetAK8Pt"),
    jetEtaLabel             = cms.InputTag("jetsAK8", "jetAK8Eta"),
    jetPhiLabel             = cms.InputTag("jetsAK8", "jetAK8Phi"),
    jetMassLabel            = cms.InputTag("jetsAK8", "jetAK8Mass"),
    jetEnergyLabel          = cms.InputTag("jetsAK8", "jetAK8E"),
    jetPrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetTrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jetFilteredMassLabel    = cms.InputTag("jetsAK8", "jetAK8filteredMass"),
    jetSoftDropMassLabel    = cms.InputTag("jetsAK8", "jetAK8softDropMass"),
    jetPartonFlavourLabel   = cms.InputTag("jetsAK8", "jetAK8PartonFlavour"),
    jetHadronFlavourLabel   = cms.InputTag("jetsAK8", "jetAK8HadronFlavour"),
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
    jetGenJetPtLabel        = cms.InputTag("jetsAK8", "jetAK8GenJetPt"),
    jetGenJetEtaLabel       = cms.InputTag("jetsAK8", "jetAK8GenJetEta"),
    jetGenJetPhiLabel       = cms.InputTag("jetsAK8", "jetAK8GenJetPhi"),
    )

defaultJetSubstructureParameters = cms.PSet( 
    jettau1Label            = cms.InputTag("jetsAK8", "jetAK8tau1"), 
    jettau2Label            = cms.InputTag("jetsAK8", "jetAK8tau2"),  
    jettau3Label            = cms.InputTag("jetsAK8", "jetAK8tau3"),  
    jetPrunedMassLabel      = cms.InputTag("jetsAK8", "jetAK8prunedMass"),
    jetTrimmedMassLabel     = cms.InputTag("jetsAK8", "jetAK8trimmedMass"),
    jetFilteredMassLabel    = cms.InputTag("jetsAK8", "jetAK8filteredMass"),
    jetSoftDropMassLabel    = cms.InputTag("jetsAK8", "jetAK8softDropMass"),
    jettopMassLabel         = cms.InputTag("jetsAK8", "jetAK8topMass"),
    jetWMassLabel           = cms.InputTag("jetsAK8", "jetAK8wMass"),
    jetminMassLabel         = cms.InputTag("jetsAK8", "jetAK8minmass"),  
    jetnSubJetsLabel        = cms.InputTag("jetsAK8", "jetAK8nSubJets"),  
    vjetsjIdx0Label         = cms.InputTag("jetsAK8", "jetAK8vSubjetIndex0"),  
    vjetsjIdx1Label         = cms.InputTag("jetsAK8", "jetAK8vSubjetIndex1"),  
    tjetsjIdx0Label         = cms.InputTag("jetsAK8", "jetAK8topSubjetIndex0"),  
    tjetsjIdx1Label         = cms.InputTag("jetsAK8", "jetAK8topSubjetIndex1"),  
    tjetsjIdx2Label         = cms.InputTag("jetsAK8", "jetAK8topSubjetIndex2"),  
    tjetsjIdx3Label         = cms.InputTag("jetsAK8", "jetAK8topSubjetIndex3"),  
    )

defaultSubjetParameters = cms.PSet(
    jetPtLabel              = cms.InputTag("subjetsAK8", "subjetAK8Pt"),
    jetEtaLabel             = cms.InputTag("subjetsAK8", "subjetAK8Eta"),
    jetPhiLabel             = cms.InputTag("subjetsAK8", "subjetAK8Phi"),
    jetMassLabel            = cms.InputTag("subjetsAK8", "subjetAK8Mass"),
    jetCSVLabel             = cms.InputTag("subjetsAK8", "subjetAK8CSV"),
    jetPartonFlavourLabel   = cms.InputTag("subjetsAK8", "subjetAK8PartonFlavour"),
    jetHadronFlavourLabel   = cms.InputTag("subjetsAK8", "subjetAK8HadronFlavour"),
    jetGenJetPtLabel        = cms.InputTag("subjetsAK8", "subjetAK8GenJetPt"),
    jetGenJetEtaLabel       = cms.InputTag("subjetsAK8", "subjetAK8GenJetEta"),
    jetGenJetPhiLabel       = cms.InputTag("subjetsAK8", "subjetAK8GenJetPhi"),
    )

defaultTopTaggedSubjetParameters = cms.PSet(
    jetPtLabel              = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagPt"),
    jetEtaLabel             = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagEta"),
    jetPhiLabel             = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagPhi"),
    jetMassLabel            = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagMass"),
    jetCSVLabel             = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagCSV"),
    jetPartonFlavourLabel   = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagPartonFlavour"),
    jetHadronFlavourLabel   = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagHadronFlavour"),
    jetGenJetPtLabel        = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagGenJetPt"),
    jetGenJetEtaLabel       = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagGenJetEta"),
    jetGenJetPhiLabel       = cms.InputTag("subjetsCmsTopTag", "subjetCmsTopTagGenJetPhi"),
    )
