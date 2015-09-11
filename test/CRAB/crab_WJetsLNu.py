from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'WJetsToLNu_Run2Spring15_50ns'
config.General.workArea = 'OS2LAna'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=False']

config.section_("Data")
config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/oiorio-EDMNTUPLE_13Aug-784ba27ac81fc4a15005b27d31a374e9/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
