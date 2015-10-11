#include <memory>
#include <vector>
#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include <TFile.h>
#include <TH1D.h>

class EventCleaner : public edm::EDFilter {
  public:
    explicit EventCleaner(const edm::ParameterSet&) ;
    ~EventCleaner() ; 
  private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    double GetLumiWeightsPVBased (const std::string file, const std::string hist, const unsigned npv) ; 

    edm::InputTag l_trigName                               ; 
    edm::InputTag l_trigBit                                ; 
    edm::InputTag l_metFiltersName                         ; 
    edm::InputTag l_metFiltersBit                          ; 
    edm::InputTag l_hbheNoiseFilter                        ; 
    std::string   l_genEvtInfoProd                         ; 
    edm::InputTag l_vtxRho                                 ; 
    edm::InputTag l_vtxZ                                   ; 
    edm::InputTag l_vtxNdf                                 ; 
    std::vector<std::string> hltPaths_                     ; 
    std::vector<std::string> metFilters_                   ; 
    const bool isData_                                     ; 
    const bool doPUReweightingNPV_                         ;
    const std::string file_PVWt_                           ; 
    const std::string hist_PVWt_                           ; 
    edm::EDGetTokenT<GenEventInfoProduct> t_genEvtInfoProd ; 

};

EventCleaner::EventCleaner(const edm::ParameterSet& iConfig) :
  l_trigName              (iConfig.getParameter<edm::InputTag>            ("trigNameLabel")),
  l_trigBit               (iConfig.getParameter<edm::InputTag>            ("trigBitLabel")),
  l_metFiltersName        (iConfig.getParameter<edm::InputTag>            ("metFiltersNameLabel")),
  l_metFiltersBit         (iConfig.getParameter<edm::InputTag>            ("metFiltersBitLabel")),
  l_hbheNoiseFilter       (iConfig.getParameter<edm::InputTag>            ("hbheNoiseFilterLabel")),
  l_genEvtInfoProd        (iConfig.getParameter<std::string>              ("genEvtInfoProdName")),
  l_vtxRho                (iConfig.getParameter<edm::InputTag>            ("vtxRhoLabel")),  
  l_vtxZ                  (iConfig.getParameter<edm::InputTag>            ("vtxZLabel")),  
  l_vtxNdf                (iConfig.getParameter<edm::InputTag>            ("vtxNdfLabel")),  
  hltPaths_               (iConfig.getParameter<std::vector<std::string>> ("hltPaths")), 
  metFilters_             (iConfig.getParameter<std::vector<std::string>> ("metFilters")), 
  isData_                 (iConfig.getParameter<bool>                     ("isData")),
  doPUReweightingNPV_     (iConfig.getParameter<bool>                     ("DoPUReweightingNPV")),
  file_PVWt_              (iConfig.getParameter<std::string>              ("File_PVWt")),
  hist_PVWt_              (iConfig.getParameter<std::string>              ("Hist_PVWt"))
{
  t_genEvtInfoProd = consumes<GenEventInfoProduct>(l_genEvtInfoProd) ; 
  produces<std::string>("evttype"); 
  produces<double>("evtwtGen");
  produces<double>("evtwtPV");
  produces<unsigned>("npv");
}

EventCleaner::~EventCleaner() {}

bool EventCleaner::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;
  using namespace std;

  typedef Handle <vector<string>> hstring ; 
  typedef Handle <vector<float>> hfloat ; 
  typedef Handle <vector<int>> hint ; 

  hstring h_trigName              ; evt.getByLabel (l_trigName               , h_trigName             );
  hfloat  h_trigBit               ; evt.getByLabel (l_trigBit                , h_trigBit              ); 
  hstring h_metFiltersName        ; evt.getByLabel (l_metFiltersName         , h_metFiltersName       );
  hfloat  h_metFiltersBit         ; evt.getByLabel (l_metFiltersBit          , h_metFiltersBit        ); 
  hfloat  h_vtxRho                ; evt.getByLabel (l_vtxRho                 , h_vtxRho               );
  hfloat  h_vtxZ                  ; evt.getByLabel (l_vtxZ                   , h_vtxZ                 );
  hint    h_vtxNdf                ; evt.getByLabel (l_vtxNdf                 , h_vtxNdf               );
  Handle <bool> h_hbheNoiseFilter ; evt.getByLabel (l_hbheNoiseFilter        , h_hbheNoiseFilter      );

  unsigned int hltdecisions(0) ; 
  for ( const string& myhltpath : hltPaths_ ) {
    vector<string>::const_iterator it ;
    for (it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it ) {
      if ( it->find(myhltpath) < std::string::npos) {
        hltdecisions |= int((h_trigBit.product())->at( it - (h_trigName.product())->begin() )) << ( it - (h_trigName.product())->begin() ) ;  
      }
    }
  }
  if ( hltPaths_.size() > 0 && !hltdecisions) return false ; 

  bool hbheNoiseFilter(h_hbheNoiseFilter.product()) ; 
  if ( !hbheNoiseFilter ) return false ; 
  if ( isData_ ) {
    bool metfilterdecision(1) ; 
    for ( const string& metfilter : metFilters_ ) {
      vector<string>::const_iterator it ; 
      for (it = (h_metFiltersName.product())->begin(); it != (h_metFiltersName.product())->end(); ++it) {
        if ( it->find(metfilter) < std::string::npos) {
          metfilterdecision *= (h_metFiltersBit.product())->at( it - (h_metFiltersName.product())->begin() ) ; 
        }
      }
    }
    if ( !metfilterdecision ) return false ; 
  }

  unsigned npv(0) ; 
  for ( unsigned ipv = 0; ipv < (h_vtxRho.product())->size(); ++ipv) {
    double vtxRho = (h_vtxRho.product())->at(ipv) ; 
    double vtxZ = (h_vtxZ.product())->at(ipv) ; 
    double vtxNdf = (h_vtxNdf.product())->at(ipv) ; 
    if ( abs(vtxRho) < 2. && abs(vtxZ) <= 24. && vtxNdf > 4 ) ++npv ; 
  }
  if ( npv < 1 ) return false ; 

  double evtwtGen(1.0) ; 
  if ( !isData_ ) {
    Handle<GenEventInfoProduct> h_genEvtInfoProd; 
    evt.getByToken(t_genEvtInfoProd, h_genEvtInfoProd);
    evtwtGen = h_genEvtInfoProd->weight() ; 
    evtwtGen /= abs(evtwtGen) ; 
  }

  double evtwtPV(1.0) ;
  if ( !isData_ && doPUReweightingNPV_ ) evtwtPV *= GetLumiWeightsPVBased(file_PVWt_, hist_PVWt_, npv) ; 

  string evttype(isData_ ? "data_" : "mc_");

  auto_ptr<string>ptr_evttype(new string(evttype)); 
  auto_ptr<double>ptr_evtwtGen(new double(evtwtGen)); 
  auto_ptr<double>ptr_evtwtPV(new double(evtwtPV)); 
  auto_ptr<unsigned>ptr_npv(new unsigned(npv)); 

  evt.put(ptr_evttype, "evttype");
  evt.put(ptr_evtwtGen, "evtwtGen");
  evt.put(ptr_evtwtPV, "evtwtPV");
  evt.put(ptr_npv, "npv");

  return true ; 

}

void EventCleaner::beginJob() {
}

void EventCleaner::endJob() {
}

double EventCleaner::GetLumiWeightsPVBased (const std::string file, const std::string hist, const unsigned npv) { 
  double wtPU(1) ;
  TFile f(file.c_str()) ;
  TH1D* hwt = dynamic_cast<TH1D*>( f.Get( hist.c_str() ) ) ; 
  wtPU = npv > 0 && npv <= 60 ? hwt->GetBinContent(npv) : 1.; 
  delete hwt ; 
  f.Close() ; 
  return wtPU ;
}

DEFINE_FWK_MODULE(EventCleaner);
