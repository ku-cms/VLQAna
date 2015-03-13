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
  // Create a log file and a factory
  string const jobName("SingleTprimevsBkg_Global_WthWt_2");
  TFile infoFile((string("info") + jobName + ".root").c_str(), "recreate");
  TMVA::Factory factory(jobName, &infoFile, "Color=True");

  // Specifiy signal and background trees and event weights
  string const filePrefix("/afs/cern.ch/user/d/devdatta/eos/cms/store/user/devdatta/");

  TFile sgnTrainFile((filePrefix + "TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/crab_TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/150305_175855/0000/SingleTprimeAnaEvts_1.root").c_str());
  unique_ptr<TTree> sgnTrainTree(dynamic_cast<TTree *>(sgnTrainFile.Get("Events")));

  TFile sgnExamFile((filePrefix + "TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/crab_TprimeJetToTH_allHdecays_M1200GeV_Tune4C_13TeV-madgraph-tauola/150305_175855/0000/SingleTprimeAnaEvts_1.root").c_str());
  unique_ptr<TTree> sgnExamTree(dynamic_cast<TTree *>(sgnExamFile.Get("Events")));

  TFile bkg0TrainFile((filePrefix + "TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/crab_TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/150305_175919/0000/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg0TrainTree(dynamic_cast<TTree *>(bkg0TrainFile.Get("Events")));

  TFile bkg0ExamFile((filePrefix + "TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/crab_TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/150305_175919/0000/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg0ExamTree(dynamic_cast<TTree *>(bkg0ExamFile.Get("Events")));

  TFile bkg1TrainFile((filePrefix + "QCD_HT_1000ToInf_13TeV-madgraph/crab_QCD_HT_1000ToInf_13TeV-madgraph/150305_175926/0000/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg1TrainTree(dynamic_cast<TTree *>(bkg1TrainFile.Get("Events")));

  TFile bkg1ExamFile((filePrefix + "QCD_HT_1000ToInf_13TeV-madgraph/crab_QCD_HT_1000ToInf_13TeV-madgraph/150305_175926/0000/SingleTprimeAnaEvts.root").c_str());
  unique_ptr<TTree> bkg1ExamTree(dynamic_cast<TTree *>(bkg1ExamFile.Get("Events")));

  factory.AddSignalTree(sgnTrainTree.get(), 0.55);
  factory.AddBackgroundTree(bkg0TrainTree.get(), 0.0000128);
  factory.AddBackgroundTree(bkg1TrainTree.get(), 454);

  //factory.AddSignalTree(sgnExamTree.get(), 1., TMVA::Types::kTesting);
  //factory.AddBackgroundTree(bkg0ExamTree.get(), 1., TMVA::Types::kTesting);

  //factory.SetWeightExpression("Weight");

  // Specify the input variables 
  factory.AddVariable("double_ana_pt1stAK8_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_pt2ndAK8_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_mass1stAK8_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_mass2ndAK8_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_MassLeading2AK8_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_DeltaEtaLeading2AK8_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_maxetaak4_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_htak4jets_SingleTpAna.obj", 'D');
  factory.AddVariable("double_ana_htak8jets_SingleTpAna.obj", 'D');
  factory.AddVariable("int_ana_ngoodAK4Jets_SingleTpAna.obj", 'I');
  factory.AddVariable("int_ana_ngoodAK8Jets_SingleTpAna.obj", 'I');
  factory.AddVariable("int_ana_ngoodBTaggedAK4Jets_SingleTpAna.obj", 'I');
  factory.AddVariable("int_ana_nWJets_SingleTpAna.obj", 'I');
  factory.AddVariable("int_ana_nHJets_SingleTpAna.obj", 'I');

  // Make the factory copy the trees
  //factory.PrepareTrainingAndTestTree("", "NormMode=EqualNumEvents");
  factory.PrepareTrainingAndTestTree("","nTrain_Signal=2000:nTrain_Background=4000:nTest_Signal=2000:nTest_Background=2000:SplitMode=Random:NormMode=NumEvents:!V");

  // Book a BFGS NN
  factory.BookMethod(TMVA::Types::kMLP, jobName + "_BFGS",
      "VarTransform=N:NeuronType=tanh:NCycles=500:HiddenLayers=30:TrainingMethod=BFGS:TestRate=5");

  //// Boosted Decision Trees Gradient Boost
  factory.BookMethod( TMVA::Types::kBDT, jobName + "BDTG",
      "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=2" );

  //// Boosted Decision Trees Adaptive Boost
  factory.BookMethod( TMVA::Types::kBDT, jobName + "BDT",
      "!H:!V:NTrees=1000:MinNodeSize=1.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.3:SeparationType=GiniIndex:nCuts=20" );

  // Train and test the MVA
  factory.TrainAllMethods();
  factory.TestAllMethods();
  factory.EvaluateAllMethods();

  infoFile.Close() ; 

  //if (!gROOT->IsBatch()) TMVAGui( infoFile.GetName() );

  return 0; 
}
