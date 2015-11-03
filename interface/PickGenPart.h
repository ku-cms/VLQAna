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

    edm::InputTag l_genPartID          ; 
    edm::InputTag l_genPartStatus      ; 
    edm::InputTag l_genPartMom0ID      ; 
    edm::InputTag l_genPartMom1ID      ; 
    edm::InputTag l_genPartMom0Status  ; 
    edm::InputTag l_genPartMom1Status  ; 
    edm::InputTag l_genPartDau0ID      ; 
    edm::InputTag l_genPartDau1ID      ; 
    edm::InputTag l_genPartDau0Status  ; 
    edm::InputTag l_genPartDau1Status  ; 
    edm::InputTag l_genPartPt          ; 
    edm::InputTag l_genPartEta         ; 
    edm::InputTag l_genPartPhi         ; 
    edm::InputTag l_genPartMass        ; 
    edm::InputTag l_genPartE           ; 
    edm::InputTag l_genPartCharge      ; 

    std::vector<int> ids_ ; 
    std::vector<int> statuses_ ; 
    bool checkstatus_ ; 
    std::vector<int> mom0ids_ ; 
    std::vector<int> mom1ids_ ; 
    bool checkmomid_ ; 
    std::vector<int> dau0ids_ ; 
    std::vector<int> dau1ids_ ; 
    bool checkdauid_ ; 
    bool debug_ ; 


    GenParticleCollection genParts_ ; 

};

#endif 
