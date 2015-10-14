#!/usr/bin/env python

import sys, os, re, copy
from optparse import OptionParser 
from ROOT import TFile

usage = """Usage: ./mergeDatasetsSimple.py [options]\n
Example: ./mergeDatasetsSimple -d datasetsToMerge.txt\n
For more help: ./mergeDatasetsSimple.py --help 
"""

def main():
  parser = OptionParser(usage=usage)

  parser.add_option("-d", "--dataset_list_for_merging", dest="dataset_list_for_merging",
      help="List of datasets to be merged",
      metavar="DATASET_LIST_FOR_MERGING")

  parser.add_option("-o", "--output_dir", dest="output_dir",
      help="Output directory (optional parameter)",
      metavar="OUTPUT_DIR")

  parser.add_option("-a", "--analyzer_module", dest="analyzer_module",
      help="Name of the analyzer module (Optional parameter, takes default value of 'ana')",
      default='ana', 
      metavar="ANALYZER_MODLE")

  (options, args) = parser.parse_args() 

  ### Check that all necessary input parameters are provided
  if not (options.dataset_list_for_merging):
    print usage
    sys.exit() 

  output_dir = os.getcwd() 
  if options.output_dir:
    output_dir = options.output_dir
  ### Redefine output dir as an absolute path if not so defined
  if not re.search('^/', output_dir):
    output_dir = os.path.join(os.getcwd(), output_dir) 

  workdir = output_dir

  group = ''
  group_datasets = {}
  group_xsec = {}
  group_intlumi = {}
  dataset_xsec = {}
  dataset_nevt = {} 

  ### Open and read the dataset_list_for_merging
  dataset_list_for_merging = open(options.dataset_list_for_merging, 'r')
  dataset_list_for_merging_lines = dataset_list_for_merging.readlines() 

  for line in dataset_list_for_merging_lines:
    line_elements = line.split() 
    if (len(line_elements)==0 or line_elements[0][0]=='#'): continue 
    if re.search(':', line):
      group = line_elements[0].rstrip(':')
      group_datasets[group] = []
      group_xsec[group] = 0.
      group_intlumi[group] = -1.
      if re.search('L=', line):
        group_intlumi[group] = float(line.split('L=')[-1].strip('\n')) 
    else:
      dataset = line_elements[0]
      xsec = float(line_elements[1])
      nevt = float(line_elements[2])
      group_datasets[group].append(dataset)
      if xsec > 0:
        group_xsec[group] = group_xsec[group] + xsec
      else:
        group_xsec[group] = -1.
      dataset_xsec[dataset] = xsec 
      dataset_nevt[dataset] = nevt

  ### Final output file
  filename = 'Final_histograms'
  if (len(options.analyzer_module)>0):
    filename+=str(('_'+options.analyzer_module))
  filename+=str('.root')
  output_root_file = TFile(os.path.join(output_dir, filename), 'RECREATE')

  ### Write histograms
  groups = group_datasets.keys()
  groups.sort()

  for group in groups:
    print group
    final_hists = {}

    for dataset in group_datasets[group]:
      if not os.path.isfile(dataset):
        print 'ERROR: File ' + dataset + ' not found'
        print 'Aborting'
        sys.exit(1)

      ### Open input ROOT file
      root_file = TFile(dataset)
      #htemp = root_file.Get(os.path.join(options.analyzer_module,'allEvents/hEventCount'))
      htemp = root_file.Get(os.path.join('allEvents/hEventCount'))
      #nEventsAll = htemp.GetBinContent(1)
      nEventsAll = htemp.Integral()
      #nEventsAll = dataset_nevt[dataset]#*23443.424/2 
      scale = 1.
      if group_xsec[group] > 0.:
        if group_intlumi[group] > 0.:
          scale = (dataset_xsec[dataset]*group_intlumi[group])/nEventsAll
        else:
          scale = dataset_xsec[dataset]/(group_xsec[group]*nEventsAll)
      print 'dataset', dataset, ' nevts ', nEventsAll, ' group sxec', group_xsec[group], ' dataset xsec ', dataset_xsec[dataset], ' int lumi ', group_intlumi[group], ' scale ', scale

      ### Get number of histograms
      nhists = root_file.Get(options.analyzer_module).GetListOfKeys().GetEntries()

      ### Loop over histograms in the input ROOT file
      for hist in range(0, nhists):
        histname = root_file.Get(options.analyzer_module).GetListOfKeys()[hist].GetName()
        ### Print histname
        htemp = root_file.Get(os.path.join(options.analyzer_module, histname))
        if htemp.InheritsFrom('TH1'):
          if histname not in final_hists.keys():
            final_hists[histname] = copy.deepcopy(htemp)
            final_hists[histname].SetName(group+'__'+histname)
            final_hists[histname].Scale(scale)
          else:
            final_hists[histname].Add(htemp, scale) 

    output_root_file.cd()
    hists = final_hists.keys()
    hists.sort() 
    print "Writing histograms...."
    for hist in hists:
      final_hists[hist].Write()
    print "Done"

  output_root_file.Close()

  print ''
  print 'Final histograms file: '+os.path.join(output_dir, filename)
  print ''

if __name__ == "__main__":
  main() 
