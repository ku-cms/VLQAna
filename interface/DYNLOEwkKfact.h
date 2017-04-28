#ifndef ANALYSIS_VLQANA_DYNLOEWKKFACT_HH
#define ANALYSIS_VLQANA_DYNLOEWKKFACT_HH

#include <string>
#include <TFile.h>
#include <TF1.h>

class DYNLOEwkKfact {
  
  public:
    DYNLOEwkKfact (const std::string fname_DYNLOCorr, const std::string funname_DYNLOCorr) { 
      file_DYNLOCorr_ = std::unique_ptr<TFile>(new TFile(fname_DYNLOCorr.c_str())) ;
      fun_DYNLOCorr_ = std::unique_ptr<TF1>(dynamic_cast<TF1*>(file_DYNLOCorr_->Get(funname_DYNLOCorr.c_str()))) ;
    }

    double const operator () (const double dileppt) {
      return fun_DYNLOCorr_->Eval(dileppt); 
    }

  private:

    std::unique_ptr<TFile>file_DYNLOCorr_ ; 
    std::unique_ptr<TF1>fun_DYNLOCorr_ ; 

} ; 

#endif
