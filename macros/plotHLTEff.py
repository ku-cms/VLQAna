#!/usr/bin/env python

import sys, ROOT

sys.argv.append('-b')

f = ROOT.TFile(sys.argv[1], "README")

hden = f.Get("/ana/Presel_"+sys.argv[2])
hnum = f.Get("/anatest/Presel_"+sys.argv[2])

ROOT.gROOT.SetStyle('Plain')
ROOT.gROOT.SetBatch(1)

c = ROOT.TCanvas("trigeff_"+sys.argv[2],"",800,600)
c.cd()

gr = ROOT.TGraphAsymmErrors(hnum, hden, 'cp')
gr.SetLineColor(1)
gr.SetMarkerColor(1)
gr.SetMarkerStyle(20)
gr.Draw("AEP")

c.SaveAs(c.GetName()+".pdf")
c.SaveAs(c.GetName()+".root")
