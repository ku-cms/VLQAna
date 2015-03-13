#!/usr/bin/env python

import sys, os, ROOT

ROOT.gROOT.SetStyle('Plain')
ROOT.gStyle.SetOptTitle(0) 
ROOT.gStyle.SetOptStat(0)

file = ROOT.TFile("infoSingleTprimevsBkg_Global_WthWt_2.root", "READ")
file.cd("Method_MLP/SingleTprimevsBkg_Global_WthWt_2_BFGS")

hmlp  = file.Get("/Method_MLP/SingleTprimevsBkg_Global_WthWt_2_BFGS/MVA_SingleTprimevsBkg_Global_WthWt_2_BFGS_rejBvsS")
hbdt  = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/MVA_SingleTprimevsBkg_Global_WthWt_2BDT_rejBvsS")
hbdtg = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDTG/MVA_SingleTprimevsBkg_Global_WthWt_2BDTG_rejBvsS")

hmlp.SetLineWidth(2)
hbdt.SetLineWidth(2)
hbdtg.SetLineWidth(2)

hmlp.SetLineColor(2)
hbdt.SetLineColor(3)
hbdtg.SetLineColor(4)

hmlp.GetXaxis().SetTitle("Signal efficiency")
hmlp.GetYaxis().SetTitle("1 - bkg. efficiency")

c0 = ROOT.TCanvas("ROCCurves_T1200GeV", "", 800, 600)
c0.cd()
hmlp.Draw()
hbdt.Draw("same")
hbdtg.Draw("same")

leg0 = ROOT.TLegend(0.14, 0.14, 0.52, 0.34, "brNdc")
leg0.SetBorderSize(0)
leg0.SetFillColor(0)
leg0.SetTextFont(132)
leg0.SetHeader("M(T) = 1200 GeV")
leg0.AddEntry(hmlp,  "MLP (BFGS)",  "l")
leg0.AddEntry(hbdt,  "BDT",  "l")
leg0.AddEntry(hbdtg, "BDTG", "l")
leg0.Draw()

c0.SaveAs(c0.GetName()+".pdf")
c0.SaveAs(c0.GetName()+".C")

hmlp_trainS = file.Get("/Method_MLP/SingleTprimevsBkg_Global_WthWt_2_BFGS/MVA_SingleTprimevsBkg_Global_WthWt_2_BFGS_Train_S")
hmlp_trainB = file.Get("/Method_MLP/SingleTprimevsBkg_Global_WthWt_2_BFGS/MVA_SingleTprimevsBkg_Global_WthWt_2_BFGS_Train_B")
hmlp_testS = file.Get("/Method_MLP/SingleTprimevsBkg_Global_WthWt_2_BFGS/MVA_SingleTprimevsBkg_Global_WthWt_2_BFGS_S")
hmlp_testB = file.Get("/Method_MLP/SingleTprimevsBkg_Global_WthWt_2_BFGS/MVA_SingleTprimevsBkg_Global_WthWt_2_BFGS_B")

hmlp_trainS.SetLineColor(2)
hmlp_trainB.SetLineColor(4)
hmlp_trainS.SetFillColor(2)
hmlp_trainB.SetFillColor(4)
hmlp_trainS.SetFillStyle(3356)
hmlp_trainB.SetFillStyle(3365)

hmlp_testS.SetLineColor(2)
hmlp_testB.SetLineColor(4)
hmlp_testS.SetMarkerColor(2)
hmlp_testB.SetMarkerColor(4)
hmlp_testS.SetMarkerStyle(20)
hmlp_testB.SetMarkerStyle(21)

hmlp_trainB.GetXaxis().SetTitle("MLP output")
hmlp_trainB.GetYaxis().SetTitle("Events")

c1 = ROOT.TCanvas("MLPOvertraining_T1200GeV", "", 800, 600)
c1.cd()
#c1.SetLogy()
hmlp_trainB.Draw("hist")
hmlp_trainS.Draw("histsame")
hmlp_testB.Draw("e1same")
hmlp_testS.Draw("e1same")

leg1 = ROOT.TLegend(0.42, 0.62, 0.88, 0.88, "brNdc")
leg1.SetBorderSize(0)
leg1.SetFillColor(0)
leg1.SetTextFont(132)
leg1.SetHeader("MLP (BFGS): M(T) = 1200 GeV")
leg1.AddEntry(hmlp_trainS,  "Signal training",  "l")
leg1.AddEntry(hmlp_trainB,  "Bkg training",  "l")
leg1.AddEntry(hmlp_testS,  "Signal testing",  "l")
leg1.AddEntry(hmlp_testB,  "Bkg testing",  "l")
leg1.Draw()

c1.SaveAs(c1.GetName()+".pdf")
c1.SaveAs(c1.GetName()+".C")

hbdtg_trainS = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDTG/MVA_SingleTprimevsBkg_Global_WthWt_2BDTG_Train_S")
hbdtg_trainB = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDTG/MVA_SingleTprimevsBkg_Global_WthWt_2BDTG_Train_B")
hbdtg_testS = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDTG/MVA_SingleTprimevsBkg_Global_WthWt_2BDTG_S")
hbdtg_testB = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDTG/MVA_SingleTprimevsBkg_Global_WthWt_2BDTG_B")

hbdtg_trainS.SetLineColor(2)
hbdtg_trainB.SetLineColor(4)
hbdtg_trainS.SetFillColor(2)
hbdtg_trainB.SetFillColor(4)
hbdtg_trainS.SetFillStyle(3356)
hbdtg_trainB.SetFillStyle(3365)

hbdtg_testS.SetLineColor(2)
hbdtg_testB.SetLineColor(4)
hbdtg_testS.SetMarkerColor(2)
hbdtg_testB.SetMarkerColor(4)
hbdtg_testS.SetMarkerStyle(20)
hbdtg_testB.SetMarkerStyle(21)

hbdtg_trainB.GetXaxis().SetTitle("BDTG output")
hbdtg_trainB.GetYaxis().SetTitle("Events")

c2 = ROOT.TCanvas("BDTGOvertraining_T1200GeV", "", 800, 600)
c2.cd()
#c2.SetLogy()
hbdtg_trainB.Draw("hist")
hbdtg_trainS.Draw("histsame")
hbdtg_testB.Draw("e1same")
hbdtg_testS.Draw("e1same")
hbdtg_trainB.SetMaximum(1.2*hbdtg_trainB.GetMaximum())

leg2 = ROOT.TLegend(0.42, 0.62, 0.88, 0.88, "brNdc")
leg2.SetBorderSize(0)
leg2.SetFillColor(0)
leg2.SetTextFont(132)
leg2.SetHeader("BDTG: M(T) = 1200 GeV")
leg2.AddEntry(hbdtg_trainS,  "Signal training",  "l")
leg2.AddEntry(hbdtg_trainB,  "Bkg training",  "l")
leg2.AddEntry(hbdtg_testS,  "Signal testing",  "l")
leg2.AddEntry(hbdtg_testB,  "Bkg testing",  "l")
leg2.Draw()

c2.SaveAs(c2.GetName()+".pdf")
c2.SaveAs(c2.GetName()+".C")

hbdt_trainS = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/MVA_SingleTprimevsBkg_Global_WthWt_2BDT_Train_S")
hbdt_trainB = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/MVA_SingleTprimevsBkg_Global_WthWt_2BDT_Train_B")
hbdt_testS = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/MVA_SingleTprimevsBkg_Global_WthWt_2BDT_S")
hbdt_testB = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/MVA_SingleTprimevsBkg_Global_WthWt_2BDT_B")

hbdt_trainS.SetLineColor(2)
hbdt_trainB.SetLineColor(4)
hbdt_trainS.SetFillColor(2)
hbdt_trainB.SetFillColor(4)
hbdt_trainS.SetFillStyle(3356)
hbdt_trainB.SetFillStyle(3365)

hbdt_testS.SetLineColor(2)
hbdt_testB.SetLineColor(4)
hbdt_testS.SetMarkerColor(2)
hbdt_testB.SetMarkerColor(4)
hbdt_testS.SetMarkerStyle(20)
hbdt_testB.SetMarkerStyle(21)

hbdt_trainB.GetXaxis().SetTitle("BDT output")
hbdt_trainB.GetYaxis().SetTitle("Events")

c3 = ROOT.TCanvas("BDTOvertraining_T1200GeV", "", 800, 600)
c3.cd()
#c3.SetLogy()
hbdt_trainB.Draw("hist")
hbdt_trainS.Draw("histsame")
hbdt_testB.Draw("e1same")
hbdt_testS.Draw("e1same")
hbdt_trainB.SetMaximum(2.4*hbdt_trainB.GetMaximum())

leg3 = ROOT.TLegend(0.42, 0.62, 0.88, 0.88, "brNdc")
leg3.SetBorderSize(0)
leg3.SetFillColor(0)
leg3.SetTextFont(132)
leg3.SetHeader("BDT: M(T) = 1200 GeV")
leg3.AddEntry(hbdt_trainS,  "Signal training",  "l")
leg3.AddEntry(hbdt_trainB,  "Bkg training",  "l")
leg3.AddEntry(hbdt_testS,  "Signal testing",  "l")
leg3.AddEntry(hbdt_testB,  "Bkg testing",  "l")
leg3.Draw()

c3.SaveAs(c3.GetName()+".pdf")
c3.SaveAs(c3.GetName()+".C")

#########

hbdt_varhtak4jetsS = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/double_ana_htak4jets_SingleTpAna.obj__Signal")
hbdt_varhtak4jetsB = file.Get("/Method_BDT/SingleTprimevsBkg_Global_WthWt_2BDT/double_ana_htak4jets_SingleTpAna.obj__Background")

hbdt_varhtak4jetsS.SetLineColor(2)
hbdt_varhtak4jetsB.SetLineColor(4)
hbdt_varhtak4jetsS.SetFillColor(2)
hbdt_varhtak4jetsB.SetFillColor(4)
hbdt_varhtak4jetsS.SetFillStyle(3356)
hbdt_varhtak4jetsB.SetFillStyle(3365)

hbdt_varhtak4jetsB.GetXaxis().SetTitle("|#eta(forwardmost AK4 jet)|")
hbdt_varhtak4jetsB.GetYaxis().SetTitle("Events")

c4 = ROOT.TCanvas("BDTvarhtak4jets_T1200GeV", "", 800, 600)
c4.cd()
#c4.SetLogy()
hbdt_varhtak4jetsS.Draw("hist")
hbdt_varhtak4jetsS.Draw("histsame")
hbdt_varhtak4jetsB.SetMaximum(2.4*hbdt_varhtak4jetsB.GetMaximum())

leg4 = ROOT.TLegend(0.42, 0.62, 0.88, 0.88, "brNdc")
leg4.SetBorderSize(0)
leg4.SetFillColor(0)
leg4.SetTextFont(132)
leg4.SetHeader("M(T) = 1200 GeV")
leg4.AddEntry(hbdt_varhtak4jetsS,  "Signal",  "l")
leg4.AddEntry(hbdt_varhtak4jetsB,  "Bkg",  "l")
leg4.Draw()

c4.SaveAs(c4.GetName()+".pdf")
c4.SaveAs(c4.GetName()+".C")

