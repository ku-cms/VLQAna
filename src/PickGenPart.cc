#include <iostream>

#include "Analysis/VLQAna/interface/PickGenPart.h"

using namespace edm;

PickGenPart::PickGenPart (const edm::ParameterSet& iConfig, edm::ConsumesCollector && iC) :
  l_genPartID          (iConfig.getParameter<edm::InputTag>("genPartID")), 
  l_genPartStatus      (iConfig.getParameter<edm::InputTag>("genPartStatus")),
  l_genPartMom0ID      (iConfig.getParameter<edm::InputTag>("genPartMom0ID")), 
  l_genPartMom1ID      (iConfig.getParameter<edm::InputTag>("genPartMom1ID")), 
  l_genPartMom0Status  (iConfig.getParameter<edm::InputTag>("genPartMom0Status")), 
  l_genPartMom1Status  (iConfig.getParameter<edm::InputTag>("genPartMom1Status")), 
  l_genPartDau0ID      (iConfig.getParameter<edm::InputTag>("genPartDau0ID")), 
  l_genPartDau1ID      (iConfig.getParameter<edm::InputTag>("genPartDau1ID")), 
  l_genPartDau0Status  (iConfig.getParameter<edm::InputTag>("genPartDau0Status")), 
  l_genPartDau1Status  (iConfig.getParameter<edm::InputTag>("genPartDau1Status")), 
  l_genPartPt          (iConfig.getParameter<edm::InputTag>("genPartPt")), 
  l_genPartEta         (iConfig.getParameter<edm::InputTag>("genPartEta")), 
  l_genPartPhi         (iConfig.getParameter<edm::InputTag>("genPartPhi")), 
  l_genPartMass        (iConfig.getParameter<edm::InputTag>("genPartMass")), 
  l_genPartE           (iConfig.getParameter<edm::InputTag>("genPartE")), 
  l_genPartCharge      (iConfig.getParameter<edm::InputTag>("genPartCharge")), 
  ids_                 (iConfig.getParameter<std::vector<int>>("ids")), 
  statuses_            (iConfig.getParameter<std::vector<int>>("statuses")), 
  checkstatus_         (iConfig.getParameter<bool>("checkstatus")), 
  mom0ids_             (iConfig.getParameter<std::vector<int>>("mom0ids")), 
  mom1ids_             (iConfig.getParameter<std::vector<int>>("mom1ids")), 
  checkmomid_          (iConfig.getParameter<bool>("checkmomid")),
  dau0ids_             (iConfig.getParameter<std::vector<int>>("dau0ids")), 
  dau1ids_             (iConfig.getParameter<std::vector<int>>("dau1ids")), 
  checkdauid_          (iConfig.getParameter<bool>("checkdauid")),
  debug_               (iConfig.getParameter<bool>("debug"))
{ 

  iC.consumes<std::vector<float>>(l_genPartID        ); 
  iC.consumes<std::vector<float>>(l_genPartStatus    ); 
  iC.consumes<std::vector<float>>(l_genPartMom0ID    ); 
  iC.consumes<std::vector<float>>(l_genPartMom1ID    ); 
  iC.consumes<std::vector<float>>(l_genPartMom0Status); 
  iC.consumes<std::vector<float>>(l_genPartMom1Status); 
  iC.consumes<std::vector<float>>(l_genPartDau0ID    ); 
  iC.consumes<std::vector<float>>(l_genPartDau1ID    ); 
  iC.consumes<std::vector<float>>(l_genPartDau0Status); 
  iC.consumes<std::vector<float>>(l_genPartDau1Status); 
  iC.consumes<std::vector<float>>(l_genPartPt        ); 
  iC.consumes<std::vector<float>>(l_genPartEta       ); 
  iC.consumes<std::vector<float>>(l_genPartPhi       ); 
  iC.consumes<std::vector<float>>(l_genPartMass      ); 
  iC.consumes<std::vector<float>>(l_genPartE         ); 
  iC.consumes<std::vector<float>>(l_genPartCharge    ); 

}

PickGenPart::~PickGenPart () {}

const GenParticleCollection PickGenPart::operator() ( edm::Event& evt) {

  using namespace std; 

  typedef edm::Handle <std::vector<float>> hfloat ; 

  hfloat h_genPartPt            ; evt.getByLabel(l_genPartPt            , h_genPartPt           ) ;  
  hfloat h_genPartEta           ; evt.getByLabel(l_genPartEta           , h_genPartEta          ) ;  
  hfloat h_genPartPhi           ; evt.getByLabel(l_genPartPhi           , h_genPartPhi          ) ;  
  hfloat h_genPartMass          ; evt.getByLabel(l_genPartMass          , h_genPartMass         ) ;  
  hfloat h_genPartE             ; evt.getByLabel(l_genPartE             , h_genPartE            ) ;  
  hfloat h_genPartCharge        ; evt.getByLabel(l_genPartCharge        , h_genPartCharge       ) ;  
  hfloat h_genPartID            ; evt.getByLabel(l_genPartID            , h_genPartID           ) ;  
  hfloat h_genPartStatus        ; evt.getByLabel(l_genPartStatus        , h_genPartStatus       ) ;  
  hfloat h_genPartMom0ID        ; evt.getByLabel(l_genPartMom0ID        , h_genPartMom0ID       ) ;  
  hfloat h_genPartMom1ID        ; evt.getByLabel(l_genPartMom1ID        , h_genPartMom1ID       ) ;  
  hfloat h_genPartMom0Status    ; evt.getByLabel(l_genPartMom0Status    , h_genPartMom0Status   ) ;  
  hfloat h_genPartMom1Status    ; evt.getByLabel(l_genPartMom1Status    , h_genPartMom1Status   ) ;  
  hfloat h_genPartDau0ID        ; evt.getByLabel(l_genPartDau0ID        , h_genPartDau0ID       ) ;  
  hfloat h_genPartDau1ID        ; evt.getByLabel(l_genPartDau1ID        , h_genPartDau1ID       ) ;  
  hfloat h_genPartDau0Status    ; evt.getByLabel(l_genPartDau0Status    , h_genPartDau0Status   ) ;  
  hfloat h_genPartDau1Status    ; evt.getByLabel(l_genPartDau1Status    , h_genPartDau1Status   ) ;  

  for ( unsigned igen = 0; igen < (h_genPartID.product())->size(); ++igen ) {

    if ( std::find(ids_.begin(), ids_.end(), (h_genPartID.product())->at(igen)) == ids_.end() ) continue ; 
    if ( checkstatus_ && std::find(statuses_.begin(), statuses_.end(), (h_genPartStatus.product())->at(igen)) == statuses_.end() ) continue ;

    if ( debug_ ) {
      std::cout << " id = " << (h_genPartID.product())->at(igen) 
        << " status = " << (h_genPartStatus.product())->at(igen) 
        << " mom0 id = " << (h_genPartMom0ID.product())->at(igen) 
        << " mom1 id = " << (h_genPartMom1ID.product())->at(igen)
        << " dau0 id = " << (h_genPartDau0ID.product())->at(igen) 
        << " dau1 id = " << (h_genPartDau1ID.product())->at(igen)
        << std::endl ;
    }

    if ( checkmomid_ && std::find(mom0ids_.begin(), mom0ids_.end(), (h_genPartMom0ID.product())->at(igen)) == mom0ids_.end() ) continue ; 
    if ( checkmomid_ && std::find(mom1ids_.begin(), mom1ids_.end(), (h_genPartMom1ID.product())->at(igen)) == mom1ids_.end() ) continue ; 
    if ( checkdauid_ && std::find(dau0ids_.begin(), dau0ids_.end(), (h_genPartDau0ID.product())->at(igen)) == dau0ids_.end() ) continue ; 
    if ( checkdauid_ && std::find(dau1ids_.begin(), dau1ids_.end(), (h_genPartDau1ID.product())->at(igen)) == dau1ids_.end() ) continue ; 

    TLorentzVector p4genpart ; 
    p4genpart.SetPtEtaPhiM( (h_genPartPt.product())->at(igen), (h_genPartEta.product())->at(igen), 
        (h_genPartPhi.product())->at(igen), (h_genPartMass.product())->at(igen) ) ; 
    vlq::GenParticle genpart ;
    genpart.setP4( p4genpart ) ;  
    genpart.setPdgID ( (h_genPartID.product())->at(igen) ) ; 
    genpart.setStatus ( (h_genPartStatus.product())->at(igen) ) ;
    genpart.setCharge( (h_genPartCharge.product())->at(igen) ) ; 
    genpart.setMom0PdgID ( (h_genPartMom0ID.product())->at(igen) ) ; 
    genpart.setMom1PdgID ( (h_genPartMom1ID.product())->at(igen) ) ; 
    genpart.setDau0PdgID ( (h_genPartDau0ID.product())->at(igen) ) ; 
    genpart.setDau1PdgID ( (h_genPartDau1ID.product())->at(igen) ) ; 
    genpart.setMom0Status ( (h_genPartMom0Status.product())->at(igen) ) ; 
    genpart.setMom1Status ( (h_genPartMom1Status.product())->at(igen) ) ; 
    genpart.setDau0Status ( (h_genPartDau0Status.product())->at(igen) ) ; 
    genpart.setDau1Status ( (h_genPartDau1Status.product())->at(igen) ) ; 
    genParts_.push_back(genpart) ; 

  }

  return genParts_ ; 
}
