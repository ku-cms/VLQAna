#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/ApplyJER.h"
#include "Analysis/VLQAna/interface/Utilities.h"

#include <TRandom.h>

#define DEBUG false

using namespace std;
using namespace edm ; 

JetMaker::JetMaker () {} 

JetMaker::~JetMaker () {} 

JetMaker::JetMaker (edm::ParameterSet const& iConfig) :
  JetIDParams_              (iConfig.getParameter<edm::ParameterSet>       ("JetIDParams")), 
  JetSubstrParams_          (iConfig.getParameter<edm::ParameterSet>       ("JetSubstrParams")), 
  SubjetParams_             (iConfig.getParameter<edm::ParameterSet>       ("SubjetParams")), 
  scaleJetP4_               (iConfig.getParameter<bool>                    ("scaleJetP4")), 
  scaledJetMass_            (iConfig.getParameter<double>                  ("scaledJetMass")), 
  jecShift_                 (iConfig.getParameter<double>                  ("jecShift")), 
  jerShift_                 (iConfig.getParameter<int>                     ("jerShift")), 
  newJECPayloadNames_       (iConfig.getParameter<std::vector<std::string>>("newJECPayloadNames")),
  jecUncPayloadName_        (iConfig.getParameter<std::string>             ("jecUncPayloadName")),
  jecAK8GroomedPayloadNames_(iConfig.getParameter<std::vector<std::string>>("jecAK8GroomedPayloadNames")), 
  doGroomedMassCorr_        (jecAK8GroomedPayloadNames_.size()>0 ? true : false)  
{

  std::string jettypeStr = iConfig.getParameter<std::string>("jettype") ;
  if      (jettypeStr == "AK4JET")             type_ = AK4JET; 
  else if (jettypeStr == "AK8JET")             type_ = AK8JET;
  else edm::LogError("JetMaker::JetMaker") << " >>>> WrongJetType: " << type_<< " Check jet type !!!" ; 

  l_npv                = JetIDParams_.getParameter<edm::InputTag> ("npvLabel") ;                   
  l_rho                = JetIDParams_.getParameter<edm::InputTag> ("rhoLabel") ;                   
  l_jetPt              = JetIDParams_.getParameter<edm::InputTag> ("jetPtLabel") ;                   
  l_jetEta             = JetIDParams_.getParameter<edm::InputTag> ("jetEtaLabel") ;                  
  l_jetPhi             = JetIDParams_.getParameter<edm::InputTag> ("jetPhiLabel") ;                   
  l_jetMass            = JetIDParams_.getParameter<edm::InputTag> ("jetMassLabel") ;                 
  l_jetEnergy          = JetIDParams_.getParameter<edm::InputTag> ("jetEnergyLabel") ;               
  l_jetPartonFlavour   = JetIDParams_.getParameter<edm::InputTag> ("jetPartonFlavourLabel") ;                  
  l_jetHadronFlavour   = JetIDParams_.getParameter<edm::InputTag> ("jetHadronFlavourLabel") ;                  
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
  l_jetGenJetPt        = JetIDParams_.getParameter<edm::InputTag> ("jetGenJetPtLabel") ;                        
  l_jetGenJetEta       = JetIDParams_.getParameter<edm::InputTag> ("jetGenJetEtaLabel") ;                        
  l_jetGenJetPhi       = JetIDParams_.getParameter<edm::InputTag> ("jetGenJetPhiLabel") ;                        
  if ( type_ == AK8JET) {
    l_jettau1            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau1Label") ;
    l_jettau2            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau2Label") ;
    l_jettau3            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau3Label") ;
    l_jetPrunedMass      = JetSubstrParams_.getParameter<edm::InputTag> ("jetPrunedMassLabel") ;
    l_jetTrimmedMass     = JetSubstrParams_.getParameter<edm::InputTag> ("jetTrimmedMassLabel") ;
    l_jetFilteredMass    = JetSubstrParams_.getParameter<edm::InputTag> ("jetFilteredMassLabel") ;
    l_jetSoftDropMass    = JetSubstrParams_.getParameter<edm::InputTag> ("jetSoftDropMassLabel") ;
    l_vjetsjIdx0         = JetSubstrParams_.getParameter<edm::InputTag> ("vjetsjIdx0Label") ; 
    l_vjetsjIdx1         = JetSubstrParams_.getParameter<edm::InputTag> ("vjetsjIdx1Label") ; 
    l_ak8sjHadFl         = SubjetParams_.getParameter<edm::InputTag> ("jetHadronFlavourLabel") ; 
    l_ak8sjPt            = SubjetParams_.getParameter<edm::InputTag> ("jetPtLabel") ; 
    l_ak8sjEta           = SubjetParams_.getParameter<edm::InputTag> ("jetEtaLabel") ; 
    l_ak8sjPhi           = SubjetParams_.getParameter<edm::InputTag> ("jetEtaLabel") ; 
    l_ak8sjMass          = SubjetParams_.getParameter<edm::InputTag> ("jetMassLabel") ; 
    l_ak8sjCSV           = SubjetParams_.getParameter<edm::InputTag> ("jetCSVLabel") ; 
    l_ak8sjGenJetPt      = JetIDParams_.getParameter<edm::InputTag> ("jetGenJetPtLabel") ;                        
    l_ak8sjGenJetEta     = JetIDParams_.getParameter<edm::InputTag> ("jetGenJetEtaLabel") ;                        
    l_ak8sjGenJetPhi     = JetIDParams_.getParameter<edm::InputTag> ("jetGenJetPhiLabel") ;                        
  }

  idxjetPtMin_ = iConfig.getParameter<double>("jetPtMin")  ;
  idxjetPtMax_ = iConfig.getParameter<double>("jetPtMax")  ;
  idxjetAbsEtaMax_ = iConfig.getParameter<double>("jetAbsEtaMax")  ;
  idxjetCSVDiscMin_ = iConfig.getParameter<double>("jetCSVDiscMin")  ;
  idxjetCSVDiscMax_ = iConfig.getParameter<double>("jetCSVDiscMax")  ;
  if ( type_ == AK8JET ) {
    idxjettau2Bytau1Min_  = iConfig.getParameter<double>("jettau2Bytau1Min")  ;
    idxjettau2Bytau1Max_  = iConfig.getParameter<double>("jettau2Bytau1Max")  ;
    idxjettau3Bytau2Min_  = iConfig.getParameter<double>("jettau3Bytau2Min")  ;
    idxjettau3Bytau2Max_  = iConfig.getParameter<double>("jettau3Bytau2Max")  ;
    idxjetMassMin_        = iConfig.getParameter<double>("jetMassMin")  ;
    idxjetMassMax_        = iConfig.getParameter<double>("jetMassMax")  ;
    idxjetPrunedMassMin_  = iConfig.getParameter<double>("jetPrunedMassMin")  ;
    idxjetPrunedMassMax_  = iConfig.getParameter<double>("jetPrunedMassMax")  ;
    idxjetTrimmedMassMin_ = iConfig.getParameter<double>("jetTrimmedMassMin")  ;
    idxjetTrimmedMassMax_ = iConfig.getParameter<double>("jetTrimmedMassMax")  ;
    idxjetSoftDropMassMin_= iConfig.getParameter<double>("jetSoftDropMassMin")  ;
    idxjetSoftDropMassMax_= iConfig.getParameter<double>("jetSoftDropMassMax")  ;
    idxsjMassMin_         = iConfig.getParameter<double>("subjetMassMin")  ;
    idxsjCSVMin_          = iConfig.getParameter<double>("subjetCSVMin")  ;
    idxsjCSVMax_          = iConfig.getParameter<double>("subjetCSVMax")  ;
    idxsjHighestCSVMin_   = iConfig.getParameter<double>("subjetHighestCSVMin")  ;
    idxsjHighestCSVMax_   = iConfig.getParameter<double>("subjetHighestCSVMax")  ;
    btaggedcsvlOP_        = iConfig.getParameter<double>("btaggedcsvlOP")  ;
    btaggedcsvmOP_        = iConfig.getParameter<double>("btaggedcsvmOP")  ;
    btaggedcsvtOP_        = iConfig.getParameter<double>("btaggedcsvtOP")  ;
  }

  if (iConfig.getParameter<bool>("IsJetIDLoose") == true && iConfig.getParameter<bool>("IsJetIDTight") == false) quality_ = JetID::LOOSE ; 
  else if (iConfig.getParameter<bool>("IsJetIDTight") == true && iConfig.getParameter<bool>("IsJetIDLoose") == false) quality_ = JetID::TIGHT ; 
  else edm::LogError("JetMaker::JetMaker") << "Ambiguous JetID: Please select only one (LOOSE or TIGHT) as True!!!" ; 

  if (doGroomedMassCorr_) { 
    jecAK8UncName_ = jecAK8GroomedPayloadNames_.back();
    std::vector<JetCorrectorParameters> vPar;
    for ( std::vector<std::string>::const_iterator it = jecAK8GroomedPayloadNames_.begin(); it != jecAK8GroomedPayloadNames_.end(); ++it) {
      JetCorrectorParameters pars(*it);
      vPar.push_back(pars) ; 
    }
    ptr_jecAK8_ = boost::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) );
  }

  if (jecShift_ != 0 ) {
    ptr_jecUnc = boost::shared_ptr<JetCorrectionUncertainty>(new JetCorrectionUncertainty(jecUncPayloadName_) ) ; 
  }

  if ( newJECPayloadNames_.size() > 0 ) {
    std::vector<JetCorrectorParameters> vPar;  
    for ( std::vector<std::string>::const_iterator it = newJECPayloadNames_.begin(); it != newJECPayloadNames_.end(); ++it) {
      JetCorrectorParameters pars(*it);
      vPar.push_back(pars) ; 
    }
    ptr_newJEC_ = boost::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) ); 
  }

}

void JetMaker::operator()(edm::Event& evt, vlq::JetCollection& jets) {

  Handle <int>            h_npv               ; evt.getByLabel (l_npv                 , h_npv               );
  Handle <double>         h_rho               ; evt.getByLabel (l_rho                 , h_rho               );
  Handle <vector<float>>  h_jetPt             ; evt.getByLabel (l_jetPt               , h_jetPt             );
  Handle <vector<float>>  h_jetEta            ; evt.getByLabel (l_jetEta              , h_jetEta            );
  Handle <vector<float>>  h_jetPhi            ; evt.getByLabel (l_jetPhi              , h_jetPhi            );
  Handle <vector<float>>  h_jetMass           ; evt.getByLabel (l_jetMass             , h_jetMass           );
  Handle <vector<float>>  h_jetEnergy         ; evt.getByLabel (l_jetEnergy           , h_jetEnergy         );
  Handle <vector<float>>  h_jetHadronFlavour  ; evt.getByLabel (l_jetHadronFlavour    , h_jetHadronFlavour  );
  Handle <vector<float>>  h_jetPartonFlavour  ; evt.getByLabel (l_jetPartonFlavour    , h_jetPartonFlavour  );
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
  Handle <vector<float>>  h_jetGenJetPt       ; evt.getByLabel (l_jetGenJetPt         , h_jetGenJetPt       );
  Handle <vector<float>>  h_jetGenJetEta      ; evt.getByLabel (l_jetGenJetEta        , h_jetGenJetEta      );
  Handle <vector<float>>  h_jetGenJetPhi      ; evt.getByLabel (l_jetGenJetPhi        , h_jetGenJetPhi      );

  if ((h_jetPt.product())->size() < 1) return ; 

  const int npv(*h_npv) ; 
  const double rho(*h_rho) ; 

  for (unsigned ijet = 0; ijet < (h_jetPt.product())->size(); ++ijet) { 

      TLorentzVector  jetP4, uncorrJetP4, newJetP4;

      jetP4.SetPtEtaPhiM( (h_jetPt.product())->at(ijet), 
          (h_jetEta.product())->at(ijet), 
          (h_jetPhi.product())->at(ijet), 
          (h_jetMass.product())->at(ijet) ) ;

      uncorrJetP4 = jetP4 * (h_jetJEC.product())->at(ijet) ; 

      double newJEC(1.0); 
      if ( newJECPayloadNames_.size() > 0 ) {
        ptr_newJEC_->setJetPt ( uncorrJetP4.Pt()     );
        ptr_newJEC_->setJetEta( uncorrJetP4.Eta()    );
        ptr_newJEC_->setJetE  ( uncorrJetP4.Energy() );
        ptr_newJEC_->setJetA  ( (h_jetArea.product())->at(ijet) );
        ptr_newJEC_->setRho   ( rho ) ;  
        ptr_newJEC_->setNPV   ( npv );
        newJEC = ptr_newJEC_->getCorrection();
      }
      newJetP4 = uncorrJetP4*newJEC ; 

#if DEBUG
      cout 
        << " \nold jec = " << 1./(h_jetJEC.product())->at(ijet) 
        << " \nnew jec = " << newJEC 
        << " \njet pt uncorrected   = " << uncorrJetP4.Pt() 
        << " \njet mass uncorrected = " << uncorrJetP4.Mag() 
        << " \njet pt before        = " << jetP4.Pt() 
        << " \njet mass before      = " << jetP4.Mag() 
        << " \njet pt newJec        = " << newJetP4.Pt() 
        << " \njet mass newJEC      = " << newJetP4.Mag() 
        << endl ; 
#endif 

      double ptsmear(1.) ;
      if ( jerShift_ != 0 ) {
        double pt_gen = (h_jetGenJetPt.product())->at(ijet) ;  
        double pt_reco   = uncorrJetP4.Pt() ;
        double eta_reco = uncorrJetP4.Eta() ; 
        double jerscalep4 = ApplyJERp4(eta_reco, jerShift_) ; 
        if (pt_gen > 0.) ptsmear = std::max( 0.0, pt_gen + jerscalep4*(pt_reco - pt_gen) )/pt_reco ; 
        else {
          TRandom* rand = new TRandom();
          ptsmear = rand->Gaus(pt_reco, sqrt( (jerscalep4*jerscalep4 - 1)*0.1 ))/pt_reco ; //// Assuming 10% JER
          delete rand; 
        }
        newJetP4 *= ptsmear ; 
#if DEBUG
        cout 
          << " \n pt reco             = " << pt_reco
          << " \n pt gen              = " << pt_gen
          << " \n eta_reco            = " << eta_reco
          << " \n jerscalep4          = " << jerscalep4
          << " \n jer smear           = " << ptsmear 
          << " \njet pt ptsmear       = " << newJetP4.Pt() 
          << " \njet mass ptsmear     = " << newJetP4.Mag() 
          << endl ; 
#endif 
      }

#if DEBUG
      cout 
        << " \n jer smear           = " << ptsmear 
        << " \njet pt ptsmear       = " << newJetP4.Pt() 
        << " \njet mass ptsmear     = " << newJetP4.Mag() 
        << endl ; 
#endif 

      double unc(0);
      if (jecShift_ != 0 ) {
        ptr_jecUnc->setJetEta( uncorrJetP4.Eta()    );
        ptr_jecUnc->setJetPt ( uncorrJetP4.Pt()     );
        unc = ptr_jecUnc->getUncertainty(true);
      }
      newJetP4 *= (1 + jecShift_*unc) ; 

#if DEBUG
      cout 
        << " \njet pt jecshift      = " << newJetP4.Pt() 
        << " \njet mass jecshift    = " << newJetP4.Mag() 
        << endl ; 
#endif 

      JetID jetID(JetIDParams_) ; 
      pat::strbitset retjetid = jetID.getBitTemplate() ;
      retjetid.set(false) ;
      if (jetID(evt, ijet, retjetid) == false) continue ;

      double jetPt      = newJetP4.Pt();
      double jetAbsEta  = std::abs(newJetP4.Eta()) ; 
      double jetCSVDisc = (h_jetCSV.product())->at(ijet); 
      if (jetPt      < idxjetPtMin_       || 
          jetPt      >  idxjetPtMax_      ||
          jetAbsEta  >  idxjetAbsEtaMax_  ||
          jetCSVDisc < idxjetCSVDiscMin_  ||
          jetCSVDisc >  idxjetCSVDiscMax_ 
         ) continue ; 

      //// Jet to put in the jet collection
      vlq::Jet jet ; 

      if ( type_ == AK8JET ) {

        double jettau1       (-1000); 
        double jettau2       (-1000); 
        double jettau3       (-1000); 
        double jetMass       (-1000); 
        double jetPrunedMass (-1000); 
        double jetTrimmedMass(-1000); 
        double jetSoftDropMass (-1000); 
        int    vjetsjIdx0    (-1000); 
        int    vjetsjIdx1    (-1000); 

        double vjetssj0HadFl (-1000) ; 
        double vjetssj0Pt    (-1000) ;
        double vjetssj0Eta   (-1000) ;
        double vjetssj0Phi   (-1000) ;
        double vjetssj0Mass  (-1000) ;
        double vjetssj0CSV   (-1000) ;

        double vjetssj1HadFl (-1000) ; 
        double vjetssj1Pt    (-1000) ;
        double vjetssj1Eta   (-1000) ;
        double vjetssj1Phi   (-1000) ;
        double vjetssj1Mass  (-1000) ;
        double vjetssj1CSV   (-1000) ;

        int nsubjetsbtaggedcsvl(0) ; 
        TLorentzVector p4sj0, p4sj1; 

        Handle <vector<float>>  h_jettau1           ; evt.getByLabel (l_jettau1             , h_jettau1        );
        Handle <vector<float>>  h_jettau2           ; evt.getByLabel (l_jettau2             , h_jettau2        );
        Handle <vector<float>>  h_jettau3           ; evt.getByLabel (l_jettau3             , h_jettau3        );
        Handle <vector<float>>  h_jetPrunedMass     ; evt.getByLabel (l_jetPrunedMass       , h_jetPrunedMass  );
        Handle <vector<float>>  h_jetTrimmedMass    ; evt.getByLabel (l_jetTrimmedMass      , h_jetTrimmedMass );
        Handle <vector<float>>  h_jetFilteredMass   ; evt.getByLabel (l_jetFilteredMass     , h_jetFilteredMass);
        Handle <vector<float>>  h_jetSoftDropMass   ; evt.getByLabel (l_jetSoftDropMass     , h_jetSoftDropMass);
        Handle <vector<float>>  h_ak8sjHadFl        ; evt.getByLabel (l_ak8sjHadFl          , h_ak8sjHadFl     );
        Handle <vector<float>>  h_ak8sjPt           ; evt.getByLabel (l_ak8sjPt             , h_ak8sjPt        );
        Handle <vector<float>>  h_ak8sjEta          ; evt.getByLabel (l_ak8sjEta            , h_ak8sjEta       );
        Handle <vector<float>>  h_ak8sjPhi          ; evt.getByLabel (l_ak8sjPhi            , h_ak8sjPhi       );
        Handle <vector<float>>  h_ak8sjMass         ; evt.getByLabel (l_ak8sjMass           , h_ak8sjMass      );
        Handle <vector<float>>  h_ak8sjCSV          ; evt.getByLabel (l_ak8sjCSV            , h_ak8sjCSV       );
        Handle <vector<float>>  h_ak8sjGenJetPt     ; evt.getByLabel (l_ak8sjGenJetPt       , h_ak8sjGenJetPt  );
        Handle <vector<float>>  h_ak8sjGenJetEta    ; evt.getByLabel (l_ak8sjGenJetEta      , h_ak8sjGenJetEta );
        Handle <vector<float>>  h_ak8sjGenJetPhi    ; evt.getByLabel (l_ak8sjGenJetPhi      , h_ak8sjGenJetPhi );
        Handle <vector<float>>  h_vjetsjIdx0        ; evt.getByLabel (l_vjetsjIdx0          , h_vjetsjIdx0     );
        Handle <vector<float>>  h_vjetsjIdx1        ; evt.getByLabel (l_vjetsjIdx1          , h_vjetsjIdx1     );

        double massCorr(1.); 
        if ( doGroomedMassCorr_ ) {
          ptr_jecAK8_->setJetPt ( uncorrJetP4.Pt()     );
          ptr_jecAK8_->setJetEta( uncorrJetP4.Eta()    );
          ptr_jecAK8_->setJetE  ( uncorrJetP4.Energy() );
          ptr_jecAK8_->setJetA  ( (h_jetArea.product())->at(ijet) );
          ptr_jecAK8_->setRho   ( rho ) ;  
          ptr_jecAK8_->setNPV   ( npv );
          massCorr = ptr_jecAK8_->getCorrection();
        }

        double masssmear(1.) ;
        if ( jerShift_ != 0 ) {
          double pt_gen = (h_jetGenJetPt.product())->at(ijet) ;  
          double pt_reco   = uncorrJetP4.Pt() ;
          double jerscalemass = ApplyJERMass() ; 
          masssmear = std::max( 0.0, pt_gen + jerscalemass*(pt_reco - pt_gen) )/pt_reco ; 
        }

        newJetP4.SetVectM(newJetP4.Vect(), newJetP4.Mag()*massCorr*masssmear) ; 

#if DEBUG
        cout 
          << " \njet pt massCorrSmear = " << newJetP4.Pt() 
          << " \njet mass massCorrSmear " << newJetP4.Mag() 
          << endl ; 
#endif 

        if (scaleJetP4_ ) newJetP4 *= scaledJetMass_/newJetP4.Mag() ; 

#if DEBUG
        cout 
          << " \njet pt scaleJetP4    = " << newJetP4.Pt() 
          << " \njet mass scaleJetP4  = " << newJetP4.Mag() 
          << endl ; 
#endif 

        jettau1         = (h_jettau1.product())->at(ijet) ; 
        jettau2         = (h_jettau2.product())->at(ijet) ; 
        jettau3         = (h_jettau3.product())->at(ijet) ; 
        jetMass         = newJetP4.Mag();
        jetPrunedMass   = masssmear * massCorr * (1 + jecShift_*unc) * (h_jetPrunedMass.product())->at(ijet) ;
        jetTrimmedMass  = masssmear * massCorr * (1 + jecShift_*unc) * (h_jetTrimmedMass.product())->at(ijet) ;
        jetSoftDropMass = masssmear * massCorr * (1 + jecShift_*unc) * (h_jetSoftDropMass.product())->at(ijet) ;
        vjetsjIdx0      = int((h_vjetsjIdx0.product())->at(ijet)) ;
        vjetsjIdx1      = int((h_vjetsjIdx1.product())->at(ijet)) ;
        if (vjetsjIdx0 >= 0 ) {
          vjetssj0HadFl   = (h_ak8sjHadFl.product())->at(vjetsjIdx0) ; 
          vjetssj0Pt      = (h_ak8sjPt.product())->at(vjetsjIdx0) ; 
          vjetssj0Eta     = (h_ak8sjEta.product())->at(vjetsjIdx0) ; 
          vjetssj0Phi     = (h_ak8sjPhi.product())->at(vjetsjIdx0) ; 
          vjetssj0Mass    = (h_ak8sjMass.product())->at(vjetsjIdx0) ; 
          vjetssj0CSV     = (h_ak8sjCSV.product())->at(vjetsjIdx0) ; 
          p4sj0.SetPtEtaPhiM(vjetssj0Pt, vjetssj0Eta, vjetssj0Phi, vjetssj0Mass) ; 
          p4sj0 *= ptsmear * newJEC  * (1 + jecShift_*unc);
        }
        if (vjetsjIdx1 >= 0) {
          vjetssj1HadFl   = (h_ak8sjHadFl.product())->at(vjetsjIdx1) ; 
          vjetssj1Pt      = (h_ak8sjPt.product())->at(vjetsjIdx1) ; 
          vjetssj1Eta     = (h_ak8sjEta.product())->at(vjetsjIdx1) ; 
          vjetssj1Phi     = (h_ak8sjPhi.product())->at(vjetsjIdx1) ; 
          vjetssj1Mass    = (h_ak8sjMass.product())->at(vjetsjIdx1) ; 
          vjetssj1CSV     = (h_ak8sjCSV.product())->at(vjetsjIdx1) ; 
          p4sj1.SetPtEtaPhiM(vjetssj1Pt, vjetssj1Eta, vjetssj1Phi, vjetssj1Mass) ; 
          p4sj1 *= ptsmear * newJEC  * (1 + jecShift_*unc);
        }

        if ( vjetssj0CSV > btaggedcsvlOP_ ) ++nsubjetsbtaggedcsvl ; 
        if ( vjetssj1CSV > btaggedcsvlOP_ ) ++nsubjetsbtaggedcsvl ; 

        double subjetHighestCSV = std::max(vjetssj0CSV,vjetssj1CSV) ; 

        if ( abs(jettau2/jettau1) >= idxjettau2Bytau1Min_ 
            && abs(jettau2/jettau1) <  idxjettau2Bytau1Max_ 
            && abs(jettau3/jettau2) >= idxjettau3Bytau2Min_ 
            && abs(jettau3/jettau2) <  idxjettau3Bytau2Max_
            && abs(jetMass) >= idxjetMassMin_ 
            && abs(jetMass) <  idxjetMassMax_ 
            && abs(jetPrunedMass) >= idxjetPrunedMassMin_ 
            && abs(jetPrunedMass) <  idxjetPrunedMassMax_
            && abs(jetTrimmedMass) >=  idxjetTrimmedMassMin_ 
            && abs(jetTrimmedMass) < idxjetTrimmedMassMax_ 
            && abs(jetSoftDropMass) >=  idxjetSoftDropMassMin_ 
            && abs(jetSoftDropMass) < idxjetSoftDropMassMax_
            && p4sj0.Mag() >=  idxsjMassMin_  
            && p4sj1.Mag() >= idxsjMassMin_ 
            && vjetssj0CSV >=  idxsjCSVMin_ 
            && vjetssj0CSV < idxsjCSVMax_ 
            && vjetssj1CSV >= idxsjCSVMin_ 
            && vjetssj1CSV <  idxsjCSVMax_ 
            && subjetHighestCSV >= idxsjHighestCSVMin_
            && subjetHighestCSV <  idxsjHighestCSVMax_
           ) { 
          jet.setTau1         ( (h_jettau1.product())->at(ijet) ) ; 
          jet.setTau2         ( (h_jettau2.product())->at(ijet) ) ; 
          jet.setTau3         ( (h_jettau3.product())->at(ijet) ) ; 
          jet.setFilteredMass ( ptsmear * massCorr * (1 + jecShift_*unc) * h_jetFilteredMass.product()->at(ijet) ) ; 
          jet.setTrimmedMass  ( ptsmear * massCorr * (1 + jecShift_*unc) * h_jetTrimmedMass.product()->at(ijet) ) ; 
          jet.setPrunedMass   ( ptsmear * massCorr * (1 + jecShift_*unc) * h_jetPrunedMass.product()->at(ijet) ) ; 
          jet.setSoftDropMass ( ptsmear * massCorr * (1 + jecShift_*unc) * h_jetSoftDropMass.product()->at(ijet) ) ; 
          jet.setHadronFlavourSubjet0   ( vjetssj0HadFl ) ;
          jet.setHadronFlavourSubjet1   ( vjetssj1HadFl ) ;
          jet.setPtSubjet0    ( p4sj0.Pt() ) ;
          jet.setPtSubjet1    ( p4sj1.Pt() ) ;
          jet.setEtaSubjet0   ( p4sj0.Eta() ) ;
          jet.setEtaSubjet1   ( p4sj1.Eta() ) ;
          jet.setCSVSubjet0   ( vjetssj0CSV ) ;
          jet.setCSVSubjet1   ( vjetssj1CSV ) ;
          jet.setNConsts      ( (h_jetnumDaughters.product())->at(ijet) ) ;
          jet.setGroomedMassCorr (masssmear * massCorr * (1 + jecShift_*unc) ) ; 
          jet.setNSubjetsBTaggedCSVL (nsubjetsbtaggedcsvl) ; 
        }
        else {
          continue ; 
        }

      } //// if type_ == AK8JET

      jet.setP4           (newJetP4) ; 
      jet.setIndex        (ijet)  ;
      jet.setPartonFlavour( (h_jetPartonFlavour.product())->at(ijet) ) ;  
      jet.setHadronFlavour( (h_jetHadronFlavour.product())->at(ijet) ) ;  
      jet.setCSV          ( (h_jetCSV.product())->at(ijet) ) ;  
      jets.push_back(jet) ; 

#if DEBUG
      cout 
        << " \njet pt finally       = " << jet.getPt() 
        << " \njet mass finally     = " << jet.getMass() 
        << endl ; 
#endif 

  } //// loop over jets 

  std::sort(jets.begin(), jets.end(), Utilities::sortByPt<vlq::Jet>) ; 

}
