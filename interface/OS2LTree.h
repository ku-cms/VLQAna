#ifndef ANALYSIS_VLQANA_OS2LTREE_HH
#define ANALYSIS_VLQANA_OS2LTREE_HH
#include <string>
#include <TTree.h>

static const int MAX_JETS = 128 ;

namespace os2l {

  class OS2LAnaTree {

    public:

      unsigned int t_evtInfoLumiBlock;
      unsigned int t_evtInfoRunNumber;
      ULong64_t    t_evtInfoEventNumber;

      //std::vector<std::pair<std::string, bool> > t_trigDecision ;
      //std::vector<tuple<std::string, bool,int> > t_trigDecision ;

      int ta_npv;
      int t_puNtrueInt;

      std::vector<string> t_TriggerNameTree;
      std::vector<float>  t_TriggerBitTree;
      std::vector<int>    t_TriggerPrescaleTree;
      std::vector<float>  t_elPt;
      std::vector<float>  t_elEta;
      std::vector<float>  t_elPhi;
      std::vector<float>  t_elE;
      std::vector<float>  t_elCharge;
      std::vector<float>  t_elIso03;
      std::vector<float>  t_elecIsLoose; 
      std::vector<float>  t_elecIsMedium; 
      std::vector<float>  t_elecIsTight; 
      std::vector<float>  t_elecIsVeto;

      std::vector<float>  t_muPt;
      std::vector<float>  t_muEta;
      std::vector<float>  t_muPhi;
      std::vector<float>  t_muE;
      std::vector<float>  t_muIso04;
      std::vector<float>  t_muCharge;
      std::vector<float>  t_muonIsTight; 
      std::vector<float>  t_muonIsLoose; 
      std::vector<float>  t_muonIsGlobal; 
      std::vector<float>  t_muonIsPFMuon;
      std::vector<float>  t_muonIsTracker;

      std::vector<float>  t_jetAK4Pt;
      std::vector<float>  t_jetAK4Eta;
      std::vector<float>  t_jetAK4Phi;
      std::vector<float>  t_jetAK4E;
      std::vector<float>  t_jetAK4GenJetPt;
      std::vector<float>  t_jetAK4GenJetEta;
      std::vector<float>  t_jetAK4GenJetPhi;
      std::vector<float>  t_jetAK4GenJetE;
      std::vector<float>  t_jetAK4CSV;
      std::vector<float>  t_jetAK4Mass;
      std::vector<float>  t_jetAK4HadronFlavour;
      std::vector<float>  t_jetAK4PartonFlavour;

      std::vector<float>  t_jetAK4BPt;
      std::vector<float>  t_jetAK4BEta;
      std::vector<float>  t_jetAK4BPhi;
      std::vector<float>  t_jetAK4BE;
      std::vector<float>  t_jetAK4BGenJetPt;
      std::vector<float>  t_jetAK4BGenJetEta;
      std::vector<float>  t_jetAK4BGenJetPhi;
      std::vector<float>  t_jetAK4BGenJetE;
      std::vector<float>  t_jetAK4BCSV;
      std::vector<float>  t_jetAK4BMass;
      std::vector<float>  t_jetAK4BHadronFlavour;
      std::vector<float>  t_jetAK4BPartonFlavour;

      double t_HT;
      double t_ST;

      double t_btagsf;
      double t_btagsf_bcUp;
      double t_btagsf_bcDown;
      double t_btagsf_lUp;
      double t_btagsf_lDown;

      std::vector<float>  t_jetAK8Pt;
      std::vector<float>  t_jetAK8Eta;
      std::vector<float>  t_jetAK8Phi;
      std::vector<float>  t_jetAK8E;

      std::vector<float>  t_jetAK8GenJetPt;
      std::vector<float>  t_jetAK8GenJetEta;
      std::vector<float>  t_jetAK8GenJetPhi;
      std::vector<float>  t_jetAK8GenJetE;

      std::vector<float>  t_jetAK8CSV;
      std::vector<float>  t_jetAK8Mass;
      std::vector<float>  t_jetAK8HadronFlavour;
      std::vector<float>  t_jetAK8PartonFlavour;
      std::vector<float>  t_jetAK8_tau1;
      std::vector<float>  t_jetAK8_tau2;
      std::vector<float>  t_jetAK8_tau3;

      std::vector<float>  t_jetAK8_MassPruned;
      std::vector<float>  t_jetAK8_SoftDropMass;
      std::vector<float>  t_jetAK8_NSubJets;

      std::vector<float>  t_genPartPt;
      std::vector<float>  t_genPartEta;
      std::vector<float>  t_genPartPhi;
      std::vector<float>  t_genPartE;
      std::vector<int>    t_genPartID;
      std::vector<int>    t_genPartStatus;
      std::vector<int>    t_genPartMom1ID;
      std::vector<int>    t_genPartMom2ID;
      std::vector<int>    t_genPartDau1ID;
      std::vector<int>    t_genPartDau2ID;
      std::vector<int>    t_genPartMom1Status;
      std::vector<int>    t_genPartMom2Status;
      std::vector<int>    t_genPartDau1Status;
      std::vector<int>    t_genPartDau2Status;

      std::vector<float>  t_metPhi;
      std::vector<float>  t_metPt;
      std::vector<float>  t_metEta;
      std::vector<float>  t_metE;

      void clearTreeVectors() {
        t_TriggerNameTree     .clear();
        t_TriggerBitTree      .clear();
        t_TriggerPrescaleTree .clear();

        t_elPt                .clear();
        t_elPhi               .clear();
        t_elEta               .clear();
        t_elE                 .clear();
        t_elCharge            .clear();
        t_elIso03             .clear();
        t_elecIsLoose         .clear(); 
        t_elecIsMedium        .clear(); 
        t_elecIsTight         .clear(); 
        t_elecIsVeto          .clear();

        t_muPt                .clear();
        t_muPhi               .clear();
        t_muEta               .clear();
        t_muE                 .clear();
        t_muCharge            .clear();
        t_muIso04             .clear();
        t_muonIsTight         .clear();
        t_muonIsLoose         .clear();
        t_muonIsGlobal        .clear();
        t_muonIsPFMuon        .clear();
        t_muonIsTracker       .clear();

        t_jetAK4Pt            .clear();
        t_jetAK4Eta           .clear();
        t_jetAK4Phi           .clear();
        t_jetAK4E             .clear();
        t_jetAK4CSV           .clear(); 
        t_jetAK4Mass          .clear();
        t_jetAK4HadronFlavour .clear();
        t_jetAK4PartonFlavour .clear();

        t_jetAK4BPt           .clear();
        t_jetAK4BEta          .clear();
        t_jetAK4BPhi          .clear();
        t_jetAK4BE            .clear();
        t_jetAK4BCSV          .clear(); 
        t_jetAK4BMass         .clear();
        t_jetAK4BHadronFlavour.clear();
        t_jetAK4BPartonFlavour.clear();

        t_jetAK8Pt            .clear();
        t_jetAK8Eta           .clear();
        t_jetAK8Phi           .clear();
        t_jetAK8E             .clear();
        t_jetAK8CSV           .clear();
        t_jetAK8Mass          .clear();
        t_jetAK8HadronFlavour .clear();
        t_jetAK8PartonFlavour .clear();
        t_jetAK8_tau1         .clear();
        t_jetAK8_tau2         .clear();
        t_jetAK8_tau3         .clear();
        t_jetAK8_MassPruned   .clear();
        t_jetAK8_SoftDropMass .clear();
        t_jetAK8_NSubJets     .clear();

        t_jetAK4GenJetPt      .clear();
        t_jetAK4GenJetPhi     .clear();
        t_jetAK4GenJetEta     .clear();
        t_jetAK4GenJetE       .clear();
        
        t_jetAK4BGenJetPt     .clear();
        t_jetAK4BGenJetPhi    .clear();
        t_jetAK4BGenJetEta    .clear();
        t_jetAK4BGenJetE      .clear();

        t_jetAK8GenJetPt      .clear();
        t_jetAK8GenJetEta     .clear();
        t_jetAK8GenJetPhi     .clear();
        t_jetAK8GenJetE       .clear();

        t_genPartPt           .clear();
        t_genPartPhi          .clear();
        t_genPartEta          .clear();
        t_genPartE            .clear();
        t_genPartID           .clear();
        t_genPartStatus       .clear();
        t_genPartMom1ID       .clear();
        t_genPartMom2ID       .clear();
        t_genPartDau1ID       .clear();
        t_genPartDau2ID       .clear();
        t_genPartMom1Status   .clear();
        t_genPartMom2Status   .clear();
        t_genPartDau1Status   .clear();
        t_genPartDau2Status   .clear();

        t_metPt               .clear(); 
        t_metPhi              .clear();
        t_metEta              .clear();
        t_metE                .clear();
         
        return ; 
      } //// clearTreeVectors 

      void RegisterTree(TTree* tree, std::string name="tree") {

        tree->Branch("t_evtInfoLumiBlock"    ,&t_evtInfoLumiBlock   ,"t_evtInfoLumiBlock/i" );
        tree->Branch("t_evtInfoRunNumber"    ,&t_evtInfoRunNumber   ,"t_evtInfoRunNumber/i" );
        tree->Branch("t_evtInfoEventNumber"  ,&t_evtInfoEventNumber ,"t_evtInfoEventNumber/l" );

        tree->Branch("t_TriggerNameTree"     ,&t_TriggerNameTree );
        tree->Branch("t_TriggerBitTree"      ,&t_TriggerBitTree );
        tree->Branch("t_TriggerPrescaleTree" ,&t_TriggerPrescaleTree );

        //tree->Branch("t_trigDecision"        , "vector< std::pair <std::string, bool>>"  , &t_trigDecision );

        tree->Branch("ta_npv"       ,&ta_npv       ,"ta_npv/I" );
        tree->Branch("t_puNtrueInt" ,&t_puNtrueInt ,"t_puNtrueInt/i");

        tree->Branch("t_elPt"         ,&t_elPt );
        tree->Branch("t_elPhi"        ,&t_elPhi );
        tree->Branch("t_elEta"        ,&t_elEta );
        tree->Branch("t_elE"          ,&t_elE );
        tree->Branch("t_elCharge"     ,&t_elCharge );
        tree->Branch("t_elIso03"      ,&t_elIso03 );  
        tree->Branch("t_elecIsLoose"  ,&t_elecIsLoose ); 
        tree->Branch("t_elecIsMedium" ,&t_elecIsMedium); 
        tree->Branch("t_elecIsTight"  ,&t_elecIsTight ); 
        tree->Branch("t_elecIsVeto"   ,&t_elecIsVeto  );

        tree->Branch("t_muPt"          ,&t_muPt );
        tree->Branch("t_muPhi"         ,&t_muPhi );
        tree->Branch("t_muEta"         ,&t_muEta );
        tree->Branch("t_muE"           ,&t_muE );
        tree->Branch("t_muCharge"      ,&t_muCharge );
        tree->Branch("t_muIso04"       ,&t_muIso04 );
        tree->Branch("t_muonIsTight"   ,&t_muonIsTight  ); 
        tree->Branch("t_muonIsLoose"   ,&t_muonIsLoose  ); 
        tree->Branch("t_muonIsGlobal"  ,&t_muonIsGlobal ); 
        tree->Branch("t_muonIsPFMuon"  ,&t_muonIsPFMuon ); 
        tree->Branch("t_muonIsTracker" ,&t_muonIsTracker); 

        tree->Branch("t_jetAK4Pt"                ,&t_jetAK4Pt );
        tree->Branch("t_jetAK4Phi"               ,&t_jetAK4Phi );
        tree->Branch("t_jetAK4Eta"               ,&t_jetAK4Eta );
        tree->Branch("t_jetAK4E"                 ,&t_jetAK4E );
        tree->Branch("t_jetAK4CSV"               ,&t_jetAK4CSV );
        tree->Branch("t_jetAK4Mass"              ,&t_jetAK4Mass );
        tree->Branch("t_jetAK4HadronFlavour"     ,&t_jetAK4HadronFlavour );
        tree->Branch("t_jetAK4PartonFlavour"     ,&t_jetAK4PartonFlavour );

        tree->Branch("t_jetAK4BPt"            ,&t_jetAK4BPt );
        tree->Branch("t_jetAK4BPhi"           ,&t_jetAK4BPhi );
        tree->Branch("t_jetAK4BEta"           ,&t_jetAK4BEta );
        tree->Branch("t_jetAK4BE"             ,&t_jetAK4BE );
        tree->Branch("t_jetAK4BCSV"           ,&t_jetAK4BCSV );
        tree->Branch("t_jetAK4BMass"          ,&t_jetAK4BMass );
        tree->Branch("t_jetAK4BHadronFlavour" ,&t_jetAK4BHadronFlavour );
        tree->Branch("t_jetAK4BPartonFlavour" ,&t_jetAK4BPartonFlavour );

        tree->Branch("t_HT", &t_HT, "t_HT/D") ; 
        tree->Branch("t_ST", &t_ST, "t_ST/D") ; 

        tree->Branch("t_btagsf"          , &t_btagsf, "t_btagsf/D" );
        tree->Branch("t_btagsf_bcUp"     , &t_btagsf_bcUp, "t_btagsf_bcUp/D" );
        tree->Branch("t_btagsf_bcDown"   , &t_btagsf_bcDown, "t_btagsf_bcDown/D" );
        tree->Branch("t_btagsf_lUp"      , &t_btagsf_lUp, "t_btagsf_lUp/D" );
        tree->Branch("t_btagsf_lDown"    , &t_btagsf_lDown, "t_btagsf_lDown/D" );    

        tree->Branch("t_jetAK8Pt"               , &t_jetAK8Pt );
        tree->Branch("t_jetAK8Phi"              , &t_jetAK8Phi );
        tree->Branch("t_jetAK8Eta"              , &t_jetAK8Eta );
        tree->Branch("t_jetAK8E"                , &t_jetAK8E );
        tree->Branch("t_jetAK8CSV"              , &t_jetAK8CSV );
        tree->Branch("t_jetAK8Mass"             , &t_jetAK8Mass );
        tree->Branch("t_jetAK8HadronFlavour"    , &t_jetAK8HadronFlavour );
        tree->Branch("t_jetAK8PartonFlavour"    , &t_jetAK8PartonFlavour );
        tree->Branch("t_jetAK8_tau1"            , &t_jetAK8_tau1        );
        tree->Branch("t_jetAK8_tau2"            , &t_jetAK8_tau2        );
        tree->Branch("t_jetAK8_tau3"            , &t_jetAK8_tau3        );
        tree->Branch("t_jetAK8_MassPruned"      , &t_jetAK8_MassPruned  );
        tree->Branch("t_jetAK8_SoftDropMass"    , &t_jetAK8_SoftDropMass);
        tree->Branch("t_jetAK8_NSubJets"        , &t_jetAK8_NSubJets    );

        tree->Branch("t_jetAK4GenJetPt"         ,&t_jetAK4GenJetPt );
        tree->Branch("t_jetAK4GenJetPhi"        ,&t_jetAK4GenJetPhi );
        tree->Branch("t_jetAK4GenJetEta"        ,&t_jetAK4GenJetEta );
        tree->Branch("t_jetAK4GenJetE"          ,&t_jetAK4GenJetE );

        tree->Branch("t_jetAK4BGenJetPt"        ,&t_jetAK4BGenJetPt );
        tree->Branch("t_jetAK4BGenJetPhi"       ,&t_jetAK4BGenJetPhi );
        tree->Branch("t_jetAK4BGenJetEta"       ,&t_jetAK4BGenJetEta );
        tree->Branch("t_jetAK4BGenJetE"         ,&t_jetAK4BGenJetE );

        tree->Branch("t_jetAK8GenJetPt"         ,&t_jetAK8GenJetPt );
        tree->Branch("t_jetAK8GenJetPhi"        ,&t_jetAK8GenJetPhi );
        tree->Branch("t_jetAK8GenJetEta"        ,&t_jetAK8GenJetEta );
        tree->Branch("t_jetAK8GenJetE"          ,&t_jetAK8GenJetE );

        tree->Branch("t_genPartPt"              ,&t_genPartPt        );
        tree->Branch("t_genPartPhi"             ,&t_genPartPhi       );
        tree->Branch("t_genPartEta"             ,&t_genPartEta       );
        tree->Branch("t_genPartE"               ,&t_genPartE         );
        tree->Branch("t_genPartID"              ,&t_genPartID        );
        tree->Branch("t_genPartStatus"          ,&t_genPartStatus    );
        tree->Branch("t_genPartMom1ID"          ,&t_genPartMom1ID    );
        tree->Branch("t_genPartMom2ID"          ,&t_genPartMom2ID    );
        tree->Branch("t_genPartDau1ID"          ,&t_genPartDau1ID    );
        tree->Branch("t_genPartDau2ID"          ,&t_genPartDau2ID    );
        tree->Branch("t_genPartMom1Status"      ,&t_genPartMom1Status);
        tree->Branch("t_genPartMom2Status"      ,&t_genPartMom2Status);
        tree->Branch("t_genPartDau1Status"      ,&t_genPartDau1Status);
        tree->Branch("t_genPartDau2Status"      ,&t_genPartDau2Status);

        tree->Branch("t_metPt"  ,&t_metPt );
        tree->Branch("t_metPhi" ,&t_metPhi);
        tree->Branch("t_metEta" ,&t_metEta);
        tree->Branch("t_metE"   ,&t_metE  );

        return;

      } //// RegisterTree

  }; //// class OS2LAnaTree 

} //// namespace os2l

#endif 
