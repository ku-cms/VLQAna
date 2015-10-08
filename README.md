setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_12

cd CMSSW_7_4_12/src/

cmsenv

git cms-init

git cms-merge-topic ku-cms:CMSSW_7_4_X

git clone -b v1.00 git://github.com/dmajumder/EventCounter.git  Analysis/EventCounter 

git clone https://github.com/skhalil/VLQAna.git Analysis/VLQAna

#To just build this stuff
cd Analysis/VLQAna

scram b -j20

#To run OS2L analysis 
cmsRun os2lana_cfg.py
