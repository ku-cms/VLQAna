#ifndef ANALYSIS_VLQAna_MUONMAKER_HH
#define ANALYSIS_VLQAna_MUONMAKER_HH

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Muon.h"

class MuonMaker {
  public:
    enum MUONIDTYPES_t {LOOSE, TIGHT} ; 
    MuonMaker (edm::ParameterSet const& pars) ; 
    ~MuonMaker () ; 
    void operator () (edm::Event& evt, vlq::MuonCollection& muons) ; 

  private:
    MUONIDTYPES_t type_ ; 
    edm::InputTag l_muCharge                   ;
    edm::InputTag l_muD0                       ;
    edm::InputTag l_muD0err                    ;
    edm::InputTag l_muDxy                      ;
    edm::InputTag l_muDxyerr                   ;
    edm::InputTag l_muDz                       ;
    edm::InputTag l_muDzerr                    ;
    edm::InputTag l_muE                        ;
    edm::InputTag l_muEta                      ;
    edm::InputTag l_muGenMuonCharge            ;
    edm::InputTag l_muGenMuonE                 ;
    edm::InputTag l_muGenMuonEta               ;
    edm::InputTag l_muGenMuonPhi               ;
    edm::InputTag l_muGenMuonPt                ;
    edm::InputTag l_muGenMuonY                 ;
    edm::InputTag l_muGlbTrkNormChi2           ;
    edm::InputTag l_muInTrkNormChi2            ;
    edm::InputTag l_muIsGlobalMuon             ;
    edm::InputTag l_muIsLooseMuon              ;
    edm::InputTag l_muIsPFMuon                 ;
    edm::InputTag l_muIsSoftMuon               ;
    edm::InputTag l_muIsTightMuon              ;
    edm::InputTag l_muIsTrackerMuon            ;
    edm::InputTag l_muIso04                    ;
    edm::InputTag l_muKey                      ;
    edm::InputTag l_muMass                     ;
    edm::InputTag l_muNumberMatchedStations    ;
    edm::InputTag l_muNumberOfPixelLayers      ;
    edm::InputTag l_muNumberOfValidTrackerHits ;
    edm::InputTag l_muNumberTrackerLayers      ;
    edm::InputTag l_muNumberValidMuonHits      ;
    edm::InputTag l_muNumberValidPixelHits     ;
    edm::InputTag l_muPhi                      ;
    edm::InputTag l_muPt                       ;
    edm::InputTag l_muSumChargedHadronPt       ;
    edm::InputTag l_muSumNeutralHadronPt       ;
    edm::InputTag l_muSumPUPt                  ;
    edm::InputTag l_muSumPhotonPt              ;
    edm::InputTag l_muY                        ;

    double muPtMin_ ; 
    double muPtMax_ ; 
    double muAbsEtaMax_ ; 
    double muIsoMin_ ; 
    double muIsoMax_ ; 

};
#endif
