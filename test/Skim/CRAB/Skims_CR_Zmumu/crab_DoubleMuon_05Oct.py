from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DoubleMuon_05Oct_CR_Zmumu'
config.General.workArea = 'B2GEDMNtuplesSkim_CR_Zmumu_20Nov/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'skim_cfg.py' 
config.JobType.pyCfgParams = ['isData=True', 'skimType=CR_Zmumu']

config.section_("Data")
config.Data.inputDataset = '/DoubleMuon/devdatta-Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4-ff3168b63d5cee365f49bf7ea3ba6ef3/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.ignoreLocality = False
config.Data.publication = True
config.Data.outLFNDirBase = '/store/group/lpcbprime/noreplica/skhalil/B2GEDMNtuplesSkim_CR_Zmumu_20Nov/'
config.Data.outputDatasetTag = 'Run2015D-05Oct2015-v1_B2GAnaFW_v74x_v8p4_Skim_CR_Zmumu_04Feb2016'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'

config.section_('User')
