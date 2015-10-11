#include "Analysis/EventSelector/interface/MuonMaker.h" 
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;
using namespace edm ; 

MuonMaker::MuonMaker (edm::ParameterSet const& pars) : 
  l_muCharge                   (pars.getParameter<edm::InputTag>("muChargeLabel")), 
  l_muD0                       (pars.getParameter<edm::InputTag>("muD0Label")), 
  l_muD0err                    (pars.getParameter<edm::InputTag>("muD0errLabel")), 
  l_muDxy                      (pars.getParameter<edm::InputTag>("muDxyLabel")), 
  l_muDxyerr                   (pars.getParameter<edm::InputTag>("muDxyerrLabel")), 
  l_muDz                       (pars.getParameter<edm::InputTag>("muDzLabel")), 
  l_muDzerr                    (pars.getParameter<edm::InputTag>("muDzerrLabel")), 
  l_muE                        (pars.getParameter<edm::InputTag>("muELabel")), 
  l_muEta                      (pars.getParameter<edm::InputTag>("muEtaLabel")), 
  l_muGenMuonCharge            (pars.getParameter<edm::InputTag>("muGenMuonChargeLabel")), 
  l_muGenMuonE                 (pars.getParameter<edm::InputTag>("muGenMuonELabel")), 
  l_muGenMuonEta               (pars.getParameter<edm::InputTag>("muGenMuonEtaLabel")), 
  l_muGenMuonPhi               (pars.getParameter<edm::InputTag>("muGenMuonPhiLabel")), 
  l_muGenMuonPt                (pars.getParameter<edm::InputTag>("muGenMuonPtLabel")), 
  l_muGenMuonY                 (pars.getParameter<edm::InputTag>("muGenMuonYLabel")), 
  l_muGlbTrkNormChi2           (pars.getParameter<edm::InputTag>("muGlbTrkNormChi2Label")), 
  l_muInTrkNormChi2            (pars.getParameter<edm::InputTag>("muInTrkNormChi2Label")), 
  l_muIsGlobalMuon             (pars.getParameter<edm::InputTag>("muIsGlobalMuonLabel")), 
  l_muIsLooseMuon              (pars.getParameter<edm::InputTag>("muIsLooseMuonLabel")), 
  l_muIsPFMuon                 (pars.getParameter<edm::InputTag>("muIsPFMuonLabel")), 
  l_muIsSoftMuon               (pars.getParameter<edm::InputTag>("muIsSoftMuonLabel")), 
  l_muIsTightMuon              (pars.getParameter<edm::InputTag>("muIsTightMuonLabel")), 
  l_muIsTrackerMuon            (pars.getParameter<edm::InputTag>("muIsTrackerMuonLabel")), 
  l_muIso04                    (pars.getParameter<edm::InputTag>("muIso04Label")), 
  l_muKey                      (pars.getParameter<edm::InputTag>("muKeyLabel")), 
  l_muMass                     (pars.getParameter<edm::InputTag>("muMassLabel")), 
  l_muNumberMatchedStations    (pars.getParameter<edm::InputTag>("muNumberMatchedStationsLabel")), 
  l_muNumberOfPixelLayers      (pars.getParameter<edm::InputTag>("muNumberOfPixelLayersLabel")), 
  l_muNumberOfValidTrackerHits (pars.getParameter<edm::InputTag>("muNumberOfValidTrackerHitsLabel")), 
  l_muNumberTrackerLayers      (pars.getParameter<edm::InputTag>("muNumberTrackerLayersLabel")), 
  l_muNumberValidMuonHits      (pars.getParameter<edm::InputTag>("muNumberValidMuonHitsLabel")), 
  l_muNumberValidPixelHits     (pars.getParameter<edm::InputTag>("muNumberValidPixelHitsLabel")), 
  l_muPhi                      (pars.getParameter<edm::InputTag>("muPhiLabel")), 
  l_muPt                       (pars.getParameter<edm::InputTag>("muPtLabel")), 
  l_muSumChargedHadronPt       (pars.getParameter<edm::InputTag>("muSumChargedHadronPtLabel")), 
  l_muSumNeutralHadronPt       (pars.getParameter<edm::InputTag>("muSumNeutralHadronPtLabel")), 
  l_muSumPUPt                  (pars.getParameter<edm::InputTag>("muSumPUPtLabel")), 
  l_muSumPhotonPt              (pars.getParameter<edm::InputTag>("muSumPhotonPtLabel")), 
  l_muY                        (pars.getParameter<edm::InputTag>("muYLabel")),
  muPtMin_ (pars.getParameter<double>("muPtMin")), 
  muPtMax_ (pars.getParameter<double>("muPtMax")), 
  muAbsEtaMax_ (pars.getParameter<double>("muAbsEtaMax")), 
  muIsoMin_ (pars.getParameter<double>("muIsoMin")), 
  muIsoMax_ (pars.getParameter<double>("muIsoMax"))  
{
  std::string muidtypestr = pars.getParameter<std::string>("muidtype") ; 
  if ( muidtypestr == "LOOSE" ) type_ = LOOSE ; 
  else if ( muidtypestr == "TIGHT" ) type_ = TIGHT ; 
  else edm::LogError("MuonMaker::MuonMaker") << " >>>> WrongMuonIdType: " << type_<< " Check muon id type !!!" ; 
}

MuonMaker::~MuonMaker () {} 

void MuonMaker::operator () (edm::Event& evt, vlq::MuonCollection& muons) { 

  Handle<vector<float>> h_muCharge                  ; evt.getByLabel(l_muCharge                  ,h_muCharge                  );
  Handle<vector<float>> h_muD0                      ; evt.getByLabel(l_muD0                      ,h_muD0                      );
  Handle<vector<float>> h_muD0err                   ; evt.getByLabel(l_muD0err                   ,h_muD0err                   );
  Handle<vector<float>> h_muDxy                     ; evt.getByLabel(l_muDxy                     ,h_muDxy                     );
  Handle<vector<float>> h_muDxyerr                  ; evt.getByLabel(l_muDxyerr                  ,h_muDxyerr                  );
  Handle<vector<float>> h_muDz                      ; evt.getByLabel(l_muDz                      ,h_muDz                      );
  Handle<vector<float>> h_muDzerr                   ; evt.getByLabel(l_muDzerr                   ,h_muDzerr                   );
  Handle<vector<float>> h_muE                       ; evt.getByLabel(l_muE                       ,h_muE                       );
  Handle<vector<float>> h_muEta                     ; evt.getByLabel(l_muEta                     ,h_muEta                     );
  Handle<vector<float>> h_muGenMuonCharge           ; evt.getByLabel(l_muGenMuonCharge           ,h_muGenMuonCharge           );
  Handle<vector<float>> h_muGenMuonE                ; evt.getByLabel(l_muGenMuonE                ,h_muGenMuonE                );
  Handle<vector<float>> h_muGenMuonEta              ; evt.getByLabel(l_muGenMuonEta              ,h_muGenMuonEta              );
  Handle<vector<float>> h_muGenMuonPhi              ; evt.getByLabel(l_muGenMuonPhi              ,h_muGenMuonPhi              );
  Handle<vector<float>> h_muGenMuonPt               ; evt.getByLabel(l_muGenMuonPt               ,h_muGenMuonPt               );
  Handle<vector<float>> h_muGenMuonY                ; evt.getByLabel(l_muGenMuonY                ,h_muGenMuonY                );
  Handle<vector<float>> h_muGlbTrkNormChi2          ; evt.getByLabel(l_muGlbTrkNormChi2          ,h_muGlbTrkNormChi2          );
  Handle<vector<float>> h_muInTrkNormChi2           ; evt.getByLabel(l_muInTrkNormChi2           ,h_muInTrkNormChi2           );
  Handle<vector<float>> h_muIsGlobalMuon            ; evt.getByLabel(l_muIsGlobalMuon            ,h_muIsGlobalMuon            );
  Handle<vector<float>> h_muIsLooseMuon             ; evt.getByLabel(l_muIsLooseMuon             ,h_muIsLooseMuon             );
  Handle<vector<float>> h_muIsPFMuon                ; evt.getByLabel(l_muIsPFMuon                ,h_muIsPFMuon                );
  Handle<vector<float>> h_muIsSoftMuon              ; evt.getByLabel(l_muIsSoftMuon              ,h_muIsSoftMuon              );
  Handle<vector<float>> h_muIsTightMuon             ; evt.getByLabel(l_muIsTightMuon             ,h_muIsTightMuon             );
  Handle<vector<float>> h_muIsTrackerMuon           ; evt.getByLabel(l_muIsTrackerMuon           ,h_muIsTrackerMuon           );
  Handle<vector<float>> h_muIso04                   ; evt.getByLabel(l_muIso04                   ,h_muIso04                   );
  Handle<vector<float>> h_muKey                     ; evt.getByLabel(l_muKey                     ,h_muKey                     );
  Handle<vector<float>> h_muMass                    ; evt.getByLabel(l_muMass                    ,h_muMass                    );
  Handle<vector<float>> h_muNumberMatchedStations   ; evt.getByLabel(l_muNumberMatchedStations   ,h_muNumberMatchedStations   );
  Handle<vector<float>> h_muNumberOfPixelLayers     ; evt.getByLabel(l_muNumberOfPixelLayers     ,h_muNumberOfPixelLayers     );
  Handle<vector<float>> h_muNumberOfValidTrackerHits; evt.getByLabel(l_muNumberOfValidTrackerHits,h_muNumberOfValidTrackerHits);
  Handle<vector<float>> h_muNumberTrackerLayers     ; evt.getByLabel(l_muNumberTrackerLayers     ,h_muNumberTrackerLayers     );
  Handle<vector<float>> h_muNumberValidMuonHits     ; evt.getByLabel(l_muNumberValidMuonHits     ,h_muNumberValidMuonHits     );
  Handle<vector<float>> h_muNumberValidPixelHits    ; evt.getByLabel(l_muNumberValidPixelHits    ,h_muNumberValidPixelHits    );
  Handle<vector<float>> h_muPhi                     ; evt.getByLabel(l_muPhi                     ,h_muPhi                     );
  Handle<vector<float>> h_muPt                      ; evt.getByLabel(l_muPt                      ,h_muPt                      );
  Handle<vector<float>> h_muSumChargedHadronPt      ; evt.getByLabel(l_muSumChargedHadronPt      ,h_muSumChargedHadronPt      );
  Handle<vector<float>> h_muSumNeutralHadronPt      ; evt.getByLabel(l_muSumNeutralHadronPt      ,h_muSumNeutralHadronPt      );
  Handle<vector<float>> h_muSumPUPt                 ; evt.getByLabel(l_muSumPUPt                 ,h_muSumPUPt                 );
  Handle<vector<float>> h_muSumPhotonPt             ; evt.getByLabel(l_muSumPhotonPt             ,h_muSumPhotonPt             );
  Handle<vector<float>> h_muY                       ; evt.getByLabel(l_muY                       ,h_muY                       );

  for (unsigned imu = 0; imu < (h_muPt.product())->size(); ++imu) {

    double muPt = (h_muPt.product())->at(imu) ; 
    double muAbsEta  = std::abs((h_muEta.product())->at(imu)) ; 
    double muIso = (h_muIso04.product())->at(imu) ; 

    bool passMuId(false) ; 
    if (type_ == LOOSE && (h_muIsLooseMuon.product())->at(imu) > 0) passMuId = true ;
    else if (type_ == TIGHT && (h_muIsTightMuon.product())->at(imu) > 0) passMuId = true ;

    if ( muPt > muPtMin_ && muPt < muPtMax_ && muAbsEta < muAbsEtaMax_ 
        && passMuId 
        && muIso > muIsoMin_ && muIso < muIsoMax_ 
       ) {
    vlq::Muon muon ; 
    TLorentzVector  muP4;
    muP4.SetPtEtaPhiM( (h_muPt.product())->at(imu), (h_muEta.product())->at(imu), (h_muPhi.product())->at(imu), (h_muMass.product())->at(imu) ) ;
    muon.setP4                      (muP4)                                              ; 
    muon.setIndex                   (imu)                                               ;
    muon.setCharge                  ((h_muCharge.product())->at(imu))                   ;
    muon.setD0                      ((h_muD0.product())->at(imu))                       ;
    muon.setD0err                   ((h_muD0err.product())->at(imu))                    ;
    muon.setDxy                     ((h_muDxy.product())->at(imu))                      ;
    muon.setDxyerr                  ((h_muDxyerr.product())->at(imu))                   ;
    muon.setDz                      ((h_muDz.product())->at(imu))                       ;
    muon.setDzerr                   ((h_muDzerr.product())->at(imu))                    ;
    muon.setE                       ((h_muE.product())->at(imu))                        ;
    muon.setEta                     ((h_muEta.product())->at(imu))                      ;
    muon.setGenMuonCharge           ((h_muGenMuonCharge.product())->at(imu))            ;
    muon.setGenMuonE                ((h_muGenMuonE.product())->at(imu))                 ;
    muon.setGenMuonEta              ((h_muGenMuonEta.product())->at(imu))               ;
    muon.setGenMuonPhi              ((h_muGenMuonPhi.product())->at(imu))               ;
    muon.setGenMuonPt               ((h_muGenMuonPt.product())->at(imu))                ;
    muon.setGenMuonY                ((h_muGenMuonY.product())->at(imu))                 ;
    muon.setGlbTrkNormChi2          ((h_muGlbTrkNormChi2.product())->at(imu))           ;
    muon.setInTrkNormChi2           ((h_muInTrkNormChi2.product())->at(imu))            ;
    muon.setIsGlobalMuon            ((h_muIsGlobalMuon.product())->at(imu))             ;
    muon.setIsLooseMuon             ((h_muIsLooseMuon.product())->at(imu))              ;
    muon.setIsPFMuon                ((h_muIsPFMuon.product())->at(imu))                 ;
    muon.setIsSoftMuon              ((h_muIsSoftMuon.product())->at(imu))               ;
    muon.setIsTightMuon             ((h_muIsTightMuon.product())->at(imu))              ;
    muon.setIsTrackerMuon           ((h_muIsTrackerMuon.product())->at(imu))            ;
    muon.setIso04                   ((h_muIso04.product())->at(imu))                    ;
    muon.setKey                     ((h_muKey.product())->at(imu))                      ;
    muon.setMass                    ((h_muMass.product())->at(imu))                     ;
    muon.setNumberMatchedStations   ((h_muNumberMatchedStations.product())->at(imu))    ;
    muon.setNumberOfPixelLayers     ((h_muNumberOfPixelLayers.product())->at(imu))      ;
    muon.setNumberOfValidTrackerHits((h_muNumberOfValidTrackerHits.product())->at(imu)) ;
    muon.setNumberTrackerLayers     ((h_muNumberTrackerLayers.product())->at(imu))      ;
    muon.setNumberValidMuonHits     ((h_muNumberValidMuonHits .product())->at(imu))     ;
    muon.setNumberValidPixelHits    ((h_muNumberValidPixelHits .product())->at(imu))    ;
    muon.setPhi                     ((h_muPhi .product())->at(imu))                     ;
    muon.setPt                      ((h_muPt .product())->at(imu))                      ;
    muon.setSumChargedHadronPt      ((h_muSumChargedHadronPt.product())->at(imu))       ;
    muon.setSumNeutralHadronPt      ((h_muSumNeutralHadronPt.product())->at(imu))       ;
    muon.setSumPUPt                 ((h_muSumPUPt.product())->at(imu))                  ;
    muon.setSumPhotonPt             ((h_muSumPhotonPt.product())->at(imu))              ;

    muons.push_back(muon) ; 
    }
  }

}
