import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo"

isMuonSel = 'Tight'
#isMuonSel = 'Medium'

## Tag muon is always matched to tag_IsoMu22
#isTrigger = 'Mu23_TrkIsoVVL'
#isTrigger = 'DoubleIsoMu17Mu8_IsoMu17leg'
#isTrigger = 'DoubleIsoMu17Mu8_IsoMu8leg'
###isTrigger = 'DoubleIsoMu17TkMu8_IsoMu8leg'# this is correct for IsoTkMu8leg

#isTrigger = 'SingleMu_IsoMu22orIsoTkMu22' ## you have to change efficiency input yourself for this mode
#isTrigger = 'SingleMu_IsoMu24orIsoTkMu24' ## you have to change efficiency input yourself for this mode
#isTrigger = 'DoubleMu_IsoMu8orIsoTkMu8leg'  ## you have to change efficiency input yourself for this mode
#isTrigger = 'DoubleMu_IsoMu17orIsoTkMu17leg'  ## you have to change efficiency input yourself for this mode
#isTrigger = 'DoubleMu_IsoMu23_l1pt20'  ## you have to change efficiency input yourself for this mode
isTrigger = 'DoubleMu_IsoMu23_l1pt23'  ## you have to change efficiency input yourself for this mode
#isTrigger = 'DoubleMu_IsoMu12'  ## you have to change efficiency input yourself for this mode

DataOpen ="1"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

#Bunch = "50ns";
#DataType = "Run2015B";

Bunch = "25ns";
DataType = "Run2016";

FileNameOpenMC1 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_LikeRun2015D.root";

#1st
FileNameOpenData1 = "../filterTree/subTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root";
FileNameOpenData2 = "../filterTree/subTree_80XRereco_Run2016C_GoldenJSON_Run276098to276384.root";
FileNameOpenData3 = "../filterTree/subTree_80XRereco_Run2016D_GoldenJSON_Run276098to276384.root";
FileNameOpenData4 = "../filterTree/subTree_80XRereco_Run2016E_GoldenJSON_Run276098to276384.root";
FileNameOpenData5a = "../filterTree/subTree_80XRereco_Run2016F_GoldenJSON_RunLt278167.root";
#2nd
FileNameOpenData5b = "../filterTree/subTree_80XRereco_Run2016F_GoldenJSON_RunGe278167.root";
#3d part G and H
FileNameOpenData6 = "../filterTree/subTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root";
FileNameOpenData7 = "../filterTree/subTree_80XRereco_Run2016H_GoldenJSON_Run284036to284044.root";
FileNameOpenData8 = "../filterTree/subTree_80XRereco_Run2016H_v2_GoldenJSON_Run281613to284035.root";
#FileNameOpenData8 = "../filterTree/subTree_80XRereco_Run2016H_v2_GoldenJSON_Run281613to284035_test.root";

FileNameOpen1 = FileNameOpenData1;
if DataOpen == "0":
   FileNameOpen1 = FileNameOpenMC1;


FileNameOutMC =   "TnP_"+isTrigger+"_"+MCType  +"_"+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80X_Run2016_Run271036to274093_TrigStudy.root":
   FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_RunLt274094_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80X_Run2016_Run275757to275783_TrigStudy.root":
   FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_Fill5043_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80X_Run2016_Run274094to275000_TrigStudy.root":
   FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_Run274094to275000_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80X_Run2016_Run275001to275783_TrigStudy.root":
   FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_Run275001to275783_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80X_Run2016_Run275784to276500_TrigStudy.root":
   FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_Run275784to276500_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80X_Run2016_Run276501to276811_TrigStudy.root":
   FileNameOutData = isTrigger+"_"+DataType+"_PTvsETA_Run276501to276811_RAW.root";
   
 
FileNameOut = FileNameOutData;
if DataOpen == "0": 
   FileNameOut = FileNameOutMC;

FileNameOutMCISO = "TnP_"+isMuonSel+"_IDandISO_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
FileNameOutDataISO = "TnP_"+isMuonSel+"_IDandISO_"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
 
FileNameOutISO = FileNameOutDataISO;
if DataOpen == "0": 
   FileNameOutISO = FileNameOutMCISO;

print '***********************************'
print 'FileNameOpen1   = , %s.' % FileNameOpen1
print 'FileNameOut    = , %s.' % FileNameOut
print 'FileNameOutISO = , %s.' % FileNameOutISO
print '***********************************'

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.TnP_Muon_ID = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    ## Input, output 
    InputFileNames = cms.vstring(
                                 "file:"+FileNameOpen1,
                                 "file:"+FileNameOpenData2,  
                                 "file:"+FileNameOpenData3,  
                                 "file:"+FileNameOpenData4,  
                                 "file:"+FileNameOpenData5a,  
                                 "file:"+FileNameOpenData5b,  
                                 #
                                 #"file:"+FileNameOpenData6,
                                 #"file:"+FileNameOpenData7,
                                 #"file:"+FileNameOpenData8,
                                 #
                                 #"root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_25ns_DY_Spring15/150707_143420/0000/tnp_MC_100.root",
                                 ), ## can put more than one
    ## copy locally to be faster: xrdcp root://eoscms//eos/cms/store/cmst3/user/botta/TnPtrees/tnpZ_Data.190456-193557.root $PWD/tnpZ_Data.190456-193557.root
    ## and then set InputFileNames = cms.vstring("tnpZ_Data.190456-193557.root"), 
    #OutputFileName = cms.string("TnP_Muon_ID_Simple_Data.root"),
    OutputFileName = cms.string(FileNameOut),
    InputTreeName = cms.string("fitter_tree"), 
    InputDirectoryName = cms.string("tpTree"),  
    ## Variables for binning
    Variables = cms.PSet(
        mass   = cms.vstring("Tag-muon Mass", "76", "125", "GeV/c^{2}"),
        pt     = cms.vstring("muon p_{T}", "0", "1000", "GeV/c"),
        l1pt     = cms.vstring("muon l1 p_{T}", "0", "1000", "GeV/c"),
        l2pt     = cms.vstring("muon l2 p_{T}", "0", "1000", "GeV/c"),
        l3pt     = cms.vstring("muon l3 p_{T}", "0", "1000", "GeV/c"),
        l1q     = cms.vstring("l1 quality", "0", "1000", " "),
        eta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        phi = cms.vstring("muon |#phi|", "-3.142", "3.142", ""),
        pair_dPhiEndcapDeg = cms.vstring("muon d#phi in endcap", "0.", "180.", ""),
        pair_dz = cms.vstring("#Deltaz between two muons", "-100", "100", "cm"),
        pair_deltaR = cms.vstring("#DeltaR between two muons", "-100", "100", "cm"),
        tag_nVertices = cms.vstring("Tag nVertices", "0.", "100.", ""),
        dB     = cms.vstring("dxy muon", "0", "2", "cm"),
        dzPV     = cms.vstring("dz PV muon", "-5", "5", "cm"),
        tag_pt     = cms.vstring("tag muon p_{T}", "0", "1000", "GeV/c"),
        combRelIsoPF04dBeta = cms.vstring("PF Combined Relative Iso", "-100", "99999", ""),
        tag_combRelIsoPF04dBeta = cms.vstring("PF Combined Relative Iso for tag muon", "-100", "99999", ""),
    ),
    ## Flags you want to use to define numerator and possibly denominator
    Categories = cms.PSet(
        PF = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        IsoMu24_eta2p1 = cms.vstring("IsoMu24_eta2p1 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu24_eta2p1 = cms.vstring("IsoMu24_eta2p1 tag Muon", "dummy[pass=1,fail=0]"),
        Tight2012 = cms.vstring("Tight2012 Muon", "dummy[pass=1,fail=0]"),
        #tag_Tight2012 = cms.vstring("Tight 2012 tag Muon", "dummy[pass=1,fail=0]"), #this variable is not included in tag muon
        Medium = cms.vstring("Medium Muon", "dummy[pass=1,fail=0]"),
        tag_IsoTkMu20 = cms.vstring("tag_IsoTkMu20 tag Muon", "dummy[pass=1,fail=0]"),
        IsoMu18 = cms.vstring("IsoMu18  probe Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu18 = cms.vstring("IsoTkMu18  probe Muon", "dummy[pass=1,fail=0]"),
        IsoMu20 = cms.vstring("IsoMu20 probe Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu20 = cms.vstring("IsoTkMu20 probe Muon", "dummy[pass=1,fail=0]"),
        IsoMu22 = cms.vstring("IsoMu22 probe Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu22 = cms.vstring("IsoTkMu22 probe Muon", "dummy[pass=1,fail=0]"),
        IsoMu24 = cms.vstring("IsoMu24 probe Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu24 = cms.vstring("IsoTkMu24 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoTkMu18 = cms.vstring("tag_IsoTkMu18 tag Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu20 = cms.vstring("tag_IsoMu20 tag Muon", "dummy[pass=1,fail=0]"),
        #Double Trigger Info
        DoubleIsoMu17Mu8_IsoMu17leg = cms.vstring("DoubleIsoMu17Mu8_IsoMu17leg Muon", "dummy[pass=1,fail=0]"),
        Mu23_TrkIsoVVL = cms.vstring("Mu23_TrkIsoVVL Muon", "dummy[pass=1,fail=0]"),
        DoubleIsoMu17Mu8_IsoMu8leg = cms.vstring("DoubleIsoMu17Mu8_IsoMu8leg Muon", "dummy[pass=1,fail=0]"),
        DoubleIsoMu17TkMu8_IsoMu8leg = cms.vstring("DoubleIsoMu17TkMu8_IsoMu8leg Muon", "dummy[pass=1,fail=0]"),
        #DoubleIsoMu17Mu8dZ_Mu17leg = cms.vstring("DoubleIsoMu17Mu8dZ_Mu17leg Muon", "dummy[pass=1,fail=0]"),
        #DoubleIsoMu17TkMu8dZ_Mu17 = cms.vstring("DoubleIsoMu17TkMu8dZ_Mu17 Muon", "dummy[pass=1,fail=0]"),
    ),
    ## PDF for signal and background (double voigtian + exponential background)
    PDFs = cms.PSet(
        vpvPlusExpo = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
    ),

    Expressions = cms.PSet(
        Trigger_IsoMu20orIsoTkMu20_Var = cms.vstring ("Trigger_IsoMu20orIsoTkMu20_Var", "IsoMu20==1 || IsoTkMu20==1", "IsoMu20", "IsoTkMu20"),
        Trigger_IsoMu22orIsoTkMu22_Var = cms.vstring ("Trigger_IsoMu22orIsoTkMu22_Var", "IsoMu22==1 || IsoTkMu22==1", "IsoMu22", "IsoTkMu22"),
        Trigger_IsoMu24orIsoTkMu24_Var = cms.vstring ("Trigger_IsoMu24orIsoTkMu24_Var", "IsoMu24==1 || IsoTkMu24==1", "IsoMu24", "IsoTkMu24"),
        Trigger_IsoMu18orIsoTkMu18_Var = cms.vstring ("Trigger_IsoMu18orIsoTkMu18_Var", "IsoMu18==1 || IsoTkMu18==1", "IsoMu18", "IsoTkMu18"),
        Trigger_IsoMu8orIsoTkMu8_Var = cms.vstring ("Trigger_IsoMu8orIsoTkMu8_Var", "DoubleIsoMu17Mu8_IsoMu8leg==1 || DoubleIsoMu17TkMu8_IsoMu8leg==1", "DoubleIsoMu17Mu8_IsoMu8leg", "DoubleIsoMu17TkMu8_IsoMu8leg"),
        Trigger_IsoMu23_l1pt20_Var = cms.vstring ("Trigger_IsoMu23_l1pt20_Var", "DoubleIsoMu17Mu8_IsoMu17leg==1 && l1pt>=20 && l2pt >=10 && l3pt>=23 && l1q>=12", "DoubleIsoMu17Mu8_IsoMu17leg", "l1pt", "l2pt", "l3pt", "l1q"),
        Trigger_IsoMu23_l1pt23_Var = cms.vstring ("Trigger_IsoMu23_l1pt23_Var", "DoubleIsoMu17Mu8_IsoMu17leg==1 && l1pt>=23 && l2pt >=10 && l3pt>=23 && l1q>=12", "DoubleIsoMu17Mu8_IsoMu17leg", "l1pt", "l2pt", "l3pt", "l1q"),
        Trigger_IsoMu12_Var = cms.vstring ("Trigger_IsoMu12_Var", "DoubleIsoMu17Mu8_IsoMu8leg==1 && l1pt>=5 && l2pt >=5 && l3pt>=12 && l1q>=12", "DoubleIsoMu17Mu8_IsoMu8leg", "l1pt", "l2pt", "l3pt", "l1q"),
        #Trigger_IsoMu17orIsoTkMu17_Var = cms.vstring ("Trigger_IsoMu17orIsoTkMu17_Var", "DoubleIsoMu17Mu8dZ_Mu17leg==1 || DoubleIsoMu17TkMu8dZ_Mu17==1", "DoubleIsoMu17Mu8dZ_Mu17leg", " DoubleIsoMu17TkMu8dZ_Mu17"),
    ),
    ## Cuts: name, variable, cut threshold
    Cuts = cms.PSet(
        Trigger_IsoMu20orIsoTkMu20 = cms.vstring("Trigger_IsoMu20orIsoTkMu20", "Trigger_IsoMu20orIsoTkMu20_Var", "0.5"),
        Trigger_IsoMu22orIsoTkMu22 = cms.vstring("Trigger_IsoMu22orIsoTkMu22", "Trigger_IsoMu22orIsoTkMu22_Var", "0.5"),
        Trigger_IsoMu24orIsoTkMu24 = cms.vstring("Trigger_IsoMu24orIsoTkMu24", "Trigger_IsoMu24orIsoTkMu24_Var", "0.5"),
        Trigger_IsoMu18orIsoTkMu18 = cms.vstring("Trigger_IsoMu18orIsoTkMu18", "Trigger_IsoMu18orIsoTkMu18_Var", "0.5"),
        Trigger_IsoMu8orIsoTkMu8 = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "Trigger_IsoMu8orIsoTkMu8_Var", "0.5"),
        Trigger_IsoMu23_l1pt20 = cms.vstring("Trigger_IsoMu23_l1pt20", "Trigger_IsoMu23_l1pt20_Var", "0.5"),
        Trigger_IsoMu23_l1pt23 = cms.vstring("Trigger_IsoMu23_l1pt23", "Trigger_IsoMu23_l1pt23_Var", "0.5"),
        Trigger_IsoMu12 = cms.vstring("Trigger_IsoMu12", "Trigger_IsoMu12_Var", "0.5"),
        #Trigger_IsoMu17orIsoTkMu17 = cms.vstring("Trigger_IsoMu17orIsoTkMu17", "Trigger_IsoMu17orIsoTkMu17_Var", "0.5"),
    ),
    ## What to fit
    Efficiencies = cms.PSet(
        ##############
        ##############
        Trigger_ptVSeta = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu24orIsoTkMu24", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu17orIsoTkMu17", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu23_l1pt20", "above"), ## variable is above cut value 
            EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu23_l1pt23", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu12", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring(isTrigger, "pass"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                # binning for Mu17,  
                #pt = cms.vdouble(10, 15, 16, 17, 18, 19, 20, 25, 30, 40, 60, 100, 200),
                # binning for Mu23  
                pt = cms.vdouble(10, 21, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200),
                # binning for Mu24  
                #pt = cms.vdouble(10, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200),
                # binning for Mu8 
                #pt = cms.vdouble(10, 13, 16, 20, 25, 30, 40, 60, 100, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                Tight2012 = cms.vstring("pass"),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.15),
                pair_dPhiEndcapDeg = cms.vdouble(80., 1000.),        
                pair_deltaR = cms.vdouble(0.3, 1000.),        
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

#        Trigger_ptVSeta_ptLt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu24orIsoTkMu24", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu17orIsoTkMu17", "above"), ## variable is above cut value 
#            EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu23_l1pt20", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu23_l1pt23", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu12", "above"), ## variable is above cut value
#            #EfficiencyCategoryAndState = cms.vstring(isTrigger, "pass"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                # binning for Mu17,  
#                #pt = cms.vdouble(10, 15, 16, 17, 18, 19, 20, 25, 30, 40, 60, 100, 200),
#                #binning for Mu23  
#                pt = cms.vdouble(10, 21, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200),
#                # binning for Mu24  
#                #pt = cms.vdouble(10, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200),
#                # binning for Mu8 
#                #pt = cms.vdouble(10, 13, 16, 20, 25, 30, 40, 60, 100, 200),
#                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
#                Tight2012 = cms.vstring("pass"),
#                combRelIsoPF04dBeta = cms.vdouble(0., 0.15),
#                dB = cms.vdouble(0., 0.01),
#                dzPV = cms.vdouble(-0.1, 0.1),
#                pair_dPhiEndcapDeg = cms.vdouble(80., 1000.),        
#                pair_deltaR = cms.vdouble(0.3, 1000.),        
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),
#
#        Trigger_ptVSeta_ptGt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu24orIsoTkMu24", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu17orIsoTkMu17", "above"), ## variable is above cut value 
#            EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu23_l1pt20", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu23_l1pt23", "above"), ## variable is above cut value 
#            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu12", "above"), ## variable is above cut value
#            #EfficiencyCategoryAndState = cms.vstring(isTrigger, "pass"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                # binning for Mu17,  
#                #pt = cms.vdouble(10, 15, 16, 17, 18, 19, 20, 25, 30, 40, 60, 100, 200),
#                #binning for Mu23  
#                pt = cms.vdouble(10, 21, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200),
#                # binning for Mu22,24  
#                #pt = cms.vdouble(10, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200),
#                ## binning for Mu8 
#                #pt = cms.vdouble(10, 13, 16, 20, 25, 30, 40, 60, 100, 200),
#                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
#                Tight2012 = cms.vstring("pass"),
#                combRelIsoPF04dBeta = cms.vdouble(0., 0.15),
#                dB = cms.vdouble(0., 0.02),
#                dzPV = cms.vdouble(-0.1, 0.1),
#                pair_dPhiEndcapDeg = cms.vdouble(80., 1000.),        
#                pair_deltaR = cms.vdouble(0.3, 1000.),        
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),


        ##############
        ##############
    ),
    ## How to do the fit
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(40),
    saveDistributionsPlot = cms.bool(False),
    NumCPU = cms.uint32(1), ## leave to 1 for now, RooFit gives funny results otherwise
    SaveWorkspace = cms.bool(False),
)

#### Slighly different configuration for isolation, where the "passing" is defined by a cut
    

process.p1 = cms.Path(process.TnP_Muon_ID)
