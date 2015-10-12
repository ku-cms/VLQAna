// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      GenVLQSel
// 
/**\class GenVLQSel GenVLQSel.cc Analysis/VLQAna/plugins/GenVLQSel.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sadia Khalil
//         Created:  Mon, 31 Aug 2015 17:57:17 GMT
//
//
///////////////////////////////////////////////////////////////////////
#include "Analysis/VLQAna/interface/GenVLQSel.h"
using namespace reco;
using namespace std;
using namespace edm;

void
GenVLQSel::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{     
   hfloat h_genPartCharge ; iEvent.getByLabel(l_genPartCharge , h_genPartCharge) ;
   hfloat h_genPartE      ; iEvent.getByLabel(l_genPartE      , h_genPartE     ) ;
   hfloat h_genPartEta    ; iEvent.getByLabel(l_genPartEta    , h_genPartEta   ) ;
   hfloat h_genPartID     ; iEvent.getByLabel(l_genPartID     , h_genPartID    ) ;
   hfloat h_genPartMass   ; iEvent.getByLabel(l_genPartMass   , h_genPartMass  ) ;
   hfloat h_genPartMomID  ; iEvent.getByLabel(l_genPartMomID  , h_genPartMomID ) ;
   hfloat h_genPartPhi    ; iEvent.getByLabel(l_genPartPhi    , h_genPartPhi   ) ;
   hfloat h_genPartPt     ; iEvent.getByLabel(l_genPartPt     , h_genPartPt    ) ;
   hfloat h_genPartStatus ; iEvent.getByLabel(l_genPartStatus , h_genPartStatus) ;
   
   if(!iEvent.isRealData()){
      //cout << "mom size" << momids_.size() << endl;
      bool TPrime(0), BPrime(0);
      vector<int>::const_iterator im ;
      for (im = momids_.begin(); im != momids_.end(); ++im ) {        
         if ( abs(*im) == 8000001) {TPrime = 1; break;}
         else if ( abs(*im) == 8000002) {BPrime = 1; break;}
         else {cout << "the mother has been chosen neither as T' or B'" << endl; break;} 
      }
         //Pick the TT branches
         std::auto_ptr< unsigned >  TTtoWbZt      (new unsigned (0));
         std::auto_ptr< unsigned >  TTtoWbHt      (new unsigned (0));
         std::auto_ptr< unsigned >  TTtoHtZt      (new unsigned (0));
         std::auto_ptr< unsigned >  TTtoWbWb      (new unsigned (0));
         std::auto_ptr< unsigned >  TTtoHtHt      (new unsigned (0));
         std::auto_ptr< unsigned >  TTtoZtZt      (new unsigned (0));
   
         //Pick the BB branches
         std::auto_ptr< unsigned >  BBtoWtZb      (new unsigned (0));
         std::auto_ptr< unsigned >  BBtoWtHb      (new unsigned (0));
         std::auto_ptr< unsigned >  BBtoHbZb      (new unsigned (0));
         std::auto_ptr< unsigned >  BBtoWtWt      (new unsigned (0));
         std::auto_ptr< unsigned >  BBtoHbHb      (new unsigned (0));
         std::auto_ptr< unsigned >  BBtoZbZb      (new unsigned (0));   
      
      bool H(0), t(0), W(0), b(0), Z(0);
      int numWb(0), numHt(0), numZt(0), numWt(0), numHb(0), numZb(0);
      
      for ( unsigned igen = 0; igen < (h_genPartID.product())->size(); ++igen ) {
         
         if ( std::find(ids_.begin(), ids_.end(), (h_genPartID.product())->at(igen)) == ids_.end()
              || ( checkmomid_ && std::find(momids_.begin(), momids_.end(), (h_genPartMomID.product())->at(igen)) == momids_.end() )
              || ( checkstatus_ && std::find(statuses_.begin(), statuses_.end(), (h_genPartStatus.product())->at(igen)) == statuses_.end() )
            )continue;
         
         int pdgId = (h_genPartID.product())->at(igen);
         if (verbose_){
            int status = (h_genPartStatus.product())->at(igen);
            int mother = (h_genPartMomID.product())->at(igen);
            cout << " pdgid = " << pdgId << ", status = " << status << ", mother = " << mother << endl ;
         } 
         
         if (abs(pdgId) == 25) H = true;
         if (abs(pdgId) == 24) W = true;
         if (abs(pdgId) == 23) Z = true;
         if (abs(pdgId) ==  6) t = true;
         if (abs(pdgId) ==  5) b = true; 
         //TT
         if ( W==1 && b==1) {++numWb; W=0; b=0;}
         if ( H==1 && t==1) {++numHt; H=0; t=0;}
         if ( Z==1 && t==1) {++numZt; Z=0; t=0;} 
         //BB
         if ( W==1 && t==1) {++numWt; W=0; t=0;}
         if ( H==1 && b==1) {++numHb; H=0; b=0;}
         if ( Z==1 && b==1) {++numZb; Z=0; b=0;} 
      }
      
      //if(numWb+numHt+numZt != 2){cout << "Suspecious event, how can't you not find a decay of TT" << endl;}
      //if(numWt+numHb+numZb != 2){cout << "Suspecious event, how can't you not find a decay of BB" << endl;}
      
      //TT
      if      (numWb+numHt == 2 && numWb != 2 && numHt !=2) {*TTtoWbHt = 1;}
      else if (numWb+numZt == 2 && numWb != 2 && numZt !=2) {*TTtoWbZt = 1;}
      else if (numHt+numZt == 2 && numHt != 2 && numZt !=2) {*TTtoHtZt = 1;}
      else if (numWb == 2)                                  {*TTtoWbWb = 1;}
      else if (numHt == 2)                                  {*TTtoHtHt = 1;}
      else if (numZt == 2)                                  {*TTtoZtZt = 1;}
      
      //BB
      if      (numWt+numHb == 2 && numWt != 2 && numHb !=2) {*BBtoWtHb = 1;}
      else if (numWt+numZb == 2 && numWt != 2 && numZb !=2) {*BBtoWtZb = 1;}
      else if (numHb+numZb == 2 && numHb != 2 && numZb !=2) {*BBtoHbZb = 1;}
      else if (numWt == 2)                                  {*BBtoWtWt = 1;}
      else if (numHb == 2)                                  {*BBtoHbHb = 1;}
      else if (numZb == 2)                                  {*BBtoZbZb = 1;}
      
      if (verbose_){
         cout << "WbHt = " << *TTtoWbHt <<", WbZt = " << *TTtoWbZt <<", HtZt = " << *TTtoHtZt << ", WbWb = " << *TTtoWbWb <<", HtHt = "<< *TTtoHtHt <<", ZtZt = " << *TTtoZtZt << endl;
         cout << "WtHb = " << *BBtoWtHb <<", WtZb = " << *BBtoWtZb <<", HbZb = " << *BBtoHbZb << ", WtWt = " << *BBtoWtWt <<", HbHb = "<< *BBtoHbHb <<", ZbZb = " << *BBtoZbZb << endl;
      }
     
      
      if(TPrime){
         iEvent.put ( TTtoWbZt,       "TTtoWbZt"      );
         iEvent.put ( TTtoWbHt,       "TTtoWbHt"      );
         iEvent.put ( TTtoHtZt,       "TTtoHtZt"      );
         iEvent.put ( TTtoWbWb,       "TTtoWbWb"      );
         iEvent.put ( TTtoHtHt,       "TTtoHtHt"      );
         iEvent.put ( TTtoZtZt,       "TTtoZtZt"      );
      }
      else if(BPrime){
         iEvent.put ( BBtoWtZb,       "BBtoWtZb"      );
         iEvent.put ( BBtoWtHb,       "BBtoWtHb"      );
         iEvent.put ( BBtoHbZb,       "BBtoHbZb"      );
         iEvent.put ( BBtoWtWt,       "BBtoWtWt"      );
         iEvent.put ( BBtoHbHb,       "BBtoHbHb"      );
         iEvent.put ( BBtoZbZb,       "BBtoZbZb"      );
      }
   }
}


//define this as a plug-in
DEFINE_FWK_MODULE(GenVLQSel);
