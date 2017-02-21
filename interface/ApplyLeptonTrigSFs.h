#ifndef ANALYSIS_VLQANA_APPLYLEPTONTRIGSFS_HH
#define ANALYSIS_VLQANA_APPLYLEPTONTRIGSFS_HH

class ApplyLeptonTrigSFs {
  public:
   
    ~ApplyLeptonTrigSFs () {} 
    double TrigSFMu1(double pt, double eta){
      double sf_=0.0; 
      if(pt > 500.) pt = 500.0;
      if(pt > 26 && pt <= 30){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.906216;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.982503;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.956337;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.980357;
      }
      
      else if(pt > 30 && pt <= 40){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.944555;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.99548;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.965959;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.984096;
     }
    
      else if(pt > 40 && pt <= 50){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.957532;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.99912;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.967858;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.984904;
      }

      else if(pt > 50 && pt <= 60){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.960397;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.99912;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.968175;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.985122;
      }

      else if(pt > 60 && pt <= 120){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.95241;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.998937;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.964898;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.983897;
      }

      else if(pt > 120 && pt <= 200){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.977009;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.00552;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.946724;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.976031;
      }

      else if(pt > 200 && pt <= 500){
	if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.918103;
        else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.982804;
        else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.949605;
        else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.983284;
      }
      return sf_ ;
    }
    /*
    double TrigSFMu2(double pt, double eta){
      double sf_=0.0;

      if(pt > 500.) pt = 499.9;
      if(pt > 10 && pt <= 20){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.899 ;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.915;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.946;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.918;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.927;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.927;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.918;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.946;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.915;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.899;
      }
      else if(pt > 20 && pt <= 25){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.915;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.932;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.957;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.921;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.931;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.931;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.921;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.957;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.932;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.915;
      }

      else if(pt > 25 && pt <= 30){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.924;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.937;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.962;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.922;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.932;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.922;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.962;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.937;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.924;
      }
      else if(pt > 30 && pt <= 35){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.929;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.941;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.964;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.920;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.932;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.920;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.964;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.941;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.929;
      }
      else if(pt > 35 && pt <= 40){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.933;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.943;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.965;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.920;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.932;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.920;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.965;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.943;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.933;
      }
      else if(pt > 40 && pt <= 50){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.934;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.944;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.964;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.920;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.933;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.933;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.920;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.964;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.944;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.934;
      }
      else if(pt > 50 && pt <= 75){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.931;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.941;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.958;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.917;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.929;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.929;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.917;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.958;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.941;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.931;
      }
      else if(pt > 75 && pt <= 100){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.919;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.932;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.938;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.913;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.924;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.924;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.913;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.938;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.932;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.919;
      }
      else if(pt > 100 && pt <= 200){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.901;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.899;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.899;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.905;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.920;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.920;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.905;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.899;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.899;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.901;
      }
      else if(pt > 200 && pt <= 300){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.859;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.791;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.812;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.876;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.901;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.901;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.876;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.812;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.791;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.859;
      }
      else if(pt > 300 && pt <= 500){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.800;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.714;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.713;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.901;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.899;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.899;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.901;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.713;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.714;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.800;
      }
      
      else if(pt > 20 && pt <= 25){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = ;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = ;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = ;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = ;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = ;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = ;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = ;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = ;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = ;
        else if(eta < 2.4       && eta > 2.1)     sf_ = ;
      }
      
       return sf_ ; 
       
       }
    */
  private: 
    double sf_ ;
    // double TrigSFMu1(double pt, double eta);
    //double TrigSFMu2(double pt, double eta);
    //    TrigSFEl1(double pt, double eta);
    //TrigSFEL2(double pt, double eta);

   
};
#endif 
