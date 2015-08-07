#ifndef ZCANDIDATEPRODUCER_HH
#define ZCANDIDATEPRODUCER_HH

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

template <class T>
class ZCandidateProducer {
  public:
    ZCandidateProducer (edm::ParameterSet const& iConfig, const T& lp, const T& lm) : 
      massMin_(iConfig.getParameter<double> ("massMin")), 
      massMax_(iConfig.getParameter<double> ("massMax")), 
      ptMin_(iConfig.getParameter<double> ("ptMin")), 
      ptMax_(iConfig.getParameter<double> ("ptMax")), 
      lp_(lp), 
      lm_(lm)
    {}

    void operator () (vlq::CandidateCollection& zcands, TH1D* h1mass, TH1D* h1pt, TH1D* h1eta, TH1D* h1drll, double evtwt) {

      for ( auto lp : lp_ ) {
        for ( auto lm : lm_ ) {
          TLorentzVector p4lp(lp.getP4()), p4lm(lm.getP4()) ;
          double mass = (p4lp+p4lm).Mag() ; 
          double pt = (p4lp+p4lm).Pt() ; 
          if ( mass > massMin_ && mass < massMax_ && pt > ptMin_ && pt < ptMax_ ) {
            vlq::Candidate zll(p4lp+p4lm) ; 
            zcands_.push_back(zll) ; 
            h1mass->Fill(mass, evtwt) ; 
            h1pt->Fill((p4lp+p4lm).Pt(), evtwt) ; 
            h1eta->Fill((p4lp+p4lm).Eta(), evtwt) ; 
            h1drll->Fill(p4lp.DeltaR(p4lm), evtwt) ; 
          }
        }
      }
      zcands = zcands_ ;

      return ;
    }

    ~ZCandidateProducer () {}  

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
