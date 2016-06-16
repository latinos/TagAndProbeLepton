====== Filter Tree to make it smaller =====

Modify subTree.C and run it in root

     .x subTree.C

It is better to copy analysed file localy and run, because speed increase more then by 10 times.


Example of copy for eos:
     eos cp /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to273730_NotCompleted.root ./


MadGraph MC weighted to Data (probe is Global or Tracker Muon):

     INPUT TREE (2836056 ENTRIES)
     OUTPUT TREE (1614495 ENTRIES): subTree_80X_MadGraphLikeRun2016B_IdStudy.root

Run2016B Golden json file Run 271036 - 274421:

     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to273730_NotCompleted.root
     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run273731_to_274240_IncludingMissingLumi_Completed.root
     /store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run274241to274421.root

Mergered file is:

     TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421.root 

Summary for Run2016B Golden json for ID Study Run 271036 - 274421 (probe is Global or Tracker Muon):

     INPUT TREE (16928466 ENTRIES)
     OUTPUT TREE (2798542 ENTRIES): subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421_IdStudy.root

Summary for Run2016B Golden json for ID Study Run 271036 - 274421 (probe is Track, a lot of BackGround, bad to us):

     INPUT TREE (16928466 ENTRIES)
     OUTPUT TREE (5007938 ENTRIES) : subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421_IdStudy_Track.root

Summary for Run2016B Golden json for Trigger Study for Run < 274421 (use file after ID selection):

     INPUT TREE (5007938 ENTRIES)
     OUTPUT TREE (764768 ENTRIES) : subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274093_TrigStudy.root

Summary for Run2016B Golden json for Trigger Study for Run >= 274421 (use file after ID selection):

     INPUT TREE  (5007938 ENTRIES)
     OUTPUT TREE (1897714 ENTRIES) : subTree_80X_Run2016B_v2_GoldenJSON_Run274094to274421_TrigStudy.root

Summary for Run2016B Golden json for ISO (merge 2 trigger files) Run 271036 - 274421:

     subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421_IsoStudy.root

For for run<273423 we have low efficiency in barrel, see slide 13:
    
https://indico.cern.ch/event/535947/contributions/2177911/attachments/1278346/1897723/2016.05.24_MuonHLT_TrigEff_80X_KPLee_v2.pdf

Finally all drop in efficiency was fixed only in Run 274094. So we skip Trigger efficiency before and after this run. 
ID and ISO efficinecies are the same in all run period.

