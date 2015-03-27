#include "Analysis/VLQAna/interface/PickGenPart.h"

PickGenPart::PickGenPart (const edm::ParameterSet& iConfig) :
  l_genPartCharge (iConfig.getParameter<edm::InputTag>("genPartCharge")), 
  l_genPartE      (iConfig.getParameter<edm::InputTag>("genPartE")), 
  l_genPartEta    (iConfig.getParameter<edm::InputTag>("genPartEta")), 
  l_genPartID     (iConfig.getParameter<edm::InputTag>("genPartID")), 
  l_genPartMass   (iConfig.getParameter<edm::InputTag>("genPartMass")), 
  l_genPartMomID  (iConfig.getParameter<edm::InputTag>("genPartMomID")), 
  l_genPartPhi    (iConfig.getParameter<edm::InputTag>("genPartPhi")), 
  l_genPartPt     (iConfig.getParameter<edm::InputTag>("genPartPt")), 
  l_genPartStatus (iConfig.getParameter<edm::InputTag>("genPartStatus")),
  ids_            (iConfig.getParameter<std::vector<int>>("ids")), 
  statuses_       (iConfig.getParameter<std::vector<int>>("statuses")), 
  checkstatus_    (iConfig.getParameter<bool>("checkstatus")), 
  momids_         (iConfig.getParameter<std::vector<int>>("momids")), 
  checkmomid_     (iConfig.getParameter<bool>("checkmomid"))  
{ }

PickGenPart::~PickGenPart () {}

const GenParticleCollection PickGenPart::operator() ( edm::Event& evt) {

  typedef edm::Handle <std::vector<float>> hfloat ; 

  hfloat h_genPartCharge ; evt.getByLabel(l_genPartCharge , h_genPartCharge) ;  
  hfloat h_genPartE      ; evt.getByLabel(l_genPartE      , h_genPartE     ) ;  
  hfloat h_genPartEta    ; evt.getByLabel(l_genPartEta    , h_genPartEta   ) ;  
  hfloat h_genPartID     ; evt.getByLabel(l_genPartID     , h_genPartID    ) ;  
  hfloat h_genPartMass   ; evt.getByLabel(l_genPartMass   , h_genPartMass  ) ;  
  hfloat h_genPartMomID  ; evt.getByLabel(l_genPartMomID  , h_genPartMomID ) ;  
  hfloat h_genPartPhi    ; evt.getByLabel(l_genPartPhi    , h_genPartPhi   ) ;  
  hfloat h_genPartPt     ; evt.getByLabel(l_genPartPt     , h_genPartPt    ) ;  
  hfloat h_genPartStatus ; evt.getByLabel(l_genPartStatus , h_genPartStatus) ;  

  for ( unsigned igen = 0; igen < (h_genPartID.product())->size(); ++igen ) {
    if ( std::find(ids_.begin(), ids_.end(), (h_genPartID.product())->at(igen)) == ids_.end()  
        || ( checkmomid_ && std::find(momids_.begin(), momids_.end(), (h_genPartMomID.product())->at(igen)) == momids_.end() ) 
        || ( checkstatus_ && std::find(statuses_.begin(), statuses_.end(), (h_genPartStatus.product())->at(igen)) == statuses_.end() ) 
        ) continue ; 
    TLorentzVector p4genpart ; 
    p4genpart.SetPtEtaPhiM( (h_genPartPt.product())->at(igen), (h_genPartEta.product())->at(igen), 
        (h_genPartPhi.product())->at(igen), (h_genPartMass.product())->at(igen) ) ; 
    vlq::GenParticle genpart ;
    genpart.setP4( p4genpart ) ;  
    genpart.setCharge( (h_genPartCharge.product())->at(igen) ) ; 
    genpart.setPdgID ( (h_genPartID.product())->at(igen) ) ; 
    genpart.setMomPdgID ( (h_genPartMomID.product())->at(igen) ) ; 
    genpart.setStatus ( (h_genPartStatus.product())->at(igen) ) ;
    genParts_.push_back(genpart) ; 
     
  }

  return genParts_ ; 
}
