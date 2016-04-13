#ifndef ANALYSIS_INTERFACE_APPLYJER_H
#define ANALYSIS_INTERFACE_APPLYJER_H

double ApplyJERMass() {
  double massjerscale(1.12) ; 
  return massjerscale ; 
}

double ApplyJERp4 (double eta, int jerShift) {

  eta = abs(eta) ;
  if (eta >= 4.7) eta = 4.699 ;
  double jerscale(0) ; 

  if (eta >= 3.2 && eta < 5.0) {
    if (jerShift == 1) jerscale = 1.320 ;  
    else if (jerShift == 2) jerscale = 1.606 ;  
    else if (jerShift == -1) jerscale = 1.034 ;  
  }
  else if (eta >= 3.0 && eta < 3.2) {
    if (jerShift == 1) jerscale = 1.303 ;  
    else if (jerShift == 2) jerscale = 1.414 ;  
    else if (jerShift == -1) jerscale = 1.192 ;  
  }
  else if (eta >= 2.5 && eta < 3.0) {
    if (jerShift == 1) jerscale = 1.343 ;  
    else if (jerShift == 2) jerscale = 1.466 ;  
    else if (jerShift == -1) jerscale = 1.220 ;  
  }
  else if (eta >= 1.9 && eta < 2.5) {
    if (jerShift == 1) jerscale = 1.126 ;  
    else if (jerShift == 2) jerscale = 1.220 ;  
    else if (jerShift == -1) jerscale = 1.032 ;  
  }
  else if (eta >= 1.3 && eta < 1.9) {
    if (jerShift == 1) jerscale = 1.088 ;  
    else if (jerShift == 2) jerscale = 1.117 ;  
    else if (jerShift == -1) jerscale = 1.059 ;  
  }
  else if (eta >= 0.8 && eta < 1.3) {
    if (jerShift == 1) jerscale = 1.061 ;  
    else if (jerShift == 2) jerscale = 1.084 ;  
    else if (jerShift == -1) jerscale = 1.038 ;  
  }
  else if (eta >= 0.0 && eta < 0.8) {
    if (jerShift == 1) jerscale = 1.061 ;  
    else if (jerShift == 2) jerscale = 1.084 ;  
    else if (jerShift == -1) jerscale = 1.038 ;  
  }

  return jerscale ; 

    //https://github.com/cms-jet/JERDatabase/blob/master/textFiles/Summer15_25nsV6/Summer15_25nsV6_DATAMCSF_AK4PFchs.txt
    //-4.7    -3.2  3   1.320     1.034     1.606
    //-3.2    -3.0  3   1.303     1.192     1.414
    //-3.0    -2.5  3   1.343     1.220     1.466
    //-2.5    -1.9  3   1.126     1.032     1.220
    //-1.9    -1.3  3   1.106     1.076     1.136
    //-1.3    -0.8  3   1.088     1.059     1.117
    //-0.8     0.0  3   1.061     1.038     1.084
    //0.0     0.8  3   1.061     1.038     1.084
    //0.8     1.3  3   1.088     1.059     1.117
    //1.3     1.9  3   1.106     1.076     1.136
    //1.9     2.5  3   1.126     1.032     1.220
    //2.5     3.0  3   1.343     1.220     1.466
    //3.0     3.2  3   1.303     1.192     1.414
    //3.2     4.7  3   1.320     1.034     1.606 
}

#endif 
