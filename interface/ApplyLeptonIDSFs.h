#ifndef ANALYSIS_VLQANA_APPLYLEPTONIDSFS_HH
#define ANALYSIS_VLQANA_APPLYLEPTONIDSFS_HH

class ApplyLeptonIDSFs {
  public:
    enum LEPTONIDTYPES_t {LOOSE, TIGHT} ; 
    ApplyLeptonIDSFs (edm::ParameterSet const& pars) : 
      sf_(1),
      zdecayMode_(pars.getParameter<std::string>("zdecayMode")) 
  {
    std::string lepidtypestr = pars.getParameter<std::string>("lepidtype") ; 
    if ( lepidtypestr == "LOOSE" ) type_ = LOOSE ;  
    else if ( lepidtypestr == "TIGHT" ) type_ = TIGHT ; 
    else edm::LogError("ApplyLeptonSF") << " >>>> WrongElectronIdType: " << type_<< " Check lepton id type !!!" ; 
  }
    ~ApplyLeptonIDSFs () {} 
    double operator () (double pt, double eta){
      if (type_ == TIGHT && zdecayMode_ == "zelel"){
        if(pt > 200.) pt = 200.; 
        if(pt > 10 && pt <= 20){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.813559;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.7737;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.89243;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.94086;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.901515;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.916256;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.933333;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.01456;
          else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.796923;
          else if(eta < 2.5       && eta > 2.0)     sf_ =  0.829341;
        }
        else if(pt > 20 && pt <= 30){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.87269  ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.837255 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.937685 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.934363 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.925373 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.951941 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.934741 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.909366;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.852071 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.880077 ;
        }
        else if(pt > 30 && pt <= 40){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.930195  ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.901563 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.946392  ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.954829 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932127 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.948563 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.9939628 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.945833 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.914861 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.916279 ;
        }
        else if(pt > 40 && pt <= 50){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.942611 ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.933426 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.945073 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.953103 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932615 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.953867 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.94528 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.927066 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.938441 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.942737 ;
        }
        else if(pt > 50 && pt <=200){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.954116 ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.946753 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.95679 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.953428 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.939009 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.95414 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.953608 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.936267 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.967742 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.949735 ;
        }
      }//end TIGHT and zelel
      if (type_ == LOOSE  && zdecayMode_ == "zelel"){
        if(pt > 200.) pt = 200.; 
        if(pt > 10 && pt <= 20){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.917582  ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.817717 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.898678 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.965135 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.961353 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.919431 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.957075 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.97852 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.864111 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.896959 ;
        }
        else if(pt > 20 && pt <= 30){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.950617 ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.905138 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.943609 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.957031 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.956975 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.971466 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.960938 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.954802 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.915436 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.945551 ;
        }
        else if(pt > 30 && pt <= 40){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 0.991474 ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.962485 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.97274 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.976932 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.966705 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.977012 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.971231 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.964029 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.96831 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.976134 ;
        }
        else if(pt > 40 && pt <= 50){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 1.001116 ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.983259 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.973171 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.979303 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.971678 ;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.981441 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.977199 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.964591 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 0.985523 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.990868 ;
        }
        else if(pt > 50 && pt <= 200){
          if(eta <= -2.0          && eta > -2.5)    sf_ = 1.00456 ;
          else if(eta <= -1.566   && eta > -2.0)    sf_ = 0.990099 ;
          else if(eta <= -1.4442  && eta > -1.566)  sf_ = 0.980746 ;
          else if(eta <= -0.8     && eta > -1.4442) sf_ = 0.98174 ;
          else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.973205;
          else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.984946 ;
          else if(eta <= 1.4442   && eta > 0.8)     sf_ = 0.982833 ;
          else if(eta <= 1.566    && eta > 1.4442)  sf_ = 0.976077 ;
          else if(eta <= 2.0      && eta > 1.566)   sf_ = 1.0022 ;
          else if(eta < 2.5       && eta > 2.0)     sf_ = 0.99666 ;
        }
      }//end LOOSE and zelel
      if (type_ == LOOSE && zdecayMode_ == "zmumu"){
        if(pt > 200.) pt = 200.; 
        if (pt > 20 && pt <= 25){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 1.00257;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.00047;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.995499;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.977091;
        }
        else if (pt > 25 && pt <= 30){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.997522;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.99901;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.992138;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.991379;
        }
        else if (pt > 30 && pt <= 40){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.995137;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.99912;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.996141;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.996729;
        }
        else if (pt > 40 && pt <= 50){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.994269;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.998493;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.995362;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.996736;
        }
        else if (pt > 50 && pt <= 60){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.998696;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.997555;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.996281;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.992798;
        }
        else if (pt > 60 && pt <= 100){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.98288;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.99412;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.991941;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.991625;
        } 
        else if (pt > 100 && pt <= 200){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.952418;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.00357;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 1.0;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 1.00099;
        }
      }//LOOSE and zmumu
      if (type_ == TIGHT && zdecayMode_ == "zmumu"){
        if(pt > 200.) pt = 200.;
        if (pt > 20 && pt <= 25){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.985294;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.991418;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.909183;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.908376;
        }
        else if (pt > 25 && pt <= 30){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.975853;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.989645;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.966866;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.970763;
        }
        else if (pt > 30 && pt <= 40){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.973918;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.990198;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.971573;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.975881;
        }
        else if (pt > 40 && pt <= 50){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.969894;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.990848;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.970849;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.976182;
        }
        else if (pt > 50 && pt <= 60){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.972266;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.971497;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.991589;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.981064;
        }
        else if (pt > 60 && pt <= 100){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.975218;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.989786;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.968216;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.973523;
        }
        else if (pt > 100 && pt <= 200){
          if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.91808;
          else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.01349;
          else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 1.02714;
          else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.987644;
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
