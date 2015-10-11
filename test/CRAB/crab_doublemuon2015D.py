from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DoubleMuon2015D-PromptReco-v3_Sep26_v74x_V7_25ns'
config.General.workArea = 'OS2LAna_13oct2015/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=True', 'zdecaymode=zmumu']

config.section_("Data")
config.Data.inputDataset = '/DoubleMuon/devdatta-crab_Run2015D-PromptReco-v3_Sep26_v74x_V7_25ns-8a6e833b8257c2f318a8d19495a1b105/USER'
config.Data.inputDBS = 'phys03'
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-257599_13TeV_PromptReco_Collisions15_25ns_JSON.txt'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.ignoreLocality = True
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna_13oct2015/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
