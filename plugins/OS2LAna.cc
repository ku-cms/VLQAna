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
//           21 Mar 2016 17:11 CDT
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

    // ----------member data ---------------------------
    edm::InputTag l_hltdecision                  ;
    edm::InputTag l_evttype                      ;
    edm::InputTag l_evtwtGen                     ;
    edm::InputTag l_evtwtPV                      ;
    edm::InputTag l_npv                          ;
    edm::ParameterSet DilepCandParams_           ; 
    edm::ParameterSet ZCandParams_               ; 
    edm::ParameterSet BoostedZCandParams_        ; 
    edm::ParameterSet GenHSelParams_             ; 
    const double STMin_                          ; 
    const bool filterSignal_                     ;
    const std::string signalType_                ;
    const std::string zdecayMode_                ;
    const bool applyLeptonSFs_                   ;
    ApplyLeptonSFs lepsfs                        ; 
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
};

using namespace std; 

OS2LAna::OS2LAna(const edm::ParameterSet& iConfig) :
  l_hltdecision           (iConfig.getParameter<edm::InputTag>     ("hltdecision")),
  l_evttype               (iConfig.getParameter<edm::InputTag>     ("evttype")),
  l_evtwtGen              (iConfig.getParameter<edm::InputTag>     ("evtwtGen")),
  l_evtwtPV               (iConfig.getParameter<edm::InputTag>     ("evtwtPV")),
  l_npv                   (iConfig.getParameter<edm::InputTag>     ("npv")),
  DilepCandParams_        (iConfig.getParameter<edm::ParameterSet> ("DilepCandParams")),
  ZCandParams_            (iConfig.getParameter<edm::ParameterSet> ("ZCandParams")),
  BoostedZCandParams_     (iConfig.getParameter<edm::ParameterSet> ("BoostedZCandParams")),
  GenHSelParams_          (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
  STMin_                  (iConfig.getParameter<double>            ("STMin")), 
  filterSignal_           (iConfig.getParameter<bool>              ("filterSignal")), 
  signalType_             (iConfig.getParameter<std::string>       ("signalType")), 
  zdecayMode_             (iConfig.getParameter<std::string>       ("zdecayMode")), 
  applyLeptonSFs_         (iConfig.getParameter<bool>              ("applyLeptonSFs")), 
  lepsfs                  (iConfig.getParameter<edm::ParameterSet> ("lepsfsParams")),
  muonmaker               (iConfig.getParameter<edm::ParameterSet> ("muselParams")),
  electronmaker           (iConfig.getParameter<edm::ParameterSet> ("elselParams")), 
  jetAK4maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK4selParams")), 
  jetAK4BTaggedmaker      (iConfig.getParameter<edm::ParameterSet> ("jetAK4BTaggedselParams")), 
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams")), 
  jetWTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetWTaggedselParams")), 
  jetTopTaggedmaker       (iConfig.getParameter<edm::ParameterSet> ("jetTopTaggedselParams")),
  lep                     (iConfig.getParameter<std::string>       ("lep"))
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

  Handle<bool>h_hltdecision ; evt.getByLabel(l_hltdecision, h_hltdecision) ; 
  Handle<string>h_evttype   ; evt.getByLabel(l_evttype  , h_evttype  ) ; 
  Handle<double>h_evtwtGen  ; evt.getByLabel(l_evtwtGen, h_evtwtGen) ; 
  Handle<double>h_evtwtPV   ; evt.getByLabel(l_evtwtPV,  h_evtwtPV ) ; 
  Handle<unsigned>h_npv     ; evt.getByLabel(l_npv, h_npv) ; 
  
  if(zdecayMode_ == "zmumu") {lep = "mu";}
  else if ( zdecayMode_ == "zele") {lep = "el";}

  if (filterSignal_ && *h_evttype.product()!=signalType_) return false ;
  const bool hltdecision(*h_hltdecision.product()) ; 
  double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 
    
  h1_["cutflow"] -> Fill(1, evtwt) ; 

  if ( !hltdecision ) return false; 
  
  h1_["cutflow"] -> Fill(2, evtwt) ; 
  h1_["npv_noreweight"] -> Fill(*h_npv.product(), *h_evtwtGen.product()); 
  h1_["npv"] -> Fill(*h_npv.product(), evtwt);
  
  vlq::MuonCollection goodMuons; 
  muonmaker(evt, goodMuons) ; 
  
  vlq::ElectronCollection goodElectrons; 
  electronmaker(evt, goodElectrons) ; 
  
  vlq::CandidateCollection dimuons, zmumu, zmumuBoosted, dielectrons, zelel, zelelBoosted ; 
  vlq::CandidateCollection zll, zllBoosted, dileptons;//generic collections

  DileptonCandsProducer dileptonsprod(DilepCandParams_) ; 
  dileptonsprod.operator()<vlq::ElectronCollection>(dielectrons, goodElectrons) ; 
  dileptonsprod.operator()<vlq::MuonCollection>(dimuons, goodMuons); 

  if (zdecayMode_ == "zmumu") {dileptons = dimuons; }
  else if (zdecayMode_ == "zelel") {dileptons = dielectrons;}
  
  if (dileptons.size() < 1) return false;  

  //apply lepton ID and Iso SF
  if (applyLeptonSFs_ && *h_evttype.product() != "EvtType_Data") {
     if ( zdecayMode_ == "zmumu" ){
        evtwt *= lepsfs(goodMuons.at(0).getPt(),goodMuons.at(0).getEta()) * lepsfs(goodMuons.at(1).getPt(), goodMuons.at(1).getEta() ) ;}
     else if ( zdecayMode_ == "zelel" ){ 
        evtwt *= lepsfs(goodElectrons.at(0).getPt(),goodElectrons.at(0).getEta()) * lepsfs(goodElectrons.at(1).getPt(), goodElectrons.at(1).getEta() ) ;}
  }

  //dilepton mass 
  for (auto idilepton : dileptons) h1_["mass_"+lep+lep] -> Fill(idilepton.getMass(), evtwt) ; 
  
  //lepton specfic properties
  if ( zdecayMode_ == "zmumu" ){       
     h1_["pt_leading_mu"] -> Fill(goodMuons.at(0).getPt(), evtwt) ; 
     h1_["eta_leading_mu"] -> Fill(goodMuons.at(0).getEta(), evtwt) ; 
     h1_["pt_2nd_mu"] -> Fill(goodMuons.at(1).getPt(), evtwt) ; 
     h1_["eta_2nd_mu"] -> Fill(goodMuons.at(1).getEta(), evtwt) ; 
     h1_["dr_mumu"] -> Fill ( (goodMuons.at(0).getP4()).DeltaR(goodMuons.at(1).getP4()) ,evtwt) ;        
  }
  else if (zdecayMode_ == "zelel" ) {
     h1_["pt_leading_el"] -> Fill(goodElectrons.at(0).getPt(), evtwt) ; 
     h1_["eta_leading_el"] -> Fill(goodElectrons.at(0).getEta(), evtwt) ; 
     h1_["pt_2nd_el"] -> Fill(goodElectrons.at(1).getPt(), evtwt) ; 
     h1_["eta_2nd_el"] -> Fill(goodElectrons.at(1).getEta(), evtwt) ; 
     h1_["dr_elel"] -> Fill ( (goodElectrons.at(0).getP4()).DeltaR(goodElectrons.at(1).getP4()) ,evtwt) ; 
     
     for  (unsigned int iele=0; iele<goodElectrons.size(); ++iele){
        float scEta = goodElectrons.at(iele).getscEta();
        if(fabs(scEta) <= 1.479){              
           h1_["Eta_EB_el"]-> Fill(goodElectrons.at(iele).getEta(), evtwt);            
           h1_["Iso03_EB_el"]->Fill(goodElectrons.at(iele).getIso03(), evtwt);
           h1_["dEtaIn_EB_el"]->Fill(goodElectrons.at(iele).getdEtaIn(), evtwt);
           h1_["dPhiIn_EB_el"]->Fill(goodElectrons.at(iele).getdPhiIn(), evtwt);
           h1_["Dz_EB_el"]->Fill(goodElectrons.at(iele).getDz(), evtwt);
           h1_["D0_EB_el"]->Fill(goodElectrons.at(iele).getD0(), evtwt);
        }
        else if  (fabs(scEta > 1.479) && fabs(scEta < 2.5)){
           h1_["Eta_EE_el"]->Fill(goodElectrons.at(iele).getEta(), evtwt);
           h1_["Iso03_EE_el"]->Fill(goodElectrons.at(iele).getIso03(), evtwt);
           h1_["dEtaIn_EE_el"]->Fill(goodElectrons.at(iele).getdEtaIn(), evtwt);
           h1_["dPhiIn_EE_el"]->Fill(goodElectrons.at(iele).getdPhiIn(), evtwt);
           h1_["Dz_EE_el"]->Fill(goodElectrons.at(iele).getDz(), evtwt);
           h1_["D0_EE_el"]->Fill(goodElectrons.at(iele).getD0(), evtwt);
        }
     }
  }
  
  CandidateFilter zllfilter(ZCandParams_) ; 
  zllfilter(dileptons, zll);

  //Z mass candidates
  h1_["nz"+lep+lep] -> Fill (zll.size(), evtwt);
  if(zll.size() > 0) h1_["cutflow"] -> Fill(3, evtwt) ;
  else return false ; 
  
  //Properties of Z candidates
  for (auto izll : zll) {
     h1_["mass_z"+lep+lep] -> Fill(izll.getMass(), evtwt) ; 
     h1_["pt_z"+lep+lep] -> Fill(izll.getPt(), evtwt) ; 
     h1_["y_z"+lep+lep] -> Fill(izll.getP4().Rapidity(), evtwt) ; 
  }
 
  //modify the Z pt to select only boosted Zs
  CandidateFilter boostedzllfilter(BoostedZCandParams_) ; 
  boostedzllfilter(dileptons, zllBoosted) ; 
  if(zllBoosted.size() > 0) h1_["cutflow"] -> Fill(4, evtwt) ;
  else return false ; 
  
  // jets
  vlq::JetCollection cleanAK4Jets, goodAK4Jets, goodBTaggedAK4Jets, goodAK8Jets, goodHTaggedJets, goodWTaggedJets, goodTopTaggedJets;
  jetAK4maker(evt, goodAK4Jets) ;
  
  //AK4 jet cleaning
  double dR_ak4jl = -100; bool fakeJet = false;  
  for (vlq::Jet& ijet : goodAK4Jets) {
     if (zdecayMode_ == "zmumu") {
        for  (unsigned int imu=0; imu<goodMuons.size(); ++imu){
           dR_ak4jl = ijet.getP4().DeltaR(goodMuons.at(imu).getP4());
           h1_["dR_muj"] -> Fill(dR_ak4jl);
           if (dR_ak4jl <= 0.3) {fakeJet = true; break;}
        }
     }
     else if (zdecayMode_ == "zelel"){ 
        for  (unsigned int iel=0; iel<goodElectrons.size(); ++iel){
           dR_ak4jl = ijet.getP4().DeltaR(goodElectrons.at(iel).getP4());
           h1_["dR_elj"] -> Fill(dR_ak4jl);
           if (dR_ak4jl <= 0.3) {fakeJet = true; break;}
        }
     }
     if(!fakeJet){cleanAK4Jets.push_back(ijet);}
  }
  
  HT htak4(cleanAK4Jets) ; 
  h1_["ht_zsel"] -> Fill(htak4.getHT(), evtwt) ; 
  h1_["npv_zsel"] -> Fill(*h_npv.product(), evtwt);
   
  jetAK4BTaggedmaker(evt, goodBTaggedAK4Jets) ; 
  //repeat the cleaning for b-jets?

  jetAK8maker(evt, goodAK8Jets); 
  jetWTaggedmaker(evt, goodWTaggedJets);
  jetHTaggedmaker(evt, goodHTaggedJets);
  jetTopTaggedmaker(evt, goodTopTaggedJets);
  
  h1_["nak4"] -> Fill(cleanAK4Jets.size(), evtwt) ; 
  h1_["nbjets"] -> Fill(goodBTaggedAK4Jets.size(), evtwt) ; 
  h1_["nak8"] -> Fill(goodAK8Jets.size(), evtwt) ; 
  h1_["nwjet"] -> Fill(goodWTaggedJets.size(), evtwt) ; 
  h1_["nhjet"] -> Fill(goodHTaggedJets.size(), evtwt) ; 
  h1_["ntjet"] -> Fill(goodTopTaggedJets.size(), evtwt) ; 

  if (cleanAK4Jets.size() > 2 ) h1_["cutflow"] -> Fill(5, evtwt) ; 
  else return false;
 
  h1_["ptak4leading"] -> Fill(cleanAK4Jets.at(0).getPt(), evtwt) ; 
  h1_["etaak4leading"] -> Fill(cleanAK4Jets.at(0).getEta(), evtwt) ;
  h1_["csvak4leading"] -> Fill(cleanAK4Jets.at(0).getCSV(), evtwt) ; 
  h1_["ptak42nd"] -> Fill(cleanAK4Jets.at(1).getPt(), evtwt) ; 
  h1_["etaak42nd"] -> Fill(cleanAK4Jets.at(1).getEta(), evtwt) ;
  h1_["csvak42nd"] -> Fill(cleanAK4Jets.at(1).getCSV(), evtwt) ;
  h1_["ptak43rd"] -> Fill(cleanAK4Jets.at(2).getPt(), evtwt) ; 
  h1_["etaak43rd"] -> Fill(cleanAK4Jets.at(2).getEta(), evtwt) ;
  h1_["csvak43rd"] -> Fill(cleanAK4Jets.at(2).getCSV(), evtwt) ; 
    
if ( goodBTaggedAK4Jets.size() > 0 ) {
    h1_["ptbjetleading"] -> Fill(goodBTaggedAK4Jets.at(0).getPt(), evtwt) ;
    h1_["etabjetleading"] -> Fill(goodBTaggedAK4Jets.at(0).getEta(), evtwt) ;
    h1_["cutflow"] -> Fill(6, evtwt) ;
  }
  else return false; 
 
  double ST = htak4.getHT() ;
  if (zdecayMode_ == "zmumu" && zmumuBoosted.size() > 0) ST += zmumuBoosted.at(0).getPt() ; 
  else if (zdecayMode_ == "zelel" && zelelBoosted.size() > 0) ST += zelelBoosted.at(0).getPt() ; 

  h1_["ht"] ->Fill(htak4.getHT(), evtwt) ; 
  h1_["st"] ->Fill(ST, evtwt) ; 

  if ( ST > STMin_ ) h1_["cutflow"] -> Fill(7, evtwt) ;  
  else return false ; 
  
  //require at lease one ak8 jet now  
  if ( goodAK8Jets.size() > 0 ) h1_["cutflow"] -> Fill(8, evtwt) ; 
  else return false ;
  
  h1_["ptak8leading"] -> Fill((goodAK8Jets.at(0)).getPt(), evtwt) ; 
  h1_["etaak8leading"] -> Fill((goodAK8Jets.at(0)).getEta(), evtwt) ;
  h1_["mak8leading"] -> Fill((goodAK8Jets.at(0)).getMass(), evtwt) ; 
  h1_["trimmedmak8leading"] -> Fill((goodAK8Jets.at(0)).getTrimmedMass(), evtwt) ;
  h1_["prunedmak8leading"] -> Fill((goodAK8Jets.at(0)).getPrunedMass(), evtwt) ;
  h1_["softdropmak8leading"] -> Fill((goodAK8Jets.at(0)).getSoftDropMass(), evtwt) ;
  if (goodAK8Jets.size() > 1) {
    h1_["ptak82nd"] -> Fill((goodAK8Jets.at(1)).getPt(), evtwt) ; 
    h1_["etaak82nd"] -> Fill((goodAK8Jets.at(1)).getEta(), evtwt) ;
    h1_["mak82nd"] -> Fill((goodAK8Jets.at(1)).getMass(), evtwt) ; 
    h1_["trimmedmak82nd"] -> Fill((goodAK8Jets.at(1)).getTrimmedMass(), evtwt) ;
    h1_["prunedmak82nd"] -> Fill((goodAK8Jets.at(1)).getPrunedMass(), evtwt) ;
    h1_["softdropmak82nd"] -> Fill((goodAK8Jets.at(1)).getSoftDropMass(), evtwt) ;
  }
  
  //fill the b-tag efficiency plots after full event selection  
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
  
  // additional cut flow bins to give an idea of boson and top tagged objects
  if ( goodWTaggedJets.size() > 0 ) h1_["cutflow"] -> Fill(9, evtwt) ;  
  if ( goodHTaggedJets.size() > 0 ) h1_["cutflow"] -> Fill(10, evtwt) ;  
  if ( goodTopTaggedJets.size() > 0 ) h1_["cutflow"] -> Fill(11, evtwt) ;  

  //Lets fill more histogram after final selection for optimization
  h1_["htSigR"] ->Fill(htak4.getHT(), evtwt) ; 
  h1_["stSigR"] ->Fill(ST, evtwt) ;   
  h1_["nwjetSigR"] -> Fill(goodWTaggedJets.size(), evtwt) ; 
  h1_["nhjetSigR"] -> Fill(goodHTaggedJets.size(), evtwt) ;   
  h1_["ntjetSigR"] -> Fill(goodTopTaggedJets.size(), evtwt) ;   
  
  //// Make B->bZ and T->tZ->bWZ candidates
  TLorentzVector tp_p4, bp_p4;
  tp_p4.SetPtEtaPhiM(0,0,0,0);
  bp_p4.SetPtEtaPhiM(0,0,0,0);

  if (goodTopTaggedJets.size() > 0) {
    if (zmumuBoosted.size()>0) tp_p4 = zmumuBoosted.at(0).getP4() + goodTopTaggedJets.at(0).getP4() ; 
    else if (zelelBoosted.size()>0) tp_p4 = zelelBoosted.at(0).getP4() + goodTopTaggedJets.at(0).getP4() ; 
  }
  else if ( goodWTaggedJets.size() > 0 && goodBTaggedAK4Jets.size() > 0 ) { 
    if (zmumuBoosted.size()>0) tp_p4 = zmumuBoosted.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() + goodWTaggedJets.at(0).getP4() ;
    else if (zelelBoosted.size()>0) tp_p4 = zelelBoosted.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() + goodWTaggedJets.at(0).getP4() ;
  }
  else if ( goodBTaggedAK4Jets.size() > 0 ) { 
    if (zmumuBoosted.size()>0) {
      tp_p4 = zmumuBoosted.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() + goodAK8Jets.at(0).getP4() ; 
      bp_p4 = zmumuBoosted.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() ; 
    }
    else if (zelelBoosted.size()>0) {
      tp_p4 = zelelBoosted.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() + goodAK8Jets.at(0).getP4() ; 
      bp_p4 = zelelBoosted.at(0).getP4() + goodBTaggedAK4Jets.at(0).getP4() ; 
    }
  }

  h1_["ptTprime"]->Fill(tp_p4.Pt(), evtwt) ; 
  h1_["yTprime"] ->Fill(tp_p4.Rapidity(), evtwt) ; 
  h1_["mTprime"] ->Fill(tp_p4.Mag(), evtwt) ; 

  h1_["ptBprime"]->Fill(bp_p4.Pt(), evtwt) ; 
  h1_["yBprime"] ->Fill(bp_p4.Rapidity(), evtwt) ; 
  h1_["mBprime"] ->Fill(bp_p4.Mag(), evtwt) ; 

  //vlq::CandidateCollection zllBoosted(zmumuBoosted.size()+zelelBoosted.size()) ;
  //for (vlq::Candidate cand : zmumuBoosted ) zllBoosted.push_back(cand) ; 
  //for (vlq::Candidate cand : zelelBoosted ) zllBoosted.push_back(cand) ; 

  std::auto_ptr<vlq::JetCollection> ptr_tjets( new vlq::JetCollection(goodTopTaggedJets) ) ; 
  std::auto_ptr<vlq::JetCollection> ptr_wjets( new vlq::JetCollection(goodWTaggedJets) ) ; 
  std::auto_ptr<vlq::JetCollection> ptr_bjets( new vlq::JetCollection(goodBTaggedAK4Jets ) ) ; 
  std::auto_ptr<vlq::JetCollection> ptr_jets ( new vlq::JetCollection(goodAK4Jets ) ) ; 
  std::auto_ptr<vlq::CandidateCollection> ptr_zllcands ( new vlq::CandidateCollection(zllBoosted) ) ; 

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
  else if ( zdecayMode_ == "zele") {lep = "el";}

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 12, 0.5, 12.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2, "Trig.+PV") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3, "Z(l^{+}l^{-})") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4, "p_{T}(Z)") ;
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5, "N(AK4)>2") ;
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6, "N(b jet)>0") ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7, "S_{T}") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8, "N(AK8)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9, "N(W jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(10,"N(H jet)>0") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(11,"N(top jet)>0") ; 

  h1_["npv_noreweight"] = fs->make<TH1D>("npv_noreweight", ";N(PV);;", 51, -0.5, 50.5) ; 
  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 
  
  h1_[("pt_leading_"+lep).c_str()] = fs->make<TH1D>(("pt_leading_"+lep).c_str(), ";p_{T} (leading #l^{#pm}) [GeV]", 50, 0., 500.) ;
  h1_[("eta_leading_"+lep).c_str()] = fs->make<TH1D>(("eta_leading_"+lep).c_str(), ";#eta (leading #l^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_[("pt_2nd_"+lep).c_str()] = fs->make<TH1D>(("pt_2nd_"+lep).c_str(), ";p_{T} (2nd #l^{#pm}) [GeV]", 50, 0., 500.) ;
  h1_[("eta_2nd_"+lep).c_str()] = fs->make<TH1D>(("eta_2nd_"+lep).c_str(), ";#eta (2nd #l^{#pm}) [GeV]", 80, -4., 4.) ;
  h1_[("dr_"+lep+lep).c_str()] = fs->make<TH1D>(("dr_"+lep+lep).c_str(), ";#DeltaR(#l^{+}#l^{-});;", 40, 0., 4.) ; 
  h1_[("mass_"+lep+lep).c_str()] = fs->make<TH1D>(("mass_"+lep+lep).c_str(), ";M(l^{+}l^{-}) [GeV]", 100, 20., 220.) ; 
  h1_[("mass_z"+lep+lep).c_str()] = fs->make<TH1D>(("mass_z"+lep+lep).c_str(), ";M(Z#rightarrow l^{+}l^{-}) [GeV]", 100, 20., 220.) ; 
  h1_[("pt_z"+lep+lep).c_str()] = fs->make<TH1D>(("pt_z"+lep+lep).c_str(), ";p_{T} (Z#rightarrow l^{+}l^{-}) [GeV]", 50, 0., 1000.) ; 
  h1_[("y_z"+lep+lep).c_str()] = fs->make<TH1D>(("y_z"+lep+lep).c_str(), ";y (Z#rightarrow e^{+}e^{-}) [GeV]", 80, -4., 4.) ; 
  h1_[("nz"+lep+lep).c_str()] = fs->make<TH1D>(("nz"+lep+lep).c_str(), ";N (Z#rightarrow l^{+}l^{-});;", 5, -0.5, 4.5) ; 
  h1_[("dR_"+lep+"j").c_str()] = fs->make<TH1D>(("dR_"+lep+"j").c_str(), ";#DeltaR(l,jet);;", 40, 0., 4.) ; 
  
  //electrons specific varaibles in EE and EB
  if (zdecayMode_ == "zelel" ){
     h1_["Eta_EB_el"] = fs->make<TH1D>("Eta_EB_el", ";Eta (EB);;", 100,-4,4) ;
     h1_["Eta_EE_el"] = fs->make<TH1D>("Eta_EE_el", ";Eta (EE);;", 100,-4,4) ;
     h1_["Iso03_EB_el"] = fs->make<TH1D>("Iso03_EB_el", ";Iso03 (EB);;", 100,0,0.3) ;
     h1_["Iso03_EE_el"] = fs->make<TH1D>("Iso03_EE_el", ";Iso03 (EE);;", 100,0,0.3) ;
     h1_["dEtaIn_EB_el"] = fs->make<TH1D>("dEtaIn_EB_el", ";dEtaIn (EB);;", 200,-0.05,0.05) ;
     h1_["dEtaIn_EE_el"] = fs->make<TH1D>("dEtaIn_EE_el", ";dEtaIn (EE);;", 200,-0.05,0.05) ;
     h1_["dPhiIn_EB_el"] = fs->make<TH1D>("dPhiIn_EB_el", ";dPhiIn (EB);;", 100,-0.2,0.2) ;
     h1_["dPhiIn_EE_el"] = fs->make<TH1D>("dPhiIn_EE_el", ";dPhiIn (EE);;", 100,-0.2,0.2);
     h1_["Dz_EB_el"] = fs->make<TH1D>("Dz_EB",";dZ (EB);;", 200,-0.1,0.1) ;
     h1_["Dz_EE_el"] = fs->make<TH1D>("Dz_EE", ";dZ (EE);;", 200,-0.4,0.4) ;
     h1_["D0_EB_el"] = fs->make<TH1D>("D0_EB", ";d0 (EB);;", 100,-0.1,0.1) ;
     h1_["D0_EE_el"] = fs->make<TH1D>("D0_EE", ";d0 (EE);;", 100,-0.1,0.1) ;
  }

  h1_["nak8"] = fs->make<TH1D>("nak8", ";N(AK8 jets);;" , 11, -0.5,10.5) ; 
  h1_["nak4"] = fs->make<TH1D>("nak4", ";N(AK4 jets);;" , 21, -0.5,20.5) ; 
  h1_["nbjets"] = fs->make<TH1D>("nbjets", ";N(b jets);;" , 11, -0.5,10.5) ; 
  h1_["nwjet"] = fs->make<TH1D>("nwjet", ";N(W jets );;" , 6, -0.5,5.5) ; 
  h1_["nhjet"] = fs->make<TH1D>("nhjet", ";N(H jets );;" , 6, -0.5,5.5) ; 
  h1_["ntjet"] = fs->make<TH1D>("ntjet", ";N(top jets);;" , 6, -0.5,5.5) ; 

  h1_["ptak8leading"]  = fs->make<TH1D>("ptak8leading", ";p_{T}(leading AK8 jet) [GeV];;" , 50, 0., 1000.) ; 
  h1_["etaak8leading"] = fs->make<TH1D>("etaak8leading", ";#eta(leading AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak8leading"] = fs->make<TH1D>("mak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak8leading"] = fs->make<TH1D>("prunedmak8leading", ";M(pruned leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak8leading"] = fs->make<TH1D>("trimmedmak8leading", ";M(trimmed leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak8leading"] = fs->make<TH1D>("softdropmak8leading", ";M(leading AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak82nd"]  = fs->make<TH1D>("ptak82nd", ";p_{T}(2nd AK8 jet) [GeV];;" , 50, 0., 1000.) ; 
  h1_["etaak82nd"] = fs->make<TH1D>("etaak82nd", ";#eta(2nd AK8 jet);;" , 80 ,-4. ,4.) ; 
  h1_["mak82nd"] = fs->make<TH1D>("mak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["prunedmak82nd"] = fs->make<TH1D>("prunedmak82nd", ";M(pruned 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["trimmedmak82nd"] = fs->make<TH1D>("trimmedmak82nd", ";M(trimmed 2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["softdropmak82nd"] = fs->make<TH1D>("softdropmak82nd", ";M(2nd AK8 jet) [GeV];;" ,100 ,0., 200.) ; 
  h1_["ptak4leading"] = fs->make<TH1D>("ptak4leading", ";p_{T}(leading AK4 jet);;" , 50, 0., 1000.) ;
  h1_["etaak4leading"] = fs->make<TH1D>("etaak4leading", ";#eta(leading AK4 jet);;" , 80 ,-4. ,4.) ; 
  h1_["csvak4leading"] = fs->make<TH1D>("csvak4leading", ";CSV (leading AK4 jet);;" ,50 ,0. ,1.) ; 
  h1_["ptak42nd"] = fs->make<TH1D>("ptak42nd", ";p_{T}(2nd AK4 jet);;" , 50, 0., 1000.) ;
  h1_["etaak42nd"] = fs->make<TH1D>("etaak42nd", ";#eta(2nd AK4 jet);;" , 80 ,-4. ,4.) ; 
  h1_["csvak42nd"] = fs->make<TH1D>("csvak42nd", ";CSV (2nd AK4 jet);;" ,50 ,0. ,1.) ; 
  h1_["ptak43rd"] = fs->make<TH1D>("ptak43rd", ";p_{T}(3rd AK4 jet);;" , 50, 0., 1000.) ;
  h1_["etaak43rd"] = fs->make<TH1D>("etaak43rd", ";#eta(3rd AK4 jet);;" , 80 ,-4. ,4.) ; 
  h1_["csvak43rd"] = fs->make<TH1D>("csvak43rd", ";CSV (3rd AK4 jet);;" ,50 ,0. ,1.) ; 
  h1_["ptbjetleading"]  = fs->make<TH1D>("ptbjetleading", ";p_{T}(leading b jet) [GeV];;" , 50, 0., 1000.) ; 
  h1_["etabjetleading"] = fs->make<TH1D>("etabjetleading", ";#eta(leading b jet);;" , 80 ,-4. ,4.) ; 

  h1_["ht_zsel"] = fs->make<TH1D>("ht_zsel" ,";H_{T} (AK4 jets) [GeV]", 100, 0., 2000.) ; 
  h1_["npv_zsel"] = fs->make<TH1D>("npv_zsel", ";N(PV);;", 51, -0.5, 50.5) ;
  h1_["ht"] = fs->make<TH1D>("ht" ,";H_{T} (AK4 jets) [GeV]", 200, 0., 4000.) ; 
  h1_["st"] = fs->make<TH1D>("st" ,";S_{T} [GeV]", 200, 0., 4000.) ; 

  h1_["htSigR"] = fs->make<TH1D>("htSigR" ,";H_{T} (AK4 jets) [GeV]", 200, 0., 4000.) ;
  h1_["stSigR"] = fs->make<TH1D>("stSigR" ,";S_{T} [GeV]", 200, 0., 4000.) ; 
  h1_["nwjetSigR"] = fs->make<TH1D>("nwjetSigR", ";N(W jets );;" , 6, -0.5,5.5) ; 
  h1_["nhjetSigR"] = fs->make<TH1D>("nhjetSigR", ";N(H jets );;" , 6, -0.5,5.5) ; 
  h1_["ntjetSigR"] = fs->make<TH1D>("ntjetSigR", ";N(top jets);;" , 6, -0.5,5.5) ; 

  h1_["ptTprime"]  = fs->make<TH1D>("ptTprime", ";p_{T}(T quark) [GeV];;" , 100, 0., 2000.) ; 
  h1_["yTprime"] = fs->make<TH1D>("yTprime", ";y(T quark);;" , 40 ,-4. ,4.) ; 
  h1_["mTprime"] = fs->make<TH1D>("mTprime", ";M(T quark) [GeV];;" ,100 ,0., 2000.) ; 

  h1_["ptBprime"]  = fs->make<TH1D>("ptBprime", ";p_{T}(B quark) [GeV];;" , 100, 0., 2000.) ; 
  h1_["yBprime"] = fs->make<TH1D>("yBprime", ";y(B quark);;" , 40 ,-4. ,4.) ; 
  h1_["mBprime"] = fs->make<TH1D>("mBprime", ";M(B quark) [GeV];;" ,100 ,0., 2000.) ; 

  h2_["pt_eta_b_all"] = fs->make<TH2D>("pt_eta_b_all", "b flavoured jets;p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_c_all"] = fs->make<TH2D>("pt_eta_c_all", "b flavoured jets;p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_l_all"] = fs->make<TH2D>("pt_eta_l_all", "b flavoured jets;p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 

  h2_["pt_eta_b_btagged"] = fs->make<TH2D>("pt_eta_b_btagged", "b flavoured jets (b-tagged);p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_c_btagged"] = fs->make<TH2D>("pt_eta_c_btagged", "b flavoured jets (b-tagged);p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
  h2_["pt_eta_l_btagged"] = fs->make<TH2D>("pt_eta_l_btagged", "b flavoured jets (b-tagged);p_{T} [GeV];#eta;", 50, 0., 1000., 80, -4, 4) ; 
}

void OS2LAna::endJob() {

  return ; 
}

DEFINE_FWK_MODULE(OS2LAna);
