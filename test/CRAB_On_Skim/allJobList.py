#! /bin/python

def list_CR_Zelel(isData):
    if isData:  
        jobList = [
            ['/DoubleEG/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zelel_24Nov2015-8754596839785bfa0cdf7f8d9e23f006/USER', 'DoubleEG-Run2015D-05Oct2015-v1', '20', ''],
            ['/DoubleEG/devdatta-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4_Skim_CR_Zelel_24Nov2015-8754596839785bfa0cdf7f8d9e23f006/USER', 'DoubleEG-Run2015D-PromptReco-v4', '40', ''],
            ]
        return jobList
    else:
        jobList = [  
            ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/skhalil-crab_DYamcnlo_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_amcatnlo', '5',''],
            ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT100to200', '1',''],
            ['/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT200to400_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT200to400', '1', ''], 
            ['/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT400to600_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT400to600', '1', ''], 
            ['/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT600toInf_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'DY_HT600toInf', '1', ''],
            ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/skhalil-crab_TT_powheg-pythia8_ext3_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TT-powheg-pythia8-ext3', '10', ''],
            ['/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_MG_pythia8_asymptotic_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_incl_madgraphMLM-pythia8', '10', ''], 
            ['/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-600to800_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-600to800_madgraphMLM-pythia8', '1', ''], 
            ['/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-800to1200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-800to1200_madgraphMLM-pythia8', '1', ''],
            ['/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-1200to2500_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-1200to2500_madgraphMLM-pythia8', '1', ''],
            ['/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_TTJets_HT-2500toInf_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TTJets_HT-2500toInf_madgraphMLM-pythia8', '1', ''],
            ['/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_100to200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-100To200', '1',''],
            ['/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_200to400_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-200To400', '1', ''],
            ['/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_400to600_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-400To600', '1', ''],
            ['/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_600to800_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-600To800', '1', ''],
            ['/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_800to1200_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-800To1200', '1', ''],
            ['/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_1200to2500_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-1200To2500', '1', ''],
            ['/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_WJets_HT_2500toInf_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WJetsToLNu_HT-2500ToInf', '1', ''],
            ['/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/skhalil-crab_ST_t-channel_powheg-pythia8_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ST_t_4f_top_powheg-pythia8', '1', ''],
            ['/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/skhalil-crab_ST_t-channel_antitop_powheg-pythia8_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ST_t_4f_antitop_powheg-pythia8', '1', ''],
            ['/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/skhalil-crab_ST_t-channel_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER','ST_t_4f_antitop_amcatnlo-pythia8', '1', ''],
            ['/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/skhalil-crab_ST_t-channel_ext1_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ST_t_4f_antitop_amcatnlo-pythia8_ext1', '1', ''],
            ['/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/skhalil-crab_ST_s-channel_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ST_s_4f_top_amcatnlo-pythia8', '1', ''],  
            ['/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/skhalil-crab_ST_tW-channel_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ST_tW_5f_top_powheg-pythia8', '1', ''],
            ['/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/skhalil-crab_ST_tW_antitop_channel_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ST_tW_5f_antitop_powheg-pythia8', '1', ''], 
            ['/WWTo2L2Nu_13TeV-powheg/skhalil-crab_WWTo2L2Nu_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WWTo2L2Nu_powheg', '1', ''],
            ['/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/skhalil-crab_WZTo2L2Q_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'WZTo2L2Q_amcatnlo', '1', ''],    
            ['/ZZTo2L2Nu_13TeV_powheg_pythia8/skhalil-crab_ZZTo2L2Nu_25ns_CR_Zelel-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'ZZTo2L2Nu_powheg_pythia8', '1', ''],
            ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-800_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-800', '1', 'EvtType_MC_tZtZ'],
            ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-800_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-800', '1', 'EvtType_MC_tZtH'],
            ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-800_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-800', '1', 'EvtType_MC_tZbW'],       
            ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-900_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-900', '1', 'EvtType_MC_tZtZ'],
            ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-900_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-900', '1', 'EvtType_MC_tZtH'],
            ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-900_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-900', '1', 'EvtType_MC_tZbW'],
            ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1000_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-1000', '1', 'EvtType_MC_tZtZ'],
            ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1000_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-1000', '1', 'EvtType_MC_tZtH'],
            ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1000_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-1000', '1', 'EvtType_MC_tZbW'],
            ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1200_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-1200', '1', 'EvtType_MC_tZtZ'],
            ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1200_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-1200', '1', 'EvtType_MC_tZtH'],
            ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1200_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-1200', '1', 'EvtType_MC_tZbW'],
            ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1500_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtZ_M-1500', '1', 'EvtType_MC_tZtZ'],
            ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1500_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZtH_M-1500', '1', 'EvtType_MC_tZtH'],
            ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/skhalil-crab_TprimeTprime_M-1500_25ns-7ad39afaa9141e6c9414a79f4df4bdce/USER', 'TpTp_tZbW_M-1500', '1', 'EvtType_MC_tZbW'], 

            ]
        return jobList

def list_CR_Zmumu(isData):
    if isData:    
        jobList = [
            ['/DoubleMuon/skhalil-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_04Feb2016-d89af00594c7943dd788edc55ad63843/USER', 'DoubleMuon-Run2015D-05Oct2015-v1','20', ''],
            ['/DoubleMuon/skhalil-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_04Feb2016-d89af00594c7943dd788edc55ad63843/USER', 'DoubleMuon-Run2015D-PromptReco-v4', '20', ''], 
            ]
        return jobList
    else:
        jobList = [ 
            ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/skhalil-crab_DYamcnlo_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_amcatnlo', '5',''], 
            ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT100to200', '1', ''],
            ['/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT200to400_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT200to400', '1', ''],
            ['/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT400to600_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT400to600', '1', ''],
            ['/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT600toInf_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT600toInf', '1', ''],
            ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/skhalil-crab_TT_powheg-pythia8_ext3_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'TT-powheg-pythia8-ext3', '10', ''],
            ]
        return jobList
