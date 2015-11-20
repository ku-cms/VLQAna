#include <memory>
#include <TH1D.h>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "Analysis/VLQAna/interface/MuonMaker.h"
#include "Analysis/VLQAna/interface/DileptonCandsProducer.h"
#include "Analysis/VLQAna/interface/ElectronMaker.h"
#include "Analysis/VLQAna/interface/JetMaker.h"

class Skim : public edm::EDFilter {
  public:
    explicit Skim(const edm::ParameterSet&);
    ~Skim(); 
  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    const std::string                     l_genEvtInfoProd ; 
    edm::EDGetTokenT<GenEventInfoProduct> t_genEvtInfoProd ; 

    edm::ParameterSet ZCandParams_               ; 
    ElectronMaker electronmaker                  ; 
    MuonMaker muonmaker                          ; 
    JetMaker jetAK4maker                         ; 
    JetMaker jetAK8maker                         ; 
    const bool   isData_                         ; 
    const int    nzelel_                         ;
    const int    nzmumu_                         ;
    const int    nak4jets_                       ;
    const int    nak8jets_                       ;

    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
}; 

Skim::Skim(const edm::ParameterSet& iConfig) : 
  l_genEvtInfoProd        (iConfig.getParameter<std::string>       ("genEvtInfoProdName")),
  ZCandParams_            (iConfig.getParameter<edm::ParameterSet> ("ZCandParams")),
  electronmaker           (iConfig.getParameter<edm::ParameterSet> ("elselParams")), 
  muonmaker               (iConfig.getParameter<edm::ParameterSet> ("muselParams")),
  jetAK4maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK4selParams")), 
  jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams")), 
  isData_                 (iConfig.getParameter<bool>              ("isData")),
  nzelel_                 (iConfig.getParameter<int>               ("nzelel")), 
  nzmumu_                 (iConfig.getParameter<int>               ("nzmumu")), 
  nak4jets_               (iConfig.getParameter<int>               ("nak4jets")), 
  nak8jets_               (iConfig.getParameter<int>               ("nak8jets"))  
{
  t_genEvtInfoProd = consumes<GenEventInfoProduct>(l_genEvtInfoProd) ; 
}

Skim::~Skim() {}

bool Skim::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm ; 

  bool pass(false) ;

  double evtwt(1.0) ; 
  if ( !isData_ ) {
    Handle<GenEventInfoProduct> h_genEvtInfoProd; 
    evt.getByToken(t_genEvtInfoProd, h_genEvtInfoProd);
    evtwt = h_genEvtInfoProd->weight() ; 
    evtwt /= abs(evtwt) ; 
  }

  h1_["cutflow_nowt"] -> Fill(1) ; 
  h1_["cutflow_wt"] -> Fill(1, evtwt) ; 

  vlq::CandidateCollection zelel, zmumu; 
  DileptonCandsProducer zllcandsprod(ZCandParams_) ; 

  if (nzelel_ > 0) {
    vlq::ElectronCollection goodElectrons; 
    electronmaker(evt, goodElectrons) ; 
    zllcandsprod.operator()<vlq::ElectronCollection>(zelel, goodElectrons) ; 
  }

  if (nzmumu_ > 0) {
    vlq::MuonCollection goodMuons; 
    muonmaker(evt, goodMuons) ; 
    zllcandsprod.operator()<vlq::MuonCollection>(zmumu, goodMuons); 
  }

  vlq::JetCollection goodAK4Jets, goodAK8Jets; 

  if (nak4jets_ > 0) jetAK4maker(evt, goodAK4Jets) ;

  if (nak8jets_ > 0) jetAK8maker(evt, goodAK8Jets) ;

  if ( (nzelel_ <= 0 || zelel.size()>0) 
      && (nzmumu_ <= 0 || zmumu.size() > 0) 
      && (nak4jets_ <= 0  || goodAK4Jets.size() > 0) 
      && (nak8jets_ <= 0 || goodAK8Jets.size() > 0)  ) {
    h1_["cutflow_nowt"] -> Fill(2) ; 
    h1_["cutflow_wt"] -> Fill(2, evtwt) ; 
    pass = true ; 
  }

  return pass ; 

}

void Skim::beginJob() { 
  h1_["cutflow_wt"] = fs->make<TH1D>("cutflow_wt", "cut flow with event weights", 2, 0.5, 2.5) ;  
  h1_["cutflow_nowt"] = fs->make<TH1D>("cutflow_nowt", "cut flow", 2, 0.5, 2.5) ;  
  h1_["cutflow_wt"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow_wt"] -> GetXaxis() -> SetBinLabel(2, "Passed") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(1, "All") ; 
  h1_["cutflow_nowt"] -> GetXaxis() -> SetBinLabel(2, "Passed") ; 
  return ; 
} 

void Skim::endJob() { return ; }

DEFINE_FWK_MODULE(Skim);
