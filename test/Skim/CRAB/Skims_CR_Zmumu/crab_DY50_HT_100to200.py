from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DY_HT100to200_25ns'
config.General.workArea = 'B2GEDMNtuplesSkim_CR_Zmumu_20Nov'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'skim_cfg.py' 
config.JobType.pyCfgParams = ['isData=False', 'skimType=CR_Zmumu']

config.section_("Data")
config.Data.inputDataset = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER'
config.Data.inputDBS = 'phys03'
config.Data.allowNonValidInputDataset = True
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.ignoreLocality = False
config.Data.publication = True
config.Data.outLFNDirBase = '/store/user/devdatta/B2GEDMNtuplesSkim_CR_Zmumu_20Nov/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
