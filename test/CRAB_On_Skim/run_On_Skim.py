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
                  default='CR_Zelel',
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
elif 'Zelel' in options.skimType:
    mode = 'zdecaymode=zelel'
else: 
    mode = 'zdecaymode= '

jobList = [
     ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT100to200'],
     
     ]

for job in jobList:
     print '------prepare to run on :  ' + job[0] + ' -----------'
     f = open(options.inputCfg, 'r')
     instring = f.read()
     
     baseList = job[0].split('/')
     if 'Tprime' in baseList[0] or 'Bprime' in baseList[0]: 
         filterSignal = 'filterSignal=True'
     else: filterSignal = 'filterSignal=False'

     outname = job[1] + '_' + options.outLabel
     a0 = instring.replace( 'DUMMY_NAME', "'"+outname+"'" )
     a1 = a0.replace( 'DUMMY_WORKDIR', "'"+options.outLabel+"'")
     a2 = a1.replace( 'DUMMY_DATASET', "'"+job[0]+"'" )
     a3 = a2.replace( 'DATA', "'"+isData+"'") 
     a4 = a3.replace( 'MODE', "'"+mode+"'")
     a5 = a4.replace( 'PUOFF', "'"+puOfficial+"'")
     a6 = a5.replace( 'FILTERSIGNAL', "'"+filterSignal+"'")
     a7 = a6.replace( 'DUMMY_SITE',"'"+'T3_US_FNALLPC'+"'")
     a8 = a7.replace( 'DUMMY_OUTPUT_PATH', "'"+'/store/group/lpcbprime/noreplica/skhalil/Histo/'+options.skimType+"'") 

     # Dump the contents of the crab config to the screen
     print '------ Config : ------- '
     print a8
     #create a directory if it doesn't exist
     c = 'mkdir '+options.skimType
     if not os.path.isdir(options.skimType):
         subprocess.call( [c], shell=True )
     # open the output file
     crabName = 'crab_' + outname + '.py'
     fout = open( options.skimType+'/'+crabName, 'w')
    # write the text to the output file
     fout.write( a8 )
     fout.close()
     print '------ CRAB starting up! ------'
    # now submit the job:
     s = 'crab submit -c ' + options.skimType+'/'+crabName
     print s
    # and submit:
    # subprocess.call( [s], shell=True )
    
