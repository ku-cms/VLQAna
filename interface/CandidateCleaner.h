#ifndef ANALYSIS_VLQANA_CANDIDATECLEANER_HH
#define ANALYSIS_VLQANA_CANDIDATECLEANER_HH
#include <vector>
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

///
/// Class to clean one set of candidates T1 from another T2:
/// Configurables:
///   dr_ = Separation in DR(eta, phi) between the two cadidates.
///   ptrel_ = relative pt between the two candidates (used for lepton 2D isolation). 
///   If ptrel_ < 0 (negative), 2D isolation is not applied, and an ordinary DR cleaning is used.
///   If ptrel_ > 0, T1 collection are cleaned from T2 if dr(t1, t2) > dr_ *or* if pt(t1)/pt(t2) > ptrel_
///

class CandidateCleaner {
  public:
    CandidateCleaner(double dr, double ptrel) : dr_(dr), ptrel_(ptrel) {}
    ~CandidateCleaner() {}
    template <class T1, class T2>
      void operator () (T1& cleanedcands, T2 othercands) {
        for (typename  T1::iterator icand = cleanedcands.begin(); icand < cleanedcands.end(); ++icand) {
          bool isclean(true); 
          for (auto othercand : othercands) {
            double dr((icand->getP4()).DeltaR(othercand.getP4()));
            if (ptrel_ < 0) {
              if ( dr < dr_ ) { isclean = false; break ; }  
            }
            else { //// Apply 2D isolation
              double ptrel ( ( ((icand->getP4()).Vect()).Cross((othercand.getP4()).Vect()) ).Mag()/(othercand.getP4()).Mag() ) ;
              if ( dr < dr_ && ptrel < ptrel_ ) { isclean = false; break ; }  
            }
          }
          if ( !isclean ) cleanedcands.erase(icand) ; 
        }
      }

  private:
    double dr_;
    double ptrel_;
}; 
#endif
