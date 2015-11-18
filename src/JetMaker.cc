#include "Analysis/VLQAna/interface/JetMaker.h"

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
  jecAK8GroomedPayloadNames_(iConfig.getParameter<std::vector<std::string>>("groomedPayloadNames")),
  doGroomedMassCorr_        (jecAK8GroomedPayloadNames_.size()>0 ? true : false)  
{

  std::string jettypeStr = iConfig.getParameter<std::string>("jettype") ;
  if      (jettypeStr == "AK4JET")             type_ = AK4JET; 
  else if (jettypeStr == "AK8JET")             type_ = AK8JET;
  else if (jettypeStr == "HTAGGEDAK8JET")      type_ = HTAGGEDAK8JET;
  else if (jettypeStr == "CMSTOPTAGGEDAK8JET") type_ = CMSTOPTAGGEDAK8JET;
  else if (jettypeStr == "PRUNEDSUBJET")       type_ = PRUNEDSUBJET; 
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
  if ( type_ == AK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
    l_jettau1            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau1Label") ;
    l_jettau2            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau2Label") ;
    l_jettau3            = JetSubstrParams_.getParameter<edm::InputTag> ("jettau3Label") ;
    l_jetPrunedMass      = JetSubstrParams_.getParameter<edm::InputTag> ("jetPrunedMassLabel") ;
    l_jetTrimmedMass     = JetSubstrParams_.getParameter<edm::InputTag> ("jetTrimmedMassLabel") ;
    l_jetFilteredMass    = JetSubstrParams_.getParameter<edm::InputTag> ("jetFilteredMassLabel") ;
    l_jetSoftDropMass    = JetSubstrParams_.getParameter<edm::InputTag> ("jetSoftDropMassLabel") ;
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

  idxjetPtMin_ = iConfig.getParameter<double>("jetPtMin")  ;
  idxjetPtMax_ = iConfig.getParameter<double>("jetPtMax")  ;
  idxjetAbsEtaMax_ = iConfig.getParameter<double>("jetAbsEtaMax")  ;
  idxjetCSVDiscMin_ = iConfig.getParameter<double>("jetCSVDiscMin")  ;
  idxjetCSVDiscMax_ = iConfig.getParameter<double>("jetCSVDiscMax")  ;
  if ( type_ == AK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
    idxjettau2Bytau1Min_ = iConfig.getParameter<double>("jettau2Bytau1Min")  ;
    idxjettau2Bytau1Max_ = iConfig.getParameter<double>("jettau2Bytau1Max")  ;
    idxjettau3Bytau2Min_ = iConfig.getParameter<double>("jettau3Bytau2Min")  ;
    idxjettau3Bytau2Max_ = iConfig.getParameter<double>("jettau3Bytau2Max")  ;
    idxjetMassMin_ = iConfig.getParameter<double>("jetMassMin")  ;
    idxjetMassMax_ = iConfig.getParameter<double>("jetMassMax")  ;
    idxjetPrunedMassMin_ = iConfig.getParameter<double>("jetPrunedMassMin")  ;
    idxjetPrunedMassMax_ = iConfig.getParameter<double>("jetPrunedMassMax")  ;
    idxjetTrimmedMassMin_ = iConfig.getParameter<double>("jetTrimmedMassMin")  ;
    idxjetTrimmedMassMax_ = iConfig.getParameter<double>("jetTrimmedMassMax")  ;
    idxjetWMassMin_ = iConfig.getParameter<double>("jetWMassMin")  ;
    idxjetWMassMax_ = iConfig.getParameter<double>("jetWMassMax")  ;
    idxjetTopMassMin_ = iConfig.getParameter<double>("jetTopMassMin")  ;
    idxjetTopMassMax_ = iConfig.getParameter<double>("jetTopMassMax")  ;
    idxjetMinMassMin_ = iConfig.getParameter<double>("jetMinMassMin")  ;
    idxjetMinMassMax_ = iConfig.getParameter<double>("jetMinMassMax")  ;
    idxjetnSubJetsMin_ = iConfig.getParameter<double>("jetnSubJetsMin")  ;
    idxjetnSubJetsMax_ = iConfig.getParameter<double>("jetnSubJetsMax")  ;
    idxsjMassMin_ = iConfig.getParameter<double>("subjetMassMin")  ;
    idxsjCSVMin_ = iConfig.getParameter<double>("subjetCSVMin")  ;
    btaggedcsvlOP_ = iConfig.getParameter<double>("btaggedcsvlOP")  ;
    btaggedcsvmOP_ = iConfig.getParameter<double>("btaggedcsvmOP")  ;
    btaggedcsvtOP_ = iConfig.getParameter<double>("btaggedcsvtOP")  ;
  }

  if (iConfig.getParameter<bool>("IsJetIDLoose") == true && iConfig.getParameter<bool>("IsJetIDTight") == false) quality_ = JetID::LOOSE ; 
  else if (iConfig.getParameter<bool>("IsJetIDTight") == true && iConfig.getParameter<bool>("IsJetIDLoose") == false) quality_ = JetID::TIGHT ; 
  else edm::LogError("JetMaker::JetMaker") << "Ambiguous JetID: Please select only one (LOOSE or TIGHT) as True!!!" ; 

  if (doGroomedMassCorr_) { 
    std::vector<JetCorrectorParameters> vPar;
    vPar.clear();
    for ( std::vector<std::string>::const_iterator payloadBegin = jecAK8GroomedPayloadNames_.begin(), payloadEnd = jecAK8GroomedPayloadNames_.end(), ipayload = payloadBegin; ipayload != payloadEnd; ++ipayload ) {
      JetCorrectorParameters pars(*ipayload);
      vPar.push_back(pars);
    }

    // Make the FactorizedJetCorrector
    jecAK8Groomed_ = boost::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) );
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

  Handle <vector<float>>  h_jettau1           ; 
  Handle <vector<float>>  h_jettau2           ; 
  Handle <vector<float>>  h_jettau3           ; 
  Handle <vector<float>>  h_jetPrunedMass     ; 
  Handle <vector<float>>  h_jetTrimmedMass    ; 
  Handle <vector<float>>  h_jetFilteredMass   ; 
  Handle <vector<float>>  h_jetSoftDropMass   ; 
  Handle <vector<float>>  h_jetwMass          ; 
  Handle <vector<float>>  h_jettopMass        ; 
  Handle <vector<float>>  h_jetminMass        ; 
  Handle <vector<float>>  h_jetnSubJets       ; 
  Handle <vector<float>>  h_ak8sjPt           ; 
  Handle <vector<float>>  h_ak8sjEta          ; 
  Handle <vector<float>>  h_ak8sjPhi          ; 
  Handle <vector<float>>  h_ak8sjMass         ; 
  Handle <vector<float>>  h_ak8sjCSV          ; 
  Handle <vector<float>>  h_vjetsjIdx0        ; 
  Handle <vector<float>>  h_vjetsjIdx1        ; 

  const int npv(*h_npv) ; 
  const double rho(*h_rho) ; 

  if ( type_ == AK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
    evt.getByLabel (l_jettau1             , h_jettau1        );
    evt.getByLabel (l_jettau2             , h_jettau2        );
    evt.getByLabel (l_jettau3             , h_jettau3        );
    evt.getByLabel (l_jetPrunedMass       , h_jetPrunedMass  );
    evt.getByLabel (l_jetTrimmedMass      , h_jetTrimmedMass );
    evt.getByLabel (l_jetFilteredMass     , h_jetFilteredMass);
    evt.getByLabel (l_jetSoftDropMass     , h_jetSoftDropMass);
    evt.getByLabel (l_jetwMass            , h_jetwMass       );
    evt.getByLabel (l_jettopMass          , h_jettopMass     );
    evt.getByLabel (l_jetminMass          , h_jetminMass     );
    evt.getByLabel (l_jetnSubJets         , h_jetnSubJets    );
    evt.getByLabel (l_ak8sjPt             , h_ak8sjPt        );
    evt.getByLabel (l_ak8sjEta            , h_ak8sjEta       );
    evt.getByLabel (l_ak8sjPhi            , h_ak8sjPhi       );
    evt.getByLabel (l_ak8sjMass           , h_ak8sjMass      );
    evt.getByLabel (l_ak8sjCSV            , h_ak8sjCSV       );
    evt.getByLabel (l_vjetsjIdx0          , h_vjetsjIdx0     );
    evt.getByLabel (l_vjetsjIdx1          , h_vjetsjIdx1     );
  }

  if ((h_jetPt.product())->size() < 1) return ; 

  for (unsigned ijet = 0; ijet < (h_jetPt.product())->size(); ++ijet) { 

    JetID jetID(JetIDParams_) ; 
    pat::strbitset retjetid = jetID.getBitTemplate() ;
    retjetid.set(false) ;
    if (jetID(evt, ijet, retjetid) == false) continue ;

    double jetPt      = (h_jetPt.product())->at(ijet);
    double jetAbsEta  = std::abs((h_jetEta.product())->at(ijet)) ; 
    double jetCSVDisc = (h_jetCSV.product())->at(ijet); 
    if (jetPt      < idxjetPtMin_       || 
        jetPt      >= idxjetPtMax_      ||
        jetAbsEta  >= idxjetAbsEtaMax_  ||
        jetCSVDisc < idxjetCSVDiscMin_  ||
        jetCSVDisc >= idxjetCSVDiscMax_ 
       ) continue ; 

    bool passflag(false) ; 

    double jettau1       (-1000); 
    double jettau2       (-1000); 
    double jettau3       (-1000); 
    double jetMass       (-1000); 
    double jetPrunedMass (-1000); 
    double jetTrimmedMass(-1000); 
    int    jetnSubJets   (-1000); 
    int    vjetsjIdx0    (-1000); 
    int    vjetsjIdx1    (-1000); 
    double vjetssj0Pt    (-1000) ;
    double vjetssj0Eta   (-1000) ;
    double vjetssj0Phi   (-1000) ;
    double vjetssj0Mass  (-1000) ;
    double vjetssj0CSV   (-1000) ;
    double vjetssj1Pt    (-1000) ;
    double vjetssj1Eta   (-1000) ;
    double vjetssj1Phi   (-1000) ;
    double vjetssj1Mass  (-1000) ;
    double vjetssj1CSV   (-1000) ;

    int nsubjetsbtaggedcsvl(0) ; 

    if ( type_ == AK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
      jettau1         = (h_jettau1.product())->at(ijet) ; 
      jettau2         = (h_jettau2.product())->at(ijet) ; 
      jettau3         = (h_jettau3.product())->at(ijet) ; 
      jetMass         = (h_jetMass.product())->at(ijet) ;
      jetPrunedMass   = (h_jetPrunedMass.product())->at(ijet) ;
      jetTrimmedMass  = (h_jetTrimmedMass.product())->at(ijet) ;
      jetnSubJets     = int((h_jetnSubJets.product())->at(ijet)) ;
      vjetsjIdx0      = int((h_vjetsjIdx0.product())->at(ijet)) ;
      vjetsjIdx1      = int((h_vjetsjIdx1.product())->at(ijet)) ;
      if (vjetsjIdx0 >= 0 ) {
        vjetssj0Pt      = (h_ak8sjPt.product())->at(vjetsjIdx0) ; 
        vjetssj0Eta     = (h_ak8sjEta.product())->at(vjetsjIdx0) ; 
        vjetssj0Phi     = (h_ak8sjPhi.product())->at(vjetsjIdx0) ; 
        vjetssj0Mass    = (h_ak8sjMass.product())->at(vjetsjIdx0) ; 
        vjetssj0CSV     = (h_ak8sjCSV.product())->at(vjetsjIdx0) ; 
      }
      if (vjetsjIdx1 >= 0) {
        vjetssj1Pt      = (h_ak8sjPt.product())->at(vjetsjIdx1) ; 
        vjetssj1Eta     = (h_ak8sjEta.product())->at(vjetsjIdx1) ; 
        vjetssj1Phi     = (h_ak8sjPhi.product())->at(vjetsjIdx1) ; 
        vjetssj1Mass    = (h_ak8sjMass.product())->at(vjetsjIdx1) ; 
        vjetssj1CSV     = (h_ak8sjCSV.product())->at(vjetsjIdx1) ; 
      }

      if ( vjetssj0CSV > btaggedcsvlOP_ ) ++nsubjetsbtaggedcsvl ; 
      if ( vjetssj1CSV > btaggedcsvlOP_ ) ++nsubjetsbtaggedcsvl ; 
      if ( jettau2/jettau1< idxjettau2Bytau1Min_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jettau2/jettau1 = " << jettau2/jettau1 << " < cutmin\n" ; 
        continue ; 
      }   
      if ( jettau2/jettau1> idxjettau2Bytau1Max_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jettau2/jettau1 = " << jettau2/jettau1 << " > cutmax\n" ; 
        continue ; 
      }   
      if ( jettau3/jettau2< idxjettau3Bytau2Min_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jettau3/jettau2 = " << jettau3/jettau2 << " < cutmin\n" ; 
        continue ; 
      }   
      if ( jettau3/jettau2> idxjettau3Bytau2Max_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jettau3/jettau2 = " << jettau3/jettau2 << " > cutmax\n" ; 
        continue ; 
      }   
      if ( jetMass        < idxjetMassMin_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jetMass = " << jetMass << " < cutmin\n" ; 
        continue ; 
      }   
      if ( jetMass        > idxjetMassMax_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jetMass = " << jetMass << " > cutmax\n" ; 
        continue ; 
      }   
      if ( jetPrunedMass  < idxjetPrunedMassMin_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jetPrunedMass = " << jetPrunedMass << " < cutmin\n" ; 
        continue ; 
      }   
      if ( jetPrunedMass  > idxjetPrunedMassMax_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jetPrunedMass = " << jetPrunedMass << " > cutmax\n" ; 
        continue ; 
      }   
      if ( jetTrimmedMass < idxjetTrimmedMassMin_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jetTrimmedMass = " << jetTrimmedMass << " < cutmin\n" ; 
        continue ; 
      }   
      if ( jetTrimmedMass > idxjetTrimmedMassMax_ ) { 
        LogDebug("JetMaker") << " ak8 jet fails jetTrimmedMass = " << jetTrimmedMass << " > cutmax\n" ; 
        continue ; 
      }   
      if (type_ == HTAGGEDAK8JET) {
        edm::LogInfo("JetMaker") << " jetnSubJets = " << jetnSubJets << " min = " << idxjetnSubJetsMin_  << " max = " << idxjetnSubJetsMax_ << endl ; 
        if (vjetsjIdx0 >= 0 && vjetsjIdx1 >= 0) {
          TLorentzVector p4sj0, p4sj1; 
          p4sj0.SetPtEtaPhiM(vjetssj0Pt, vjetssj0Eta, vjetssj0Phi, vjetssj0Mass) ; 
          p4sj1.SetPtEtaPhiM(vjetssj1Pt, vjetssj1Eta, vjetssj1Phi, vjetssj1Mass) ; 
          if (jetnSubJets >= idxjetnSubJetsMin_
              && jetnSubJets <= idxjetnSubJetsMax_
              && p4sj0.Mag() > idxsjMassMin_ 
              && p4sj1.Mag() > idxsjMassMin_
              && vjetssj0CSV >= idxsjCSVMin_
              && vjetssj1CSV >= idxsjCSVMin_
             ) passflag = true ; 
          else passflag = false ; 
        }
        else passflag = false ; 
      }
      else if (type_ == CMSTOPTAGGEDAK8JET) {
        Handle <vector<float>>  h_tjetsjIdx0        ; evt.getByLabel (l_tjetsjIdx0          , h_tjetsjIdx0     );
        Handle <vector<float>>  h_tjetsjIdx1        ; evt.getByLabel (l_tjetsjIdx1          , h_tjetsjIdx1     );
        Handle <vector<float>>  h_tjetsjIdx2        ; evt.getByLabel (l_tjetsjIdx2          , h_tjetsjIdx2     );
        Handle <vector<float>>  h_tjetsjIdx3        ; evt.getByLabel (l_tjetsjIdx3          , h_tjetsjIdx3     );
        //int    tjetsjIdx0      = int((h_tjetsjIdx0.product())->at(ijet)) ;
        //int    tjetsjIdx1      = int((h_tjetsjIdx1.product())->at(ijet)) ;
        //int    tjetsjIdx2      = int((h_tjetsjIdx2.product())->at(ijet)) ;
        //int    tjetsjIdx3      = int((h_tjetsjIdx3.product())->at(ijet)) ;
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
        //double jetMinMass      = (h_jetnSubJets.product())->at(ijet) ;
        double jetWMass        = (h_jetwMass.product())->at(ijet) ;
        double jetTopMass      = (h_jettopMass.product())->at(ijet) ;
        if (jetnSubJets >= idxjetnSubJetsMin_
            && jetnSubJets <= idxjetnSubJetsMax_ 
            && jetTopMass > idxjetTopMassMin_ 
            && jetTopMass < idxjetTopMassMax_
            && jetWMass > idxjetMinMassMin_ 
            && jetWMass < idxjetMinMassMax_
           ) {
          passflag = true ; 
        }
        else passflag = false ; 
      }
      else passflag = true ; 

    } //// if fatjets 
    else passflag = true ; 

    if (passflag)  {
      vlq::Jet jet ; 

      TLorentzVector  jetP4;
      jetP4.SetPtEtaPhiE( (h_jetPt.product())->at(ijet), (h_jetEta.product())->at(ijet), (h_jetPhi.product())->at(ijet), (h_jetEnergy.product())->at(ijet) ) ;

      //// Apply correction on jet groomed mass
      double prunedcorr(1.); 
      if ( doGroomedMassCorr_ ) {
        jetP4 *= (h_jetJEC.product())->at(ijet) ; 
        jecAK8Groomed_->setJetEta( jetP4.Eta()    );
        jecAK8Groomed_->setJetPt ( jetP4.Pt()     );
        jecAK8Groomed_->setJetE  ( jetP4.Energy() );
        jecAK8Groomed_->setJetA  ( (h_jetArea.product())->at(ijet) );
        jecAK8Groomed_->setRho   ( rho ) ;  
        jecAK8Groomed_->setNPV   ( npv );
        prunedcorr = jecAK8Groomed_->getCorrection();
      }

      if (scaleJetP4_) {
        if ( type_ == AK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) jetP4 *= scaledJetMass_/(h_jetPrunedMass.product())->at(ijet) ;  
        else jetP4 *= scaledJetMass_/jetP4.Mag() ; 
      }

      jet.setP4           (jetP4) ; 
      jet.setIndex        (ijet)  ;
      jet.setPartonFlavour( (h_jetPartonFlavour.product())->at(ijet) ) ;  
      jet.setHadronFlavour( (h_jetHadronFlavour.product())->at(ijet) ) ;  
      jet.setCSV          ( (h_jetCSV.product())->at(ijet) ) ;  
      if ( type_ == AK8JET || type_ == HTAGGEDAK8JET || type_ == CMSTOPTAGGEDAK8JET ) {
        jet.setTau1         ( (h_jettau1.product())->at(ijet) ) ; 
        jet.setTau2         ( (h_jettau2.product())->at(ijet) ) ; 
        jet.setTau3         ( (h_jettau3.product())->at(ijet) ) ; 
        jet.setFilteredMass ( prunedcorr*(h_jetFilteredMass.product())->at(ijet) ) ; 
        jet.setTrimmedMass  ( prunedcorr*(h_jetTrimmedMass.product())->at(ijet) ) ; 
        jet.setPrunedMass   ( prunedcorr*(h_jetPrunedMass.product())->at(ijet) ) ; 
        jet.setSoftDropMass ( prunedcorr*(h_jetSoftDropMass.product())->at(ijet) ) ; 
        jet.setNSubjets     ( jetnSubJets ) ; 
        jet.setCSVSubjet0   ( vjetssj0CSV ) ;
        jet.setCSVSubjet1   ( vjetssj1CSV ) ;
        jet.setNConsts      ( (h_jetnumDaughters.product())->at(ijet) ) ;
        jet.setGroomedMassCorr (prunedcorr) ; 
        jet.setNSubjetsBTaggedCSVL (nsubjetsbtaggedcsvl) ; 
      }
      jets.push_back(jet) ; 
    }

  } //// loop over jets 

}
