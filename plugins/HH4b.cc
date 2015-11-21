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
#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/HH4bTree.h"
#include <TH1D.h>
#include <TTree.h>

class HH4b : public edm::EDFilter {
  public:
    explicit HH4b(const edm::ParameterSet&) ;
    ~HH4b() ; 
  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    // ----------member data ---------------------------
    edm::InputTag l_evtwtGen                     ;
    edm::InputTag l_evtwtPV                      ;
    edm::InputTag l_npv                          ;
    JetMaker     jetAK8maker                     ; 
    JetMaker     jetHTaggedmaker                 ; 
    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    EventInfoBranches selectedevt; 
    JetInfoBranches ak8jets ; 
    JetInfoBranches hjets ; 
    TTree* tree_ ; 
};

using namespace std; 

template <typename T>
struct iterator_extractor { typedef typename T::iterator type; };

template <typename T>
struct iterator_extractor<T const> { typedef typename T::const_iterator type; };


template <typename T>
class Indexer {
  public:
    class iterator {
      typedef typename iterator_extractor<T>::type inner_iterator;

      typedef typename std::iterator_traits<inner_iterator>::reference inner_reference;
      public:
      typedef std::pair<size_t, inner_reference> reference;

      iterator(inner_iterator it): _pos(0), _it(it) {}

      reference operator*() const { return reference(_pos, *_it); }

      iterator& operator++() { ++_pos; ++_it; return *this; }
      iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }

      bool operator==(iterator const& it) const { return _it == it._it; }
      bool operator!=(iterator const& it) const { return !(*this == it); }

      private:
      size_t _pos;
      inner_iterator _it;
    };

    Indexer(T& t): _container(t) {}

    iterator begin() const { return iterator(_container.begin()); }
    iterator end() const { return iterator(_container.end()); }

  private:
    T& _container;
}; // class Indexer

template <typename T>
Indexer<T> index(T& t) { return Indexer<T>(t); }

HH4b::HH4b(const edm::ParameterSet& iConfig) :
  l_evtwtGen              (iConfig.getParameter<edm::InputTag>     ("evtwtGen")),
  l_evtwtPV               (iConfig.getParameter<edm::InputTag>     ("evtwtPV")),
  l_npv                   (iConfig.getParameter<edm::InputTag>     ("npv")),
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  jetHTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetHTaggedselParams"))   
{
}

HH4b::~HH4b() {}

bool HH4b::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  Handle<double>h_evtwtGen ; evt.getByLabel(l_evtwtGen, h_evtwtGen) ; 
  Handle<double>h_evtwtPV  ; evt.getByLabel(l_evtwtPV,  h_evtwtPV ) ; 
  Handle<unsigned>h_npv    ; evt.getByLabel(l_npv, h_npv) ; 

  double evtwt((*h_evtwtGen.product()) * (*h_evtwtPV.product())) ; 

  h1_["cutflow"] -> Fill(1, evtwt) ; 
  h1_["npv"] -> Fill(*h_npv.product(), evtwt); 

  vlq::JetCollection  goodAK8Jets , goodHTaggedJets ; 

  jetAK8maker(evt, goodAK8Jets); 
  if (goodAK8Jets.size() < 2) return false;
  
  ak8jets.njets = goodAK8Jets.size() ; 
  for (auto ijet : index(goodAK8Jets) ) {
    ak8jets.Index[ijet.first] = (ijet.second).getIndex() ;
    ak8jets.ParentIndex[ijet.first] = -1 ;
    ak8jets.Pt[ijet.first] = (ijet.second).getPt() ;
    ak8jets.Eta[ijet.first] = (ijet.second).getEta() ;
    ak8jets.Phi[ijet.first] = (ijet.second).getPhi() ;
    ak8jets.Mass[ijet.first] = (ijet.second).getMass() ;
    ak8jets.MassPruned[ijet.first] = (ijet.second).getPrunedMass() ;
    ak8jets.MassSoftDrop[ijet.first] = (ijet.second).getPrunedMass() ;
    ak8jets.tau1[ijet.first] = (ijet.second).getTau1() ;
    ak8jets.tau2[ijet.first] = (ijet.second).getTau2() ;
    ak8jets.tau3[ijet.first] = (ijet.second).getTau3() ;
    ak8jets.CSVIVFv2[ijet.first] = (ijet.second).getCSV() ;
    ak8jets.nhf[ijet.first] = (ijet.second).getNHF() ;
    ak8jets.chf[ijet.first] = (ijet.second).getCHF() ;
    ak8jets.emf[ijet.first] = (ijet.second).getEMF() ;
    ak8jets.phf[ijet.first] = (ijet.second).getPHF() ;
    ak8jets.muf[ijet.first] = (ijet.second).getMUF() ;
    ak8jets.nconsts[ijet.first] = (ijet.second).getNConsts() ;
    ak8jets.nsubjets[ijet.first] = (ijet.second).getNSubjets() ;
    ak8jets.csvSubjet0[ijet.first] = (ijet.second).getCSVSubjet0() ;
    ak8jets.csvSubjet1[ijet.first] = (ijet.second).getCSVSubjet1() ;
    ak8jets.groomedMassCorr[ijet.first] = (ijet.second).getGroomedMassCorr() ;
    ak8jets.nsubjetsBTaggedCSVL[ijet.first] = (ijet.second).getNSubjetsBTaggedCSVL() ;
  }

  jetHTaggedmaker(evt, goodHTaggedJets);
  if (goodHTaggedJets.size() < 2) return false;

  double cosThetaStar = abs(goodAK8Jets.at(0).getEta() -  goodAK8Jets.at(1).getEta()) ; 
  if (cosThetaStar > 1.3) return false ; 

  TLorentzVector p4_hjet0 = goodHTaggedJets.at(0).getP4() ; 
  TLorentzVector p4_hjet1 = goodHTaggedJets.at(1).getP4() ; 
  TLorentzVector p4_leading2hjets = p4_hjet0+p4_hjet1 ;

  selectedevt.deta_leading2hjets_ = cosThetaStar ; 
  selectedevt.minv_leading2hjets_ = p4_leading2hjets.Mag();
  selectedevt.minv_leading2hjets_subtractedd_ = p4_leading2hjets.Mag() - (goodHTaggedJets.at(0).getMass() - 125.) - (goodHTaggedJets.at(1).getMass() -125.);
  selectedevt.pt_leading2hjets_ = p4_leading2hjets.Pt();
  selectedevt.eta_leading2hjets_ = p4_leading2hjets.Eta();
  selectedevt.y_leading2hjets_ = p4_leading2hjets.Rapidity();
  selectedevt.phi_leading2hjets_ = p4_leading2hjets.Phi();

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
    hjets.CSVIVFv2[ijet.first] = (ijet.second).getCSV() ;
    hjets.nhf[ijet.first] = (ijet.second).getNHF() ;
    hjets.chf[ijet.first] = (ijet.second).getCHF() ;
    hjets.emf[ijet.first] = (ijet.second).getEMF() ;
    hjets.phf[ijet.first] = (ijet.second).getPHF() ;
    hjets.muf[ijet.first] = (ijet.second).getMUF() ;
    hjets.nconsts[ijet.first] = (ijet.second).getNConsts() ;
    hjets.nsubjets[ijet.first] = (ijet.second).getNSubjets() ;
    hjets.csvSubjet0[ijet.first] = (ijet.second).getCSVSubjet0() ;
    hjets.csvSubjet1[ijet.first] = (ijet.second).getCSVSubjet1() ;
    hjets.groomedMassCorr[ijet.first] = (ijet.second).getGroomedMassCorr() ;
    hjets.nsubjetsBTaggedCSVL[ijet.first] = (ijet.second).getNSubjetsBTaggedCSVL() ;
  }

  tree_->Fill();

  return true ; 
}

// ------------ method called once each job just before starting event loop  ------------
void HH4b::beginJob() {

  h1_["cutflow"] = fs->make<TH1D>("cutflow", "cut flow", 12, 0.5, 12.5) ;  
  h1_["npv"] = fs->make<TH1D>("npv", ";N(PV);;", 51, -0.5, 50.5) ; 
  tree_ = fs->make<TTree>("tree", "HH4b") ; 
  selectedevt.RegisterTree(tree_,"SelectedEvent") ; 
  //ak8jets.RegisterTree(tree_,"AK8Jets") ; 
  hjets.RegisterTree(tree_,"HJets") ; 

}

void HH4b::endJob() {

  return ; 
}

DEFINE_FWK_MODULE(HH4b);
