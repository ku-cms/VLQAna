#ifndef VCANDPRODUCER_HH
#define VCANDPRODUCER_HH

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"

#include <vector>

class VCandProducer {
  public:
    VCandProducer (const vlq::JetCollection& jets, 
        const double massMin, const double massMax, 
        const double drjjMax,const double scaledmassdropMin, const double scaledmassdropMax) :
      jets_(jets),
      massMin_(massMin),
      massMax_(massMax),
      drjjMax_(drjjMax),
      scaledmassdropMin_(scaledmassdropMin),  
      scaledmassdropMax_(scaledmassdropMax)   
  { makeCands() ; }

    void getCands (std::vector<vlq::ResolvedVjj>& cands) { 
      for (auto cand : VCands_) {
        cands.push_back(cand) ; 
      }
    }

    ~VCandProducer () {} ; 

  private:
    void makeCands() {
      for (auto ij = jets_.cbegin(); ij != jets_.cend(); ++ij)
        for (auto jj = ij+1; jj != jets_.cend(); ++jj) {
          TLorentzVector p4j1(ij->getP4()), p4j2(jj->getP4()) ;
          TLorentzVector p4v = p4j1 + p4j2 ; 
          double drjj = p4j1.DeltaR(p4j2) ; 
          double mass = p4v.Mag() ; 
          double massdrop = (max(p4j1.Mag(), p4j2.Mag())/p4v.Mag()) ; 
          double scaledmassdrop = massdrop*drjj ; 
          if ( mass < massMin_ || mass > massMax_ || drjj > drjjMax_ || scaledmassdrop > scaledmassdropMax_ || scaledmassdrop < scaledmassdropMin_) continue; 
          std::pair <int, int> jetIndices( ij->getIndex(), jj->getIndex() ) ; 
          vlq::ResolvedVjj vjj ;
          vjj.setP4( p4v ) ; 
          vjj.setDrjj( drjj ) ; 
          vjj.setMass( mass ) ; 
          vjj.setMassDrop( massdrop ) ;
          vjj.setScaledMassDrop( scaledmassdrop ) ;
          vjj.setJetIndices( jetIndices ) ; 
          VCands_.push_back(vjj) ; 
        }
    }

    vlq::JetCollection jets_ ; 
    double massMin_ ; 
    double massMax_ ; 
    double drjjMax_ ; 
    double scaledmassdropMin_ ; 
    double scaledmassdropMax_ ; 
    std::vector<vlq::ResolvedVjj> VCands_ ; 
};
#endif 

