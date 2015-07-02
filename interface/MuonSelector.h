#ifndef MUONSELECTOR_HH
#define MUONSELECTOR_HH

using namespace std;
using namespace edm ; 

class MuonSelector {
  public:
    enum MUONIDTYPES_t {LOOSE, MEDIUM, TIGHT} ; 
    MuonSelector (edm::ParameterSet const& pars) : 
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
    muCharge_ (pars.getParameter<double>("muCharge")), 
    muIsoMin_ (pars.getParameter<double>("muIsoMin")), 
    muIsoMax_ (pars.getParameter<double>("muIsoMax"))  
  {
    std::string muidtypestr = pars.getParameter<std::string>("muidtype") ; 
    if ( muidtypestr == "LOOSE" ) type_ = LOOSE ; 
    else if ( muidtypestr == "MEDIUM" ) type_ = MEDIUM ; 
    else if ( muidtypestr == "TIGHT" ) type_ = TIGHT ; 
    else edm::LogError("MuonSelector::MuonSelector") << " >>>> WrongMuonIdType: " << type_<< " Check muon id type !!!" ; 
  }

    bool operator () (edm::Event& evt, int const & mu, bool& ret ) { 
      ret = false ; 

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

      double muCharge  = (h_muCharge.product())->at(mu) ; 
      double muPt = (h_muPt.product())->at(mu) ; 
      double muAbsEta  = std::abs((h_muEta.product())->at(mu)) ; 
      double muIso = (h_muIso04.product())->at(mu) ; 

      bool passMuId(false) ; 
      if (type_ == TIGHT && (h_muIsTightMuon.product())->at(mu) > 0) passMuId = true ;

      if ( muPt > muPtMin_ && muPt < muPtMax_ && muAbsEta < muAbsEtaMax_ 
          && std::abs(muCharge - muCharge_) < 0.001*abs(muCharge_)  
          && passMuId 
          && muIso > muIsoMin_ && muIso < muIsoMax_ 
          ) ret = true  ;

      return ret ; 

    }

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
    double muCharge_ ; 
    double muIsoMin_ ; 
    double muIsoMax_ ; 


};
#endif
