#! /bin/python

def list_CR_Zelel(isData):
    if isData:  
        jobList =[
            ['/DoubleEG/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zelel_24Nov2015-8754596839785bfa0cdf7f8d9e23f006/USER', 'DoubleEG-Run2015D-05Oct2015-v1', ''],
            ['/DoubleEG/devdatta-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4_Skim_CR_Zelel_24Nov2015-8754596839785bfa0cdf7f8d9e23f006/USER', 'DoubleEG-Run2015D-PromptReco-v4', ''],
            ]
        return jobList
    else:
        jobList[  
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
        return jobList

def list_CR_Zmumu(isData):
    if isData:    
        jobList = [
            ['/DoubleMuon/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_24Nov2015-d89af00594c7943dd788edc55ad63843/USER', 'DoubleMuon-Run2015D-05Oct2015-v1', ''],
            ['/DoubleMuon/devdatta-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_24Nov2015-d89af00594c7943dd788edc55ad63843/USER',
'DoubleMuon-Run2015D-PromptReco-v4', ''], 
            ]
        return jobList
    else:
        jobList = [ 
            ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT100to200', ''],
            ]
        return jobList
