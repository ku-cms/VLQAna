/**
 * The program trains an MVA to perform jet assignment for semileptonic decay of a top quark.
 */

#include <TMVA/Factory.h>

#include <TFile.h>

#include <string>
#include <memory>

using namespace std;

int main()
{
  //// Create a log file and a factory0
  string const jobName("SingleTprimevsBkg_Global_WthWt_3");
  TFile infoFile0((string("info0") + jobName + ".root").c_str(), "recreate");
  TFile infoFile1((string("info1") + jobName + ".root").c_str(), "recreate");
  TMVA::Factory factory0(jobName, &infoFile0, "Color=True"); //// tjets
  TMVA::Factory factory1(jobName, &infoFile1, "Color=True"); //// hjets

  //// Specifiy signal and background trees and event weights
  string const filePrefix("/afs/cern.ch/user/d/devdatta/eos/cms/store/user/devdatta/B2GEDMNtupleSkim25Mar2015/");

  TFile sgnTrainFile((filePrefix + "TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> sgnTrainTree(dynamic_cast<TTree *>(sgnTrainFile.Get("Events")));

  TFile sgnExamFile((filePrefix + "TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> sgnExamTree(dynamic_cast<TTree *>(sgnExamFile.Get("Events")));

  TFile bkg0TrainFile((filePrefix + "QCD_HT_1000ToInf_13TeV-madgraph/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg0TrainTree(dynamic_cast<TTree *>(bkg0TrainFile.Get("Events")));

  TFile bkg0ExamFile((filePrefix + "QCD_HT_1000ToInf_13TeV-madgraph/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg0ExamTree(dynamic_cast<TTree *>(bkg0ExamFile.Get("Events")));

  TFile bkg1TrainFile((filePrefix + "TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg1TrainTree(dynamic_cast<TTree *>(bkg1TrainFile.Get("Events")));

  TFile bkg1ExamFile((filePrefix + "TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg1ExamTree(dynamic_cast<TTree *>(bkg1ExamFile.Get("Events")));

  factory0.AddSignalTree(sgnTrainTree.get());
  factory0.AddBackgroundTree(bkg0TrainTree.get());
  //factory0.AddBackgroundTree(bkg1TrainTree.get());
  
  factory1.AddSignalTree(sgnTrainTree.get());
  factory1.AddBackgroundTree(bkg0TrainTree.get());
  //factory1.AddBackgroundTree(bkg1TrainTree.get());
  
  //// Specify the input variables 
  factory0.AddVariable("double_ana_htak4jets_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_ana_htak8jets_SingleTpAna.obj", 'D');
  factory0.AddVariable("uint_ana_ngoodAK4Jets_SingleTpAna.obj", 'I');
  factory0.AddVariable("uint_ana_ngoodAK8Jets_SingleTpAna.obj", 'I');
  factory0.AddVariable("uint_ana_ngoodBTaggedAK4Jets_SingleTpAna.obj", 'I');

  factory0.AddVariable("double_sel_ptbleading_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_etableading_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_ptjforward_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_etajforward_SingleTpAna.obj", 'D');

  factory0.AddVariable("double_sel_pttjet_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_mtjet_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_pthjet_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_mhjet_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_ptth_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_mth_SingleTpAna.obj", 'D');
  factory0.AddVariable("double_sel_detath_SingleTpAna.obj", 'D');

  factory1.AddVariable("double_ana_htak4jets_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_ana_htak8jets_SingleTpAna.obj", 'D');
  factory1.AddVariable("uint_ana_ngoodAK4Jets_SingleTpAna.obj", 'I');
  factory1.AddVariable("uint_ana_ngoodAK8Jets_SingleTpAna.obj", 'I');
  factory1.AddVariable("uint_ana_ngoodBTaggedAK4Jets_SingleTpAna.obj", 'I');

  factory1.AddVariable("double_sel_ptbleading_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_etableading_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_ptjforward_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_etajforward_SingleTpAna.obj", 'D');

  factory1.AddVariable("double_sel_pthjet_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_mhjet_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_ptwjet_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_mwhb_SingleTpAna.obj", 'D');
  factory1.AddVariable("double_sel_drwb_SingleTpAna.obj", 'D');

  factory0.PrepareTrainingAndTestTree("int_sel_evttype_SingleTpAna.obj==0 || int_sel_evttype_SingleTpAna.obj==1","nTrain_Signal=4000:nTrain_Background=4000:nTest_Signal=4000:nTest_Background=4000:SplitMode=Random:NormMode=NumEvents:!V");
  factory0.BookMethod( TMVA::Types::kBDT, jobName + "BDTG0",
      "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=2" );

  factory0.TrainAllMethods();
  factory0.TestAllMethods();
  factory0.EvaluateAllMethods();

  infoFile0.Close() ; 

  factory1.PrepareTrainingAndTestTree("int_sel_evttype_SingleTpAna.obj>=2","nTrain_Signal=4000:nTrain_Background=4000:nTest_Signal=4000:nTest_Background=4000:SplitMode=Random:NormMode=NumEvents:!V");
  factory1.BookMethod( TMVA::Types::kBDT, jobName + "BDTG1",
      "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=2" );
      
  factory1.TrainAllMethods();
  factory1.TestAllMethods();
  factory1.EvaluateAllMethods();

  infoFile1.Close() ; 

  //if (!gROOT->IsBatch()) TMVAGui( infoFile.GetName() );

  return 0; 
}
