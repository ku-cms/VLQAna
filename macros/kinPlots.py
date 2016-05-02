#!/usr/bin/env python

import os, sys, ROOT, math

def plot (f) :  

  fin = ROOT.TFile.Open(f)

  mass = (f.split('M-')[-1]).split('_')[0]
  
  mychain = fin.Get("hh4b/tree")
  entries = mychain.GetEntriesFast()
  
  hmsubtr = ROOT.TH1D("hmsubtr", ";M_{subtr}(jj);;", 40, 800, 2800)
  hmsubtr_nobtagsf = ROOT.TH1D("hmsubtr_nobtagsf", ";M_{subtr}(jj);;", 40, 800, 2800)
  
  hnSJBtagged = ROOT.TH1D("hnSJBtagged", ";N(b tagged subjets);;", 5, -0.5, 4.5)
  hnSJBtagged_bcUp = ROOT.TH1D("hnSJBtagged_bcUp", ";N(b tagged subjets);;", 5, -0.5, 4.5)
  hnSJBtagged_bcDown = ROOT.TH1D("hnSJBtagged_bcDown", ";N(b tagged subjets);;", 5, -0.5, 4.5)
  
  for event in mychain:
    msubtr = event.SelectedEvent_minv_leading2hjets_subtr
    nSJBTagged = event.HJets_nsubjetsBTaggedCSVL[0]+event.HJets_nsubjetsBTaggedCSVL[1]
    btagsf = event.SelectedEvent_btagsf
    btagsf_bcUp = event.SelectedEvent_btagsf_bcUp
    btagsf_bcDown = event.SelectedEvent_btagsf_bcDown
    if math.isnan(btagsf):
      #print "Gotcha! btagsf = ", btagsf, " is a nan"  
      continue
    if math.isnan(btagsf_bcUp):
      #print "Gotcha! btagsf_bcUp = ", btagsf_bcUp, " is a nan"  
      continue
    if math.isnan(btagsf_bcDown):
      #print "Gotcha! btagsf_bcDown = ", btagsf_bcDown, " is a nan"  
      continue
    hmsubtr_nobtagsf.Fill(msubtr)
    hmsubtr.Fill(msubtr,btagsf)
    hnSJBtagged.Fill(nSJBTagged, btagsf)
    hnSJBtagged_bcUp.Fill(nSJBTagged, btagsf_bcUp)
    hnSJBtagged_bcDown.Fill(nSJBTagged, btagsf_bcDown)
    #print 'btag sf %s + %s - %s' % (btagsf, btagsf_bcUp, btagsf_bcDown)
  
  #hmsubtr.SetLineColor(3)
  #hmsubtr_nobtagsf.SetLineColor(2)
  #
  #ROOT.gROOT.SetBatch(True)
  #
  #c_msubtr = ROOT.TCanvas("c_msubtr","M_{subtr}(jj)",800,600)
  #c_msubtr.cd()
  #hmsubtr_nobtagsf.Draw("hist")
  #hmsubtr.Draw("histsame")
  #c_msubtr.SaveAs(c_msubtr.GetName()+".pdf")
  #c_msubtr.SaveAs(c_msubtr.GetName()+".root")
  
  hnSJBtagged_bcUp.SetLineColor(2)
  hnSJBtagged_bcDown.SetLineColor(3)
  hnSJBtagged.SetLineColor(4)
  
  ROOT.gROOT.SetStyle('Plain')
  ROOT.gStyle.SetOptStat(0)

  c_nSJBtagged = ROOT.TCanvas("c_nSJBtagged_BG"+mass,"N(b tagged subjets)",800,600)
  c_nSJBtagged.cd()
  hnSJBtagged_bcUp.Draw("hist")
  hnSJBtagged_bcDown.Draw("histsame")
  hnSJBtagged.Draw("histsame")

  leg = ROOT.TLegend(0.12,0.68,0.52,0.88)
  leg.SetBorderSize(0)
  leg.SetHeader("BG"+mass)
  leg.AddEntry(hnSJBtagged, "N(b-tagged subjets)", "l")
  leg.AddEntry(hnSJBtagged_bcUp, "N(b-tagged subjets): b-tag SF up", "l")
  leg.AddEntry(hnSJBtagged_bcDown, "N(b-tagged subjets): b-tag SF down", "l")
  leg.Draw()

  c_nSJBtagged.SaveAs(c_nSJBtagged.GetName()+".pdf")
  c_nSJBtagged.SaveAs(c_nSJBtagged.GetName()+".root")
  
  fout = ROOT.TFile("nSJBtagged_BG"+mass+".root","RECREATE")
  fout.cd()
  hnSJBtagged.Write()
  hnSJBtagged_bcUp.Write()
  hnSJBtagged_bcDown.Write()

  fout.Close()
  
  #fout = ROOT.TFile("hmsubtr.root","RECREATE")
  #fout.cd()
  #hmsubtr.Write()
  #hmsubtr_nobtagsf.Write()
  #fout.Close()

  n2b = hnSJBtagged.GetBinContent(3)
  n2b_bcUp = hnSJBtagged_bcUp.GetBinContent(3)
  n2b_bcDown = hnSJBtagged_bcDown.GetBinContent(3) 
  
  n3b = hnSJBtagged.GetBinContent(4)
  n3b_bcUp = hnSJBtagged_bcUp.GetBinContent(4)
  n3b_bcDown = hnSJBtagged_bcDown.GetBinContent(4) 
  
  n4b = hnSJBtagged.GetBinContent(5)
  n4b_bcUp = hnSJBtagged_bcUp.GetBinContent(5)
  n4b_bcDown = hnSJBtagged_bcDown.GetBinContent(5) 
  
  btagerrUp_2b = (n2b_bcUp-n2b)/n2b
  btagerrDown_2b = (n2b_bcDown-n2b)/n2b

  btagerrUp_3b = (n3b_bcUp-n3b)/n3b
  btagerrDown_3b = (n3b_bcDown-n3b)/n3b

  btagerrUp_4b = (n4b_bcUp-n4b)/n4b
  btagerrDown_4b = (n4b_bcDown-n4b)/n4b

  #print "3b cat: ", hnSJBtagged.GetBinContent(4), " 4 b cat: ", hnSJBtagged.GetBinContent(5)
  #print "3b cat bcUp: ", hnSJBtagged_bcUp.GetBinContent(4), " 4 b cat bcUp: ", hnSJBtagged_bcUp.GetBinContent(5)
  #print "3b cat bcDown: ", hnSJBtagged_bcDown.GetBinContent(4), " 4 b cat bcDown: ", hnSJBtagged_bcDown.GetBinContent(5)
  
  print "BG",mass," GeV: "
  print "2 b cat: Btag uncert (up, down) = %f %f" % (btagerrUp_2b, btagerrDown_2b)
  print "3 b cat: Btag uncert (up, down) = %f %f" % (btagerrUp_3b, btagerrDown_3b)
  print "4 b cat: Btag uncert (up, down) = %f %f" % (btagerrUp_4b, btagerrDown_4b)
  print " " 

files = [
"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_29Apr2016/BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph_76X.root",
"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_29Apr2016/BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph_76X.root",
"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_29Apr2016/BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph_76X.root",
#"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016_V2/BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph_76X.root", 
#"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016_V2/BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph_76X.root", 
#"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016_V2/BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph_76X.root", 
#"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016_V2/BulkGravTohhTohbbhbb_narrow_M-1800_13TeV-madgraph_76X.root", 
#"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016_V2/BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph_76X.root", 
#"~/eos/cms/store/group/phys_b2g/devdatta/HH4b_76X_24Apr2016_V2/BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph_76X.root", 
]

for f in files:
  plot(f)

