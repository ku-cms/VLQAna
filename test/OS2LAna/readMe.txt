#instructions for CRAB submisison to produce the skims
1. Create soft links of the following files in /Skim directory.

ln -s ../2016_25ns_Spring_PUXsec65740nb50.root .
ln -s ../2016_25ns_Spring_PUXsec69200nb50.root .
ln -s ../2016_25ns_Spring_PUXsec72660nb50.root .
ln -s ../PUDistMC_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU.root .
ln -s ../CSVv2_ichep.csv .
ln -s ../Spring16_25nsV6_MC_L2Relative_AK8PFchs.txt .
ln -s ../Spring16_25nsV6_MC_L3Absolute_AK8PFchs.txt .
ln -s ../Spring16_25nsV6_MC_Uncertainty_AK8PFchs.txt .
ln -s ../Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt .
ln -s ../os2lana_cfg.py .
ln -s ../scalefactors_v4.root .
ln -s ../inputFiles_cfi.py .

2. Edit allJobList.py accordingly to parse the dataset names and parameter options for os2lana_cfg.py

3. Before submitting the CRAB job, its better to first comment last line of crab_command.py, and the run it as "python crab_command.py". Take a moment to look at the crab config and subdirectory where CRAB logs will be stored etc. Once assured, rerun the script after uncommenting the last line.
