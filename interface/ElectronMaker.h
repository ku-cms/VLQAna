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
   bool passElId(string WP, bool isEB, float dEtaIn, float dPhiIn, float full5x5siee, float HoE, float Iso, float D0, float Dz, float ooEmooP, bool conv, int missHits);
    
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
   //double elIsoMin_ ; 
   //double elIsoMax_ ; 
   //bool   useVID_ ; 
};
#endif
