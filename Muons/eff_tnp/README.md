contact: Anna
-----

For Moriond 2017 HWW:

All run periods for Trigger are described here:

    https://github.com/latinos/LatinoAnalysis/blob/master/Gardener/python/data/trigger/Trigger_cfg.py#L104

Triggers are used for full 2016 dataset are described here:

    https://indico.cern.ch/event/598403/sessions/218044/note/

Muon legs diffent in time:
    DoubleMu: Mu17||TrMu17 for run >=281613 (Run2016H) esle Mu17
    MuEG    : Mu12 for run>= 278273 (Run2016F: RunGe278167) esle Mu8

The rest legs are the same during full 2016:
    DoubleMu: Mu8||TkMu8
    MuEG    : Mu23

To calculate Mu23 use Mu17 leg:
    Mu17_TrkIsoVVL: L1pT=11, L1Quality>=8, L2 pT > 10, L3 pT > 17
    Mu23_TrkIsoVVL: L1pT=23 (I see that it is seeded by L1_Mu20_EG10 OR  L1_Mu23_EG10 but I have the impression that  L1_Mu20_EG10 was prescaled at some point), L1Quality>=12, L2 pT > 10 , L3 pT > 23   

To calculate Mu12 use Mu8 leg:


-----
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

for Run2016 B-F:

     root.exe -b -l -q ../filterTree/subTree_MC_Moriond17_DY_tranch4Premix_part1_5.root ../filterTree/subTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root ../filterTree/subTree_80XRereco_Run2016C_GoldenJSON_Run276098to276384.root ../filterTree/subTree_80XRereco_Run2016D_GoldenJSON_Run276098to276384.root ../filterTree/subTree_80XRereco_Run2016E_GoldenJSON_Run276098to276384.root ../filterTree/subTree_80XRereco_Run2016F_GoldenJSON_Run276098to276384.root addNVtxWeight.cxx+


