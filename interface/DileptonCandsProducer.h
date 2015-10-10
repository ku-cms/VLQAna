#ifndef ANALYSIS_VLQANA_DILEPTONCANDSPRODUCER_HH
#define ANALYSIS_VLQANA_DILEPTONCANDSPRODUCER_HH

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

class DileptonCandsProducer {
  public:
    DileptonCandsProducer (edm::ParameterSet const& iConfig) : 
      massMin_(iConfig.getParameter<double> ("massMin")), 
      massMax_(iConfig.getParameter<double> ("massMax")), 
      ptMin_(iConfig.getParameter<double> ("ptMin")), 
      ptMax_(iConfig.getParameter<double> ("ptMax")) 
  {}

    template <class T>
    void operator () (vlq::CandidateCollection& zcands, const T leptons) {

      for ( auto l1 = leptons.begin(); l1 != leptons.end(); ++l1) {
        for ( auto l2 = std::next(l1); l2 != leptons.end(); ++l2) {
          if (l1->getCharge()*l2->getCharge() != -1 ) continue ; 
          TLorentzVector p4l1(l1->getP4()), p4l2(l2->getP4()) ;
          double mass = (p4l1+p4l2).Mag() ; 
          double pt = (p4l1+p4l2).Pt() ; 
          if ( mass > massMin_ && mass < massMax_ && pt > ptMin_ && pt < ptMax_ ) {
            vlq::Candidate zll(p4l1+p4l2) ; 
            zcands.push_back(zll) ; 
          }
        }
      }

      return ;
    }

    ~DileptonCandsProducer () {}  

  private:
    double massMin_ ;
    double massMax_ ; 
    double ptMin_ ; 
    double ptMax_ ; 
}; 
#endif 
