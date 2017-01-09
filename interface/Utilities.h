#ifndef ANALYSIS_VLQANA_UTILITIES_HH
#define ANALYSIS_VLQANA_UTILITIES_HH

#include <utility>
#include <limits>

#include "AnalysisDataFormats/BoostedObjects/interface/Electron.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Muon.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

template <typename T>
struct iterator_extractor { typedef typename T::iterator type; };

template <typename T>
struct iterator_extractor<T const> { typedef typename T::const_iterator type; };

template <typename T>
class Indexer {
  public:
    class iterator {
      typedef typename iterator_extractor<T>::type inner_iterator;

      typedef typename std::iterator_traits<inner_iterator>::reference inner_reference;
      public:
      typedef std::pair<size_t, inner_reference> reference;

      iterator(inner_iterator it): _pos(0), _it(it) {}

      reference operator*() const { return reference(_pos, *_it); }

      iterator& operator++() { ++_pos; ++_it; return *this; }
      iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }

      bool operator==(iterator const& it) const { return _it == it._it; }
      bool operator!=(iterator const& it) const { return !(*this == it); }

      private:
      size_t _pos;
      inner_iterator _it;
    };

    Indexer(T& t): _container(t) {}

    iterator begin() const { return iterator(_container.begin()); }
    iterator end() const { return iterator(_container.end()); }

  private:
    T& _container;
}; // class Indexer

template <typename T>
Indexer<T> index(T& t) { return Indexer<T>(t); }

struct compareByPt {
  bool operator () (const vlq::Candidate& cand0, const vlq::Candidate& cand1) {
    return cand0.getPt() > cand1.getPt() ;     
  }                                           
};

struct Utilities {
  public: 

    template<typename T1, typename T2>
    static double DeltaR(T1 t1, T2 t2) {
      return t1.getP4().DeltaR(t2.getP4()) ; 
    }

    template<typename T1, typename T2>
    static int closestObjIdx (const T1 p, const std::vector<T2> objs) {
      int idx(-1);
      if (objs.size() > 1) {
        double drmin = std::numeric_limits<double>::infinity();
        for (auto obj : index(objs) ) {
          double dr = p.getP4().DeltaR(objs.at(obj.first).getP4()) ;
          if (dr < drmin) {
            drmin = dr;
            idx = obj.first;
          }
        }
      }
      return idx;
    }

    template<typename T1, typename T2>
    static double pTrel(const T1 p, const T2 reference_axis) {
      double ptrel(0.);
      TVector3 p3(p.getP4().Px(),p.getP4().Py(),p.getP4().Pz());
      TVector3 ref3(reference_axis.getP4().Px(),reference_axis.getP4().Py(),reference_axis.getP4().Pz());
      if(ref3.Mag()!=0) {
        ptrel = p3.Cross(ref3).Mag()/ref3.Mag();
      } 
      return ptrel;
    }

    template<typename T1, typename T2>
    static std::pair<double, double> drmin_pTrel(const T1 p, const std::vector<T2> jets) {
      int closestJet = closestObjIdx(p, jets);
      const constexpr auto inf = std::numeric_limits<double>::infinity();
      if(closestJet < 0) return std::make_pair(inf, inf);
      else return std::make_pair(DeltaR(p, jets.at(closestJet)), pTrel(p, jets.at(closestJet)));
    }

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
