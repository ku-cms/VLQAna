#ifndef PICKGENPART_HH
#define PICKGENPART_HH

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticle.h"

typedef std::vector<vlq::GenParticle> GenParticleCollection ; 

class PickGenPart {
  public:
    explicit PickGenPart(const edm::ParameterSet&) ; 
    ~PickGenPart() ; 
    const GenParticleCollection operator() (edm::Event&) ; 

  private: 

    edm::InputTag l_genPartCharge ; 
    edm::InputTag l_genPartE      ; 
    edm::InputTag l_genPartEta    ; 
    edm::InputTag l_genPartID     ; 
    edm::InputTag l_genPartMass   ; 
    edm::InputTag l_genPartMomID  ; 
    edm::InputTag l_genPartPhi    ; 
    edm::InputTag l_genPartPt     ; 
    edm::InputTag l_genPartStatus ; 

    int id_ ; 
    int status_ ; 
    GenParticleCollection genParts_ ; 

};

#endif 
