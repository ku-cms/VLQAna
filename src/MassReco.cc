#include <iostream>
#include "Analysis/VLQAna/interface/MassReco.h"
using namespace std;

MassReco::MassReco() {}

MassReco::~MassReco() {}

TLorentzVector MassReco::getGen(GenParticleCollection genParts, int ID, int MomID){
  TLorentzVector genInfo;
  for (auto& gen : genParts){
    if (gen.getPdgID() == ID && gen.getMom0PdgID() == MomID)
      genInfo = gen.getP4();
  }
  return(genInfo);
}

TLorentzVector MassReco::getGen(GenParticleCollection genParts, int IDlow, int IDhigh, int MomID){
  TLorentzVector genInfo;
  for (auto& gen : genParts){
    if (gen.getPdgID() >= IDlow && gen.getPdgID() <= IDhigh && gen.getMom0PdgID() == MomID)
      genInfo = gen.getP4();
  }
  return(genInfo);
}

TLorentzVector MassReco::getMatchedJet(TLorentzVector genPart, vlq::JetCollection goodJets, double dR){
  TLorentzVector jetInfo;
  for (auto& jet : goodJets){
    if (genPart.DeltaR(jet.getP4()) < dR && genPart.Pt() > 0)
      jetInfo = jet.getP4();
  }
  return(jetInfo);
}

// overload function to find all masses
double MassReco::findInvMass(TLorentzVector gen1, TLorentzVector gen2){
  double genSum = -999;
  if (gen1 != gen2 && (gen1 + gen2).M() != 0 && gen1.Pt() > 0 && gen2.Pt() > 0)
    genSum = (gen1 + gen2).M();
  return(genSum);
}
double MassReco::findInvMass(TLorentzVector gen1, TLorentzVector gen2, TLorentzVector b){
  double genSum = -999;
  if (gen1 != gen2 && (gen1 + gen2).M() != 0 && b.Pt() > 0 && gen1.Pt() > 0 && gen2.Pt() > 0)
    genSum = (gen1 + gen2 + b).M();
  return(genSum);
}

pair<double, double> MassReco::doReco(vlq::JetCollection ak4Jets, TLorentzVector fatJet, double bosMass, TLorentzVector Leptons){
  pair<double, double> chi2_result;
  double loop = 100000;
  vector<pair<double, double> > chi2s;
  pair<double, double> chi2_fill;
  chi2_fill.first = 10000;
  chi2_fill.second = 10000;
  TLorentzVector ak4[5];
  int index_array[] = {0, 1, 2, 3, 4};
  for (int mass=0; mass<=2000; mass+=5){
    double loop_check = 100000;
    do{
      int i0 = index_array[0];
      int i1 = index_array[1];
      int i2 = index_array[2];
      int i3 = index_array[3];
      int i4 = index_array[4];
      vector<TLorentzVector> passToChi2;
      if (!passToChi2.empty())
        passToChi2.clear();
      if (ak4Jets.size() > 4){
        ak4[0] = ak4Jets.at(i0).getP4();
        ak4[1] = ak4Jets.at(i1).getP4();
        ak4[2] = ak4Jets.at(i2).getP4();
        ak4[3] = ak4Jets.at(i3).getP4();
        ak4[4] = ak4Jets.at(i4).getP4();
      }
      else
        continue;
      // Need to know recommended size for ak4
      passToChi2.push_back(ak4[0]);
      passToChi2.push_back(ak4[1]);
      passToChi2.push_back(ak4[2]);
      passToChi2.push_back(ak4[3]);
      loop = chi2(passToChi2, fatJet, Leptons, bosMass,  mass);

      if (loop < loop_check){
        loop_check = loop;
        chi2_result.first = loop_check;
        chi2_result.second = mass;
      }
    }
    while(std::next_permutation(index_array, index_array + 5));

    chi2s.push_back(chi2_result);
  }

  chi2_fill = vector_eval(chi2s);
  return(chi2_fill);
}


pair<double, double> MassReco::doReco(vlq::JetCollection collection, double bosMass, TLorentzVector Leptons){
  int next = 0;
  for(int i=0; i<5; i++){
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
      }
      else
        continue;

      passToChi2.push_back(Jets[0]);
      passToChi2.push_back(Jets[1]);
      passToChi2.push_back(Jets[2]);
      passToChi2.push_back(Jets[3]);

      loop = chi2(passToChi2, Leptons, bosMass,  mass);

      if (loop < loop_check){
        loop_check = loop;
        chi2_result.first = loop_check;
        chi2_result.second = mass;
      }
    }
    while(std::next_permutation(index_array, index_array + 5));

    chi2s.push_back(chi2_result);
  }

  chi2_fill = vector_eval(chi2s);
  return(chi2_fill);
}

double MassReco::chi2(vector<TLorentzVector> jets, TLorentzVector Leptons, double bosMass, double mass){

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

  return(result);
}

double MassReco::chi2(vector<TLorentzVector> ak4Jets, TLorentzVector ak8Jet, TLorentzVector Leptons, double bosMass, double mass){

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
