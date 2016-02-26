import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *
ana = cms.EDFilter("VLQAna", 
    isData                     = cms.InputTag("evtcleaner","isData"), 
    hltdecision                = cms.InputTag("evtcleaner","hltdecision"), 
    evttype                    = cms.InputTag("evtcleaner","evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner","evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner","evtwtPV"),
    evtwtPVLow                 = cms.InputTag("evtcleaner","evtwtPVLow"),
    evtwtPVHigh                = cms.InputTag("evtcleaner","evtwtPVHigh"),
    npv                        = cms.InputTag("evtcleaner","npv"),
    npuTrue                    = cms.InputTag("evtcleaner","npuTrue"),
    htHat                      = cms.InputTag("evtcleaner","htHat"),
    lhewtids                   = cms.InputTag("evtcleaner","lhewtids"),
    lhewts                     = cms.InputTag("evtcleaner","lhewts"), 
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetAntiHTaggedselParams    = defaultHJetSelectionParameters.clone(
      subjetCSVMin = cms.double(-1000000) ,
      subjetCSVMax = cms.double(0.605) ,
      ), 
    jetTopTaggedselParams      = defaultTJetSelectionParameters.clone(
      jettau3Bytau2Max    = cms.double(0.54) ,
      subjetHighestCSVMin = cms.double(0.79) ,
      ), 
    HTMin                      = cms.double  (1000.), 
    doBTagSFUnc                = cms.bool(False), 
    storePreselEvts            = cms.bool(False), 
    doPreselOnly               = cms.bool(False), 
    )

