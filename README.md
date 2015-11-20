setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_15_patch1

cd CMSSW_7_4_15_patch1/src/

cmsenv

git cms-init

git cms-merge-topic ku-cms:CMSSW_7_4_X

git clone git://github.com/dmajumder/EventCounter.git Analysis/EventCounter 

git clone -b Data2015D git@github.com:ku-cms/VLQAna.git Analysis/VLQAna  

#To just build this stuff
cd Analysis/VLQAna

scram b -j20

# To run
cd test
cmsRun vlqAna_cfg.py 

#To run OS2L analysis 
cmsRun os2lana_cfg.py
