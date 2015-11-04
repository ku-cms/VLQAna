#include <iostream>
#include <memory>
#include <vector>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "Analysis/VLQAna/interface/JetMaker.h"
#include <TH1D.h>
#include <TLorentzVector.h>

class HJetTagging : public EDFilter {
  public:
    explicit HJetTagging (const edm::ParameterSet&) ; 
    ~HJetTagging() ; 
  private: 
    virtual void beginJob() override ;
    virtual void endJob() override ;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override ; 
    bool isMatchedToHbb(vlq::Jet, vlq::GenParticleWithDaughtersCollection) ; 

    edm::InputTag l_HbbCands ; 
    JetMaker jetAK8maker ; 
    JetMaker jetHTaggedmaker ; 
    edm::Service<TFileService> fs ; 
    std::map<std::string, TH1D*> h1_ ; 
};

HJetTagging::HJetTagging (const edm::ParameterSet& iConfig) :
  l_HbbCands              (iConfig.getParameter<edm::InputTag>     ("HbbCandsLabel")),
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams"))  
{
}

HJetTagging::~HJetTagging () {} 

bool HJetTagging::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace std;
  using namespace edm ; 
  vlq::JetCollection goodAK8Jets, goodHTaggedJets ;
  jetAK8maker(evt, goodAK8Jets); 
  jetHTaggedmaker(evt, goodHTaggedJets);
  Handle<vlq::GenParticleWithDaughtersCollection> h_HbbCands ; evt.getByLabel (l_HbbCands , h_HbbCands );
  
  int nak8_matchedToHbb(0), nhjet_matchedToHbb(0); 
  for (vlq::Jet jet : goodAK8Jets) {
    if ( !isMatchedToHbb(jet, *h_HbbCands.product() ) ) continue ; 
    nak8_matchedToHbb++ ; 
    h1_["ptak8"]->Fill( jet.getPt()  ) ; 
    h1_["massak8"]->Fill( jet.getMass()  ) ; 
    h1_["mprunedak8"]->Fill( jet.getPrunedMass()  ) ; 
    h1_["msoftdropak8"]->Fill( jet.getSoftDropMass()  ) ; 
    h1_["t21ak8"] -> Fill(jet.getTau2()/jet.getTau1()) ;
  }

  for (vlq::Jet jet : goodHTaggedJets) {
    if ( !isMatchedToHbb(jet, *h_HbbCands.product() ) ) continue ; 
    nhjet_matchedToHbb++ ; 
    h1_["pthjet"]->Fill( jet.getPt()  ) ; 
    h1_["masshjet"]->Fill( jet.getMass()  ) ; 
    h1_["mprunedhjet"]->Fill( jet.getPrunedMass()  ) ; 
    h1_["msoftdrophjet"]->Fill( jet.getSoftDropMass()  ) ; 
    h1_["t21hjet"] -> Fill(jet.getTau2()/jet.getTau1()) ;
  }

  h1_["nak8"] -> Fill(nak8_matchedToHbb) ; 
  h1_["nhjet"] -> Fill(nhjet_matchedToHbb) ; 

  return true ; 
}

void HJetTagging::beginJob() {
  h1_["nak8"]  = fs->make<TH1D>("nak8", ";N (AK8 jets);;" , 5, -0.5, 4.5) ; 
  h1_["nhjet"] = fs->make<TH1D>("nhjet", ";N (H-tagged jets);;" , 5, -0.5, 4.5) ; 
  h1_["ptak8"] = fs->make<TH1D>("ptak8", ";p_{T}(AK8 jets) [GeV];;" , 50, 0., 1000.) ; 
  h1_["pthjet"]= fs->make<TH1D>("pthjet", ";p_{T}(H-tagged jets) [GeV];;" , 50, 0., 1000.) ; 
  h1_["t21ak8"] = fs->make<TH1D>("t21ak8", ";#tau_{2}/#tau_{1}(AK8 jets);;" , 50, 0., 1.) ; 
  h1_["t21hjet"] = fs->make<TH1D>("t21hjet", ";#tau_{2}/#tau_{1}(H-tagged jets);;" , 50, 0., 1.) ; 
  h1_["massak8"] = fs->make<TH1D>("massak8", ";M(AK8 jets) [GeV];;" , 50, 50., 250.) ; 
  h1_["masshjet"]= fs->make<TH1D>("masshjet", ";M(H-tagged jets) [GeV];;" , 50, 50., 250.) ; 
  h1_["mprunedak8"] = fs->make<TH1D>("mprunedak8", ";M_{pruned}(AK8 jets) [GeV];;" , 50, 50., 250.) ; 
  h1_["mprunedhjet"]= fs->make<TH1D>("mprunedhjet", ";M_{pruned}(H-tagged jets) [GeV];;" , 50, 50., 250.) ; 
  h1_["msoftdropak8"] = fs->make<TH1D>("msoftdropak8", ";M_{softdrop}(AK8 jets) [GeV];;" , 50, 50., 250.) ; 
  h1_["msoftdrophjet"]= fs->make<TH1D>("msoftdrophjet", ";M_{softdrop}(H-tagged jets) [GeV];;" , 50, 50., 250.) ; 
}

void HJetTagging::endJob () {
  return ; 
}

bool HJetTagging::isMatchedToHbb(vlq::Jet jet, vlq::GenParticleWithDaughtersCollection HbbCands) { 

  bool ismatched(false) ;
  vlq::GenParticleWithDaughtersCollection::const_iterator ihbb ;
  vlq::GenParticleCollection::const_iterator idau ; 
  for ( ihbb = HbbCands.begin(); ihbb != HbbCands.end(); ++ihbb ) {
    if ( (ihbb->getP4()).DeltaR(jet.getP4()) > 0.3 ) continue ; 
    vlq::GenParticleCollection daus = ihbb->getDaughters() ; 
    for ( idau = daus.begin(); idau != daus.end(); ++idau) {
      if ( (idau->getP4()).DeltaR(jet.getP4()) > 0.3 ) continue ; 
      ismatched=true ; 
    }
  }
  return ismatched;

}

DEFINE_FWK_MODULE(HJetTagging);
