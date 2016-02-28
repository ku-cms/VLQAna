import FWCore.ParameterSet.Config as cms
from Analysis.VLQAna.JetSelector_cfi import *

hh4b = cms.EDFilter("HH4b",
    runno               = cms.InputTag("evtcleaner","runno"), 
    lumisec             = cms.InputTag("evtcleaner","lumisec"), 
    evtno               = cms.InputTag("evtcleaner","evtno"), 
    isData              = cms.InputTag("evtcleaner","isData"), 
    evtwtGen            = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV             = cms.InputTag("evtcleaner","evtwtPV"),
    evtwtPVLow          = cms.InputTag("evtcleaner","evtwtPVLow"),
    evtwtPVHigh         = cms.InputTag("evtcleaner","evtwtPVHigh"),
    htHat               = cms.InputTag("evtcleaner","htHat"),
    lhewtids            = cms.InputTag("evtcleaner","lhewtids"),
    lhewts              = cms.InputTag("evtcleaner","lhewts"), 
    hltdecision         = cms.InputTag("evtcleaner","hltdecision"), 
    npv                 = cms.InputTag("evtcleaner","npv"),
    npuTrue             = cms.InputTag("evtcleaner","npuTrue"),
    jetAK8selParams     = defaultAK8JetSelectionParameters.clone(
      jetAbsEtaMax = cms.double(100), 
      ),
    jetHTaggedselParams = defaultHJetSelectionParameters.clone(
      jetPrunedMassMin    = cms.double(90) ,
      jetPrunedMassMax    = cms.double(145) ,
      ),
    )
