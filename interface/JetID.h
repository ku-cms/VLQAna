#ifndef JETID_H
#define JETID_H

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "Analysis/VLQAna/interface/Jet.h"
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
      l_jetAK4Pt              (params.getParameter<edm::InputTag> ("jetAK4PtLabel")),                   
      l_jetAK4Eta             (params.getParameter<edm::InputTag> ("jetAK4EtaLabel")),                  
      l_jetAK4Phi             (params.getParameter<edm::InputTag> ("jetAK4PhiLabel")),                   
      l_jetAK4Mass            (params.getParameter<edm::InputTag> ("jetAK4MassLabel")),                 
      l_jetAK4Energy          (params.getParameter<edm::InputTag> ("jetAK4EnergyLabel")),               
      l_jetAK4Flavour         (params.getParameter<edm::InputTag> ("jetAK4FlavourLabel")),                  
      l_jetAK4CSV             (params.getParameter<edm::InputTag> ("jetAK4CSVLabel")),              
      l_jetAK4JEC             (params.getParameter<edm::InputTag> ("jetAK4JECLabel")),           
      l_jetAK4nHadEnergy      (params.getParameter<edm::InputTag> ("jetAK4nHadEnergyLabel")),          
      l_jetAK4nEMEnergy       (params.getParameter<edm::InputTag> ("jetAK4nEMEnergyLabel")),         
      l_jetAK4HFHadronEnergy  (params.getParameter<edm::InputTag> ("jetAK4HFHadronEnergyLabel")),      
      l_jetAK4cHadEnergy      (params.getParameter<edm::InputTag> ("jetAK4cHadEnergyLabel")),          
      l_jetAK4cEMEnergy       (params.getParameter<edm::InputTag> ("jetAK4cEMEnergyLabel")),            
      l_jetAK4numDaughters    (params.getParameter<edm::InputTag> ("jetAK4numDaughtersLabel")),             
      l_jetAK4cMultip         (params.getParameter<edm::InputTag> ("jetAK4cMultipLabel")),              
      l_jetAK4Y               (params.getParameter<edm::InputTag> ("jetAK4YLabel")),                      
      l_jetAK4Area            (params.getParameter<edm::InputTag> ("jetAK4AreaLabel"))                         
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

      TLorentzVector jetP4Raw ; 
      jetP4Raw.SetPtEtaPhiM( (h_jetAK4Pt.product())->at(ijet), 
          (h_jetAK4Eta.product())->at(ijet), 
          (h_jetAK4Phi.product())->at(ijet), 
          (h_jetAK4Mass.product())->at(ijet) ) ;
      float jec = (h_jetAK4JEC.product())->at(ijet) ; 
      jetP4Raw *= jec ; 
      float jeteta = (h_jetAK4Eta.product())->at(ijet) ; 
      chf = (h_jetAK4cHadEnergy.product())->at(ijet)/ jetP4Raw.E() ; 
      nhf = (h_jetAK4nHadEnergy.product())->at(ijet)/ jetP4Raw.E() ; 
      nef = (h_jetAK4nEMEnergy.product())->at(ijet) / jetP4Raw.E() ; 
      nch = (h_jetAK4cMultip.product())->at(ijet) ; 
      cef = (h_jetAK4cEMEnergy.product())->at(ijet) / jetP4Raw.E() ; 
      nconstituents = (h_jetAK4numDaughters.product())->at(ijet) ; 

      //    if ( patJet != 0 ) {
      //
      //      if ( patJet->isPFJet() ) {
      //	chf = patJet->chargedHadronEnergyFraction();
      //	nhf = ( patJet->neutralHadronEnergy() + patJet->HFHadronEnergy() ) / patJet->energy();
      //	cef = patJet->chargedEmEnergyFraction();
      //	nef = patJet->neutralEmEnergyFraction();
      //	nch = patJet->chargedMultiplicity();
      //	nconstituents = patJet->numberOfDaughters();
      //      } 
      //      // Handle the special case where this is a composed jet for
      //      // subjet analyses
      //      else if ( patJet->isBasicJet() ) {
      //	double e_chf = 0.0;
      //	double e_nhf = 0.0;
      //	double e_cef = 0.0;
      //	double e_nef = 0.0;
      //	nch = 0;
      //	nconstituents = 0;
      //
      //	for ( reco::Jet::const_iterator ibegin = patJet->begin(),
      //		iend = patJet->end(), isub = ibegin;
      //	      isub != iend; ++isub ) {
      //	  reco::PFJet const * pfsub = dynamic_cast<reco::PFJet const *>( &*isub );
      //	  e_chf += pfsub->chargedHadronEnergy();
      //	  e_nhf += (pfsub->neutralHadronEnergy() + pfsub->HFHadronEnergy());
      //	  e_cef += pfsub->chargedEmEnergy();
      //	  e_nef += pfsub->neutralEmEnergy();
      //	  nch += pfsub->chargedMultiplicity();
      //	  nconstituents += pfsub->numberOfDaughters();
      //	}
      //	double e = patJet->energy();
      //	if ( e > 0.000001 ) {
      //	  chf = e_chf / e;
      //	  nhf = e_nhf / e;
      //	  cef = e_cef / e;
      //	  nef = e_nef / e;
      //	} else {
      //	  chf = nhf = cef = nef = 0.0;
      //	}
      //      }
      //    } // end if pat jet
      //    else if ( pfJet != 0 ) {
      //      chf = pfJet->chargedHadronEnergyFraction();
      //      nhf = ( pfJet->neutralHadronEnergy() + pfJet->HFHadronEnergy() ) / pfJet->energy();
      //      cef = pfJet->chargedEmEnergyFraction();
      //      nef = pfJet->neutralEmEnergyFraction();
      //      nch = pfJet->chargedMultiplicity();
      //      nconstituents = pfJet->numberOfDaughters();
      //    } // end if PF jet
      //    // Handle the special case where this is a composed jet for
      //    // subjet analyses
      //    else if ( basicJet != 0 ) {
      //      double e_chf = 0.0;
      //      double e_nhf = 0.0;
      //      double e_cef = 0.0;
      //      double e_nef = 0.0;
      //      nch = 0;
      //      nconstituents = 0;
      //      
      //      for ( reco::Jet::const_iterator ibegin = basicJet->begin(),
      //	      iend = patJet->end(), isub = ibegin;
      //	    isub != iend; ++isub ) {
      //	reco::PFJet const * pfsub = dynamic_cast<reco::PFJet const *>( &*isub );
      //	e_chf += pfsub->chargedHadronEnergy();
      //	e_nhf += (pfsub->neutralHadronEnergy() + pfsub->HFHadronEnergy());
      //	e_cef += pfsub->chargedEmEnergy();
      //	e_nef += pfsub->neutralEmEnergy();
      //	nch += pfsub->chargedMultiplicity();
      //	nconstituents += pfsub->numberOfDaughters();
      //      }
      //      double e = basicJet->energy();
      //      if ( e > 0.000001 ) {
      //	chf = e_chf / e;
      //	nhf = e_nhf / e;
      //	cef = e_cef / e;
      //	nef = e_nef / e;
      //      }
      //    } // end if basic jet


      //    // Cuts for all |eta|:
      //    if ( ignoreCut(indexNConstituents_) || nconstituents > cut(indexNConstituents_, int() ) ) passCut( ret, indexNConstituents_);
      //    if ( ignoreCut(indexNEF_)           || ( nef < cut(indexNEF_, double()) ) ) passCut( ret, indexNEF_);
      //    if ( ignoreCut(indexNHF_)           || ( nhf < cut(indexNHF_, double()) ) ) passCut( ret, indexNHF_);    
      //    // Cuts for |eta| < 2.4:
      //    if ( ignoreCut(indexCEF_)           || ( cef < cut(indexCEF_, double()) || std::abs(jet.eta()) > 2.4 ) ) passCut( ret, indexCEF_);
      //    if ( ignoreCut(indexCHF_)           || ( chf > cut(indexCHF_, double()) || std::abs(jet.eta()) > 2.4 ) ) passCut( ret, indexCHF_);
      //    if ( ignoreCut(indexNCH_)           || ( nch > cut(indexNCH_, int())    || std::abs(jet.eta()) > 2.4 ) ) passCut( ret, indexNCH_);    

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
