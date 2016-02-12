import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo"

#isMuonSel = 'Tight2012'
isMuonSel = 'Medium'

DataOpen ="1"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

#Bunch = "50ns";
#DataType = "Run2015B";

Bunch = "25ns";
DataType = "Run2015D";


FileNameOpenMC = "tnp_"+Bunch+MCType+"_v3_PUlike"+DataType+"_"+Bunch+".root";
if MCType == "DY_madgraph":
  FileNameOpenMC1 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_part1.root";
  FileNameOpenMC2 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_part2.root";

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
   FileNameOpen2 = FileNameOpenMC2;

FileNameOutMCISO = "TnP_"+isMuonSel+"_IDandISO_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"1Deff_RAW.root";
FileNameOutDataISO = "TnP_"+isMuonSel+"_IDandISO_"+DataType+"_"+Bunch+"_1Deff_RAW.root";

FileNameOut = "TnP_"+isMuonSel+"_ID_"+DataType+"_"+Bunch+"_1Deff_RAW.root";
 
FileNameOutISO = FileNameOutDataISO;
if DataOpen == "0": 
   FileNameOutISO = FileNameOutMCISO;

print '***********************************'
print 'FileNameOpen1   = , %s.' % FileNameOpen1
print 'FileNameOpen2   = , %s.' % FileNameOpen2
print 'FileNameOpen3   = , %s.' % FileNameOpen3
print 'FileNameOpen4   = , %s.' % FileNameOpen4
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
        Tight2012 = cms.vstring("Tight2012 Muon", "dummy[pass=1,fail=0]"),
        #tag_Tight2012 = cms.vstring("Tight 2012 tag Muon", "dummy[pass=1,fail=0]"), #this variable is not included in tag muon
        Medium = cms.vstring("Medium Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu20 = cms.vstring("tag_IsoMu20 tag Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu20 = cms.vstring("IsoTkMu20 probe Muon", "dummy[pass=1,fail=0]"),
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

    Efficiencies = cms.PSet(
        ########
        tag_nVertices_Medium_ptGt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(20, 5000.),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(20, 1000),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
        ########
########

    ),
    ## How to do the fit
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(40),
    saveDistributionsPlot = cms.bool(False),
    NumCPU = cms.uint32(1), ## leave to 1 for now, RooFit gives funny results otherwise
    SaveWorkspace = cms.bool(False),
)

#### Slighly different configuration for isolation, where the "passing" is defined by a cut
process.TnP_Muon_Iso = process.TnP_Muon_ID.clone(
    OutputFileName = cms.string(FileNameOutISO),
    ## More variables
    #Variables = process.TnP_Muon_ID.Variables.clone(),
    ## Flags you want to use to define numerator and possibly denominator
    
    Expressions = cms.PSet(
        MediumISO_gt20Var = cms.vstring ("MediumISO_gt20Var", "Medium==1 && abs(dB)<0.02 && abs(dzPV)<0.1 && combRelIsoPF04dBeta<0.15", "Medium", "dB","dzPV","combRelIsoPF04dBeta"),
        MediumISO_lt20Var = cms.vstring ("MediumISO_lt20Var", "Medium==1 && abs(dB)<0.01 && abs(dzPV)<0.1 && combRelIsoPF04dBeta<0.15", "Medium", "dB","dzPV","combRelIsoPF04dBeta"),
        MediumISO_Var = cms.vstring ("MediumISO_Var", "Medium==1 && combRelIsoPF04dBeta<0.15", "Medium", "combRelIsoPF04dBeta")
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
    ),

    ## What to fit
    Efficiencies = cms.PSet(
        Medium_ISO_tag_nVertices = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20., 30.),
                pt     = cms.vdouble( 5, 10, 20, 5000 ),
                #Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                eta = cms.vdouble( -2.4, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

#        Medium_ISO_tag_nVertices_ptLt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_lt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                pt     = cms.vdouble( 10,  20 ),
#                eta = cms.vdouble( -2.4, 2.4 ),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),
#
#        Medium_ISO_tag_nVertices_ptGt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_gt20", "above"), ## variable is above cut value
#            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                pt     = cms.vdouble( 20, 5000 ),
#                eta = cms.vdouble( -2.4, 2.4 ),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),

        ##############
        ##############

        Medium_ISO_pt = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(5, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
                eta = cms.vdouble( -2.4, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

#        Medium_ISO_pt_ptLt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_lt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                pt = cms.vdouble(3, 5, 7, 9, 10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                eta = cms.vdouble( -2.4, 2.4 ),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),
#
#        Medium_ISO_pt_ptGt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_gt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                pt = cms.vdouble(3, 5, 7, 9, 10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                eta = cms.vdouble( -2.4, 2.4 ),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),

        ##############
        ##############

        Medium_ISO_eta = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.0, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
                pt = cms.vdouble(10,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

#        Medium_ISO_eta_ptLt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_lt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.0, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
#                pt = cms.vdouble(10,20),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),
#
#
#        Medium_ISO_eta_ptGt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_gt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.0, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                pt = cms.vdouble(20,1000),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),
        ##############
        Medium_ISO_phi = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142),
                eta = cms.vdouble( -2.4, 2.4),
                #Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

#        Medium_ISO_phi_ptLt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_lt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142),
#                eta = cms.vdouble( -2.4, 2.4),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                pt = cms.vdouble(10,20),
#            ),
#            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
#        ),
#
#
#        Medium_ISO_phi_tight_ptGt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring("MediumISO_gt20", "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142),
#                eta = cms.vdouble( -2.4, 2.4),
#                #Medium = cms.vstring("pass"),
#                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                tag_pt = cms.vdouble(20, 5000.),
#                pt = cms.vdouble(20,1000),
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

#process.p1 = cms.Path(process.TnP_Muon_ID)
process.p2 = cms.Path(process.TnP_Muon_Iso)
