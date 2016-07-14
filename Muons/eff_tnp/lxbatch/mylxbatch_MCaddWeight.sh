#!/bin/sh

REMOTEDIR=/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/TagAndProbeLepton/Muons/eff_tnp

cd $REMOTEDIR
eval `scram runtime -sh`
#cd -

date

root.exe -b -l -q /afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM.root /afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part1.root /afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part2.root /afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part3.root /afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part4.root addNVtxWeight.cxx+

mv tnpZ_withNVtxWeights.root TnPTree_76X_DYLL_M50_MadGraphMLM_DataWeight.root

date

