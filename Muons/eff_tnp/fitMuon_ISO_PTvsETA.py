import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo";
#FitFunction = "DoubleGaussPlusChebychev";

IsoType = "ISOTight";
#IsoType = "ISOFake";

isMuonSel = 'Tight'
#isMuonSel = 'Medium';

DataOpen ="1"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

#Bunch = "50ns";
#DataType = "Run2015B";

Bunch = "25ns";
DataType = "Run2015D";


FileNameOpenMC = "tnp_"+Bunch+MCType+"_PUlike"+DataType+"_"+Bunch+".root";
if MCType == "DY_madgraph":
  FileNameOpenMC1 = "/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_part1.root";

FileNameOpenData1 = "../filterTree/subTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root";
FileNameOpenData2 = "../filterTree/subTree_80XRereco_Run2016C_GoldenJSON_Run276098to276384.root";
FileNameOpenData3 = "../filterTree/subTree_80XRereco_Run2016D_GoldenJSON_Run276098to276384.root";
FileNameOpenData4 = "../filterTree/subTree_80XRereco_Run2016E_GoldenJSON_Run276098to276384.root";
FileNameOpenData5 = "../filterTree/subTree_80XRereco_Run2016F_GoldenJSON_Run276098to276384.root";
#2nd part G and H
FileNameOpenData6 = "../filterTree/subTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root";
FileNameOpenData7 = "../filterTree/subTree_80XRereco_Run2016H_GoldenJSON_Run284036to284044.root";
FileNameOpenData8 = "../filterTree/subTree_80XRereco_Run2016H_v2_GoldenJSON_Run281613to284035.root";

FileNameOpen1 = FileNameOpenData1;
if DataOpen == "0": 
   FileNameOpen1 = FileNameOpenMC1;

FileNameOutMCISO = "TnP_"+IsoType+"_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
FileNameOutDataISO = "TnP_"+IsoType+"_"+DataType+"_PTvsETA_RAW.root";
if FileNameOpenData1 == "../filterTree/subTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root":
   FileNameOutDataISO = IsoType+"_"+DataType+"_PTvsETA_Run2016B_RAW.root";
 
FileNameOutISO = FileNameOutDataISO;
if DataOpen == "0": 
   FileNameOutISO = FileNameOutMCISO;

print '***********************************'
print 'FileNameOpen1   = , %s.' % FileNameOpen1
#print 'FileNameOut    = , %s.' % FileNameOut
print 'FileNameOutISO = , %s.' % FileNameOutISO
#print 'Check that for Run2015D you open 2 files and for MC 1 file'
print '***********************************'

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

#from ROOT import  RooFit, RooRealVar, RooGaussian, RooChebychev, RooAddPdf, RooArgList, RooArgSet, RooDataSet, RooCategory, RooPlot
#from ROOT import RooFit, RooRealVar, RooGaussian, RooChebychev, RooAddPdf, RooArgList, RooArgSet, RooDataSet, RooCategory, RooPlot, TCanvas, gPad, RooSimultaneous, kDashed


process.TnP_Muon_ID = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    ## Input, output 
    InputFileNames = cms.vstring(
                                 #"file:"+FileNameOpen1,  
                                 #"file:"+FileNameOpenData2,
                                 #"file:"+FileNameOpenData3,
                                 #"file:"+FileNameOpenData4,
                                 #"file:"+FileNameOpenData5,
                                 #
                                 "file:"+FileNameOpenData6,
                                 "file:"+FileNameOpenData7,
                                 "file:"+FileNameOpenData8,
                                 #"root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_25ns_DY_Spring15/150707_143420/0000/tnp_MC_100.root",
                                 ), ## can put more than one
    ## copy locally to be faster: xrdcp root://eoscms//eos/cms/store/cmst3/user/botta/TnPtrees/tnpZ_Data.190456-193557.root $PWD/tnpZ_Data.190456-193557.root
    ## and then set InputFileNames = cms.vstring("tnpZ_Data.190456-193557.root"), 
    #OutputFileName = cms.string("TnP_Muon_ID_Simple_Data.root"),
    OutputFileName = cms.string(FileNameOutISO),
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
        DoubleGaussPlusChebychev = cms.vstring(
            "Gaussian::signal1(mass, mean1[90,80,100], sigma1[2.495])",
            "Gaussian::signal2(mass, mean1[90,80,100], sigma2[0.5,0.02,5])",# the same mean1 as in signal1
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            #"RooChebychev::backgroundPass(mass, cPass1[0,-1,1],cPass2[0,-1,1])",
            #"RooChebychev::backgroundFail(mass, cFail1[0,-1,1],cFail2[0,-1,1])",
            "Chebychev::backgroundPass(mass, {cPass1[0,-1,1],cPass2[0,-1,1]})",
            "Chebychev::backgroundFail(mass, {cFail1[0,-1,1],cFail2[0,-1,1]})",
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
    #OutputFileName = cms.string("TnP_Muon_Iso_Simple_Data.root"),
    OutputFileName = cms.string(FileNameOutISO),
    ## More variables
    #Variables = process.TnP_Muon_ID.Variables.clone(

    Expressions = cms.PSet(

        ISOTight_Var = cms.vstring ("ISOTight_Var", "combRelIsoPF04dBeta<0.15", "combRelIsoPF04dBeta"),
        ISOFake_Var = cms.vstring ("ISOFake_Var", "combRelIsoPF04dBeta<0.4", "combRelIsoPF04dBeta"),
        #ISOFakeTrk_Var = cms.vstring ("ISOFakeTrk_Var", "chargedHadIso03/pt<0.4", "chargedHadIso03"),

    ),
    ## Cuts: name, variable, cut threshold
    Cuts = cms.PSet(
        PFIsoLoose = cms.vstring("PFIsoLoose" ,"combRelIsoPF04dBeta", "0.25"),
        PFIsoTight = cms.vstring("PFIsoTight" ,"combRelIsoPF04dBeta", "0.15"),
        ISOTight = cms.vstring("ISOTight", "ISOTight_Var", "0.5"),
        ISOFake = cms.vstring("ISOFake", "ISOFake_Var", "0.5"),

    ),
    ## What to fit
    Efficiencies = cms.PSet(
        ##############
        ##############

        Tight_ISO_ptVSeta = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(IsoType, "above"), ## variable is above cut value 
           BinnedVariables = cms.PSet(
                # detailed bins -> not enought stat. for MuonID
                pt = cms.vdouble(10, 13, 16, 20, 25, 30, 40, 60, 100, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                Tight2012 = cms.vstring("pass"),
                #tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                #tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
        ),

#        Tight_ISO_ptVSeta_ptLt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#            EfficiencyCategoryAndState = cms.vstring(IsoType, "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                pt = cms.vdouble(10, 13, 16, 20, 25, 30, 40, 60, 100, 200),
#                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
#                Tight2012 = cms.vstring("pass"),
#                dB = cms.vdouble(0., 0.01),
#                dzPV = cms.vdouble(-0.1, 0.1),
#                #tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                #tag_pt = cms.vdouble(20, 5000.),
#            ),
#            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
#        ),
#
#        Tight_ISO_ptVSeta_ptGt20 = cms.PSet(
#            UnbinnedVariables = cms.vstring("mass"),
#           EfficiencyCategoryAndState = cms.vstring(IsoType, "above"), ## variable is above cut value 
#            BinnedVariables = cms.PSet(
#                pt = cms.vdouble(10, 13, 16, 20, 25, 30, 40, 60, 100, 200),
#               eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
#                Tight2012 = cms.vstring("pass"),
#                dB = cms.vdouble(0., 0.02),
#                dzPV = cms.vdouble(-0.1, 0.1),
#               #tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
#                # tag_pt = cms.vdouble(20, 5000.),
#            ),
#            BinToPDFmap = cms.vstring(FitFunction), ## PDF to use, as defined below
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
