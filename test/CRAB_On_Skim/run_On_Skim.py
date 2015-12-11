#! /bin/python
import os
from string import *
import subprocess

from optparse import OptionParser


parser = OptionParser()

parser.add_option('--inputCfg', metavar='C', type='string', action='store',
                  default='crab_dummy_os2lana.py',
                  dest='inputCfg',
                  help='input config tag to be used')

parser.add_option('--outLabel', metavar='L', type='string', action='store',
                  default='os2lana_v1',
                  dest='outLabel',
                  help='output tag to be used')

parser.add_option('--skimType', metavar='S', type='string', action='store',
                  default='CR_Zmumu',
                  dest='skimType',
                  help='Skim type: CR_Zelel, CR_Zmumu, SR_Zelel, SR_Zmumu')
    
parser.add_option('--isData', metavar='I', type='int', action='store',
                  default=0,
                  dest='isData',
                  help='run on data or MC')



(options, args) = parser.parse_args()

#set the parameter options in os2lana.py
if options.isData == 1:
    isData  = 'isData=True'
    puOfficial = 'doPUReweightingOfficial=False'
else: 
    isData = 'isData=False'
    puOfficial = 'doPUReweightingOfficial=True'

if 'Zmumu' in options.skimType:
    mode = 'zdecaymode=zmumu'
    applySF = 'applyLeptonSFs=False'
elif 'Zelel' in options.skimType:
    mode = 'zdecaymode=zelel'
    applySF = 'applyLeptonSFs=True'

# add all the datasets for particular skim
if options.skimType=='CR_Zelel':
    print 'Submitting jobs for electron channel in control region -------->'
    jobList = [
        ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT100to200', ''],
        ['/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT200to400_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT200to400', ''],
        ['/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT400to600_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT400to600', ''],
        ['/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT600toInf_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT600toInf', ''],
        ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/skhalil-crab_TT_powheg-pythia8_ext3_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TT-powheg-pythia8-ext3', ''],
        ['/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_MG_pythia8_asymptotic_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_incl_madgraphMLM-pythia8', ''],
        ['/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-600to800_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-600to800_madgraphMLM-pythia8', ''],
        ['/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-800to1200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-800to1200_madgraphMLM-pythia8', ''],
        ['/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-1200to2500_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-1200to2500_madgraphMLM-pythia8', ''],
        ['/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-2500toInf_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-2500toInf_madgraphMLM-pythia8', ''],
        ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-800_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-800', 'EvtType_MC_tZtZ'],
        ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-800_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-800', 'EvtType_MC_tZtH'],
        ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-800_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-800', 'EvtType_MC_tZbW'],
        ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-900_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-900', 'EvtType_MC_tZtZ'],
        ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-900_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-900', 'EvtType_MC_tZtH'],
        ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-900_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-900', 'EvtType_MC_tZbW'],
        ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1000_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-1000', 'EvtType_MC_tZtZ'],
        ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1000_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-1000', 'EvtType_MC_tZtH'],
        ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1000_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-1000', 'EvtType_MC_tZbW'],
        ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1200_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-1200', 'EvtType_MC_tZtZ'],
        ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1200_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-1200', 'EvtType_MC_tZtH'],
        ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1200_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-1200', 'EvtType_MC_tZbW'],
        ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1500_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-1500', 'EvtType_MC_tZtZ'],
        ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1500_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-1500', 'EvtType_MC_tZtH'],
        ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1500_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-1500', 'EvtType_MC_tZbW'],
        ]

if options.skimType=='CR_Zmumu':
    print 'Submitting jobs for muon channel in control region -------->'
    jobList = [
        ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT100to200', ''],
        ]
    
for job in jobList:
     print '------prepare to run on :  ' + job[0] + ' -----------'
     f = open(options.inputCfg, 'r')
     instring = f.read()
     baseList = job[0].split('/')
     outname = job[1] + '_' + options.outLabel

     a0 = instring.replace( 'DUMMY_WORKDIR', "'"+options.outLabel+"'")
     a1 = a0.replace( 'DUMMY_DATASET', "'"+job[0]+"'" )
     a2 = a1.replace( 'DATA', "'"+isData+"'") 
     a3 = a2.replace( 'MODE', "'"+mode+"'")
     a4 = a3.replace( 'LEPSF', "'"+applySF+"'")
     a5 = a4.replace( 'PUOFF', "'"+puOfficial+"'")
    
     if 'Tprime' in baseList[1] or 'Bprime' in baseList[1]:     
         a6 = a5.replace( 'FILTERSIGNAL', "'filterSignal=True'")
         a7 = a6.replace('SIGNALTYPE', "'signalType="+job[2]+"'")  
     else:
         a6 = a5.replace( ', FILTERSIGNAL', '')
         a7 = a6.replace( ', SIGNALTYPE', '')
         
     a8 = a7.replace( 'DUMMY_NAME', "'"+outname+"'" )
     a9 = a8.replace( 'DUMMY_SITE',"'"+'T3_US_FNALLPC'+"'")
     a10 = a9.replace( 'DUMMY_OUTPUT_PATH', "'"+'/store/group/lpcbprime/noreplica/skhalil/Histo/'+options.skimType+"'") 

     # Dump the contents of the crab config to the screen
     print '------ Config : ------- '
     print a10
     #create a directory if it doesn't exist
     c = 'mkdir '+options.skimType
     if not os.path.isdir(options.skimType):
         subprocess.call( [c], shell=True )
     # open the output file
     crabName = 'crab_' + outname + '.py'
     fout = open( options.skimType+'/'+crabName, 'w')
     # write the text to the output file
     fout.write( a10 )
     fout.close()
     print '------ CRAB starting up! ------'
     # now submit the job:
     s = 'crab submit -c ' + options.skimType+'/'+crabName
     print s
     # and submit:
     #subprocess.call( [s], shell=True )
    
