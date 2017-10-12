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
    config.General.workArea = '80X_trees_3p2_topWp'
    config.General.transferLogs = True

    config.section_("JobType")
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = 'vlqana_cfg.py' 
    config.JobType.pyCfgParams = ['btageffmap=btagEff_TTJets_loose.root','applyBTagSFs=True','cleanEvents=True','isData=False','doPUReweightingOfficial=True','jecShift=0','jerShift=1', 'HTMin=0', 'storePreselEvts=True', 'storeLHEWts=False'] 
    #config.JobType.pyCfgParams = ['btageffmap=btagEff_TttH_2600_Width-10p_loose.root','applyBTagSFs=True','cleanEvents=True','isData=False','doPUReweightingOfficial=True','jecShift=0','jerShift=1', 'HTMin=0', 'storePreselEvts=True', 'storeLHEWts=False'] 
    #config.JobType.pyCfgParams = ['cleanEvents=True','isData=True','doPUReweightingOfficial=False','jecShift=0','jerShift=0', 'HTMin=0', 'storePreselEvts=True'] 
    config.JobType.inputFiles = [
        '../data/PUDistMC_Summer2016_25ns_Moriond17MC_PoissonOOTPU.root'
        ,'../data/RunII2016Rereco_25ns_PUXsec69000nb.root'
        ,'../data/RunII2016Rereco_25ns_PUXsec65550nb.root'
        ,'../data/RunII2016Rereco_25ns_PUXsec72450nb.root'
        ,'../data/RunII2016Rereco_25ns_RunsBtoG_PUXsec69000nb.root'
        ,'../data/RunII2016Rereco_25ns_RunH_PUXsec69000nb.root'
        ,'../data/Summer16_23Sep2016V4_MC_L2Relative_AK8PFPuppi.txt'
        ,'../data/Summer16_23Sep2016V4_MC_L3Absolute_AK8PFPuppi.txt'
        ,'../data/Summer16_23Sep2016V4_MC_Uncertainty_AK4PFchs.txt'
        ,'../data/Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt'
        ,'../data/Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt'
        ,'../data/Summer16_23Sep2016V4_MC_Uncertainty_AK8PFchs.txt'
        ,'../data/Summer16_23Sep2016V4_MC_Uncertainty_AK8PFPuppi.txt'
        #,'../data/Summer16_23Sep2016V4_DATA_L2L3Residual_AK4PFchs.txt' 
        #,'../data/Summer16_23Sep2016V4_DATA_L2L3Residual_AK8PFchs.txt' 
        #,'../data/Summer16_23Sep2016V4_DATA_L2Relative_AK8PFchs.txt' 
        #,'../data/Summer16_23Sep2016V4_DATA_L3Absolute_AK8PFchs.txt' 
        #,'../data/Summer16_23Sep2016V4_DATA_Uncertainty_AK4PFchs.txt' 
        #,'../data/Summer16_23Sep2016V4_DATA_Uncertainty_AK8PFchs.txt' 
        ,'../data/btagEff_TTJets_loose.root'
        ,'../data/btagEff_TtH_800_loose.root'
        ,'../data/btagEff_TtH_900_loose.root'
        ,'../data/btagEff_TtH_1000_loose.root'
        ,'../data/btagEff_TtH_1100_loose.root'
        ,'../data/btagEff_TtH_1200_loose.root'
        ,'../data/btagEff_TtH_1300_loose.root'
        ,'../data/btagEff_TtH_1400_loose.root'
        ,'../data/btagEff_TtH_1500_loose.root'
        ,'../data/btagEff_TtH_1700_loose.root'
        ,'../data/btagEff_TtH_1800_loose.root'
        ,'../data/btagEff_TbtH_2600_Width-10p_loose.root'
        ,'../data/btagEff_TttH_2600_Width-10p_loose.root'
        ,'../data/btagEff_loose_QCDHT300.root'
        ,'../data/btagEff_loose_QCDHT500.root'
        ,'../data/btagEff_loose_QCDHT700.root'
        ,'../data/btagEff_loose_QCDHT1000.root'
        ,'../data/btagEff_loose_QCDHT1500.root'
        ,'../data/btagEff_loose_QCDHT2000.root'
        ,'../data/btagEff_loose_QCDPT170.root'
        ,'../data/btagEff_loose_QCDPT300.root'
        ,'../data/btagEff_loose_QCDPT470.root'
        ,'../data/btagEff_loose_QCDPT600.root'
        ,'../data/btagEff_loose_QCDPT800.root'
        ,'../data/btagEff_loose_QCDPT1000.root'
        ,'../data/btagEff_loose_QCDPT1400.root'
        ,'../data/btagEff_loose_QCDPT1800.root'
        ,'../data/btagEff_loose_QCDPT2400.root'
        ,'../data/btagEff_loose_QCDPT3200.root'
        ,'../data/subjet_CSVv2_Moriond17_B_H.csv'
        ]
    config.JobType.maxJobRuntimeMin = 2000
    config.JobType.maxMemoryMB = 2500

    config.section_("Data")
    config.Data.inputDataset = None
    config.Data.inputDBS = 'phys03'
    #config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON.txt'
    config.Data.splitting = 'FileBased'
    #config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 1
    config.Data.ignoreLocality = False
    config.Data.publication = False     
    config.Data.outLFNDirBase = '/store/user/eschmitz/B2G/80X_VLQAna_B2G3p2_topWp'
    
    config.section_("Site")
    config.Site.storageSite = 'T2_US_Nebraska'

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
        pd = job.split('/')[1] + job.split('/')[2].split('-')[0]
        processing = (job.split('/')[2]).split('-')[0] + (job.split('/')[2]).split('-')[1] + (job.split('/')[2]).split('-')[2] + (job.split('/')[2]).split('-')[0] #for data
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
