====== Filter Tree to make it smaller =====

Modify subTree.C and run it in root

     .x subTree.C

It is better to copy analysed file localy and run, because speed increase more then by 10 times.


Example of copy for eos:
     eos cp /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to273730_NotCompleted.root ./

Moriond2017:
Files used for DATA:
    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunB/TnPTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root 
       INPUT TREE (52458925 ENTRIES)
       OUTPUT TREE (7234780 ENTRIES)
       subTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root

    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunC/TnPTree_80XRereco_Run2016C_GoldenJSON_Run276098to276384.root
       INPUT TREE (26933378 ENTRIES)
       OUTPUT TREE (3167436 ENTRIES)
       subTree_80XRereco_Run2016C_GoldenJSON_Run276098to276384.root 

    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunD/TnPTree_80XRereco_Run2016D_GoldenJSON_Run276098to276384.root 
       INPUT TREE (42466548 ENTRIES)
       OUTPUT TREE (5284655 ENTRIES)
       subTree_80XRereco_Run2016D_GoldenJSON_Run276098to276384.root 

    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunE/TnPTree_80XRereco_Run2016E_GoldenJSON_Run276098to276384.root 
       INPUT TREE (45121233 ENTRIES)
       OUTPUT TREE (4856314 ENTRIES)
       subTree_80XRereco_Run2016E_GoldenJSON_Run276098to276384.root

    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunF/TnPTree_80XRereco_Run2016F_GoldenJSON_Run276098to276384.root 
       INPUT TREE (34868293 ENTRIES)
       OUTPUT TREE (3747686 ENTRIES)

    /store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunG/TnPTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root
       INPUT TREE (73608526 ENTRIES)
       OUTPUT TREE (9788946 ENTRIES)
       subTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root

    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunH/TnPTree_80XRereco_Run2016H_v2_GoldenJSON_Run281613to284035.root
       INPUT TREE (91962465 ENTRIES)
       OUTPUT TREE (11862934 ENTRIES)

    /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v5/data/RunH/TnPTree_80XRereco_Run2016H_GoldenJSON_Run284036to284044.root
       INPUT TREE (1957231 ENTRIES)
       OUTPUT TREE (279895 ENTRIES)

MC:
    /eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/MCDR80X/DY_Summer16PremixMoriond/ 1-5
       INPUT TREE (7488049 ENTRIES)
       OUTPUT TREE (4067751 ENTRIES)
       subTree_MC_Moriond17_DY_tranch4Premix_part1_5

    /eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/MCDR80X/DY_Summer16PremixMoriond/ 6-10
       INPUT TREE (8217199 ENTRIES)
       OUTPUT TREE (4463893 ENTRIES)
       subTree_MC_Moriond17_DY_tranch4Premix_part6_10

Trigger Study:



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

    
    https://indico.cern.ch/event/535947/contributions/2177911/attachments/1278346/1897723/2016.05.24_MuonHLT_TrigEff_80X_KPLee_v2.pdf

Finally all drop in efficiency was fixed only in Run 274094. So we skip Trigger efficiency before and after this run. 
ID and ISO efficinecies are the same in all run period.

