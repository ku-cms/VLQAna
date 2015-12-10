#include <iostream>
#include "Analysis/VLQAna/interface/ElectronMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;
using namespace edm ; 

ElectronMaker::ElectronMaker (edm::ParameterSet const& pars) : 
  l_elCharge            (pars.getParameter<edm::InputTag>("elChargeLabel")),
  l_elD0                (pars.getParameter<edm::InputTag>("elD0Label")),
  l_elDz                (pars.getParameter<edm::InputTag>("elDzLabel")),
  l_elE                 (pars.getParameter<edm::InputTag>("elELabel")),
  l_elEta               (pars.getParameter<edm::InputTag>("elEtaLabel")),
  l_elHoE               (pars.getParameter<edm::InputTag>("elHoELabel")),
  l_elIso03             (pars.getParameter<edm::InputTag>("elIso03Label")),
  l_elKey               (pars.getParameter<edm::InputTag>("elKeyLabel")),
  l_elMass              (pars.getParameter<edm::InputTag>("elMassLabel")),
  l_elPhi               (pars.getParameter<edm::InputTag>("elPhiLabel")),
  l_elPt                (pars.getParameter<edm::InputTag>("elPtLabel")),
  l_elY                 (pars.getParameter<edm::InputTag>("elYLabel")),
  l_eldEtaIn            (pars.getParameter<edm::InputTag>("eldEtaInLabel")),
  l_eldPhiIn            (pars.getParameter<edm::InputTag>("eldPhiInLabel")),
  l_elfull5x5siee       (pars.getParameter<edm::InputTag>("elfull5x5sieeLabel")),
  l_elhasMatchedConVeto (pars.getParameter<edm::InputTag>("elhasMatchedConVetoLabel")),
  l_elisEB              (pars.getParameter<edm::InputTag>("elisEBLabel")),
  l_elisLoose           (pars.getParameter<edm::InputTag>("elisLooseLabel")),
  l_elisMedium          (pars.getParameter<edm::InputTag>("elisMediumLabel")),
  l_elisTight           (pars.getParameter<edm::InputTag>("elisTightLabel")),
  l_elisVeto            (pars.getParameter<edm::InputTag>("elisVetoLabel")),
  l_elvidLoose          (pars.getParameter<edm::InputTag>("elvidLooseLabel")),
  l_elvidMedium         (pars.getParameter<edm::InputTag>("elvidMediumLabel")),
  l_elvidTight          (pars.getParameter<edm::InputTag>("elvidTightLabel")),
  l_elvidVeto           (pars.getParameter<edm::InputTag>("elvidVetoLabel")),
  l_elvidHEEP           (pars.getParameter<edm::InputTag>("elvidHEEPLabel")),
  l_elmissHits          (pars.getParameter<edm::InputTag>("elmissHitsLabel")),
  l_elooEmooP           (pars.getParameter<edm::InputTag>("elooEmooPLabel")),
  l_elscEta             (pars.getParameter<edm::InputTag>("elscEtaLabel")),
  elPtMin_ (pars.getParameter<double>("elPtMin")), 
  elPtMax_ (pars.getParameter<double>("elPtMax")), 
  elAbsEtaMax_ (pars.getParameter<double>("elAbsEtaMax")), 
  elIsoMin_ (pars.getParameter<double>("elIsoMin")), 
  elIsoMax_ (pars.getParameter<double>("elIsoMax")), 
  useVID_   (pars.getParameter<bool>("useVID")) 
{
  std::string elidtypestr = pars.getParameter<std::string>("elidtype") ; 
  if ( elidtypestr == "LOOSE" ) type_ = LOOSE ; 
  else if ( elidtypestr == "MEDIUM" ) type_ = MEDIUM ; 
  else if ( elidtypestr == "TIGHT" ) type_ = TIGHT ; 
  else if ( elidtypestr == "VETO" ) type_ = VETO ; 
  else if ( elidtypestr == "HEEP" ) type_ = HEEP ; 
  else edm::LogError("ElectronMaker::ElectronMaker") << " >>>> WrongElectronIdType: " << type_<< " Check electron id type !!!" ; 
}

ElectronMaker::~ElectronMaker () {} 

void ElectronMaker::operator () (edm::Event& evt, vlq::ElectronCollection& electrons) { 

  Handle<vector<float>> h_elCharge             ; evt.getByLabel(l_elCharge            , h_elCharge            ); 
  Handle<vector<float>> h_elD0                 ; evt.getByLabel(l_elD0                , h_elD0                ); 
  Handle<vector<float>> h_elDz                 ; evt.getByLabel(l_elDz                , h_elDz                ); 
  Handle<vector<float>> h_elE                  ; evt.getByLabel(l_elE                 , h_elE                 ); 
  Handle<vector<float>> h_elEta                ; evt.getByLabel(l_elEta               , h_elEta               ); 
  Handle<vector<float>> h_elHoE                ; evt.getByLabel(l_elHoE               , h_elHoE               ); 
  Handle<vector<float>> h_elIso03              ; evt.getByLabel(l_elIso03             , h_elIso03             ); 
  Handle<vector<float>> h_elKey                ; evt.getByLabel(l_elKey               , h_elKey               ); 
  Handle<vector<float>> h_elMass               ; evt.getByLabel(l_elMass              , h_elMass              ); 
  Handle<vector<float>> h_elPhi                ; evt.getByLabel(l_elPhi               , h_elPhi               ); 
  Handle<vector<float>> h_elPt                 ; evt.getByLabel(l_elPt                , h_elPt                ); 
  Handle<vector<float>> h_elY                  ; evt.getByLabel(l_elY                 , h_elY                 ); 
  Handle<vector<float>> h_eldEtaIn             ; evt.getByLabel(l_eldEtaIn            , h_eldEtaIn            ); 
  Handle<vector<float>> h_eldPhiIn             ; evt.getByLabel(l_eldPhiIn            , h_eldPhiIn            ); 
  Handle<vector<float>> h_elfull5x5siee        ; evt.getByLabel(l_elfull5x5siee       , h_elfull5x5siee       ); 
  Handle<vector<float>> h_elhasMatchedConVeto  ; evt.getByLabel(l_elhasMatchedConVeto , h_elhasMatchedConVeto ); 
  Handle<vector<float>> h_elisEB               ; evt.getByLabel(l_elisEB              , h_elisEB              ); 
  Handle<vector<float>> h_elisLoose            ; evt.getByLabel(l_elisLoose           , h_elisLoose           ); 
  Handle<vector<float>> h_elisMedium           ; evt.getByLabel(l_elisMedium          , h_elisMedium          ); 
  Handle<vector<float>> h_elisTight            ; evt.getByLabel(l_elisTight           , h_elisTight           ); 
  Handle<vector<float>> h_elisVeto             ; evt.getByLabel(l_elisVeto            , h_elisVeto            ); 
  Handle<vector<float>> h_elvidLoose           ; evt.getByLabel(l_elvidLoose          , h_elvidLoose          ); 
  Handle<vector<float>> h_elvidMedium          ; evt.getByLabel(l_elvidMedium         , h_elvidMedium         ); 
  Handle<vector<float>> h_elvidTight           ; evt.getByLabel(l_elvidTight          , h_elvidTight          ); 
  Handle<vector<float>> h_elvidVeto            ; evt.getByLabel(l_elvidVeto           , h_elvidVeto           ); 
  Handle<vector<float>> h_elvidHEEP            ; evt.getByLabel(l_elvidHEEP           , h_elvidHEEP           ); 
  Handle<vector<float>> h_elmissHits           ; evt.getByLabel(l_elmissHits          , h_elmissHits          ); 
  Handle<vector<float>> h_elooEmooP            ; evt.getByLabel(l_elooEmooP           , h_elooEmooP           ); 
  Handle<vector<float>> h_elscEta              ; evt.getByLabel(l_elscEta             , h_elscEta             ); 

  for (unsigned iel = 0; iel < (h_elPt.product())->size(); ++iel) {

    double elPt = (h_elPt.product())->at(iel) ; 
    //double eleEta = (h_elEta.product())->at(iel) ;
    double elAbsEta  = std::abs((h_elEta.product())->at(iel)) ; 
    double elIso = (h_elIso03.product())->at(iel) ; 

    bool passElId(false) ; 
    if ( useVID_ ) {
      if (type_ == LOOSE && (h_elvidLoose.product())->at(iel) > 0) passElId = true ;
      else if (type_ == MEDIUM && (h_elvidMedium.product())->at(iel) > 0) passElId = true ;
      else if (type_ == TIGHT && (h_elvidTight.product())->at(iel) > 0) passElId = true ;
      else if (type_ == VETO && (h_elvidVeto.product())->at(iel) > 0) passElId = true ;
      else if (type_ == HEEP && (h_elvidHEEP.product())->at(iel) > 0) passElId = true ;
    }
    else {
      if (type_ == LOOSE && (h_elisLoose.product())->at(iel) > 0) passElId = true ;
      else if (type_ == MEDIUM && (h_elisMedium.product())->at(iel) > 0) passElId = true ;
      else if (type_ == TIGHT && (h_elisTight.product())->at(iel) > 0) passElId = true ;
      else if (type_ == VETO && (h_elisVeto.product())->at(iel) > 0) passElId = true ;
    }

    if ( elPt > elPtMin_ && elPt < elPtMax_ && elAbsEta < elAbsEtaMax_ 
        && passElId 
        && ( useVID_ || (elIso > elIsoMin_ && elIso < elIsoMax_) ) 
       ) {
      vlq::Electron electron ; 
      //double idSF = getEleSF(elPt, eleEta);

      TLorentzVector  elP4;
      elP4.SetPtEtaPhiM( (h_elPt.product())->at(iel), (h_elEta.product())->at(iel), (h_elPhi.product())->at(iel), (h_elMass.product())->at(iel) ) ;
      electron.setP4                (elP4)                                      ;
      electron.setIndex             (iel)                                       ; 
      //electron.setIDSF              (idSF)                                      ;  
      electron.setCharge            (h_elCharge            .product()->at(iel)) ; 
      electron.setD0                (h_elD0                .product()->at(iel)) ; 
      electron.setDz                (h_elDz                .product()->at(iel)) ; 
      electron.setE                 (h_elE                 .product()->at(iel)) ; 
      electron.setEta               (h_elEta               .product()->at(iel)) ; 
      electron.setHoE               (h_elHoE               .product()->at(iel)) ; 
      electron.setIso03             (h_elIso03             .product()->at(iel)) ; 
      electron.setKey               (h_elKey               .product()->at(iel)) ; 
      electron.setMass              (h_elMass              .product()->at(iel)) ; 
      electron.setPhi               (h_elPhi               .product()->at(iel)) ; 
      electron.setPt                (h_elPt                .product()->at(iel)) ; 
      electron.setY                 (h_elY                 .product()->at(iel)) ; 
      electron.setdEtaIn            (h_eldEtaIn            .product()->at(iel)) ; 
      electron.setdPhiIn            (h_eldPhiIn            .product()->at(iel)) ; 
      electron.setfull5x5siee       (h_elfull5x5siee       .product()->at(iel)) ; 
      electron.sethasMatchedConVeto (h_elhasMatchedConVeto .product()->at(iel)) ; 
      electron.setisEB              (h_elisEB              .product()->at(iel)) ; 
      electron.setisLoose           (h_elisLoose           .product()->at(iel)) ; 
      electron.setisMedium          (h_elisMedium          .product()->at(iel)) ; 
      electron.setisTight           (h_elisTight           .product()->at(iel)) ; 
      electron.setisVeto            (h_elisVeto            .product()->at(iel)) ; 
      electron.setmissHits          (h_elmissHits          .product()->at(iel)) ; 
      electron.setooEmooP           (h_elooEmooP           .product()->at(iel)) ; 
      electron.setscEta             (h_elscEta             .product()->at(iel)) ; 

      electrons.push_back(electron) ; 
    }

  }

}

