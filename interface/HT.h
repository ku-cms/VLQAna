#ifndef HT_H
#define HT_H

#include "Analysis/VLQAna/interface/Jet.h"

class HT {

  public :

    HT () : HT_(0) {} 
    HT (const HT& MyHT) : HT_(MyHT.getHT()) {}  
    HT (const std::vector<TLorentzVector>& p4jets) : HT_(0) { 
      for ( auto& jp4 : p4jets ) {
        HT_ += jp4.Pt() ; 
      }
    } 
    HT (const JetCollection& jets) : HT_(0) {
      for ( auto& jet : jets ) {
        HT_ += (jet.p4()).Pt() ; 
      }
    }
    ~HT() { } 

    double getHT () const { return HT_ ; } 

  private: 

    double HT_ ; 

    //void setJetCollection (JetCollection& JetColl) { vJets_.push_back(JetColl) ; } 

    //void clearJetCollections() {vJets_.clear() ; HT_ = 0;} 

    //void buildHT() { 

    //  if ( vJets_.size() == 0 ) HT_ = 0; 

    //  for (std::vector<JetCollection>::const_iterator itjetcolls =  vJets_.begin(); itjetcolls != vJets_.end(); ++itjetcolls) { 
    //    for (JetCollection::const_iterator itjet = itjetcolls->begin(); itjet != itjetcolls->end(); ++itjet) { 
    //      HT_ += itjet->Pt() ; 
    //    }
    //  }

    //} 

    //std::vector<JetCollection> vJets_ ; 

};


#endif 
