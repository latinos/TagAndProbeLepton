contact: Anna

t&p trees for Re-Reco Run2015D and MC are located at:

    /store/group/phys_muon/TagAndProbe/76XtreeProduction

Example to open i root directly:

    root -l root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_50ns_DY_Spring15/50ns_DY_Spring15.root

Example to copy from eos:

    xrdcp --force --recursive root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/SingleMuon/tnp_Run2015B_PromptReco_50ns_v3.root ./

How to mount and unmount /store

    cd /tmp/kropiv

    eosmount eos eos

    cd eos/cms/store/group/phys_higgs/cmshww/kropiv/

    eosumount eos eos #don't forget to unmount

Example to add weights for pile up:

     root.exe -b -l -q tnp_25nsDY_madgraph.root tnp_Run2015D_PromptReco_25ns_SingleMu_v3.root tnp_Run2015D_PromptReco_25ns_SingleMu_v4.root addNVtxWeight.cxx+

for Run2016B:

     root.exe -b -l -q ../filterTree/subTree_80X_MadGraph_IdStudy.root ../filterTree/subTree_80X_Run2016B_DCSOnly_Run273423_273450_IdStudy.root addNVtxWeight.cxx+
