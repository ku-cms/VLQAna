setenv SCRAM_ARCH slc6_amd64_gcc530

cmsrel CMSSW_8_0_20

cd CMSSW_8_0_20/src

git cms-init 

git cms-merge-topic dmajumder:CMSSW_8_0_X_AnalysisDataFormats_BoostedObjects

git clone git@github.com:dmajumder/EventCounter.git Analysis/EventCounter

git clone -b CMSSW_8_0_X_NewB2GAnaFW git@github.com:dmajumder/VLQAna.git Analysis/VLQAna
 
#To just build this stuff
scram b -j20

# To run on OS2L analysis
cd Analysis/VLQAna/test

cmsRun vlqAna_cfg.py 

#To generate VLQ trees after pre-selection

cmsRun vlqAna_cfg.py storePreselEvts=True 

To process lots of CRAB jobs producing the above trees:

python tpthPreselTrees_submit_all.py -f CRAB/tpth_tosubmit.txt 

Make sure to uncomment the dataset names in the file 'CRAB/tpth_tosubmit.txt ' you want to process.

Be mindful of the switches for  processing data and MC.

To process data, change in tpthPreselTrees_submit_all.py  line 52:

config.JobType.pyCfgParams = ['isData=True','doPUReweightingOfficial=False','jecShift=0','jerShift=0', 'doBTagSFUnc=False']

# To run crab jobs for skims, e.g for CR in dielectron channel

Analysis/VLQAna/test/Skim/CRAB/Skims_CR_Zelel 

Modify the exisiting crab file, by changing the relvant parameters, like config.General.requestName, config.Data.inputDataset, config.Data.outLFNDirBase, config.Site.storageSite etc.

crab submit -c crab_XX.py

This will create an output condor directory, through which you can check the status of the jobs.

crab status -d MY_CONDOR_DIR

Please see more details https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial.
