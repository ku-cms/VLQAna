#ifndef JET_H
#define JET_H

#include <vector>
#include <TLorentzVector.h>

class Jet ;
typedef std::vector<Jet> JetCollection ; 

class Jet : public TLorentzVector {
  public:
    Jet () {} ; 
    Jet (const TLorentzVector& p4) : p4_(p4) {}
    Jet (const Jet& jet) : p4_(jet.p4()) {}
    ~Jet () {}; 
    TLorentzVector p4() const {return p4_ ;} 
  private: 
    TLorentzVector p4_ ; 
} ;

#endif
