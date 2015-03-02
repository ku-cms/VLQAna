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

    enum JETTYPES_t { AK4JET, BTAGGEDAK4JET, PRUNEDSUBJET, N_JETTYPES} ; 

    JetSelector () {} 

    JetSelector (edm::ParameterSet const& params) :
      JetIDParams_ (params.getParameter<edm::ParameterSet> ("JetIDParams"))
  {

    std::string jettypeStr = params.getParameter<std::string>("jettype") ;
    if (jettypeStr == "AK4JET") jettype_ = AK4JET; 
    else if (jettypeStr == "BTAGGEDAK4JET") jettype_ = BTAGGEDAK4JET;
    else if (jettypeStr == "PRUNEDSUBJET") jettype_ = PRUNEDSUBJET; 
    else edm::LogError("JetSelector::JetSelector") << " >>>> WrongJetType: " << jettype_<< " Check jet type !!!" ; 

    l_jetAK4Pt              = JetIDParams_.getParameter<edm::InputTag> ("jetAK4PtLabel") ;                   
    l_jetAK4Eta             = JetIDParams_.getParameter<edm::InputTag> ("jetAK4EtaLabel") ;                  
    l_jetAK4Phi             = JetIDParams_.getParameter<edm::InputTag> ("jetAK4PhiLabel") ;                   
    l_jetAK4Mass            = JetIDParams_.getParameter<edm::InputTag> ("jetAK4MassLabel") ;                 
    l_jetAK4Energy          = JetIDParams_.getParameter<edm::InputTag> ("jetAK4EnergyLabel") ;               
    l_jetAK4Flavour         = JetIDParams_.getParameter<edm::InputTag> ("jetAK4FlavourLabel") ;                  
    l_jetAK4CSV             = JetIDParams_.getParameter<edm::InputTag> ("jetAK4CSVLabel") ;              
    l_jetAK4JEC             = JetIDParams_.getParameter<edm::InputTag> ("jetAK4JECLabel") ;           
    l_jetAK4nHadEnergy      = JetIDParams_.getParameter<edm::InputTag> ("jetAK4nHadEnergyLabel") ;          
    l_jetAK4nEMEnergy       = JetIDParams_.getParameter<edm::InputTag> ("jetAK4nEMEnergyLabel") ;         
    l_jetAK4HFHadronEnergy  = JetIDParams_.getParameter<edm::InputTag> ("jetAK4HFHadronEnergyLabel") ;      
    l_jetAK4cHadEnergy      = JetIDParams_.getParameter<edm::InputTag> ("jetAK4cHadEnergyLabel") ;          
    l_jetAK4cEMEnergy       = JetIDParams_.getParameter<edm::InputTag> ("jetAK4cEMEnergyLabel") ;            
    l_jetAK4numDaughters    = JetIDParams_.getParameter<edm::InputTag> ("jetAK4numDaughtersLabel") ;             
    l_jetAK4cMultip         = JetIDParams_.getParameter<edm::InputTag> ("jetAK4cMultipLabel") ;              
    l_jetAK4Y               = JetIDParams_.getParameter<edm::InputTag> ("jetAK4YLabel") ;                      
    l_jetAK4Area            = JetIDParams_.getParameter<edm::InputTag> ("jetAK4AreaLabel") ;                        

    push_back("jetPtMin") ;
    push_back("jetPtMax") ;
    push_back("jetAbsEtaMax") ;
    push_back("jetCSVDiscMin") ;
    push_back("jetCSVDiscMax") ;

    set("jetPtMin"             ,params.getParameter<double>("jetPtMin") ) ;
    set("jetPtMax"             ,params.getParameter<double>("jetPtMax") ) ;
    set("jetAbsEtaMax"         ,params.getParameter<double>("jetAbsEtaMax") ) ;
    if (jettype_ == BTAGGEDAK4JET) {
      set("jetCSVDiscMin"        ,params.getParameter<double>("jetCSVDiscMin") ,true) ;
      set("jetCSVDiscMax"        ,params.getParameter<double>("jetCSVDiscMax") ,true) ;
    }
    else {
      set("jetCSVDiscMin"        ,params.getParameter<double>("jetCSVDiscMin") ,false) ;
      set("jetCSVDiscMax"        ,params.getParameter<double>("jetCSVDiscMax") ,false) ;
    }

    indexjetPtMin_            = index_type(&bits_ ,"jetPtMin") ;
    indexjetPtMax_            = index_type(&bits_ ,"jetPtMax") ;
    indexjetAbsEtaMax_        = index_type(&bits_ ,"jetAbsEtaMax") ;
    indexjetCSVDiscMin_       = index_type(&bits_ ,"jetCSVDiscMin") ;
    indexjetCSVDiscMax_       = index_type(&bits_ ,"jetCSVDiscMax") ;

    retInternal_ = getBitTemplate();   

    if (params.getParameter<bool>("IsJetIDLoose") == true && params.getParameter<bool>("IsJetIDTight") == false) quality_ = JetID::LOOSE ; 
    else if (params.getParameter<bool>("IsJetIDTight") == true && params.getParameter<bool>("IsJetIDLoose") == false) quality_ = JetID::TIGHT ; 
    else edm::LogError("JetSelector::JetSelector") << "Ambiguous JetID: Please select only one (LOOSE or TIGHT) as True!!!" ; 

  }

    bool operator()(int & jet, pat::strbitset & ret ) {
      return true ;  
    }

    bool operator()(int const  & jet, pat::strbitset & ret ) {
      return true ;  
    }

    using Selector<int>::operator();

    //bool operator()(edm::Event& evt, int const & jet, JetCollection& fatjets, pat::strbitset & ret ) {
    //  if ( firstDataCuts(evt, jet, ret ) ) {
    //    return noJetFatJetOverlap (evt, jet, fatjets) ;
    //  }
    //  else return firstDataCuts(evt, jet, ret ) ; 
    //}

    bool operator()(edm::Event& evt, int const & jet, pat::strbitset & ret ) {
      return firstDataCuts(evt, jet, ret ) ; 
    }

    bool firstDataCuts(edm::Event& evt,  const int & jet, pat::strbitset & ret) {

      Handle <vector<float>>  h_jetAK4Pt             ; evt.getByLabel (l_jetAK4Pt               , h_jetAK4Pt             );
      Handle <vector<float>>  h_jetAK4Eta            ; evt.getByLabel (l_jetAK4Eta              , h_jetAK4Eta            );
      Handle <vector<float>>  h_jetAK4Phi            ; evt.getByLabel (l_jetAK4Phi              , h_jetAK4Phi            );
      Handle <vector<float>>  h_jetAK4Mass           ; evt.getByLabel (l_jetAK4Mass             , h_jetAK4Mass           );
      Handle <vector<float>>  h_jetAK4Energy         ; evt.getByLabel (l_jetAK4Energy           , h_jetAK4Energy         );
      Handle <vector<float>>  h_jetAK4Flavour        ; evt.getByLabel (l_jetAK4Flavour          , h_jetAK4Flavour        );
      Handle <vector<float>>  h_jetAK4CSV            ; evt.getByLabel (l_jetAK4CSV              , h_jetAK4CSV            );
      Handle <vector<float>>  h_jetAK4JEC            ; evt.getByLabel (l_jetAK4JEC              , h_jetAK4JEC            );
      Handle <vector<float>>  h_jetAK4nHadEnergy     ; evt.getByLabel (l_jetAK4nHadEnergy       , h_jetAK4nHadEnergy     );
      Handle <vector<float>>  h_jetAK4nEMEnergy      ; evt.getByLabel (l_jetAK4nEMEnergy        , h_jetAK4nEMEnergy      );
      Handle <vector<float>>  h_jetAK4HFHadronEnergy ; evt.getByLabel (l_jetAK4HFHadronEnergy   , h_jetAK4HFHadronEnergy );
      Handle <vector<float>>  h_jetAK4cHadEnergy     ; evt.getByLabel (l_jetAK4cHadEnergy       , h_jetAK4cHadEnergy     );
      Handle <vector<float>>  h_jetAK4cEMEnergy      ; evt.getByLabel (l_jetAK4cEMEnergy        , h_jetAK4cEMEnergy      );
      Handle <vector<float>>  h_jetAK4numDaughters   ; evt.getByLabel (l_jetAK4numDaughters     , h_jetAK4numDaughters   );
      Handle <vector<float>>  h_jetAK4cMultip        ; evt.getByLabel (l_jetAK4cMultip          , h_jetAK4cMultip        );
      Handle <vector<float>>  h_jetAK4Y              ; evt.getByLabel (l_jetAK4Y                , h_jetAK4Y              );
      Handle <vector<float>>  h_jetAK4Area           ; evt.getByLabel (l_jetAK4Area             , h_jetAK4Area           );
      JetID jetID(JetIDParams_) ; 
      ret.set(false);
      bool isJetID(false) ; 
      pat::strbitset retjetid = jetID.getBitTemplate() ;
      retjetid.set(false) ;
      if (jetID(evt, jet,retjetid) != 0) isJetID = true ;

      double jetPt         = (h_jetAK4Pt.product())->at(jet);
      double jetAbsEta     = std::abs((h_jetAK4Eta.product())->at(jet)) ; 
      double jetCSVDisc    = (h_jetAK4CSV.product())->at(jet); 

      if (isJetID == false) return false ; 
      else ret.set(true) ; 

      //if ( jetPt <  cut(indexjetPtMin_, double()) && 
      //      jetAbsEta < cut(indexjetAbsEtaMax_, double()) && 
      //      jetCSVDisc >  cut(indexjetCSVDiscMin_, double()) ) 
      //    cout << " jet with pt = " << (h_jetAK4Pt.product())->at(jet) << " eta = " << jetAbsEta << " csv disc = " << jetCSVDisc << " fails selection\n";

      if ( ignoreCut(indexjetPtMin_)        || jetPt > cut(indexjetPtMin_, double() ) ) passCut( ret ,indexjetPtMin_) ; 
      if ( ignoreCut(indexjetPtMax_)        || jetPt < cut(indexjetPtMax_, double() ) ) passCut( ret ,indexjetPtMax_) ; 
      if ( ignoreCut(indexjetAbsEtaMax_)    || jetAbsEta < cut(indexjetAbsEtaMax_, double() ) ) passCut( ret ,indexjetAbsEtaMax_) ; 

      if ( ignoreCut(indexjetCSVDiscMin_) || jetCSVDisc >  cut(indexjetCSVDiscMin_, double() ) ) passCut( ret ,indexjetCSVDiscMin_) ;
      if ( ignoreCut(indexjetCSVDiscMax_) || jetCSVDisc <= cut(indexjetCSVDiscMax_, double() ) ) passCut( ret ,indexjetCSVDiscMax_) ;

      setIgnored( ret ) ; 
      return (bool)ret ; 
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

    JETTYPES_t jettype_ ; 

    JetID* jetID_ ; 
    pat::strbitset retjetid_ ; 
    JetID::Quality_t quality_; 
    edm::ParameterSet JetIDParams_ ; 

    index_type indexjetPtMin_ ;
    index_type indexjetPtMax_ ;
    index_type indexjetAbsEtaMax_ ;
    index_type indexjetCSVDiscMin_; 
    index_type indexjetCSVDiscMax_; 

    edm::InputTag l_jetAK4Pt              ; 
    edm::InputTag l_jetAK4Eta             ; 
    edm::InputTag l_jetAK4Phi             ; 
    edm::InputTag l_jetAK4Mass            ; 
    edm::InputTag l_jetAK4Energy          ; 
    edm::InputTag l_jetAK4Flavour         ; 
    edm::InputTag l_jetAK4CSV             ; 
    edm::InputTag l_jetAK4JEC             ; 
    edm::InputTag l_jetAK4nHadEnergy      ;
    edm::InputTag l_jetAK4nEMEnergy       ;
    edm::InputTag l_jetAK4HFHadronEnergy  ;
    edm::InputTag l_jetAK4cHadEnergy      ;
    edm::InputTag l_jetAK4cEMEnergy       ;
    edm::InputTag l_jetAK4numDaughters    ;
    edm::InputTag l_jetAK4cMultip         ;
    edm::InputTag l_jetAK4Y               ;
    edm::InputTag l_jetAK4Area            ; 
};

#endif 
