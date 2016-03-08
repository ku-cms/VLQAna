#ifndef UTILITIES_HH
#define UTILITIES_HH

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
