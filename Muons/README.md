# TagAndProbe for Muons

*****************************

Results are documented at following twiki:

https://twiki.cern.ch/twiki/bin/view/CMS/HWW2015TriggerResults

To install tag and probe follow instructions (current V4.1):

https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonTagAndProbeTreesRun2

Do not forget to set correct architecture before cmsenv, if not compiled well:
    export SCRAM_ARCH=slc6_amd64_gcc493

We are going to use CMSSW_7_6_3_patch2 for Re-reco Run2015D and CMSSW_8_0_7_patch2 for Run2016B.
    git clone https://github.com/latinos/TagAndProbeLepton.git


Tag and Probe trees for Re-reco Run2015D, produced by Muon POG, are located at:
    /store/group/phys_muon/TagAndProbe/76XtreeProduction

Tag and Probe trees for Prompt reco Run2016B, produced by Muon POG, are located at:
    /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/DY_madgraphMLM
    /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/

Privite link to PromtReco Run2015D: 
    /eos/cms/store/group/phys_higgs/cmshww

*****************************

Triggers and Selections are listed here:
https://github.com/latinos/LatinoTrees/blob/master/AnalysisStep/python/skimEventProducer_cfi.py

*****************************

Check HLT menue:

https://cmsweb-testbed.cern.ch/confdb/

or if it is down:

http://testserver1.cern.ch/

*****************************
