setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_12

cd CMSSW_7_4_12/src/

cmsenv

git cms-init

git cms-merge-topic ku-cms:CMSSW_7_4_X

git clone -b v1.00 git://github.com/dmajumder/EventCounter.git  MyAnalysis/EventCounter 

git clone https://github.com/ku-cms/VLQAna.git MyAnalysis/VLQAna

#To just build this stuff
cd MyAnalysis/VLQAna

scram b -j20

# To run
cd test
cmsRun vlqAna_cfg.py 

#To run OS2L analysis 
cmsRun os2lana_cfg.py
