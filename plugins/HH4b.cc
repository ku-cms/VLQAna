#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/HH4bTree.h"
#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/BTagSFUtils.h"
#include <TH1D.h>
#include <TTree.h>
#include <TF1.h>
#include <boost/math/special_functions/fpclassify.hpp>
#include <algorithm> 

class HH4b : public edm::EDFilter {
  public:
    explicit HH4b(const edm::ParameterSet&) ;
    ~HH4b() ; 
  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    bool passHiggsTagging(vlq::Jet jet) ; 

    // ----------member data ---------------------------
    edm::EDGetTokenT<int>           t_runno      ;
    edm::EDGetTokenT<int>           t_lumisec    ;
    edm::EDGetTokenT<int>           t_evtno      ;
    edm::EDGetTokenT<bool>          t_isData     ;
    edm::EDGetTokenT<double>        t_evtwtGen   ;
    edm::EDGetTokenT<double>        t_evtwtPV    ;
    edm::EDGetTokenT<double>        t_evtwtPVLow ;
    edm::EDGetTokenT<double>        t_evtwtPVHigh;
    edm::EDGetTokenT<double>        t_htHat      ;
    edm::EDGetTokenT<int>           t_npuTrue    ;
    edm::EDGetTokenT<vector<int>>   t_lhewtids   ;
    edm::EDGetTokenT<vector<double>>t_lhewts     ;
    edm::EDGetTokenT<bool>          t_hltdecision;
    edm::EDGetTokenT<unsigned>      t_npv        ;
    JetMaker     jetAK8maker                     ; 
    JetMaker     jetHTaggedmaker                 ; 
    const std::string  btageffFile_              ;
    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    EventInfoBranches selectedevt; 
    JetInfoBranches ak8jets ; 
    JetInfoBranches hjets ; 
    TTree* tree_ ; 
    const bool printEvtNo_;

    std::unique_ptr<BTagSFUtils> btagsfutils_ ; 

    std::ofstream outfile0b_ ; 
    std::ofstream outfile4b_ ; 

    static const double CSVv2L ; 
};

using namespace std; 

HH4b::HH4b(const edm::ParameterSet& iConfig) :
  t_runno         (consumes<int>           (iConfig.getParameter<edm::InputTag>("runno"      ))),   
  t_lumisec       (consumes<int>           (iConfig.getParameter<edm::InputTag>("lumisec"    ))),   
  t_evtno         (consumes<int>           (iConfig.getParameter<edm::InputTag>("evtno"      ))),   
  t_isData        (consumes<bool>          (iConfig.getParameter<edm::InputTag>("isData"     ))),   
  t_evtwtGen      (consumes<double>        (iConfig.getParameter<edm::InputTag>("evtwtGen"   ))),   
  t_evtwtPV       (consumes<double>        (iConfig.getParameter<edm::InputTag>("evtwtPV"    ))),   
  t_evtwtPVLow    (consumes<double>        (iConfig.getParameter<edm::InputTag>("evtwtPVLow" ))),   
  t_evtwtPVHigh   (consumes<double>        (iConfig.getParameter<edm::InputTag>("evtwtPVHigh"))),   
  t_htHat         (consumes<double>        (iConfig.getParameter<edm::InputTag>("htHat"      ))),   
  t_npuTrue       (consumes<int>           (iConfig.getParameter<edm::InputTag>("npuTrue"    ))),   
  t_lhewtids      (consumes<vector<int>>   (iConfig.getParameter<edm::InputTag>("lhewtids"   ))),   
  t_lhewts        (consumes<vector<double>>(iConfig.getParameter<edm::InputTag>("lhewts"     ))),   
  t_hltdecision   (consumes<bool>          (iConfig.getParameter<edm::InputTag>("hltdecision"))),   
  t_npv           (consumes<unsigned>      (iConfig.getParameter<edm::InputTag>("npv"        ))),   
  jetAK8maker     (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams"),consumesCollector()), 
  jetHTaggedmaker (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams"),consumesCollector()),
  btageffFile_    (iConfig.getParameter<std::string>       ("btageffFile")), 
  printEvtNo_     (iConfig.getParameter<bool>("printEvtNo")), 
  btagsfutils_    (new BTagSFUtils())
{

}

HH4b::~HH4b() { }

const double HH4b::CSVv2L = 0.460;

bool HH4b::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<int>           h_runno         ; evt.getByToken(t_runno      , h_runno      ) ; 
  Handle<int>           h_lumisec       ; evt.getByToken(t_lumisec    , h_lumisec    ) ; 
  Handle<int>           h_evtno         ; evt.getByToken(t_evtno      , h_evtno      ) ; 
  Handle<bool>          h_isData        ; evt.getByToken(t_isData     , h_isData     ) ; 
  Handle<double>        h_evtwtGen      ; evt.getByToken(t_evtwtGen   , h_evtwtGen   ) ; 
  Handle<double>        h_evtwtPV       ; evt.getByToken(t_evtwtPV    , h_evtwtPV    ) ; 
  Handle<double>        h_evtwtPVLow    ; evt.getByToken(t_evtwtPVLow , h_evtwtPVLow ) ; 
  Handle<double>        h_evtwtPVHigh   ; evt.getByToken(t_evtwtPVHigh, h_evtwtPVHigh) ; 
  Handle<double>        h_htHat         ; evt.getByToken(t_htHat      , h_htHat      ) ; 
  Handle<int>           h_npuTrue       ; evt.getByToken(t_npuTrue    , h_npuTrue    ) ; 
  Handle<vector<int>>   h_lhewtids      ; evt.getByToken(t_lhewtids   , h_lhewtids   ) ; 
  Handle<vector<double>>h_lhewts        ; evt.getByToken(t_lhewts     , h_lhewts     ) ; 
  Handle<bool>          h_hltdecision   ; evt.getByToken(t_hltdecision, h_hltdecision) ; 
  Handle<unsigned>      h_npv           ; evt.getByToken(t_npv        , h_npv        ) ; 

  const int runno(*h_runno.product()) ; 
  const int lumisec(*h_lumisec.product()) ; 
  const int evtno(*h_evtno.product()) ; 
  const bool isData(*h_isData.product()) ; 
  const double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 
  const double htHat((*h_htHat.product())) ; 
  const bool hltdecision(*h_hltdecision.product()) ; 
  const unsigned npv(*h_npv.product()) ; 

  vlq::JetCollection  goodAK8Jets ;  
  jetAK8maker(evt, goodAK8Jets); 

  double cosThetaStar(goodAK8Jets.size()>= 2 ? abs(goodAK8Jets.at(0).getEta() -  goodAK8Jets.at(1).getEta()) : 999999) ; 
  TLorentzVector p4null; p4null.SetPtEtaPhiE(0,0,0,0); 
  TLorentzVector p4_jet0 = goodAK8Jets.size()>=1 ? goodAK8Jets.at(0).getP4() : p4null ;
  TLorentzVector p4_jet1 = goodAK8Jets.size()>= 2 ? goodAK8Jets.at(1).getP4() : p4null ;
  double invm(goodAK8Jets.size()>= 2 ? (p4_jet0 + p4_jet1).Mag() : -999999) ;
  double mj_0(goodAK8Jets.size()>= 2 ? goodAK8Jets.at(0).getPrunedMass() : -999999) ;
  double mj_1(goodAK8Jets.size()>= 2 ? goodAK8Jets.at(1).getPrunedMass() : -999999) ;
  double t21_0(goodAK8Jets.size()>= 2 ? 
      ( goodAK8Jets.at(0).getTau1() != 0 ? goodAK8Jets.at(0).getTau2() / goodAK8Jets.at(0).getTau1() : 999999) 
      : 999999 ) ; 
  double t21_1(goodAK8Jets.size()>= 2 ? 
      ( goodAK8Jets.at(1).getTau1() != 0 ? goodAK8Jets.at(1).getTau2() / goodAK8Jets.at(1).getTau1() : 999999) 
      : 999999 ) ; 
  int nsjBTagged(goodAK8Jets.size()>= 2 ? 
      goodAK8Jets.at(0).getNSubjetsBTaggedCSVL() + goodAK8Jets.at(1).getNSubjetsBTaggedCSVL() : -999999) ; 

  //// Event flags for cut flows
  const bool hltNPV   (hltdecision && (npv > 0)) ; 
  const bool ak8Pt    (goodAK8Jets.size()>= 2) ; 
  const bool ak8eta   (goodAK8Jets.size()>= 2 && ( abs(goodAK8Jets.at(0).getEta()) <= 2.4 && abs(goodAK8Jets.at(1).getEta()) <= 2.4) ); 
  const bool ak8DEta  (cosThetaStar < 1.3);
  const bool ak8Mjj   (invm > 1000.);
  const bool ak8Mj    ((mj_0 >= 105 && mj_0 <= 135) && (mj_1 >= 105 && mj_1 <= 135) ) ; 
  const bool ak8t21   ((t21_0 < 0.75 && t21_1 < 0.75) && (t21_0 < 0.6 || t21_1 < 0.6)); 
  const bool evt0b    (nsjBTagged == 0) ; 
  const bool evt1b    (nsjBTagged == 1) ; 
  const bool evt2b    (nsjBTagged == 2) ; 
  const bool evt3b    (nsjBTagged == 3) ; 
  const bool evt4b    (nsjBTagged == 4) ; 
  const bool evt3bHPHP(nsjBTagged == 3 && (t21_0 < 0.6 && t21_1 < 0.6));

  //// Cut flow
  h1_["cutflow"] -> Fill(1) ; 
  if ( hltNPV  ) h1_["cutflow"] -> Fill(2) ; 
  if ( hltNPV && ak8Pt  ) h1_["cutflow"] -> Fill(3) ; 
  if ( hltNPV && ak8Pt && ak8eta  ) h1_["cutflow"] -> Fill(4) ; 
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta ) h1_["cutflow"] -> Fill(5) ; 
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj  ) h1_["cutflow"] -> Fill(6) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj  ) h1_["cutflow"] -> Fill(7) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21  ) h1_["cutflow"] -> Fill(8) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt0b  ) h1_["cutflow"] -> Fill( 9) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt1b  ) h1_["cutflow"] -> Fill(10) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt2b  ) h1_["cutflow"] -> Fill(11) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt3b  ) h1_["cutflow"] -> Fill(12) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt4b  ) h1_["cutflow"] -> Fill(13) ;
  if ( hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt3bHPHP) h1_["cutflow"] -> Fill(14) ;

  if ( printEvtNo_ && hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt0b  ) {
    outfile0b_ << runno << " " << lumisec << " " << evtno << " " 
      << goodAK8Jets.at(0).getCSVSubjet0() << " " << goodAK8Jets.at(0).getCSVSubjet1() << " " 
      << goodAK8Jets.at(1).getCSVSubjet0() << " " << goodAK8Jets.at(1).getCSVSubjet1() << " " 
      << std::endl ; 
  }

  if ( printEvtNo_ && hltNPV && ak8Pt && ak8eta && ak8DEta && ak8Mjj && ak8Mj && ak8t21 && evt4b  ) {
    outfile4b_ << runno << " " << lumisec << " " << evtno << " " 
      << goodAK8Jets.at(0).getCSVSubjet0() << " " << goodAK8Jets.at(0).getCSVSubjet1() << " " 
      << goodAK8Jets.at(1).getCSVSubjet0() << " " << goodAK8Jets.at(1).getCSVSubjet1() << " " 
      << std::endl ; 
  }

  //// Event selection
  if ( !hltNPV || !ak8Pt ) return false; 

  h1_["npv"] -> Fill(*h_npv.product()); 

  //// Leading 2 jets pass Higgs tagging
  if ( !passHiggsTagging(goodAK8Jets.at(0)) || !passHiggsTagging(goodAK8Jets.at(1)) ) return false ;

  vlq::JetCollection goodHTaggedJets ;
  goodHTaggedJets.push_back(goodAK8Jets.at(0)); 
  goodHTaggedJets.push_back(goodAK8Jets.at(1)); 

  double btagsf(1) ;
  double btagsf_bcUp(1) ; 
  double btagsf_bcDown(1) ; 
  double btagsf_lUp(1) ; 
  double btagsf_lDown(1) ; 

  TLorentzVector p4_hjet0 = goodHTaggedJets.at(0).getP4() ; 
  TLorentzVector p4_hjet1 = goodHTaggedJets.at(1).getP4() ; 
  TLorentzVector p4_leading2hjets = p4_hjet0+p4_hjet1 ;

  selectedevt.deta_leading2hjets_ = cosThetaStar ; 
  selectedevt.minv_leading2hjets_ = p4_leading2hjets.Mag();
  selectedevt.minv_leading2hjets_subtr_ = p4_leading2hjets.Mag() 
    - (goodHTaggedJets.at(0).getMass() - 125.) 
    - (goodHTaggedJets.at(1).getMass() - 125.);
  selectedevt.pt_leading2hjets_ = p4_leading2hjets.Pt();
  selectedevt.eta_leading2hjets_ = p4_leading2hjets.Eta();
  selectedevt.y_leading2hjets_ = p4_leading2hjets.Rapidity();
  selectedevt.phi_leading2hjets_ = p4_leading2hjets.Phi();

  std::vector<std::pair<int, double>> lhe_ids_wts;
  for (auto idx : index(*h_lhewtids.product()) ) {
    int id = (*h_lhewtids.product()).at(idx.first) ; 
    double wt = (*h_lhewts.product()).at(idx.first) ; 
    lhe_ids_wts.push_back(std::make_pair(id, wt)) ; 
  }

  selectedevt.runno_ = int(runno);
  selectedevt.lumisec_ = int(lumisec);
  selectedevt.evtno_ = int(evtno);
  selectedevt.evtwt_ = evtwt ; 
  selectedevt.evtwtPV_ = double(*h_evtwtPV.product()) ; 
  selectedevt.evtwtPVLow_ = double(*h_evtwtPVLow.product()) ; 
  selectedevt.evtwtPVHigh_ = double(*h_evtwtPVHigh.product()) ; 
  selectedevt.npv_ = npv ; 
  selectedevt.npuTrue_ = int(*h_npuTrue.product()) ; 
  selectedevt.lhewts_ = lhe_ids_wts;
  selectedevt.htHat_ = htHat ; 

  selectedevt.nsubjetsBTaggedCSVL_ = 0 ;

  std::vector<double>sjcsvs;
  std::vector<double>sjpts;
  std::vector<double>sjetas;
  std::vector<int>sjflhads;

  hjets.njets = goodHTaggedJets.size() ; 
  for (auto ijet : index(goodHTaggedJets) ) {
    hjets.Index[ijet.first] = (ijet.second).getIndex() ;
    hjets.ParentIndex[ijet.first] = -1 ;
    hjets.Pt[ijet.first] = (ijet.second).getPt() ;
    hjets.Eta[ijet.first] = (ijet.second).getEta() ;
    hjets.Phi[ijet.first] = (ijet.second).getPhi() ;
    hjets.Mass[ijet.first] = (ijet.second).getMass() ;
    hjets.MassPruned[ijet.first] = (ijet.second).getPrunedMass() ;
    hjets.MassSoftDrop[ijet.first] = (ijet.second).getSoftDropMass() ;
    hjets.tau1[ijet.first] = (ijet.second).getTau1() ;
    hjets.tau2[ijet.first] = (ijet.second).getTau2() ;
    hjets.tau3[ijet.first] = (ijet.second).getTau3() ;
    hjets.hadFlavour[ijet.first] = (ijet.second).getHadronFlavour() ;
    hjets.CSVIVFv2[ijet.first] = (ijet.second).getCSV() ;
    hjets.nhf[ijet.first] = (ijet.second).getNHF() ;
    hjets.chf[ijet.first] = (ijet.second).getCHF() ;
    hjets.emf[ijet.first] = (ijet.second).getEMF() ;
    hjets.phf[ijet.first] = (ijet.second).getPHF() ;
    hjets.muf[ijet.first] = (ijet.second).getMUF() ;
    hjets.nconsts[ijet.first] = (ijet.second).getNConsts() ;
    hjets.groomedMassCorr[ijet.first] = (ijet.second).getGroomedMassCorr() ;
    hjets.nsubjets[ijet.first] = (ijet.second).getNSubjets() ;
    hjets.nsubjetsBTaggedCSVL[ijet.first] = (ijet.second).getNSubjetsBTaggedCSVL() ;
    selectedevt.nsubjetsBTaggedCSVL_  += (ijet.second).getNSubjetsBTaggedCSVL() ;  
    hjets.hadFlavourSubjet0[ijet.first] = (ijet.second).getHadronFlavourSubjet0() ;
    hjets.hadFlavourSubjet1[ijet.first] = (ijet.second).getHadronFlavourSubjet1() ;
    hjets.ptSubjet0[ijet.first] = (ijet.second).getPtSubjet0() ;
    hjets.ptSubjet1[ijet.first] = (ijet.second).getPtSubjet1() ;
    hjets.etaSubjet0[ijet.first] = (ijet.second).getEtaSubjet0() ;
    hjets.etaSubjet1[ijet.first] = (ijet.second).getEtaSubjet1() ;
    hjets.csvSubjet0[ijet.first] = (ijet.second).getCSVSubjet0() ;
    hjets.csvSubjet1[ijet.first] = (ijet.second).getCSVSubjet1() ;

    if ( !isData ) { 

      sjcsvs.push_back((ijet.second).getCSVSubjet0()) ; 
      sjcsvs.push_back((ijet.second).getCSVSubjet1()) ; 

      sjpts.push_back((ijet.second).getPtSubjet0()) ;  
      sjpts.push_back((ijet.second).getPtSubjet1()) ;  

      sjetas.push_back((ijet.second).getEtaSubjet0()) ;  
      sjetas.push_back((ijet.second).getEtaSubjet1()) ;  

      sjflhads.push_back(abs((ijet.second).getHadronFlavourSubjet0())) ; 
      sjflhads.push_back(abs((ijet.second).getHadronFlavourSubjet1())) ;

    } //// if !isData do  b tag SFs

  } //// Loop over all Higgs jets

  if ( !isData ) btagsfutils_->getBTagSFs (sjcsvs, sjpts, sjetas, sjflhads, CSVv2L, btagsf, btagsf_bcUp, btagsf_bcDown, btagsf_lUp, btagsf_lDown) ; 

  selectedevt.btagsf_ = btagsf;
  selectedevt.btagsf_bcUp_ = btagsf_bcUp ; 
  selectedevt.btagsf_bcDown_ = btagsf_bcDown ; 
  selectedevt.btagsf_lUp_ = btagsf_lUp ; 
  selectedevt.btagsf_lDown_ = btagsf_lDown ; 

  tree_->Fill();

  return true ; 
}

bool HH4b::passHiggsTagging(vlq::Jet jet) {
  bool passHiggsTagging(0);
  if (jet.getPt() > 300. 
      && abs(jet.getEta()) <= 2.4
      && abs(jet.getPrunedMass()) >= 90 
      //&& (jet.getTau1() == 0. || jet.getTau2()/jet.getTau1() < 0.75)
      && (jet.getTau1() == 0. || jet.getTau2()/jet.getTau1() < 1.00)
     ) passHiggsTagging = true ; 
  return passHiggsTagging;
}

// ------------ method called once each job just before starting event loop  ------------
void HH4b::beginJob() {

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 14, 0.5, 14.5) ;  
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(1,"All") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(2,"Trigger") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(3 ,"p_{T}") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(4,"|#eta|") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(5,"|#Delta#eta|") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(6,"M(jet_{0},jet(1))") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(7,"M(jets)") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(8,"#tau_{21}") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(9,"0b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(10,"1b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(11,"2b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(12,"3b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(13,"4b") ; 
  h1_["cutflow"] -> GetXaxis() -> SetBinLabel(14,"3b+HPHP") ; 

  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 
  tree_ = fs->make<TTree>("tree", "HH4b") ; 
  selectedevt.RegisterTree(tree_,"SelectedEvent") ; 
  hjets.RegisterTree(tree_,"HJets") ; 

  if ( printEvtNo_ ) {
    outfile0b_.open("EvtNo_0b.txt",ios::out) ; 
    outfile0b_ << " Cat0b: Runno " << " Lumisec " << " Evtno " 
      << " j0-sj0 CSVv2 " << " j0-sj1 CSVv2 " 
      << " j1-sj0 CSVv2 " << " j1-sj1 CSVv2 " 
      << std::endl ; 

    outfile4b_.open("EvtNo_4b.txt",ios::out) ; 
    outfile4b_ << " Cat4b: Runno " << " Lumisec " << " Evtno " 
      << " j0-sj0 CSVv2 " << " j0-sj1 CSVv2 " 
      << " j1-sj0 CSVv2 " << " j1-sj1 CSVv2 " 
      << std::endl ; 
  }

}

void HH4b::endJob() {

  outfile0b_.close() ;
  outfile4b_.close() ;
  return ; 
}

DEFINE_FWK_MODULE(HH4b);
