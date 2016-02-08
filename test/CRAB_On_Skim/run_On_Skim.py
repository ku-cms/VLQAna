#! /bin/python
import os
from string import *
import subprocess
import glob
#from __future__ import 
from allJobList import *
from optparse import OptionParser


parser = OptionParser()

parser.add_option('--inputCfg', metavar='C', type='string', action='store',
                  default='crab_dummy_os2lana.py',
                  dest='inputCfg',
                  help='input config tag to be used')

parser.add_option('--outLabel', metavar='L', type='string', action='store',
                  default='os2lana_v2',
                  dest='outLabel',
                  help='output tag to be used')

parser.add_option('--skimType', metavar='S', type='string', action='store',
                  default='CR_Zmumu',
                  dest='skimType',
                  help='Skim type: CR_Zelel, CR_Zmumu, SR_Zelel, SR_Zmumu')
    
parser.add_option('--isData', metavar='I', type='int', action='store',
                  default=1,
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
    if options.isData == 0: applySF = 'applyLeptonSFs=True'
    else: applySF = 'applyLeptonSFs=False'

# add all the datasets for particular skim
if options.skimType=='CR_Zelel':
    print 'Submitting jobs for electron channel in control region -------->'
    jobList = list_CR_Zelel(options.isData)

if options.skimType=='CR_Zmumu':
    print 'Submitting jobs for muon channel in control region -------->'
    jobList = list_CR_Zmumu(options.isData)
 
for job in jobList:
     print '------prepare to run on :  ' + job[0] + ' -----------'
     f = open(options.inputCfg, 'r')
     instring = f.read()
     baseList = job[0].split('/')
     #print baseList
     outname = job[1] + '_' + options.outLabel

     a0 = instring.replace( 'DUMMY_WORKDIR', "'"+options.outLabel+"'")
     a1 = a0.replace( 'DUMMY_DATASET', "'"+job[0]+"'" )
     a2 = a1.replace( 'DATA', "'"+isData+"'") 
     a3 = a2.replace( 'MODE', "'"+mode+"'")
     a4 = a3.replace( 'LEPSF', "'"+applySF+"'")
     a5 = a4.replace( 'PUOFF', "'"+puOfficial+"'") 
     a6 = a5.replace( 'DUMMY_NUMBER',  job[2])  
     if 'Tprime' in baseList[1] or 'Bprime' in baseList[1]:     
         a7 = a6.replace( 'FILTERSIGNAL', "'filterSignal=True'")
         a8 = a7.replace('SIGNALTYPE', "'signalType="+job[3]+"'")  
     else:
         a7 = a6.replace( ', FILTERSIGNAL', '')
         a8 = a7.replace( ', SIGNALTYPE', '')         
     a9 = a8.replace( 'DUMMY_NAME', "'"+outname+"'" )
     a10 = a9.replace( 'DUMMY_SITE',"'"+'T3_US_FNALLPC'+"'")
     a11 = a10.replace( 'DUMMY_OUTPUT_PATH', "'"+'/store/group/lpcbprime/noreplica/skhalil/Histo/'+options.skimType+"'") 
     if options.isData:
         a12 = a11.replace('DUMMY_BASE', "'LumiBased'")
     else: 
         a12 = a11.replace('DUMMY_BASE', "'FileBased'")    
     # Dump the contents of the crab config to the screen
     print '------ Config : ------- '
     print a12
     #create a directory if it doesn't exist
     c = 'mkdir '+options.skimType
     if not os.path.isdir(options.skimType):
         subprocess.call( [c], shell=True )
     # open the output file
     crabName = 'crab_' + outname + '.py'
     fout = open( options.skimType+'/'+crabName, 'w')
     # write the text to the output file
     fout.write( a12 )
     fout.close()
     print '------ CRAB starting up! ------'
     # now submit the job:
     s = 'crab submit -c ' + options.skimType+'/'+crabName
     print s
     # and submit:
     subprocess.call( [s], shell=True )
    
