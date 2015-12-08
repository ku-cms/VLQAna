#!/bin/python

from string import *
import subprocess
import os

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--command', metavar='C', type='string', action='store',
                  default='report',
                  dest='command',
                  help='crab command to execute')

parser.add_option('--skimType', metavar='S', type='string', action='store',
                  default='CR_Zelel',
                  dest='skimType',
                  help='skim type')

parser.add_option('--signal', metavar='S', type='int', action='store',
                  default = '0',
                  dest='signal',
                  help='check signal MC or not')


(options, args) = parser.parse_args()
print options

path = '/uscms_data/d2/skhalil/MyVLQAna2/CMSSW_7_4_15_patch1/src/Analysis/VLQAna/test/Skim/CRAB/Skims_'+options.skimType

mass = ['700', '800', '900', '1000', '1200', '1500']

sigSamples = []
if options.signal:
    if options.skimType == 'CR_Zelel': dir = 'B2GEDMNtuplesSkim_CR_20Nov/'
    elif options.skimType == 'SR_Zelel': dir = 'B2GEDMNtuplesSkim_SR_20Nov/'
    else: dir = 'B2GEDMNtuplesSkim_'+options.skimType+'_20Nov/'
    for m in mass:
        TT = 'TprimeTprime_M-'+m+'_25ns'
        BB = 'BprimeBprime_M-'+m+'_25ns' 
        sigSamples.append(TT)
        sigSamples.append(BB)
else:
    dir = 'B2GEDMNtuplesSkim_'+options.skimType+'_20Nov/'  
    sigSamples = [
          'TT_powheg-pythia8_ext3_25ns_'+options.skimType,
          'TTJets_MG_pythia8_asymptotic_25ns_'+options.skimType,
          'TTJets_HT-600to800_25ns_'+options.skimType,
          'TTJets_HT-800to1200_25ns_'+options.skimType,
          'TTJets_HT-1200to2500_25ns_'+options.skimType,  
          'TTJets_HT-2500toInf_25ns_'+options.skimType, 
          'ST_t-channel_antitop_powheg-pythia8_25ns_'+options.skimType, 
 
         #'WJets_HT_100to200_25ns_'+options.skimType,
         #'WJets_HT_200to400_25ns_'+options.skimType,
         #'WJets_HT_400to600_25ns_'+options.skimType,
         #'WJets_HT_600to800_25ns_'+options.skimType,
         #'WJets_HT_800to1200_25ns_'+options.skimType,
         #'WJets_HT_1200to2500_25ns_'+options.skimType,
         #'WJets_HT_2500toInf_25ns_'+options.skimType,
         #'DY_HT100to200_25ns_'+options.skimType,
         #'DY_HT200to400_25ns_'+options.skimType,
         #'DY_HT400to600_25ns_'+options.skimType,
         #'DY_HT600toInf_25ns_'+options.skimType,
        ]
     
for sig in sigSamples:
    sample = 'crab_'+sig
    exe = 'crab '+options.command+' -d '+path+'/'+dir+sample
    print '--------------->'
    print exe
    subprocess.call( [exe], shell=True )
