====== Filter Tree to make it smaller =====

Modify subTree.C and run it in root

     .x subTree.C

It is better to copy analysed file localy and run, because speed increase more then by 10 times.


Example of copy for eos:
     eos cp /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to273730_NotCompleted.root ./


Files used for DATA:
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to273730_NotCompleted.root
       INPUT TREE (4274583 ENTRIES)
       OUTPUT TREE (773632 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run273731_to_274240_IncludingMissingLumi_Completed.root
       INPUT TREE (1819339 ENTRIES)
       OUTPUT TREE (317601 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run274241to274421.root
       INPUT TREE (10834544 ENTRIES)
       OUTPUT TREE (1687217 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v2/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run274422to274443.root
       INPUT TREE (4001955 ENTRIES)
       OUTPUT TREE (648346 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v2/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run274444to275125.root
       INPUT TREE (12062727 ENTRIES)
       OUTPUT TREE (1911772 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v3/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run275126to275783.root
       INPUT TREE (12007161 ENTRIES)
       OUTPUT TREE (1920460 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v3/data/TnPTree_80X_Run2016C_v2_GoldenJSON_Run275126to275783.root
       INPUT TREE (3162594 ENTRIES)
       OUTPUT TREE (449817 ENTRIES)
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v3/data/TnPTree_80X_Run2016C_v2_GoldenJSON_Run275784to276097.root
       INPUT TREE (11138416 ENTRIES)
       OUTPUT TREE (1657234 ENTRIES)

Add to one Data file subTree_80X_Run2016_Run271036to276097.root:
       hadd subTree_80X_Run2016_Run271036to276097.root subTree_80X_Run2016_Run271036to273730_NotCompleted.root subTree_80X_Run2016_Run273731_to_274240_IncludingMissingLumi_Completed.root subTree_80X_Run2016_Run274444to275125.root subTree_80X_Run2016_Run274241to274421.root subTree_80X_Run2016_Run274422to274443.root subTree_80X_Run2016B_Run275126to275783.root subTree_80X_Run2016C_Run275126to275783.root subTree_80X_Run2016C_Run275784to276097.root 

MadGraph MC weighted to Data (probe is Global or Tracker Muon):

    TnPTree_80X_DYLL_M50_MadGraphMLM_part1.root
     INPUT TREE (2836056 ENTRIES)
     OUTPUT TREE (1706282 ENTRIES)
    TnPTree_80X_DYLL_M50_MadGraphMLM_part2.root
     INPUT TREE (2822928 ENTRIES)
     OUTPUT TREE (1697812 ENTRIES)
    TnPTree_80X_DYLL_M50_MadGraphMLM_part3.root
     INPUT TREE (2668716 ENTRIES)
     OUTPUT TREE (1604698 ENTRIES)

Add to on MC file
    hadd subTree_80X_MadGraph.root subTree_80X_MadGraph_part1.root subTree_80X_MadGraph_part2.root subTree_80X_MadGraph_part3.root


******

Summary for Run2016 Golden json for Trigger Study for Run < 274094 (use file after ID selection):

    subTree_80X_Run2016_Run271036to274093_TrigStudy.root
      INPUT TREE (4690222 ENTRIES)
      OUTPUT TREE (697182 ENTRIES)

Summary for Run2016B Golden json for Trigger Study for Run >= 274094 (use file after ID selection):

    subTree_80X_Run2016_Run274094to276097_TrigStudy.root
      INPUT TREE (4690222 ENTRIES)
      OUTPUT TREE (3440537 ENTRIES)

Summary for Run2016B Golden json for ISO (merge 2 trigger files) Run 271036 - 274421:

     subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421_IsoStudy.root

For for run<273423 we have low efficiency in barrel, see slide 13:
    
https://indico.cern.ch/event/535947/contributions/2177911/attachments/1278346/1897723/2016.05.24_MuonHLT_TrigEff_80X_KPLee_v2.pdf

Finally all drop in efficiency was fixed only in Run 274094. So we skip Trigger efficiency before and after this run. 
ID and ISO efficinecies are the same in all run period.

