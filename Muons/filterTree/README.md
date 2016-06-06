====== Filter Tree to make it smaller =====

Modify subTree.C and run it in root

     .x subTree.C

It is better to copy analysed file localy and run, because speed increase more then by 10 times.

Summary for Run2016B DCSonly json for ID Study:

     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v1_DCSOnly.root
     INPUT TREE (492014 ENTRIES)
     OUTPUT TREE (141122 ENTRIES)
     OUTPUT TREE (0 ENTRIES) for run>=273423

     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_DCSOnly_UptoRun273450.root
     INPUT TREE (1869408 ENTRIES)
     OUTPUT TREE (547377 ENTRIES)
     OUTPUT TREE (281970 ENTRIES) for run>=273423

Summary for Run2016B DCSonly json for ISO or Trigger Study:

     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v1_DCSOnly.root
     INPUT TREE (492014 ENTRIES)
     OUTPUT TREE (75544 ENTRIES)
     OUTPUT TREE (0 ENTRIES) for run>=273423

     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_DCSOnly_UptoRun273450.root
     INPUT TREE (1869408 ENTRIES)
     OUTPUT TREE (299359 ENTRIES)
     OUTPUT TREE (154291 ENTRIES) for run>=273423

INFO:

     Run < 273423 (190 /pb)
     Run >= 273423 (122 /pb)

For for run<273423 we have low efficiency in barrel, see slide 13:
    
https://indico.cern.ch/event/535947/contributions/2177911/attachments/1278346/1897723/2016.05.24_MuonHLT_TrigEff_80X_KPLee_v2.pdf

Compbinned version of Run2016B v1 and v2 for ID study:

    subTree_80X_Run2016B_DCSOnly_UptoRun273450_IdStudy.root
    for run>=273423

Compbinned version of Run2016B v1 and v2 for ISO and Triger study:

    subTree_80X_Run2016B_DCSOnly_UptoRun273450_ISOandTrigStudy.root
    subTree_80X_Run2016B_DCSOnly_Run273423_273450_ISOandTrigStudy.root for run>=273423
