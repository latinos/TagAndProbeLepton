*****************************
Tag and Probe efficiency:

muonID+ISO for HWW:

for muon ID:

Medium && |dz_PV| < 0.1 && {dxy < 0.01 for pT < 20 GeV || dxy < 0.02 for pT > 20 GeV}

for ISO:

PF Combined Relative Iso < 0.15 (combRelIsoPF04dBeta < 0.15)

*****************************
Triggers used for HWW:

HLT_IsoMu18_v

HLT_IsoTkMu18_v (bad, need to be replaced by HLT_IsoTkMu20_v, under discussion)

HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v

HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v

HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v

HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v

*****************************
muonID+ISO efficiency from Tracker muon:


from DATA: TnP_MediumIDandISO_Run2015D_25ns_PTvsETA_binBig_HWW.txt

from MC (pile up reweight to DATA): TnP_MediumIDandISO_DY_madgraph25nsLikeRun2015D_25ns_PTvsETA_binBig_HWW.txt

*****************************
Trigger efficiency from muonID+ISO selections using DATA only:

HLT_IsoMu18: TnP_IsoMu18_Run2015D_25ns_PTvsETA_binSmall_HWW.txt

HLT_IsoTkMu18 (broken bad trigger to use for v3 and good after run 257968): TnP_IsoTkMu18_Run2015D_25ns_PTvsETA_binSmall_HWW.txt

*****************************
Trigger efficiecny for Double Mu trigger looks reasonable, but should be confirmed (good for 1st iteration):

IsoMu17leg  : TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2015D_25ns_PTvsETA_binBig_HWW.txt

IsoMu8leg   : TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binSmall_HWW.txt

IsoTkMu8 leg: TnP_DoubleIsoMu17TkMu8_TkMu8leg_Run2015D_25ns_PTvsETA_binSmall_HWW.txt
