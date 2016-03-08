#!/usr/bin/env python
"""
This is a small script that submits a config over many datasets
"""
import os
from optparse import OptionParser

def getOptions() :
    """
    Parse and return the arguments provided by the user.
    """
    usage = ('usage: python submit_all.py -c CONFIG -d DIR ')

    parser = OptionParser(usage=usage)    
    #parser.add_option("-c", "--config", dest="config",
    #    help=("The crab script you want to submit "),
    #    metavar="CONFIG")
    #parser.add_option("-d", "--dir", dest="dir",
    #    help=("The crab directory you want to use "),
    #    metavar="DIR")
    parser.add_option("-f", "--datasets", dest="datasets",
        help=("File listing datasets to run over"),
        metavar="FILE")
    (options, args) = parser.parse_args()


    #if options.config == None or options.dir == None:
     #   parser.error(usage)
    
    return options
    

def main():

    options = getOptions()

    from WMCore.Configuration import Configuration
    config = Configuration()

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.section_("General")
    config.General.workArea = 'TpToTH_PreselTrees_01Mar2016'
    config.General.transferLogs = True

    config.section_("JobType")
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = 'vlqana_cfg.py' 
    config.JobType.pyCfgParams = ['isData=False','doPUReweightingOfficial=True','jecShift=0','jerShift=1', 'HTMin=800', 'storePreselEvts=True'] 
    #config.JobType.pyCfgParams = ['isData=True','doPUReweightingOfficial=False','jecShift=0','jerShift=0', 'HTMin=800', 'storePreselEvts=True'] 
    config.JobType.inputFiles = [
         'hnpv_data_Run2015D_mc_RunIISpring15DR74-Asympt25ns_pvwt.root'
        ,'PUDistData_Run2015ABCD.root'
        ,'PUDistMC_2015_25ns_Startup_PoissonOOTPU.root'
        ,'RunII2015_25ns_PUXsec65550nb.root'
        ,'RunII2015_25ns_PUXsec72450nb.root'
        ,'RunII2015_25ns_PUXsec69000nb.root'
        ,'Summer15_25nsV7_MC_L1FastJet_AK4PFchs.txt'
        ,'Summer15_25nsV7_MC_L2Relative_AK4PFchs.txt'
        ,'Summer15_25nsV7_MC_L3Absolute_AK4PFchs.txt'
        ,'Summer15_25nsV7_MC_Uncertainty_AK4PFchs.txt'
        ,'Summer15_25nsV7_MC_L1FastJet_AK8PFchs.txt'
        ,'Summer15_25nsV7_MC_L2Relative_AK8PFchs.txt'
        ,'Summer15_25nsV7_MC_L3Absolute_AK8PFchs.txt'
        ,'Summer15_25nsV7_MC_Uncertainty_AK8PFchs.txt'
        ,'Summer15_25nsV7_DATA_L1FastJet_AK8PFchs.txt' 
        ,'Summer15_25nsV7_DATA_L1RC_AK8PFchs.txt' 
        ,'Summer15_25nsV7_DATA_L2L3Residual_AK4PFchs.txt' 
        ,'Summer15_25nsV7_DATA_L2L3Residual_AK8PFchs.txt' 
        ,'Summer15_25nsV7_DATA_L2Relative_AK8PFchs.txt' 
        ,'Summer15_25nsV7_DATA_L3Absolute_AK8PFchs.txt' 
        ,'Summer15_25nsV7_DATA_Uncertainty_AK4PFchs.txt' 
        ,'Summer15_25nsV7_DATA_Uncertainty_AK8PFchs.txt' 
        ,'btag-eff-subjet.root'
        ]
    config.JobType.maxJobRuntimeMin = 2000
    config.JobType.maxMemoryMB = 2500

    config.section_("Data")
    config.Data.inputDataset = None
    config.Data.inputDBS = 'phys03'
    #config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON.txt'
    config.Data.splitting = 'FileBased'
    #config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 2
    config.Data.ignoreLocality = False
    config.Data.publication = False     
    config.Data.outLFNDirBase = '/store/group/phys_b2g/devdatta/TpToTH_PreselTrees_01Mar2016/'
    
    config.section_("Site")
    config.Site.storageSite = 'T2_CH_CERN'

    #print 'Using config ' + options.config
    #print 'Writing to directory ' + options.dir
    
    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print 'Cannot execute commend'
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    datasetsFile = open( options.datasets )
    jobsLines = datasetsFile.readlines()
    jobs = []
    for ijob in jobsLines :
        s = ijob.rstrip()
        if (len(s)==0 or s[0][0]=='#'): continue
        jobs.append( s )
        print '  --> added ' + s
        
    for ijob, job in enumerate(jobs) :

        print "-->  ", job
        pd = job.split('/')[1]
        processing = (job.split('/')[2]).split('-')[0] + (job.split('/')[2]).split('-')[1] + (job.split('/')[2]).split('-')[2] + (job.split('/')[2]).split('-')[3] #for data
        if (len(pd + '_' + processing)<=100): 
          config.General.requestName = pd + '_' + processing
        else:
          config.General.requestName = pd 
        config.Data.inputDataset = job
        print 'Submitting ' + config.General.requestName + ', dataset = ' + job
        print 'Configuration :'
        #print config
        try :
            from multiprocessing import Process
            p = Process(target=submit, args=(config,))
            p.start()
            p.join()
            #submit(config)
        except :
            print 'Not submitted.'
        
if __name__ == '__main__':
    main()            
