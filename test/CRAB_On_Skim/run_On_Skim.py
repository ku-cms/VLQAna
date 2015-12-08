#! /bin/python

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

parser.add_option('--isData', metavar='I', type='int', action='store',
                  default=0,
                  dest='isData',
                  help='run on data or MC')



(options, args) = parser.parse_args()

if options.isData == 1:
    isData  = 'isData=True'
else: 
    isData = 'isData=False'


jobList = [
     ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT100to200'],
     
     ]

for job in jobList:
     print '------------------------- prepare to run on :  ' + job[0] + ' ---------------------------'
     f = open(options.inputCfg, 'r')
     instring = f.read()
     
    # Get the dataset name, without the user-level stuff
     baseList = job[0].split('/')
     outname = baseList[1] + '_' + options.outLabel
     a0 = instring.replace( 'DUMMY_NAME', outname )
     a1 = a0.replace( 'POSTFIX', options.outLabel)
     a2 = a1.replace( 'DUMMY_DATASET', job[0] )
     a3 = a2.replace( 'DATA', isData)
     print a3
   
    #with open("crab_dummy_os2lana.py") as f:
    #    old = f.read() 
    #    old.replace('DUMMY_NAME', job[0])
    #    print old
#now write new one:
#with open("test.py", "w") as f:
#    f.write(file_str)




#result = src.substitute(d)

#print d

#import subprocess, os, ConfigParser


#dummy_config_name = 'crab_dummy_os2lana.py'

#dummy_config = ConfigParser.RawConfigParser()
#dummy_config.read(dummy_config_name)

#pset = 'os2lana_cfg.py'

# one pset for all jobs
#dummy_config.set('CMSSW','pset',pset)

#joblist = [
#     {DUMMY_NAME:'DY_HT100to200', DUMMY_DATASET:'/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER'}, 
#]

#for job in joblist:
#    config = dummy_config
