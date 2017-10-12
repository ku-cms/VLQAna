#ifndef ANALYSIS_VLQANA_TTHT_HH
#define ANALYSIS_VLQANA_TTHT_HH
#include <string>
#include <TTree.h>
#include <vector>
#include <utility>  

class TtHEventInfoBranches {
  public:

    int    runno_ ;
    int    lumisec_ ; 
    int    evtno_;    
    int    bcno_;
    int    time_;
    double htHat_; 
    double EvtWeight_ ; 
    double EvtWtPV_;
    double EvtWtPVBG_;
    double EvtWtPVH_;
    double EvtWtPVLow_;
    double EvtWtPVHigh_;
    double EvtWtHT_;
    double EvtWtHTUp_;
    double EvtWtHTDown_;
    int    npv_;
    int    npuTrue_;
    double toptagsf_;
    double toptagsf_Up_;
    double toptagsf_Down_;
    double btagsf_;
    double btagsf_bcUp_;
    double btagsf_bcDown_;
    double btagsf_lUp_;
    double btagsf_lDown_;
    double mtprime_;
    double mtprimeDummy_;
    double mtprimeDummyA_;
    double mtprimeDummyC_;
    double ht_ ; 
    int    nAK4_;
    int    nAK8_;
    int    nEl_;
    int    nMu_;
    int    nCleanedEl_;
    int    nCleanedMu_;
    bool   isRegionA_;
    bool   isRegionB_;
    bool   isRegionC_;
    bool   isRegionD_;
    bool   isRegionNotABCD_;
    double isotropy_;
    double circularity_;
    double sphericity_;
    double aplanarity_;
    double C_;
    double D_;
    double thrust_;
    double thrustminor_;
    double isotropy_ExtraAK4_;
    double circularity_ExtraAK4_;
    double sphericity_ExtraAK4_;
    double aplanarity_ExtraAK4_;
    double C_ExtraAK4_;
    double D_ExtraAK4_;
    double thrust_ExtraAK4_;
    double thrustminor_ExtraAK4_;
    std::vector<std::pair<int, double> > lhewts_ ; 

    void RegisterTree(TTree* cutTree, std::string name="SelectedEvents") {
      cutTree->Branch((name+"_runno").c_str(), &runno_, (name+"_runno/I").c_str());
      cutTree->Branch((name+"_lumisec").c_str(), &lumisec_, (name+"_lumisec/I").c_str());
      cutTree->Branch((name+"_evtno").c_str(), &evtno_, (name+"_evtno/I").c_str());
      cutTree->Branch((name+"_bcno").c_str(), &bcno_, (name+"_bcno/I").c_str());
      cutTree->Branch((name+"_time").c_str(), &time_, (name+"_time/I").c_str());
      cutTree->Branch((name+"_htHat").c_str(), &htHat_, (name+"_htHat/D").c_str()) ; 
      cutTree->Branch((name+"_EvtWeight").c_str(), &EvtWeight_, "EvtWeight/D");
      cutTree->Branch((name+"_EvtWtPV").c_str(), &EvtWtPV_, "EvtWtPV/D");
      cutTree->Branch((name+"_EvtWtPVBG").c_str(), &EvtWtPVBG_, "EvtWtPVBG/D");
      cutTree->Branch((name+"_EvtWtPVH").c_str(), &EvtWtPVH_, "EvtWtPVH/D");
      cutTree->Branch((name+"_EvtWtPVLow").c_str(), &EvtWtPVLow_, "EvtWtPVLow/D");
      cutTree->Branch((name+"_EvtWtPVHigh").c_str(), &EvtWtPVHigh_, "EvtWtPVHigh/D");
      cutTree->Branch((name+"_EvtWtHT").c_str(), &EvtWtHT_, "EvtWtHT/D");
      cutTree->Branch((name+"_EvtWtHTUp").c_str(), &EvtWtHTUp_, "EvtWtHTUp/D");
      cutTree->Branch((name+"_EvtWtHTDown").c_str(), &EvtWtHTDown_, "EvtWtHTDown/D");
      cutTree->Branch((name+"_npv").c_str(), &npv_, "npv/I");
      cutTree->Branch((name+"_npuTrue").c_str(), &npuTrue_, "npuTrue/I");
      cutTree->Branch((name+"_toptagsf").c_str(), &toptagsf_, "toptagsf/D");
      cutTree->Branch((name+"_toptagsf_Up").c_str(), &toptagsf_Up_, "toptagsf_Up/D");
      cutTree->Branch((name+"_toptagsf_Down").c_str(), &toptagsf_Down_, "toptagsf_Down/D");
      cutTree->Branch((name+"_btagsf").c_str(), &btagsf_, "btagsf/D");
      cutTree->Branch((name+"_btagsf_bcUp").c_str(), &btagsf_bcUp_, "btagsf_bcUp/D");
      cutTree->Branch((name+"_btagsf_bcDown").c_str(), &btagsf_bcDown_, "btagsf_bcDown/D");
      cutTree->Branch((name+"_btagsf_lUp").c_str(), &btagsf_lUp_, "btagsf_lUp/D");
      cutTree->Branch((name+"_btagsf_lDown").c_str(), &btagsf_lDown_, "btagsf_lDown/D");
      cutTree->Branch((name+"_mtprime").c_str(), &mtprime_, "mtprime/D");
      cutTree->Branch((name+"_mtprimeDummy").c_str(), &mtprimeDummy_, "mtprimeDummy/D");
      cutTree->Branch((name+"_mtprimeDummyA").c_str(), &mtprimeDummyA_, "mtprimeDummyA/D");
      cutTree->Branch((name+"_mtprimeDummyC").c_str(), &mtprimeDummyC_, "mtprimeDummyC/D");
      cutTree->Branch((name+"_ht").c_str(), &ht_, "ht/D");
      cutTree->Branch((name+"_nAK4").c_str(), &nAK4_, "nAK4/I");
      cutTree->Branch((name+"_nAK8").c_str(), &nAK8_, "nAK8/I");
      cutTree->Branch((name+"_nEl").c_str(), &nEl_, "nEl/I");
      cutTree->Branch((name+"_nMu").c_str(), &nMu_, "nMu/I");
      cutTree->Branch((name+"_nCleanedEl").c_str(), &nCleanedEl_, "nCleanedEl/I");
      cutTree->Branch((name+"_nCleanedMu").c_str(), &nCleanedMu_, "nCleanedMu/I");
      cutTree->Branch((name+"_isRegionA").c_str(), &isRegionA_, "isRegionA/O");
      cutTree->Branch((name+"_isRegionB").c_str(), &isRegionB_, "isRegionB/O");
      cutTree->Branch((name+"_isRegionC").c_str(), &isRegionC_, "isRegionC/O");
      cutTree->Branch((name+"_isRegionD").c_str(), &isRegionD_, "isRegionD/O");
      cutTree->Branch((name+"_isRegionNotABCD").c_str(), &isRegionNotABCD_, "isRegionNotABCD/O");
      cutTree->Branch((name+"_lhewts").c_str(), &lhewts_) ;  
      cutTree->Branch((name+"_isotropy").c_str(), &isotropy_, "isotropy/D");
      cutTree->Branch((name+"_circularity").c_str(), &circularity_, "circularity/D");
      cutTree->Branch((name+"_sphericity").c_str(), &sphericity_, "sphericity/D");
      cutTree->Branch((name+"_aplanarity").c_str(), &aplanarity_, "aplanarity/D");
      cutTree->Branch((name+"_C").c_str(), &C_, "C/D");
      cutTree->Branch((name+"_D").c_str(), &D_, "D/D");
      cutTree->Branch((name+"_thrust").c_str(), &thrust_, "thrust/D");
      cutTree->Branch((name+"_thrustminor").c_str(), &thrustminor_, "thrustminor/D");
      cutTree->Branch((name+"_isotropy_ExtraAK4").c_str(), &isotropy_ExtraAK4_, "isotropy_ExtraAK4_/D");
      cutTree->Branch((name+"_circularity_ExtraAK4").c_str(), &circularity_ExtraAK4_, "circularity_ExtraAK4_/D");
      cutTree->Branch((name+"_sphericity_ExtraAK4").c_str(), &sphericity_ExtraAK4_, "sphericity_ExtraAK4_/D");
      cutTree->Branch((name+"_aplanarity_ExtraAK4").c_str(), &aplanarity_ExtraAK4_, "aplanarity_ExtraAK4_/D");
      cutTree->Branch((name+"_C_ExtraAK4").c_str(), &C_ExtraAK4_, "C_ExtraAK4_/D");
      cutTree->Branch((name+"_D_ExtraAK4").c_str(), &D_ExtraAK4_, "D_ExtraAK4_/D");
      cutTree->Branch((name+"_thrust_ExtraAK4").c_str(), &thrust_ExtraAK4_, "thrust_ExtraAK4_/D");
      cutTree->Branch((name+"_thrustminor_ExtraAK4").c_str(), &thrustminor_ExtraAK4_, "thrustminor_ExtraAK4_/D");

    }

};

class TtHJetInfoBranches {
  public:

    std::vector<int>  idxAK4; 
    std::vector<double> ptAK4;
    std::vector<double> etaAK4;
    std::vector<double> phiAK4;
    std::vector<double> MAK4;
    std::vector<double> csvAK4;
    std::vector<double> partonFlavourAK4; 
    std::vector<double> hadronFlavourAK4;
 
    std::vector<int>  idxExtraAK4; 
    std::vector<double> ptExtraAK4;
    std::vector<double> etaExtraAK4;
    std::vector<double> phiExtraAK4;
    std::vector<double> MExtraAK4;
    std::vector<double> csvExtraAK4;
    std::vector<double> partonFlavourExtraAK4; 
    std::vector<double> hadronFlavourExtraAK4; 

    std::vector<int> idxAK8; 
    std::vector<double> ptAK8;
    std::vector<double> etaAK8;
    std::vector<double> phiAK8;
    std::vector<double> MAK8;
    std::vector<double> SoftDropMassAK8;
    std::vector<double> PrunedMassAK8;
    std::vector<double> tau1AK8;
    std::vector<double> tau2AK8;
    std::vector<double> tau3AK8;
    std::vector<double> csvAK8;
    std::vector<double> partonFlavourAK8; 
    std::vector<double> hadronFlavourAK8; 

    std::vector<double> doubleBAK8;
    std::vector<double> sj0CSVAK8;
    std::vector<double> sj1CSVAK8;
    std::vector<double> hadronFlavourSJ0AK8; 
    std::vector<double> hadronFlavourSJ1AK8; 
    std::vector<double> sj0ptAK8;
    std::vector<double> sj1ptAK8;
    std::vector<double> sj0etaAK8;
    std::vector<double> sj1etaAK8;
    std::vector<double> sj0phiAK8;
    std::vector<double> sj1phiAK8;
    std::vector<double> sj0EnergyAK8;
    std::vector<double> sj1EnergyAK8;

    std::vector<int> idxHTagged; 
    std::vector<double> ptHTagged;
    std::vector<double> etaHTagged;
    std::vector<double> phiHTagged;
    std::vector<double> MHTagged;
    std::vector<double> SoftDropMassHTagged;
    std::vector<double> PrunedMassHTagged;
    std::vector<double> tau1HTagged;
    std::vector<double> tau2HTagged;
    std::vector<double> tau3HTagged;
    std::vector<double> csvHTagged;
    std::vector<double> partonFlavourHTagged; 
    std::vector<double> hadronFlavourHTagged; 

    std::vector<double> doubleBHTagged;
    std::vector<double> sj0CSVHTagged;
    std::vector<double> sj1CSVHTagged;
    std::vector<double> hadronFlavourSJ0HTagged; 
    std::vector<double> hadronFlavourSJ1HTagged; 
    std::vector<double> sj0ptHTagged;
    std::vector<double> sj1ptHTagged;
    std::vector<double> sj0etaHTagged;
    std::vector<double> sj1etaHTagged;
    std::vector<double> sj0phiHTagged;
    std::vector<double> sj1phiHTagged;
    std::vector<double> sj0EnergyHTagged;
    std::vector<double> sj1EnergyHTagged;

    std::vector<int> idxAntiHTagged; 
    std::vector<double> ptAntiHTagged;
    std::vector<double> etaAntiHTagged;
    std::vector<double> phiAntiHTagged;
    std::vector<double> MAntiHTagged;
    std::vector<double> SoftDropMassAntiHTagged;
    std::vector<double> PrunedMassAntiHTagged;
    std::vector<double> tau1AntiHTagged;
    std::vector<double> tau2AntiHTagged;
    std::vector<double> tau3AntiHTagged;
    std::vector<double> csvAntiHTagged;
    std::vector<double> partonFlavourAntiHTagged; 
    std::vector<double> hadronFlavourAntiHTagged; 

    std::vector<double> doubleBAntiHTagged;
    std::vector<double> sj0CSVAntiHTagged;
    std::vector<double> sj1CSVAntiHTagged;
    std::vector<double> hadronFlavourSJ0AntiHTagged; 
    std::vector<double> hadronFlavourSJ1AntiHTagged; 
    std::vector<double> sj0ptAntiHTagged;
    std::vector<double> sj1ptAntiHTagged;
    std::vector<double> sj0etaAntiHTagged;
    std::vector<double> sj1etaAntiHTagged;
    std::vector<double> sj0phiAntiHTagged;
    std::vector<double> sj1phiAntiHTagged;
    std::vector<double> sj0EnergyAntiHTagged;
    std::vector<double> sj1EnergyAntiHTagged;

    std::vector<int> idxTopTagged; 
    std::vector<double> ptTopTagged;
    std::vector<double> etaTopTagged;
    std::vector<double> phiTopTagged;
    std::vector<double> MTopTagged;
    std::vector<double> SoftDropMassTopTagged;
    std::vector<double> PrunedMassTopTagged;
    std::vector<double> tau1TopTagged;
    std::vector<double> tau2TopTagged;
    std::vector<double> tau3TopTagged;
    std::vector<double> csvTopTagged;
    std::vector<double> partonFlavourTopTagged; 
    std::vector<double> hadronFlavourTopTagged; 

    std::vector<double> doubleBTopTagged;
    std::vector<double> sj0CSVTopTagged;
    std::vector<double> sj1CSVTopTagged;
    std::vector<double> hadronFlavourSJ0TopTagged; 
    std::vector<double> hadronFlavourSJ1TopTagged; 
    std::vector<double> sj0ptTopTagged;
    std::vector<double> sj1ptTopTagged;
    std::vector<double> sj0etaTopTagged;
    std::vector<double> sj1etaTopTagged;
    std::vector<double> sj0phiTopTagged;
    std::vector<double> sj1phiTopTagged;
    std::vector<double> sj0EnergyTopTagged;
    std::vector<double> sj1EnergyTopTagged;

    std::vector<int> idxAntiTopTagged; 
    std::vector<double> ptAntiTopTagged;
    std::vector<double> etaAntiTopTagged;
    std::vector<double> phiAntiTopTagged;
    std::vector<double> MAntiTopTagged;
    std::vector<double> SoftDropMassAntiTopTagged;
    std::vector<double> PrunedMassAntiTopTagged;
    std::vector<double> tau1AntiTopTagged;
    std::vector<double> tau2AntiTopTagged;
    std::vector<double> tau3AntiTopTagged;
    std::vector<double> csvAntiTopTagged;
    std::vector<double> partonFlavourAntiTopTagged; 
    std::vector<double> hadronFlavourAntiTopTagged; 

    std::vector<double> doubleBAntiTopTagged;
    std::vector<double> sj0CSVAntiTopTagged;
    std::vector<double> sj1CSVAntiTopTagged;
    std::vector<double> hadronFlavourSJ0AntiTopTagged; 
    std::vector<double> hadronFlavourSJ1AntiTopTagged;
    std::vector<double> sj0ptAntiTopTagged;
    std::vector<double> sj1ptAntiTopTagged;
    std::vector<double> sj0etaAntiTopTagged;
    std::vector<double> sj1etaAntiTopTagged;
    std::vector<double> sj0phiAntiTopTagged;
    std::vector<double> sj1phiAntiTopTagged;
    std::vector<double> sj0EnergyAntiTopTagged;
    std::vector<double> sj1EnergyAntiTopTagged;
 
    std::vector<int> idxZTagged; 
    std::vector<double> ptZTagged;
    std::vector<double> etaZTagged;
    std::vector<double> phiZTagged;
    std::vector<double> MZTagged;
    std::vector<double> SoftDropMassZTagged;
    std::vector<double> PrunedMassZTagged;
    std::vector<double> tau1ZTagged;
    std::vector<double> tau2ZTagged;
    std::vector<double> tau3ZTagged;
    std::vector<double> csvZTagged;
    std::vector<double> partonFlavourZTagged; 
    std::vector<double> hadronFlavourZTagged; 

    std::vector<double> doubleBZTagged;
    std::vector<double> sj0CSVZTagged;
    std::vector<double> sj1CSVZTagged;
    std::vector<double> hadronFlavourSJ0ZTagged; 
    std::vector<double> hadronFlavourSJ1ZTagged; 
    std::vector<double> sj0ptZTagged;
    std::vector<double> sj1ptZTagged;
    std::vector<double> sj0etaZTagged;
    std::vector<double> sj1etaZTagged;
    std::vector<double> sj0phiZTagged;
    std::vector<double> sj1phiZTagged;
    std::vector<double> sj0EnergyZTagged;
    std::vector<double> sj1EnergyZTagged;

    std::vector<int> idxAntiZTagged; 
    std::vector<double> ptAntiZTagged;
    std::vector<double> etaAntiZTagged;
    std::vector<double> phiAntiZTagged;
    std::vector<double> MAntiZTagged;
    std::vector<double> SoftDropMassAntiZTagged;
    std::vector<double> PrunedMassAntiZTagged;
    std::vector<double> tau1AntiZTagged;
    std::vector<double> tau2AntiZTagged;
    std::vector<double> tau3AntiZTagged;
    std::vector<double> csvAntiZTagged;
    std::vector<double> partonFlavourAntiZTagged; 
    std::vector<double> hadronFlavourAntiZTagged; 

    std::vector<double> doubleBAntiZTagged;
    std::vector<double> sj0CSVAntiZTagged;
    std::vector<double> sj1CSVAntiZTagged;
    std::vector<double> hadronFlavourSJ0AntiZTagged; 
    std::vector<double> hadronFlavourSJ1AntiZTagged;
    std::vector<double> sj0ptAntiZTagged;
    std::vector<double> sj1ptAntiZTagged;
    std::vector<double> sj0etaAntiZTagged;
    std::vector<double> sj1etaAntiZTagged;
    std::vector<double> sj0phiAntiZTagged;
    std::vector<double> sj1phiAntiZTagged;
    std::vector<double> sj0EnergyAntiZTagged;
    std::vector<double> sj1EnergyAntiZTagged;
 
    void RegisterTree(TTree *cutTree, std::string name="JetInfo") {

      cutTree->Branch("idxAK4", &idxAK4); 
      cutTree->Branch("ptAK4", &ptAK4); 
      cutTree->Branch("etaAK4", &etaAK4);
      cutTree->Branch("phiAK4", &phiAK4);
      cutTree->Branch("MAK4", &MAK4);
      cutTree->Branch("csvAK4", &csvAK4);
      cutTree->Branch("partonFlavourAK4", &partonFlavourAK4);
      cutTree->Branch("hadronFlavourAK4", &hadronFlavourAK4);

      cutTree->Branch("idxExtraAK4", &idxExtraAK4); 
      cutTree->Branch("ptExtraAK4", &ptExtraAK4); 
      cutTree->Branch("etaExtraAK4", &etaExtraAK4);
      cutTree->Branch("phiExtraAK4", &phiExtraAK4);
      cutTree->Branch("MExtraAK4", &MExtraAK4);
      cutTree->Branch("csvExtraAK4", &csvExtraAK4);
      cutTree->Branch("partonFlavourExtraAK4", &partonFlavourExtraAK4);
      cutTree->Branch("hadronFlavourExtraAK4", &hadronFlavourExtraAK4);

      cutTree->Branch("idxAK8", &idxAK8); 
      cutTree->Branch("ptAK8", &ptAK8); 
      cutTree->Branch("etaAK8", &etaAK8);
      cutTree->Branch("phiAK8", &phiAK8);
      cutTree->Branch("MAK8", &MAK8);
      cutTree->Branch("SoftDropMassAK8", &SoftDropMassAK8);
      cutTree->Branch("PrunedMassAK8", &PrunedMassAK8);
      cutTree->Branch("tau1AK8", &tau1AK8);
      cutTree->Branch("tau2AK8", &tau2AK8);
      cutTree->Branch("tau3AK8", &tau3AK8);
      cutTree->Branch("csvAK8", &csvAK8);
      cutTree->Branch("partonFlavourAK8", &partonFlavourAK8);
      cutTree->Branch("hadronFlavourAK8", &hadronFlavourAK8);

      cutTree->Branch("doubleBAK8",&doubleBAK8);
      cutTree->Branch("sj0CSVAK8",&sj0CSVAK8);
      cutTree->Branch("sj1CSVAK8",&sj1CSVAK8);
      cutTree->Branch("hadronFlavourSJ0AK8",&hadronFlavourSJ0AK8);
      cutTree->Branch("hadronFlavourSJ1AK8",&hadronFlavourSJ1AK8);
      cutTree->Branch("sj0ptAK8",&sj0ptAK8);
      cutTree->Branch("sj1ptAK8",&sj1ptAK8);
      cutTree->Branch("sj0etaAK8",&sj0etaAK8);
      cutTree->Branch("sj1etaAK8",&sj1etaAK8);
      cutTree->Branch("sj0phiAK8",&sj0phiAK8);
      cutTree->Branch("sj1phiAK8",&sj1phiAK8);
      cutTree->Branch("sj0EnergyAK8",&sj0EnergyAK8);
      cutTree->Branch("sj1EnergyAK8",&sj1EnergyAK8);

      cutTree->Branch("idxHTagged", &idxHTagged); 
      cutTree->Branch("ptHTagged", &ptHTagged); 
      cutTree->Branch("etaHTagged", &etaHTagged);
      cutTree->Branch("phiHTagged", &phiHTagged);
      cutTree->Branch("MHTagged", &MHTagged);
      cutTree->Branch("SoftDropMassHTagged", &SoftDropMassHTagged);
      cutTree->Branch("PrunedMassHTagged", &PrunedMassHTagged);
      cutTree->Branch("tau1HTagged", &tau1HTagged);
      cutTree->Branch("tau2HTagged", &tau2HTagged);
      cutTree->Branch("tau3HTagged", &tau3HTagged);
      cutTree->Branch("csvHTagged", &csvHTagged);
      cutTree->Branch("partonFlavourHTagged", &partonFlavourHTagged);
      cutTree->Branch("hadronFlavourHTagged", &hadronFlavourHTagged);

      cutTree->Branch("doubleBHTagged",&doubleBHTagged);
      cutTree->Branch("sj0CSVHTagged",&sj0CSVHTagged);
      cutTree->Branch("sj1CSVHTagged",&sj1CSVHTagged);
      cutTree->Branch("hadronFlavourSJ0HTagged",&hadronFlavourSJ0HTagged);
      cutTree->Branch("hadronFlavourSJ1HTagged",&hadronFlavourSJ1HTagged);
      cutTree->Branch("sj0ptHTagged",&sj0ptHTagged);
      cutTree->Branch("sj1ptHTagged",&sj1ptHTagged);
      cutTree->Branch("sj0etaHTagged",&sj0etaHTagged);
      cutTree->Branch("sj1etaHTagged",&sj1etaHTagged);
      cutTree->Branch("sj0phiHTagged",&sj0phiHTagged);
      cutTree->Branch("sj1phiHTagged",&sj1phiHTagged);
      cutTree->Branch("sj0EnergyHTagged",&sj0EnergyHTagged);
      cutTree->Branch("sj1EnergyHTagged",&sj1EnergyHTagged);

      cutTree->Branch("idxAntiHTagged", &idxAntiHTagged); 
      cutTree->Branch("ptAntiHTagged", &ptAntiHTagged); 
      cutTree->Branch("etaAntiHTagged", &etaAntiHTagged);
      cutTree->Branch("phiAntiHTagged", &phiAntiHTagged);
      cutTree->Branch("MAntiHTagged", &MAntiHTagged);
      cutTree->Branch("SoftDropMassAntiHTagged", &SoftDropMassAntiHTagged);
      cutTree->Branch("PrunedMassAntiHTagged", &PrunedMassAntiHTagged);
      cutTree->Branch("tau1AntiHTagged", &tau1AntiHTagged);
      cutTree->Branch("tau2AntiHTagged", &tau2AntiHTagged);
      cutTree->Branch("tau3AntiHTagged", &tau3AntiHTagged);
      cutTree->Branch("csvAntiHTagged", &csvAntiHTagged);
      cutTree->Branch("partonFlavourAntiHTagged", &partonFlavourAntiHTagged);
      cutTree->Branch("hadronFlavourAntiHTagged", &hadronFlavourAntiHTagged);

      cutTree->Branch("doubleBAntiHTagged",&doubleBAntiHTagged);
      cutTree->Branch("sj0CSVAntiHTagged",&sj0CSVAntiHTagged);
      cutTree->Branch("sj1CSVAntiHTagged",&sj1CSVAntiHTagged);
      cutTree->Branch("hadronFlavourSJ0AntiHTagged",&hadronFlavourSJ0AntiHTagged);
      cutTree->Branch("hadronFlavourSJ1AntiHTagged",&hadronFlavourSJ1AntiHTagged);
      cutTree->Branch("sj0ptAntiHTagged",&sj0ptAntiHTagged);
      cutTree->Branch("sj1ptAntiHTagged",&sj1ptAntiHTagged);
      cutTree->Branch("sj0etaAntiHTagged",&sj0etaAntiHTagged);
      cutTree->Branch("sj1etaAntiHTagged",&sj1etaAntiHTagged);
      cutTree->Branch("sj0phiAntiHTagged",&sj0phiAntiHTagged);
      cutTree->Branch("sj1phiAntiHTagged",&sj1phiAntiHTagged);
      cutTree->Branch("sj0EnergyAntiHTagged",&sj0EnergyAntiHTagged);
      cutTree->Branch("sj1EnergyAntiHTagged",&sj1EnergyAntiHTagged);

      cutTree->Branch("idxTopTagged", &idxTopTagged); 
      cutTree->Branch("ptTopTagged", &ptTopTagged); 
      cutTree->Branch("etaTopTagged", &etaTopTagged);
      cutTree->Branch("phiTopTagged", &phiTopTagged);
      cutTree->Branch("MTopTagged", &MTopTagged);
      cutTree->Branch("SoftDropMassTopTagged", &SoftDropMassTopTagged);
      cutTree->Branch("PrunedMassTopTagged", &PrunedMassTopTagged);
      cutTree->Branch("tau1TopTagged", &tau1TopTagged);
      cutTree->Branch("tau2TopTagged", &tau2TopTagged);
      cutTree->Branch("tau3TopTagged", &tau3TopTagged);
      cutTree->Branch("csvTopTagged", &csvTopTagged);
      cutTree->Branch("partonFlavourTopTagged", &partonFlavourTopTagged);
      cutTree->Branch("hadronFlavourTopTagged", &hadronFlavourTopTagged);

      cutTree->Branch("doubleBTopTagged",&doubleBTopTagged);
      cutTree->Branch("sj0CSVTopTagged",&sj0CSVTopTagged);
      cutTree->Branch("sj1CSVTopTagged",&sj1CSVTopTagged);
      cutTree->Branch("hadronFlavourSJ0TopTagged",&hadronFlavourSJ0TopTagged);
      cutTree->Branch("hadronFlavourSJ1TopTagged",&hadronFlavourSJ1TopTagged);
      cutTree->Branch("sj0ptTopTagged",&sj0ptTopTagged);
      cutTree->Branch("sj1ptTopTagged",&sj1ptTopTagged);
      cutTree->Branch("sj0etaTopTagged",&sj0etaTopTagged);
      cutTree->Branch("sj1etaTopTagged",&sj1etaTopTagged);
      cutTree->Branch("sj0phiTopTagged",&sj0phiTopTagged);
      cutTree->Branch("sj1phiTopTagged",&sj1phiTopTagged);
      cutTree->Branch("sj0EnergyTopTagged",&sj0EnergyTopTagged);
      cutTree->Branch("sj1EnergyTopTagged",&sj1EnergyTopTagged);

      cutTree->Branch("idxAntiTopTagged", &idxAntiTopTagged); 
      cutTree->Branch("ptAntiTopTagged", &ptAntiTopTagged); 
      cutTree->Branch("etaAntiTopTagged", &etaAntiTopTagged);
      cutTree->Branch("phiAntiTopTagged", &phiAntiTopTagged);
      cutTree->Branch("MAntiTopTagged", &MAntiTopTagged);
      cutTree->Branch("SoftDropMassAntiTopTagged", &SoftDropMassAntiTopTagged);
      cutTree->Branch("PrunedMassAntiTopTagged", &PrunedMassAntiTopTagged);
      cutTree->Branch("tau1AntiTopTagged", &tau1AntiTopTagged);
      cutTree->Branch("tau2AntiTopTagged", &tau2AntiTopTagged);
      cutTree->Branch("tau3AntiTopTagged", &tau3AntiTopTagged);
      cutTree->Branch("csvAntiTopTagged", &csvAntiTopTagged);
      cutTree->Branch("partonFlavourAntiTopTagged", &partonFlavourAntiTopTagged);
      cutTree->Branch("hadronFlavourAntiTopTagged", &hadronFlavourAntiTopTagged);

      cutTree->Branch("doubleBAntiTopTagged",&doubleBAntiTopTagged);
      cutTree->Branch("sj0CSVAntiTopTagged",&sj0CSVAntiTopTagged);
      cutTree->Branch("sj1CSVAntiTopTagged",&sj1CSVAntiTopTagged);
      cutTree->Branch("hadronFlavourSJ0AntiTopTagged",&hadronFlavourSJ0AntiTopTagged);
      cutTree->Branch("hadronFlavourSJ1AntiTopTagged",&hadronFlavourSJ1AntiTopTagged);
      cutTree->Branch("sj0ptAntiTopTagged",&sj0ptAntiTopTagged);
      cutTree->Branch("sj1ptAntiTopTagged",&sj1ptAntiTopTagged);
      cutTree->Branch("sj0etaAntiTopTagged",&sj0etaAntiTopTagged);
      cutTree->Branch("sj1etaAntiTopTagged",&sj1etaAntiTopTagged);
      cutTree->Branch("sj0phiAntiTopTagged",&sj0phiAntiTopTagged);
      cutTree->Branch("sj1phiAntiTopTagged",&sj1phiAntiTopTagged);
      cutTree->Branch("sj0EnergyAntiTopTagged",&sj0EnergyAntiTopTagged);
      cutTree->Branch("sj1EnergyAntiTopTagged",&sj1EnergyAntiTopTagged);

      cutTree->Branch("idxZTagged", &idxZTagged); 
      cutTree->Branch("ptZTagged", &ptZTagged); 
      cutTree->Branch("etaZTagged", &etaZTagged);
      cutTree->Branch("phiZTagged", &phiZTagged);
      cutTree->Branch("MZTagged", &MZTagged);
      cutTree->Branch("SoftDropMassZTagged", &SoftDropMassZTagged);
      cutTree->Branch("PrunedMassZTagged", &PrunedMassZTagged);
      cutTree->Branch("tau1ZTagged", &tau1ZTagged);
      cutTree->Branch("tau2ZTagged", &tau2ZTagged);
      cutTree->Branch("tau3ZTagged", &tau3ZTagged);
      cutTree->Branch("csvZTagged", &csvZTagged);
      cutTree->Branch("partonFlavourZTagged", &partonFlavourZTagged);
      cutTree->Branch("hadronFlavourZTagged", &hadronFlavourZTagged);

      cutTree->Branch("doubleBZTagged",&doubleBZTagged);
      cutTree->Branch("sj0CSVZTagged",&sj0CSVZTagged);
      cutTree->Branch("sj1CSVZTagged",&sj1CSVZTagged);
      cutTree->Branch("hadronFlavourSJ0ZTagged",&hadronFlavourSJ0ZTagged);
      cutTree->Branch("hadronFlavourSJ1ZTagged",&hadronFlavourSJ1ZTagged);
      cutTree->Branch("sj0ptZTagged",&sj0ptZTagged);
      cutTree->Branch("sj1ptZTagged",&sj1ptZTagged);
      cutTree->Branch("sj0etaZTagged",&sj0etaZTagged);
      cutTree->Branch("sj1etaZTagged",&sj1etaZTagged);
      cutTree->Branch("sj0phiZTagged",&sj0phiZTagged);
      cutTree->Branch("sj1phiZTagged",&sj1phiZTagged);
      cutTree->Branch("sj0EnergyZTagged",&sj0EnergyZTagged);
      cutTree->Branch("sj1EnergyZTagged",&sj1EnergyZTagged);

      cutTree->Branch("idxAntiZTagged", &idxAntiZTagged); 
      cutTree->Branch("ptAntiZTagged", &ptAntiZTagged); 
      cutTree->Branch("etaAntiZTagged", &etaAntiZTagged);
      cutTree->Branch("phiAntiZTagged", &phiAntiZTagged);
      cutTree->Branch("MAntiZTagged", &MAntiZTagged);
      cutTree->Branch("SoftDropMassAntiZTagged", &SoftDropMassAntiZTagged);
      cutTree->Branch("PrunedMassAntiZTagged", &PrunedMassAntiZTagged);
      cutTree->Branch("tau1AntiZTagged", &tau1AntiZTagged);
      cutTree->Branch("tau2AntiZTagged", &tau2AntiZTagged);
      cutTree->Branch("tau3AntiZTagged", &tau3AntiZTagged);
      cutTree->Branch("csvAntiZTagged", &csvAntiZTagged);
      cutTree->Branch("partonFlavourAntiZTagged", &partonFlavourAntiZTagged);
      cutTree->Branch("hadronFlavourAntiZTagged", &hadronFlavourAntiZTagged);

      cutTree->Branch("doubleBAntiZTagged",&doubleBAntiZTagged);
      cutTree->Branch("sj0CSVAntiZTagged",&sj0CSVAntiZTagged);
      cutTree->Branch("sj1CSVAntiZTagged",&sj1CSVAntiZTagged);
      cutTree->Branch("hadronFlavourSJ0AntiZTagged",&hadronFlavourSJ0AntiZTagged);
      cutTree->Branch("hadronFlavourSJ1AntiZTagged",&hadronFlavourSJ1AntiZTagged);
      cutTree->Branch("sj0ptAntiZTagged",&sj0ptAntiZTagged);
      cutTree->Branch("sj1ptAntiZTagged",&sj1ptAntiZTagged);
      cutTree->Branch("sj0etaAntiZTagged",&sj0etaAntiZTagged);
      cutTree->Branch("sj1etaAntiZTagged",&sj1etaAntiZTagged);
      cutTree->Branch("sj0phiAntiZTagged",&sj0phiAntiZTagged);
      cutTree->Branch("sj1phiAntiZTagged",&sj1phiAntiZTagged);
      cutTree->Branch("sj0EnergyAntiZTagged",&sj0EnergyAntiZTagged);
      cutTree->Branch("sj1EnergyAntiZTagged",&sj1EnergyAntiZTagged);
    }

    //void ReadTree(TTree* tree, std::string name="JetInfo") {
    //}
};

class TtHLeptonInfoBranches {
  public:

    std::vector<int>  idxEl; 
    std::vector<double> ptEl;
    std::vector<double> etaEl;
    std::vector<double> phiEl;
    std::vector<double> EEl;
    std::vector<double> IsoDREl;
    std::vector<double> dR_Iso2DEl;
    std::vector<double> ptrel_Iso2DEl;
    std::vector<double> IsoDRAfterIso2DEl;

    std::vector<int>  idxCleanedEl; 
    std::vector<double> ptCleanedEl;
    std::vector<double> etaCleanedEl;
    std::vector<double> phiCleanedEl;
    std::vector<double> ECleanedEl;

    std::vector<int>  idxMu; 
    std::vector<double> ptMu;
    std::vector<double> etaMu;
    std::vector<double> phiMu;
    std::vector<double> EMu;
    std::vector<double> IsoDRMu;
    std::vector<double> dR_Iso2DMu;
    std::vector<double> ptrel_Iso2DMu;
    std::vector<double> IsoDRAfterIso2DMu;

    std::vector<int>  idxCleanedMu; 
    std::vector<double> ptCleanedMu;
    std::vector<double> etaCleanedMu;
    std::vector<double> phiCleanedMu;
    std::vector<double> ECleanedMu;

    void RegisterTree(TTree *cutTree, std::string name="LeptonInfo") {

      cutTree->Branch("idxEl", &idxEl); 
      cutTree->Branch("ptEl", &ptEl); 
      cutTree->Branch("etaEl", &etaEl);
      cutTree->Branch("phiEl", &phiEl);
      cutTree->Branch("EEl", &EEl);
      cutTree->Branch("IsoDREl", &IsoDREl);
      cutTree->Branch("dR_Iso2DEl", &dR_Iso2DEl);
      cutTree->Branch("ptrel_Iso2DEl", &ptrel_Iso2DEl);
      cutTree->Branch("IsoDRAfterIso2DEl", &IsoDRAfterIso2DEl);

      cutTree->Branch("idxCleanedEl", &idxCleanedEl); 
      cutTree->Branch("ptCleanedEl", &ptCleanedEl); 
      cutTree->Branch("etaCleanedEl", &etaCleanedEl);
      cutTree->Branch("phiCleanedEl", &phiCleanedEl);
      cutTree->Branch("ECleanedEl", &ECleanedEl);

      cutTree->Branch("idxMu", &idxMu); 
      cutTree->Branch("ptMu", &ptMu); 
      cutTree->Branch("etaMu", &etaMu);
      cutTree->Branch("phiMu", &phiMu);
      cutTree->Branch("EMu", &EMu);
      cutTree->Branch("IsoDRMu", &IsoDRMu);
      cutTree->Branch("dR_Iso2DMu", &dR_Iso2DMu);
      cutTree->Branch("ptrel_Iso2DMu", &ptrel_Iso2DMu);
      cutTree->Branch("IsoDRAfterIso2DMu", &IsoDRAfterIso2DMu);

      cutTree->Branch("idxCleanedMu", &idxCleanedMu); 
      cutTree->Branch("ptCleanedMu", &ptCleanedMu); 
      cutTree->Branch("etaCleanedMu", &etaCleanedMu);
      cutTree->Branch("phiCleanedMu", &phiCleanedMu);
      cutTree->Branch("ECleanedMu", &ECleanedMu);
    }

};

#endif 
