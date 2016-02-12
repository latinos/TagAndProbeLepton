import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo"

#isMuonSel = 'Tight2012'
isMuonSel = 'Medium'

## Tag muon is always matched to tag_IsoMu20
#isTrigger = 'IsoMu18'
#isTrigger = 'IsoTkMu20'
#isTrigger = 'DoubleIsoMu17Mu8_IsoMu17leg'
#isTrigger = 'DoubleIsoMu17Mu8_IsoMu8leg'
#isTrigger = 'DoubleIsoMu17TkMu8_IsoMu8leg'# this is correct for IsoTkMu8leg

isTrigger = 'IsoMu18orIsoTkMu20' ## you have to change efficiency input yourself for this mode
#isTrigger = 'IsoMu8orIsoTkMu8leg'  ## you have to change efficiency input yourself for this mode

DataOpen ="1"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

#Bunch = "50ns";
#DataType = "Run2015B";

Bunch = "25ns";
DataType = "Run2015D";

FileNameOpenMC1 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_LikeRun2015D.root";

FileNameOpenData1 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part1.root";
FileNameOpenData2 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part2.root";
FileNameOpenData3 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part3.root";
FileNameOpenData4 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part4.root";

FileNameOpen1 = FileNameOpenData1;
FileNameOpen2 = FileNameOpenData2;
FileNameOpen3 = FileNameOpenData3;
FileNameOpen4 = FileNameOpenData4;
if DataOpen == "0":
   FileNameOpen1 = FileNameOpenMC1;


FileNameOutMC =   "TnP_"+isTrigger+"_"+MCType  +"_"+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
FileNameOutData = "TnP_"+isTrigger+"_"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
 
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
print 'FileNameOpen2   = , %s.' % FileNameOpen2
print 'FileNameOpen3   = , %s.' % FileNameOpen3
print 'FileNameOpen4   = , %s.' % FileNameOpen4
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
                                 "file:"+FileNameOpen2,
                                 "file:"+FileNameOpen3, # only for Data  
                                 "file:"+FileNameOpen4, # only for Data 
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
        eta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        phi = cms.vstring("muon |#phi|", "-3.142", "3.142", ""),
        pair_dz = cms.vstring("#Deltaz between two muons", "-100", "100", "cm"),
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
        IsoTkMu20 = cms.vstring("IsoTkMu20 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoTkMu18 = cms.vstring("tag_IsoTkMu18 tag Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu20 = cms.vstring("tag_IsoMu20 tag Muon", "dummy[pass=1,fail=0]"),
        #Double Trigger Info
        DoubleIsoMu17Mu8_IsoMu17leg = cms.vstring("DoubleIsoMu17Mu8_IsoMu17leg Muon", "dummy[pass=1,fail=0]"),
        DoubleIsoMu17Mu8_IsoMu8leg = cms.vstring("DoubleIsoMu17Mu8_IsoMu8leg Muon", "dummy[pass=1,fail=0]"),
        DoubleIsoMu17TkMu8_IsoMu8leg = cms.vstring("DoubleIsoMu17TkMu8_IsoMu8leg Muon", "dummy[pass=1,fail=0]"),
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
        Trigger_IsoMu18orIsoTkMu20_Var = cms.vstring ("Trigger_IsoMu18orIsoTkMu20_Var", "IsoMu18==1 || IsoTkMu20==1", "IsoMu18", "IsoTkMu20"),
        Trigger_IsoMu8orIsoTkMu8_Var = cms.vstring ("Trigger_IsoMu8orIsoTkMu8_Var", "DoubleIsoMu17Mu8_IsoMu8leg==1 || DoubleIsoMu17TkMu8_IsoMu8leg==1", "DoubleIsoMu17Mu8_IsoMu8leg", "DoubleIsoMu17TkMu8_IsoMu8leg"),
        MediumISO_gt20Var = cms.vstring ("MediumISO_gt20Var", "Medium==1 && abs(dB)<0.02 && abs(dzPV)<0.1 && combRelIsoPF04dBeta<0.15", "Medium", "dB","dzPV","combRelIsoPF04dBeta"),
        MediumISO_lt20Var = cms.vstring ("MediumISO_lt20Var", "Medium==1 && abs(dB)<0.01 && abs(dzPV)<0.1 && combRelIsoPF04dBeta<0.15", "Medium", "dB","dzPV","combRelIsoPF04dBeta"),
        MediumISO_Var = cms.vstring ("MediumISO_Var", "Medium==1 && combRelIsoPF04dBeta<0.15", "Medium", "combRelIsoPF04dBeta")
    ),
    ## Cuts: name, variable, cut threshold
    Cuts = cms.PSet(
        MediumISO_gt20 = cms.vstring("MediumISO_gt20", "MediumISO_gt20Var", "0.5"),
        MediumISO_lt20 = cms.vstring("MediumISO_lt20", "MediumISO_lt20Var", "0.5"),
        MediumISO = cms.vstring("MediumISO", "MediumISO_Var", "0.5"),
        Trigger_IsoMu18orIsoTkMu20 = cms.vstring("Trigger_IsoMu18orIsoTkMu20", "Trigger_IsoMu18orIsoTkMu20_Var", "0.5"),
        Trigger_IsoMu8orIsoTkMu8 = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "Trigger_IsoMu8orIsoTkMu8_Var", "0.5"),
    ),
    ## What to fit
    Efficiencies = cms.PSet(
        ##############
        ##############
   #     Trigger_ptVSeta = cms.PSet(
   #         UnbinnedVariables = cms.vstring("mass"),
   #         EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu18orIsoTkMu20", "above"), ## variable is above cut value 
   #         #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "above"), ## variable is above cut value 
   #         #EfficiencyCategoryAndState = cms.vstring(isTrigger, "pass"), ## variable is above cut value 
   #         BinnedVariables = cms.PSet(
   #             # binning for Mu17, Mu18, Mu20 
   #             pt = cms.vdouble(10, 15, 16, 17, 18, 19, 20, 21, 22,  24,  26, 30, 35, 40, 60, 100, 200),
   #             eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
   #             # binning for Mu8 
   #             #pt = cms.vdouble(10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 60, 100, 200),
   #             #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
   #             Medium = cms.vstring("pass"),
   #             combRelIsoPF04dBeta = cms.vdouble(0., 0.15),
   #             tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
   #             tag_pt = cms.vdouble(20, 5000.),
   #         ),
   #         BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
   #     ),

        Trigger_ptVSeta_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu18orIsoTkMu20", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "above"), ## variable is above cut value 
            #EfficiencyCategoryAndState = cms.vstring(isTrigger, "pass"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                # binning for Mu17, Mu18, Mu20 
                pt = cms.vdouble(10, 15, 16, 17, 18, 19, 20, 21, 22,  24,  26, 30, 35, 40, 60, 100, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                # binning for Mu8 
                #pt = cms.vdouble(10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 60, 100, 200),
                #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                Medium = cms.vstring("pass"),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.15),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

    #    Trigger_ptVSeta_ptGt20 = cms.PSet(
    #        UnbinnedVariables = cms.vstring("mass"),
    #        EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu18orIsoTkMu20", "above"), ## variable is above cut value 
    #        #EfficiencyCategoryAndState = cms.vstring("Trigger_IsoMu8orIsoTkMu8", "above"), ## variable is above cut value 
    #        #EfficiencyCategoryAndState = cms.vstring(isTrigger, "pass"), ## variable is above cut value 
    #        BinnedVariables = cms.PSet(
    #            # binning for Mu17, Mu18, Mu20 
    #            pt = cms.vdouble(10, 15, 16, 17, 18, 19, 20, 21, 22,  24,  26, 30, 35, 40, 60, 100, 200),
    #            eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
    #            # binning for Mu8 
    #            #pt = cms.vdouble(10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 60, 100, 200),
    #            #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
    #            Medium = cms.vstring("pass"),
    #            combRelIsoPF04dBeta = cms.vdouble(0., 0.15),
    #            dB = cms.vdouble(0., 0.02),
    #            dzPV = cms.vdouble(-0.1, 0.1),
    #            tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
    #            tag_pt = cms.vdouble(20, 5000.),
    #        ),
    #        BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
    #    ),


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
