#!/bin/sh

REMOTEDIR=/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/TagAndProbeLepton/Muons/eff_tnp

cd $REMOTEDIR
eval `scram runtime -sh`
#cd -
rm out_fitMuon_MediumIDandISO_1Deff.txt
cmsRun $REMOTEDIR/fitMuon_MediumIDandISO_1Deff.py > out_fitMuon_MediumIDandISO_1Deff.txt

#cp out_fitMuon_MediumIDandISO_1Deff_Test.txt $REMOTEDIR/lxbatch/
#cp *.root $REMOTEDIR/lxbatch/ 
