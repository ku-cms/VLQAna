import FWCore.ParameterSet.Config as cms
from Analysis.VLQAna.JetSelector_cfi import *

hh4b = cms.EDFilter("HH4b",
    evtwtGen            = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV             = cms.InputTag("evtcleaner","evtwtPV"),
    partonBin           = cms.InputTag("evtcleaner","partonBin"),
    hltdecision         = cms.InputTag("evtcleaner","hltdecision"), 
    npv                 = cms.InputTag("evtcleaner","npv"),
    jetAK8selParams     = defaultAK8JetSelectionParameters.clone(
      jetAbsEtaMax = cms.double(100), 
      ),
    jetHTaggedselParams = defaultHJetSelectionParameters.clone(
      jetPrunedMassMin    = cms.double(90) ,
      jetPrunedMassMax    = cms.double(145) ,
      ),
    )
