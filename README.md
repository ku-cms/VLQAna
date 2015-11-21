setenv SCRAM_ARCH slc6_amd64_gcc491


cmsrel CMSSW_7_4_15_patch1

cd CMSSW_7_4_15_patch1/src/

cmsenv

git cms-init

git cms-merge-topic dmajumder:CMSSW_7_4_X_AnalysisDataFormats_BoostedObjects

git clone git@github.com:dmajumder/EventCounter.git Analysis/EventCounter 

git clone https://github.com/skhalil/VLQAna.git Analysis/VLQAna  

 
#To just build this stuff
scram b -j20

# To run on OS2L analysis
cd Analysis/VLQAna/test

cmsRun os2lana_cfg.py

# To run crab jobs for skims, e.g for CR in dielectron channel

Analysis/VLQAna/test/Skim/CRAB/Skims_CR_Zelel 

Modify the exisiting crab file, by changing the relvant parameters, like config.General.requestName, config.Data.inputDataset, config.Data.outLFNDirBase, config.Site.storageSite etc.

cmsRun crab_XX.py


