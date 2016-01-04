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
           [dir, '/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_DY_HT600toInf'+'_'+prefix],
           [dir, '/TT_TuneCUETP8M1_13TeV-powheg-pythia8', 'crab_TT-powheg-pythia8-ext3'+'_'+prefix], 
           [dir, '/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_incl_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-600to800_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-800to1200_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-1200to2500_madgraphMLM-pythia8'+'_'+prefix],     
           [dir, '/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_TTJets_HT-2500toInf_madgraphMLM-pythia8'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-100To200'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-200To400'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-400To600'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-600To800'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-800To1200'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-1200To2500'+'_'+prefix],
           [dir, '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'crab_WJetsToLNu_HT-2500ToInf'+'_'+prefix],
           [dir, '/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1', 'crab_ST_t_4f_top_powheg-pythia8'+'_'+prefix],
           [dir, '/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1','crab_ST_t_4f_antitop_powheg-pythia8'+'_'+prefix], 
           [dir, '/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1', 'crab_ST_t_4f_antitop_amcatnlo-pythia8'+'_'+prefix],
           [dir, '/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1', 'crab_ST_t_4f_antitop_amcatnlo-pythia8_ext1'+'_'+prefix],
          
           
           [dir, '/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1','crab_ST_s_4f_top_amcatnlo-pythia8'+'_'+prefix],
           [dir, '/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1', 'crab_ST_tW_5f_antitop_powheg-pythia8'+'_'+prefix],
           [dir, '/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1', 'crab_ST_tW_5f_top_powheg-pythia8'+'_'+prefix],
           
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
    name =  sample[2].replace('crab_','')
    if 'amcatnlo' in  sample[2]:
        if 'antitop' in  sample[2]: outname = name.replace('antitop_','') 
        elif 'top' in sample[2]: outname = name.replace('top_','')  
    else: outname = name
    #print task, ', ', outname
    rootPath = path+sample[0]+sample[1]+'/'+sample[2]+'/'+task+'/0000/*.root'
    subprocess.call( ['ls '+rootPath+' | wc -l'], shell=True )
    add = 'hadd '+outname+'_'+sample[0]+'.root   '+rootPath
    print add 
    subprocess.call( [add], shell=True )
    print '------------------------------------------------------------------->'
    
