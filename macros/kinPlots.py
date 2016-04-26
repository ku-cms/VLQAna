#!/usr/bin/env python

import os, sys, ROOT, math

fin = ROOT.TFile.Open("~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016/BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph_76X.root")

mychain = fin.Get("hh4b/tree")
entries = mychain.GetEntriesFast()

hmsubtr = ROOT.TH1D("hmsubtr", ";M_{subtr}(jj);;", 40, 800, 2800)
hmsubtr_nobtagsf = ROOT.TH1D("hmsubtr_nobtagsf", ";M_{subtr}(jj);;", 40, 800, 2800)

hnSJBtagged = ROOT.TH1D("hnSJBtagged", ";N(b tagged subjets);;", 5, -0.5, 4.5)

for event in mychain:
  msubtr = event.SelectedEvent_minv_leading2hjets_subtr
  btagsf = event.SelectedEvent_btagsf
  hmsubtr_nobtagsf.Fill(msubtr)
  if math.isnan(btagsf):
    print "Gotcha! btagsf = ", btagsf, " is a nan"  
    continue
  hmsubtr.Fill(msubtr,btagsf)
  nSJBTagged = event.HJets_nsubjetsBTaggedCSVL[0]+event.HJets_nsubjetsBTaggedCSVL[1]
  hnSJBtagged.Fill(nSJBTagged)

hmsubtr.SetLineColor(3)
hmsubtr_nobtagsf.SetLineColor(2)

ROOT.gROOT.SetBatch(True)

c_msubtr = ROOT.TCanvas("c_msubtr","M_{subtr}(jj)",800,600)
c_msubtr.cd()
hmsubtr_nobtagsf.Draw("hist")
hmsubtr.Draw("histsame")
c_msubtr.SaveAs(c_msubtr.GetName()+".pdf")
c_msubtr.SaveAs(c_msubtr.GetName()+".root")

c_nSJBtagged = ROOT.TCanvas("c_nSJBtagged","N(b tagged subjets)",800,600)
c_nSJBtagged.cd()
hnSJBtagged.Draw("hist")
c_nSJBtagged.SaveAs(c_nSJBtagged.GetName()+".pdf")
c_nSJBtagged.SaveAs(c_nSJBtagged.GetName()+".root")

fout = ROOT.TFile("hmsubtr.root","RECREATE")
fout.cd()
hmsubtr.Write()
hmsubtr_nobtagsf.Write()
fout.Close()
