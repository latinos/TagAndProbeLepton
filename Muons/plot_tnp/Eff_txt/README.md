#Tag and Probe efficiency

*****************************
muonID+ISO for HWW:

for muon ID:

Medium && |dz_PV| < 0.1 && {dxy < 0.01 for pT < 20 GeV || dxy < 0.02 for pT > 20 GeV}

for ISO:

Tigt PF Combined Relative Iso < 0.15 (combRelIsoPF04dBeta < 0.15)


Fake PF Combined Relative Iso < 0.40 (combRelIsoPF04dBeta < 0.40)

For both Isolations above we should apply Tracker Relative Isolation: isolationR03().sumPt/pt < 0.4

Currently all Iso and trigger efficiencies are calculated without Tracker Relative Isolation. 

We don't need to recalculate new efficiencies, because:

    efficiency of isolationR03().sumPt/pt<0.4 is 99.96 % on top of rel. PF ISO < 0.15

    efficiency of isolationR03().sumPt/pt<0.4 is 99.52 % on top of loose tail of 0.15 < rel. PF ISO < 0.4
    
    Look at https://github.com/latinos/TagAndProbeLepton/tree/master/Muons/plot_tnp/Plots_ISO 


*****************************
Triggers used for HWW:

HLT_IsoMu18_v||HLT_IsoTkMu20_v (HLT_IsoTkMu18_v was not active in the beginning of Run2015D) 

HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v

HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v

HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v

HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v

*****************************
#muonID+ISO efficiency from Tracker muon:

from DATA: MediumIDandISO_Run2015D_25ns_PTvsETA_HWW.txt

from MC (pile up reweight to DATA): MediumIDandISO_DY_madgraph25nsLikeRun2015D_25ns_PTvsETA_HWW.txt

*****************************
#Trigger efficiency after passing muonID+ISO selections using DATA only:

#SingleMu trigger:

HLT_IsoMu18||HLT_IsoTkMu20: SingleMu_IsoMu18orIsoTkMu20_Run2015D_25ns_PTvsETA_HWW.txt

For comparison:

HLT_IsoMu18: SingleMu_IsoMu18_Run2015D_25ns_PTvsETA_HWW.txt

HLT_IsoTkMu20: SingleMu_IsoTkMu20_Run2015D_25ns_PTvsETA_HWW.txt

HLT_IsoTkMu18 (broken bad trigger to use for v3 and good after run 257968, don't use it): SingleMu_IsoTkMu18_Run2015D_25ns_PTvsETA_HWW.txt

*****************************
# Trigger leg efficiecny for DoubleMu triggers:

IsoMu17leg  : DoubleMu_IsoMu17leg_Run2015D_25ns_PTvsETA_HWW.txt

IsoMu8leg   : DoubleMu_IsoMu8leg_Run2015D_25ns_PTvsETA_HWW.txt

IsoMu8||IsoTkMu8leg: DoubleMu_IsoMu8orIsoTkMu8leg_Run2015D_25ns_PTvsETA_HWW.txt

For comparison:

IsoTkMu8 leg: DoubleMu_IsoTkMu8leg_Run2015D_25ns_PTvsETA_HWW.txt
