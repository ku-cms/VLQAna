#!/usr/bin/env python

usage='''
Usage: 
python plotHLTEff.py singleT_Trig.root HT
python plotHLTEff.py singleT_Trig.root Mjj

The first argument is the filename, the second argument is the histogram name used to plot the efficiency
'''

import sys, ROOT

if len(sys.argv) < 3:
  sys.exit(usage)

sys.argv.append('-b')

f = ROOT.TFile(sys.argv[1], "README")

hden = f.Get("/hh4b/"+sys.argv[2])
hnum = f.Get("/hh4btest/"+sys.argv[2])

nbins = int(sys.argv[3])

run = sys.argv[4]

hden.Rebin(nbins)
hnum.Rebin(nbins)

ROOT.gROOT.SetBatch(1)
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPalette(1)
ROOT.gStyle.SetNdivisions(405,"x");
ROOT.gStyle.SetEndErrorSize(0.)
ROOT.gStyle.SetErrorX(0.001)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)

c0 = ROOT.TCanvas("SingleMu_"+run+"_"+sys.argv[2]+"_all_pass","",800,600)
c0.cd()
c0.SetLogy()
hden.SetLineColor(2)
hnum.SetLineColor(3)
hden.GetXaxis().SetRangeUser(500,3000)
hden.GetYaxis().SetTitle("Events/"+str(int(hden.GetBinWidth(1)))+" GeV")
hden.Draw("hist")
hnum.Draw("histsame")
c0.Update()
leg = ROOT.TLegend(0.5,0.6,0.88,0.88,"","brNDC")
leg.SetBorderSize(0)
leg.SetFillColor(0)
leg.SetTextSize(0.020)
leg.SetHeader(run)
leg.AddEntry(hden,"PFJet260 (prescaled)","l")
leg.AddEntry(hnum,"PFJet260 (prescaled) && OR combination","l")
leg.Draw()
c0.Update()
txt0 = ROOT.TPaveText(0.4,0.55,0.88,0.65,"brNDC")
txt0.SetBorderSize(0)
txt0.SetFillColor(0)
txt0.SetTextFont(42);
txt0.SetTextSize(0.02);
txt0.AddText("Jet p_{T} > 200 GeV, |#eta| < 2.4")
txt0.AddText("#Delta#eta| < 1.3 jet mass > 50 GeV")
txt0.Draw()
c0.Update()
c0.RedrawAxis()
c0.SaveAs(c0.GetName()+".pdf")
c0.SaveAs(c0.GetName()+".root")
c0.SaveAs(c0.GetName()+".C")

c = ROOT.TCanvas("SingleMu_"+run+"_"+"trigeff_"+sys.argv[2],"",800,600)
c.cd()
gr = ROOT.TGraphAsymmErrors(hnum, hden, 'cp')
gr.SetLineColor(1)
gr.SetMarkerColor(1)
gr.SetMarkerStyle(20)
gr.Draw("AEP")
gr.GetHistogram().GetXaxis().SetRangeUser(500,3000)
gr.GetHistogram().GetXaxis().SetTitle(hden.GetXaxis().GetTitle())
gr.GetHistogram().GetYaxis().SetTitle("Efficiency")
c.Update()
leg = ROOT.TLegend(0.3,0.5,0.88,0.70,"","brNDC")
leg.SetBorderSize(0)
leg.SetFillColor(0)
leg.SetTextSize(0.020)
leg.SetHeader(run)
leg.AddEntry(gr,"#splitline{PFHT800 OR AK8PFHT650_TrimR0p1PT0p03Mass50}{#splitline{ OR AK8PFJet360 OR PFHT650_WideJetMJJ900DEtaJJ1p5}{#splitline{AK8PFHT700_TrimR0p1PT0p03Mass50}{ OR AK8DiPFJet280_200_TrimMass30_BTagCSV_p20}}}","l")
leg.Draw()
c.Update()
txt0 = ROOT.TPaveText(0.4,0.35,0.88,0.45,"brNDC")
txt0.SetBorderSize(0)
txt0.SetFillColor(0)
txt0.SetTextFont(42);
txt0.SetTextSize(0.02);
txt0.AddText("Jet p_{T} > 200 GeV, |#eta| < 2.4")
txt0.AddText("#Delta#eta| < 1.3 jet mass > 50 GeV")
txt0.Draw()
c.Update()
c.RedrawAxis()
c.SaveAs(c.GetName()+".pdf")
c.SaveAs(c.GetName()+".root")
c.SaveAs(c.GetName()+".C")
