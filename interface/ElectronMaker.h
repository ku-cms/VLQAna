#ifndef ANALYSIS_VLQANA_ELECTRONMAKER_HH
#define ANALYSIS_VLQANA_ELECTRONMAKER_HH

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Electron.h"

using namespace std;
using namespace edm ; 

class ElectronMaker {
  public:
    enum ELECTRONIDTYPES_t {LOOSE, MEDIUM, TIGHT, VETO, HEEP} ; 
    ElectronMaker (edm::ParameterSet const& pars) ; 
    ~ElectronMaker () ; 
    void operator () (edm::Event& evt, vlq::ElectronCollection& electrons) ; 

  private: 
   //double getEleSF(double pt, double eta);
    ELECTRONIDTYPES_t type_ ; 
    edm::InputTag l_elCharge        ;
    edm::InputTag l_elD0            ;
    edm::InputTag l_elDz            ;
    edm::InputTag l_elE             ;
    edm::InputTag l_elEta           ;
    edm::InputTag l_elHoE           ;
    edm::InputTag l_elIso03         ;
    edm::InputTag l_elKey           ;
    edm::InputTag l_elMass          ;
    edm::InputTag l_elPhi           ;
    edm::InputTag l_elPt            ;
    edm::InputTag l_elY             ;
    edm::InputTag l_eldEtaIn        ;
    edm::InputTag l_eldPhiIn        ;
    edm::InputTag l_elfull5x5siee   ;
    edm::InputTag l_elhasMatchedConVeto   ;
    edm::InputTag l_elisEB          ;
    edm::InputTag l_elisLoose       ;
    edm::InputTag l_elisMedium      ;
    edm::InputTag l_elisTight       ;
    edm::InputTag l_elisVeto        ;
    edm::InputTag l_elvidLoose      ;
    edm::InputTag l_elvidMedium     ;
    edm::InputTag l_elvidTight      ;
    edm::InputTag l_elvidVeto       ;
    edm::InputTag l_elvidHEEP       ;
    edm::InputTag l_elmissHits      ;
    edm::InputTag l_elooEmooP       ;
    edm::InputTag l_elscEta         ;

    double elPtMin_ ; 
    double elPtMax_ ; 
    double elAbsEtaMax_ ; 
    double elIsoMin_ ; 
    double elIsoMax_ ; 
    bool   useVID_ ; 
};
#endif
/*
inline double ElectronMaker::getEleSF(double pt, double eta){
   double SF = 1.0;
   if(pt > 10 && pt <= 20){
      if(eta <= -2.0          && eta > -2.5)    SF =  1.15;
      else if(eta <= -1.566   && eta > -2.0)    SF =  0.96;
      else if(eta <= -1.4442  && eta > -1.566)  SF =  1.12;
      else if(eta <= -0.8     && eta > -1.4442) SF =  1.07;
      else if(eta <= 0.0      && eta > -0.8)    SF =  1.05;
      else if(eta <= 0.8      && eta > 0.0)     SF =  1.01;
      else if(eta <= 1.4442   && eta > 0.8)     SF =  1.05;
      else if(eta <= 1.566    && eta > 1.4442)  SF =  1.52;
      else if(eta <= 2.0      && eta > 1.566)   SF =  1.01;
      else if(eta < 2.5       && eta > 2.0)     SF =  1.05;
   }
   else if(pt > 20 && pt <= 30){
      if(eta <= -2.0          && eta > -2.5)    SF =  1.01;
      else if(eta <= -1.566   && eta > -2.0)    SF =  0.94;
      else if(eta <= -1.4442  && eta > -1.566)  SF =  1.06;
      else if(eta <= -0.8     && eta > -1.4442) SF =  1.00;
      else if(eta <= 0.0      && eta > -0.8)    SF =  0.99;
      else if(eta <= 0.8      && eta > 0.0)     SF =  1.00;
      else if(eta <= 1.4442   && eta > 0.8)     SF =  1.02;
      else if(eta <= 1.566    && eta > 1.4442)  SF =  0.98;
      else if(eta <= 2.0      && eta > 1.566)   SF =  0.86;
      else if(eta < 2.5       && eta > 2.0)     SF =  1.04;
   }
   else if(pt > 30 && pt <= 40){
      if(eta <= -2.0          && eta > -2.5)    SF =  0.98;
      else if(eta <= -1.566   && eta > -2.0)    SF =  0.96;
      else if(eta <= -1.4442  && eta > -1.566)  SF =  0.99;
      else if(eta <= -0.8     && eta > -1.4442) SF =  0.96;
      else if(eta <= 0.0      && eta > -0.8)    SF =  0.96;
      else if(eta <= 0.8      && eta > 0.0)     SF =  0.96;
      else if(eta <= 1.4442   && eta > 0.8)     SF =  0.95;
      else if(eta <= 1.566    && eta > 1.4442)  SF =  0.95;
      else if(eta <= 2.0      && eta > 1.566)   SF =  0.95;
      else if(eta < 2.5       && eta > 2.0)     SF =  0.99;
   }
   else if(pt > 40 && pt <= 50){
      if(eta <= -2.0          && eta > -2.5)    SF =  1.01;
      else if(eta <= -1.566   && eta > -2.0)    SF =  1.00;
      else if(eta <= -1.4442  && eta > -1.566)  SF =  0.98;
      else if(eta <= -0.8     && eta > -1.4442) SF =  0.97;
      else if(eta <= 0.0      && eta > -0.8)    SF =  0.97;
      else if(eta <= 0.8      && eta > 0.0)     SF =  0.97;
      else if(eta <= 1.4442   && eta > 0.8)     SF =  0.97;
      else if(eta <= 1.566    && eta > 1.4442)  SF =  0.98;
      else if(eta <= 2.0      && eta > 1.566)   SF =  1.00;
      else if(eta < 2.5       && eta > 2.0)     SF =  1.00;
   }
   else if(pt > 50 && pt <= 60){
      if(eta <= -2.0          && eta > -2.5)    SF =  1.00;
      else if(eta <= -1.566   && eta > -2.0)    SF =  0.94;
      else if(eta <= -1.4442  && eta > -1.566)  SF =  0.98;
      else if(eta <= -0.8     && eta > -1.4442) SF =  0.97;
      else if(eta <= 0.0      && eta > -0.8)    SF =  0.96;
      else if(eta <= 0.8      && eta > 0.0)     SF =  0.98;
      else if(eta <= 1.4442   && eta > 0.8)     SF =  0.92;
      else if(eta <= 1.566    && eta > 1.4442)  SF =  0.91;
      else if(eta <= 2.0      && eta > 1.566)   SF =  1.00;
      else if(eta < 2.5       && eta > 2.0)     SF =  0.96;
   }
   else if(pt > 60 && pt <= 100){
      if(eta <= -2.0          && eta > -2.5)    SF =  0.90;
      else if(eta <= -1.566   && eta > -2.0)    SF =  0.99;
      else if(eta <= -1.4442  && eta > -1.566)  SF =  1.02;
      else if(eta <= -0.8     && eta > -1.4442) SF =  0.98;
      else if(eta <= 0.0      && eta > -0.8)    SF =  0.98;
      else if(eta <= 0.8      && eta > 0.0)     SF =  0.98;
      else if(eta <= 1.4442   && eta > 0.8)     SF =  0.97;
      else if(eta <= 1.566    && eta > 1.4442)  SF =  0.85;
      else if(eta <= 2.0      && eta > 1.566)   SF =  0.97;
      else if(eta < 2.5       && eta > 2.0)     SF =  1.00;
   }
   return SF;
     
}
*/
