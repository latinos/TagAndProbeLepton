# TagAndProbe for Muons

*****************************

To install tag and probe follow instructions (current V2):

https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonTagAndProbeTreesRun2

Do not forget to set correct architecture before cmsenv, if not compiled well:

export SCRAM_ARCH=slc6_amd64_gcc491

We are going to use CMSSW_7_4_7.

git clone https://github.com/latinos/TagAndProbeLepton.git


Tag and Probe tree will be located at:

/eos/cms/store/group/phys_higgs/cmshww

*****************************

Triggers and Selections are listed here:
https://github.com/latinos/LatinoTrees/blob/master/AnalysisStep/python/skimEventProducer_cfi.py

*****************************

Check HLT menue:

https://cmsweb-testbed.cern.ch/confdb/

or if it is down:

http://testserver1.cern.ch/


*****************************

MC DY Samples:

/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/AODSIM

/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/AODSIM

CMSSW_7_4_1_patch1

Global tags :

for 25 ns : MCRUN2_74_V9

for 50 ns : MCRUN2_74_V9A

MINAOD MC:

/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM

/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM

CMSSW_7_4_1_patch1

*****************************

MC ggH->WW->2l2nu Smaples (it is not used for TnP):

/GluGluHToWWTo2L2Nu_M120_13TeV_powheg_JHUgen_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/AODSIM

CMSSW_7_4_1_patch3

*****************************
 
