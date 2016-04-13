from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TT_powheg-pythia8_25ns_SR_Zmumu'
config.General.workArea = 'B2GEDMNtuplesSkim_SR_Zmumu_20Nov/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'skim_cfg.py' 
config.JobType.pyCfgParams = ['isData=False', 'skimType=SR_Zmumu']

config.section_("Data")
config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/decosa-TT_TuneCUETP8M1_13TeV-ff3168b63d5cee365f49bf7ea3ba6ef3/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.ignoreLocality = False
config.Data.publication = True
config.Data.outLFNDirBase = '/store/group/lpcbprime/noreplica/skhalil/B2GEDMNtuplesSkim_SR_Zmumu_20Nov/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'

config.section_('User')
