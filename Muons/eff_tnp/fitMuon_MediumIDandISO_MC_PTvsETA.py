import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo"

#isMuonSel = 'Tight2012'
isMuonSel = 'Medium'

# no request trigger for tag Muon in MC !!!! -> otherwise sometimes could be empty histo
DataOpen ="0"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

#Bunch = "50ns";
#DataType = "Run2015B";

Bunch = "25ns";
DataType = "Run2015D";


FileNameOpenMC = "tnp_"+Bunch+MCType+"_v3_PUlike"+DataType+"_"+Bunch+".root";
if MCType == "DY_madgraph":
  FileNameOpenMC = "tnp_25nsDY_madgraph_PUlikeRun2015D_25ns.root";
  #FileNameOpenMC = "tnp_"+Bunch+MCType+"_v3_part.root";
 
#FileNameOpenData = "tnp_"+DataType+"_PromptReco_"+Bunch+"_v3.root";  
FileNameOpenData = "tnp_"+DataType+"_PromptReco_"+Bunch+"_SingleMu_v3.root";  
FileNameOpenData2 = "tnp_"+DataType+"_PromptReco_"+Bunch+"_SingleMu_v4.root";  

FileNameOpen = FileNameOpenData;
FileNameOpen2 = FileNameOpenData2;
if DataOpen == "0": 
   FileNameOpen = FileNameOpenMC;

FileNameOutMC = "TnP_"+isMuonSel+"_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_RAW.root";
FileNameOutData = "TnP_"+isMuonSel+"_"+DataType+"_"+Bunch+"_RAW.root";
 
FileNameOut = FileNameOutData;
if DataOpen == "0": 
   FileNameOut = FileNameOutMC;

FileNameOutMCISO = "TnP_"+isMuonSel+"IDandISO_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
FileNameOutDataISO = "TnP_"+isMuonSel+"IDandISO_"+DataType+"_"+Bunch+"_PTvsETA_RAW.root";
 
FileNameOutISO = FileNameOutDataISO;
if DataOpen == "0": 
   FileNameOutISO = FileNameOutMCISO;

print '***********************************'
print 'FileNameOpen   = , %s.' % FileNameOpen
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
                                 #"file:../crab/crab_projects_tnp/crab_50ns_DY_Spring15/results/tnp_MC.root",  
                                 "file:"+FileNameOpen,  
                                 #"file:"+FileNameOpen2, for Data only  
                                 #DY 
                                 #"file:tnp_Run2015B_PromptReco_v2.root",  
                                 #"file:tnp_50nsDY_v3_PUlikeRun2015B_50ns.root",  
                                 #"file:tnp_50nsDY_v3_PUlikeRun2015C_50ns.root",  
                                 #"file:tnp_25nsDY_v3_PUlikeRun2015C_25ns.root",  
                                 #"file:tnp_25nsDY_v3_PUlikeRun2015D_25ns.root",  
                                 #DATA: 
                                 #"file:tnp_Run2015B_PromptReco_50ns_v3.root",  
                                 #"file:tnp_Run2015C_PromptReco_50ns_v3.root",  
                                 #"file:tnp_Run2015C_PromptReco_25ns_v3.root",  
                                 #"file:tnp_Run2015D_PromptReco_25ns_v3.root",
                                 #"root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_25ns_DY_Spring15/150707_143420/0000/tnp_MC_100.root",
                                 ), ## can put more than one
    ## copy locally to be faster: xrdcp root://eoscms//eos/cms/store/cmst3/user/botta/TnPtrees/tnpZ_Data.190456-193557.root $PWD/tnpZ_Data.190456-193557.root
    ## and then set InputFileNames = cms.vstring("tnpZ_Data.190456-193557.root"), 
    #OutputFileName = cms.string("TnP_Muon_ID_Simple_Data.root"),
    OutputFileName = cms.string(FileNameOut),
    InputTreeName = cms.string("fitter_tree"), 
    InputDirectoryName = cms.string("tpTree"), 
    #Defined weight
    WeightVariable = cms.string("weight"), 
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
        weight = cms.vstring("weight","0","10",""), # for MC weighted PU
    ),
    ## Flags you want to use to define numerator and possibly denominator
    Categories = cms.PSet(
        PF = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        IsoMu24_eta2p1 = cms.vstring("IsoMu24_eta2p1 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu24_eta2p1 = cms.vstring("IsoMu24_eta2p1 tag Muon", "dummy[pass=1,fail=0]"),
        Tight2012 = cms.vstring("Tight2012 Muon", "dummy[pass=1,fail=0]"),
        #tag_Tight2012 = cms.vstring("Tight 2012 tag Muon", "dummy[pass=1,fail=0]"), #this variable is not included in tag muon
        Medium = cms.vstring("Medium Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu18 = cms.vstring("tag_IsoMu18 tag Muon", "dummy[pass=1,fail=0]"),
        IsoMu18 = cms.vstring("IsoMu18  probe Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu20 = cms.vstring("IsoTkMu20 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoTkMu20 = cms.vstring("tag_IsoTkMu20 tag Muon", "dummy[pass=1,fail=0]"),
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
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                #tag_IsoMu18 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
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
    Variables = process.TnP_Muon_ID.Variables.clone(
        combRelIsoPF04dBeta = cms.vstring("PF Combined Relative Iso", "-100", "99999", ""),
        tag_nVertices       = cms.vstring("N(vertices)", "0", "99", "")
        #dB     = cms.vstring("dxy muon", "0", "2", "cm"),
        #dzPV     = cms.vstring("dz PV muon", "-5", "5", "cm"),

    ),
    
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
        ##############
        ##############

        Medium_ISO_ptVSeta = cms.PSet(
            UnbinnedVariables = cms.vstring("mass", "weight"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                # detailed bins -> not enought stat.
                #pt = cms.vdouble(10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #less detailed binning
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 60, 100, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #Medium = cms.vstring("pass"),
                #tag_IsoMu18 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        Medium_ISO_ptVSeta_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass", "weight"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO_lt20", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 60, 100, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #Medium = cms.vstring("pass"),
                #tag_IsoMu18 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        Medium_ISO_ptVSeta_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass", "weight"),
            EfficiencyCategoryAndState = cms.vstring("MediumISO_gt20", "above"), ## variable is above cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 60, 100, 200),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #Medium = cms.vstring("pass"),
                #tag_IsoMu18 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(20, 5000.),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        ##############
        ##############
    ),
)

#process.p1 = cms.Path(process.TnP_Muon_ID)
process.p2 = cms.Path(process.TnP_Muon_Iso)
