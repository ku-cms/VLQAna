#! /bin/python

def list_Zelel(isData):
    if isData:  
        jobList = [
            ['/DoubleEG/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4-ff3168b63d5cee365f49bf7ea3ba6ef3/USER', 'DoubleEG-Run2015D-05Oct2015-v1', '40', ''],
            ]
        return jobList
    else:
        jobList = [  
            ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_Run2Spring15MiniAODv2_25ns_v74x_v84-50153fb607659b6f9fb41d9f35391d0e/USER', 'DY_amcatnlo', '10',''],
            #['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext3-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER', 'TT_powheg', '20', ''],
            ]
        return jobList

def list_Zmumu(isData):
    if isData:    
        jobList = [
            ['/DoubleMuon/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4-ff3168b63d5cee365f49bf7ea3ba6ef3/USER', 'DoubleMuon-Run2015D-05Oct2015-v1', '20', ''],
            ['/DoubleMuon/devdatta-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4-5daaa7fbf157b0642c1d3dfb260fbeff/USER', 'DoubleMuon-Run2015D-PromptReco-v4', '20', ''], 
            ]
        return jobList
    else:
        jobList = [ 
            ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_Run2Spring15MiniAODv2_25ns_v74x_v84-50153fb607659b6f9fb41d9f35391d0e/USER', 'DY_amcatnlo', '5',''], 
            #['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER', 'DY_HT100to200', '5', ''],
            #['/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER', 'DY_HT200to400', '5', ''],
            #['/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2-7b09a84a5c42d0a63b01d8e8e63c7a89/USER', 'DY_HT400to600', '5', ''],
            #['/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER', 'DY_HT600toInf', '5', ''],
            ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext3-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER', 'TT-powheg-pythia8-ext3', '10', ''],
            ]
        return jobList
