#! /usr/bin/env python

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--files', type='string', action='store',
    dest='files',
    help='Input files')

parser.add_option('--outname', type='string', action='store',
    default='outplots.root',
    dest='outname',
    help='Name of output file')

parser.add_option('--verbose', action='store_true',
    default=False,
    dest='verbose',
    help='Print debugging info')

parser.add_option('--maxEvts', type='int', action='store',
    default=-1,
    dest='maxEvts',
    help='Number of events to run. -1 is all events')

parser.add_option('--minMuonPt', type='float', action='store',
    default=30.,
    dest='minMuonPt',
    help='Minimum PT for muons')

parser.add_option('--maxMuonEta', type='float', action='store',
    default=2.1,
    dest='maxMuonEta',
    help='Maximum muon pseudorapidity')

parser.add_option('--minElectronPt', type='float', action='store',
    default=30.,
    dest='minElectronPt',
    help='Minimum PT for electrons')

parser.add_option('--maxElectronEta', type='float', action='store',
    default=2.5,
    dest='maxElectronEta',
    help='Maximum electron pseudorapidity')

parser.add_option('--minAK4Pt', type='float', action='store',
    default=30.,
    dest='minAK4Pt',
    help='Minimum PT for AK4 jets')

parser.add_option('--maxAK4Rapidity', type='float', action='store',
    default=2.4,
    dest='maxAK4Rapidity',
    help='Maximum AK4 rapidity')

parser.add_option('--minAK8Pt', type='float', action='store',
    default=400.,
    dest='minAK8Pt',
    help='Minimum PT for AK8 jets')

parser.add_option('--maxAK8Rapidity', type='float', action='store',
    default=2.4,
    dest='maxAK8Rapidity',
    help='Maximum AK8 rapidity')

(options, args) = parser.parse_args()
argv = []

import ROOT, sys, copy
from DataFormats.FWLite import Events, Handle

infiles = [options.files]
printGen = True
events = Events (infiles)

trigBitHandle, trigBitLabel, trigBitProd = Handle ("std::vector<float>"), ("TriggerUserData"), ("triggerBitTree")
trigNameHandle, trigNameLabel, trigNameProd = Handle ("std::vector<string>"), ("TriggerUserData"), ("triggerNameTree")

elPtHandle, elLabel, elPtProd = Handle ("std::vector<float>"), ("electrons"), ("elPt")
elEtaHandle, elLabel, elEtaProd = Handle ("std::vector<float>"), ("electrons"), ("elEta")
elPhiHandle, elLabel, elPhiProd = Handle ("std::vector<float>"), ("electrons"), ("elPhi")
elEHandle, elLabel, elEProd = Handle ("std::vector<float>"), ("electrons"), ("elE")
elChargeHandle, elLabel, elChargeProd = Handle ("std::vector<float>"), ("electrons"), ("elCharge")
elisMediumHandle, elLabel, elisMediumProd = Handle ("std::vector<float>"), ("electrons"), ("elisMedium")

muPtHandle, muLabel, muPtProd = Handle ("std::vector<float>"), ("muons"), ("muPt")
muEtaHandle, muLabel, muEtaProd = Handle ("std::vector<float>"), ("muons"), ("muEta")
muPhiHandle, muLabel, muPhiProd = Handle ("std::vector<float>"), ("muons"), ("muPhi")
muEHandle, muLabel, muEProd = Handle ("std::vector<float>"), ("muons"), ("muE")
muChargeHandle, muLabel, muChargeProd = Handle ("std::vector<float>"), ("muons"), ("muCharge")
muIsTightMuonHandle, muLabel, muIsTightMuonProd = Handle ("std::vector<float>"), ("muons"), ("muIsTightMuon")

jetAK4PtHandle, jetAK4Label, jetAK4PtProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4Pt")
jetAK4GenPartPtHandle, jetAK4Label, jetAK4GenPartPtProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4GenPartonPt")
jetAK4EtaHandle, jetAK4Label, jetAK4EtaProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4Eta")
jetAK4GenPartYHandle, jetAK4Label, jetAK4GenPartYProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4GenPartonY")
jetAK4PhiHandle, jetAK4Label, jetAK4PhiProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4Phi")
jetAK4EHandle, jetAK4Label, jetAK4EProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4E")
jetAK4FlavourHandle, jetAK4Label, jetAK4FlavourProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4HadronFlavour")
jetAK4CSVHandle, jetAK4Label, jetAK4CSVProd = Handle ("std::vector<float>"), ("jetsAK4"), ("jetAK4CSV")

jetAK8PtHandle, jetAK8Label, jetAK8PtProd = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8Pt")
jetAK8EtaHandle, jetAK8Label, jetAK8EtaProd = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8Eta")
jetAK8PhiHandle, jetAK8Label, jetAK8PhiProd = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8Phi")
jetAK8EHandle, jetAK8Label, jetAK8EProd = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8E")
jetAK8MassHandle, jetAK8Label, jetAK8MassProd = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8Mass")
jetAK8subjetIndex0Handle, jetAK8Label, jetAK8subjetIndex0Prod = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8subjetIndex0")
jetAK8subjetIndex1Handle, jetAK8Label, jetAK8subjetIndex1Prod = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8subjetIndex1")
jetAK8FlavourHandle, jetAK8Label, jetAK8FlavourProd = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8HadronFlavour")
jetAK8tau1Handle, jetAK8Label, jetAK8tau1Prod = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8tau1")
jetAK8tau2Handle, jetAK8Label, jetAK8tau2Prod = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8tau2")
jetAK8tau3Handle, jetAK8Label, jetAK8tau3Prod = Handle ("std::vector<float>"), ("jetsAK8"), ("jetAK8tau3")

subjetAK8PtHandle, subjetAK8Label, subjetAK8PtProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8Pt")
subjetAK8EtaHandle, subjetAK8Label, subjetAK8EtaProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8Eta")
subjetAK8PhiHandle, subjetAK8Label, subjetAK8PhiProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8Phi")
subjetAK8EHandle, subjetAK8Label, subjetAK8EProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8E")
subjetAK8MassHandle, subjetAK8Label, subjetAK8MassProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8Mass")
subjetAK8FlavourHandle, subjetAK8Label, subjetAK8FlavourProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8HadronFlavour")
subjetAK8CSVHandle, subjetAK8Label, subjetAK8CSVProd = Handle ("std::vector<float>"), ("subjetsAK8"), ("subjetAK8subjetCSV")

jetsCmsTopTagPtHandle, jetsCmsTopTagLabel, jetsCmsTopTagPtProd = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagPt")
jetsCmsTopTagEtaHandle, jetsCmsTopTagLabel, jetsCmsTopTagEtaProd = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagEta")
jetsCmsTopTagPhiHandle, jetsCmsTopTagLabel, jetsCmsTopTagPhiProd = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagPhi")
jetsCmsTopTagEHandle, jetsCmsTopTagLabel, jetsCmsTopTagEProd = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagE")
jetsCmsTopTagMassHandle, jetsCmsTopTagLabel, jetsCmsTopTagMassProd = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagMass")
jetsCmsTopTagsubjetIndex0Handle, jetsCmsTopTagLabel, jetsCmsTopTagsubjetIndex0Prod = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagsubjetIndex0")
jetsCmsTopTagsubjetIndex1Handle, jetsCmsTopTagLabel, jetsCmsTopTagsubjetIndex1Prod = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagsubjetIndex1")
jetsCmsTopTagFlavourHandle, jetsCmsTopTagLabel, jetsCmsTopTagFlavourProd = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagHadronFlavour")
jetsCmsTopTagtau1Handle, jetsCmsTopTagLabel, jetsCmsTopTagtau1Prod = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagtau1")
jetsCmsTopTagtau2Handle, jetsCmsTopTagLabel, jetsCmsTopTagtau2Prod = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagtau2")
jetsCmsTopTagtau3Handle, jetsCmsTopTagLabel, jetsCmsTopTagtau3Prod = Handle ("std::vector<float>"), ("jetsCmsTopTag"), ("jetsCmsTopTagtau3")

genPtHandle, genLabel, genPtProd = Handle("std::vector<float>"), ("genPart"), ("genPartPt")
genEtaHandle, genLabel, genEtaProd = Handle("std::vector<float>"), ("genPart"), ("genPartEta")
genPhiHandle, genLabel, genPhiProd = Handle("std::vector<float>"), ("genPart"), ("genPartPhi")
genEHandle, genLabel, genEProd = Handle("std::vector<float>"), ("genPart"), ("genPartE")
genIDHandle, genLabel, genIDProd = Handle("std::vector<float>"), ("genPart"), ("genPartID")
genStatusHandle, genLabel, genStatusProd = Handle("std::vector<float>"), ("genPart"), ("genPartStatus")
genMomIDHandle, genLabel, genMomIDProd = Handle("std::vector<float>"), ("genPart"), ("genPartMomID")
genMom0IDHandle, genLabel, genMom0IDProd = Handle("std::vector<float>"), ("genPart"), ("genPartMom0ID")
genMom1IDHandle, genLabel, genMom1IDProd = Handle("std::vector<float>"), ("genPart"), ("genPartMom1ID")
genDau0IDHandle, genLabel, genDau0IDProd = Handle("std::vector<float>"), ("genPart"), ("genPartDau0ID")
genDau1IDHandle, genLabel, genDau1IDProd = Handle("std::vector<float>"), ("genPart"), ("genPartDau1ID")

f = ROOT.TFile(options.outname, "RECREATE")
f.cd()

hpassedHLTBits = ROOT.TH1D("hpassedHLTBits", ";passed HLT bits;", 104, -0.5, 103.5)

hak4jetPt = ROOT.TH1D("hak4jetPt", ";AK4 jets p_{t} [GeV];;", 200, 0.0, 2000.)
hak4jetEta = ROOT.TH1D("hak4jetEta", ";AK4 jets #eta;;", 20, -4, 4)

hak8jetPt = ROOT.TH1D("hak8jetPt", ";AK8 jets p_{t} [GeV];;", 200, 0.0, 2000.)

hak8jetEta = ROOT.TH1D("hak8jetEta", ";AK8 jets #eta;;", 20, -4, 4)

hak8jetPhi = ROOT.TH1D("hak8jetPhi", ";AK8 jets #phi;;", 20, -4, 4)

hak8jetFlavour = ROOT.TH1D("hak8jetFlavour", "AK8 jets flavour", 8, -0.5, 7.5) 

hdrak8jetClosestel = ROOT.TH1D("hdrak8jetClosestel", "#DeltaR(AK8 jet, closest electron)", 80, 0., 4.0) 
hdrak8jetClosestmu = ROOT.TH1D("hdrak8jetClosestmu", "#DeltaR(AK8 jet, closest #mu)", 80, 0., 4.0) 

####

htprimept = ROOT.TH1D("htprimept",";p_{T} (T) [GeV];;", 100, 0.0, 1000.)
htprimey = ROOT.TH1D("htprimey",";y (T);;", 80, -4, 4)

htoppt = ROOT.TH1D("htoppt",";p_{t} (t) [GeV];;", 100, 0.0, 1000.)
htopy = ROOT.TH1D("htopy",";y (t);;", 80, -4, 4)

hWpt = ROOT.TH1D("hWpt",";p_{t} (W) [GeV];;", 100, 0.0, 1000.)
hWy = ROOT.TH1D("hWy",";y (W);;", 80, -4, 4)

hbFromtpt = ROOT.TH1D("hbFromtpt",";p_{t} (b from t) [GeV];;", 100, 0.0, 1000.)
hbFromty = ROOT.TH1D("hbFromty",";y (b from t);;", 80, -4, 4)

hdrwb = ROOT.TH1D("hdrwb", ";#DeltaR(Wb);;",40, 0, 4)

htopjetpt = ROOT.TH1D("htopjetpt",";p_{T} (top jet) [GeV];;", 400, 0.0, 800.)
htopjety = ROOT.TH1D("htopjety",";y (top jet);;", 80, -4, 4)
htopjetmass = ROOT.TH1D("htopjetmass",";M (top jet) [GeV];;", 100, 0.0, 200.)
htopjettau21 = ROOT.TH1D("htopjettau21",";#tau2/#tau1 (top jet);;", 40, 0.0, 1.)
htopjettau32 = ROOT.TH1D("htopjettau32",";#tau3/#tau2 (top jet);;", 40, 0.0, 1.)

hhiggspt = ROOT.TH1D("hhiggspt",";p_{T} (H) [GeV];;", 400, 0.0, 800.)
hhiggsy = ROOT.TH1D("hhiggsy",";y (H);;", 80, -4, 4)
h2ptbb_drbb = ROOT.TH2D("h2ptbb_drbb", ";p_{T} (b#bar{b}) [GeV];#DeltaR(b#bar{b});",400, 0.0, 800.,80, 0, 4) 

hhiggsjetpt = ROOT.TH1D("hhiggsjetpt",";p_{T} (H jet) [GeV];;", 400, 0.0, 800.)
hhiggsjety = ROOT.TH1D("hhiggsjety",";y (H jet);;", 80, -4, 4)
hhiggsjetmass = ROOT.TH1D("hhiggsjetmass",";M (H jet) [GeV];;", 100, 0.0, 200.)
hhiggsjettau21 = ROOT.TH1D("hhiggsjettau21",";#tau2/#tau1 (H jet);;", 40, 0.0, 1.)

hsubjet0CSV = ROOT.TH1D("hsubjet0CSV",";subjet 0 CSV;;", 40, 0, 1.2)
hsubjet1CSV = ROOT.TH1D("hsubjet1CSV",";subjet 1 CSV;;", 40, 0, 1.2)
hdrsubjets = ROOT.TH1D("hdrsubjets", ";#DeltaR(subjets);",40, 0, 1) 

hhiggstaggedjetpt = ROOT.TH1D("hhiggstaggedjetpt",";p_{T} (H jet) [GeV];;", 400, 0.0, 800.)

hotherbpt = ROOT.TH1D("hotherbpt",";p_{T} (associated b quark) [GeV];;", 400, 0.0, 800.)
hotherby = ROOT.TH1D("hotherby",";y (associated b quark);;", 80, -4, 4)

hotherbjetpt = ROOT.TH1D("hotherbjetpt",";p_{T} (associated b jet) [GeV];;", 400, 0.0, 800.)
hotherbjety = ROOT.TH1D("hotherbjety",";y (associated b jet);;", 80, -4, 4)
hotherbjetCSV = ROOT.TH1D("hotherbjetCSV",";CSV disc. (associated b jet);;", 40, 0., 1.2) 

hotherqpt = ROOT.TH1D("hotherqpt",";p_{T} (associated quark) [GeV];;", 400, 0.0, 800.)
hotherqy = ROOT.TH1D("hotherqy",";y (associated quark);;", 80, -4, 4)

hotherqjetpt = ROOT.TH1D("hotherqjetpt",";p_{T} (associated quark) [GeV];;", 400, 0.0, 800.)
hotherqjety = ROOT.TH1D("hotherqjety",";y (associated jet);;", 80, -4, 4)
hotherqjetCSV = ROOT.TH1D("hotherqjetCSV",";CSV disc. (associated jet);;", 40, 0., 1.2) 

hforwardjetpt = ROOT.TH1D("hforwardjetpt",";p_{T} (forward jet) [GeV];;", 400, 0.0, 800.)
hforwardjetGenPartPt = ROOT.TH1D("hforwardjetGenPartPt",";p_{T} (forward jet gen parton) [GeV];;", 400, 0.0, 800.)
hforwardjeteta = ROOT.TH1D("hforwardjeteta",";#eta (forward jet);;", 80, -4, 4) 
hforwardjetGenPartY = ROOT.TH1D("hforwardjetGenPartY",";y (forward jet gen parton);;", 80, -4, 4) 
hforwardjetflavour = ROOT.TH1D("hforwardjetflavour",";forward jet flavour;;", 8, -0.5, 7.5) 
hforwardjetCSV = ROOT.TH1D("hforwardjetCSV",";forward jet CSV;;", 40, 0, 1.2)

# loop over events
i = 1
for event in events:
  if (i > options.maxEvts):
    break
  if i%1000 == 0:
    print  '--------- Processing Event ' + str(i)

  event.getByLabel (trigBitLabel, trigBitProd, trigBitHandle)
  event.getByLabel (trigNameLabel, trigNameProd, trigNameHandle)

  event.getByLabel (elLabel, elPtProd, elPtHandle)
  event.getByLabel (elLabel, elEtaProd, elEtaHandle)
  event.getByLabel (elLabel, elPhiProd, elPhiHandle)
  event.getByLabel (elLabel, elEProd, elEHandle)
  event.getByLabel (elLabel, elChargeProd, elChargeHandle)
  event.getByLabel (elLabel, elisMediumProd, elisMediumHandle)

  event.getByLabel (muLabel, muPtProd, muPtHandle)
  event.getByLabel (muLabel, muEtaProd, muEtaHandle)
  event.getByLabel (muLabel, muPhiProd, muPhiHandle)
  event.getByLabel (muLabel, muEProd, muEHandle)
  event.getByLabel (muLabel, muChargeProd, muChargeHandle)
  event.getByLabel (muLabel, muIsTightMuonProd, muIsTightMuonHandle)

  event.getByLabel (jetAK4Label, jetAK4PtProd, jetAK4PtHandle)
  event.getByLabel (jetAK4Label, jetAK4GenPartPtProd, jetAK4GenPartPtHandle)
  event.getByLabel (jetAK4Label, jetAK4EtaProd, jetAK4EtaHandle)
  event.getByLabel (jetAK4Label, jetAK4GenPartYProd, jetAK4GenPartYHandle)
  event.getByLabel (jetAK4Label, jetAK4PhiProd, jetAK4PhiHandle)
  event.getByLabel (jetAK4Label, jetAK4EProd, jetAK4EHandle)
  event.getByLabel (jetAK4Label, jetAK4FlavourProd, jetAK4FlavourHandle)
  event.getByLabel (jetAK4Label, jetAK4CSVProd, jetAK4CSVHandle)

  event.getByLabel (jetAK8Label, jetAK8PtProd, jetAK8PtHandle)
  event.getByLabel (jetAK8Label, jetAK8EtaProd, jetAK8EtaHandle)
  event.getByLabel (jetAK8Label, jetAK8PhiProd, jetAK8PhiHandle)
  event.getByLabel (jetAK8Label, jetAK8EProd, jetAK8EHandle)
  event.getByLabel (jetAK8Label, jetAK8MassProd, jetAK8MassHandle)
  event.getByLabel (jetAK8Label, jetAK8subjetIndex0Prod, jetAK8subjetIndex0Handle)
  event.getByLabel (jetAK8Label, jetAK8subjetIndex1Prod, jetAK8subjetIndex1Handle)
  event.getByLabel (jetAK8Label, jetAK8FlavourProd, jetAK8FlavourHandle)
  event.getByLabel (jetAK8Label, jetAK8tau1Prod, jetAK8tau1Handle)
  event.getByLabel (jetAK8Label, jetAK8tau2Prod, jetAK8tau2Handle)
  event.getByLabel (jetAK8Label, jetAK8tau3Prod, jetAK8tau3Handle)

  event.getByLabel (subjetAK8Label, subjetAK8PtProd, subjetAK8PtHandle)
  event.getByLabel (subjetAK8Label, subjetAK8EtaProd, subjetAK8EtaHandle)
  event.getByLabel (subjetAK8Label, subjetAK8PhiProd, subjetAK8PhiHandle)
  event.getByLabel (subjetAK8Label, subjetAK8EProd, subjetAK8EHandle)
  event.getByLabel (subjetAK8Label, subjetAK8MassProd, subjetAK8MassHandle)
  event.getByLabel (subjetAK8Label, subjetAK8FlavourProd, subjetAK8FlavourHandle)
  event.getByLabel (subjetAK8Label, subjetAK8CSVProd, subjetAK8CSVHandle)

  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagPtProd, jetsCmsTopTagPtHandle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagEtaProd, jetsCmsTopTagEtaHandle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagPhiProd, jetsCmsTopTagPhiHandle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagEProd, jetsCmsTopTagEHandle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagMassProd, jetsCmsTopTagMassHandle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagsubjetIndex0Prod, jetsCmsTopTagsubjetIndex0Handle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagsubjetIndex1Prod, jetsCmsTopTagsubjetIndex1Handle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagFlavourProd, jetsCmsTopTagFlavourHandle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagtau1Prod, jetsCmsTopTagtau1Handle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagtau2Prod, jetsCmsTopTagtau2Handle)
  event.getByLabel (jetsCmsTopTagLabel, jetsCmsTopTagtau3Prod, jetsCmsTopTagtau3Handle)

  event.getByLabel (genLabel, genPtProd, genPtHandle)
  event.getByLabel (genLabel, genEtaProd, genEtaHandle)
  event.getByLabel (genLabel, genPhiProd, genPhiHandle)
  event.getByLabel (genLabel, genEProd, genEHandle)
  event.getByLabel (genLabel, genIDProd, genIDHandle)
  event.getByLabel (genLabel, genStatusProd, genStatusHandle)
  event.getByLabel (genLabel, genMomIDProd, genMomIDHandle)
  #event.getByLabel (genLabel, genMom0IDProd, genMom0IDHandle)
  #event.getByLabel (genLabel, genMom1IDProd, genMom1IDHandle)
  #event.getByLabel (genLabel, genDau0IDProd, genDau0IDHandle)
  #event.getByLabel (genLabel, genDau1IDProd, genDau1IDHandle)

  trigBit = trigBitHandle.product()
  trigName = trigNameHandle.product()

  elPt = elPtHandle.product()
  elEta = elEtaHandle.product()
  elPhi = elPhiHandle.product()
  elE = elEHandle.product()
  elCharge = elChargeHandle.product()
  elisMedium = elisMediumHandle.product()

  muPt = muPtHandle.product()
  muEta = muEtaHandle.product()
  muPhi = muPhiHandle.product()
  muE = muEHandle.product()
  muCharge = muChargeHandle.product()
  muIsTightMuon = muIsTightMuonHandle.product()

  jetAK4Pt = jetAK4PtHandle.product()
  jetAK4GenPartPt = jetAK4GenPartPtHandle.product()
  jetAK4Eta = jetAK4EtaHandle.product()
  jetAK4GenPartY = jetAK4GenPartYHandle.product()
  jetAK4Phi = jetAK4PhiHandle.product()
  jetAK4E = jetAK4EHandle.product()
  jetAK4Flavour = jetAK4FlavourHandle.product()
  jetAK4CSV = jetAK4CSVHandle.product()

  jetAK8Pt = jetAK8PtHandle.product()
  jetAK8Eta = jetAK8EtaHandle.product()
  jetAK8Phi = jetAK8PhiHandle.product()
  jetAK8E = jetAK8EHandle.product()
  jetAK8Mass = jetAK8MassHandle.product()
  jetAK8subjetIndex0 = jetAK8subjetIndex0Handle.product()
  jetAK8subjetIndex1 = jetAK8subjetIndex1Handle.product()
  jetAK8Flavour = jetAK8FlavourHandle.product()
  jetAK8tau1 = jetAK8tau1Handle.product()
  jetAK8tau2 = jetAK8tau2Handle.product()
  jetAK8tau3 = jetAK8tau3Handle.product()

  subjetAK8Pt = subjetAK8PtHandle.product()
  subjetAK8Eta = subjetAK8EtaHandle.product()
  subjetAK8Phi = subjetAK8PhiHandle.product()
  subjetAK8E = subjetAK8EHandle.product()
  subjetAK8Mass = subjetAK8MassHandle.product()
  subjetAK8Flavour = subjetAK8FlavourHandle.product()
  subjetAK8CSV = subjetAK8CSVHandle.product()

  jetsCmsTopTagPt = jetsCmsTopTagPtHandle.product()
  jetsCmsTopTagEta = jetsCmsTopTagEtaHandle.product()
  jetsCmsTopTagPhi = jetsCmsTopTagPhiHandle.product()
  jetsCmsTopTagE = jetsCmsTopTagEHandle.product()
  jetsCmsTopTagMass = jetsCmsTopTagMassHandle.product()
  jetsCmsTopTagsubjetIndex0 = jetsCmsTopTagsubjetIndex0Handle.product()
  jetsCmsTopTagsubjetIndex1 = jetsCmsTopTagsubjetIndex1Handle.product()
  jetsCmsTopTagFlavour = jetsCmsTopTagFlavourHandle.product()
  jetsCmsTopTagtau1 = jetsCmsTopTagtau1Handle.product()
  jetsCmsTopTagtau2 = jetsCmsTopTagtau2Handle.product()
  jetsCmsTopTagtau3 = jetsCmsTopTagtau3Handle.product()

  genPt = genPtHandle.product() 
  genEta = genEtaHandle.product() 
  genPhi = genPhiHandle.product() 
  genE = genEHandle.product() 
  genID = genIDHandle.product() 
  genStatus = genStatusHandle.product() 
  genMomID = genMomIDHandle.product() 
  #genMom0ID = genMom0IDHandle.product() 
  #genMom1ID = genMom1IDHandle.product() 
  #genDau0ID = genDau0IDHandle.product() 
  #genDau1ID = genDau1IDHandle.product() 

  for itrig in range(0,trigName.size()):
    if i == 1:
      print " HLT bit ", itrig, " name ", trigName.at(itrig), " decision ", trigBit.at(itrig)
    if trigBit.at(itrig) == 1.0:
      hpassedHLTBits.Fill(itrig) 
  
  tpp4 = ROOT.TLorentzVector()
  topp4 = ROOT.TLorentzVector()
  wp4 = ROOT.TLorentzVector()
  qbFromtp4 = ROOT.TLorentzVector()
  higgsp4  = ROOT.TLorentzVector() 
  qbp4 = ROOT.TLorentzVector()
  qabp4 = ROOT.TLorentzVector()
  otherbp4 = ROOT.TLorentzVector()
  otherqp4 = ROOT.TLorentzVector()
  iW = -1 
  ibFromt = -1
  ih = -1
  ib = -1
  ibbar = -1 
  iotherb = -1 
  iotherq = -1 
  for igen in range(0,genPt.size()):

    if abs(genID.at(igen)) == 6000006: 
      tpp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
      htprimept.Fill(tpp4.Pt()) 
      htprimey.Fill(tpp4.Rapidity())
    elif abs(genID.at(igen)) == 6 and abs(genMomID.at(igen))==6000006:
      topp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
      htoppt.Fill(topp4.Pt()) 
      htopy.Fill(topp4.Rapidity())
    elif abs(genID.at(igen)) == 25 and abs(genMomID.at(igen))==6000006:
      higgsp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
      hhiggspt.Fill(higgsp4.Pt()) 
      hhiggsy.Fill(higgsp4.Rapidity())
      ih = igen
    elif abs(genID.at(igen)) == 24 and abs(genMomID.at(igen)) == 6:
        wp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
        hWpt.Fill(wp4.Pt()) 
        hWy.Fill(wp4.Rapidity())
        iW = igen 
    elif abs(genID.at(igen)) == 5 and abs(genMomID.at(igen)) == 6:
        qbFromtp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
        hbFromtpt.Fill(qbFromtp4.Pt()) 
        hbFromty.Fill(qbFromtp4.Rapidity())
        ibFromt = igen
    elif genID.at(igen) == 5 and abs(genMomID.at(igen)) == 25:
        qbp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
        ib = igen
    elif genID.at(igen) == -5 and abs(genMomID.at(igen)) == 25:
        qabp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
        ibbar = igen 
    elif abs(genID.at(igen)) == 5 and ( abs(genMomID.at(igen)) < 6 or abs(genMomID.at(igen)) == 21 ):
        iotherb = igen 
        otherbp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
        hotherbpt.Fill(otherbp4.Pt())
        hotherby.Fill(otherbp4.Rapidity())
    elif abs(genID.at(igen)) < 5 and ( abs(genMomID.at(igen)) < 6 or abs(genMomID.at(igen)) == 21 ):
        iotherq = igen 
        otherqp4.SetPtEtaPhiE(genPt.at(igen), genEta.at(igen), genPhi.at(igen), genE.at(igen))
        hotherqpt.Fill(otherqp4.Pt())
        hotherqy.Fill(otherqp4.Rapidity())

  if iW > -1 and ibFromt > -1:
    drwb = wp4.DeltaR(qbFromtp4)
    hdrwb.Fill(drwb)

  if qbp4.Pt() > 0 and qabp4.Pt() > 0:
    qbqabp4 = qbp4 + qabp4
    drbb = qbp4.DeltaR(qabp4)
    h2ptbb_drbb.Fill(higgsp4.Pt(),drbb) 

  for itop in range(0, jetsCmsTopTagPt.size()):
    topjetp4 = ROOT.TLorentzVector()
    topjetp4.SetPtEtaPhiE(jetsCmsTopTagPt.at(itop), jetsCmsTopTagEta.at(itop), jetsCmsTopTagPhi.at(itop), jetsCmsTopTagE.at(itop))
    htopjetpt.Fill(topp4.Pt())
    htopjety.Fill(topp4.Rapidity()) 
    htopjetmass.Fill(jetsCmsTopTagMass.at(itop))
    if jetsCmsTopTagtau1.at(itop) != 0:
      htopjettau21.Fill(jetsCmsTopTagtau2.at(itop)/jetsCmsTopTagtau1.at(itop))
    if jetsCmsTopTagtau2.at(itop) != 0:
      htopjettau32.Fill(jetsCmsTopTagtau3.at(itop)/jetsCmsTopTagtau2.at(itop))

  for iak8 in range(0, jetAK8Pt.size()): 
    isj0 = -1
    isj1 = -1 
    ak8p4 = ROOT.TLorentzVector()
    ak8p4.SetPtEtaPhiE(jetAK8Pt.at(iak8), jetAK8Eta.at(iak8), jetAK8Phi.at(iak8), jetAK8E.at(iak8))
    if ih > -1 and ib > -1 and ibbar > -1 and ak8p4.DeltaR(higgsp4) < 0.8 and ak8p4.DeltaR(qbp4) < 0.8 and ak8p4.DeltaR(qabp4) < 0.8:
      hhiggsjetpt.Fill(ak8p4.Pt())
      hhiggsjety.Fill(ak8p4.Rapidity()) 
      hhiggsjetmass.Fill(jetAK8Mass.at(iak8))
      hhiggsjettau21.Fill(jetAK8tau2.at(iak8)/jetAK8tau1.at(iak8))
      isj0 = int(jetAK8subjetIndex0.at(iak8))
      isj1 = int(jetAK8subjetIndex1.at(iak8))
      if isj0 > -1 and isj1 > -1 and isj0 < subjetAK8Pt.size() and isj1 < subjetAK8Pt.size():
        sj0p4 = ROOT.TLorentzVector() 
        sj1p4 = ROOT.TLorentzVector() 
        sj0p4.SetPtEtaPhiE(subjetAK8Pt.at(isj0), subjetAK8Eta.at(isj0), subjetAK8Phi.at(isj0), subjetAK8E.at(isj0))
        sj1p4.SetPtEtaPhiE(subjetAK8Pt.at(isj1), subjetAK8Eta.at(isj1), subjetAK8Phi.at(isj1), subjetAK8E.at(isj1))
        hdrsubjets.Fill(sj0p4.DeltaR(sj1p4))
        hsubjet0CSV.Fill(subjetAK8CSV.at(isj0))
        hsubjet1CSV.Fill(subjetAK8CSV.at(isj1))
        ###Do Higgs-tagging
        if ( jetAK8Mass.at(iak8) > 110 and jetAK8Mass.at(iak8) < 150 and 
            jetAK8tau2.at(iak8)/jetAK8tau1.at(iak8) < 0.5 and
            subjetAK8CSV.at(isj0) > 0.814 and subjetAK8CSV.at(isj1) > 0.814):
          hhiggstaggedjetpt.Fill(ak8p4.Pt())

  iforwardjet = -1
  etaforwardjet = 0 
  for iak4 in range(0, jetAK4Pt.size()):
    ak4p4 = ROOT.TLorentzVector()
    ak4p4.SetPtEtaPhiE(jetAK4Pt.at(iak4), jetAK4Eta.at(iak4), jetAK4Phi.at(iak4), jetAK4E.at(iak4))
    if ak4p4.DeltaR(otherbp4) < 0.4:
      hotherbjetpt.Fill(ak4p4.Pt())
      hotherbjety.Fill(ak4p4.Rapidity())
      hotherbjetCSV.Fill(jetAK4CSV.at(iak4))
    if ak4p4.DeltaR(otherqp4) < 0.4:
      hotherqjetpt.Fill(ak4p4.Pt())
      hotherqjety.Fill(ak4p4.Rapidity())
      hotherqjetCSV.Fill(jetAK4CSV.at(iak4))
    if abs(ak4p4.Eta()) > etaforwardjet:
      etaforwardjet = abs(ak4p4.Eta()) 
      iforwardjet = iak4

  hforwardjetpt.Fill(jetAK4Pt.at(iforwardjet))
  hforwardjetGenPartPt.Fill(jetAK4GenPartPt.at(iforwardjet))
  hforwardjeteta.Fill(jetAK4Eta.at(iforwardjet))
  hforwardjetGenPartY.Fill(jetAK4GenPartY.at(iforwardjet))
  hforwardjetCSV.Fill(jetAK4CSV.at(iforwardjet))
  if abs(jetAK4Flavour.at(iforwardjet)) <=6:
    hforwardjetflavour.Fill(jetAK4Flavour.at(iforwardjet))
  elif (jetAK4Flavour.at(iforwardjet)) == 21:
    hforwardjetflavour.Fill(7)

  i = i + 1 # End of event loop 

f.cd()

hhiggstaggedjetpt.Rebin(20)
hhiggsjetpt.Rebin(20)
grhtageff = ROOT.TGraphAsymmErrors()
grhtageff.SetName("grhtageff")
grhtageff.Divide(hhiggstaggedjetpt, hhiggsjetpt, "cp")

f.Write()
f.Close()
