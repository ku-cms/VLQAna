from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DY_HT200to400_25ns'
config.General.workArea = 'OS2LAna_29Oct2015/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=False', 'doPUReweightingOfficial=True']
config.JobType.inputFiles = ['hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root', 'PUDistData_Run2015ABCD.root', 'PUDistMC_2015_25ns_Startup_PoissonOOTPU.root']

config.section_("Data")
config.Data.inputDataset = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/vorobiev-B2GAnaFW_Run2Spring15_25ns_v74x_V61-d5e3976e154b1b4043d031aaa9c2809b/USER' 
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna_29Oct2015/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
