#!/usr/bin/env python

import os, sys, ROOT
import math

f = ROOT.TFile.Open(sys.argv[1], "READ")
mychain = f.Get("ana/tree")
entries=mychain.GetEntriesFast()

idxpdfs=range(111,212)

evtwt=0.
evtwtpdfUp=0.
evtwtpdfDown=0.

passevtwt=0.
passevtwtpdfUp=0.
passevtwtpdfDown=0.

for event in mychain:
  #issig = event.isRegionD
  #if not issig: continue

  pdfwtUp = 0.
  pdfwtDown = 0.

  lhewts = event.lhewts
  for i in idxpdfs: 
    lhewt = lhewts[i-1]
    if i%2 == 0:
      pdfwtUp += math.pow(lhewt.second-1,2.)
    elif i%2 == 1:
      pdfwtDown += math.pow(lhewt.second-1,2.)

  pdfwtUp = pdfwtUp/100.
  pdfwtDown = pdfwtDown/100.
  
  pdfwtUp = math.sqrt(pdfwtUp)
  pdfwtDown = math.sqrt(pdfwtDown)

  #print " pdfwtUp %s down %s" % (pdfwtUp, pdfwtDown)

  evtwt+=1
  evtwtpdfUp += 1+pdfwtUp
  evtwtpdfDown += 1-pdfwtDown
  
  idtop = event.idxTopTagged
  idhiggs = event.idxHTagged
  if len(idtop) < 1 or len(idhiggs) < 1: continue

  passevtwt+=1
  passevtwtpdfUp += 1+pdfwtUp
  passevtwtpdfDown += 1-pdfwtDown
  
print "evtwt %f pdfwt +%f -%f" % (evtwt, evtwtpdfUp, evtwtpdfDown)
print "pdfuncert = +%f -%f" % ((evtwtpdfUp-evtwt)/evtwt, (evtwt-evtwtpdfDown)/evtwt) 

aenominal = passevtwt/evtwt
aepdfwtUp = passevtwtpdfUp/evtwtpdfUp
aepdfwtDown = passevtwtpdfDown/evtwtpdfDown

print " nominal acceptance = ", aenominal
print " pdfwtUp acceptance = ", aepdfwtUp
print " pdfwtDown acceptance = ", aepdfwtDown

print "aceptance pdf uncert = %f %f" % ( (aepdfwtUp-aenominal)/aenominal, (aepdfwtDown-aenominal)/aenominal )
