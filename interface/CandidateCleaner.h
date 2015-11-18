#ifndef ANALYSIS_VLQANA_CANDIDATECLEANER_HH
#define ANALYSIS_VLQANA_CANDIDATECLEANER_HH
#include <vector>
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

template <typename T1, typename T2>
class CandidateCleaner {
  public:
    CandidateCleaner() {}
    ~CandidateCleaner() {}
    void clean (T1& cleanedcands, T1 targetcands, T2 othercands) {
      for (typename  T1::iterator icand = targetcands.begin(); icand < targetcands.end(); ++icand) {
        for (auto othercand : othercands) {
          if ( (icand->getP4()).DeltaR(othercand.getP4()) > 0.4 ) cleanedcands.push_back(*icand) ; 
        }
      }
    }
}; 
#endif
