setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_16_patch2

cd CMSSW_7_4_16_patch2/src/

cmsenv

git cms-init

git cms-merge-topic dmajumder:CMSSW_7_4_X_AnalysisDataFormats_BoostedObjects

git clone git@github.com:dmajumder/EventCounter.git Analysis/EventCounter 

git clone -b VLQtrees git@github.com:dmajumder/VLQAna.git Analysis/VLQAna  

#To just build this stuff
scram b -j20

# To run
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


