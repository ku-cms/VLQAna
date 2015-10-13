#ifndef ANALYSIS_VLQANA_CANDIDATEFILTER_HH
#define ANALYSIS_VLQANA_CANDIDATEFILTER_HH
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

class CandidateFilter {
  public:
    CandidateFilter (edm::ParameterSet const& iConfig) : 
      massMin_(iConfig.getParameter<double> ("massMin")), 
      massMax_(iConfig.getParameter<double> ("massMax")), 
      ptMin_(iConfig.getParameter<double> ("ptMin")), 
      ptMax_(iConfig.getParameter<double> ("ptMax")) { }
    ~CandidateFilter () {}  

    void operator () (const vlq::CandidateCollection cands, vlq::CandidateCollection& filteredcands) {
      filteredcands.clear() ; 
      for ( auto cand : cands ) {
        double mass = cand.getMass() ;
        double pt = cand.getPt() ; 
        if ( mass > massMin_ && mass < massMax_ && pt > ptMin_ && pt < ptMax_ ) filteredcands.push_back(cand) ; 
      } 
      return ; 
    }

  private:
    double massMin_ ;
    double massMax_ ; 
    double ptMin_ ; 
    double ptMax_ ; 
}; 
#endif 
