#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "Analysis/VLQAna/interface/PickGenPart.h"
#include <iostream>

class HbbCandidateProducer : public edm::EDProducer {
  public:
    explicit HbbCandidateProducer(const edm::ParameterSet&);
    ~HbbCandidateProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  private:
    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    // ----------member data ---------------------------
    bool isData_ ; 
    bool isSignal_ ; 

    edm::ParameterSet GenHSelParams_          ; 
    edm::ParameterSet GenbSelParams_          ; 
    edm::ParameterSet GenbbarSelParams_       ; 

};

HbbCandidateProducer::HbbCandidateProducer (const edm::ParameterSet& iConfig) : 
  GenHSelParams_    (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
  GenbSelParams_    (iConfig.getParameter<edm::ParameterSet> ("GenbSelParams")),
  GenbbarSelParams_ (iConfig.getParameter<edm::ParameterSet> ("GenbbarSelParams")) 
{

  produces<vlq::GenParticleWithDaughtersCollection>("HbbCandidates") ; 

}

HbbCandidateProducer::~HbbCandidateProducer () {} 

void HbbCandidateProducer::produce( edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;
  using namespace std;

  PickGenPart genh(GenHSelParams_) ; 
  PickGenPart genb(GenbSelParams_) ; 
  PickGenPart genbbar(GenbbarSelParams_) ; 

  GenParticleCollection higgses = genh(evt) ;  
  GenParticleCollection bfromhiggses = genb(evt) ;  
  GenParticleCollection bbarfromhiggses = genbbar(evt) ;  

  //std::cout << " Nhbb = " << higgses.size() << std::endl ; 
  //std::cout << " Nbfromh = " << bfromhiggses.size() << std::endl ; 
  //std::cout << " Nbbarfromh = " << bbarfromhiggses.size() << std::endl ; 

  vlq::GenParticleWithDaughtersCollection hbbcands ; 
  for ( vlq::GenParticle& h : higgses ) {
    vlq::GenParticleWithDaughters hbbcand ; 
    vlq::GenParticleCollection hbbdaus ; 
    std::vector<TLorentzVector> p4bs ; 
    for ( vlq::GenParticle& b : bfromhiggses ) {
      for ( vlq::GenParticle& bbar : bbarfromhiggses ) {
        //TLorentzVector p4bbbar = b.getP4() + bbar.getP4() ; 
        //if ( (h.getP4()).DeltaR(p4bbbar) < 0.4 && abs((h.getP4().Pt() - p4bbbar.Pt())/h.getP4().Pt()) < 0.1 ) {
          p4bs.push_back(b.getP4()) ; 
          p4bs.push_back(bbar.getP4()) ; 
          hbbdaus.push_back(b) ; 
          hbbdaus.push_back(bbar) ;
        //}
      }
    }
    if ( p4bs.size() > 0 ) { 
      hbbcand.setDaughters(hbbdaus)  ; 
      hbbcands.push_back(hbbcand) ; 
    }
  }

  auto_ptr<vlq::GenParticleWithDaughtersCollection>hbbcandsptr( new vlq::GenParticleWithDaughtersCollection(hbbcands) );
  evt.put (hbbcandsptr, "HbbCandidates") ; 

}

void HbbCandidateProducer::beginJob() {
}

void HbbCandidateProducer::endJob() {
}

void HbbCandidateProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(HbbCandidateProducer);
