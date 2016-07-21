#Tag and Probe efficiency

******
#muonID+ISO for HWW:

IMPORTANT: We move from Medim selection to Tight due to efficiency degradation for Medium ID as function of inst. luminosity

Efficiency is recalculated for part July 8 Golden json file: Runs 271036-274421 

for muon ID (TightHWW):

    Tight && |dz_PV| < 0.1 && {dxy < 0.01 for pT < 20 GeV || dxy < 0.02 for pT > 20 GeV}

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
#Triggers used for HWW for Run2016:

    HLT_IsoMu22_v||HLT_IsoTkMu22_v 

    HLT_IsoMu24_v||HLT_IsoTkMu24_v (back up) 

    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v

    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v

    HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v

    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v

******
#muonID efficiency from Tracker muon:

We have calculated muon ID efficiency with respect of muon to be Tracker or Global Muon.

from DATA: 

     TightID_Run2016_PTvsETA_HWW.txt

from MC (pile up reweight to DATA): 

     TightID_DY_madgraphLikeRun2016_PTvsETA_HWW.txt

******
#ISO efficiency from Tracker muon:

We have calculated ISO efficiency with respect of muon to pass TighHWW selections.

from DATA:

     ISOTight_Run2016_PTvsETA_HWW.txt

from MC (pile up reweight to DATA):

     ISOTight_DY_madgraphLikeRun2016_PTvsETA_HWW.txt

******
#Trigger efficiency after passing muonID+ISO selections using DATA only:

We have calculated Trigger efficiency with respect of muon to pass TighHWW and ISO selections.

Some drop in efficiency in barrel was fixed only in Run 274094. So we skip Trigger efficiency before and after this run.
ID and ISO efficinecies are the same in all run period.

#SingleMu trigger 

HLT_IsoMu22||HLT_IsoTkMu22: 

    SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunGe274094_HWW.txt
    SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunLt274094_HWW.txt

HLT_IsoMu24||HLT_IsoTkMu24:

    SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunGe274094_HWW.txt
    SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunLt274094_HWW.txt

#Trigger leg efficiecny for DoubleMu triggers:

IsoMu17leg: 
 
    DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunLt274094_HWW.txt

IsoMu8leg:

    DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunLt274094_HWW.txt

IsoMu8||IsoTkMu8leg: 

    DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunLt274094_HWW.txt

IsoTkMu8leg:

    DoubleMu_IsoTkMu8leg_Run2016_PTvsETA_RunGe274094_HWW.txt
    DoubleMu_IsoTkMu8leg_Run2016_PTvsETA_RunLt274094_HWW.txt
