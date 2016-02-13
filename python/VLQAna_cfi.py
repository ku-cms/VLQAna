import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *
ana = cms.EDFilter("VLQAna", 
    evttype                    = cms.InputTag("evtcleaner","evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner","evtwtPV"),
    npv                        = cms.InputTag("evtcleaner","npv"),
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetAntiHTaggedselParams    = defaultAK8JetSelectionParameters.clone(
      subjetCSVMax = cms.double(0.605) ,
      ), 
    jetTopTaggedselParams      = defaultTJetSelectionParameters.clone(
      jettau3Bytau2Max    = cms.double(0.61) ,
      subjetHighestCSVMin = cms.double(0.66) ,
      ), 
    HTMin                      = cms.double  (1000.), 
    doBTagSFUnc                = cms.bool(False), 
    )

