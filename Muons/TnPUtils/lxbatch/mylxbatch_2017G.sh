#!/bin/sh

REMOTEDIR=/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_25/src/TagAndProbeLepton/Muons/TnPUtils/lxbatch

cd $REMOTEDIR
eval `scram runtime -sh`
#cd -

python ../addBranch "../../filterTree/subTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root" "outputG.root" "abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi" "pair_dPhi"
0
python ../addBranch "outputG.root" "subTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root" "pair_dPhi*(180/3.1415926535) if ((tag_eta > 0.9 and eta > 0.9) or (tag_eta < -0.9 and eta < -0.9)) else 180;pair_dPhi;tag_eta;eta;phi;tag_phi" "pair_dPhiEndcapDeg"
