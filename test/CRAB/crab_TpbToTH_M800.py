from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TprimeBToTH_M800_LH_Run2Spring15_25ns'
config.General.workArea = 'SingleTpToTH_06oct2015'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'vlqana_cfg.py' 
config.JobType.pyCfgParams = ['isData=False']

config.section_("Data")
config.Data.inputDataset = '/TprimeBToTH_M-800_LH_TuneCUETP8M1_13TeV-madgraph-pythia8/phys_b2g-B2GAnaFW_v74x_v6p1_25ns-d5e3976e154b1b4043d031aaa9c2809b/USER' 
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/SingleTpToTH_06oct2015/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
