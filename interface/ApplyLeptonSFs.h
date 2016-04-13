#ifndef ANALYSIS_VLQANA_APPLYLEPTONSFS_HH
#define ANALYSIS_VLQANA_APPLYLEPTONSFS_HH

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class ApplyLeptonSFs {
  public:
    enum LEPTONIDTYPES_t {LOOSE, TIGHT} ; 
    ApplyLeptonSFs (edm::ParameterSet const& pars, edm::ConsumesCollector && iC) : 
      sf_(1),
      zdecayMode_(pars.getParameter<std::string>("zdecayMode")) 
  {
     std::string lepidtypestr = pars.getParameter<std::string>("lepidtype") ; 
     if ( lepidtypestr == "LOOSE" ) type_ = LOOSE ;  
     else if ( lepidtypestr == "TIGHT" ) type_ = TIGHT ; 
     else edm::LogError("ApplyLeptonSF") << " >>>> WrongElectronIdType: " << type_<< " Check lepton id type !!!" ; 
  }
    ~ApplyLeptonSFs () {} 
    double operator () (double pt, double eta){
       if (type_ == TIGHT && zdecayMode_ == "zelel"){
          if(pt > 100.) pt = 100.; 
          if(pt > 10 && pt <= 20){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.15;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.96;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.12;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.07;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.05;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.01;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.05;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.52;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.01;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.05;
          }
          else if(pt > 20 && pt <= 30){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.01;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.94;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.06;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.00;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.99;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.02;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.98;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.86;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.04;
          }
          else if(pt > 30 && pt <= 40){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  0.98;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.96;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.99;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.96;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.96;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.96;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.95;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.95;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.95;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  0.99;
          }
          else if(pt > 40 && pt <= 50){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.01;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.00;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.98;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.97;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.97;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.97;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.97;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.98;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.00;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.00;
          }
          else if(pt > 50 && pt <= 60){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.00;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.94;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.98;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.97;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.96;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.98;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.92;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.91;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.00;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  0.96;
          }
          else if(pt > 60 && pt <= 100){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  0.90;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.99;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.02;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.98;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.98;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.98;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.97;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.85;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.97;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.00;
          }
       }//end TIGHT and zelel
       if (type_ == LOOSE  && zdecayMode_ == "zelel"){
          if(pt > 100.) pt = 100.; 
          if(pt > 10 && pt <= 20){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.11;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.08;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.14;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.10;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.01;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.11;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.14;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.22;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.08;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.07;
          }
          else if(pt > 20 && pt <= 30){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.00;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.06;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.15;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.07;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.03;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.97;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.13;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.03;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.04;
          }
          else if(pt > 30 && pt <= 40){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.02;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.00;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.93;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.01;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.99;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.00;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.95;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.95;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.03;
          }
          else if(pt > 40 && pt <= 50){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.01;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.01;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.02;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.99;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.99;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.99;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.00;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.01;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.01;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.00;
          }
          else if(pt > 50 && pt <= 100){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.00;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.01;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.02;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.00;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.00;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.98;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.91;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.99;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.01;
          }
       }//end LOOSE and zelel
       if (type_ == LOOSE && zdecayMode_ == "zmumu"){
          if(pt > 120.) pt = 120.; 
          if (pt > 20 && pt <= 25){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9950;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.0035;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9955;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 1.0035;
          }
          else if (pt > 25 && pt <= 30){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9925;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9955;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9959;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9943;
          }
          else if (pt > 30 && pt <= 40){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9998;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9979;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9992;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9969;
          }
          else if (pt > 40 && pt <= 50){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9989;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9995;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9981;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9959;
          }
          else if (pt > 50 && pt <= 60){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9947;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9975;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9992;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9911;
          }
          else if (pt > 60 && pt <= 120){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9995;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.0026;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9996;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.99978;
          }  
       }//LOOSE and zmumu
       if (type_ == TIGHT && zdecayMode_ == "zmumu"){
          if(pt > 120) pt = 120;
          if (pt > 20 && pt <= 25){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9748;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9861;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9838;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 1.0011;
          }
          else if (pt > 25 && pt <= 30){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9787;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9831;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9838;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9916;
          }
          else if (pt > 30 && pt <= 40){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9791;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9805;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9884;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9934;
          }
          else if (pt > 40 && pt <= 50){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9808;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9781;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9876;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9923;
          }
          else if (pt > 50 && pt <= 60){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9786;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9660;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9821;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9897;
          }
          else if (pt > 60 && pt <= 120){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9819;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9687;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9870;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9948;
          }
       }//TIGHT and zmumu
       return sf_ ; 
    }
  private: 
    double sf_ ;
    const std::string zdecayMode_ ; 
    LEPTONIDTYPES_t type_ ; 
};
#endif 
