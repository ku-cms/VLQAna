#! /bin/python

def list_Zelel(isData):
    if isData:  
        jobList = [
            ['/DoubleEG/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4-ff3168b63d5cee365f49bf7ea3ba6ef3/USER', 'DoubleEG-Run2015D-05Oct2015-v1', '40', ''],
            ]
        return jobList
    else:
        jobList = [  
            ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/phys_b2g-B2GAnaFW_v74x_v6p1_25ns-V2-d5e3976e154b1b4043d031aaa9c2809b/USER ', 'DY_amcatnlo', '10',''],
            ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext3-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER ', '20', ''],
            ]
        return jobList

def list_Zmumu(isData):
    if isData:    
        jobList = [
            ['/DoubleMuon/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_24Nov2015-d89af00594c7943dd788edc55ad63843/USER', 'DoubleMuon-Run2015D-05Oct2015-v1', '20', ''],
            ['/DoubleMuon/devdatta-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_24Nov2015-d89af00594c7943dd788edc55ad63843/USER','DoubleMuon-Run2015D-PromptReco-v4', '20', ''], 
            ]
        return jobList
    else:
        jobList = [ 
            ['/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/skhalil-crab_DY_HT100to200_25ns_CR_Zmumu-30a01c6a40dfe28fc773f3b6cedc2f04/USER', 'DY_HT100to200', '1', ''],
            ]
        return jobList
