#ifndef PICKGENPART_HH
#define PICKGENPART_HH

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticle.h"

typedef std::vector<vlq::GenParticle> GenParticleCollection ; 

class PickGenPart {
  public:
    explicit PickGenPart(const edm::ParameterSet&, edm::ConsumesCollector && iC) ; 
    ~PickGenPart() ; 
    const GenParticleCollection operator() (edm::Event&) ; 

  private: 

    edm::EDGetTokenT<std::vector<float>> t_genPartID          ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartStatus      ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartMom0ID      ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartMom1ID      ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartMom0Status  ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartMom1Status  ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartDau0ID      ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartDau1ID      ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartDau0Status  ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartDau1Status  ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartPt          ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartEta         ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartPhi         ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartMass        ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartE           ; 
    edm::EDGetTokenT<std::vector<float>> t_genPartCharge      ; 

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
