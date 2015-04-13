#ifndef HT_H
#define HT_H

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

class HT {

  public :

    HT () : HT_(0) {} 
    HT (const HT& MyHT) : HT_(MyHT.getHT()) {}  
    HT (const std::vector<TLorentzVector>& p4jets) : HT_(0) { 
      for ( auto& jp4 : p4jets ) {
        HT_ += jp4.Pt() ; 
      }
    } 
    HT (const vlq::JetCollection& jets) : HT_(0) {
      for ( auto& jet : jets ) {
        HT_ += (jet.getP4()).Pt() ; 
      }
    }
    ~HT() { } 

    double getHT () const { return HT_ ; } 

  private: 

    double HT_ ; 

};


#endif 
