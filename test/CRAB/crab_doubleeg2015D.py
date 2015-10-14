from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = ''
config.General.workArea = 'OS2LAna_14Oct2015/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=True', 'zdecaymode=zelel']

config.section_("Data")
config.Data.inputDataset = ''
config.Data.inputDBS = 'phys03'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Cert_246908-258159_13TeV_PromptReco_Collisions15_25ns_JSON_v3.txt'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.ignoreLocality = True
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna_14Oct2015/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
