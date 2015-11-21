#ifndef ANALYSIS_VLQANA_JETMAKER_H
#define ANALYSIS_VLQANA_JETMAKER_H

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "Analysis/VLQAna/interface/JetID.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

#include <boost/algorithm/string.hpp>
#include <string>
#include <TLorentzVector.h>

using namespace std;
using namespace edm ; 

class JetMaker { 
  public:
    enum JETTYPES_t { AK4JET, AK8JET, HTAGGEDAK8JET, CMSTOPTAGGEDAK8JET, PRUNEDSUBJET, N_JETTYPES} ; 
    JetMaker () ; 
    ~JetMaker () ; 
    JetMaker (edm::ParameterSet const&) ;
    void operator()(edm::Event&, vlq::JetCollection&) ;

  private:
    JETTYPES_t type_ ; 
    JetID* jetID_ ; 
    pat::strbitset retjetid_ ; 
    JetID::Quality_t quality_; 
    edm::ParameterSet JetIDParams_ ; 
    edm::ParameterSet JetSubstrParams_ ; 
    edm::ParameterSet SubjetParams_ ; 

    bool         scaleJetP4_     ;
    double       scaledJetMass_  ; 
    std::vector<std::string>  jecAK8GroomedPayloadNames_;

    double idxjetPtMin_          ;
    double idxjetPtMax_          ;
    double idxjetAbsEtaMax_      ;
    double idxjetCSVDiscMin_     ; 
    double idxjetCSVDiscMax_     ; 
    double idxjettau2Bytau1Min_  ; 
    double idxjettau2Bytau1Max_  ; 
    double idxjettau3Bytau2Min_  ; 
    double idxjettau3Bytau2Max_  ; 
    double idxjetMassMin_        ; 
    double idxjetMassMax_        ; 
    double idxjetPrunedMassMin_  ; 
    double idxjetPrunedMassMax_  ; 
    double idxjetTrimmedMassMin_ ; 
    double idxjetTrimmedMassMax_ ; 
    double idxjetWMassMin_       ; 
    double idxjetWMassMax_       ; 
    double idxjetTopMassMin_     ; 
    double idxjetTopMassMax_     ; 
    double idxjetMinMassMin_     ; 
    double idxjetMinMassMax_     ; 
    double idxjetnSubJetsMin_    ; 
    double idxjetnSubJetsMax_    ; 
    double idxsjMassMin_         ; 
    double idxsjCSVMin_          ; 
    double btaggedcsvlOP_        ; 
    double btaggedcsvmOP_        ; 
    double btaggedcsvtOP_        ; 

    edm::InputTag l_npv                ; 
    edm::InputTag l_rho                ; 
    edm::InputTag l_jetPt              ; 
    edm::InputTag l_jetEta             ; 
    edm::InputTag l_jetPhi             ; 
    edm::InputTag l_jetMass            ; 
    edm::InputTag l_jetEnergy          ; 
    edm::InputTag l_jetPartonFlavour   ; 
    edm::InputTag l_jetHadronFlavour   ; 
    edm::InputTag l_jetCSV             ; 
    edm::InputTag l_jetJEC             ; 
    edm::InputTag l_jetnHadEnergy      ;
    edm::InputTag l_jetnEMEnergy       ;
    edm::InputTag l_jetHFHadronEnergy  ;
    edm::InputTag l_jetcHadEnergy      ;
    edm::InputTag l_jetcEMEnergy       ;
    edm::InputTag l_jetnumDaughters    ;
    edm::InputTag l_jetcMultip         ;
    edm::InputTag l_jetY               ;
    edm::InputTag l_jetArea            ; 
    edm::InputTag l_jettau1            ; 
    edm::InputTag l_jettau2            ; 
    edm::InputTag l_jettau3            ; 
    edm::InputTag l_jetPrunedMass      ; 
    edm::InputTag l_jetTrimmedMass     ; 
    edm::InputTag l_jetFilteredMass    ; 
    edm::InputTag l_jetSoftDropMass    ; 
    edm::InputTag l_jetwMass           ; 
    edm::InputTag l_jettopMass         ; 
    edm::InputTag l_jetminMass         ; 
    edm::InputTag l_jetnSubJets        ; 
    edm::InputTag l_vjetsjIdx0         ; 
    edm::InputTag l_vjetsjIdx1         ; 
    edm::InputTag l_tjetsjIdx0         ; 
    edm::InputTag l_tjetsjIdx1         ; 
    edm::InputTag l_tjetsjIdx2         ; 
    edm::InputTag l_tjetsjIdx3         ; 
    edm::InputTag l_ak8sjPt            ; 
    edm::InputTag l_ak8sjEta           ; 
    edm::InputTag l_ak8sjPhi           ; 
    edm::InputTag l_ak8sjMass          ; 
    edm::InputTag l_ak8sjCSV           ; 
    boost::shared_ptr<FactorizedJetCorrector> jecAK8Groomed_ ;    
    bool doGroomedMassCorr_;

};

#endif 
