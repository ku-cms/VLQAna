from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TTjets_25ns'
config.General.workArea = 'OS2LAna_16Nov2015_v2/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=False', 'doPUReweightingNPV=True']
config.JobType.inputFiles = ['Summer15_25nsV6_MC_L2L3Residual_AK8PFchs.txt', 'Summer15_25nsV6_MC_L3Absolute_AK8PFchs.txt', 'hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root', 'PUDistData_Run2015ABCD.root', 'PUDistMC_2015_25ns_Startup_PoissonOOTPU.root']

config.section_("Data")
config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v3-7b09a84a5c42d0a63b01d8e8e63c7a89/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna_16Nov2015_v2/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
