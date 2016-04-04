#ifndef ANALYSIS_VLQANA_CANDIDATECLEANER_HH
#define ANALYSIS_VLQANA_CANDIDATECLEANER_HH
#include <vector>
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

class CandidateCleaner {
  public:
    CandidateCleaner(double dr) : dr_(dr) {}
    ~CandidateCleaner() {}
    template <class T1, class T2>
      void operator () (T1& cleanedcands, T2 othercands) {
        for (typename  T1::iterator icand = cleanedcands.begin(); icand < cleanedcands.end(); ++icand) {
          bool isclean(true); 
          for (auto othercand : othercands) {
            if ( (icand->getP4()).DeltaR(othercand.getP4()) < dr_ ) { isclean = false; break ; }  
          }
          if ( !isclean ) cleanedcands.erase(icand) ; 
        }
      }

  private:
    double dr_;
}; 
#endif
