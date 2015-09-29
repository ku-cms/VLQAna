from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DoubleEG2015D-PromptReco-v3_Sep26_v74x_V7_25ns'
config.General.workArea = 'OS2LAna'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=True']

config.section_("Data")
config.Data.inputDataset = '/DoubleEG/devdatta-crab_DoubleEG_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns-8a6e833b8257c2f318a8d19495a1b105/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.ignoreLocality = True
config.Data.publication = False
config.Data.publishWithGroupName = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
