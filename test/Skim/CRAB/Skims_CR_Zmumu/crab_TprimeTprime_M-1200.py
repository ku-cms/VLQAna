from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TprimeTprime_M-1200_25ns'
config.General.workArea = 'B2GEDMNtuplesSkim_CR_Zmumu_20Nov'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'skim_cfg.py' 
config.JobType.pyCfgParams = ['isData=False', 'skimType=CR_Zmumu']

config.section_("Data")
config.Data.inputDataset = '/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_Run2Spring15MiniAODv2_25ns_v74x_v84-dde4a6f9141ed18b3aaa23431003cf13/USER'
config.Data.inputDBS = 'phys03'
config.Data.allowNonValidInputDataset = True
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.ignoreLocality = False
config.Data.publication = True
config.Data.outLFNDirBase = '/store/group/lpcbprime/noreplica/skhalil/B2GEDMNtuplesSkim_CR_Zmumu_20Nov/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'

config.section_('User')
