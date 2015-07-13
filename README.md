setenv SCRAM_ARCH slc6_amd64_gcc491

cmsrel CMSSW_7_4_5_patch1

cd CMSSW_7_4_5_patch1/src/

cmsenv

git cms-merge-topic ku-cms:CMSSW_7_4_X

git clone https://github.com/ku-cms/VLQAna.git Analysis/VLQAna

#To just build this stuff
cd Analysis/VLQAna

scram b -j20

