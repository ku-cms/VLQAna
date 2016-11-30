#ifndef PICKGENPART_HH
#define PICKGENPART_HH

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

typedef std::vector<vlq::GenParticle> GenParticleCollection ; 

class PickGenPart {
  public:
    explicit PickGenPart(const edm::ParameterSet&, edm::ConsumesCollector && iC) ; 
    ~PickGenPart() ; 
    const GenParticleCollection operator() (edm::Event&) ; 

  private: 

    edm::EDGetTokenT<std::vector<reco::GenParticle>> t_genparticles ;

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
