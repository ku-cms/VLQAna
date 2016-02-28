#ifndef ANALYSIS_VLQANA_HH4BTREE_HH
#define ANALYSIS_VLQANA_HH4BTREE_HH
#include <string>
#include <TTree.h>

static const int MAX_JETS = 128 ;

class EventInfoBranches {
  public:

    int    runno_ ;
    int    lumisec_ ; 
    int    evtno_;    
    int    bcno_;
    int    time_;
    double htHat_; 
    double evtwt_ ;
    double evtwtPV_;
    double evtwtPVLow_;
    double evtwtPVHigh_;
    int    npv_;
    int    npuTrue_;
    double deta_leading2hjets_;
    double minv_leading2hjets_;
    double minv_leading2hjets_subtr_;
    double pt_leading2hjets_;
    double eta_leading2hjets_;
    double y_leading2hjets_;
    double phi_leading2hjets_;
    int    nsubjetsBTaggedCSVL_; 
    double btagsf_;
    double btagsf_bcUp_;
    double btagsf_bcDown_;
    double btagsf_lUp_;
    double btagsf_lDown_;
    double ht_ ; 
    std::vector<std::pair<int, double> > lhewts_ ; 

    void RegisterTree(TTree* tree, std::string name="SelectedEvents") {
      tree->Branch((name+"_runno").c_str(),&runno_, (name+"_runno/I").c_str());
      tree->Branch((name+"_lumisec").c_str(),&lumisec_, (name+"_lumisec/I").c_str());
      tree->Branch((name+"_evtno").c_str(),&evtno_, (name+"_evtno/I").c_str());
      tree->Branch((name+"_bcno").c_str(),&bcno_, (name+"_bcno/I").c_str());
      tree->Branch((name+"_time").c_str(),&time_, (name+"_time/I").c_str());
      tree->Branch((name+"_htHat").c_str(), &htHat_, (name+"_htHat/D").c_str()) ; 
      tree->Branch((name+"_evtwt").c_str(), &evtwt_, (name+"_evtwt/D").c_str()) ; 
      tree->Branch((name+"_evtwtPV").c_str(), &evtwtPV_, (name+"_evtwtPV/D").c_str()) ; 
      tree->Branch((name+"_evtwtPVLow").c_str(), &evtwtPVLow_, (name+"_evtwtPVLow/D").c_str()) ; 
      tree->Branch((name+"_evtwtPVHigh").c_str(), &evtwtPVHigh_, (name+"_evtwtPVHigh/D").c_str()) ; 
      tree->Branch((name+"_npv").c_str(),&npv_, (name+"_npv/I").c_str());
      tree->Branch((name+"_npuTrue").c_str(),&npuTrue_, (name+"_npuTrue/I").c_str());
      tree->Branch((name+"_deta_leading2hjets").c_str(), &deta_leading2hjets_, (name+"_deta_leading2hjets/D").c_str()) ; 
      tree->Branch((name+"_minv_leading2hjets").c_str(), &minv_leading2hjets_, (name+"_minv_leading2hjets/D").c_str()) ; 
      tree->Branch((name+"_minv_leading2hjets_subtr").c_str(), &minv_leading2hjets_subtr_, (name+"_minv_leading2hjets_subtr/D").c_str()) ; 
      tree->Branch((name+"_pt_leading2hjets").c_str(), &pt_leading2hjets_, (name+"_pt_leading2hjets/D").c_str()) ; 
      tree->Branch((name+"_eta_leading2hjets").c_str(), &eta_leading2hjets_, (name+"_eta_leading2hjets/D").c_str()) ; 
      tree->Branch((name+"_y_leading2hjets").c_str(), &y_leading2hjets_, (name+"_y_leading2hjets/D").c_str()) ; 
      tree->Branch((name+"_phi_leading2hjets").c_str(), &phi_leading2hjets_, (name+"_phi_leading2hjets/D").c_str()) ; 
      tree->Branch((name+"_nsubjetsBTaggedCSVL").c_str(), &nsubjetsBTaggedCSVL_, (name+"_nsubjetsBTaggedCSVL/I").c_str()) ; 
      tree->Branch((name+"_btagsf").c_str(), &btagsf_, (name+"_btagsf/D").c_str()) ; 
      tree->Branch((name+"_btagsf_bcUp").c_str(), &btagsf_bcUp_, (name+"_btagsf_bcUp/D").c_str()) ; 
      tree->Branch((name+"_btagsf_bcDown").c_str(), &btagsf_bcDown_, (name+"_btagsf_bcDown/D").c_str()) ; 
      tree->Branch((name+"_btagsf_lUp").c_str(), &btagsf_lUp_, (name+"_btagsf_lUp/D").c_str()) ; 
      tree->Branch((name+"_btagsf_lDown").c_str(), &btagsf_lDown_, (name+"_btagsf_lDown/D").c_str()) ; 
      tree->Branch((name+"_lhewts").c_str(), &lhewts_) ;  
      tree->Branch((name+"_ht").c_str(),&ht_, (name+"_ht/I").c_str());
    }

    void ReadTree(TTree* tree, std::string name="SelectedEvents") {
      tree->SetBranchAddress((name+"_runno").c_str(), &runno_) ; 
      tree->SetBranchAddress((name+"_lumisec").c_str(), &lumisec_) ; 
      tree->SetBranchAddress((name+"_evtno").c_str(), &evtno_) ; 
      tree->SetBranchAddress((name+"_bcno").c_str(), &bcno_) ; 
      tree->SetBranchAddress((name+"_time").c_str(), &time_) ; 
      tree->SetBranchAddress((name+"_htHat").c_str(), &htHat_) ; 
      tree->SetBranchAddress((name+"_evtwt").c_str(), &evtwt_) ; 
      tree->SetBranchAddress((name+"_evtwtPV").c_str(), &evtwtPV_) ; 
      tree->SetBranchAddress((name+"_evtwtPVLow").c_str(), &evtwtPVLow_) ; 
      tree->SetBranchAddress((name+"_evtwtPVHigh").c_str(), &evtwtPVHigh_) ; 
      tree->SetBranchAddress((name+"_npv").c_str(), &npv_) ; 
      tree->SetBranchAddress((name+"_npuTrue").c_str(), &npuTrue_) ; 
      tree->SetBranchAddress((name+"_deta_leading2hjets").c_str(), &deta_leading2hjets_) ; 
      tree->SetBranchAddress((name+"_minv_leading2hjets").c_str(), &minv_leading2hjets_) ; 
      tree->SetBranchAddress((name+"_minv_leading2hjets_subtr").c_str(), &minv_leading2hjets_subtr_) ; 
      tree->SetBranchAddress((name+"_pt_leading2hjets").c_str(), &pt_leading2hjets_) ; 
      tree->SetBranchAddress((name+"_eta_leading2hjets").c_str(), &eta_leading2hjets_) ; 
      tree->SetBranchAddress((name+"_y_leading2hjets").c_str(), &y_leading2hjets_) ; 
      tree->SetBranchAddress((name+"_phi_leading2hjets").c_str(), &phi_leading2hjets_) ; 
      tree->SetBranchAddress((name+"_nsubjetsBTaggedCSVL").c_str(), &nsubjetsBTaggedCSVL_) ; 
      tree->SetBranchAddress((name+"_btagsf").c_str(), &btagsf_) ; 
      tree->SetBranchAddress((name+"_btagsf_bcUp").c_str(), &btagsf_bcUp_) ; 
      tree->SetBranchAddress((name+"_btagsf_bcDown").c_str(), &btagsf_bcDown_) ; 
      tree->SetBranchAddress((name+"_btagsf_lUp").c_str(), &btagsf_lUp_) ; 
      tree->SetBranchAddress((name+"_btagsf_lDown").c_str(), &btagsf_lDown_) ; 
      tree->SetBranchAddress((name+"_lhewts").c_str(), &lhewts_) ; 
      tree->SetBranchAddress((name+"_ht").c_str(), &ht_) ; 
    }

};

class JetInfoBranches {
  public: 

    int   njets; 
    int   Index[MAX_JETS];
    int   ParentIndex[MAX_JETS]; // used for subjets

    double Pt[MAX_JETS];
    double Eta[MAX_JETS];
    double Phi[MAX_JETS];
    double Mass[MAX_JETS];
    double MassPruned[MAX_JETS]; 
    double MassSoftDrop[MAX_JETS]; 
    double tau1[MAX_JETS]; 
    double tau2[MAX_JETS]; 
    double tau3[MAX_JETS]; 
    double hadFlavour[MAX_JETS]; 
    double CSVIVFv2[MAX_JETS]; 
    double nhf[MAX_JETS]; 
    double chf[MAX_JETS]; 
    double emf[MAX_JETS]; 
    double phf[MAX_JETS]; 
    double muf[MAX_JETS]; 
    int    nconsts[MAX_JETS]; 
    int    nsubjets[MAX_JETS]; 
    double hadFlavourSubjet0[MAX_JETS]; 
    double hadFlavourSubjet1[MAX_JETS]; 
    double ptSubjet0[MAX_JETS]; 
    double ptSubjet1[MAX_JETS]; 
    double etaSubjet0[MAX_JETS]; 
    double etaSubjet1[MAX_JETS]; 
    double csvSubjet0[MAX_JETS]; 
    double csvSubjet1[MAX_JETS]; 
    double groomedMassCorr[MAX_JETS]; 
    int    nsubjetsBTaggedCSVL[MAX_JETS]; 

    void RegisterTree(TTree *tree, std::string name="JetInfo") {
      tree->Branch((name+"_njets").c_str(), &njets, (name+"_njets/I").c_str() );
      tree->Branch((name+"_Index").c_str(), &Index[0], (name+".Index["+name+"_njets]/I").c_str());
      tree->Branch((name+"_Pt").c_str(), &Pt[0], (name+".Pt["+name+"_njets]/D").c_str());
      tree->Branch((name+"_Eta").c_str(), &Eta[0], (name+".Eta["+name+"_njets]/D").c_str());
      tree->Branch((name+"_Phi").c_str(), &Phi[0], (name+".Phi["+name+"_njets]/D").c_str());
      tree->Branch((name+"_Mass").c_str(), &Mass[0] , (name+".Mass["+name+"_njets]/D").c_str()); 
      tree->Branch((name+"_MassPruned").c_str(), &MassPruned[0], (name+".MassPruned["+name+"_njets]/D").c_str()); 
      tree->Branch((name+"_MassSoftDrop").c_str(), &MassSoftDrop[0], (name+".MassSoftDrop["+name+"_njets]/D").c_str()); 
      tree->Branch((name+"_tau1").c_str(), &tau1[0], (name+".tau1["+name+"_njets]/D").c_str()); 
      tree->Branch((name+"_tau2").c_str(), &tau2[0], (name+".tau2["+name+"_njets]/D").c_str()); 
      tree->Branch((name+"_tau3").c_str(), &tau3[0], (name+".tau3["+name+"_njets]/D").c_str());       
      tree->Branch((name+"_hadFlavour").c_str(), &hadFlavour[0], (name+".hadFlavour["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_CSVIVFv2").c_str(), &CSVIVFv2[0], (name+".CSVIVFv2["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_nhf").c_str(), &nhf[0], (name+".nhf["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_chf").c_str(), &chf[0], (name+".chf["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_emf").c_str(), &emf[0], (name+".emf["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_phf").c_str(), &phf[0], (name+".phf["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_muf").c_str(), &muf[0], (name+".muf["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_muf").c_str(), &muf[0], (name+".muf["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_nconsts").c_str(), &nconsts[0], (name+".nconsts["+name+"_njets]/I").c_str() );
      tree->Branch((name+"_nsubjets").c_str(), &nsubjets[0], (name+".nsubjets["+name+"_njets]/I").c_str() );
      tree->Branch((name+"_hadFlavourSubjet0").c_str(), &hadFlavourSubjet0[0], (name+".hadFlavourSubjet0["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_hadFlavourSubjet1").c_str(), &hadFlavourSubjet1[0], (name+".hadFlavourSubjet1["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_ptSubjet0").c_str(), &ptSubjet0[0], (name+".ptSubjet0["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_ptSubjet1").c_str(), &ptSubjet1[0], (name+".ptSubjet1["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_etaSubjet0").c_str(), &etaSubjet0[0], (name+".etaSubjet0["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_etaSubjet1").c_str(), &etaSubjet1[0], (name+".etaSubjet1["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_csvSubjet0").c_str(), &csvSubjet0[0], (name+".csvSubjet0["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_csvSubjet1").c_str(), &csvSubjet1[0], (name+".csvSubjet1["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_groomedMassCorr").c_str(), &groomedMassCorr[0], (name+".groomedMassCorr["+name+"_njets]/D").c_str() );
      tree->Branch((name+"_nsubjetsBTaggedCSVL").c_str(), &nsubjetsBTaggedCSVL[0], (name+".nsubjetsBTaggedCSVL["+name+"_njets]/I").c_str() );
    }

    void ReadTree(TTree* tree, std::string name="JetInfo") {
      tree->SetBranchAddress((name+"_njets").c_str(), &njets);
      tree->SetBranchAddress((name+"_Index").c_str(), &Index[0]);
      tree->SetBranchAddress((name+"_Pt").c_str(), &Pt[0]);
      tree->SetBranchAddress((name+"_Eta").c_str(), &Eta[0]);
      tree->SetBranchAddress((name+"_Phi").c_str(), &Phi[0]);
      tree->SetBranchAddress((name+"_Mass").c_str(), &Mass[0]); 
      tree->SetBranchAddress((name+"_MassPruned").c_str(), &MassPruned[0]); 
      tree->SetBranchAddress((name+"_MassSoftDrop").c_str(), &MassSoftDrop[0]); 
      tree->SetBranchAddress((name+"_tau1").c_str(), &tau1[0]); 
      tree->SetBranchAddress((name+"_tau2").c_str(), &tau2[0]); 
      tree->SetBranchAddress((name+"_tau3").c_str(), &tau3[0]);       
      tree->SetBranchAddress((name+"_hadFlavour").c_str(), &hadFlavour[0]);
      tree->SetBranchAddress((name+"_CSVIVFv2").c_str(), &CSVIVFv2[0]);
      tree->SetBranchAddress((name+"_nhf").c_str(), &nhf[0]);
      tree->SetBranchAddress((name+"_chf").c_str(), &chf[0]);
      tree->SetBranchAddress((name+"_emf").c_str(), &emf[0]);
      tree->SetBranchAddress((name+"_phf").c_str(), &phf[0]);
      tree->SetBranchAddress((name+"_muf").c_str(), &muf[0]);
      tree->SetBranchAddress((name+"_nconsts").c_str(), &nconsts[0]      ) ; 
      tree->SetBranchAddress((name+"_nsubjets").c_str(), &nsubjets[0]      ) ; 
      tree->SetBranchAddress((name+"_hadFlavourSubjet0").c_str(), &hadFlavourSubjet0[0]) ; 
      tree->SetBranchAddress((name+"_hadFlavourSubjet1").c_str(), &hadFlavourSubjet1[0]) ; 
      tree->SetBranchAddress((name+"_ptSubjet0").c_str(), &ptSubjet0[0]) ; 
      tree->SetBranchAddress((name+"_ptSubjet1").c_str(), &ptSubjet1[0]) ; 
      tree->SetBranchAddress((name+"_etaSubjet0").c_str(), &etaSubjet0[0]) ; 
      tree->SetBranchAddress((name+"_etaSubjet1").c_str(), &etaSubjet1[0]) ; 
      tree->SetBranchAddress((name+"_csvSubjet0").c_str(), &csvSubjet0[0]) ; 
      tree->SetBranchAddress((name+"_csvSubjet1").c_str(), &csvSubjet1[0]) ; 
      tree->SetBranchAddress((name+"_groomedMassCorr").c_str(), &groomedMassCorr[0]) ; 
      tree->SetBranchAddress((name+"_nsubjetsBTaggedCSVL").c_str(), &nsubjetsBTaggedCSVL[0]) ; 
    }

};
#endif 
