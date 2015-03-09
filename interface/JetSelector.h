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

class JetSelector : public Selector<int> {
  public:

    enum JETTYPES_t { AK4JET, BTAGGEDAK4JET, AK8JET, BTAGGEDAK8JET, HTAGGEDAK8JET, CMSTOPTAGGEDAK8JET, PRUNEDSUBJET, N_JETTYPES} ; 

    JetSelector () {} 

    JetSelector (edm::ParameterSet const& pars) :
      JetIDParams_ (pars.getParameter<edm::ParameterSet> ("JetIDParams")), 
      JetSubstrParams_ (pars.getParameter<edm::ParameterSet> ("JetSubstrParams")) 
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
        l_jetsubjetIndex0    = JetSubstrParams_.getParameter<edm::InputTag> ("jetsubjetIndex0Label") ; 
        l_jetsubjetIndex1    = JetSubstrParams_.getParameter<edm::InputTag> ("jetsubjetIndex1Label") ; 
        l_jetsubjetIndex2    = JetSubstrParams_.getParameter<edm::InputTag> ("jetsubjetIndex2Label") ; 
        l_jetsubjetIndex3    = JetSubstrParams_.getParameter<edm::InputTag> ("jetsubjetIndex3Label") ; 
      }

      push_back("jetPtMin") ;
      push_back("jetPtMax") ;
      push_back("jetAbsEtaMax") ;
      push_back("jetCSVDiscMin") ;
      push_back("jetCSVDiscMax") ;
      if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
        push_back("jettau2Bytau1Min") ;
        push_back("jettau2Bytau1Max") ;
        push_back("jettau3Bytau2Min") ;
        push_back("jettau3Bytau2Max") ;
        push_back("jetMassMin") ;
        push_back("jetMassMax") ;
        push_back("jetPrunedMassMin") ;
        push_back("jetPrunedMassMax") ;
        push_back("jetTrimmedMassMin") ;
        push_back("jetTrimmedMassMax") ;
        push_back("jetWMassMin") ;
        push_back("jetWMassMax") ;
        push_back("jetTopMassMin") ;
        push_back("jetTopMassMax") ;
        push_back("jetMinMassMin") ;
        push_back("jetMinMassMax") ;
        push_back("jetnSubJetsMin") ;
        push_back("jetnSubJetsMax") ;
      }

      set("jetPtMin"         ,pars.getParameter<double>("jetPtMin") ) ;
      set("jetPtMax"         ,pars.getParameter<double>("jetPtMax") ) ;
      set("jetAbsEtaMax"     ,pars.getParameter<double>("jetAbsEtaMax") ) ;
      set("jetCSVDiscMin"    ,pars.getParameter<double>("jetCSVDiscMin") ,(type_ == BTAGGEDAK4JET)) ;
      set("jetCSVDiscMax"    ,pars.getParameter<double>("jetCSVDiscMax") ,(type_ == BTAGGEDAK4JET)) ;
      if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
        set("jettau2Bytau1Min" ,pars.getParameter<double>("jettau2Bytau1Min"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jettau2Bytau1Max" ,pars.getParameter<double>("jettau2Bytau1Max"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jettau3Bytau2Min" ,pars.getParameter<double>("jettau3Bytau2Min"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jettau3Bytau2Max" ,pars.getParameter<double>("jettau3Bytau2Max"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jetMassMin"       ,pars.getParameter<double>("jetMassMin"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jetMassMax"       ,pars.getParameter<double>("jetMassMax"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jetPrunedMassMin" ,pars.getParameter<double>("jetPrunedMassMin"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jetPrunedMassMax" ,pars.getParameter<double>("jetPrunedMassMax"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jetTrimmedMassMin",pars.getParameter<double>("jetTrimmedMassMin"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetTrimmedMassMax",pars.getParameter<double>("jetTrimmedMassMax"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetWMassMin"      ,pars.getParameter<double>("jetWMassMin"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetWMassMax"      ,pars.getParameter<double>("jetWMassMax"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetTopMassMin"    ,pars.getParameter<double>("jetTopMassMin"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetTopMassMax"    ,pars.getParameter<double>("jetTopMassMax"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetMinMassMin"    ,pars.getParameter<double>("jetMinMassMin"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetMinMassMax"    ,pars.getParameter<double>("jetMinMassMax"), (type_ == CMSTOPTAGGEDAK8JET)) ;
        set("jetnSubJetsMin"   ,pars.getParameter<double>("jetnSubJetsMin"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
        set("jetnSubJetsMax"   ,pars.getParameter<double>("jetnSubJetsMax"), (type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET)) ;
      }

      idxjetPtMin_          = index_type(&bits_ ,"jetPtMin") ;
      idxjetPtMax_          = index_type(&bits_ ,"jetPtMax") ;
      idxjetAbsEtaMax_      = index_type(&bits_ ,"jetAbsEtaMax") ;
      idxjetCSVDiscMin_     = index_type(&bits_ ,"jetCSVDiscMin") ;
      idxjetCSVDiscMax_     = index_type(&bits_ ,"jetCSVDiscMax") ;
      if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
        idxjettau2Bytau1Min_  = index_type(&bits_ ,"jettau2Bytau1Min") ;
        idxjettau2Bytau1Max_  = index_type(&bits_ ,"jettau2Bytau1Max") ;
        idxjettau3Bytau2Min_  = index_type(&bits_ ,"jettau3Bytau2Min") ;
        idxjettau3Bytau2Max_  = index_type(&bits_ ,"jettau3Bytau2Max") ;
        idxjetMassMin_        = index_type(&bits_ ,"jetMassMin") ;
        idxjetMassMax_        = index_type(&bits_ ,"jetMassMax") ;
        idxjetPrunedMassMin_  = index_type(&bits_ ,"jetPrunedMassMin") ;
        idxjetPrunedMassMax_  = index_type(&bits_ ,"jetPrunedMassMax") ;
        idxjetTrimmedMassMin_ = index_type(&bits_ ,"jetTrimmedMassMin") ;
        idxjetTrimmedMassMax_ = index_type(&bits_ ,"jetTrimmedMassMax") ;
        idxjetWMassMin_       = index_type(&bits_ ,"jetWMassMin") ;
        idxjetWMassMax_       = index_type(&bits_ ,"jetWMassMax") ;
        idxjetTopMassMin_     = index_type(&bits_ ,"jetTopMassMin") ;
        idxjetTopMassMax_     = index_type(&bits_ ,"jetTopMassMax") ;
        idxjetMinMassMin_     = index_type(&bits_ ,"jetMinMassMin") ;
        idxjetMinMassMax_     = index_type(&bits_ ,"jetMinMassMax") ;
        idxjetnSubJetsMin_    = index_type(&bits_ ,"jetnSubJetsMin") ;
        idxjetnSubJetsMax_    = index_type(&bits_ ,"jetnSubJetsMax") ;
      }

      retInternal_ = getBitTemplate();   

      if (pars.getParameter<bool>("IsJetIDLoose") == true && pars.getParameter<bool>("IsJetIDTight") == false) quality_ = JetID::LOOSE ; 
      else if (pars.getParameter<bool>("IsJetIDTight") == true && pars.getParameter<bool>("IsJetIDLoose") == false) quality_ = JetID::TIGHT ; 
      else edm::LogError("JetSelector::JetSelector") << "Ambiguous JetID: Please select only one (LOOSE or TIGHT) as True!!!" ; 

    }

    bool operator()(int & jet, pat::strbitset & ret ) {
      return true ;  
    }

    bool operator()(int const  & jet, pat::strbitset & ret ) {
      return true ;  
    }

    using Selector<int>::operator();

    bool operator()(edm::Event& evt, int const & jet, pat::strbitset & ret ) {

      JetID jetID(JetIDParams_) ; 
      pat::strbitset retjetid = jetID.getBitTemplate() ;
      retjetid.set(false) ;
      if (jetID(evt, jet, retjetid) == false) return false ; 

      ret.set(false);

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
        if (jetPt      > cut(idxjetPtMin_     , double()) && 
            jetPt      < cut(idxjetPtMax_     , double()) &&
            jetAbsEta  < cut(idxjetAbsEtaMax_ , double()) &&
            jetCSVDisc > cut(idxjetCSVDiscMin_, double()) &&
            jetCSVDisc < cut(idxjetCSVDiscMax_, double()) 
           ) return true ;
        else return false ; 
      }
      else if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {

        Handle <vector<float>>  h_jettau1           ; evt.getByLabel (l_jettau1             , h_jettau1           );
        Handle <vector<float>>  h_jettau2           ; evt.getByLabel (l_jettau2             , h_jettau2           );
        Handle <vector<float>>  h_jettau3           ; evt.getByLabel (l_jettau3             , h_jettau3           );
        Handle <vector<float>>  h_jetprunedMass     ; evt.getByLabel (l_jetprunedMass       , h_jetprunedMass     );
        Handle <vector<float>>  h_jettrimmedMass    ; evt.getByLabel (l_jettrimmedMass      , h_jettrimmedMass    );
        Handle <vector<float>>  h_jetwMass          ; evt.getByLabel (l_jetwMass            , h_jetwMass          );
        Handle <vector<float>>  h_jettopMass        ; evt.getByLabel (l_jettopMass          , h_jettopMass        );
        Handle <vector<float>>  h_jetminMass        ; evt.getByLabel (l_jetminMass          , h_jetminMass        );
        Handle <vector<float>>  h_jetnSubJets       ; evt.getByLabel (l_jetnSubJets         , h_jetnSubJets       );
        Handle <vector<float>>  h_jetsubjetIndex0   ; evt.getByLabel (l_jetsubjetIndex0     , h_jetsubjetIndex0   );
        Handle <vector<float>>  h_jetsubjetIndex1   ; evt.getByLabel (l_jetsubjetIndex1     , h_jetsubjetIndex1   );
        Handle <vector<float>>  h_jetsubjetIndex2   ; evt.getByLabel (l_jetsubjetIndex2     , h_jetsubjetIndex2   );
        Handle <vector<float>>  h_jetsubjetIndex3   ; evt.getByLabel (l_jetsubjetIndex3     , h_jetsubjetIndex3   );

        double jettau1         = (h_jettau1.product())->at(jet) ; 
        double jettau2         = (h_jettau2.product())->at(jet) ; 
        double jettau3         = (h_jettau3.product())->at(jet) ; 
        double jetMass         = (h_jetMass.product())->at(jet) ;
        double jetPrunedMass   = (h_jetprunedMass.product())->at(jet) ;
        double jetTrimmedMass  = (h_jettrimmedMass.product())->at(jet) ;
        //double jetWMass        = (h_jetwMass.product())->at(jet) ;
        //double jetTopMass      = (h_jettopMass.product())->at(jet) ;
        //double jetMinMass      = (h_jetnSubJets.product())->at(jet) ;
        //int    jetnSubJets     = int((h_jetminMass.product())->at(jet)) ;

        if ( jetPt          < cut(idxjetPtMin_         , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails pt = " << jetPt << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetPt          > cut(idxjetPtMax_         , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails pt = " << jetPt << " > cutmax\n" ; 
          return false ; 
        }  
        if ( jetAbsEta      > cut(idxjetAbsEtaMax_     , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails eta = " << jetAbsEta << " > cutmax\n" ; 
          return false ; 
        }  
        if ( jetCSVDisc     < cut(idxjetCSVDiscMin_    , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails csv = " << jetCSVDisc << " < cutmin\n" ; 
          return false ; 
        }  
        if ( jetCSVDisc     > cut(idxjetCSVDiscMax_    , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails csv = " << jetCSVDisc << " > cutmax\n" ; 
          return false ; 
        }  
        if ( jettau2/jettau1< cut(idxjettau2Bytau1Min_ , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau2/jettau1 = " << jettau2/jettau1 << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jettau2/jettau1> cut(idxjettau2Bytau1Max_ , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau2/jettau1 = " << jettau2/jettau1 << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jettau3/jettau2< cut(idxjettau3Bytau2Min_ , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau3/jettau2 = " << jettau3/jettau2 << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jettau3/jettau2> cut(idxjettau3Bytau2Max_ , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jettau3/jettau2 = " << jettau3/jettau2 << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jetMass        < cut(idxjetMassMin_       , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetMass = " << jetMass << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetMass        > cut(idxjetMassMax_       , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetMass = " << jetMass << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jetPrunedMass  < cut(idxjetPrunedMassMin_ , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetPrunedMass = " << jetPrunedMass << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetPrunedMass  > cut(idxjetPrunedMassMax_ , double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetPrunedMass = " << jetPrunedMass << " > cutmax\n" ; 
          return false ; 
        }   
        if ( jetTrimmedMass < cut(idxjetTrimmedMassMin_, double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetTrimmedMass = " << jetTrimmedMass << " < cutmin\n" ; 
          return false ; 
        }   
        if ( jetTrimmedMass > cut(idxjetTrimmedMassMax_, double() ) ) { 
          LogDebug("JetSelector") << " ak8 jet fails jetTrimmedMass = " << jetTrimmedMass << " > cutmax\n" ; 
          return false ; 
        }   
        //if ( jetWMass       < cut(idxjetWMassMin_      , double() ) ) { 
        //  return false ; 
        //}   
        //if ( jetWMass       > cut(idxjetWMassMax_      , double() ) ) { 
        //  return false ; 
        //}   
        //if ( jetTopMass     < cut(idxjetTopMassMin_    , double() ) ) { 
        //  return false ; 
        //}   
        //if ( jetTopMass     > cut(idxjetTopMassMax_    , double() ) ) { 
        //  return false ; 
        //}   
        //if ( jetMinMass     < cut(idxjetMinMassMin_    , double() ) ) { 
        //  return false ; 
        //}   
        //if ( jetMinMass     > cut(idxjetMinMassMax_    , double() ) ) { 
        //  return false ; 
        //}   
        //if ( jetnSubJets    < cut(idxjetnSubJetsMin_   , int()    ) ) { 
        //  return false ; 
        //}   
        //if ( jetnSubJets    > cut(idxjetnSubJetsMax_   , int()    ) ) { 
        //  return false ; 
        //}  
        else {
          return true ;
        }

      }
      else {
        edm::LogError("JetSelector::JetSelector") << " >>>> WrongJetType: " << type_<< " Check jet type !!!" ; 
        return false ; 
      }

      /*
         if ( ignoreCut(idxjetPtMin_         ) || jetPt          > cut(idxjetPtMin_         , double() ) ) passCut( ret ,idxjetPtMin_         ) ; 
         if ( ignoreCut(idxjetPtMax_         ) || jetPt          < cut(idxjetPtMax_         , double() ) ) passCut( ret ,idxjetPtMax_         ) ; 
         if ( ignoreCut(idxjetAbsEtaMax_     ) || jetAbsEta      < cut(idxjetAbsEtaMax_     , double() ) ) passCut( ret ,idxjetAbsEtaMax_     ) ; 
         if ( ignoreCut(idxjetCSVDiscMin_    ) || jetCSVDisc     > cut(idxjetCSVDiscMin_    , double() ) ) passCut( ret ,idxjetCSVDiscMin_    ) ;
         if ( ignoreCut(idxjetCSVDiscMax_    ) || jetCSVDisc     < cut(idxjetCSVDiscMax_    , double() ) ) passCut( ret ,idxjetCSVDiscMax_    ) ;
         if ( type_ == AK8JET || type_ == BTAGGEDAK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
         Handle <vector<float>>  h_jettau1           ; evt.getByLabel (l_jettau1             , h_jettau1           );
         Handle <vector<float>>  h_jettau2           ; evt.getByLabel (l_jettau2             , h_jettau2           );
         Handle <vector<float>>  h_jettau3           ; evt.getByLabel (l_jettau3             , h_jettau3           );
         Handle <vector<float>>  h_jetprunedMass     ; evt.getByLabel (l_jetprunedMass       , h_jetprunedMass     );
         Handle <vector<float>>  h_jettrimmedMass    ; evt.getByLabel (l_jettrimmedMass      , h_jettrimmedMass    );
         Handle <vector<float>>  h_jetwMass          ; evt.getByLabel (l_jetwMass            , h_jetwMass          );
         Handle <vector<float>>  h_jettopMass        ; evt.getByLabel (l_jettopMass          , h_jettopMass        );
         Handle <vector<float>>  h_jetminMass        ; evt.getByLabel (l_jetminMass          , h_jetminMass        );
         Handle <vector<float>>  h_jetnSubJets       ; evt.getByLabel (l_jetnSubJets         , h_jetnSubJets       );
         Handle <vector<float>>  h_jetsubjetIndex0   ; evt.getByLabel (l_jetsubjetIndex0     , h_jetsubjetIndex0   );
         Handle <vector<float>>  h_jetsubjetIndex1   ; evt.getByLabel (l_jetsubjetIndex1     , h_jetsubjetIndex1   );
         Handle <vector<float>>  h_jetsubjetIndex2   ; evt.getByLabel (l_jetsubjetIndex2     , h_jetsubjetIndex2   );
         Handle <vector<float>>  h_jetsubjetIndex3   ; evt.getByLabel (l_jetsubjetIndex3     , h_jetsubjetIndex3   );

         double jettau1         = (h_jettau1.product())->at(jet) ; 
         double jettau2         = (h_jettau2.product())->at(jet) ; 
         double jettau3         = (h_jettau3.product())->at(jet) ; 
         double jetMass         = (h_jetMass.product())->at(jet) ;
         double jetPrunedMass   = (h_jetprunedMass.product())->at(jet) ;
         double jetTrimmedMass  = (h_jettrimmedMass.product())->at(jet) ;
         double jetWMass        = (h_jetwMass.product())->at(jet) ;
         double jetTopMass      = (h_jettopMass.product())->at(jet) ;
         double jetMinMass      = (h_jetnSubJets.product())->at(jet) ;
         int    jetnSubJets     = int((h_jetminMass.product())->at(jet)) ;

         if ( ignoreCut(idxjettau2Bytau1Min_ ) || jettau2/jettau1< cut(idxjettau2Bytau1Min_ , double() ) ) passCut( ret ,idxjettau2Bytau1Min_ ) ;
         if ( ignoreCut(idxjettau2Bytau1Max_ ) || jettau2/jettau1> cut(idxjettau2Bytau1Max_ , double() ) ) passCut( ret ,idxjettau2Bytau1Max_ ) ;
         if ( ignoreCut(idxjettau3Bytau2Min_ ) || jettau3/jettau2< cut(idxjettau3Bytau2Min_ , double() ) ) passCut( ret ,idxjettau3Bytau2Min_ ) ;
         if ( ignoreCut(idxjettau3Bytau2Max_ ) || jettau3/jettau2> cut(idxjettau3Bytau2Max_ , double() ) ) passCut( ret ,idxjettau3Bytau2Max_ ) ;
         if ( ignoreCut(idxjetMassMin_       ) || jetMass        < cut(idxjetMassMin_       , double() ) ) passCut( ret ,idxjetMassMin_       ) ;
         if ( ignoreCut(idxjetMassMax_       ) || jetMass        > cut(idxjetMassMax_       , double() ) ) passCut( ret ,idxjetMassMax_       ) ;
         if ( ignoreCut(idxjetPrunedMassMin_ ) || jetPrunedMass  < cut(idxjetPrunedMassMin_ , double() ) ) passCut( ret ,idxjetPrunedMassMin_ ) ;
         if ( ignoreCut(idxjetPrunedMassMax_ ) || jetPrunedMass  > cut(idxjetPrunedMassMax_ , double() ) ) passCut( ret ,idxjetPrunedMassMax_ ) ;
         if ( ignoreCut(idxjetTrimmedMassMin_) || jetTrimmedMass < cut(idxjetTrimmedMassMin_, double() ) ) passCut( ret ,idxjetTrimmedMassMin_) ;
         if ( ignoreCut(idxjetTrimmedMassMax_) || jetTrimmedMass > cut(idxjetTrimmedMassMax_, double() ) ) passCut( ret ,idxjetTrimmedMassMax_) ;
         if ( ignoreCut(idxjetWMassMin_      ) || jetWMass       < cut(idxjetWMassMin_      , double() ) ) passCut( ret ,idxjetWMassMin_      ) ;
         if ( ignoreCut(idxjetWMassMax_      ) || jetWMass       > cut(idxjetWMassMax_      , double() ) ) passCut( ret ,idxjetWMassMax_      ) ;
         if ( ignoreCut(idxjetTopMassMin_    ) || jetTopMass     < cut(idxjetTopMassMin_    , double() ) ) passCut( ret ,idxjetTopMassMin_    ) ;
         if ( ignoreCut(idxjetTopMassMax_    ) || jetTopMass     > cut(idxjetTopMassMax_    , double() ) ) passCut( ret ,idxjetTopMassMax_    ) ;
         if ( ignoreCut(idxjetMinMassMin_    ) || jetMinMass     < cut(idxjetMinMassMin_    , double() ) ) passCut( ret ,idxjetMinMassMin_    ) ;
         if ( ignoreCut(idxjetMinMassMax_    ) || jetMinMass     > cut(idxjetMinMassMax_    , double() ) ) passCut( ret ,idxjetMinMassMax_    ) ;
         if ( ignoreCut(idxjetnSubJetsMin_   ) || jetnSubJets    < cut(idxjetnSubJetsMin_   , int()    ) ) passCut( ret ,idxjetnSubJetsMin_   ) ;
         if ( ignoreCut(idxjetnSubJetsMax_   ) || jetnSubJets    > cut(idxjetnSubJetsMax_   , int()    ) ) passCut( ret ,idxjetnSubJetsMax_   ) ;
         }

         if ( type_ != HTAGGEDAK8JET ) {
         setIgnored( ret ) ; 
         return (bool)ret ; 
         }

      //int jetsubjetIndex0 = int((h_jetsubjetIndex0.product())->at(jet)) ; 
      //int jetsubjetIndex1 = int((h_jetsubjetIndex1.product())->at(jet)) ; 
      //int jetsubjetIndex2 = int((h_jetsubjetIndex2.product())->at(jet)) ; 
      //int jetsubjetIndex3 = int((h_jetsubjetIndex3.product())->at(jet)) ; 

      setIgnored( ret ) ; 
      return (bool)ret ; 
      */

    }

  private:

    //bool noJetFatJetOverlap (JetInfoBranches& jetInfo, int jet, JetCollection& fatjets) { 
    //  bool noJetOverlap(true) ; 
    //  TLorentzVector jet_p4;
    //  jet_p4.SetPtEtaPhiM(jetInfo.Pt[jet], jetInfo.Eta[jet], jetInfo.Phi[jet], jetInfo.Mass[jet]); 
    //  for (JetCollection::const_iterator ifatjet = fatjets.begin(); ifatjet != fatjets.end(); ++ifatjet) {
    //    TLorentzVector fatjet_p4 ; 
    //    fatjet_p4.SetPtEtaPhiM(ifatjet->Pt(), ifatjet->Eta(), ifatjet->Phi(), ifatjet->Mass());  
    //    if (jet_p4.DeltaR(fatjet_p4) < 1.2) noJetOverlap = false ; 
    //    break ; 
    //  }
    //  return noJetOverlap ; 
    //}

    JETTYPES_t type_ ; 

    JetID* jetID_ ; 
    pat::strbitset retjetid_ ; 
    JetID::Quality_t quality_; 
    edm::ParameterSet JetIDParams_ ; 
    edm::ParameterSet JetSubstrParams_ ; 

    index_type idxjetPtMin_          ;
    index_type idxjetPtMax_          ;
    index_type idxjetAbsEtaMax_      ;
    index_type idxjetCSVDiscMin_     ; 
    index_type idxjetCSVDiscMax_     ; 
    index_type idxjettau2Bytau1Min_        ; 
    index_type idxjettau2Bytau1Max_        ; 
    index_type idxjettau3Bytau2Min_        ; 
    index_type idxjettau3Bytau2Max_        ; 
    index_type idxjetMassMin_        ; 
    index_type idxjetMassMax_        ; 
    index_type idxjetPrunedMassMin_  ; 
    index_type idxjetPrunedMassMax_  ; 
    index_type idxjetTrimmedMassMin_ ; 
    index_type idxjetTrimmedMassMax_ ; 
    index_type idxjetWMassMin_       ; 
    index_type idxjetWMassMax_       ; 
    index_type idxjetTopMassMin_     ; 
    index_type idxjetTopMassMax_     ; 
    index_type idxjetMinMassMin_     ; 
    index_type idxjetMinMassMax_     ; 
    index_type idxjetnSubJetsMin_    ; 
    index_type idxjetnSubJetsMax_    ; 

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
    edm::InputTag l_jetsubjetIndex0    ; 
    edm::InputTag l_jetsubjetIndex1    ; 
    edm::InputTag l_jetsubjetIndex2    ; 
    edm::InputTag l_jetsubjetIndex3    ; 

};

#endif 
