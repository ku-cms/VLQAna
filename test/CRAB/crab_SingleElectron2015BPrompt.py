from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SingleElectronPrompt_50ns'
config.General.workArea = 'OS2LAna'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=True']

config.section_("Data")
config.Data.inputDataset = '/SingleElectron/decosa-SingleElectron_Run2015B-PromptReco-v1_13Aug15-cbce20f52720ded6b8666f172a87a311/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
