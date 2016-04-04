#ifndef ANALYSIS_VLQAna_MUONMAKER_HH
#define ANALYSIS_VLQAna_MUONMAKER_HH

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Muon.h"

class MuonMaker {
  public:
    enum MUONIDTYPES_t {LOOSE, TIGHT} ; 
    MuonMaker (edm::ParameterSet const&, edm::ConsumesCollector && iC) ; 
    ~MuonMaker () ; 
    void operator () (edm::Event& evt, vlq::MuonCollection& muons) ; 

  private:
    MUONIDTYPES_t type_ ; 
    edm::EDGetTokenT<std::vector<float>> t_muCharge                   ;
    edm::EDGetTokenT<std::vector<float>> t_muD0                       ;
    edm::EDGetTokenT<std::vector<float>> t_muD0err                    ;
    edm::EDGetTokenT<std::vector<float>> t_muDxy                      ;
    edm::EDGetTokenT<std::vector<float>> t_muDxyerr                   ;
    edm::EDGetTokenT<std::vector<float>> t_muDz                       ;
    edm::EDGetTokenT<std::vector<float>> t_muDzerr                    ;
    edm::EDGetTokenT<std::vector<float>> t_muE                        ;
    edm::EDGetTokenT<std::vector<float>> t_muEta                      ;
    edm::EDGetTokenT<std::vector<float>> t_muGenMuonCharge            ;
    edm::EDGetTokenT<std::vector<float>> t_muGenMuonE                 ;
    edm::EDGetTokenT<std::vector<float>> t_muGenMuonEta               ;
    edm::EDGetTokenT<std::vector<float>> t_muGenMuonPhi               ;
    edm::EDGetTokenT<std::vector<float>> t_muGenMuonPt                ;
    edm::EDGetTokenT<std::vector<float>> t_muGenMuonY                 ;
    edm::EDGetTokenT<std::vector<float>> t_muGlbTrkNormChi2           ;
    edm::EDGetTokenT<std::vector<float>> t_muInTrkNormChi2            ;
    edm::EDGetTokenT<std::vector<float>> t_muIsGlobalMuon             ;
    edm::EDGetTokenT<std::vector<float>> t_muIsLooseMuon              ;
    edm::EDGetTokenT<std::vector<float>> t_muIsPFMuon                 ;
    edm::EDGetTokenT<std::vector<float>> t_muIsSoftMuon               ;
    edm::EDGetTokenT<std::vector<float>> t_muIsTightMuon              ;
    edm::EDGetTokenT<std::vector<float>> t_muIsTrackerMuon            ;
    edm::EDGetTokenT<std::vector<float>> t_muIso04                    ;
    edm::EDGetTokenT<std::vector<float>> t_muKey                      ;
    edm::EDGetTokenT<std::vector<float>> t_muMass                     ;
    edm::EDGetTokenT<std::vector<float>> t_muNumberMatchedStations    ;
    edm::EDGetTokenT<std::vector<float>> t_muNumberOfPixelLayers      ;
    edm::EDGetTokenT<std::vector<float>> t_muNumberOfValidTrackerHits ;
    edm::EDGetTokenT<std::vector<float>> t_muNumberTrackerLayers      ;
    edm::EDGetTokenT<std::vector<float>> t_muNumberValidMuonHits      ;
    edm::EDGetTokenT<std::vector<float>> t_muNumberValidPixelHits     ;
    edm::EDGetTokenT<std::vector<float>> t_muPhi                      ;
    edm::EDGetTokenT<std::vector<float>> t_muPt                       ;
    edm::EDGetTokenT<std::vector<float>> t_muSumChargedHadronPt       ;
    edm::EDGetTokenT<std::vector<float>> t_muSumNeutralHadronPt       ;
    edm::EDGetTokenT<std::vector<float>> t_muSumPUPt                  ;
    edm::EDGetTokenT<std::vector<float>> t_muSumPhotonPt              ;
    edm::EDGetTokenT<std::vector<float>> t_muY                        ;

    double muPtMin_ ; 
    double muPtMax_ ; 
    double muAbsEtaMax_ ; 
    double muIsoMin_ ; 
    double muIsoMax_ ; 

};
#endif
