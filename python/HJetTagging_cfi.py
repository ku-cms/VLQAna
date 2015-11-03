import FWCore.ParameterSet.Config as cms
from Analysis.VLQAna.HbbCandidateProducer_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *

hjets = cms.EDFilter("HJetTagging",
    HbbCandsLabel              = cms.InputTag("hbb", "HbbCandidates"),
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    )
