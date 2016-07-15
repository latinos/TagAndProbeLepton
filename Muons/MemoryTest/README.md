
### Test new memory suppression tool
In CMSSW_8_0_12/src:
 
     git cms-addpkg PhysicsTools/TagAndProbe

To have good code from Manuel:
     cp ~mcbs/public/forAnnaTnP/TagAndProbe/src/TagProbeFitter.cc /afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/PhysicsTools/TagAndProbe/src
     cp ~mcbs/public/forAnnaTnP/TagAndProbe/interface/TagProbeFitter.h /afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/PhysicsTools/TagAndProbe/interface/

Compile in CMSSW_8_0_12/src:
     scramv1 b -v

Check 2nd time that everything is compiled

Copy fitMuon.py from https://gaperrin.web.cern.ch/gaperrin/tnp/TnP2016/2016Data_2p6InvfbTopUp_27_06_2016/fitMuon.py

Run for 4 options:

    "OutputName noiso tight data_all data"
    "OutputName noiso medium data_all data"
    "OutputName noiso loose data_all data"
    "OutputName tight tight data_all data"

     cmsRun fitMuon.py Tight_noiso noiso tight data_all data pt_alleta
     cmsRun fitMuon.py Medium_noiso noiso medium data_all data pt_alleta
     cmsRun fitMuon.py Loose_noiso noiso loose data_all data pt_alleta
     cmsRun fitMuon.py Tight_Tightiso tight tight data_all data pt_alleta

For MC weight test:
     cmsRun fitMuon.py Tight_Tightiso tight tight mc_all mc_2016B pt_alleta

    

Produce it for modified PhysicsTools/TagAndProbe and original one. Calculate SF with:

https://github.com/HuguesBrun/plotsAndSFsExtractor

It should be 1 everywhere if code works propely.  

To extract code:

     git clone https://github.com/HuguesBrun/plotsAndSFsExtractor.git

How to Run:
     root -b -q -l 'extractPlotsAndComputeTheSFs.C("Loose_noiso_PtBins","../MemorySave/EfficiencyLoose_noiso/DATA_data/TnP_MC_NUM_LooseID_DEN_genTracks_PAR_pt_alleta_bin1.root", "../MemoryOriginal/EfficiencyLoose_noiso/DATA_data/TnP_MC_NUM_LooseID_DEN_genTracks_PAR_pt_alleta_bin1.root")'
     root -b -q -l 'extractPlotsAndComputeTheSFs.C("Medium_noiso_PtBins","../MemorySave/EfficiencyMedium_noiso/DATA_data/TnP_MC_NUM_MediumID_DEN_genTracks_PAR_pt_alleta_bin1.root", "../MemoryOriginal/EfficiencyMedium_noiso/DATA_data/TnP_MC_NUM_MediumID_DEN_genTracks_PAR_pt_alleta_bin1.root")'
     root -b -q -l 'extractPlotsAndComputeTheSFs.C("Tight_noiso_PtBins","../MemorySave/EfficiencyTight_noiso/DATA_data/TnP_MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_alleta_bin1.root", "../MemoryOriginal/EfficiencyTight_noiso/DATA_data/TnP_MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_alleta_bin1.root")'
     root -b -q -l 'extractPlotsAndComputeTheSFs.C("Tight_Tightiso_PtBins","../MemorySave/EfficiencyTight_Tightiso/DATA_data/TnP_MC_NUM_TightRelIso_DEN_TightID_PAR_pt_alleta_bin1.root", "../MemoryOriginal/EfficiencyTight_Tightiso/DATA_data/TnP_MC_NUM_TightRelIso_DEN_TightID_PAR_pt_alleta_bin1.root")'


To check weight in MC if it works for MemorySave:

    root -b -q -l 'extractPlotsAndComputeTheSFs.C("Tight_Tightiso_PtBins_MC","../MemorySave/EfficiencyTight_Tightiso_MC/MC_mc_2016B/TnP_MC_NUM_TightRelIso_DEN_TightID_PAR_pt_alleta_bin1.root", "../MemoryOriginal/EfficiencyTight_Tightiso_MC/MC_mc_2016B/TnP_MC_NUM_TightRelIso_DEN_TightID_PAR_pt_alleta_bin1.root")'


******
