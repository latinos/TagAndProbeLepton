#!/bin/sh

REMOTEDIR=/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/eff_tnp

cd $REMOTEDIR
eval `scram runtime -sh`
#cd -
rm out_fitMuon_MuTrigger_PTvsETA.txt
cmsRun $REMOTEDIR/fitMuon_MuTrigger_PTvsETA.py > out_fitMuon_MuTrigger_PTvsETA.txt
