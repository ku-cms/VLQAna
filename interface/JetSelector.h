#ifndef JETSELECTOR_H
#define JETSELECTOR_H

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "Analysis/VLQAna/interface/JetID.h"

#include <boost/algorithm/string.hpp>
#include <string>
#include <TLorentzVector.h>

using namespace std;
using namespace edm ; 

class JetSelector { 
  public:

    enum JETTYPES_t { AK4JET, BTAGGEDAK4JET, AK8JET, BTAGGEDAK8JET, HTAGGEDAK8JET, CMSTOPTAGGEDAK8JET, PRUNEDSUBJET, N_JETTYPES} ; 

    JetSelector () {} 

    JetSelector (edm::ParameterSet const& pars) :
      JetIDParams_ (pars.getParameter<edm::ParameterSet> ("JetIDParams")), 
      JetSubstrParams_ (pars.getParameter<edm::ParameterSet> ("JetSubstrParams")), 
      SubjetParams_ (pars.getParameter<edm::ParameterSet> ("SubjetParams")) 
    {

      std::string jettypeStr = pars.getParameter<std::string>("jettype") ;
      if      (jettypeStr == "AK4JET")             type_ = AK4JET; 
      else if (jettypeStr == "BTAGGEDAK4JET")      type_ = BTAGGEDAK4JET;
      else if (jettypeStr == "AK8JET")             type_ = AK8JET;
      else if (jettypeStr == "BTAGGEDAK8JET")      type_ = BTAGGEDAK8JET;
      else if (jettypeStr == "HTAGGEDAK8JET")      type_ = HTAGGEDAK8JET;
      else if (jettypeStr == "CMSTOPTAGGEDAK8JET") type_ = CMSTOPTAGGEDAK8JET;
      else if (jettypeStr == "PRUNEDSUBJET")       type_ = PRUNEDSUBJET; 
      else edm::LogError("JetSelector::JetSelector") << " >>>> WrongJetType: " << type_<< " Check jet type !!!" ; 

      l_jetPt              = JetIDParams_.getParameter<edm::InputTag> ("jetPtLabel") ;                   
      l_jetEta             = JetIDParams_.getParameter<edm::InputTag> ("jetEtaLabel") ;                  
      l_jetPhi             = JetIDParams_.getParameter<edm::InputTag> ("jetPhiLabel") ;                   
      l_jetMass            = JetIDParams_.getParameter<edm::InputTag> ("jetMassLabel") ;                 
      l_jetEnergy          = JetIDParams_.getParameter<edm::InputTag> ("jetEnergyLabel") ;               
      l_jetFlavour         = JetIDParams_.getParameter<edm::InputTag> ("jetFlavourLabel") ;                  
      l_jetCSV             = JetIDParams_.getParameter<edm::InputTag> ("jetCSVLabel") ;              
      l_jetJEC             = JetIDParams_.getParameter<edm::InputTag> ("jetJECLabel") ;           
      l_jetnHadEnergy      = JetIDParams_.getParameter<edm::InputTag> ("jetnHadEnergyLabel") ;          
      l_jetnEMEnergy       = JetIDParams_.getParameter<edm::InputTag> ("jetnEMEnergyLabel") ;         
      l_jetHFHadronEnergy  = JetIDParams_.getParameter<edm::InputTag> ("jetHFHadronEnergyLabel") ;      
      l_jetcHadEnergy      = JetIDParams_.getParameter<edm::InputTag> ("jetcHadEnergyLabel") ;          
      l_jetcEMEnergy       = JetIDParams_.getParameter<edm::InputTag> ("jetcEMEnergyLabel") ;            
      l_jetnumDaughters    = JetIDParams_.getParameter<edm::InputTag> ("jetnumDaughtersLabel") ;             
      l_jetcMultip         = JetIDParams_.getParameter<edm::InputTag> ("jetcMultipLabel") ;              
      l_jetY               = JetIDParams_.getParameter<edm::InputTag> ("jetYLabel") ;                      
      l_jetArea            = JetIDParams_.getParameter<edm::InputTag> ("jetAreaLabel") ;                        
      if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
        l_jettau1            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau1Label") ;
        l_jettau2            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau2Label") ;
        l_jettau3            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau3Label") ;
        l_jetprunedMass      = JetSubstrParams_.getParameter<edm::InputTag> ("jetPrunedMassLabel") ;
        l_jettrimmedMass     = JetSubstrParams_.getParameter<edm::InputTag> ("jetTrimmedMassLabel") ;
        l_jetwMass           = JetSubstrParams_.getParameter<edm::InputTag> ("jetWMassLabel") ;
        l_jettopMass         = JetSubstrParams_.getParameter<edm::InputTag> ("jettopMassLabel") ;
        l_jetminMass         = JetSubstrParams_.getParameter<edm::InputTag> ("jetminMassLabel") ;
        l_jetnSubJets        = JetSubstrParams_.getParameter<edm::InputTag> ("jetnSubJetsLabel") ; 
        l_vjetsjIdx0         = JetSubstrParams_.getParameter<edm::InputTag> ("vjetsjIdx0Label") ; 
        l_vjetsjIdx1         = JetSubstrParams_.getParameter<edm::InputTag> ("vjetsjIdx1Label") ; 
        l_tjetsjIdx0         = JetSubstrParams_.getParameter<edm::InputTag> ("tjetsjIdx2Label") ; 
        l_tjetsjIdx1         = JetSubstrParams_.getParameter<edm::InputTag> ("tjetsjIdx3Label") ; 
        l_tjetsjIdx2         = JetSubstrParams_.getParameter<edm::InputTag> ("tjetsjIdx2Label") ; 
        l_tjetsjIdx3         = JetSubstrParams_.getParameter<edm::InputTag> ("tjetsjIdx3Label") ; 
        l_ak8sjPt            = SubjetParams_.getParameter<edm::InputTag> ("jetPtLabel") ; 
        l_ak8sjEta           = SubjetParams_.getParameter<edm::InputTag> ("jetEtaLabel") ; 
        l_ak8sjPhi           = SubjetParams_.getParameter<edm::InputTag> ("jetEtaLabel") ; 
        l_ak8sjMass          = SubjetParams_.getParameter<edm::InputTag> ("jetMassLabel") ; 
        l_ak8sjCSV           = SubjetParams_.getParameter<edm::InputTag> ("jetCSVLabel") ; 
      }

      idxjetPtMin_ = pars.getParameter<double>("jetPtMin")  ;
      idxjetPtMax_ = pars.getParameter<double>("jetPtMax")  ;
      idxjetAbsEtaMax_ = pars.getParameter<double>("jetAbsEtaMax")  ;
      idxjetCSVDiscMin_ = pars.getParameter<double>("jetCSVDiscMin")  ;
      idxjetCSVDiscMax_ = pars.getParameter<double>("jetCSVDiscMax")  ;
      if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
        idxjettau2Bytau1Min_ = pars.getParameter<double>("jettau2Bytau1Min")  ;
        idxjettau2Bytau1Max_ = pars.getParameter<double>("jettau2Bytau1Max")  ;
        idxjettau3Bytau2Min_ = pars.getParameter<double>("jettau3Bytau2Min")  ;
        idxjettau3Bytau2Max_ = pars.getParameter<double>("jettau3Bytau2Max")  ;
        idxjetMassMin_ = pars.getParameter<double>("jetMassMin")  ;
        idxjetMassMax_ = pars.getParameter<double>("jetMassMax")  ;
        idxjetPrunedMassMin_ = pars.getParameter<double>("jetPrunedMassMin")  ;
        idxjetPrunedMassMax_ = pars.getParameter<double>("jetPrunedMassMax")  ;
        idxjetTrimmedMassMin_ = pars.getParameter<double>("jetTrimmedMassMin")  ;
        idxjetTrimmedMassMax_ = pars.getParameter<double>("jetTrimmedMassMax")  ;
        idxjetWMassMin_ = pars.getParameter<double>("jetWMassMin")  ;
        idxjetWMassMax_ = pars.getParameter<double>("jetWMassMax")  ;
        idxjetTopMassMin_ = pars.getParameter<double>("jetTopMassMin")  ;
        idxjetTopMassMax_ = pars.getParameter<double>("jetTopMassMax")  ;
        idxjetMinMassMin_ = pars.getParameter<double>("jetMinMassMin")  ;
        idxjetMinMassMax_ = pars.getParameter<double>("jetMinMassMax")  ;
        idxjetnSubJetsMin_ = pars.getParameter<double>("jetnSubJetsMin")  ;
        idxjetnSubJetsMax_ = pars.getParameter<double>("jetnSubJetsMax")  ;
        idxsjMassMin_ = pars.getParameter<double>("subjetMassMin")  ;
        idxsjCSVMin_ = pars.getParameter<double>("subjetCSVMin")  ;
        idxsjCSVMax_ = pars.getParameter<double>("subjetCSVMax")  ;
      }

      if (pars.getParameter<bool>("IsJetIDLoose") == true && pars.getParameter<bool>("IsJetIDTight") == false) quality_ = JetID::LOOSE ; 
      else if (pars.getParameter<bool>("IsJetIDTight") == true && pars.getParameter<bool>("IsJetIDLoose") == false) quality_ = JetID::TIGHT ; 
      else edm::LogError("JetSelector::JetSelector") << "Ambiguous JetID: Please select only one (LOOSE or TIGHT) as True!!!" ; 

    }

    bool operator()(edm::Event& evt, int const & jet, bool& ret ) {

      JetID jetID(JetIDParams_) ; 
      pat::strbitset retjetid = jetID.getBitTemplate() ;
      retjetid.set(false) ;
      if (jetID(evt, jet, retjetid) == false) return false ; 

      ret = false ; 

      Handle <vector<float>>  h_jetPt             ; evt.getByLabel (l_jetPt               , h_jetPt             );
      Handle <vector<float>>  h_jetEta            ; evt.getByLabel (l_jetEta              , h_jetEta            );
      Handle <vector<float>>  h_jetPhi            ; evt.getByLabel (l_jetPhi              , h_jetPhi            );
      Handle <vector<float>>  h_jetMass           ; evt.getByLabel (l_jetMass             , h_jetMass           );
      Handle <vector<float>>  h_jetEnergy         ; evt.getByLabel (l_jetEnergy           , h_jetEnergy         );
      Handle <vector<float>>  h_jetFlavour        ; evt.getByLabel (l_jetFlavour          , h_jetFlavour        );
      Handle <vector<float>>  h_jetCSV            ; evt.getByLabel (l_jetCSV              , h_jetCSV            );
      Handle <vector<float>>  h_jetJEC            ; evt.getByLabel (l_jetJEC              , h_jetJEC            );
      Handle <vector<float>>  h_jetnHadEnergy     ; evt.getByLabel (l_jetnHadEnergy       , h_jetnHadEnergy     );
      Handle <vector<float>>  h_jetnEMEnergy      ; evt.getByLabel (l_jetnEMEnergy        , h_jetnEMEnergy      );
      Handle <vector<float>>  h_jetHFHadronEnergy ; evt.getByLabel (l_jetHFHadronEnergy   , h_jetHFHadronEnergy );
      Handle <vector<float>>  h_jetcHadEnergy     ; evt.getByLabel (l_jetcHadEnergy       , h_jetcHadEnergy     );
      Handle <vector<float>>  h_jetcEMEnergy      ; evt.getByLabel (l_jetcEMEnergy        , h_jetcEMEnergy      );
      Handle <vector<float>>  h_jetnumDaughters   ; evt.getByLabel (l_jetnumDaughters     , h_jetnumDaughters   );
      Handle <vector<float>>  h_jetcMultip        ; evt.getByLabel (l_jetcMultip          , h_jetcMultip        );
      Handle <vector<float>>  h_jetY              ; evt.getByLabel (l_jetY                , h_jetY              );
      Handle <vector<float>>  h_jetArea           ; evt.getByLabel (l_jetArea             , h_jetArea           );

      double jetPt      = (h_jetPt.product())->at(jet);
      double jetAbsEta  = std::abs((h_jetEta.product())->at(jet)) ; 
      double jetCSVDisc = (h_jetCSV.product())->at(jet); 

      if ( type_ == AK4JET || type_ == BTAGGEDAK4JET ) {
        if (jetPt      > idxjetPtMin_      && 
            jetPt      < idxjetPtMax_      &&
            jetAbsEta  < idxjetAbsEtaMax_  &&
            jetCSVDisc > idxjetCSVDiscMin_ &&
            jetCSVDisc < idxjetCSVDiscMax_ 
           ) return true ;
        else return false ; 
      }
      else if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {

        Handle <vector<float>>  h_jettau1           ; evt.getByLabel (l_jettau1             , h_jettau1        );
        Handle <vector<float>>  h_jettau2           ; evt.getByLabel (l_jettau2             , h_jettau2        );
        Handle <vector<float>>  h_jettau3           ; evt.getByLabel (l_jettau3             , h_jettau3        );
        Handle <vector<float>>  h_jetprunedMass     ; evt.getByLabel (l_jetprunedMass       , h_jetprunedMass  );
        Handle <vector<float>>  h_jettrimmedMass    ; evt.getByLabel (l_jettrimmedMass      , h_jettrimmedMass );
        Handle <vector<float>>  h_jetwMass          ; evt.getByLabel (l_jetwMass            , h_jetwMass       );
        Handle <vector<float>>  h_jettopMass        ; evt.getByLabel (l_jettopMass          , h_jettopMass     );
        Handle <vector<float>>  h_jetminMass        ; evt.getByLabel (l_jetminMass          , h_jetminMass     );
        Handle <vector<float>>  h_jetnSubJets       ; evt.getByLabel (l_jetnSubJets         , h_jetnSubJets    );
        Handle <vector<float>>  h_ak8sjPt           ; evt.getByLabel (l_ak8sjPt             , h_ak8sjPt        );
        Handle <vector<float>>  h_ak8sjEta          ; evt.getByLabel (l_ak8sjEta            , h_ak8sjEta       );
        Handle <vector<float>>  h_ak8sjPhi          ; evt.getByLabel (l_ak8sjPhi            , h_ak8sjPhi       );
        Handle <vector<float>>  h_ak8sjMass         ; evt.getByLabel (l_ak8sjMass           , h_ak8sjMass      );
        Handle <vector<float>>  h_ak8sjCSV          ; evt.getByLabel (l_ak8sjCSV            , h_ak8sjCSV       );

        double jettau1         = (h_jettau1.product())->at(jet) ; 
        double jettau2         = (h_jettau2.product())->at(jet) ; 
        double jettau3         = (h_jettau3.product())->at(jet) ; 
        double jetMass         = (h_jetMass.product())->at(jet) ;
        double jetPrunedMass   = (h_jetprunedMass.product())->at(jet) ;
        double jetTrimmedMass  = (h_jettrimmedMass.product())->at(jet) ;
        int    jetnSubJets     = int((h_jetnSubJets.product())->at(jet)) ;

        if ( jetPt          < idxjetPtMin_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails pt = " << jetPt << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetPt          > idxjetPtMax_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails pt = " << jetPt << " > cutmax\n" ; 
          return false ; 
        }  
        if ( jetAbsEta      > idxjetAbsEtaMax_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails eta = " << jetAbsEta << " > cutmax\n" ; 
          return false ; 
        }  
        if ( jetCSVDisc     < idxjetCSVDiscMin_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails csv = " << jetCSVDisc << " < cutmin\n" ; 
          return false ; 
        }  
        if ( jetCSVDisc     > idxjetCSVDiscMax_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails csv = " << jetCSVDisc << " > cutmax\n" ; 
          return false ; 
        }  
        if ( jettau2/jettau1< idxjettau2Bytau1Min_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau2/jettau1 = " << jettau2/jettau1 << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jettau2/jettau1> idxjettau2Bytau1Max_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau2/jettau1 = " << jettau2/jettau1 << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jettau3/jettau2< idxjettau3Bytau2Min_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau3/jettau2 = " << jettau3/jettau2 << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jettau3/jettau2> idxjettau3Bytau2Max_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau3/jettau2 = " << jettau3/jettau2 << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jetMass        < idxjetMassMin_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetMass = " << jetMass << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetMass        > idxjetMassMax_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetMass = " << jetMass << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jetPrunedMass  < idxjetPrunedMassMin_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetPrunedMass = " << jetPrunedMass << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetPrunedMass  > idxjetPrunedMassMax_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetPrunedMass = " << jetPrunedMass << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jetTrimmedMass < idxjetTrimmedMassMin_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetTrimmedMass = " << jetTrimmedMass << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetTrimmedMass > idxjetTrimmedMassMax_ ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetTrimmedMass = " << jetTrimmedMass << " > cutmax\n" ; 
          return false ; 
        }   
        if (type_ == HTAGGEDAK8JET) {
          LogDebug("JetSelector") << " jetnSubJets = " << jetnSubJets << " min = " << idxjetnSubJetsMin_  << " max = " << idxjetnSubJetsMax_ << endl ; 
          Handle <vector<float>>  h_vjetsjIdx0        ; evt.getByLabel (l_vjetsjIdx0          , h_vjetsjIdx0     );
          Handle <vector<float>>  h_vjetsjIdx1        ; evt.getByLabel (l_vjetsjIdx1          , h_vjetsjIdx1     );
          int    vjetsjIdx0      = int((h_vjetsjIdx0.product())->at(jet)) ;
          int    vjetsjIdx1      = int((h_vjetsjIdx1.product())->at(jet)) ;
          double vjetssj0Pt      = (h_ak8sjPt.product())->at(vjetsjIdx0) ; 
          double vjetssj1Pt      = (h_ak8sjPt.product())->at(vjetsjIdx1) ; 
          double vjetssj0Eta     = (h_ak8sjEta.product())->at(vjetsjIdx0) ; 
          double vjetssj1Eta     = (h_ak8sjEta.product())->at(vjetsjIdx1) ; 
          double vjetssj0Phi     = (h_ak8sjPhi.product())->at(vjetsjIdx0) ; 
          double vjetssj1Phi     = (h_ak8sjPhi.product())->at(vjetsjIdx1) ; 
          double vjetssj0Mass    = (h_ak8sjMass.product())->at(vjetsjIdx0) ; 
          double vjetssj1Mass    = (h_ak8sjMass.product())->at(vjetsjIdx1) ; 
          double vjetssj0CSV     = (h_ak8sjCSV.product())->at(vjetsjIdx0) ; 
          double vjetssj1CSV     = (h_ak8sjCSV.product())->at(vjetsjIdx1) ; 
          TLorentzVector p4sj0, p4sj1; 
          p4sj0.SetPtEtaPhiM(vjetssj0Pt, vjetssj0Eta, vjetssj0Phi, vjetssj0Mass) ; 
          p4sj1.SetPtEtaPhiM(vjetssj1Pt, vjetssj1Eta, vjetssj1Phi, vjetssj1Mass) ; 
          if (jetnSubJets >= idxjetnSubJetsMin_
              && jetnSubJets <= idxjetnSubJetsMax_
              && p4sj0.Mag() > idxsjMassMin_ 
              && p4sj1.Mag() > idxsjMassMin_
              && vjetssj0CSV > idxsjCSVMin_
              && vjetssj1CSV > idxsjCSVMin_
              && vjetssj0CSV < idxsjCSVMax_
              && vjetssj1CSV < idxsjCSVMax_
              ) return true ; 
          else return false ; 
        }
        else if (type_ == CMSTOPTAGGEDAK8JET) {
          return true; 
          Handle <vector<float>>  h_tjetsjIdx0        ; evt.getByLabel (l_tjetsjIdx0          , h_tjetsjIdx0     );
          Handle <vector<float>>  h_tjetsjIdx1        ; evt.getByLabel (l_tjetsjIdx1          , h_tjetsjIdx1     );
          Handle <vector<float>>  h_tjetsjIdx2        ; evt.getByLabel (l_tjetsjIdx2          , h_tjetsjIdx2     );
          Handle <vector<float>>  h_tjetsjIdx3        ; evt.getByLabel (l_tjetsjIdx3          , h_tjetsjIdx3     );
          //int    tjetsjIdx0      = int((h_tjetsjIdx0.product())->at(jet)) ;
          //int    tjetsjIdx1      = int((h_tjetsjIdx1.product())->at(jet)) ;
          //int    tjetsjIdx2      = int((h_tjetsjIdx2.product())->at(jet)) ;
          //int    tjetsjIdx3      = int((h_tjetsjIdx3.product())->at(jet)) ;
          //double tjetssj0Pt      = (h_ak8sjPt.product())->at(tjetsjIdx0) ; 
          //double tjetssj1Pt      = (h_ak8sjPt.product())->at(tjetsjIdx2) ; 
          //double tjetssj2Pt      = (h_ak8sjPt.product())->at(tjetsjIdx2) ; 
          //double tjetssj3Pt      = (h_ak8sjPt.product())->at(tjetsjIdx3) ; 
          //double tjetssj0Eta     = (h_ak8sjEta.product())->at(tjetsjIdx0) ; 
          //double tjetssj1Eta     = (h_ak8sjEta.product())->at(tjetsjIdx1) ; 
          //double tjetssj2Eta     = (h_ak8sjEta.product())->at(tjetsjIdx2) ; 
          //double tjetssj3Eta     = (h_ak8sjEta.product())->at(tjetsjIdx3) ; 
          //double tjetssj0Phi     = (h_ak8sjPhi.product())->at(tjetsjIdx0) ; 
          //double tjetssj1Phi     = (h_ak8sjPhi.product())->at(tjetsjIdx1) ; 
          //double tjetssj2Phi     = (h_ak8sjPhi.product())->at(tjetsjIdx2) ; 
          //double tjetssj3Phi     = (h_ak8sjPhi.product())->at(tjetsjIdx3) ; 
          //double tjetssj0Mass    = (h_ak8sjMass.product())->at(tjetsjIdx0) ; 
          //double tjetssj1Mass    = (h_ak8sjMass.product())->at(tjetsjIdx1) ; 
          //double tjetssj2Mass    = (h_ak8sjMass.product())->at(tjetsjIdx2) ; 
          //double tjetssj3Mass    = (h_ak8sjMass.product())->at(tjetsjIdx3) ; 
          //double jetWMass        = (h_jetwMass.product())->at(jet) ;
          double jetTopMass      = (h_jettopMass.product())->at(jet) ;
          double jetMinMass      = (h_jetnSubJets.product())->at(jet) ;
          if (jetnSubJets >= idxjetnSubJetsMin_
              && jetnSubJets <= idxjetnSubJetsMax_ 
              && jetTopMass > idxjetTopMassMin_ 
              && jetTopMass < idxjetTopMassMax_
              && jetMinMass > idxjetMinMassMin_ 
              && jetMinMass < idxjetMinMassMax_
              ) return true ; 
          else return false ; 
        }
        else {
          return true ;
        }

      }
      else {
        edm::LogError("JetSelector::JetSelector") << " >>>> WrongJetType: " << type_<< " Check jet type !!!" ; 
        return false ; 
      }

    }

  private:

    JETTYPES_t type_ ; 

    JetID* jetID_ ; 
    pat::strbitset retjetid_ ; 
    JetID::Quality_t quality_; 
    edm::ParameterSet JetIDParams_ ; 
    edm::ParameterSet JetSubstrParams_ ; 
    edm::ParameterSet SubjetParams_ ; 

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
    double idxsjCSVMax_          ; 

    edm::InputTag l_jetPt              ; 
    edm::InputTag l_jetEta             ; 
    edm::InputTag l_jetPhi             ; 
    edm::InputTag l_jetMass            ; 
    edm::InputTag l_jetEnergy          ; 
    edm::InputTag l_jetFlavour         ; 
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
    edm::InputTag l_jetprunedMass      ; 
    edm::InputTag l_jettrimmedMass     ; 
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

};

#endif 
