import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *
ana = cms.EDFilter("VLQAna", 
    evttype                    = cms.InputTag("evtcleaner","evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner","evtwtPV"),
    npv                        = cms.InputTag("evtcleaner","npv"),
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK4BTaggedselParams     = defaultBTaggedAK4JetSelectionParameters, 
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetWTaggedselParams        = defaultWJetSelectionParameters,
    jetTopTaggedselParams      = defaultTJetSelectionParameters, 
    HTMin                      = cms.double  (1000.), 
    )

