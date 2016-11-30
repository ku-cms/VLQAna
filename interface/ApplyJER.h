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
    if (jerShift == 1) jerscale = 1.226 ;  
    else if (jerShift == 2) jerscale = 1.371 ;  
    else if (jerShift == -1) jerscale = 1.081 ;  
  }
  else if (eta >= 3.0 && eta < 3.2) {
    if (jerShift == 1) jerscale = 0.998 ;  
    else if (jerShift == 2) jerscale = 1.064 ;  
    else if (jerShift == -1) jerscale = 0.932 ;  
  }
  else if (eta >= 2.8 && eta < 3.0) {
    if (jerShift == 1) jerscale = 1.595 ;  
    else if (jerShift == 2) jerscale = 1.770 ;  
    else if (jerShift == -1) jerscale = 1.420 ;  
  }
  else if (eta >= 2.5 && eta < 2.8) {
    if (jerShift == 1) jerscale = 1.266 ;  
    else if (jerShift == 2) jerscale = 1.398 ;  
    else if (jerShift == -1) jerscale = 1.134 ;  
  }
  else if (eta >= 2.3 && eta < 2.5) {
    if (jerShift == 1) jerscale = 1.168 ;  
    else if (jerShift == 2) jerscale = 1.288 ;  
    else if (jerShift == -1) jerscale = 1.048 ;  
  }
  else if (eta >= 2.1 && eta < 2.3) {
    if (jerShift == 1) jerscale = 1.094 ;  
    else if (jerShift == 2) jerscale = 1.187 ;  
    else if (jerShift == -1) jerscale = 1.001 ;  
  }
  else if (eta >= 1.9 && eta < 2.1) {
    if (jerShift == 1) jerscale = 1.167 ;  
    else if (jerShift == 2) jerscale = 1.253 ;  
    else if (jerShift == -1) jerscale = 1.081 ;  
  }
  else if (eta >= 1.7 && eta < 1.9) {
    if (jerShift == 1) jerscale = 1.041 ;  
    else if (jerShift == 2) jerscale = 1.103 ;  
    else if (jerShift == -1) jerscale = 0.979 ;  
  }
  else if (eta >= 1.3 && eta < 1.7) {
    if (jerShift == 1) jerscale = 1.115 ;  
    else if (jerShift == 2) jerscale = 1.145 ;  
    else if (jerShift == -1) jerscale = 1.085 ;  
  }
  else if (eta >= 1.1 && eta < 1.3) {
    if (jerShift == 1) jerscale = 1.029 ;  
    else if (jerShift == 2) jerscale = 1.095 ;  
    else if (jerShift == -1) jerscale = 0.963 ;  
  }
  else if (eta >= 0.8 && eta < 1.1) {
    if (jerShift == 1) jerscale = 1.168 ;  
    else if (jerShift == 2) jerscale = 1.214 ;  
    else if (jerShift == -1) jerscale = 1.122 ;  
  }
  else if (eta >= 0.5 && eta < 0.8) {
    if (jerShift == 1) jerscale = 1.167 ;  
    else if (jerShift == 2) jerscale = 1.215 ;  
    else if (jerShift == -1) jerscale = 1.119 ;  
  }
  else if (eta >= 0.0 && eta < 0.5) {
    if (jerShift == 1) jerscale = 1.122 ;  
    else if (jerShift == 2) jerscale = 1.148 ;  
    else if (jerShift == -1) jerscale = 1.096 ;  
  }

  return jerscale ; 
//2015 JERs
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
    ///
//2016 JERs
    //https://github.com/cms-jet/JERDatabase/blob/master/textFiles/Spring16_25nsV6/Spring16_25nsV6_MC_SF_AK4PFchs.txt  (same SFs for AK8CHS and AK8Puppi)
    //-4.7  -3.2  3   1.226  1.081  1.371
    //-3.2  -3.0  3   0.998  0.932  1.064
    //-3.0  -2.8  3   1.595  1.420  1.770
    //-2.8  -2.5  3   1.266  1.134  1.398
    //-2.5  -2.3  3   1.168  1.048  1.288
    //-2.3  -2.1  3   1.094  1.001  1.187
    //-2.1  -1.9  3   1.167  1.081  1.253
    //-1.9  -1.7  3   1.041  0.979  1.103
    //-1.7  -1.3  3   1.115  1.085  1.145
    //-1.3  -1.1  3   1.029  0.963  1.095 
    //-1.1  -0.8  3   1.168  1.122  1.214
    //-0.8  -0.5  3   1.167  1.119  1.215
    //-0.5   0.0  3   1.122  1.096  1.148
    // 0.0   0.5  3   1.122  1.096  1.148   
    // 0.5   0.8  3   1.167  1.119  1.215
    // 0.8   1.1  3   1.168  1.122  1.214
    // 1.1   1.3  3   1.029  0.963  1.095
    // 1.3   1.7  3   1.115  1.085  1.145
    // 1.7   1.9  3   1.041  0.979  1.103
    // 1.9   2.1  3   1.167  1.081  1.253
    // 2.1   2.3  3   1.094  1.001  1.187
    // 2.3   2.5  3   1.168  1.048  1.288
    // 2.5   2.8  3   1.266  1.134  1.398
    // 2.8   3.0  3   1.595  1.420  1.770
    // 3.0   3.2  3   0.998  0.932  1.064
    // 3.2   4.7  3   1.226  1.081  1.371
     
}

#endif 
