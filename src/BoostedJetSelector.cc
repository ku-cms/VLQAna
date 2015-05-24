#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

#include <TLorentzVector.h>

class BoostedJetSelector {
  public :
    explicit BoostedJetSelector(const edm::ParameterSet&);
    ~BoostedJetSelector() ; 
    void select() ; 

  private:
    
};

BoostedJetSelector::BoostedJetSelector(const edm::ParameterSet& iConfig) 
{}

BoostedJetSelector::~BoostedJetSelector() 
{}

void BoostedJetSelector::select () 
{}
