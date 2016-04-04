#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "Analysis/VLQAna/interface/PickGenPart.h"

#include <iostream>

class CompositeParticleProducer : public edm::EDProducer {
  public:
    explicit CompositeParticleProducer(const edm::ParameterSet&);
    ~CompositeParticleProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  private:
    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    // ----------member data ---------------------------
    bool isData_ ; 
    bool isSignal_ ; 
    std::string particlename_ ; 

    edm::ParameterSet GenPartParams_    ; 
    std::vector<edm::ParameterSet> GenDauParams_     ; 

};

CompositeParticleProducer::CompositeParticleProducer (const edm::ParameterSet& iConfig) : 
  particlename_  (iConfig.getParameter<std::string> ("particlename")), 
  GenPartParams_ (iConfig.getParameter<edm::ParameterSet> ("GenPartParams")),
  GenDauParams_  (iConfig.getParameter<std::vector<edm::ParameterSet>> ("GenDauParams")) 
{

  produces<vlq::GenParticleWithDaughtersCollection>(particlename_.c_str()) ; 

}

CompositeParticleProducer::~CompositeParticleProducer () {} 

void CompositeParticleProducer::produce( edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;
  using namespace std;

  vlq::GenParticleCollection genPart ; 
  std::vector<vlq::GenParticleCollection> genDaus ; 

  PickGenPart genpart(GenPartParams_,consumesCollector()) ; 
  genPart = genpart(evt) ; 

  for (std::vector<edm::ParameterSet>::iterator is = GenDauParams_.begin(); is != GenDauParams_.end(); ++is) {
    PickGenPart gendau(*is,consumesCollector()) ;
    genDaus.push_back(gendau(evt)) ; 
  }

  cout << " genDaus size = " << genDaus.size() << endl ;

  vlq::GenParticleWithDaughtersCollection partcands ; 

  auto_ptr<vlq::GenParticleWithDaughtersCollection>partcandsptr( new vlq::GenParticleWithDaughtersCollection(partcands) );
  evt.put (partcandsptr, particlename_.c_str()) ; 

}

void CompositeParticleProducer::beginJob() {
}

void CompositeParticleProducer::endJob() {
}

void CompositeParticleProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(CompositeParticleProducer);
