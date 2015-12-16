#!/bin/python

import subprocess
import os

def getTask(crab):
    with open(crabPath+crab+"/crab.log") as f:
        for line in f:
            if "Task name:" in line:
                return line.split(':')[4].strip()

prefix = 'os2lana_v1'
path = '/eos/uscms/store/user/lpcbprime/noreplica/skhalil/Histo/'
crabPath = '/uscms_data/d2/skhalil/MyVLQAna2/CMSSW_7_4_15_patch1/src/Analysis/VLQAna/test/CRAB_On_Skim/'+prefix+'/'
dir = 'CR_Zelel'

samples = [[dir, '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_DY_HT100to200'+'_'+prefix],
           [dir, '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_DY_HT200to400'+'_'+prefix], 
           [dir, '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_DY_HT400to600'+'_'+prefix], 
           [dir, '/TT_TuneCUETP8M1_13TeV-powheg-pythia8', 'crab_TT-powheg-pythia8-ext3'+'_'+prefix], 
           [dir, '/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_incl_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-600to800_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-800to1200_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-1200to2500_madgraphMLM-pythia8'+'_'+prefix],    
           [dir, '/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-2500toInf_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZbW_M-800'+'_'+prefix],
           [dir, '/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtH_M-800'+'_'+prefix],
           [dir, '/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtZ_M-800'+'_'+prefix],
           [dir, '/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZbW_M-900'+'_'+prefix],
           [dir, '/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtH_M-900'+'_'+prefix],
           [dir, '/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtZ_M-900'+'_'+prefix],           
           [dir, '/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZbW_M-1000'+'_'+prefix],
           [dir, '/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtH_M-1000'+'_'+prefix],
           [dir, '/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtZ_M-1000'+'_'+prefix],           
           [dir, '/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZbW_M-1200'+'_'+prefix],
           [dir, '/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtH_M-1200'+'_'+prefix],
           [dir, '/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8', 'crab_TpTp_tZtZ_M-1200'+'_'+prefix],
        ]
               
#add them
for sample in samples :
    task = getTask(sample[2])
    outname =  sample[2].replace('crab_','') 
    #print task, ', ', outname
    rootPath = path+sample[0]+sample[1]+'/'+sample[2]+'/'+task+'/0000/*.root'
    subprocess.call( ['ls '+rootPath+' | wc -l'], shell=True )
    add = 'hadd '+outname+'_'+sample[0]+'.root   '+rootPath
    print add 
    subprocess.call( [add], shell=True )
    print '------------------------------------------------------------------->'
    
