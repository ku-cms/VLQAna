#! /bin/python

def list_Zelel_data():
    jobList = [
        ['/DoubleEG/skhi-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-642b48c1c707cb5cfa93fc168fde448b/USER', 'DoubleEG-Run2016', '20'],
        ]
    return jobList

def list_Zmumu_data():
    jobList = [
        ['/DoubleMuon/skhi-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-642b48c1c707cb5cfa93fc168fde448b/USER','DoubleMuon', '10'],
        ]
    return jobList


def list_MC(): 
    jobList = [
        ['/DYJetsToLL_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-a300e501c1a543433113bdc094d47173/USER', 'DY_Pt-100to250', '10'],
        ['/DYJetsToLL_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-a300e501c1a543433113bdc094d47173/USER', 'DY_Pt-250to400', '10'],
        ['/DYJetsToLL_Pt-400To650_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-a300e501c1a543433113bdc094d47173/USER', 'DY_Pt-400to650', '10'],
        ['/DYJetsToLL_Pt-650ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-a300e501c1a543433113bdc094d47173/USER', 'DY_Pt-650ToInf', '10'],
        ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/grauco-B2GAnaFW_80X_V2p1-edbed0685401a5848e7d61871b3a63d8/USER', 'TTbar_TuneCUETP8M1_powheg', '20'],
        ['/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TTbar_TuneCUETP8M2T4_powheg', '10'],
        
        ['/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-800', '2'],
        ['/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-900', '2'],
        ['/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1000', '2'],
        ['/TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1100', '2'],
        ['/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1200', '2'],
        ['/TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1300', '2'],
        ['/TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1400', '2'],
        ['/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1500', '2'],
        ['/TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1600', '2'],
        ['/TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1700', '2'],
        ['/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'TprimeTprime_M-1800', '2'],
        ['/BprimeBprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-800', '2'],
        ['/BprimeBprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-900', '2'],
        ['/BprimeBprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1000', '2'],
        ['/BprimeBprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1100', '2'],
        ['/BprimeBprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1200', '2'],
        ['/BprimeBprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1300', '2'],
        ['/BprimeBprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1400', '2'],
        ['/BprimeBprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1500', '2'],
        ['/BprimeBprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1600', '2'],
        ['/BprimeBprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1700', '2'],
        ['/BprimeBprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/vorobiev-B2GAnaFW_RunIISpring16MiniAODv2_25ns_v80x_v2p1-24c95768e44153a28c3920000b3803cb/USER', 'BprimeBprime_M-1800', '2'],
         
        ]   
    return jobList
