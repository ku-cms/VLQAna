#ifndef ANALYSIS_INTERFACE_BTAGSFUTILS_H
#define ANALYSIS_INTERFACE_BTAGSFUTILS_H
#include <TF1.h>
#include <map>

struct BTagSFUtils {

  public: 
    static double getBTagEff_CSVv2L (double pt, double jetFl) {

      //std::string hname="";
      //if (jetFl == 5) hname="b_sub1And2PtR";
      //else if (jetFl == 4) hname="c_sub1And2PtR";
      //else if (jetFl == 0) hname="light_sub1And2PtR"; 
      //TFile f(btageffFile_.c_str());
      //TH1D* heff = dynamic_cast<TH1D*>( f.Get(hname.c_str()) ) ; 
      //int bin = heff->FindBin(pt) ;
      //if ( bin < 1 ) eff = 0; 
      //else  { 
      //  if ( bin > heff->GetNbinsX() ) bin = heff->GetNbinsX(); 
      //  eff = heff->GetBinContent( bin ) ; 
      //}
      //delete heff ;
      //f.Close();

      double eff(1) ; 
      if (jetFl == 5) eff = 0.8 ; 
      else if (jetFl == 4) eff = 0.3 ; 
      else if (jetFl == 0) eff = 0.1 ; 
      return eff ;
    }

    static double getBTagSF_CSVv2L (double jetPt, double jetFl, double errbc, double errl) {
      double btagsf(1);

      double pt(jetPt) ; 
      if ((jetFl == 5 || jetFl == 4)) {
        if (jetPt < 30.) {
          pt = 30; 
          errbc *= 2;
        }
        if (jetPt > 670.) {
          pt = 670. ;
          errbc *= 2;
        }
      }
      else {
        if (jetPt < 20.) {
          pt= 20; 
          errl *= 2;
        }
        if (jetPt > 1000.) {
          pt = 1000. ;
          errl *= 2; 
        }
      }

      TF1* SFb_CSVv2L = new TF1("SFb_CSVv2L", "0.908299+(2.70877e-06*(log(x+370.144)*(log(x+370.144)*(3-(-(104.614*log(x+370.144)))))))",0,2000) ;

      std::map<std::pair<double,double>,double> SFb_CSVv2L_err = { 
        {std::make_pair(30,50)  , 0.022327613085508347}, 
        {std::make_pair(50,70)  , 0.015330483205616474}, 
        {std::make_pair(70,100) , 0.024493992328643799}, 
        {std::make_pair(100,140), 0.020933238789439201}, 
        {std::make_pair(140,200), 0.029219608753919601}, 
        {std::make_pair(200,300), 0.039571482688188553}, 
        {std::make_pair(300,670), 0.047329759448766708}  
      } ;

      TF1* SFc_CSVv2L = new TF1("SFc_CSVv2L", "0.908299+(2.70877e-06*(log(x+370.144)*(log(x+370.144)*(3-(-(104.614*log(x+370.144)))))))",0,2000) ;

      std::map<std::pair<double,double>,double> SFc_CSVv2L_err = { 
        {std::make_pair(30,50)  , 0.044655226171016693}, 
        {std::make_pair(50,70)  , 0.030660966411232948}, 
        {std::make_pair(70,100) , 0.048987984657287598}, 
        {std::make_pair(100,140), 0.041866477578878403}, 
        {std::make_pair(140,200), 0.058439217507839203}, 
        {std::make_pair(200,300), 0.079142965376377106}, 
        {std::make_pair(300,670), 0.094659518897533417}  
      } ;

      TF1* SFl_CSVv2L = new TF1("SFl_CSVv2L", "((1.07278+(0.000535714*x))+(-1.14886e-06*(x*x)))+(7.0636e-10*(x*(x*x)))",0,2000) ;
      TF1* SFl_CSVv2L_errUp = new TF1("SFl_CSVv2L_errUp", "((1.12921+(0.000804962*x))+(-1.87332e-06*(x*x)))+(1.18864e-09*(x*(x*x)))",0,2000) ; 
      TF1* SFl_CSVv2L_errDown = new TF1("SFl_CSVv2L_errDown", "((1.01637+(0.000265653*x))+(-4.22531e-07*(x*x)))+(2.23396e-10*(x*(x*x)))",0,2000) ;

      double errb(0), errc(0) ; 
      for ( auto const& ent : SFb_CSVv2L_err ) if (pt >= (ent.first).first && pt < (ent.first).second ) errb = ent.second ; 
      for ( auto const& ent : SFc_CSVv2L_err ) if (pt >= (ent.first).first && pt < (ent.first).second ) errc = ent.second ; 

      if (jetFl == 5) btagsf = SFb_CSVv2L->Eval(pt) + errb*errbc; 
      else if (jetFl == 4) btagsf = SFc_CSVv2L->Eval(pt) + errc*errbc; 
      else if (jetFl == 0) btagsf = (
          SFl_CSVv2L->Eval(pt)*(1 - abs(errl)) + 
          (SFl_CSVv2L_errUp->Eval(pt)*abs(errl)*(1+errl)/2) + 
          (SFl_CSVv2L_errDown->Eval(pt)*abs(errl)*(1-errl)/2) ) ;  

      return btagsf ; 
    }

};
#endif 
