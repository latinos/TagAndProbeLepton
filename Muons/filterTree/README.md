====== Filter Tree to make it smaller =====

Modify subTree.C and run it in root

     .x subTree.C

It is better to copy analysed file localy and run, because speed increase more then by 10 times.


Example of copy for eos:
     eos cp /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to273730_NotCompleted.root ./


Files used for DATA:
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v3/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to275125_incomplete.root
       INPUT TREE (32693395 ENTRIES)
       OUTPUT TREE (5301716 ENTRIES)
       subTree_80X_Run2016_Run271036to275125_incomplete.root
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v3/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run275126to275783.root
       INPUT TREE (12007161 ENTRIES)
       OUTPUT TREE (1920460 ENTRIES)
       subTree_80X_Run2016B_Run275126to275783.root
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v3/data/TnPTree_80X_Run2016C_v2_GoldenJSON_Run275126to275783.root
       INPUT TREE (3162594 ENTRIES)
       OUTPUT TREE (449817 ENTRIES)
       subTree_80X_Run2016C_Run275126to275783.root
Add to one Data file:

hadd subTree_80X_Run2016_Run271036to275783_IdStudy.root subTree_80X_Run2016_Run271036to275125_incomplete.root subTree_80X_Run2016B_Run275126to275783.root subTree_80X_Run2016C_Run275126to275783.root

IdStudy and Trigger file for fill 5043, runs 275757-275783 (latest fill in July 8 Golden json):
      INPUT TREE (7671993 ENTRIES)
      OUTPUT TREE (356294 ENTRIES)
      subTree_80X_Run2016_Run275757to275783_IdStudy.root

       INPUT TREE (356294 ENTRIES)
      OUTPUT TREE (311145 ENTRIES)
      subTree_80X_Run2016_Run275757to275783_TrigStudy.root

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
      INPUT TREE (7671993 ENTRIES)
      OUTPUT TREE (696266 ENTRIES)

Summary for Run2016B Golden json for Trigger Study for Run >= 274094 (use file after ID selection):

    subTree_80X_Run2016_Run274094to275783_TrigStudy.root
      INPUT TREE (7671993 ENTRIES)
      OUTPUT TREE (6061935 ENTRIES)

Summary for Run2016B Golden json for Trigger Study for Run >= 274094 (Mu8 leg): (run>=274094 && run<274444) || run>275125 (use file after ID selection):
      INPUT TREE  (4690222 ENTRIES)
      OUTPUT TREE (1760536 ENTRIES)


Summary for Run2016B Golden json for ISO (merge 2 trigger files) Run 271036 - 274421:

     subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421_IsoStudy.root

For for run<273423 we have low efficiency in barrel, see slide 13:
    
https://indico.cern.ch/event/535947/contributions/2177911/attachments/1278346/1897723/2016.05.24_MuonHLT_TrigEff_80X_KPLee_v2.pdf

Finally all drop in efficiency was fixed only in Run 274094. So we skip Trigger efficiency before and after this run. 
ID and ISO efficinecies are the same in all run period.

