#ifndef UTILITIES_HH
#define UTILITIES_HH

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

struct Utilities {
  public: 
    static bool sortByPt (const vlq::Jet& jet1, const vlq::Jet& jet2) {
      return jet1.getPt() > jet2.getPt() ;  
    }

    static bool sortByMass (const vlq::Jet& jet1, const vlq::Jet& jet2) {
      return jet1.getMass() > jet2.getMass() ;  
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
