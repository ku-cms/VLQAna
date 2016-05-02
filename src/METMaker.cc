#include <iostream>
#include "Analysis/VLQAna/interface/METMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std ;
using namespace edm ;

METMaker::METMaker(edm::ParameterSet const& pars, edm::ConsumesCollector && iC) :
  l_metFullPhi        (pars.getParameter<edm::InputTag>("metFullPhiLabel")),
  l_metFullPt         (pars.getParameter<edm::InputTag>("metFullPtLabel")),
  l_metFullPx         (pars.getParameter<edm::InputTag>("metFullPxLabel")),
  l_metFullPy         (pars.getParameter<edm::InputTag>("metFulluncorPhiLabel")),
  l_metFulluncorPhi       (pars.getParameter<edm::InputTag>("metFulluncorPhiLabel")),
  l_metFulluncorPt      (pars.getParameter<edm::InputTag>("metFulluncorPtLabel")),
  l_metFulluncorSumEt     (pars.getParameter<edm::InputTag>("metFulluncorSumEtLabel")),
  METPtMin_ (pars.getParameter<double>("METPtMin")),
  METPtMax_ (pars.getParameter<double>("METPtMax"))
{
  iC.consumes<std::vector<float>>(l_metFullPhi);
  iC.consumes<std::vector<float>>(l_metFullPt);
  iC.consumes<std::vector<float>>(l_metFullPx);
  iC.consumes<std::vector<float>>(l_metFullPy);
  iC.consumes<std::vector<float>>(l_metFulluncorPhi);
  iC.consumes<std::vector<float>>(l_metFulluncorPt);
  iC.consumes<std::vector<float>>(l_metFulluncorSumEt);
}

METMaker::~METMaker () {}

void METMaker::operator () (edm::Event& evt, vlq::MetCollection& MET){
  Handle<vector<float>> h_metFullPhi      ; evt.getByLabel(l_metFullPhi       , h_metFullPhi)     ;
  Handle<vector<float>> h_metFullPt       ; evt.getByLabel(l_metFullPt      , h_metFullPt)      ;
  Handle<vector<float>> h_metFullPx       ; evt.getByLabel(l_metFullPx      , h_metFullPx)      ;
  Handle<vector<float>> h_metFullPy       ; evt.getByLabel(l_metFullPy      , h_metFullPy)      ;
  Handle<vector<float>> h_metFulluncorPhi   ; evt.getByLabel(l_metFulluncorPhi    , h_metFulluncorPhi)  ;
  Handle<vector<float>> h_metFulluncorPt    ; evt.getByLabel(l_metFulluncorPt     , h_metFulluncorPt)   ;
  Handle<vector<float>> h_metFulluncorSumEt   ; evt.getByLabel(l_metFulluncorSumEt  , h_metFulluncorSumEt)  ;

  double metFullPt = (h_metFullPt.product())->at(0);
  TLorentzVector  metP4;
  metP4.SetPtEtaPhiM(h_metFullPt.product()->at(0), 0, h_metFullPhi.product()->at(0), 0); 
  if (metFullPt > METPtMin_ && metFullPt < METPtMax_){
    vlq::Met met;
    met.setFullPhi      (h_metFullPhi       .product()->at(0));
    met.setFullPt      (h_metFullPt      .product()->at(0));
    met.setFullPx       (h_metFullPx      .product()->at(0));
    met.setFullPy      (h_metFullPy      .product()->at(0));
    met.setFulluncorPhi       (h_metFulluncorPhi    .product()->at(0));
    met.setFulluncorPt     (h_metFulluncorPt     .product()->at(0));
    met.setFulluncorSumEt   (h_metFulluncorSumEt  .product()->at(0));
    met.setP4                (metP4);

    MET.push_back(met);       
  }
}
