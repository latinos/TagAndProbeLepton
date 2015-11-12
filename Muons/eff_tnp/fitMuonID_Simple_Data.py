import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo"

#isMuonSel = 'Tight2012'
isMuonSel = 'Medium'

DataOpen ="0"; # 1 - Open data; 0 - Open MC
#MCType = "DY";
MCType = "DY_madgraph";

Bunch = "50ns";
#DataType = "Run2015B";

#Bunch = "25ns";
DataType = "Run2015D";


FileNameOpenMC = "tnp_"+Bunch+MCType+"_v3_PUlike"+DataType+"_"+Bunch+".root";
if MCType == "DY_madgraph":
  FileNameOpenMC = "tnp_"+Bunch+MCType+"_v3_part.root";

FileNameOpenData = "tnp_"+DataType+"_PromptReco_"+Bunch+"_v3.root";  

FileNameOpen = FileNameOpenData;
if DataOpen == "0": 
   FileNameOpen = FileNameOpenMC;

FileNameOutMC = "TnP_"+isMuonSel+"_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_RAW.root";
FileNameOutData = "TnP_"+isMuonSel+"_"+DataType+"_"+Bunch+"_RAW.root";
 
FileNameOut = FileNameOutData;
if DataOpen == "0": 
   FileNameOut = FileNameOutMC;

FileNameOutMCISO = "TnP_ISO_"+isMuonSel+"_"+MCType+Bunch+"Like"+DataType+"_"+Bunch+"_RAW.root";
FileNameOutDataISO = "TnP_ISO_"+isMuonSel+"_"+DataType+"_"+Bunch+"_RAW.root";
 
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
        tag_IsoMu20 = cms.vstring("tag_IsoMu20 tag Muon", "dummy[pass=1,fail=0]"),
        IsoMu20 = cms.vstring("IsoMu20  probe Muon", "dummy[pass=1,fail=0]"),
        IsoTkMu20 = cms.vstring("IsoTkMu20 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoTkMu20 = cms.vstring("tag_IsoTkMu20 tag Muon", "dummy[pass=1,fail=0]"),
    ),
    ## What to fit
    Efficiencies = cms.PSet(
    #    PF_pt_eta = cms.PSet(
    #        UnbinnedVariables = cms.vstring("mass"),
    #        EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
    #        BinnedVariables = cms.PSet(
    #            ## Binning in continuous variables
    #            pt     = cms.vdouble( 10, 20, 30, 40, 60, 100 ),
    #            abseta = cms.vdouble( 0.0, 1.2, 2.4),
    #            ## flags and conditions required at the denominator, 
    #            tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
    #            pair_dz = cms.vdouble(-1.,1.)             ## and for which -1.0 < dz < 1.0
    #        ),
    #        BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
    #    ),


########
        IsoMu20_ptVSeta_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("IsoMu20", "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                #tag_Tight2012 = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #pt = cms.vdouble(10, 20, 22, 30, 40, 60, 100),
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),


########
        IsoMu20_pt_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("IsoMu20", "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                #tag_Tight2012 = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, 2.4),
                #pt = cms.vdouble(10, 20, 22, 30, 40, 60, 100),
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),

########
        IsoMu20_eta_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("IsoMu20", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                pt = cms.vdouble(22, 1000),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        IsoMu20_phi_Medium = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("IsoMu20", "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(22, 1000),
                #phi = cms.vdouble(-3.142, -1.5, 0., 1.5, 3.142), # for GI or CI MC only
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        IsoMu20_tag_nVertices_Medium = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("IsoMu20", "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(22, 1000),
                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
########################
########
        IsoTkMu20_ptVSeta_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("IsoTkMu20", "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoTkMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                #tag_Medium = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),


########
        IsoTkMu20_pt_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("IsoTkMu20", "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoTkMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                #tag_Medium = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        IsoTkMu20_eta_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("IsoTkMu20", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
               tag_IsoTkMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                pt = cms.vdouble(22, 1000),
           ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        IsoTkMu20_phi_Medium = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("IsoTkMu20", "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoTkMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(22, 1000),
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        IsoTkMu20_tag_nVertices_Medium = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("IsoTkMu20", "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                Medium = cms.vstring("pass"), ## probe muon is tight
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                combRelIsoPF04dBeta = cms.vdouble(0., 0.12),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(22, 1000),
                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
################################
        pt_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                #tag_Tight2012 = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(10, 20, 30, 40, 60, 100),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        pt_Medium_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                #tag_Tight2012 = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, 2.4),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        pt_Medium_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                #tag_Tight2012 = cms.vstring("pass"),
                eta = cms.vdouble(-2.4, 2.4),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
########

        eta_Medium = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                pt = cms.vdouble(10, 1000),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        eta_Medium_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                pt = cms.vdouble(10, 20),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        eta_Medium_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                pt = cms.vdouble(20, 1000),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
########

        phi_Medium = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(10, 1000),
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        phi_Medium_ptLt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(10, 20),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        phi_Medium_ptGt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(20, 1000),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
########

        #if filename == 'Data':
        ########
        tag_nVertices_Medium = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(10, 1000),
                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
        ########
        tag_nVertices_Medium_ptLt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(10, 20),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_nVertices = cms.vdouble(0., 5., 8., 10., 12., 14., 16., 20.), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
        ########
        tag_nVertices_Medium_ptGt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu20 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                tag_pt = cms.vdouble(22, 5000.),
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
    ## Cuts: name, variable, cut threshold
    Cuts = cms.PSet(
        PFIsoLoose = cms.vstring("PFIsoLoose" ,"combRelIsoPF04dBeta", "0.20"),
        PFIsoTight = cms.vstring("PFIsoTight" ,"combRelIsoPF04dBeta", "0.12"),
    ),
    ## What to fit
    Efficiencies = cms.PSet(
       # Iso_vtx_tight = cms.PSet(
       #     UnbinnedVariables = cms.vstring("mass"),
       #     EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
       #     BinnedVariables = cms.PSet(
       #         tag_nVertices = cms.vdouble(0.5,4.5,8.5,12.5,16.5,20.5,24.5,30.5), 
       #         #PF = cms.vstring("pass"),                 ## 
       #         Tight2012 = cms.vstring("pass"),
       #         tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
       #         tag_pt = cms.vdouble(22, 5000.),
       #         #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
       #         pt     = cms.vdouble( 25,  100 ),
       #         abseta = cms.vdouble( 0.0, 2.4 ),
       #     ),
       #     BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
       # ),
       # Iso_vtx_loose = cms.PSet(
       #     UnbinnedVariables = cms.vstring("mass"),
       #     EfficiencyCategoryAndState = cms.vstring("PFIsoLoose", "below"), ## variable is below cut value 
       #     BinnedVariables = cms.PSet(
       #         tag_nVertices = cms.vdouble(0.5,4.5,8.5,12.5,16.5,20.5,24.5,30.5), 
       #         #PF = cms.vstring("pass"),                 ## 
       #         Tight2012 = cms.vstring("pass"),
       #         tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
       #         tag_pt = cms.vdouble(22, 5000.),
       #         #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
       #         pt     = cms.vdouble( 25,  100 ),
       #         abseta = cms.vdouble( 0.0, 2.4 ),
       #     ),
       #     BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
       # ),
        ##############
        Iso_pt_tight = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                eta = cms.vdouble( -2.4, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        Iso_pt_tight_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                eta = cms.vdouble( -2.4, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        Iso_pt_tight_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                eta = cms.vdouble( -2.4, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),




        ##############
        Iso_eta_tight = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        Iso_eta_tight_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,20),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),


        Iso_eta_tight_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(20,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),
        ##############
        Iso_phi_tight = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142),
                eta = cms.vdouble( -2.4, 2.4),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),

        Iso_phi_tight_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142),
                eta = cms.vdouble( -2.4, 2.4),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,20),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),


        Iso_phi_tight_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                phi = cms.vdouble(-3.142, -2.8, -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0., 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.142),
                eta = cms.vdouble( -2.4, 2.4),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(-0.1, 0.1),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(20,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),



        ##############
        Iso_pt_loose = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoLoose", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60, 80, 120, 200),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                eta = cms.vdouble( -2.4, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),
        ##############
        Iso_eta_loose = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoLoose", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                eta = cms.vdouble( -2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4 ),
                #PF = cms.vstring("pass"),                 ## 
                Medium = cms.vstring("pass"),
                tag_IsoMu20 = cms.vstring("pass"), ## tag trigger matched
                tag_pt = cms.vdouble(22, 5000.),
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),


        ##############
    ),
)

process.p1 = cms.Path(process.TnP_Muon_ID)
process.p2 = cms.Path(process.TnP_Muon_Iso)
