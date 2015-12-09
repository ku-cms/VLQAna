#ifndef ANALYSIS_VLQANA_APPLYLEPTONSFS_HH
#define ANALYSIS_VLQANA_APPLYLEPTONSFS_HH

class ApplyLeptonSFs {
  public:
    ApplyLeptonSFs () : 
      sf_(1) 
  {}
    ~ApplyLeptonSFs () {} 
    double operator () (double pt, double eta){
      if (pt > 100.) pt = 100. ; 
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
      return sf_ ; 
    }
  private: 
    double sf_ ; 
};
#endif 
