#include <iostream>
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

#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/Candidate.h"

#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/JetID.h"

#include <TFile.h>
#include <TF1.h>
#include <TH1D.h>
#include <TLorentzVector.h>

using namespace std;

class MassReco : public edm::EDFilter {
public:
  explicit MassReco(const edm::ParameterSet&);
  ~MassReco();

private:
  virtual void beginJob() override;
  virtual bool filter(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  pair<double, double> vector_eval(vector<pair<double, double> >);
  double resolvedChi2(vector<TLorentzVector>, TLorentzVector, double, double);
  double boostedChi2(vector<TLorentzVector>, TLorentzVector, TLorentzVector, double, double, double);
  pair<double, double> doBoostedReco(vector<vlq::Jet>, TLorentzVector, double, TLorentzVector, double);
  pair<double, double> doResolvedReco(vector<vlq::Jet>, double, TLorentzVector);
  

  edm::EDGetTokenT<vector<float> >     elPt_t;
  edm::EDGetTokenT<vector<float> >     elEta_t;
  edm::EDGetTokenT<vector<float> >     elPhi_t;
  edm::EDGetTokenT<vector<float> >     elE_t;
  edm::EDGetTokenT<vector<float> >     muPt_t;
  edm::EDGetTokenT<vector<float> >     muEta_t;
  edm::EDGetTokenT<vector<float> >     muPhi_t;
  edm::EDGetTokenT<vector<float> >     muE_t;
  edm::EDGetTokenT<vector<vlq::Jet> >  ak4_t;
  edm::EDGetTokenT<vector<vlq::Jet> >  bjets_t;
  edm::EDGetTokenT<vector<vlq::Jet> >  zjets_t;
  edm::EDGetTokenT<vector<vlq::Jet> >  hjets_t;
  edm::EDGetTokenT<vector<vlq::Candidate> > zllcands_t;
  edm::EDGetTokenT<double>             evtwt_t;

  const double ptMin_;
  const string zdecaymode_;
  const string signalType_;

  edm::Service<TFileService> fs;
  map<string, TH1D*> h1_;

};

MassReco::MassReco(const edm::ParameterSet& iConfig) :
  elPt_t     (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("elPt"))),
  elEta_t    (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("elEta"))),
  elPhi_t    (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("elPhi"))),
  elE_t      (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("elE"))),
  muPt_t     (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("muPt"))),
  muEta_t    (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("muEta"))),
  muPhi_t    (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("muPhi"))),
  muE_t      (consumes<vector<float> > (iConfig.getParameter<edm::InputTag>("muE"))),
  ak4_t      (consumes<vector<vlq::Jet> > (iConfig.getParameter<edm::InputTag>("jets"))),
  bjets_t    (consumes<vector<vlq::Jet> > (iConfig.getParameter<edm::InputTag>("bjets"))),
  zjets_t    (consumes<vector<vlq::Jet> > (iConfig.getParameter<edm::InputTag>("zjets"))),
  hjets_t    (consumes<vector<vlq::Jet> > (iConfig.getParameter<edm::InputTag>("hjets"))),
  zllcands_t (consumes<vector<vlq::Candidate> > (iConfig.getParameter<edm::InputTag>("zllcands"))),
  evtwt_t    (consumes<double>           (iConfig.getParameter<edm::InputTag>("evtwt"))),
  ptMin_     (iConfig.getParameter<double> ("ptMin")),
  zdecaymode_       (iConfig.getParameter<string> ("zdecaymode")),
  signalType_ (iConfig.getParameter<string> ("signalType"))
{}

MassReco::~MassReco() {}

bool MassReco::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  edm::Handle<vector<float> >     elPt_h    ; evt.getByToken(elPt_t, elPt_h)    ;
  edm::Handle<vector<float> >     elEta_h   ; evt.getByToken(elEta_t, elEta_h)   ;
  edm::Handle<vector<float> >     elPhi_h   ; evt.getByToken(elPhi_t, elPhi_h)   ;
  edm::Handle<vector<float> >     elE_h     ; evt.getByToken(elE_t, elE_h)     ;
  edm::Handle<vector<float> >     muPt_h    ; evt.getByToken(muPt_t, muPt_h)    ;
  edm::Handle<vector<float> >     muEta_h   ; evt.getByToken(muEta_t, muEta_h)   ;
  edm::Handle<vector<float> >     muPhi_h   ; evt.getByToken(muPhi_t, muPhi_h)   ;
  edm::Handle<vector<float> >     muE_h     ; evt.getByToken(muE_t, muE_h)     ;
  edm::Handle<vector<vlq::Jet> > ak4_h      ; evt.getByToken(ak4_t,  ak4_h)     ;
  edm::Handle<vector<vlq::Jet> > bjets_h    ; evt.getByToken(bjets_t,  bjets_h) ;
  edm::Handle<vector<vlq::Jet> > zjets_h    ; evt.getByToken(zjets_t,  zjets_h) ;
  edm::Handle<vector<vlq::Jet> > hjets_h    ; evt.getByToken(hjets_t,  hjets_h) ;
  edm::Handle<vector<vlq::Candidate> > zllcands_h; evt.getByToken(zllcands_t, zllcands_h) ;
  edm::Handle<double>              evtwt_h  ; evt.getByToken(evtwt_t,  evtwt_h) ;

  double evtwt = *evtwt_h.product();

  TLorentzVector zllcand = (*zllcands_h.product()).at(0).getP4();
  //cout << zllcands.size() << endl;

  // vector<TLorentzVector> lepP4;
  // if (zdecaymode_ == "zelel"){
  //   for (unsigned i=0; i<elPt_h->size(); i++){
  //     TLorentzVector el;
  //     el.SetPtEtaPhiE((*elPt_h.product()).at(i), (*elEta_h.product()).at(i), (*elPhi_h.product()).at(i), (*elE_h.product()).at(i));
  //     lepP4.push_back(el);
  //   }
  // }
  // else if (zdecaymode_ == "zmumu"){
  //   for (unsigned i=0; i<muPt_h->size(); i++){
  //     TLorentzVector mu;
  //     mu.SetPtEtaPhiE((*muPt_h.product()).at(i), (*muEta_h.product()).at(i), (*muPhi_h.product()).at(i), (*muE_h.product()).at(i));
  //     lepP4.push_back(mu);
  //   }
  // }
      
  vector<vlq::Jet> ak4s = *ak4_h.product();
  vector<vlq::Jet> bjets = *bjets_h.product();
  vector<vlq::Jet> zjets = *zjets_h.product();
  vector<vlq::Jet> hjets = *hjets_h.product();

  //TLorentzVector leptons = (lepP4.at(0) + lepP4.at(1));
  //  cout << lepP4.at(0).E() << " " << lepP4.at(1).E() << endl;

  pair<double, double> resReco_bZ, boostReco_bZ, mergeReco_bZ;
  pair<double, double> resReco_bH, boostReco_bH, mergeReco_bH;
  
  resReco_bZ.first = 9999;
  resReco_bZ.second = -1;
  resReco_bH.first = 9999;
  resReco_bH.second = -1;
  boostReco_bZ.first = 9999;
  boostReco_bZ.second = -1;
  boostReco_bH.first = 9999;
  boostReco_bH.second = -1;
  mergeReco_bZ.first = 9999;
  mergeReco_bZ.second = -1;
  mergeReco_bH.first = 9999;
  mergeReco_bH.second = -1;

  bool doZ = (signalType_ == "EvtType_MC_bZbZ" || signalType_ == "");
  bool doH = (signalType_ == "EvtType_MC_bZbH" || signalType_ == "");

  if (zjets.size() > 0 && doZ)
    boostReco_bZ = doBoostedReco(ak4s, zjets.at(0).getP4(), 91.2, zllcand, 150.);
   if (hjets.size() > 0 && doH)
     boostReco_bH = doBoostedReco(ak4s, hjets.at(0).getP4(), 125., zllcand, 150.);

  if (ak4s.size() > 3){
    if (zjets.size() == 0 && doZ)
      resReco_bZ = doResolvedReco(ak4s, 91.2, zllcand);
    if (hjets.size() == 0 && doH)
    resReco_bH = doResolvedReco(ak4s, 125., zllcand);
  }
  
  for (unsigned i=0; i<ak4s.size(); i++){
    if (ak4s.at(i).getP4().M() > 65 && ak4s.at(i).getP4().M() < 105 && ak4s.at(i).getP4().Pt() > 200 && doZ && ak4s.size() < 4 && zjets.size() == 0)
      mergeReco_bZ = doBoostedReco(ak4s, ak4s.at(i).getP4(), 91.2, zllcand, 150.);
    if (ak4s.at(i).getP4().M() > 105 && ak4s.at(i).getP4().M() < 135 && ak4s.at(i).getP4().Pt() > 200 && doH && ak4s.size() < 4 && hjets.size() == 0)
    mergeReco_bH = doBoostedReco(ak4s, ak4s.at(i).getP4(), 125., zllcand, 150.);
  }

  if (resReco_bZ.second > 0) h1_["resReco_bZ"]->Fill(resReco_bZ.second, evtwt);
  if (resReco_bH.second > 0) h1_["resReco_bH"]->Fill(resReco_bH.second, evtwt);
  if (boostReco_bZ.second > 0) h1_["boostReco_bZ"]->Fill(boostReco_bZ.second, evtwt);
  if (boostReco_bH.second > 0) h1_["boostReco_bH"]->Fill(boostReco_bH.second, evtwt);
  if (mergeReco_bZ.second > 0) h1_["mergeReco_bZ"]->Fill(mergeReco_bZ.second, evtwt);
  if (mergeReco_bH.second > 0) h1_["mergeReco_bH"]->Fill(mergeReco_bH.second, evtwt);

  if (resReco_bZ.first < boostReco_bZ.first && resReco_bZ.first < mergeReco_bZ.first)
    h1_["comboReco_bZ"]->Fill(resReco_bZ.second, evtwt);
  else if (boostReco_bZ.first < resReco_bZ.first && boostReco_bZ.first < mergeReco_bZ.first)
    h1_["comboReco_bZ"]->Fill(boostReco_bZ.second, evtwt);
  else if (mergeReco_bZ.first < resReco_bZ.first && mergeReco_bZ.first < boostReco_bZ.first)
    h1_["comboReco_bZ"]->Fill(mergeReco_bZ.second, evtwt);

  if (resReco_bH.first < boostReco_bH.first && resReco_bH.first < mergeReco_bH.first)
    h1_["comboReco_bH"]->Fill(resReco_bH.second, evtwt);
  else if (boostReco_bH.first < resReco_bH.first && boostReco_bH.first < mergeReco_bH.first)
    h1_["comboReco_bH"]->Fill(boostReco_bH.second, evtwt);
  else if (mergeReco_bH.first < resReco_bH.first && mergeReco_bH.first < boostReco_bH.first)
    h1_["comboReco_bH"]->Fill(mergeReco_bH.second, evtwt);

  if (zjets.size() > 0)
    h1_["hey"]->Fill(zjets.at(0).getP4().M(), evtwt);


  return true;
}

void MassReco::beginJob(){
  h1_["resReco_bZ"] = fs->make<TH1D>("resReco_bZ", "Resolved Reconstruction B->bZ", 1000, 0., 3000);
  h1_["resReco_bH"] = fs->make<TH1D>("resReco_bH", "Resolved Reconstruction B->bH", 1000, 0., 3000);
  h1_["boostReco_bZ"] = fs->make<TH1D>("boostReco_bZ", "Boosted Reconstruction B->bZ", 1000, 0., 3000);
  h1_["boostReco_bH"] = fs->make<TH1D>("boostReco_bH", "Boosted Reconstruction B->bH", 1000, 0., 3000);
  h1_["mergeReco_bZ"] = fs->make<TH1D>("mergeReco_bZ", "Merged Reconstruction B->bZ", 1000, 0., 3000);
  h1_["mergeReco_bH"] = fs->make<TH1D>("mergeReco_bH", "Merged Reconstruction B->bH", 1000, 0., 3000);
  h1_["comboReco_bZ"] = fs->make<TH1D>("comboReco_bZ", "Combo Reconstruction B->bZ", 1000, 0., 3000);
  h1_["comboReco_bH"] = fs->make<TH1D>("comboReco_bH", "Combo Reconstruction B->bH", 1000, 0., 3000);
  h1_["hey"] = fs->make<TH1D>("hey", "hey", 20, 0., 110.);

  
}

void MassReco::endJob(){
  return;
}

pair<double, double> MassReco::vector_eval(vector<pair<double, double> > vec){
  double min_value = 9999.;
  double mass = -1;
  for( unsigned ind = 0; ind < vec.size(); ++ind) {
    if (vec[ind].first < min_value){
      min_value = vec[ind].first;
      mass = vec[ind].second;
    }
  }
  return std::make_pair(min_value, mass);
}

double MassReco::resolvedChi2(vector<TLorentzVector> jets, TLorentzVector Leptons, double bosMass, double mass){

  double Zup = abs((jets[2] + jets[3]).M() - bosMass);
  double Zup2 = Zup * Zup;
  double term1 = Zup2 / (12.2676 * 12.2676);

  double BHup = abs((jets[1] + jets[2] + jets[3]).M() - mass);
  double BHup2 = BHup * BHup;
  double term2 = BHup2 / (78.6888 * 78.6888);

  double BLup = abs((jets[0] + Leptons).M() - mass);
  double BLup2 = BLup * BLup;
  double term3 = BLup2 / (59.0947 * 59.0947);

  double result = term1 + term2 + term3;
  //  cout << term1 << " " << term2 << " " << term3 << endl;
  return(result);
}

double MassReco::boostedChi2(vector<TLorentzVector> ak4Jets, TLorentzVector ak8Jet, TLorentzVector Leptons, double bosMass, double mass, double pT){
  if (ak8Jet.Pt() > pT && ak8Jet.M() != ak4Jets.at(0).M() && ak8Jet.M() != ak4Jets.at(1).M() && ak4Jets.at(0).DeltaR(ak8Jet) > 1.){
    double Zup = abs(ak8Jet.M() - bosMass);
    double Zup2 = Zup * Zup;
    double term1 = Zup2 / (12 * 12);
    
    double BHup = abs((ak8Jet + ak4Jets[0]).M() - mass);
    double BHup2 = BHup * BHup;
    double term2 = BHup2 / (78 * 78);
    
    double BLup = abs((ak4Jets[1] + Leptons).M() - mass);
    double BLup2 = BLup * BLup;
    double term3 = BLup2 / (59 * 59);
    
    double result = term1 + term2 + term3;
    return(result);
  }
  else
    return(9999.);
}
pair<double, double> MassReco::doBoostedReco(vector<vlq::Jet> ak4Jets, TLorentzVector fatJet, double bosMass, TLorentzVector Leptons, double pT){
  pair<double, double> chi2_result;
  double loop = 100000;
  vector<pair<double, double> > chi2s;
  pair<double, double> chi2_fill;
  chi2_fill.first = 10000;
  chi2_fill.second = 10000;
  TLorentzVector ak4[3];
  int index_array[] = {0, 1, 2};
  for (int mass=0; mass<=3000; mass+=5){
    double loop_check = 100000;
    int n = 0;
    do{
      int i0 = index_array[0];
      int i1 = index_array[1];
      int i2 = index_array[2];
      vector<TLorentzVector> passToChi2;
      if (!passToChi2.empty())
        passToChi2.clear();
      if (ak4Jets.size() > 2){
        ak4[0] = ak4Jets.at(i0).getP4();
        ak4[1] = ak4Jets.at(i1).getP4();
        ak4[2] = ak4Jets.at(i2).getP4();
	passToChi2.push_back(ak4[0]);
	passToChi2.push_back(ak4[1]);
	passToChi2.push_back(ak4[2]);
	n = 3;
      }
      else if (ak4Jets.size() == 2){
	ak4[0] = ak4Jets.at(i0).getP4();
	ak4[1] = ak4Jets.at(i1).getP4();
	passToChi2.push_back(ak4[0]);
	passToChi2.push_back(ak4[1]);
	n = 2;
      }
      else
        continue;

      loop = boostedChi2(passToChi2, fatJet, Leptons, bosMass,  mass, pT);

      if (loop < loop_check){
        loop_check = loop;
        chi2_result.first = loop_check;
        chi2_result.second = mass;
      }
    }
    while(std::next_permutation(index_array, index_array + n));

    chi2s.push_back(chi2_result);
  }

  chi2_fill = vector_eval(chi2s);
  return(chi2_fill);
}

pair<double, double> MassReco::doResolvedReco(vector<vlq::Jet> collection, double bosMass, TLorentzVector Leptons){
  int next = 0;
  for(int i=0; i<4; i++){
    if (collection.at(i).getPt() > 0)
      ++next;
  }

  pair<double, double> chi2_result;
  double loop = 100000;
  vector<pair<double,double> > chi2s;

  pair<double, double> chi2_fill;
  chi2_fill.first = 10000;
  chi2_fill.second = 10000;

  TLorentzVector Jets[5];

  int index_array[] = {0, 1, 2, 3, 4};

  for (int mass = 0; mass <= 2000; mass+=5){

    double loop_check = 10000;
    int n = 0;

    do{
      int i0 = index_array[0];
      int i1 = index_array[1];
      int i2 = index_array[2];
      int i3 = index_array[3];
      int i4 = index_array[4];
      vector<TLorentzVector> passToChi2;
      if (!passToChi2.empty())
        passToChi2.clear();
      if (collection.size() > 4){

        Jets[0] = collection.at(i0).getP4();
        Jets[1] = collection.at(i1).getP4();
        Jets[2] = collection.at(i2).getP4();
        Jets[3] = collection.at(i3).getP4();
        Jets[4] = collection.at(i4).getP4();

	passToChi2.push_back(Jets[0]);
	passToChi2.push_back(Jets[1]);
	passToChi2.push_back(Jets[2]);
	passToChi2.push_back(Jets[3]);
	passToChi2.push_back(Jets[4]);
	n = 5;

      }
      else if (collection.size() == 4){

        Jets[0] = collection.at(i0).getP4();
        Jets[1] = collection.at(i1).getP4();
        Jets[2] = collection.at(i2).getP4();
        Jets[3] = collection.at(i3).getP4();

	passToChi2.push_back(Jets[0]);
	passToChi2.push_back(Jets[1]);
	passToChi2.push_back(Jets[2]);
	passToChi2.push_back(Jets[3]);

	n = 4;
      }
      else
        continue;

      loop = resolvedChi2(passToChi2, Leptons, bosMass,  mass);

      if (loop < loop_check){
        loop_check = loop;
        chi2_result.first = loop_check;
        chi2_result.second = mass;
      }
    }
    while(std::next_permutation(index_array, index_array + n));

    chi2s.push_back(chi2_result);
  }

  chi2_fill = vector_eval(chi2s);
return(chi2_fill);
}


DEFINE_FWK_MODULE(MassReco);


  
 
