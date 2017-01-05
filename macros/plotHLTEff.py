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
