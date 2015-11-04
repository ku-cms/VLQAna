#ifndef UTILITIES_HH
#define UTILITIES_HH

#include "AnalysisDataFormats/BoostedObjects/interface/Electron.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Muon.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

struct compareByPt {
  bool operator () (const vlq::Candidate& cand0, const vlq::Candidate& cand1) {
    return cand0.getPt() > cand1.getPt() ;     
  }                                           
};

struct Utilities {
  public: 
    template <typename T>
    static bool sortByPt (const T& t1, const T& t2) {
      return t1.getPt() > t2.getPt() ;  
    }

    template <typename T>
    static bool sortByEta (const T& t1, const T& t2) {
      return t1.getEta() > t2.getEta() ;  
    }

    template <typename T>
    static bool sortByMass (const T& t1, const T& t2) {
      return t1.getMass() > t2.getMass() ;  
    }

    static bool sortByTrimmedMass (const vlq::Jet& jet1, const vlq::Jet& jet2) {
      return jet1.getTrimmedMass() > jet2.getTrimmedMass() ;  
    }

    static bool sortBySoftDropMass (const vlq::Jet& jet1, const vlq::Jet& jet2) {
      return jet1.getSoftDropMass() > jet2.getSoftDropMass() ;  
    }

    static bool sortByCSV (const vlq::Jet& jet1, const vlq::Jet& jet2) {
      return jet1.getCSV() > jet2.getCSV() ;  
    }
}; 

#endif 
