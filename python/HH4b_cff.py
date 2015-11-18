import FWCore.ParameterSet.Config as cms
from Analysis.VLQAna.JetSelector_cfi import *

hh4b = cms.EDFilter("HH4b",
    evtwtGen            = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV             = cms.InputTag("evtcleaner","evtwtPV"),
    npv                 = cms.InputTag("evtcleaner","npv"),
    jetAK8selParams     = defaultAK8JetSelectionParameters,
    jetHTaggedselParams = defaultHJetSelectionParameters.clone(
      scaleJetP4        = cms.bool(False),
      scaledJetMass     = cms.double(125.0), 
      jetPrunedMassMin    = cms.double(90) ,
      jetPrunedMassMax    = cms.double(145) ,
      btaggedcsvlOP       = cms.double(0.605) , 
      btaggedcsvmOP       = cms.double(0.890) , 
      btaggedcsvtOP       = cms.double(0.970) , 
      ),
    )


