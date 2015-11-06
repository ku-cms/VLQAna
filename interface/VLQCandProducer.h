#ifndef ANALYSIS_VLQANA_VLQCANDPRODUCER_HH
#define ANALYSIS_VLQANA_VLQCANDPRODUCER_HH
#include <boost/algorithm/string.hpp>
#include <string>
#include <map>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"

#include <TH1D.h>
#include <TLorentzVector.h>

using namespace std;
using namespace edm ; 

class VLQCandProducer : public edm::EDFilter {
  public:
    explicit VLQCandProducer (edm::ParameterSet const&)  ; 
    ~VLQCandProducer () ; 
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
  private:
    edm::InputTag l_tjets ; 
    edm::InputTag l_wjets ; 
    edm::InputTag l_bjets ; 
    edm::InputTag l_jets  ; 
    edm::InputTag l_zll   ; 

    double mass_t_ ; 
    double mass_w_ ;
    double mass_z_ ;
    double sigma_t_ ; 
    double sigma_w_ ;
    double sigma_z_ ;
    double sigma_hadvlq_ ;
    double sigma_lepvlq_ ; 

    vlq::CandidateCollection vquarks_ ; 

    edm::Service<TFileService> fs                ; 
    std::map<std::string, TH1D*> h1_             ; 
    
};
#endif 
