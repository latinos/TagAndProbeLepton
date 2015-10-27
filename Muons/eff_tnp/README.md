contact: Anna

t&p trees are located at:

/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_50ns_DY_Spring15/50ns_DY_Spring15.root
/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_25ns_DY_Spring15/25ns_DY_Spring15.root

Example to open i root directly:

root -l root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_50ns_DY_Spring15/50ns_DY_Spring15.root

Example to copy from eos:

xrdcp --force --recursive root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/SingleMuon/tnp_Run2015B_PromptReco_50ns_v3.root ./

How to mount and unmount /store

cd /tmp/kropiv

eosmount eos eos

cd eos/cms/store/group/phys_higgs/cmshww/kropiv/

eosumount eos eos #don't forget to unmount
