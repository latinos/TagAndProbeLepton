#!/bin/sh

REMOTEDIR=/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/eff_tnp

cd $REMOTEDIR
eval `scram runtime -sh`
#cd -
rm out_fitMuon_MediumIDandISO_PTvsETA.txt
cmsRun $REMOTEDIR/fitMuon_MediumIDandISO_PTvsETA.py > out_fitMuon_MediumIDandISO_PTvsETA.txt

#cp out_fitMuon_MediumIDandISO_1Deff_Test.txt $REMOTEDIR/lxbatch/
#cp *.root $REMOTEDIR/lxbatch/ 
