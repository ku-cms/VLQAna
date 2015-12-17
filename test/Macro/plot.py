#! /usr/bin/env python
import sys
import os
import subprocess
from array import array
from ROOT import TH1D,TH2D,TFile,TMath,TCanvas,THStack,TLegend,TPave,TLine,TLatex
from ROOT import gROOT,gStyle,gPad,gStyle
from ROOT import Double,kBlue,kRed,kOrange,kMagenta,kYellow,kCyan,kGreen,kGray,kBlack,kTRUE

gROOT.Macro("~/rootlogon.C")
gStyle.SetOptStat(0)

# ===============
# options
# ===============
from optparse import OptionParser
parser = OptionParser()
parser.add_option('--Lumi', metavar='D', type='float', action='store',
                  default= 2200.,
                  dest='Lumi',
                  help='Data Luminosity in pb-1')

parser.add_option('--globalSF', metavar='SF', type='float',
                  default = 1.0,
                  dest='globalSF',
                  help='Global trigger SF (%default default)')

parser.add_option('--plotDir', metavar='P', type='string', action='store',
                  default='DecPlots',
                  dest='plotDir',
                  help='output directory of plots')

parser.add_option('--skimType', metavar='S', type='string', action='store',
                  default='CR_Zelel',
                  dest='skimType',
                  help='Skim type: CR_Zelel, CR_Zmumu, SR_Zelel, SR_Zmumu')

parser.add_option('--processDir', metavar='pD', type='string', action='store',
                  default='ana',
                  dest='processDir',
                  help='directory to read histograms from')

parser.add_option('--var', metavar='T', type='string', action='store',
                  default='cutflow',
                  dest='var',
                  help='variable to plot')

parser.add_option('--sys', metavar='T', type='string', action='store',
                  default='nominal',
                  dest='sys',
                  help='nominal, BTagSFup, BTagSFdown, ScaleUp, ScaleDown, MatchUp, MatchDown')

parser.add_option('--verbose',action='store_true',
                  default=False,
                  dest='verbose',
                  help='verbose switch')

parser.add_option('--rebin', metavar='T', type='int', action='store',
                  default='1',
                  dest='rebin',
                  help='rebin the histograms')

(options,args) = parser.parse_args()
# ==========end: options =============
var = options.var
lumi = options.Lumi
gSF  = options.globalSF
rebinS = options.rebin
pDir = options.processDir
plotDir = options.plotDir
skimType = options.skimType
verbose = options.verbose

if 'elel' in skimType: title = '#mu^{#pm}#mu^{#mp}+jets'
elif 'mumu' in skimType: title = 'e^{#pm}e^{#mp}+jets'
else: title = ''
# ==========add the input ============

execfile("input.py")

# === prepare the input labels and legends ===========
dataLabel     = 'Data_'
topLabel      = 'Top_'
dyLabel       = 'DY_'
sTopLabel     = 'STop_'

dataLeg       = 'Data'
topLeg        = 't#bar{t}'
dyLeg         = 'Drell-Yan'

# === create structure ============
top      = [[f_ttbar,         Top_xs,            Top_num,            lumi]]

dy       = [
            [f_DY100to200,    DY100to200_xs,      DY100to200_num,    lumi],
            [f_DY200to400,    DY200to400_xs,      DY200to400_num,    lumi],
            [f_DY400to600,    DY400to600_xs,      DY400to600_num,    lumi],
            [f_DY600toInf,    DY600toInf_xs,      DY600toInf_num,    lumi],    
           ]

tZtZ_800 = [[f_TpTp_tZtZ_800, TpTp800_xs,         TpTp800_num,       lumi]]
tZbW_800 = [[f_TpTp_tZbW_800, TpTp800_xs,         TpTp800_num,       lumi]]
tZtH_800 = [[f_TpTp_tZtH_800, TpTp800_xs,         TpTp800_num,       lumi]]

h_top      = getHisto(topLabel,        topLeg,         pDir, var,  top,      8,          verbose)
h_dy       = getHisto(dyLabel,         dyLeg,          pDir, var,  dy,       90,         verbose)
h_tZtZ_800 = getHisto('TT_tZtZ_M800_', 'TT_tZtZ_M800', pDir, var,  tZtZ_800, kBlue-9,    verbose)
h_tZbW_800 = getHisto('TT_tZbW_M800_', 'TT_tZbW_M800', pDir, var,  tZbW_800, kOrange-9,  verbose)
h_tZtH_800 = getHisto('TT_tZtH_M800_', 'TT_tZtH_M800', pDir, var,  tZtH_800, kMagenta+1, verbose)

templates = []
templates.append(h_top)
templates.append(h_dy)
templates.append(h_tZtZ_800)
templates.append(h_tZbW_800)
templates.append(h_tZtH_800)

#f = TFile(plotDir+"/"+skimType+"/"+var+".root", "RECREATE")
#for ihist in templates:
#    ihist.Write()
#f.Close()

#get background uncertainty
h_bkg = h_top.Clone()
h_bkg.Reset()
h_bkg.SetName("total bkg")
h_bkg.Add(h_dy)
h_bkg.Add(h_top)

#histo properties
nBins = h_bkg.GetNbinsX()
bMin = h_bkg.GetBinLowEdge(1)
bMax = h_bkg.GetBinLowEdge(nBins+1)
bin1 = h_bkg.GetXaxis().FindBin(bMin)
bin2 = h_bkg.GetXaxis().FindBin(bMax)

for ibin in range(0,nBins+1):    
    iTop     = h_top.GetBinContent(ibin)
    iDY      = h_dy.GetBinContent(ibin)
    # stat error
    stat_err = (h_bkg.GetBinError(ibin))**2 
    # add approximate systematic uncertainty to each bin
    lumi_err = 0.04**2
    btag_err = 0.017**2
    ID_err   = 0.03**2
    JES_err  = 0.05*0.05
    dy_err   = (0.1*iDY)**2
    top_err  = (0.1*iTop)**2
    
    new_err = stat_err + top_err + lumi_err + btag_err + ID_err + JES_err + dy_err
    if h_bkg.GetBinError(ibin) != 0: h_bkg.SetBinError(ibin, TMath.Sqrt(new_err))

h_bkg.SetMarkerSize(0)
h_bkg.SetLineWidth(2)
h_bkg.SetFillColor(14)
h_bkg.SetLineColor(0)
h_bkg.SetFillStyle(3244)

#histogram to print the total background with stat uncertainty
h_tot = h_top.Clone()
h_tot.Reset()
h_tot.SetName("Total_"+h_tot.GetName().split('_',1)[1])
h_tot.Add(h_top)
h_tot.Add(h_dy)

print h_tot.GetName().split('_',1)[1]

## =========Drawing==============

hs = THStack("","")

for ihist in reversed(templates[0:2]):
    hs.Add(ihist)
    print 'histo added', ihist.GetName()

# Canvas
c1 = TCanvas('c1', 'c1', 800, 600)
c1.Divide(1,2)
scale = (1.0 - 0.3)/0.35

# prepare top pad for original plot
pad = c1.cd(1)
pad.SetPad(0, 0.3, 1, 1)
pad.SetTopMargin(0.1)
pad.SetBottomMargin(0.005)
t = pad.GetTopMargin()

# prepare the 2nd pad
pad = c1.cd(2)
pad.SetPad(0, 0.0, 1, 0.3)
pad.SetTopMargin(0.06)
pad.SetBottomMargin(0.4)
pad.SetTickx(1)
pad.SetTicky(1)
c1.cd(1)

hs.SetMaximum(hs.GetMaximum()*5)
hs.SetMinimum(0.1)
gPad.SetLogy()

hs.Draw("Hist")
h_bkg.Draw("e2 same")
for ihist in reversed(templates[2:5]):
    #print 'overlaying, ', ihist.GetName() 
    ihist.Draw("ehist same")

xTitle= h_top.GetXaxis().GetTitle()
yTitle= h_top.GetYaxis().GetTitle()

setTitle(hs, xTitle)
gPad.RedrawAxis()
ll = TLatex()
ll.SetNDC(kTRUE)
ll.SetTextSize(0.05)
ll.DrawLatex(0.78,0.92, "2.2 fb^{-1} (13 TeV)");

cms = TLatex()
cms.SetNDC(kTRUE)
cms.SetTextFont(61)
cms.SetTextSize(0.08)
cms.DrawLatex(0.12, 1-t+0.2*t,"CMS")

sel = TLatex()
sel.SetNDC(kTRUE)
sel.SetTextSize(0.065)

chan = TLatex()
chan.SetNDC(kTRUE)
chan.SetTextSize(0.065)
chan.DrawLatex(0.50, 0.76, title)

prel = TLatex()
prel.SetNDC(kTRUE)
prel.SetTextFont(52)
prel.SetTextSize(0.75*t*0.76)
prel.DrawLatex(0.22,0.92,"Preliminary")

leg.Draw()
gPad.RedrawAxis()


c1.cd(2)
# add the systematic band
h_ratio = h_bkg.Clone()
h_ratio_bkg = h_bkg.Clone()
h_ratio_bkg.SetDirectory(0)
h_ratio.SetDirectory(0)
#h_ratio.Divide(h_data, h_tot)
h_ratio.Divide(h_tot, h_tot)
h_ratio_bkg.Divide(h_bkg, h_tot)

for ibin in range(1, nBins+1):
    if h_bkg.GetBinContent(ibin) == 0: h_ratio_bkg.SetBinContent(ibin,1)

prepareRatio(h_ratio, h_ratio_bkg, scale, xTitle)

line = TLine(bMin, 1, bMax, 1)
line.SetLineColor(kBlack)
h_ratio.Draw("")
h_ratio_bkg.Draw("e2same")
h_ratio.Draw("same")
line.Draw()

gPad.RedrawAxis()

#create a directory if it doesn't exist
m_1 = 'mkdir '+plotDir
m_2 = 'mkdir '+plotDir+"/"+skimType
if not os.path.isdir(plotDir):
    subprocess.call( [m_1], shell=True )
if not os.path.isdir(plotDir+"/"+skimType):
    subprocess.call( [m_2], shell=True )    
    
c1.SaveAs(plotDir+"/"+skimType+"/"+var+"_.pdf")
c1.SaveAs(plotDir+"/"+skimType+"/"+var+"_.gif")
raw_input("hold on")
