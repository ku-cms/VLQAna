#ifndef JETID_H
#define JETID_H

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include <TLorentzVector.h>
#include <TMath.h>

using namespace std; 
using namespace edm; 

class JetID : public Selector<int>  {

  public: // interface

    enum Version_t { FIRSTDATA, N_VERSIONS };
    enum Quality_t { LOOSE, TIGHT, N_QUALITY};

    JetID() {}
    JetID(JetID&) {} 

    JetID( edm::ParameterSet const & params ) : 
      l_jetPt              (params.getParameter<edm::InputTag> ("jetPtLabel")),                   
      l_jetEta             (params.getParameter<edm::InputTag> ("jetEtaLabel")),                  
      l_jetPhi             (params.getParameter<edm::InputTag> ("jetPhiLabel")),                   
      l_jetMass            (params.getParameter<edm::InputTag> ("jetMassLabel")),                 
      l_jetEnergy          (params.getParameter<edm::InputTag> ("jetEnergyLabel")),               
      l_jetPartonFlavour   (params.getParameter<edm::InputTag> ("jetPartonFlavourLabel")),                  
      l_jetHadronFlavour   (params.getParameter<edm::InputTag> ("jetHadronFlavourLabel")),                  
      l_jetCSV             (params.getParameter<edm::InputTag> ("jetCSVLabel")),              
      l_jetJEC             (params.getParameter<edm::InputTag> ("jetJECLabel")),           
      l_jetnHadEnergy      (params.getParameter<edm::InputTag> ("jetnHadEnergyLabel")),          
      l_jetnEMEnergy       (params.getParameter<edm::InputTag> ("jetnEMEnergyLabel")),         
      l_jetHFHadronEnergy  (params.getParameter<edm::InputTag> ("jetHFHadronEnergyLabel")),      
      l_jetcHadEnergy      (params.getParameter<edm::InputTag> ("jetcHadEnergyLabel")),          
      l_jetcEMEnergy       (params.getParameter<edm::InputTag> ("jetcEMEnergyLabel")),            
      l_jetnumDaughters    (params.getParameter<edm::InputTag> ("jetnumDaughtersLabel")),             
      l_jetcMultip         (params.getParameter<edm::InputTag> ("jetcMultipLabel")),              
      l_jetY               (params.getParameter<edm::InputTag> ("jetYLabel")),                      
      l_jetArea            (params.getParameter<edm::InputTag> ("jetAreaLabel"))                         
  {
    std::string versionStr = params.getParameter<std::string>("version");
    std::string qualityStr = params.getParameter<std::string>("quality");

    if ( versionStr == "FIRSTDATA" ) 
      version_ = FIRSTDATA;
    else
      version_ = FIRSTDATA;  /// will have other options eventually, most likely

    if      ( qualityStr == "LOOSE") quality_ = LOOSE;
    else if ( qualityStr == "TIGHT") quality_ = TIGHT;
    else quality_ = LOOSE;

    push_back("CHF" );
    push_back("NHF" );
    push_back("CEF" );
    push_back("NEF" );
    push_back("NCH" );
    push_back("nConstituents");


    // Set some default cuts for LOOSE, TIGHT
    if ( quality_ == LOOSE ) {
      set("CHF", 0.0);
      set("NHF", 0.99);
      set("CEF", 0.99);
      set("NEF", 0.99);
      set("NCH", 0);
      set("nConstituents", 1);
    } else if ( quality_ == TIGHT ) {
      set("CHF", 0.0);
      set("NHF", 0.9);
      set("CEF", 0.99);
      set("NEF", 0.9);
      set("NCH", 0);
      set("nConstituents", 1);      
    }


    // Now check the configuration to see if the user changed anything
    if ( params.exists("CHF") ) set("CHF", params.getParameter<double>("CHF") );
    if ( params.exists("NHF") ) set("NHF", params.getParameter<double>("NHF") );
    if ( params.exists("CEF") ) set("CEF", params.getParameter<double>("CEF") );
    if ( params.exists("NEF") ) set("NEF", params.getParameter<double>("NEF") );
    if ( params.exists("NCH") ) set("NCH", params.getParameter<int>   ("NCH") );
    if ( params.exists("nConstuents") ) set("nConstituents", params.getParameter<int> ("nConstituents") );

    if ( params.exists("cutsToIgnore") )
      setIgnoredCuts( params.getParameter<std::vector<std::string> >("cutsToIgnore") );


    indexNConstituents_ = index_type (&bits_, "nConstituents");
    indexNEF_ = index_type (&bits_, "NEF");
    indexNHF_ = index_type (&bits_, "NHF");
    indexCEF_ = index_type (&bits_, "CEF");
    indexCHF_ = index_type (&bits_, "CHF");
    indexNCH_ = index_type (&bits_, "NCH");

    retInternal_ = getBitTemplate();

  }


    JetID( Version_t version, Quality_t quality) :
      version_(version), 
      quality_(quality)
  { 

    push_back("CHF" );
    push_back("NHF" );
    push_back("CEF" );
    push_back("NEF" );
    push_back("NCH" );
    push_back("nConstituents");


    // Set some default cuts for LOOSE, TIGHT
    if ( quality_ == LOOSE ) {
      set("CHF", 0.0);
      set("NHF", 0.99);
      set("CEF", 0.99);
      set("NEF", 0.99);
      set("NCH", 0);
      set("nConstituents", 1);
    } else if ( quality_ == TIGHT ) {
      set("CHF", 0.0);
      set("NHF", 0.9);
      set("CEF", 0.99);
      set("NEF", 0.9);
      set("NCH", 0);
      set("nConstituents", 1);      
    }


    indexNConstituents_ = index_type (&bits_, "nConstituents");
    indexNEF_ = index_type (&bits_, "NEF");
    indexNHF_ = index_type (&bits_, "NHF");
    indexCEF_ = index_type (&bits_, "CEF");
    indexCHF_ = index_type (&bits_, "CHF");
    indexNCH_ = index_type (&bits_, "NCH");

    retInternal_ = getBitTemplate();   
  }


    // 
    // Accessor from PAT jets
    // 
    bool operator()( int & jet, pat::strbitset & ret ) {
      return true ; 
    }

    // 
    // Accessor from *CORRECTED* 4-vector, EMF, and Jet ID. 
    // This can be used with reco quantities. 
    // 
    bool operator()( int const & jet, pat::strbitset & ret ) {
      return true ; 
    }

    using Selector<int>::operator();

    bool operator()( edm::Event& evt, const int & jet, pat::strbitset & ret ) {
      return firstDataCuts( evt, jet, ret );
    }

    // 
    // cuts based on craft 08 analysis. 
    // 
    bool firstDataCuts(edm::Event& evt, const int & ijet, pat::strbitset & ret) { 

      ret.set(false);

      // cache some variables
      double chf = 0.0;
      double nhf = 0.0;
      double cef = 0.0;
      double nef = 0.0;
      int    nch = 0;
      int    nconstituents = 0;

      Handle <vector<float>>  h_jetPt             ; evt.getByLabel (l_jetPt               , h_jetPt             );
      Handle <vector<float>>  h_jetEta            ; evt.getByLabel (l_jetEta              , h_jetEta            );
      Handle <vector<float>>  h_jetPhi            ; evt.getByLabel (l_jetPhi              , h_jetPhi            );
      Handle <vector<float>>  h_jetMass           ; evt.getByLabel (l_jetMass             , h_jetMass           );
      Handle <vector<float>>  h_jetEnergy         ; evt.getByLabel (l_jetEnergy           , h_jetEnergy         );
      Handle <vector<float>>  h_jetPartonFlavour  ; evt.getByLabel (l_jetPartonFlavour    , h_jetPartonFlavour  );
      Handle <vector<float>>  h_jetHadronFlavour  ; evt.getByLabel (l_jetHadronFlavour    , h_jetHadronFlavour  );
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

      TLorentzVector jetP4Raw ; 
      jetP4Raw.SetPtEtaPhiM( (h_jetPt.product())->at(ijet), 
          (h_jetEta.product())->at(ijet), 
          (h_jetPhi.product())->at(ijet), 
          (h_jetMass.product())->at(ijet) ) ;
      float jec = 1; //(h_jetJEC.product())->at(ijet) ; 
      jetP4Raw *= jec ; 
      float jeteta = (h_jetEta.product())->at(ijet) ; 
      chf = (h_jetcHadEnergy.product())->at(ijet)/ jetP4Raw.E() ; 
      nhf = (h_jetnHadEnergy.product())->at(ijet)/ jetP4Raw.E() ; 
      cef = (h_jetcEMEnergy.product())->at(ijet) / jetP4Raw.E() ; 
      nef = (h_jetnEMEnergy.product())->at(ijet) / jetP4Raw.E() ; 
      nch = (h_jetcMultip.product())->at(ijet) ; 
      nconstituents = (h_jetnumDaughters.product())->at(ijet) ; 

      // Cuts for all |eta|:
      if ( ignoreCut(indexNConstituents_) || nconstituents > cut(indexNConstituents_, int() ) ) passCut( ret, indexNConstituents_);
      if ( ignoreCut(indexNEF_)           || ( nef < cut(indexNEF_, double()) ) ) passCut( ret, indexNEF_);
      if ( ignoreCut(indexNHF_)           || ( nhf < cut(indexNHF_, double()) ) ) passCut( ret, indexNHF_);    
      // Cuts for |eta| < 2.4:
      if ( ignoreCut(indexCEF_)           || ( cef < cut(indexCEF_, double()) || std::abs(jeteta) > 2.4 ) ) passCut( ret, indexCEF_);
      if ( ignoreCut(indexCHF_)           || ( chf > cut(indexCHF_, double()) || std::abs(jeteta) > 2.4 ) ) passCut( ret, indexCHF_);
      if ( ignoreCut(indexNCH_)           || ( nch > cut(indexNCH_, int())    || std::abs(jeteta) > 2.4 ) ) passCut( ret, indexNCH_);    

      setIgnored( ret );
      return (bool)ret;
    }

  private: // member variables

    Version_t version_;
    Quality_t quality_;

    index_type indexNConstituents_;
    index_type indexNEF_;
    index_type indexNHF_;
    index_type indexCEF_;
    index_type indexCHF_;
    index_type indexNCH_;

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
};

#endif 
