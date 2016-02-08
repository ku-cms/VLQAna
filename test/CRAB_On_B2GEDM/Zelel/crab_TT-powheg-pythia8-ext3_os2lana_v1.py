from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")

config.General.requestName = 'TT-powheg-pythia8-ext3_os2lana_v1'
config.General.workArea = 'os2lana_v1'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'os2lana_cfg.py'
config.JobType.pyCfgParams = ['isData=False', 'zdecaymode=zelel', 'doPUReweightingOfficial=True', 'applyLeptonSFs=True']
config.JobType.inputFiles = ['Summer15_25nsV6_MC_L2L3Residual_AK8PFchs.txt', 'Summer15_25nsV6_MC_L3Absolute_AK8PFchs.txt', 'hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root', 'PUDistData_Run2015ABCD.root', 'PUDistMC_2015_25ns_Startup_PoissonOOTPU.root']

config.section_("Data")
config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/jkarancs-B2GAnaFW_v74x_V8p4_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext3-v1-7b09a84a5c42d0a63b01d8e8e63c7a89/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/group/lpcbprime/noreplica/skhalil/Histo_B2GEDM/Zelel'

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
config.section_('User')

