#!/bin/python

import subprocess
import os

def getTask(crab):
    with open(crabPath+crab+"/crab.log") as f:
        for line in f:
            if "Task name:" in line:
                return line.split(':')[4].strip()

prefix = 'os2lana_v2'
path = '/store/user/lpcbprime/noreplica/skhalil/Histo_B2GEDM/'
crabPath = '/uscms_data/d2/skhalil/MyVLQAna2/CMSSW_7_4_15_patch1/src/Analysis/VLQAna/test/CRAB_On_B2GEDM/'+prefix+'/'
dir = 'Zmumu'

samples = [ 
           [dir, '/DoubleMuon', 'crab_DoubleMuon-Run2015D-05Oct2015-v1_os2lana_v2'],
           #[dir,'/DoubleEG', 'crab_DoubleEG-Run2015D-05Oct2015-v1_os2lana_v1'],
           [dir,'/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8', 'crab_DY_amcatnlo_os2lana_v2'],
           [dir,'/TT_TuneCUETP8M1_13TeV-powheg-pythia8','crab_TT-powheg-pythia8-ext3_os2lana_v2'],          
        ]
               
#add them
for sample in samples :
    task = getTask(sample[2])
    name =  sample[2].replace('crab_','')
    #outname = ''
    if 'amcatnlo' in  sample[2]:
        if 'antitop' in  sample[2]: outname = name.replace('antitop_','') 
        elif 'top' in sample[2]: outname = name.replace('top_','') 
        else: outname = name 
    else: outname = name
    print task, ', ', outname
    rootPath = path+sample[0]+sample[1]+'/'+sample[2]+'/'+task+'/0000/'
    subprocess.call( ['xrdfsls -u '+rootPath+' | grep ".root" | wc -l'], shell=True, executable='/bin/tcsh')
    add = 'hadd '+outname+'_'+sample[0]+'.root   `xrdfsls -u '+rootPath+'| grep ".root"`'
    subprocess.call( [add], shell=True, executable='/bin/tcsh')
    print '------------------------------------------------------------------->'
    
