#ifndef ANALYSIS_VLQANA_ELECTRONMAKER_HH
#define ANALYSIS_VLQANA_ELECTRONMAKER_HH

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Electron.h"

using namespace std;
using namespace edm ; 

class ElectronMaker {
  public:
    enum ELECTRONIDTYPES_t {LOOSE, MEDIUM, TIGHT, VETO, HEEP} ; 
    ElectronMaker (edm::ParameterSet const&, edm::ConsumesCollector && iC) ; 
    ~ElectronMaker () ; 
    void operator () (edm::Event& evt, vlq::ElectronCollection& electrons) ; 
   bool passElId(string WP, bool isEB, float dEtaIn, float dPhiIn, float full5x5siee, float HoE, float Iso, float D0, float Dz, float ooEmooP, bool conv, int missHits);
    
  private: 
   //double getEleSF(double pt, double eta);
    ELECTRONIDTYPES_t type_ ; 
    edm::EDGetTokenT<std::vector<float>> t_elCharge             ;
    edm::EDGetTokenT<std::vector<float>> t_elD0                 ;
    edm::EDGetTokenT<std::vector<float>> t_elDz                 ;
    edm::EDGetTokenT<std::vector<float>> t_elE                  ;
    edm::EDGetTokenT<std::vector<float>> t_elEta                ;
    edm::EDGetTokenT<std::vector<float>> t_elHoE                ;
    edm::EDGetTokenT<std::vector<float>> t_elIso03              ;
    edm::EDGetTokenT<std::vector<float>> t_elKey                ;
    edm::EDGetTokenT<std::vector<float>> t_elMass               ;
    edm::EDGetTokenT<std::vector<float>> t_elPhi                ;
    edm::EDGetTokenT<std::vector<float>> t_elPt                 ;
    edm::EDGetTokenT<std::vector<float>> t_elY                  ;
    edm::EDGetTokenT<std::vector<float>> t_eldEtaIn             ;
    edm::EDGetTokenT<std::vector<float>> t_eldPhiIn             ;
    edm::EDGetTokenT<std::vector<float>> t_elfull5x5siee        ;
    edm::EDGetTokenT<std::vector<float>> t_elhasMatchedConVeto  ;
    edm::EDGetTokenT<std::vector<float>> t_elisEB               ;
    edm::EDGetTokenT<std::vector<float>> t_elisLoose            ;
    edm::EDGetTokenT<std::vector<float>> t_elisMedium           ;
    edm::EDGetTokenT<std::vector<float>> t_elisTight            ;
    edm::EDGetTokenT<std::vector<float>> t_elisVeto             ;
    edm::EDGetTokenT<std::vector<float>> t_elvidLoose           ;
    edm::EDGetTokenT<std::vector<float>> t_elvidMedium          ;
    edm::EDGetTokenT<std::vector<float>> t_elvidTight           ;
    edm::EDGetTokenT<std::vector<float>> t_elvidVeto            ;
    edm::EDGetTokenT<std::vector<float>> t_elvidHEEP            ;
    edm::EDGetTokenT<std::vector<float>> t_elmissHits           ;
    edm::EDGetTokenT<std::vector<float>> t_elooEmooP            ;
    edm::EDGetTokenT<std::vector<float>> t_elscEta              ;

    double elPtMin_ ; 
    double elPtMax_ ; 
    double elAbsEtaMax_ ; 
   //double elIsoMin_ ; 
   //double elIsoMax_ ; 
   //bool   useVID_ ; 
};
#endif
