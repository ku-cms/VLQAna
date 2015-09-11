#ifndef DILEPTONCANDSPRODUCER_HH
#define DILEPTONCANDSPRODUCER_HH

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

template <class T>
class DileptonCandsProducer {
  public:
    DileptonCandsProducer (edm::ParameterSet const& iConfig, const T& lp, const T& lm) : 
      massMin_(iConfig.getParameter<double> ("massMin")), 
      massMax_(iConfig.getParameter<double> ("massMax")), 
      ptMin_(iConfig.getParameter<double> ("ptMin")), 
      ptMax_(iConfig.getParameter<double> ("ptMax")), 
      lp_(lp), 
      lm_(lm)
    {}

    void operator () (vlq::CandidateCollection& zcands) {

      for ( auto lp : lp_ ) {
        for ( auto lm : lm_ ) {
          TLorentzVector p4lp(lp.getP4()), p4lm(lm.getP4()) ;
          double mass = (p4lp+p4lm).Mag() ; 
          double pt = (p4lp+p4lm).Pt() ; 
          if ( mass > massMin_ && mass < massMax_ && pt > ptMin_ && pt < ptMax_ ) {
            vlq::Candidate zll(p4lp+p4lm) ; 
            zcands_.push_back(zll) ; 
          }
        }
      }
      zcands = zcands_ ;

      return ;
    }

    ~DileptonCandsProducer () {}  

  private:
    vlq::CandidateCollection zcands_ ;
    double massMin_ ;
    double massMax_ ; 
    double ptMin_ ; 
    double ptMax_ ; 
    T lp_ ;
    T lm_ ;
}; 
#endif 
