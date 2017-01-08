#include <iostream>
#include "Analysis/VLQAna/interface/ElectronMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;
using namespace edm ; 

ElectronMaker::ElectronMaker (edm::ParameterSet const& iConfig, edm::ConsumesCollector && iC) : 
  t_elCharge            (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elChargeLabel"))),
  t_elDxy               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elDxyLabel"))),
  t_elDz                (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elDzLabel"))),
  t_elE                 (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elELabel"))),
  t_elEta               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elEtaLabel"))),
  t_elHoE               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elHoELabel"))),
  t_elRelIsoEA          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elRelIsoEALabel"))),
  t_elKey               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elKeyLabel"))),
  t_elPhi               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elPhiLabel"))),
  t_elPt                (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elPtLabel"))),
  t_eldEtaIn            (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("eldEtaInLabel"))),
  t_eldEtaInSeed        (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("eldEtaInSeedLabel"))),
  t_eldPhiIn            (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("eldPhiInLabel"))),
  t_elfull5x5siee       (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elfull5x5sieeLabel"))),
  t_elhasMatchedConVeto (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elhasMatchedConVetoLabel"))),
  t_elvidLoose          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidLooseLabel"))),
  t_elvidMedium         (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidMediumLabel"))),
  t_elvidTight          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidTightLabel"))),
  t_elvidVeto           (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidVetoLabel"))),
  t_elvidHEEP           (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidHEEPLabel"))),
  t_elmissHits          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elmissHitsLabel"))),
  t_elooEmooP           (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elooEmooPLabel"))),
  t_elscEta             (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elscEtaLabel"))),
  elPtMin_              (iConfig.getParameter<double>("elPtMin")), 
  elPtMax_              (iConfig.getParameter<double>("elPtMax")), 
  elAbsEtaMax_          (iConfig.getParameter<double>("elAbsEtaMax")),
  applyIso_             (iConfig.getParameter<bool>("applyIso"))
{
  std::string elidtypestr = iConfig.getParameter<std::string>("elidtype") ;
  if ( elidtypestr == "LOOSE" ) type_ = LOOSE ; 
  else if ( elidtypestr == "MEDIUM" ) type_ = MEDIUM ; 
  else if ( elidtypestr == "TIGHT" ) type_ = TIGHT ; 
  else if ( elidtypestr == "VETO" ) type_ = VETO ; 
  else edm::LogError(">>>>ERROR>>>>ElectronMaker::ElectronMaker>>>>  WrongElectronIdType: ") << type_<< " Check electron id type !!!" ; 
}

ElectronMaker::~ElectronMaker () {} 

void ElectronMaker::operator () (edm::Event& evt, vlq::ElectronCollection& electrons) { 

  Handle<vector<float>> h_elCharge             ; evt.getByToken(t_elCharge            , h_elCharge            ); 
  Handle<vector<float>> h_elDxy                ; evt.getByToken(t_elDxy               , h_elDxy               ); 
  Handle<vector<float>> h_elDz                 ; evt.getByToken(t_elDz                , h_elDz                ); 
  Handle<vector<float>> h_elE                  ; evt.getByToken(t_elE                 , h_elE                 ); 
  Handle<vector<float>> h_elEta                ; evt.getByToken(t_elEta               , h_elEta               ); 
  Handle<vector<float>> h_elHoE                ; evt.getByToken(t_elHoE               , h_elHoE               ); 
  Handle<vector<float>> h_elRelIsoEA           ; evt.getByToken(t_elRelIsoEA          , h_elRelIsoEA          ); 
  Handle<vector<float>> h_elKey                ; evt.getByToken(t_elKey               , h_elKey               ); 
  Handle<vector<float>> h_elPhi                ; evt.getByToken(t_elPhi               , h_elPhi               ); 
  Handle<vector<float>> h_elPt                 ; evt.getByToken(t_elPt                , h_elPt                ); 
  Handle<vector<float>> h_eldEtaIn             ; evt.getByToken(t_eldEtaIn            , h_eldEtaIn            ); 
  Handle<vector<float>> h_eldEtaInSeed         ; evt.getByToken(t_eldEtaInSeed        , h_eldEtaInSeed        ); 
  Handle<vector<float>> h_eldPhiIn             ; evt.getByToken(t_eldPhiIn            , h_eldPhiIn            ); 
  Handle<vector<float>> h_elfull5x5siee        ; evt.getByToken(t_elfull5x5siee       , h_elfull5x5siee       ); 
  Handle<vector<float>> h_elhasMatchedConVeto  ; evt.getByToken(t_elhasMatchedConVeto , h_elhasMatchedConVeto ); 
  Handle<vector<float>> h_elvidLoose           ; evt.getByToken(t_elvidLoose          , h_elvidLoose          ); 
  Handle<vector<float>> h_elvidMedium          ; evt.getByToken(t_elvidMedium         , h_elvidMedium         ); 
  Handle<vector<float>> h_elvidTight           ; evt.getByToken(t_elvidTight          , h_elvidTight          ); 
  Handle<vector<float>> h_elvidVeto            ; evt.getByToken(t_elvidVeto           , h_elvidVeto           ); 
  Handle<vector<float>> h_elvidHEEP            ; evt.getByToken(t_elvidHEEP           , h_elvidHEEP           ); 
  Handle<vector<float>> h_elmissHits           ; evt.getByToken(t_elmissHits          , h_elmissHits          ); 
  Handle<vector<float>> h_elooEmooP            ; evt.getByToken(t_elooEmooP           , h_elooEmooP           ); 
  Handle<vector<float>> h_elscEta              ; evt.getByToken(t_elscEta             , h_elscEta             ); 

  for (unsigned iel = 0; iel < (h_elPt.product())->size(); ++iel) {

    double elPt = (h_elPt.product())->at(iel) ; 
    double elAbsEta  = std::abs((h_elEta.product())->at(iel)) ; 
    double elscAbsEta  = std::abs((h_elscEta.product())->at(iel)) ; 
    double elRelIsoEA = (h_elRelIsoEA.product())->at(iel) ; 
    double dEtaInSeed = (h_eldEtaInSeed.product())->at(iel);
    double dPhiIn = (h_eldPhiIn.product())->at(iel);
    double full5x5siee = (h_elfull5x5siee.product())->at(iel);
    double HoE = (h_elHoE.product())->at(iel);
    double Dxy = (h_elDxy.product())->at(iel);
    double Dz = (h_elDz.product())->at(iel);
    double ooEmooP = (h_elooEmooP.product())->at(iel);
    bool   hasMatchedConVeto = (h_elhasMatchedConVeto.product())->at(iel);
    double missHits = (h_elmissHits.product())->at(iel);
    bool   isEB = elAbsEta < 1.479 ;
  
    bool elisLoose  = passElId("LOOSE" , isEB, dEtaInSeed, dPhiIn, full5x5siee, HoE, elRelIsoEA, ooEmooP, hasMatchedConVeto, missHits, Dxy, Dz);
    bool elisMedium = passElId("MEDIUM", isEB, dEtaInSeed, dPhiIn, full5x5siee, HoE, elRelIsoEA, ooEmooP, hasMatchedConVeto, missHits, Dxy, Dz); 
    bool elisTight  = passElId("TIGHT" , isEB, dEtaInSeed, dPhiIn, full5x5siee, HoE, elRelIsoEA, ooEmooP, hasMatchedConVeto, missHits, Dxy, Dz);  
    bool elisVeto   = passElId("VETO"  , isEB, dEtaInSeed, dPhiIn, full5x5siee, HoE, elRelIsoEA, ooEmooP, hasMatchedConVeto, missHits, Dxy, Dz);  

    bool passId(false); 
    if (type_ == LOOSE  && elisLoose ) passId = true ;
    else if (type_ == MEDIUM && elisMedium) passId = true ;
    else if (type_ == TIGHT  && elisTight ) passId = true ;
    else if (type_ == VETO   && elisVeto  ) passId = true ;
    else passId = false ; 
    
    if (elPt > elPtMin_ && elPt < elPtMax_ && elAbsEta < elAbsEtaMax_ && passId ){
      vlq::Electron electron ; 
      TLorentzVector  elP4;
      elP4.SetPtEtaPhiE( (h_elPt.product())->at(iel), (h_elEta.product())->at(iel), (h_elPhi.product())->at(iel), (h_elE.product())->at(iel) ) ;
      electron.setP4                (elP4)                                      ;
      electron.setIndex             (iel)                                       ; 
      electron.setCharge            (h_elCharge            .product()->at(iel)) ; 
      electron.setDxy               (h_elDxy               .product()->at(iel)) ; 
      electron.setDz                (h_elDz                .product()->at(iel)) ; 
      electron.setE                 (h_elE                 .product()->at(iel)) ; 
      electron.setEta               (h_elEta               .product()->at(iel)) ; 
      electron.setHoE               (h_elHoE               .product()->at(iel)) ; 
      electron.setIso03             (h_elRelIsoEA          .product()->at(iel)) ; 
      electron.setKey               (h_elKey               .product()->at(iel)) ; 
      electron.setMass              (elP4.Mag())                                ; 
      electron.setPhi               (h_elPhi               .product()->at(iel)) ; 
      electron.setPt                (h_elPt                .product()->at(iel)) ; 
      electron.setY                 (elP4.Rapidity())                           ; 
      electron.setdEtaIn            (h_eldEtaIn            .product()->at(iel)) ; 
      electron.setdEtaInSeed        (h_eldEtaInSeed        .product()->at(iel)) ; 
      electron.setdPhiIn            (h_eldPhiIn            .product()->at(iel)) ; 
      electron.setfull5x5siee       (h_elfull5x5siee       .product()->at(iel)) ; 
      electron.sethasMatchedConVeto (h_elhasMatchedConVeto .product()->at(iel)) ; 
      electron.setisEB              (isEB) ; 
      electron.setisLoose           (elisLoose ) ; 
      electron.setisMedium          (elisMedium) ; 
      electron.setisTight           (elisTight ) ; 
      electron.setisVeto            (elisVeto  ) ; 
      electron.setmissHits          (h_elmissHits          .product()->at(iel)) ; 
      electron.setooEmooP           (h_elooEmooP           .product()->at(iel)) ; 
      electron.setscEta             (h_elscEta             .product()->at(iel)) ; 

      electrons.push_back(electron) ; 
    }

  }

}


bool ElectronMaker::passElId(string WP, bool isEB, float dEtaInSeed, float dPhiIn, float full5x5siee, float HoE, float RelIsoEA, float ooEmooP, bool conv, int missHits, float Dxy, float Dz) { 

   bool pass = false;

   if(WP == "VETO"){
      if(isEB){
         pass = (fabs(dEtaInSeed) < 0.00749) && (fabs(dPhiIn) < 0.228) && (full5x5siee < 0.0115) && (HoE < 0.356) && (fabs(Dxy) < 0.05) && (fabs(Dz) < 0.10) && (ooEmooP < 0.299) && (RelIsoEA < 0.175)  && !conv && (missHits <= 2);
      }
      else{
         pass = (fabs(dEtaInSeed) < 0.00895) && (fabs(dPhiIn) < 0.213) && (full5x5siee < 0.037) && (HoE < 0.211) && (fabs(Dxy) < 0.10) && (fabs(Dz) < 0.20) && (ooEmooP < 0.15 ) && ( applyIso_ ? (RelIsoEA < 0.159) : 1 ) && !conv && (missHits <= 3);
      }
   }
   else if(WP == "LOOSE"){
      if(isEB){
         pass = (fabs(dEtaInSeed) < 0.00477) && (fabs(dPhiIn) < 0.222) && (full5x5siee <  0.011) && (HoE < 0.298) && (fabs(Dxy) < 0.05) && (fabs(Dz) < 0.10) && (ooEmooP <  0.241) && (RelIsoEA < 0.0994)  && !conv && (missHits <= 1);
      }
      else{
         pass = (fabs(dEtaInSeed) < 0.00868) && (fabs(dPhiIn) < 0.213) && (full5x5siee < 0.0314) && (HoE < 0.101 ) && (fabs(Dxy) < 0.10) && (fabs(Dz) < 0.20) && (ooEmooP < 0.14 ) && (RelIsoEA < 0.107)  && !conv && (missHits <= 1);
      }
   }
   else if(WP == "MEDIUM"){
      if(isEB){
         pass = (fabs(dEtaInSeed) < 0.00311) && (fabs(dPhiIn) < 0.103 ) && (full5x5siee < 0.00998) && (HoE < 0.253 ) && (fabs(Dxy) < 0.05) && (fabs(Dz) < 0.10) && (ooEmooP < 0.134 ) && (RelIsoEA < 0.0695)  && !conv && (missHits <= 1);
      }
      else{
         pass = (fabs(dEtaInSeed) < 0.00609) && (fabs(dPhiIn) < 0.045) && (full5x5siee <  0.0298) && (HoE < 0.0878) && (fabs(Dxy) < 0.10) && (fabs(Dz) < 0.20) && (ooEmooP < 0.13  ) && ( applyIso_ ? (RelIsoEA < 0.0821) : 1 ) && !conv && (missHits <= 1);
      }
   }
   else if(WP == "TIGHT"){
      if(isEB){
         pass = (fabs(dEtaInSeed) < 0.00308) && (fabs(dPhiIn) < 0.0816) && (full5x5siee < 0.00998) && (HoE < 0.0414) && (fabs(Dxy) < 0.05) && (fabs(Dz) <  0.10) && (ooEmooP <  0.0129) && (RelIsoEA < 0.0588)  && !conv && (missHits <= 1);
      }
      else{
         pass = (fabs(dEtaInSeed) < 0.00605) && (fabs(dPhiIn) < 0.0394) && (full5x5siee < 0.0292) && (HoE < 0.0641) && (fabs(Dxy) < 0.10) && (fabs(Dz) < 0.20) && (ooEmooP <  0.0129 )  && ( applyIso_ ? (RelIsoEA < 0.0571) : 1 ) && !conv && (missHits <= 1);
      }
   }

   return pass;
} 
