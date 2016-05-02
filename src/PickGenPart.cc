#include <iostream>

#include "Analysis/VLQAna/interface/PickGenPart.h"

using namespace edm;

PickGenPart::PickGenPart (const edm::ParameterSet& iConfig, edm::ConsumesCollector && iC) :
  t_genPartID          (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartID"))), 
  t_genPartStatus      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartStatus"))),
  t_genPartMom0ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom0ID"))), 
  t_genPartMom1ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom1ID"))), 
  t_genPartMom0Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom0Status"))), 
  t_genPartMom1Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom1Status"))), 
  t_genPartDau0ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau0ID"))), 
  t_genPartDau1ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau1ID"))), 
  t_genPartDau0Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau0Status"))), 
  t_genPartDau1Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau1Status"))), 
  t_genPartPt          (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartPt"))), 
  t_genPartEta         (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartEta"))), 
  t_genPartPhi         (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartPhi"))), 
  t_genPartMass        (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMass"))), 
  t_genPartE           (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartE"))), 
  t_genPartCharge      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartCharge"))), 
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
}

PickGenPart::~PickGenPart () {}

const GenParticleCollection PickGenPart::operator() ( edm::Event& evt) {

  using namespace std; 

  typedef edm::Handle <std::vector<float>> hfloat ; 

  hfloat h_genPartPt            ; evt.getByToken(t_genPartPt            , h_genPartPt           ) ;  
  hfloat h_genPartEta           ; evt.getByToken(t_genPartEta           , h_genPartEta          ) ;  
  hfloat h_genPartPhi           ; evt.getByToken(t_genPartPhi           , h_genPartPhi          ) ;  
  hfloat h_genPartMass          ; evt.getByToken(t_genPartMass          , h_genPartMass         ) ;  
  hfloat h_genPartE             ; evt.getByToken(t_genPartE             , h_genPartE            ) ;  
  hfloat h_genPartCharge        ; evt.getByToken(t_genPartCharge        , h_genPartCharge       ) ;  
  hfloat h_genPartID            ; evt.getByToken(t_genPartID            , h_genPartID           ) ;  
  hfloat h_genPartStatus        ; evt.getByToken(t_genPartStatus        , h_genPartStatus       ) ;  
  hfloat h_genPartMom0ID        ; evt.getByToken(t_genPartMom0ID        , h_genPartMom0ID       ) ;  
  hfloat h_genPartMom1ID        ; evt.getByToken(t_genPartMom1ID        , h_genPartMom1ID       ) ;  
  hfloat h_genPartMom0Status    ; evt.getByToken(t_genPartMom0Status    , h_genPartMom0Status   ) ;  
  hfloat h_genPartMom1Status    ; evt.getByToken(t_genPartMom1Status    , h_genPartMom1Status   ) ;  
  hfloat h_genPartDau0ID        ; evt.getByToken(t_genPartDau0ID        , h_genPartDau0ID       ) ;  
  hfloat h_genPartDau1ID        ; evt.getByToken(t_genPartDau1ID        , h_genPartDau1ID       ) ;  
  hfloat h_genPartDau0Status    ; evt.getByToken(t_genPartDau0Status    , h_genPartDau0Status   ) ;  
  hfloat h_genPartDau1Status    ; evt.getByToken(t_genPartDau1Status    , h_genPartDau1Status   ) ;  

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
