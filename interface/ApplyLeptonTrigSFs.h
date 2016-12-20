#ifndef ANALYSIS_VLQANA_APPLYLEPTONTRIGSFS_HH
#define ANALYSIS_VLQANA_APPLYLEPTONTRIGSFS_HH

class ApplyLeptonTrigSFs {
  public:
   
    ~ApplyLeptonTrigSFs () {} 
    double TrigSFMu1(double pt, double eta){
      double sf_=0.0; 
      if(pt > 500.) pt = 499.9;
      if(pt > 10 && pt <= 20){     
	if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.470;
	else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.565;
	else if(eta <= -1.2     && eta > -1.6)    sf_ = 0.603;
	else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.591;
	else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.612;
	else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.612;
	else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.591;
	else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.603;
	else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.565;
	else if(eta < 2.4       && eta > 2.1)     sf_ = 0.470 ;
          }
      else if(pt > 20 && pt <= 25){
	if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.778;
	else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.902;
	else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.947;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.914;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.930;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.930;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.914;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.947;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.902;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.778 ;          
      }
      else if(pt > 25 && pt <= 30){
	if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.817;
	else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.920;
	else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.956;
	else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.917;
	else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.931;
	else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.931;
	else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.917;
	else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.956;
	else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.920;
	else if(eta < 2.4       && eta > 2.1)     sf_ = 0.817;
      }
      
      else if(pt > 30 && pt <= 35){
	if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.842;
	else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.928;
	else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.960;
	else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.916;
	else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932;
	else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.932;
	else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.916;
	else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.960;
	else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.928;
	else if(eta < 2.4       && eta > 2.1)     sf_ = 0.842;
      }
      else if(pt > 35 && pt <= 40){
	if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.858;
	else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.934;
	else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.962;
	else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.916;
	else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932;
	else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.932;
	else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.916;
	else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.962;
	else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.934;
	else if(eta < 2.4       && eta > 2.1)     sf_ = 0.858;
      }

      else if(pt > 40 && pt <= 50){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.876 ;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.936;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.961;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.917;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.932;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.932;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.917;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.961;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.936;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.876;
      }

      else if(pt > 50 && pt <= 75){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.886;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.936;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.956;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.914;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.929;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.929;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.914;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.956;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.936;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.886;
      }

      else if(pt > 75 && pt <= 100){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.886;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.928;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.936;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.911;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.923;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.923;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.911;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.936;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.928;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.886;
      }

      else if(pt > 100 && pt <= 200){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.872;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.896;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.898;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.903;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.920;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.920;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.903;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.898;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.896;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.872;
      }

      else if(pt > 200 && pt <= 300){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.837;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.786;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.809;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.871;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.901;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.901;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.871;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.809;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.786;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.837;
      }

      else if(pt > 300 && pt <500){
        if     (eta <= -2.1     && eta > -2.4)    sf_ = 0.700;
        else if(eta <= -1.6     && eta > -2.1)    sf_ = 0.703;
        else if(eta <= -1.2     && eta > -2.1)    sf_ = 0.718;
        else if(eta <= -0.8     && eta > -1.2)    sf_ = 0.901;
        else if(eta <= 0.0      && eta > -0.8)    sf_ = 0.899;
        else if(eta <= 0.8      && eta > 0.0)     sf_ = 0.899;
        else if(eta <= 1.2      && eta > 0.8)     sf_ = 0.901;
        else if(eta <= 1.6      && eta > 1.2)     sf_ = 0.718;
        else if(eta <= 2.1      && eta > 1.6)     sf_ = 0.703;
        else if(eta < 2.4       && eta > 2.1)     sf_ = 0.700;
      }
      return sf_ ;
    }

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
      /*
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
      */
       return sf_ ; 
    }
  private: 
    double sf_ ;
    // double TrigSFMu1(double pt, double eta);
    //double TrigSFMu2(double pt, double eta);
    //    TrigSFEl1(double pt, double eta);
    //TrigSFEL2(double pt, double eta);

   
};
#endif 
