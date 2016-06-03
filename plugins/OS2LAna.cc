// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      OS2LAna
// 
/**\class VLQAna OS2LAna.cc Analysis/VLQAna/plugins/OS2LAna.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Devdatta Majumder
//         Created:  Fri, 27 Feb 2015 16:09:10 GMT
// Modified: Sadia Khalil
//           25 Mar 2016 17:11 CDT
//

#include <iostream>
#include <memory>
#include <vector>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"

#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/DileptonCandsProducer.h"
#include "Analysis/VLQAna/interface/CandidateFilter.h"
#include "Analysis/VLQAna/interface/MuonMaker.h"
#include "Analysis/VLQAna/interface/ElectronMaker.h"
#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/HT.h"
#include "Analysis/VLQAna/interface/ApplyLeptonSFs.h"
#include "Analysis/VLQAna/interface/CandidateCleaner.h"
#include "Analysis/VLQAna/interface/METMaker.h"
#include "Analysis/VLQAna/interface/PickGenPart.h"
#include "Analysis/VLQAna/interface/JetID.h"
#include "Analysis/VLQAna/interface/MassReco.h"
#include "Analysis/VLQAna/interface/BTagSFUtils.h"

#include <TFile.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLorentzVector.h>

//
// class declaration
//

class OS2LAna : public edm::EDFilter {
  public:
    explicit OS2LAna(const edm::ParameterSet&);
    ~OS2LAna();

  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    void fillAdditionalPlots( vlq::ElectronCollection goodElectrons,double evtwt);
    double GetDYNLOCorr(const double dileppt); 
    // ----------member data ---------------------------
    edm::EDGetTokenT<string>   t_evttype         ;
    edm::EDGetTokenT<double>   t_evtwtGen        ;
    edm::EDGetTokenT<double>   t_evtwtPV         ;
    edm::EDGetTokenT<unsigned> t_npv             ;
    edm::EDGetTokenT<bool>     t_hltdecision     ;
    edm::ParameterSet DilepCandParams_           ; 
    edm::ParameterSet ZCandParams_               ; 
    edm::ParameterSet BoostedZCandParams_        ; 
    edm::ParameterSet GenHSelParams_             ;
    edm::ParameterSet genParams_                 ;
    const double HTMin_                          ;
    const double STMin_                          ; 
    const bool filterSignal_                     ;
    const bool additionalPlots_                  ;
    const std::string signalType_                ;
    const std::string zdecayMode_                ;
    const bool optimizeReco_                     ;
    const double vlqMass_                        ;
    const double bosonMass_                      ;
    const bool applyLeptonSFs_                   ;
    const bool applyBTagSFs_                     ;
    const bool applyDYNLOCorr_                   ;
    const std::string fname_DYNLOCorr_           ; 
    const std::string funname_DYNLOCorr_         ; 
    ApplyLeptonSFs lepsfs                        ;
    METMaker metmaker                            ;
    MuonMaker muonmaker                          ; 
    ElectronMaker electronmaker                  ; 
    JetMaker jetAK4maker                         ; 
    JetMaker jetAK4BTaggedmaker                  ; 
    JetMaker jetAK8maker                         ; 
    JetMaker jetHTaggedmaker                     ; 
    JetMaker jetWTaggedmaker                     ; 
    JetMaker jetTopTaggedmaker                   ; 
    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    std::map<std::string, TH2D*> h2_             ; 
    std::string lep; 
    PickGenPart genpart                          ;
    const std::string fnamebtagSF_               ;
    std::unique_ptr<BTagSFUtils> btagsfutils_    ; 

};

using namespace std;

// static data member definitions
void OS2LAna::fillAdditionalPlots( vlq::ElectronCollection goodElectrons,double evtwt){

  for  (unsigned int iele=0; iele<goodElectrons.size(); ++iele){
    float scEta = goodElectrons.at(iele).getscEta();
    if(fabs(scEta) <= 1.479){
      h1_["Eta_EB_el_pre"]-> Fill(goodElectrons.at(iele).getEta(), evtwt);
      h1_["Iso03_EB_el_pre"]->Fill(goodElectrons.at(iele).getIso03(), evtwt);
      h1_["dEtaIn_EB_el_pre"]->Fill(goodElectrons.at(iele).getdEtaIn(), evtwt);
      h1_["dPhiIn_EB_el_pre"]->Fill(goodElectrons.at(iele).getdPhiIn(), evtwt);
      h1_["Dz_EB_el_pre"]->Fill(goodElectrons.at(iele).getDz(), evtwt);
      h1_["D0_EB_el_pre"]->Fill(goodElectrons.at(iele).getD0(), evtwt);
    }
    else if  (fabs(scEta > 1.479) && fabs(scEta < 2.5)){
      h1_["Eta_EE_el_pre"]->Fill(goodElectrons.at(iele).getEta(), evtwt);
      h1_["Iso03_EE_el_pre"]->Fill(goodElectrons.at(iele).getIso03(), evtwt);
      h1_["dEtaIn_EE_el_pre"]->Fill(goodElectrons.at(iele).getdEtaIn(), evtwt);
      h1_["dPhiIn_EE_el_pre"]->Fill(goodElectrons.at(iele).getdPhiIn(), evtwt);
      h1_["Dz_EE_el_pre"]->Fill(goodElectrons.at(iele).getDz(), evtwt);
      h1_["D0_EE_el_pre"]->Fill(goodElectrons.at(iele).getD0(), evtwt);
    }
  }
}

// constructors and destructor
OS2LAna::OS2LAna(const edm::ParameterSet& iConfig) :
  t_evttype               (consumes<string>  (iConfig.getParameter<edm::InputTag>("evttype"))),
  t_evtwtGen              (consumes<double>  (iConfig.getParameter<edm::InputTag>("evtwtGen"))),
  t_evtwtPV               (consumes<double>  (iConfig.getParameter<edm::InputTag>("evtwtPV"))),
  t_npv                   (consumes<unsigned>(iConfig.getParameter<edm::InputTag>("npv"))),
  t_hltdecision           (consumes<bool>    (iConfig.getParameter<edm::InputTag>("hltdecision"))),
  DilepCandParams_        (iConfig.getParameter<edm::ParameterSet> ("DilepCandParams")),
  ZCandParams_            (iConfig.getParameter<edm::ParameterSet> ("ZCandParams")),
  BoostedZCandParams_     (iConfig.getParameter<edm::ParameterSet> ("BoostedZCandParams")),
  GenHSelParams_          (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
  genParams_              (iConfig.getParameter<edm::ParameterSet> ("genParams")),
  HTMin_                  (iConfig.getParameter<double>            ("HTMin")),
  STMin_                  (iConfig.getParameter<double>            ("STMin")), 
  filterSignal_           (iConfig.getParameter<bool>              ("filterSignal")), 
  additionalPlots_        (iConfig.getParameter<bool>              ("additionalPlots")), 
  signalType_             (iConfig.getParameter<std::string>       ("signalType")), 
  zdecayMode_             (iConfig.getParameter<std::string>       ("zdecayMode")),
  optimizeReco_           (iConfig.getParameter<bool>              ("optimizeReco")),
  vlqMass_                (iConfig.getParameter<double>            ("vlqMass")),
  bosonMass_              (iConfig.getParameter<double>            ("bosonMass")),
  applyLeptonSFs_         (iConfig.getParameter<bool>              ("applyLeptonSFs")), 
  applyBTagSFs_           (iConfig.getParameter<bool>              ("applyBTagSFs")), 
  applyDYNLOCorr_         (iConfig.getParameter<bool>              ("applyDYNLOCorr")), 
  fname_DYNLOCorr_        (iConfig.getParameter<std::string>       ("File_DYNLOCorr")),
  funname_DYNLOCorr_      (iConfig.getParameter<std::string>       ("Fun_DYNLOCorr")),
  lepsfs                  (iConfig.getParameter<edm::ParameterSet> ("lepsfsParams")),
  metmaker                (iConfig.getParameter<edm::ParameterSet> ("metselParams"),consumesCollector()),
  muonmaker               (iConfig.getParameter<edm::ParameterSet> ("muselParams"),consumesCollector()),
  electronmaker           (iConfig.getParameter<edm::ParameterSet> ("elselParams"),consumesCollector()),
  jetAK4maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK4selParams"),consumesCollector()),
  jetAK4BTaggedmaker      (iConfig.getParameter<edm::ParameterSet> ("jetAK4BTaggedselParams"),consumesCollector()),
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams"),consumesCollector()),
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams"),consumesCollector()),
  jetWTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetWTaggedselParams"),consumesCollector()),
  jetTopTaggedmaker       (iConfig.getParameter<edm::ParameterSet> ("jetTopTaggedselParams"),consumesCollector()),   
  lep                     (iConfig.getParameter<std::string>       ("lep")), 
  genpart                 (genParams_, consumesCollector()),
  fnamebtagSF_            (iConfig.getParameter<std::string>       ("fnamebtagSF")),
  btagsfutils_            (new BTagSFUtils(fnamebtagSF_,BTagEntry::OP_MEDIUM,30., 670., 30., 670., 20., 1000.))
{

  produces<vlq::JetCollection>("tjets") ; 
  produces<vlq::JetCollection>("wjets") ; 
  produces<vlq::JetCollection>("bjets") ; 
  produces<vlq::JetCollection>("jets") ; 
  produces<vlq::CandidateCollection>("zllcands") ; 
}


OS2LAna::~OS2LAna() {}

bool OS2LAna::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<string>   h_evttype     ; evt.getByToken(t_evttype    , h_evttype    ) ; 
  Handle<double>   h_evtwtGen    ; evt.getByToken(t_evtwtGen   , h_evtwtGen   ) ; 
  Handle<double>   h_evtwtPV     ; evt.getByToken(t_evtwtPV    , h_evtwtPV    ) ; 
  Handle<unsigned> h_npv         ; evt.getByToken(t_npv        , h_npv        ) ; 
  Handle<bool>     h_hltdecision ; evt.getByToken(t_hltdecision, h_hltdecision) ; 

  //  unsigned npv(*h_npv.product()) ; 

  if(zdecayMode_ == "zmumu") {lep = "mu";}
  else if ( zdecayMode_ == "zelel") {lep = "el";}
  else edm::LogError("OS2LAna::filter") << " >>>> WrongleptonType: " << lep << " Check lep name !!!" ;

  if (filterSignal_) {
    if (*h_evttype.product()!=signalType_) return false ;
    else  h1_["signalEvts"] -> Fill(1) ;
  }

  const bool hltdecision(*h_hltdecision.product()) ; 
  if ( !hltdecision ) return false;

  //double evtwtgen(*h_evtwtGen.product());
  double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 

  vlq::MuonCollection goodMuons; 
  muonmaker(evt, goodMuons) ; 

  vlq::ElectronCollection goodElectrons; 
  electronmaker(evt, goodElectrons) ;

  vlq::MetCollection goodMet;
  metmaker(evt, goodMet) ;

  vlq::CandidateCollection dimuons, dielectrons, dileptons;   
  vlq::CandidateCollection zll; //generic collection

  // dilepton properties: M > 50, lead pt > 45, second pt > 25
  DileptonCandsProducer dileptonsprod(DilepCandParams_) ; 
  dileptonsprod.operator()<vlq::MuonCollection>(dimuons, goodMuons); 
  dileptonsprod.operator()<vlq::ElectronCollection>(dielectrons, goodElectrons) ; 

  //================================================================
  //First pre-selection: 1) 2 OS dileptons from boosted Z, >=3 jets
  //================================================================

  //dilepton candidate
  if (zdecayMode_ == "zmumu") {dileptons = dimuons; }
  else if (zdecayMode_ == "zelel") {dileptons = dielectrons;}
  if (dileptons.size()  < 1) return false;

  //// Get Dy EWK correction
  if ( applyDYNLOCorr_ ) {
    double EWKNLOkfact(GetDYNLOCorr(dileptons.at(0).getPt())) ; 
    evtwt *= EWKNLOkfact ;
  }

  //get lepton ID and Iso SF
  if (applyLeptonSFs_ && *h_evttype.product() != "EvtType_Data") {
    if ( zdecayMode_ == "zmumu" ){
      evtwt *= lepsfs(goodMuons.at(0).getPt(),goodMuons.at(0).getEta()) * lepsfs(goodMuons.at(1).getPt(), goodMuons.at(1).getEta() ) ;}
    else if ( zdecayMode_ == "zelel" ){ 
      evtwt *= lepsfs(goodElectrons.at(0).getPt(),goodElectrons.at(0).getEta()) * lepsfs(goodElectrons.at(1).getPt(), goodElectrons.at(1).getEta() ) ;}
  }

  h1_["cutflow"] -> Fill(1, evtwt) ;

  //Z mass candidate filter: 75 < M < 105, lead pt > 45, 2nd pt > 25, Z pt > 0
  CandidateFilter zllfilter(ZCandParams_) ; 
  zllfilter(dileptons, zll);

  // jets
  vlq::JetCollection goodAK4Jets;
  jetAK4maker(evt, goodAK4Jets) ;

  CandidateCleaner cleanjets(0.4);
  if (zdecayMode_ == "zmumu") {cleanjets(goodAK4Jets, goodMuons);}
  else if (zdecayMode_ == "zelel") {cleanjets(goodAK4Jets, goodElectrons);} 

  HT htak4(goodAK4Jets) ; 

  ////////////////////////////////////////////////////////// 
  //Fill N-1 selected plots for dilepton mass, Ht, ad Njets
  //////////////////////////////////////////////////////////

  //Fill Z mass: >=3 jets, HT > 300
  if (goodAK4Jets.size() > 2 && htak4.getHT() > HTMin_){
    for (auto idilepton : dileptons) h1_["mass_z"+lep+lep+"_pre"] -> Fill(idilepton.getMass(), evtwt) ; 
  }
  //at least one Z cand in event
  if(zll.size() > 0) {h1_["cutflow"] -> Fill(2, evtwt) ;}
  else return false ;

  //Fill Njets: HT > 300 && Z mass
  if (htak4.getHT() > HTMin_){h1_["nak4_pre"] -> Fill(goodAK4Jets.size(), evtwt) ;} 

  //at least 3 AK4 jets in event
  if (goodAK4Jets.size() > 2 ) {h1_["cutflow"] -> Fill(3, evtwt) ;} 
  else return false;

  //Fill HT: >=3 jets, && Z mass
  h1_["ht_pre"] -> Fill(htak4.getHT(), evtwt) ; 

  // at least HT > 150 in event
  if ( htak4.getHT() > HTMin_ ) h1_["cutflow"] -> Fill(4, evtwt) ;  
  else return false ; 

  //deltaPhi(MET,lep)

  ///////////////////////////////////////////// 
  // fill rest of the plots after pre-selection
  /////////////////////////////////////////////

  double ST = htak4.getHT() ;
  ST += zll.at(0).getPt() + goodMet.at(0).getFullPt(); 
  h1_["st_pre"] -> Fill(ST, evtwt) ;   

  //ak4 jet plots
  for(int j=0; j<3; ++j){
    h1_[Form("ptak4jet%d_pre", j+1)]  -> Fill(goodAK4Jets.at(j).getPt(), evtwt) ; 
    h1_[Form("etaak4jet%d_pre", j+1)] -> Fill(goodAK4Jets.at(j).getEta(), evtwt) ;
    h1_[Form("cvsak4jet%d_pre", j+1)] -> Fill(goodAK4Jets.at(j).getCSV(), evtwt) ;
  }
  h1_["phi_jet1MET_pre"] -> Fill( (goodAK4Jets.at(0).getP4()).DeltaPhi(goodMet.at(0).getP4()), evtwt);

  // npv
  h1_["npv_noweight_pre"] -> Fill(*h_npv.product(), *h_evtwtGen.product()); 
  h1_["npv_pre"] -> Fill(*h_npv.product(), evtwt);

  // met
  h1_["met_pre"] -> Fill(goodMet.at(0).getFullPt(), evtwt);
  h1_["metPhi_pre"] -> Fill(goodMet.at(0).getFullPhi(), evtwt);

  //lepton specfic properties
  if ( zdecayMode_ == "zmumu" ){       
    for(int l=0; l<2; ++l){
      h1_["pt_"+lep+Form("%d_pre", l+1)]  -> Fill(goodMuons.at(l).getPt(), evtwt) ; 
      h1_["eta_"+lep+Form("%d_pre", l+1)]  -> Fill(goodMuons.at(l).getEta(), evtwt) ; 
    } 

    h1_["dr_mumu_pre"]-> Fill( (goodMuons.at(0).getP4()).DeltaR(goodMuons.at(1).getP4()), evtwt );
  }
  else if (zdecayMode_ == "zelel" ) {
    for(int l=0; l<2; ++l){
      h1_["pt_"+lep+Form("%d_pre", l+1)]   -> Fill(goodElectrons.at(l).getPt(), evtwt) ; 
      h1_["eta_"+lep+Form("%d_pre", l+1)]  -> Fill(goodElectrons.at(l).getEta(), evtwt) ; 
    } 

    h1_["dr_elel_pre"]-> Fill( (goodElectrons.at(0).getP4()).DeltaR(goodElectrons.at(1).getP4()), evtwt );
    if(additionalPlots_) fillAdditionalPlots(goodElectrons,evtwt);
  }

  // Z pt
  for (auto izll : zll) h1_["pt_z"+lep+lep+"_pre"] -> Fill(izll.getPt(), evtwt) ;

  //========================================================
  // Preselection done, proceeding with control selections
  //========================================================

  //b-tagging:
  vlq::JetCollection goodBTaggedAK4Jets;
  jetAK4BTaggedmaker(evt, goodBTaggedAK4Jets) ; 

  if (zdecayMode_ == "zmumu") {cleanjets(goodBTaggedAK4Jets, goodMuons); }
  else if (zdecayMode_ == "zelel") {cleanjets(goodBTaggedAK4Jets, goodElectrons); }  

  double btagsf(1) ;
  double btagsf_bcUp(1) ; 
  double btagsf_bcDown(1) ; 
  double btagsf_lUp(1) ; 
  double btagsf_lDown(1) ; 
  if ( applyBTagSFs_ ) {
     std::vector<double>csvs;
     std::vector<double>pts;
     std::vector<double>etas;
     std::vector<int>   flhads;

     for (vlq::Jet jet : goodAK4Jets) {
       csvs.push_back(jet.getCSV()) ; 
       pts.push_back(jet.getPt()) ; 
       etas.push_back(jet.getEta()) ; 
       flhads.push_back(jet.getHadronFlavour()) ; 
     }

     btagsfutils_->getBTagSFs (csvs, pts, etas, flhads, jetAK4maker.idxjetCSVDiscMin_, btagsf, btagsf_bcUp, btagsf_bcDown, btagsf_lUp, btagsf_lDown) ; 

     std::cout << " btag sf = " << btagsf << " bc Up = " << btagsf_bcUp << " btagsf_bcDown = " 
       << btagsf_bcDown << " btagsf_lUp " << btagsf_lUp << " btagsf_lDown " << btagsf_lDown << std::endl;  
  }

  //fill control plots
  if ( goodBTaggedAK4Jets.size() > 0 && ST < 700) {
    for (auto izll : zll) {
      h1_["mass_z"+lep+lep+"_cnt"] -> Fill(izll.getMass(), evtwt) ;  
      h1_["pt_z"+lep+lep+"_cnt"] -> Fill(izll.getPt(), evtwt) ; 
    }
    h1_["nak4_cnt"] -> Fill(goodAK4Jets.size(), evtwt) ;
    h1_["ht_cnt"] -> Fill(htak4.getHT(), evtwt) ;
    h1_["st_cnt"] -> Fill(ST, evtwt) ;   
    h1_["npv_noweight_cnt"] -> Fill(*h_npv.product(), *h_evtwtGen.product()); 
    h1_["npv_cnt"] -> Fill(*h_npv.product(), evtwt);
    h1_["met_cnt"] -> Fill(goodMet.at(0).getFullPt(), evtwt);
    h1_["metPhi_cnt"] -> Fill(goodMet.at(0).getFullPhi(), evtwt);

    //lepton specfic properties
    if ( zdecayMode_ == "zmumu" ){       
      for(int l=0; l<2; ++l){
        h1_["pt_"+lep+Form("%d_cnt", l+1)]  -> Fill(goodMuons.at(l).getPt(), evtwt) ; 
        h1_["eta_"+lep+Form("%d_cnt", l+1)]  -> Fill(goodMuons.at(l).getEta(), evtwt) ; 
      } 
      h1_["dr_mumu_cnt"]-> Fill( (goodMuons.at(0).getP4()).DeltaR(goodMuons.at(1).getP4()), evtwt );
    }
    else if (zdecayMode_ == "zelel" ) {
      for(int l=0; l<2; ++l){
        h1_["pt_"+lep+Form("%d_cnt", l+1)]   -> Fill(goodElectrons.at(l).getPt(), evtwt) ; 
        h1_["eta_"+lep+Form("%d_cnt", l+1)]  -> Fill(goodElectrons.at(l).getEta(), evtwt) ; 
      } 
      h1_["dr_elel_cnt"]-> Fill( (goodElectrons.at(0).getP4()).DeltaR(goodElectrons.at(1).getP4()), evtwt );
    }

    //ak4 jet plots
    for(int j=0; j<3; ++j){
      h1_[Form("ptak4jet%d_cnt", j+1)]  -> Fill(goodAK4Jets.at(j).getPt(), evtwt) ; 
      h1_[Form("etaak4jet%d_cnt", j+1)] -> Fill(goodAK4Jets.at(j).getEta(), evtwt) ;
      h1_[Form("cvsak4jet%d_cnt", j+1)] -> Fill(goodAK4Jets.at(j).getCSV(), evtwt) ;
    }
    h1_["phi_jet1MET_cnt"] -> Fill( (goodAK4Jets.at(0).getP4()).DeltaPhi(goodMet.at(0).getP4()), evtwt);
  }

  //===========================================================
  // Control selection done, proceeding with signal selections
  //===========================================================

  //Boosted Z candidates: Z pt > 150 GeV
  //CandidateFilter boostedzllfilter(BoostedZCandParams_) ; 
  //boostedzllfilter(dileptons, zllBoosted) ;    
  //if(zllBoosted.size() > 0) h1_["cutflow"] -> Fill(4, evtwt) ;
  //else return false ; 

  // leading jet pt > 100 GeV
  if (goodAK4Jets.at(0).getPt() > 100){h1_["cutflow"] -> Fill(5, evtwt) ; }
  else return false;

  // 2nd laeding jet pt > 50 GeV
  if (goodAK4Jets.at(1).getPt() > 50){h1_["cutflow"] -> Fill(6, evtwt) ; }
  else return false;

  // at least one b-jet 
  if ( goodBTaggedAK4Jets.size() > 0 ) { h1_["cutflow"] -> Fill(7, evtwt) ;}
  else return false;

  // ST > 1000 GeV
  if ( ST > STMin_ ) h1_["cutflow"] -> Fill(8, evtwt) ;  
  else return false ; 

  // get AK8, top, b, Z, and W jets
  vlq::JetCollection goodAK8Jets, goodHTaggedJets, goodWTaggedJets, goodTopTaggedJets;
  jetAK8maker(evt, goodAK8Jets); 
  cleanjets(goodAK8Jets, goodMuons); 
  cleanjets(goodAK8Jets, goodElectrons); 

  jetWTaggedmaker(evt, goodWTaggedJets);
  cleanjets(goodWTaggedJets, goodMuons); 
  cleanjets(goodWTaggedJets, goodElectrons); 

  jetHTaggedmaker(evt, goodHTaggedJets);
  cleanjets(goodHTaggedJets, goodMuons); 
  cleanjets(goodHTaggedJets, goodElectrons); 

  jetTopTaggedmaker(evt, goodTopTaggedJets);
  cleanjets(goodTopTaggedJets, goodMuons); 
  cleanjets(goodTopTaggedJets, goodElectrons); 

  //if (matchedAK8Jets.size() > 0) h1_["cutflow"] -> Fill(9, evtwt) ;
  //else return false 

  ///////////////////////////////////////
  // fill all the plots in signal region
  ///////////////////////////////////////
  for (auto izll : zll) {
    h1_["mass_z"+lep+lep] -> Fill(izll.getMass(), evtwt) ;  
    h1_["pt_z"+lep+lep] -> Fill(izll.getPt(), evtwt) ; 
  }

  h1_["nak4"] -> Fill(goodAK4Jets.size(), evtwt) ;
  h1_["ht"] -> Fill(htak4.getHT(), evtwt) ;
  h1_["st"] -> Fill(ST, evtwt) ;   
  h1_["npv_noweight"] -> Fill(*h_npv.product(), *h_evtwtGen.product()); 
  h1_["npv"] -> Fill(*h_npv.product(), evtwt);
  h1_["met"] -> Fill(goodMet.at(0).getFullPt(), evtwt);
  h1_["metPhi"] -> Fill(goodMet.at(0).getFullPhi(), evtwt);

  //lepton specfic properties
  if ( zdecayMode_ == "zmumu" ){       
    for(int l=0; l<2; ++l){
      h1_["pt_"+lep+Form("%d", l+1)]  -> Fill(goodMuons.at(l).getPt(), evtwt) ; 
      h1_["eta_"+lep+Form("%d", l+1)]  -> Fill(goodMuons.at(l).getEta(), evtwt) ; 
    } 
    h1_["dr_mumu"]-> Fill( (goodMuons.at(0).getP4()).DeltaR(goodMuons.at(1).getP4()), evtwt );
  }
  else if (zdecayMode_ == "zelel" ) {
    for(int l=0; l<2; ++l){
      h1_["pt_"+lep+Form("%d", l+1)]   -> Fill(goodElectrons.at(l).getPt(), evtwt) ; 
      h1_["eta_"+lep+Form("%d", l+1)]  -> Fill(goodElectrons.at(l).getEta(), evtwt) ; 
    } 
    h1_["dr_elel"]-> Fill( (goodElectrons.at(0).getP4()).DeltaR(goodElectrons.at(1).getP4()), evtwt );
  }
  //ak4 jet plots
  for(int j=0; j<3; ++j){
    h1_[Form("ptak4jet%d", j+1)]  -> Fill(goodAK4Jets.at(j).getPt(), evtwt) ; 
    h1_[Form("etaak4jet%d", j+1)] -> Fill(goodAK4Jets.at(j).getEta(), evtwt) ;
    h1_[Form("cvsak4jet%d", j+1)] -> Fill(goodAK4Jets.at(j).getCSV(), evtwt) ;
  }
  h1_["phi_jet1MET"] -> Fill( (goodAK4Jets.at(0).getP4()).DeltaPhi(goodMet.at(0).getP4()), evtwt);

  // fill the b-tagging plots and efficiency maps
  h1_["nbjets"] -> Fill(goodBTaggedAK4Jets.size(), evtwt) ;
  h1_["ptbjetleading"] -> Fill(goodBTaggedAK4Jets.at(0).getPt(), evtwt) ;
  h1_["etabjetleading"] -> Fill(goodBTaggedAK4Jets.at(0).getEta(), evtwt) ;

  for (vlq::Jet jet : goodAK4Jets) {
    if ( abs(jet.getHadronFlavour()) == 5) h2_["pt_eta_b_all"] -> Fill(jet.getPt(), jet.getEta()) ; 
    else if ( abs(jet.getHadronFlavour()) == 4) h2_["pt_eta_c_all"] -> Fill(jet.getPt(), jet.getEta()) ; 
    else if ( abs(jet.getHadronFlavour()) == 0) h2_["pt_eta_l_all"] -> Fill(jet.getPt(), jet.getEta()) ; 
  }

  for (vlq::Jet jet : goodBTaggedAK4Jets) {
    if ( abs(jet.getHadronFlavour()) == 5) h2_["pt_eta_b_btagged"] -> Fill(jet.getPt(), jet.getEta()) ; 
    else if ( abs(jet.getHadronFlavour()) == 4) h2_["pt_eta_c_btagged"] -> Fill(jet.getPt(), jet.getEta()) ; 
    else if ( abs(jet.getHadronFlavour()) == 0) h2_["pt_eta_l_btagged"] -> Fill(jet.getPt(), jet.getEta()) ; 
  }

  // fill the additional plots
  h1_["nak8"] -> Fill(goodAK8Jets.size(), evtwt) ;
  h1_["nwjet"] -> Fill(goodWTaggedJets.size(), evtwt) ; 
  h1_["nhjet"] -> Fill(goodHTaggedJets.size(), evtwt) ; 
  h1_["ntjet"] -> Fill(goodTopTaggedJets.size(), evtwt) ; 

  if (goodAK8Jets.size() > 0) {
    h1_["ptak8leading"] -> Fill((goodAK8Jets.at(0)).getPt(), evtwt) ; 
    h1_["etaak8leading"] -> Fill((goodAK8Jets.at(0)).getEta(), evtwt) ;
    h1_["mak8leading"] -> Fill((goodAK8Jets.at(0)).getMass(), evtwt) ; 
    h1_["trimmedmak8leading"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass(), evtwt) ;
    h1_["prunedmak8leading"] -> Fill((goodAK8Jets.at(0)).getPrunedMass(), evtwt) ;
    h1_["softdropmak8leading"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass(), evtwt) ;
  }
  if (goodAK8Jets.size() > 1) {
    h1_["ptak82nd"] -> Fill((goodAK8Jets.at(1)).getPt(), evtwt) ; 
    h1_["etaak82nd"] -> Fill((goodAK8Jets.at(1)).getEta(), evtwt) ;
    h1_["mak82nd"] -> Fill((goodAK8Jets.at(1)).getMass(), evtwt) ; 
    h1_["trimmedmak82nd"] -> Fill((goodAK8Jets.at(1)).getTrimmedMass(), evtwt) ;
    h1_["prunedmak82nd"] -> Fill((goodAK8Jets.at(1)).getPrunedMass(), evtwt) ;
    h1_["softdropmak82nd"] -> Fill((goodAK8Jets.at(1)).getSoftDropMass(), evtwt) ;
  }

  //// Make B->bZ and T->tZ->bWZ candidates
  TLorentzVector tp_p4, bp_p4;
  tp_p4.SetPtEtaPhiM(0,0,0,0);
  bp_p4.SetPtEtaPhiM(0,0,0,0);

  if (goodTopTaggedJets.size() > 0 && zll.size()>0) {
    tp_p4 = zll.at(0).getP4() + goodTopTaggedJets.at(0).getP4() ;
  }
  else if ( goodWTaggedJets.size() > 0 && goodBTaggedAK4Jets.size() > 0  && zll.size()>0 ) { 
    tp_p4 = zll.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() + goodWTaggedJets.at(0).getP4() ;
  }
  else if ( goodBTaggedAK4Jets.size() > 0 && zll.size()>0 && goodAK8Jets.size()>0) {    
    tp_p4 = zll.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() + goodAK8Jets.at(0).getP4() ; 
  }
  else if ( goodBTaggedAK4Jets.size() > 0 && zll.size()>0 ){
    bp_p4 = zll.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() ; 
  }

  h1_["ptTprime"]->Fill(tp_p4.Pt(), evtwt) ; 
  h1_["yTprime"] ->Fill(tp_p4.Rapidity(), evtwt) ; 
  h1_["mTprime"] ->Fill(tp_p4.Mag(), evtwt) ; 

  h1_["ptBprime"]->Fill(bp_p4.Pt(), evtwt) ; 
  h1_["yBprime"] ->Fill(bp_p4.Rapidity(), evtwt) ; 
  h1_["mBprime"] ->Fill(bp_p4.Mag(), evtwt) ;

  //Do mass reconstruction
  MassReco reco;

  TLorentzVector lep1, lep2, Leptons;
  if (zdecayMode_ == "zelel"){
    lep1 = goodElectrons.at(0).getP4();
    lep2 = goodElectrons.at(1).getP4();
  }
  else if (zdecayMode_ == "zmumu"){
    lep1 = goodMuons.at(0).getP4();
    lep2 = goodMuons.at(1).getP4();
  }
  Leptons = lep1 + lep2;
  //TLorentzVector Leptons = zll.at(0).getP4();

  if (optimizeReco_ && *h_evttype.product() != "EvtType_Data"){

    GenParticleCollection genPartsInfo;
    genPartsInfo = genpart(evt) ;
    // Declare TLorentzVectors to fill with genParticles
    TLorentzVector bGen, bbarGen, q1, q2;// Z1, Z2;
    TLorentzVector qJet, qbarJet, bJet, bbarJet;
    TLorentzVector had_bjet, lep_bjet, had_bGen, lep_bGen;
    bGen = reco.getGen(genPartsInfo, 5, 8000002);
    bbarGen = reco.getGen(genPartsInfo, -5, 8000002);
    q1 = reco.getGen(genPartsInfo, 1, 5, 8000002);
    q2 = reco.getGen(genPartsInfo, -5, -1, 8000002);

    qJet = reco.getMatchedJet(q1, goodAK4Jets, 0.3);
    qbarJet = reco.getMatchedJet(q2, goodAK4Jets, 0.3);
    bJet = reco.getMatchedJet(bGen, goodAK4Jets, 0.3);
    bbarJet = reco.getMatchedJet(bbarGen, goodAK4Jets, 0.3);

    //Choose charge of b (Change based on B' mass)
    double bcheck = abs((bGen + q1 + q2).M() - vlqMass_);
    double bbarcheck = abs((bbarGen + q1 + q2).M() - vlqMass_);
    if (bcheck < bbarcheck){
      had_bGen = bGen;
      lep_bGen = bbarGen;
      had_bjet = bJet;
      lep_bjet = bbarJet;
    }
    else {
      had_bGen = bbarGen;
      lep_bGen = bGen;
      had_bjet = bbarJet;
      lep_bjet = bJet;
    }
    double genZ = reco.findInvMass(q1, q2);
    double genB = reco.findInvMass(q1, q2, had_bGen);
    double ZJet = reco.findInvMass(qJet, qbarJet);
    double hadBJet = reco.findInvMass(qJet, qbarJet, had_bjet);
    double lepBJet = reco.findInvMass(lep1, lep2, lep_bjet);

    h1_["genZ"]->Fill(genZ, evtwt);
    h1_["genBMass"] -> Fill(genB, evtwt);
    h1_["ZJetMass"]->Fill(ZJet,evtwt);
    h1_["hadBJetMass"] ->Fill(hadBJet, evtwt);
    h1_["lepBJetMass"] ->Fill(lepBJet, evtwt);
  }
  pair<double, double> chi2_result;
  if (goodAK4Jets.size() > 4)
    chi2_result = reco.doReco(goodAK4Jets, bosonMass_, Leptons);
  //else if (goodAK8Jets.size() > 0)
  //chi2_result = reco.doReco(goodAK4Jets, goodAK8Jets.at(0).getP4(), bosonMass_, Leptons);
  else{
    chi2_result.first = -999;
    chi2_result.second = -999;
  }

  //Fill Histograms
  h1_["ZJetMasslep"] ->Fill(Leptons.M(), evtwt);
  h1_["chi2_chi"] ->Fill(chi2_result.first, evtwt);
  h1_["sqrtChi2"] ->Fill(sqrt(chi2_result.first), evtwt);
  h1_["chi2_mass"] ->Fill(chi2_result.second, evtwt);

  std::auto_ptr<vlq::JetCollection> ptr_tjets( new vlq::JetCollection(goodTopTaggedJets) ) ; 
  std::auto_ptr<vlq::JetCollection> ptr_wjets( new vlq::JetCollection(goodWTaggedJets) ) ; 
  std::auto_ptr<vlq::JetCollection> ptr_bjets( new vlq::JetCollection(goodBTaggedAK4Jets ) ) ; 
  std::auto_ptr<vlq::JetCollection> ptr_jets ( new vlq::JetCollection(goodAK4Jets ) ) ; 
  std::auto_ptr<vlq::CandidateCollection> ptr_zllcands ( new vlq::CandidateCollection(zll) ) ; 

  evt.put(ptr_tjets, "tjets") ; 
  evt.put(ptr_wjets, "wjets") ; 
  evt.put(ptr_bjets, "bjets") ; 
  evt.put(ptr_jets , "jets")  ; 
  evt.put(ptr_zllcands , "zllcands")  ; 

  return true ; 
}

// ------------ method called once each job just before starting event loop  ------------
void OS2LAna::beginJob() {
  if(zdecayMode_ == "zmumu") {lep = "mu";}
  else if ( zdecayMode_ == "zelel") {lep = "el";}
  else edm::LogError("OS2LAna::beginJob") << " >>>> WrongleptonType: " << lep << " Check lep name !!!" ;

  if (filterSignal_){h1_["signalEvts"] = fs->make<TH1D>("signalEvts", "signalEvts", 2, 0.5, 2.5) ;}
  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 8, 0.5, 8.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1, "Trig.+l^{+}l^{-}") ;
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2, "75 #lt M(l^{+}l^{-}) #lt 105") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3, "N(AK4) #geq 3") ;
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4, "H_{T} #geq 150") ;
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5, "leading jet pt > 100") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6, "2nd jet pt > 50") ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7, "N(b jet) #geq 1") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8, "S_{T} #geq 1000") ; 
  //h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9, "N(AK8) #geq 1") ; //this is not the event cut

  TFileDirectory pre = fs->mkdir ("pre");
  TFileDirectory sig = fs->mkdir ("sig");
  TFileDirectory cnt = fs->mkdir ("cnt");
  TFileDirectory *bookDir[3]; bookDir[0] = &pre; bookDir[1] = &cnt; bookDir[2] = &sig;
  std::vector<string> suffix = {"_pre", "_cnt", ""};

  for (int i=0; i<3; i++){
    h1_[("npv_noweight"+suffix[i]).c_str()] = bookDir[i]->make<TH1D>( ("npv_noweight"+suffix[i]).c_str(), ";N(PV);;", 51, -0.5, 50.5) ; 
    h1_[("npv"+suffix[i]).c_str()]  =  bookDir[i]->make<TH1D>( ("npv"+suffix[i]).c_str(), ";N(PV);;", 51, -0.5, 50.5) ; 
    h1_[("nak4"+suffix[i]).c_str()] =  bookDir[i]->make<TH1D>( ("nak4"+suffix[i]).c_str(), ";N(AK4 jets);;" , 21, -0.5, 20.5) ;
    h1_[("ht"+suffix[i]).c_str()]   =  bookDir[i]->make<TH1D>( ("ht"+suffix[i]).c_str(), ";H_{T} (AK4 jets) [GeV]", 100, 0., 4000.) ;
    h1_[("st"+suffix[i]).c_str()]   =  bookDir[i]->make<TH1D>( ("st"+suffix[i]).c_str() ,";S_{T} [GeV]", 100, 0., 4000.) ;
    h1_[("met"+suffix[i]).c_str()]  =  bookDir[i]->make<TH1D>( ("met"+suffix[i]).c_str(), "MET [GeV]", 100, 0., 1000.);
    h1_[("metPhi"+suffix[i]).c_str()]  =  bookDir[i]->make<TH1D>( ("metPhi"+suffix[i]).c_str(), "#Phi(MET)", 20, -5., 5.);

    //jets
    for(int j=1; j<4; ++j){
      string jetPtName = Form("ptak4jet%d", j)+suffix[i]; string jetPtTitle  = Form(";p_{T}(%d leading AK4 jet) [GeV];;",j);
      h1_[jetPtName.c_str()] = bookDir[i]->make<TH1D>(jetPtName.c_str(), jetPtTitle.c_str(), 50, 0., 1000.) ;
      string jetEtaName = Form("etaak4jet%d", j)+suffix[i]; string jetEtaTitle  = Form(";#eta(%d leading AK4 jet) ;;",j);
      h1_[jetEtaName.c_str()] = bookDir[i]->make<TH1D>(jetEtaName.c_str(), jetEtaTitle.c_str(), 80 ,-4. ,4.) ;
      string jetCVSName = Form("cvsak4jet%d", j)+suffix[i]; string jetCVSTitle  = Form(";CVS(%d leading AK4 jet) ;;",j); 
      h1_[jetCVSName.c_str()] = bookDir[i]->make<TH1D>(jetCVSName.c_str(), jetCVSTitle.c_str(), 50 ,0. ,1.) ;
    }
    string jet1METPhiName = "phi_jet1MET"+suffix[i];
    h1_[jet1METPhiName.c_str()] = bookDir[i]->make<TH1D>(jet1METPhiName.c_str(), ";#Phi(leading jet, MET)", 20, -5., 5.) ;

    //leptons
    string mass_Z = "mass_z"+lep+lep+suffix[i];
    h1_[mass_Z.c_str()] = bookDir[i]->make<TH1D>(mass_Z.c_str(), ";M(Z#rightarrow l^{+}l^{-}) [GeV]", 100, 20., 220.) ;
    string dr_ll = "dr_"+lep+lep+suffix[i];  
    h1_[dr_ll.c_str()] = bookDir[i]->make<TH1D>(dr_ll.c_str(), ";#DeltaR(l^{+}l^{-});;", 40, 0., 4.) ;
    string pt_Z = "pt_z"+lep+lep+suffix[i];
    h1_[pt_Z.c_str()] = bookDir[i]->make<TH1D>(pt_Z.c_str(), ";p_{T} (Z#rightarrow l^{+}l^{-}) [GeV]", 50, 0., 1000.) ; 
    for(int l=1; l<3; ++l){
      string lepPtName = "pt_"+lep+Form("%d",l)+suffix[i]; string lepPtTitle = Form(";p_{T}(%d leading lepton) [GeV];;",l);
      h1_[lepPtName.c_str()] = bookDir[i]->make<TH1D>(lepPtName.c_str(), lepPtTitle.c_str(), 50, 0., 500.) ;
      string lepEtaName = "eta_"+lep+Form("%d",l)+suffix[i]; string lepEtaTitle  = Form(";#eta(%d leading lepton) ;;",l);
      h1_[lepEtaName.c_str()] = bookDir[i]->make<TH1D>(lepEtaName.c_str(), lepEtaTitle.c_str(), 80, -4., 4.) ;
    }
  }

  //additional plots
  h1_["nbjets"] = sig.make<TH1D>("nbjets", ";N(b jets);;" , 11, -0.5,10.5) ; 
  h1_["ptbjetleading"]  = sig.make<TH1D>("ptbjetleading", ";p_{T}(leading b jet) [GeV];;" , 50, 0., 1000.) ; 
  h1_["etabjetleading"] = sig.make<TH1D>("etabjetleading", ";#eta(leading b jet);;" , 80 ,-4. ,4.) ;

  h1_["nak8"] = sig.make<TH1D>("nak8", ";N(AK8 jets);;" , 11, -0.5,10.5) ; 
  h1_["nwjet"] = sig.make<TH1D>("nwjet", ";N(W jets );;" , 6, -0.5,5.5) ; 
  h1_["nhjet"] = sig.make<TH1D>("nhjet", ";N(H jets );;" , 6, -0.5,5.5) ; 
  h1_["ntjet"] = sig.make<TH1D>("ntjet", ";N(top jets);;" , 6, -0.5,5.5) ; 

  h1_["ptak8leading"]  = sig.make<TH1D>("ptak8leading", ";p_{T}(leading AK8 jet) [GeV];;" , 50, 0., 1000.) ; 
  h1_["etaak8leading"] = sig.make<TH1D>("etaak8leading", ";#eta(leading AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak8leading"] = sig.make<TH1D>("mak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak8leading"] = sig.make<TH1D>("prunedmak8leading", ";M(pruned leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak8leading"] = sig.make<TH1D>("trimmedmak8leading", ";M(trimmed leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak8leading"] = sig.make<TH1D>("softdropmak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak82nd"]  = sig.make<TH1D>("ptak82nd", ";p_{T}(2nd AK8 jet) [GeV];;" , 50, 0., 1000.) ; 
  h1_["etaak82nd"] = sig.make<TH1D>("etaak82nd", ";#eta(2nd AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak82nd"] = sig.make<TH1D>("mak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak82nd"] = sig.make<TH1D>("prunedmak82nd", ";M(pruned 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak82nd"] = sig.make<TH1D>("trimmedmak82nd", ";M(trimmed 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak82nd"] = sig.make<TH1D>("softdropmak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ;

  h1_["ptTprime"]  = sig.make<TH1D>("ptTprime", ";p_{T}(T quark) [GeV];;" , 100, 0., 2000.) ; 
  h1_["yTprime"] = sig.make<TH1D>("yTprime", ";y(T quark);;" , 40 ,-4. ,4.) ; 
  h1_["mTprime"] = sig.make<TH1D>("mTprime", ";M(T quark) [GeV];;" ,100 ,0., 2000.) ; 

  h1_["ptBprime"]  = sig.make<TH1D>("ptBprime", ";p_{T}(B quark) [GeV];;" , 100, 0., 2000.) ; 
  h1_["yBprime"] = sig.make<TH1D>("yBprime", ";y(B quark);;" , 40 ,-4. ,4.) ; 
  h1_["mBprime"] = sig.make<TH1D>("mBprime", ";M(B quark) [GeV];;" ,100 ,0., 2000.) ; 

  // b-tagging efficiency maps:
  h2_["pt_eta_b_all"] = fs->make<TH2D>("pt_eta_b_all", "b flavoured jets;p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_c_all"] = fs->make<TH2D>("pt_eta_c_all", "b flavoured jets;p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_l_all"] = fs->make<TH2D>("pt_eta_l_all", "b flavoured jets;p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 

  h2_["pt_eta_b_btagged"] = fs->make<TH2D>("pt_eta_b_btagged", "b flavoured jets (b-tagged);p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_c_btagged"] = fs->make<TH2D>("pt_eta_c_btagged", "b flavoured jets (b-tagged);p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_l_btagged"] = fs->make<TH2D>("pt_eta_l_btagged", "b flavoured jets (b-tagged);p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 

  // plots to study B mass recontruction
  if (optimizeReco_){
    h1_["genZ"] = sig.make<TH1D>("genZ", ";M (Gen Z Boson) [GeV];;", 20, 0., 200.);
    h1_["genBMass"] = sig.make<TH1D>("genBMass", ";M(Gen B quark) [GeV];;", 100, 800., 1200);
    h1_["ZJetMass"] = sig.make<TH1D>("ZJetMass", ";JetM (Hadronic Z Boson) [GeV];;", 20, 0., 200.);
    h1_["hadBJetMass"] = sig.make<TH1D>("BJetMass", ";JetM (Hadronic B quark) [GeV];;", 100, 500., 1500.);
    h1_["lepBJetMass"] = sig.make<TH1D>("BJetMasslep", ";M (B Jet Leptonic);;", 100, 500., 1500.);
  }

  h1_["ZJetMasslep"] = sig.make<TH1D>("ZJetMasslep", ";M (Z Jet Leptonic);;", 20, 0., 200.);
  h1_["chi2_chi"] = sig.make<TH1D>("chi2_chi", ";#chi^{2};;", 100, 0., 500.);
  h1_["sqrtChi2"] = sig.make<TH1D>("sqrtChi2", ";#chi;;", 100, 0., 500.);
  h1_["chi2_mass"] = sig.make<TH1D>("chi_mass", ";M_{#chi^{2}}(B);;", 180, 200., 2000.);

  //electrons specific varaibles in EE and EB at preselection level
  if (zdecayMode_ == "zelel" && additionalPlots_){
    h1_["Eta_EB_el_pre"] = pre.make<TH1D>("Eta_EB_el_pre", ";Eta (EB);;", 100,-4,4) ;
    h1_["Eta_EE_el_pre"] = pre.make<TH1D>("Eta_EE_el_pre", ";Eta (EE);;", 100,-4,4) ;
    h1_["Iso03_EB_el_pre"] = pre.make<TH1D>("Iso03_EB_el_pre", ";Iso03 (EB);;", 100,0,0.3) ;
    h1_["Iso03_EE_el_pre"] = pre.make<TH1D>("Iso03_EE_el_pre", ";Iso03 (EE);;", 100,0,0.3) ;
    h1_["dEtaIn_EB_el_pre"] = pre.make<TH1D>("dEtaIn_EB_el_pre", ";dEtaIn (EB);;", 200,-0.05,0.05) ;
    h1_["dEtaIn_EE_el_pre"] = pre.make<TH1D>("dEtaIn_EE_el_pre", ";dEtaIn (EE);;", 200,-0.05,0.05) ;
    h1_["dPhiIn_EB_el_pre"] = pre.make<TH1D>("dPhiIn_EB_el_pre", ";dPhiIn (EB);;", 100,-0.2,0.2) ;
    h1_["dPhiIn_EE_el_pre"] = pre.make<TH1D>("dPhiIn_EE_el_pre", ";dPhiIn (EE);;", 100,-0.2,0.2);
    h1_["Dz_EB_el_pre"] = pre.make<TH1D>("Dz_EB_el_pre",";dZ (EB);;", 200,-0.1,0.1) ;
    h1_["Dz_EE_el_pre"] = pre.make<TH1D>("Dz_EE_el_pre", ";dZ (EE);;", 200,-0.4,0.4) ;
    h1_["D0_EB_el_pre"] = pre.make<TH1D>("D0_EB_el_pre", ";d0 (EB);;", 100,-0.1,0.1) ;
    h1_["D0_EE_el_pre"] = pre.make<TH1D>("D0_EE_el_pre", ";d0 (EE);;", 100,-0.1,0.1) ;
  }

}

double OS2LAna::GetDYNLOCorr(const double dileppt) {

  std::unique_ptr<TFile >file_DYNLOCorr = std::unique_ptr<TFile>(new TFile(fname_DYNLOCorr_.c_str())) ;
  std::unique_ptr<TF1>fun_DYNLOCorr = std::unique_ptr<TF1>(dynamic_cast<TF1*>(file_DYNLOCorr->Get(funname_DYNLOCorr_.c_str()))) ; 
  double EWKNLOkfact = fun_DYNLOCorr->Eval(dileppt);
  return EWKNLOkfact; 

}

void OS2LAna::endJob() {

  return ; 
}

DEFINE_FWK_MODULE(OS2LAna);
