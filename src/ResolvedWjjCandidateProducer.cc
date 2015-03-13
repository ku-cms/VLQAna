// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      ResolvedWjjCandidateProducer
// 
/**\class ResolvedWjjCandidateProducer ResolvedWjjCandidateProducer.cc Analysis/VLQAna/plugins/ResolvedWjjCandidateProducer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Devdatta Majumder
//         Created:  Fri, 27 Feb 2015 16:09:10 GMT
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "AnalysisDataFormats/BoostedObjects/interface/Jet.h"
#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"

#include <TLorentzVector.h>

//
// class declaration
//

class ResolvedWjjCandidateProducer : public edm::EDProducer {
  public:
    explicit ResolvedWjjCandidateProducer(const edm::ParameterSet&);
    ~ResolvedWjjCandidateProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    // ----------member data ---------------------------
    //
    struct wjj {
      int widx ;
      int j1idx ;
      int j2idx ; 
    };

    edm::InputTag l_genPartPt                 ; 
    edm::InputTag l_genPartEta                ; 
    edm::InputTag l_genPartPhi                ; 
    edm::InputTag l_genPartE                  ; 
    edm::InputTag l_genPartMass               ; 
    edm::InputTag l_genPartID                 ; 
    edm::InputTag l_genPartStatus             ; 
    edm::InputTag l_genPartMomID              ; 

    edm::InputTag l_jetAK4Pt                  ; 
    edm::InputTag l_jetAK4Eta                 ; 
    edm::InputTag l_jetAK4Phi                 ; 
    edm::InputTag l_jetAK4Mass                ; 
    edm::InputTag l_jetAK4Flavour             ; 
    edm::InputTag l_jetAK4CSV                 ; 
    edm::InputTag l_ak4goodjets               ;
    bool   isMC_                              ;
    bool   isSignal_                          ;  
    double wmassmin_                          ;
    double wmassmax_                          ;
    double scaledmassdropmin_                 ;
    double scaledmassdropmax_                 ;

};

using namespace std; 

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
ResolvedWjjCandidateProducer::ResolvedWjjCandidateProducer(const edm::ParameterSet& iConfig) :
  l_genPartPt             (iConfig.getParameter<edm::InputTag> ("genPartPt")),
  l_genPartEta            (iConfig.getParameter<edm::InputTag> ("genPartEta")),
  l_genPartPhi            (iConfig.getParameter<edm::InputTag> ("genPartPhi")),
  l_genPartE              (iConfig.getParameter<edm::InputTag> ("genPartE")),
  l_genPartMass           (iConfig.getParameter<edm::InputTag> ("genPartMass")),
  l_genPartID             (iConfig.getParameter<edm::InputTag> ("genPartID")),
  l_genPartStatus         (iConfig.getParameter<edm::InputTag> ("genPartStatus")),
  l_genPartMomID          (iConfig.getParameter<edm::InputTag> ("genPartMomID")),
  l_jetAK4Pt              (iConfig.getParameter<edm::InputTag> ("jetAK4PtLabel")),  
  l_jetAK4Eta             (iConfig.getParameter<edm::InputTag> ("jetAK4EtaLabel")),  
  l_jetAK4Phi             (iConfig.getParameter<edm::InputTag> ("jetAK4PhiLabel")),  
  l_jetAK4Mass            (iConfig.getParameter<edm::InputTag> ("jetAK4MassLabel")),  
  l_jetAK4Flavour         (iConfig.getParameter<edm::InputTag> ("jetAK4FlavourLabel")),  
  l_jetAK4CSV             (iConfig.getParameter<edm::InputTag> ("jetAK4CSVLabel")),  
  l_ak4goodjets           (iConfig.getParameter<edm::InputTag> ("ak4goodjets")),
  isMC_                   (iConfig.getParameter<bool>          ("isMC")),
  isSignal_               (iConfig.getParameter<bool>          ("isSignal")),
  wmassmin_               (iConfig.getParameter<double>        ("wmassmin")), 
  wmassmax_               (iConfig.getParameter<double>        ("wmassmax")), 
  scaledmassdropmin_      (iConfig.getParameter<double>        ("scaledmassdropmin")), 
  scaledmassdropmax_      (iConfig.getParameter<double>        ("scaledmassdropmax"))
{

  produces<vector<vlq::Jet>>("JetCollection") ; 
  produces<vector<vlq::ResolvedVjj>>("ResolvedWjjCollection") ; 

}


ResolvedWjjCandidateProducer::~ResolvedWjjCandidateProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ResolvedWjjCandidateProducer::produce(edm::Event& evt, const edm::EventSetup& iSetup)
{
  using namespace edm;

  typedef Handle <vector<float>> hfloat ; 
  typedef Handle <vector<unsigned>> hunsigned ; 

  hfloat h_genPartPt             ; evt.getByLabel (l_genPartPt     , h_genPartPt    ); 
  hfloat h_genPartEta            ; evt.getByLabel (l_genPartEta    , h_genPartEta   ); 
  hfloat h_genPartPhi            ; evt.getByLabel (l_genPartPhi    , h_genPartPhi   ); 
  hfloat h_genPartE              ; evt.getByLabel (l_genPartE      , h_genPartE     ); 
  hfloat h_genPartMass           ; evt.getByLabel (l_genPartMass   , h_genPartMass  ); 
  hfloat h_genPartID             ; evt.getByLabel (l_genPartID     , h_genPartID    ); 
  hfloat h_genPartStatus         ; evt.getByLabel (l_genPartStatus , h_genPartStatus); 
  hfloat h_genPartMomID          ; evt.getByLabel (l_genPartMomID  , h_genPartMomID ); 
  hfloat  h_jetAK4Pt             ; evt.getByLabel (l_jetAK4Pt      , h_jetAK4Pt     );
  hfloat  h_jetAK4Eta            ; evt.getByLabel (l_jetAK4Eta     , h_jetAK4Eta    );
  hfloat  h_jetAK4Phi            ; evt.getByLabel (l_jetAK4Phi     , h_jetAK4Phi    );
  hfloat  h_jetAK4Mass           ; evt.getByLabel (l_jetAK4Mass    , h_jetAK4Mass   );
  hfloat  h_jetAK4Flavour        ; evt.getByLabel (l_jetAK4Flavour , h_jetAK4Flavour);
  hfloat  h_jetAK4CSV            ; evt.getByLabel (l_jetAK4CSV     , h_jetAK4CSV    );
  hunsigned h_ak4goodjets        ; evt.getByLabel (l_ak4goodjets , h_ak4goodjets) ;

  vector<vlq::Jet> v_jetsfromw; ; 
  vector<vlq::ResolvedVjj> v_wjj ; 
  if ( isMC_ && isSignal_ ) { 
    vector<int> widx ;
    vector<int> qidx ;
    for ( unsigned igen = 0; igen < (h_genPartPt.product())->size(); ++igen ) {
      if ( abs(h_genPartID.product()->at(igen)) == 24  ) widx.push_back(igen) ; 
      if ( abs(h_genPartID.product()->at(igen)) < 6 && abs(h_genPartMomID.product()->at(igen)) == 24  ) qidx.push_back(igen) ; 
    }

    if ( widx.size()  == 0 || qidx.size() == 0 ) return ; 

    for (int& iw : widx ) {
      TLorentzVector p4w ;
      p4w.SetPtEtaPhiM( (h_genPartPt.product())->at(iw), 
          (h_genPartEta.product())->at(iw), 
          (h_genPartPhi.product())->at(iw), 
          (h_genPartMass.product())->at(iw)  ) ; 

      for ( int iq1 : qidx ) {
        TLorentzVector p4q1 ;
        p4q1.SetPtEtaPhiM( (h_genPartPt.product())->at(iq1), 
            (h_genPartEta.product())->at(iq1), 
            (h_genPartPhi.product())->at(iq1), 
            (h_genPartMass.product())->at(iq1)  ) ; 
        TLorentzVector p4j1 ; 
        for ( unsigned ij1 = 0; ij1 < h_ak4goodjets.product()->size(); ++ij1 ) {
          p4j1.SetPtEtaPhiM(h_jetAK4Pt.product()->at(ij1), 
              h_jetAK4Eta.product()->at(ij1), 
              h_jetAK4Phi.product()->at(ij1), 
              h_jetAK4Mass.product()->at(ij1)) ; 
          if ( p4j1.DeltaR(p4q1) < 0.4 ) {
            for (  int iq2 : qidx ) {
              if ( iq2 <= iq1 ) continue ; 
              TLorentzVector p4q2 ;
              p4q2.SetPtEtaPhiM( (h_genPartPt.product())->at(iq2), 
                  (h_genPartEta.product())->at(iq2), 
                  (h_genPartPhi.product())->at(iq2), 
                  (h_genPartMass.product())->at(iq2)  ) ; 
              TLorentzVector p4j2 ; 
              for ( unsigned ij2 = 0; ij2 < h_ak4goodjets.product()->size() && ij2 != ij1 ; ++ij2 ) {
                p4j2.SetPtEtaPhiM(h_jetAK4Pt.product()->at(ij2), 
                    h_jetAK4Eta.product()->at(ij2), 
                    h_jetAK4Phi.product()->at(ij2), 
                    h_jetAK4Mass.product()->at(ij2)) ; 
                if ( p4j2.DeltaR(p4q2) < 0.4 ) {
                  TLorentzVector p4w = p4j1 + p4j2 ; 
                  float drjj = p4j1.DeltaR(p4j2) ; 
                  float mass = p4w.Mag() ; 
                  float massdrop =  max(p4j1.Mag(), p4j2.Mag())/p4w.Mag() ; 
                  float scaledmassdrop = massdrop*drjj ;
                  std::pair <int, int> jetIndices(ij1, ij2) ; 
                  vlq::ResolvedVjj wjj ;
                  wjj.setP4( p4w ) ; 
                  wjj.setDrjj( drjj ) ; 
                  wjj.setMass( mass ) ; 
                  wjj.setMassDrop( massdrop ) ;
                  wjj.setScaledMassDrop( scaledmassdrop ) ;
                  wjj.setJetIndices( jetIndices ) ; 
                  v_wjj.push_back(wjj) ; 
                  vlq::Jet j1 ; 
                  vlq::Jet j2;
                  j1.setP4(p4j1) ;
                  j2.setP4(p4j2) ; 
                  j1.setIndex(ij1) ;
                  j2.setIndex(ij2) ;
                  v_jetsfromw.push_back(j1) ;
                  v_jetsfromw.push_back(j2) ;
                }
              }
            }
          }
        }
      }
    }
  }
  else if ( isMC_ && !isSignal_ ) {
    vector<unsigned>ak4idx = *h_ak4goodjets.product() ; 
    for ( unsigned ij = 0; ij < ak4idx.size(); ++ij ) {
      for ( unsigned jj = ij+1; jj < ak4idx.size(); ++jj) {
        TLorentzVector p4j1, p4j2 ; 
        p4j1.SetPtEtaPhiM(h_jetAK4Pt.product()->at(ij), h_jetAK4Eta.product()->at(ij), h_jetAK4Phi.product()->at(ij), h_jetAK4Mass.product()->at(ij)) ; 
        p4j2.SetPtEtaPhiM(h_jetAK4Pt.product()->at(jj), h_jetAK4Eta.product()->at(jj), h_jetAK4Phi.product()->at(jj), h_jetAK4Mass.product()->at(jj)) ; 

        //// Make W candidates 
        TLorentzVector p4w = p4j1 + p4j2 ; 
          float drjj = p4j1.DeltaR(p4j2) ; 
          float mass = p4w.Mag() ; 
          float massdrop =  max(p4j1.Mag(), p4j2.Mag())/p4w.Mag() ; 
          float scaledmassdrop = massdrop*drjj ;
          std::pair <int, int> jetIndices(ij, jj) ; 
          vlq::ResolvedVjj wjj ;
          wjj.setP4( p4w ) ; 
          wjj.setDrjj( drjj ) ; 
          wjj.setMass( mass ) ; 
          wjj.setMassDrop( massdrop ) ;
          wjj.setScaledMassDrop( scaledmassdrop ) ;
          wjj.setJetIndices( jetIndices ) ; 
          v_wjj.push_back(wjj) ; 
          vlq::Jet j1 ; 
          vlq::Jet j2;
          j1.setP4(p4j1) ;
          j2.setP4(p4j2) ; 
          j1.setIndex(ij) ;
          j2.setIndex(jj) ;
          v_jetsfromw.push_back(j1) ;
          v_jetsfromw.push_back(j2) ;
      }
    }
  }

  auto_ptr<vector<vlq::ResolvedVjj> > wjjcoll( new vector<vlq::ResolvedVjj> (v_wjj) );
  auto_ptr<vector<vlq::Jet> > jetcoll( new vector<vlq::Jet> (v_jetsfromw) );
  evt.put(jetcoll, "JetCollection") ; 
  evt.put(wjjcoll, "ResolvedWjjCollection") ; 

  return ; 

}

// ------------ method called once each job just before starting event loop  ------------
  void 
ResolvedWjjCandidateProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ResolvedWjjCandidateProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
   void
   ResolvedWjjCandidateProducer::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void
   ResolvedWjjCandidateProducer::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void
   ResolvedWjjCandidateProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void
   ResolvedWjjCandidateProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ResolvedWjjCandidateProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ResolvedWjjCandidateProducer);
