import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo";
#FitFunction = "DoubleGaussPlusExpo";

#isMuonSel = 'Tight2012'
isMuonSel = 'Medium';

DataOpen ="1"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

#Bunch = "50ns";
#DataType = "Run2015B";

Bunch = "25ns";
DataType = "Run2015D";


FileNameOpenMC1 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_LikeRun2015D.root";

FileNameOpenData1 = "../filterTree/subTree_80X_Run2016B_DCSOnly_Run273423_273450_IdStudy.root";

FileNameOpen1 = FileNameOpenData1;
if DataOpen == "0": 
   FileNameOpen1 = FileNameOpenMC1;

FileNameOutMC = "TnP_"+isMuonSel+"_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_"+FitFunction+"_M_RAW.root";
FileNameOutData = "TnP_"+isMuonSel+"_"+DataType+"_"+Bunch+"_PTvsETA_"+FitFunction+"_M_RAW.root";
 
FileNameOut = FileNameOutData;
if DataOpen == "0": 
   FileNameOut = FileNameOutMC;

FileNameOutMCISO = "TnP_TightISO_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
FileNameOutDataISO = "TnP_TightISO_"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
 
FileNameOutISO = FileNameOutDataISO;
if DataOpen == "0": 
   FileNameOutISO = FileNameOutMCISO;

print '***********************************'
print 'FileNameOpen1   = , %s.' % FileNameOpen1
print 'FileNameOut    = , %s.' % FileNameOut
print 'FileNameOutISO = , %s.' % FileNameOutISO
print 'Check that for Run2015D you open 2 files and for MC 1 file'
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
        Tight2012 = cms.vstring("Tight2012 Muon", "dummy[pass=1,fail=0]"),
        #tag_Tight2012 = cms.vstring("Tight 2012 tag Muon", "dummy[pass=1,fail=0]"), #this variable is not included in tag muon
        Medium = cms.vstring("Medium Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu20 = cms.vstring("tag_IsoMu20 tag Muon", "dummy[pass=1,fail=0]"),
        IsoMu18 = cms.vstring("IsoMu18  probe Muon", "dummy[pass=1,fail=0]"),
        IsoMu20 = cms.vstring("IsoMu20 probe Muon", "dummy[pass=1,fail=0]"),
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
        DoubleGaussPlusExpo = cms.vstring(
            "Gaussian::signal1(mass, mean1[90,80,100], sigma1[2., 1., 5.])",
            "Gaussian::signal2(mass, mean1[90,80,100], sigma2[5.,1.,10.])",# the same mean1 as in signal1
            "SUM::signal(vFrac[0.8,0.5,1.]*signal1, signal2)",
            #"Chebychev::backgroundPass(mass, {cPass1[-0.7,-1,1],cPass2[0.3,-1,1]})",
            #"Chebychev::backgroundFail(mass, {cFail1[-0.7,-1,1],cFail2[0.2,-1,1]})",
            "Exponential::backgroundPass(mass, lp[-0.03,-1,1.])",
            "Exponential::backgroundFail(mass, lf[-0.13,-1,1.])",
            #"Chebychev::backgroundPass(mass, {cPass1[-0.7,-1,1],cPass2[0.3,-1,1],cPass3[0.,-1,1]})",
            #"Chebychev::backgroundFail(mass, {cFail1[-0.7,-1,1],cFail2[0.2,-1,1],cFail3[0.,-1,1]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
    ),
    Expressions = cms.PSet(
        ID_Medium_gt20Var = cms.vstring ("ID_Medium_gt20Var", "Medium==1 && abs(dB)<0.02 && abs(dzPV)<0.1", "Medium", "dB","dzPV"),
        ID_Medium_lt20Var = cms.vstring ("ID_Medium_lt20Var", "Medium==1 && abs(dB)<0.01 && abs(dzPV)<0.1", "Medium", "dB","dzPV"),
        ID_Medium_Var = cms.vstring ("ID_Medium_Var", "Medium==1", "Medium"),
    ),
    ## Cuts: name, variable, cut threshold
    Cuts = cms.PSet(
        ID_Medium_gt20 = cms.vstring("ID_Medium_gt20", "ID_Medium_gt20Var", "0.5"),
        ID_Medium_lt20 = cms.vstring("ID_Medium_lt20", "ID_Medium_lt20Var", "0.5"),
        ID_Medium = cms.vstring("ID_Medium", "ID_Medium_Var", "0.5"),
    ),
    ## What to fit
    Efficiencies = cms.PSet(
        ########
     #   tag_nVertices_Medium = cms.PSet(
     #      EfficiencyCategoryAndState = cms.vstring("ID_Medium", "above"),
     #       UnbinnedVariables = cms.vstring("mass"),
     #       BinnedVariables = cms.PSet(
     #           tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
     #           tag_pt = cms.vdouble(20, 5000.),
     #           eta = cms.vdouble(-2.4, 2.4),
     #           pt = cms.vdouble(20, 5000),
     #           tag_nVertices = cms.vdouble(0., 10., 15., 20., 30), # for GI or CI MC only
     #       ),
     #       BinToPDFmap = cms.vstring(FitFunction)
     #   ),
        ##############

        Medium_ID_ptVSeta = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("ID_Medium", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                # detailed bins -> not enought stat. for MuonID
                #pt = cms.vdouble(3, 5, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #less detailed binning
                #pt = cms.vdouble(5, 8, 10, 13, 16),#test
                #pt = cms.vdouble(5, 8, 10, 13, 16, 20, 25, 30, 35, 40, 60, 100, 200),
                pt = cms.vdouble(10, 20, 30, 50, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),

        Medium_ID_ptVSeta_ptLt20 = cms.PSet(
           UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("ID_Medium_lt20", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(5, 8, 10, 13, 16, 20, 25, 30, 35, 40, 60, 100, 200),
                #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                pt = cms.vdouble(10, 20, 30, 50, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),

        Medium_ID_ptVSeta_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("ID_Medium_gt20", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(5, 8, 10, 13, 16, 20, 25, 30, 35, 40, 60, 100, 200),
                #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                pt = cms.vdouble(10, 20, 30, 50, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),
        ########
        ########

    ),
    ## How to do the fit
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(40),
    #binsForFit = cms.uint32(50),
    saveDistributionsPlot = cms.bool(False),
    NumCPU = cms.uint32(1), ## leave to 1 for now, RooFit gives funny results otherwise
    SaveWorkspace = cms.bool(False),
)

#### Slighly different configuration for isolation, where the "passing" is defined by a cut
process.TnP_Muon_Iso = process.TnP_Muon_ID.clone(
    #OutputFileName = cms.string("TnP_Muon_Iso_Simple_Data.root"),
    OutputFileName = cms.string(FileNameOutISO),
    ## More variables
    Variables = process.TnP_Muon_ID.Variables.clone(
        combRelIsoPF04dBeta = cms.vstring("PF Combined Relative Iso", "-100", "99999", ""),
        tag_nVertices       = cms.vstring("N(vertices)", "0", "99", ""),
        #dB     = cms.vstring("dxy muon", "0", "2", "cm"),
        #dzPV     = cms.vstring("dz PV muon", "-5", "5", "cm"),
    ),
    ## Flags you want to use to define numerator and possibly denominator
    Categories = cms.PSet(
        PF = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        Tight2012 = cms.vstring("Tight2012 Muon", "dummy[pass=1,fail=0]"),
        #tag_Tight2012 = cms.vstring("Tight 2012 tag Muon", "dummy[pass=1,fail=0]"), #this variable is not included in tag muon
        Medium = cms.vstring("Medium Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu20 = cms.vstring("tag_IsoMu20 tag Muon", "dummy[pass=1,fail=0]"),
        IsoMu18 = cms.vstring("IsoMu18  probe Muon", "dummy[pass=1,fail=0]"),
        IsoMu20 = cms.vstring("IsoMu20 probe Muon", "dummy[pass=1,fail=0]"),
    ),    
    Expressions = cms.PSet(

        MediumISO_gt20Var = cms.vstring ("MediumISO_gt20Var", "Medium==1 && abs(dB)<0.02 && abs(dzPV)<0.1 && combRelIsoPF04dBeta<0.15", "Medium", "dB","dzPV","combRelIsoPF04dBeta"),
        MediumISO_lt20Var = cms.vstring ("MediumISO_lt20Var", "Medium==1 && abs(dB)<0.01 && abs(dzPV)<0.1 && combRelIsoPF04dBeta<0.15", "Medium", "dB","dzPV","combRelIsoPF04dBeta"),
        MediumISO_Var = cms.vstring ("MediumISO_Var", "Medium==1 && combRelIsoPF04dBeta<0.15", "Medium", "combRelIsoPF04dBeta"),
        ISOTight_Var = cms.vstring ("ISOTight_Var", "combRelIsoPF04dBeta<0.15", "combRelIsoPF04dBeta"),
    ),
    ## Cuts: name, variable, cut threshold
    Cuts = cms.PSet(
        PFIsoLoose = cms.vstring("PFIsoLoose" ,"combRelIsoPF04dBeta", "0.25"),
        PFIsoTight = cms.vstring("PFIsoTight" ,"combRelIsoPF04dBeta", "0.15"),
        #PFIsoLoose = cms.vstring("PFIsoLoose" ,"combRelIsoPF04dBeta", "0.20"), ## 8 TeV data cut
        #PFIsoTight = cms.vstring("PFIsoTight" ,"combRelIsoPF04dBeta", "0.12"), ## 8 TeV data cut
        MediumISO_gt20 = cms.vstring("MediumISO_gt20", "MediumISO_gt20Var", "0.5"),
        MediumISO_lt20 = cms.vstring("MediumISO_lt20", "MediumISO_lt20Var", "0.5"),
        MediumISO = cms.vstring("MediumISO", "MediumISO_Var", "0.5"),
        ISOTight = cms.vstring("ISOTight", "ISOTight_Var", "0.5"),
    ),
    ## What to fit
    Efficiencies = cms.PSet(
        ##############
        ##############

        Medium_ISO_ptVSeta = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("ISOTight", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                # detailed bins -> not enought stat. for MuonID
                pt = cms.vdouble(3, 5, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #less detailed binning
                #pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 60, 100, 200),
                #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),

        Medium_ISO_ptVSeta_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("ISOTight", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(3, 5, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),

        Medium_ISO_ptVSeta_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("ISOTight", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(3, 5, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),

        ##############
        ##############
    ),
)

process.p1 = cms.Path(process.TnP_Muon_ID)
#process.p2 = cms.Path(process.TnP_Muon_Iso)
