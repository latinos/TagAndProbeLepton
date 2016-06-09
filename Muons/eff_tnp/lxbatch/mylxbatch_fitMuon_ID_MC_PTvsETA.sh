#!/bin/sh

REMOTEDIR=/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_7_patch2/src/TagAndProbeLepton/Muons/eff_tnp

cd $REMOTEDIR
eval `scram runtime -sh`
#cd -
rm out_fitMuon_ID_MC_PTvsETA.txt
cmsRun $REMOTEDIR/fitMuon_ID_MC_PTvsETA.py > out_fitMuon_ID_MC_PTvsETA.txt

