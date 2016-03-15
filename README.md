setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_15_patch1

cd CMSSW_7_4_16_patch2/src/

cmsenv

git cms-init

git cms-merge-topic dmajumder:CMSSW_7_4_X_AnalysisDataFormats_BoostedObjects

git clone git@github.com:dmajumder/EventCounter.git Analysis/EventCounter 

git clone -b Data2015D  git@github.com:skhalil/VLQAna.git  Analysis/VLQAna

 
#To just build this stuff
scram b -j20

# To run on OS2L analysis
cd Analysis/VLQAna/test

cmsRun vlqAna_cfg.py 

# To run crab jobs for skims, e.g for CR in dielectron channel

Analysis/VLQAna/test/Skim/CRAB/Skims_CR_Zelel 

Modify the exisiting crab file, by changing the relvant parameters, like config.General.requestName, config.Data.inputDataset, config.Data.outLFNDirBase, config.Site.storageSite etc.

condor submit -c crab_XX.py

This will create an output condor directory, through which you can check the status of the jobs.

condor status -d MY_CONDOR_DIR

Please see more details https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial.


