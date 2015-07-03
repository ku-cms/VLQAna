#ifndef ZCANDIDATEPRODUCER_HH
#define ZCANDIDATEPRODUCER_HH

#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

template <class T>
class ZCandidateProducer {
  public:
    ZCandidateProducer (const T& lp, const T& lm) : 
      lp_(lp), 
      lm_(lm)
    {}

    void operator () (vlq::CandidateCollection& zcands, TH1D* h1mass, TH1D* h1pt, TH1D* h1eta, TH1D* h1drll) {

      for ( auto lp : lp_ ) {
        for ( auto lm : lm_ ) {
          TLorentzVector p4lp(lp.getP4()), p4lm(lm.getP4()) ;
          double mass = (p4lp+p4lm).Mag() ; 
          if ( mass > 60 && mass < 120 ) {
            vlq::Candidate zll(p4lp+p4lm) ; 
            zcands_.push_back(zll) ; 
            h1mass->Fill(mass) ; 
            h1pt->Fill((p4lp+p4lm).Pt()) ; 
            h1eta->Fill((p4lp+p4lm).Eta()) ; 
            h1drll->Fill(p4lp.DeltaR(p4lm)) ; 
          }
        }
      }
      zcands = zcands_ ;

      return ;
    }

    ~ZCandidateProducer () {}  

  private:
    vlq::CandidateCollection zcands_ ;
    T lp_ ;
    T lm_ ;
}; 
#endif 
