setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_5_patch1

cd CMSSW_7_4_5_patch1/src/

cmsenv

git cms-merge-topic ku-cms:CMSSW_7_4_X

git clobe -b v1.00 git://github.com/cms-btv-pog/cms-EventCounter.git  Analysis/EventCounter 
git clone https://github.com/ku-cms/VLQAna.git Analysis/VLQAna

#To just build this stuff
cd AnalysisDataFormats/BoostedObjects 

scram b -j20

cd ../../Analysis/VLQAna

scram b -j20

# To run
cd test
cmsRun vlqAna_cfg.py 

#To run OS2L analysis 
cmsRun os2lana_cfg.py
