from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TTjets_25ns'
config.General.workArea = 'OS2LAna_13oct2015/'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py' 
config.JobType.pyCfgParams = ['isData=False', 'doPUReweightingNPV=True']
config.JobType.inputFiles = ['hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root']

config.section_("Data")
config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_Run2Spring15_25ns_v74x_V6_1-6cd0525a22c1e7f79f9247caf4357294/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/devdatta/OS2LAna_13oct2015/'
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

config.section_('User')
