#ifndef CANDIDATEFILTER_HH
#define CANDIDATEFILTER_HH
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

class CandidateFilter {
  public:
    CandidateFilter (edm::ParameterSet const& iConfig) : 
      massMin_(iConfig.getParameter<double> ("massMin")), 
      massMax_(iConfig.getParameter<double> ("massMax")), 
      ptMin_(iConfig.getParameter<double> ("ptMin")), 
      ptMax_(iConfig.getParameter<double> ("ptMax")) { }
    ~CandidateFilter () {}  

    void operator () (vlq::CandidateCollection& cands, vlq::CandidateCollection& filteredcands) {
      vlq::CandidateCollection cands_ ;
      cands_.clear() ; 
      for ( auto cand : cands ) {
        double mass = cand.getMass() ;
        double pt = cand.getPt() ; 
        if ( mass > massMin_ && mass < massMax_ && pt > ptMin_ && pt < ptMax_ ) cands_.push_back(cand) ; 
      } 
      filteredcands = cands_ ;  
      return ; 
    }

  private:
    double massMin_ ;
    double massMax_ ; 
    double ptMin_ ; 
    double ptMax_ ; 
}; 
#endif 
