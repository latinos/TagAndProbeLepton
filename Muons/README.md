# TagAndProbe for Muons

******

Results are documented at following twiki:

https://twiki.cern.ch/twiki/bin/view/CMS/HWW2015TriggerResults

To install tag and probe follow instructions (current V4.1):

https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonTagAndProbeTreesRun2


----

### Test new memory suppression tool
In CMSSW_8_0_12/src:
 
     git cms-addpkg PhysicsTools/TagAndProbe

To have good code from Manuel:
     cp ~mcbs/public/forAnnaTnP/TagAndProbe/src/TagProbeFitter.cc /afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/PhysicsTools/TagAndProbe/src
     cp ~mcbs/public/forAnnaTnP/TagAndProbe/interface/TagProbeFitter.h /afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/PhysicsTools/TagAndProbe/interface/

Compile in CMSSW/src:
     scramv1 b -v

Check 2nd time that everything is compiled
----- 
### For Prompt Reco 2015B Data

    export SCRAM_ARCH=slc6_amd64_gcc530
    cmsrel CMSSW_8_0_7_patch2
    cd CMSSW_8_0_7_patch2/src/
    cmsenv
    git cms-merge-topic battibass:stage2_L1_matching
    git clone https://github.com/battibass/MuonAnalysis-TagAndProbe.git MuonAnalysis/TagAndProbe -b 80X_trigger
    scramv1 b -j 10

My HWW code:

    git clone https://github.com/latinos/TagAndProbeLepton.git

Tag and Probe trees for Prompt reco Run2016B, produced by Muon POG, are located at:

    /DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16DR80-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext1-v1/AODSIM 
    /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/DY_madgraphMLM

    /SingleMuon/Run2016B-PromptReco-v1/AOD
    /SingleMuon/Run2016B-PromptReco-v2/AOD
    /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/

-----
### For Re-reco 2015D data

Do not forget to set correct architecture before cmsenv, if not compiled well:

    export SCRAM_ARCH=slc6_amd64_gcc493

We are going to use CMSSW_7_6_3_patch2 for Re-reco Run2015D 

    git clone https://github.com/latinos/TagAndProbeLepton.git


Tag and Probe trees for Re-reco Run2015D, produced by Muon POG, are located at:

    /store/group/phys_muon/TagAndProbe/76XtreeProduction


Privite link to PromtReco Run2015D: 

    /eos/cms/store/group/phys_higgs/cmshww

******

### Triggers and Selections are listed here:

https://github.com/latinos/LatinoTrees/blob/master/AnalysisStep/python/skimEventProducer_cfi.py

******

### Check HLT menue:

https://cmsweb-testbed.cern.ch/confdb/

or if it is down:

http://testserver1.cern.ch/

******
