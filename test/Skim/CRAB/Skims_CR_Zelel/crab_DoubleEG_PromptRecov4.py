from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DoubleEG_PromptRecov4'
config.General.workArea = 'B2GEDMNtuplesSkim_CR_Zelel_24Nov/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'skim_cfg.py' 
config.JobType.pyCfgParams = ['isData=True', 'skimType=CR_Zelel']

config.section_("Data")
config.Data.inputDataset = '/DoubleEG/devdatta-Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4-5daaa7fbf157b0642c1d3dfb260fbeff/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.ignoreLocality = False
config.Data.publication = True
config.Data.outLFNDirBase = '/store/group/phys_b2g/B2GAnaFW/Skims/CR_Zelel/'
config.Data.outputDatasetTag = 'Run2015D-PromptReco-v4_B2GAnaFW_v74x_v8p4_Skim_CR_Zelel_24Nov2015'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
