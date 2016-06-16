#Tag and Probe efficiency

******
#muonID+ISO for HWW:

for muon ID:

    Medium && |dz_PV| < 0.1 && {dxy < 0.01 for pT < 20 GeV || dxy < 0.02 for pT > 20 GeV}

for ISO:

    Tigt PF Combined Relative Iso < 0.15 (combRelIsoPF04dBeta < 0.15)


Fake PF Combined Relative Iso < 0.40 (combRelIsoPF04dBeta < 0.40) done only for Run2015D reReco:

For both Isolations above we should apply Tracker Relative Isolation: isolationR03().sumPt/pt < 0.4

Currently all Iso and trigger efficiencies are calculated without Tracker Relative Isolation. 

We don't need to recalculate new efficiencies, because:

     efficiency of isolationR03().sumPt/pt<0.4 is 99.96 % on top of rel. PF ISO < 0.15

      efficiency of isolationR03().sumPt/pt<0.4 is 99.52 % on top of loose tail of 0.15 < rel. PF ISO < 0.4
    
Look at https://github.com/latinos/TagAndProbeLepton/tree/master/Muons/plot_tnp/Plots_ISO 


******
#Triggers used for HWW for Run2016B:

    HLT_IsoMu20_v||HLT_IsoTkMu20_v 

    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v

    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v

    HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v

    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v

******
#muonID efficiency from Tracker muon:

from DATA: 

     MediumID_Run2016B_PTvsETA_HWW.txt

from MC (pile up reweight to DATA): 

     MediumID_DY_madgraph25nsLikeRun2016B_PTvsETA_HWW.txt

******
#Trigger efficiency after passing muonID+ISO selections using DATA only:

Some drop in efficiency in barrel was fixed only in Run 274094. So we skip Trigger efficiency before and after this run.
ID and ISO efficinecies are the same in all run period.

#SingleMu trigger 

HLT_IsoMu20||HLT_IsoTkMu20: 

    SingleMu_IsoMu20orIsoTkMu20_Run2016B_PTvsETA_RunGe274094_HWW.txt
    SingleMu_IsoMu20orIsoTkMu20_Run2016B_PTvsETA_RunLt274094_HWW.txt

#Trigger leg efficiecny for DoubleMu triggers:

IsoMu17leg: 
 
    DoubleMu_IsoMu17leg_Run2016B_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoMu17leg_Run2016B_PTvsETA_RunLt274094_HWW.txt

IsoMu8leg:

    DoubleMu_IsoMu8leg_Run2016B_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoMu8leg_Run2016B_PTvsETA_RunLt274094_HWW.txt

IsoMu8||IsoTkMu8leg: 

    DoubleMu_IsoMu8orIsoTkMu8leg_Run2016B_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoMu8orIsoTkMu8leg_Run2016B_PTvsETA_RunLt274094_HWW.txt

IsoTkMu17leg:

    DoubleMu_IsoTkMu8leg_Run2016B_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoTkMu8leg_Run2016B_PTvsETA_RunLt274094_HWW.txt
