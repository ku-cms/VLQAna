#ifndef ANALYSIS_VLQANA_MASSRECO_HH
#define ANALYSIS_VLQANA_MASSRECO_HH

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/GenParticle.h"
using namespace std;
using namespace edm;

#include <TLorentzVector.h>

typedef std::vector<vlq::GenParticle> GenParticleCollection;

class MassReco {
  public: 
    MassReco() ;
    ~MassReco() ;
    TLorentzVector getGen(GenParticleCollection, int, int) ;
    TLorentzVector getGen(GenParticleCollection, int, int, int) ;
    TLorentzVector getMatchedJet(TLorentzVector, vlq::JetCollection, double) ;
    double findInvMass(TLorentzVector, TLorentzVector) ;
    double findInvMass(TLorentzVector, TLorentzVector, TLorentzVector) ;
    pair<double, double> doReco(vlq::JetCollection, double, TLorentzVector) ;
    pair<double, double> doReco(vlq::JetCollection, TLorentzVector, double, TLorentzVector);
    double chi2(vector<TLorentzVector>, TLorentzVector, double, double) ;
    double chi2(vector<TLorentzVector>, TLorentzVector, TLorentzVector, double, double);
    pair<double, double> vector_eval(vector<pair<double, double> >) ;
};
#endif
