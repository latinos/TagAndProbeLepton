import FWCore.ParameterSet.Config as cms


FitFunction = "vpvPlusExpo"

#filename = 'Data'
filename = 'MC'
isMuonSel = 'Tight2012'
#isMuonSel = 'Medium'

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.TnP_Muon_ID = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    ## Input, output 
    InputFileNames = cms.vstring(
                                 #"root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_50ns_DY_Spring15/50ns_DY_Spring15.root"
                                 #"root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_50ns_DY_Spring15/150707_143432/0000/tnp_MC_99.root",
                                 #"file:../crab/crab_projects_tnp/crab_50ns_DY_Spring15/results/tnp_MC.root",  
                                 #DY 25 ns
                                 #"file:../crab/tnp_Run2015B_PromptReco.root",  
                                 "file:50ns_DY_Spring15_3_4_5_6Star.root",  
                                 #"root://eoscms//eos/cms/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_50ns_DY_Spring15/50ns_DY_Spring15.root",
                                 ), ## can put more than one
    ## copy locally to be faster: xrdcp root://eoscms//eos/cms/store/cmst3/user/botta/TnPtrees/tnpZ_Data.190456-193557.root $PWD/tnpZ_Data.190456-193557.root
    ## and then set InputFileNames = cms.vstring("tnpZ_Data.190456-193557.root"), 
    OutputFileName = cms.string("TnP_Muon_ID_Simple_MC.root"),
    InputTreeName = cms.string("fitter_tree"), 
    InputDirectoryName = cms.string("tpTree"),  
    ## Variables for binning
    Variables = cms.PSet(
        mass   = cms.vstring("Tag-muon Mass", "76", "125", "GeV/c^{2}"),
        pt     = cms.vstring("muon p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        phi = cms.vstring("muon |#phi|", "-3.142", "3.142", ""),
        pair_dz = cms.vstring("#Deltaz between two muons", "-100", "100", "cm"),
        #tag_nVertices = cms.vstring("Tag nVertices", "0.", "100.", ""),
        dB     = cms.vstring("dxy muon", "0", "2", "cm"),
        dzPV     = cms.vstring("dz PV muon", "-5", "5", "cm"),
    ),
    ## Flags you want to use to define numerator and possibly denominator
    Categories = cms.PSet(
        PF = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        IsoMu24_eta2p1 = cms.vstring("IsoMu24_eta2p1 probe Muon", "dummy[pass=1,fail=0]"),
        tag_IsoMu24_eta2p1 = cms.vstring("IsoMu24_eta2p1 tag Muon", "dummy[pass=1,fail=0]"),
        Tight2012 = cms.vstring("Tight2012 Muon", "dummy[pass=1,fail=0]"),
        #tag_Tight2012 = cms.vstring("Tight 2012 tag Muon", "dummy[pass=1,fail=0]"), #this variable is not included in tag muon
        Medium = cms.vstring("Medium Muon", "dummy[pass=1,fail=0]"),
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
    #            tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
    #            pair_dz = cms.vdouble(-1.,1.)             ## and for which -1.0 < dz < 1.0
    #        ),
    #        BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
    #    ),
########
        pt_Tight2012 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                #tag_Tight2012 = cms.vstring("pass"),
                abseta = cms.vdouble(0, 2.4),
                pt = cms.vdouble(10, 20, 30, 40, 60, 100),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        pt_Tight2012_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                #tag_Tight2012 = cms.vstring("pass"),
                abseta = cms.vdouble(0, 2.4),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(0., 0.1),
                pt = cms.vdouble(10, 15, 20),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        pt_Tight2012_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            #EfficiencyCategoryAndState = cms.vstring("PF", "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                #tag_Tight2012 = cms.vstring("pass"),
                abseta = cms.vdouble(0, 2.4),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(0., 0.1),
                pt = cms.vdouble(20, 30, 40, 60, 100),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
########

        abseta_Tight2012 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                abseta = cms.vdouble(0., 0.8, 1.2, 2.1, 2.4),
                pt = cms.vdouble(10, 1000),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        abseta_Tight2012_ptLt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                abseta = cms.vdouble(0., 0.8, 1.2, 2.1, 2.4),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(0., 0.1),
                pt = cms.vdouble(10, 20),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        abseta_Tight2012_ptGt20 = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"), ## Numerator definition
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                abseta = cms.vdouble(0., 0.8, 1.2, 2.1, 2.4),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(0., 0.1),
                pt = cms.vdouble(20, 1000),
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
########

        phi_Tight2012 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                abseta = cms.vdouble(0., 2.4),
                pt = cms.vdouble(10, 1000),
                phi = cms.vdouble(-3.142, -1.5, 0., 1.5, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        phi_Tight2012_ptLt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                abseta = cms.vdouble(0., 2.4),
                pt = cms.vdouble(10, 20),
                dB = cms.vdouble(0., 0.01),
                dzPV = cms.vdouble(0., 0.1),
                phi = cms.vdouble(-3.142, -1.5, 0., 1.5, 3.142), # for GI or CI MC only
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
        phi_Tight2012_ptGt20 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring(isMuonSel, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## i.e. use only events for which this flag is true
                abseta = cms.vdouble(0., 2.4),
                pt = cms.vdouble(20, 1000),
                dB = cms.vdouble(0., 0.02),
                dzPV = cms.vdouble(0., 0.1),
                phi = cms.vdouble(-3.142, -1.5, 0., 1.5, 3.142), # for GI or CI MC only
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
    OutputFileName = cms.string("TnP_Muon_Iso_Simple_MC.root"),
    ## More variables
    Variables = process.TnP_Muon_ID.Variables.clone(
        combRelIsoPF04dBeta = cms.vstring("PF Combined Relative Iso", "-100", "99999", ""),
        tag_nVertices       = cms.vstring("N(vertices)", "0", "99", "")
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
       #         tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## tag trigger matched
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
       #         tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## tag trigger matched
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
                pt = cms.vdouble(10, 20, 30, 40, 60, 100),
                #PF = cms.vstring("pass"),                 ## 
                Tight2012 = cms.vstring("pass"),
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## tag trigger matched
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                abseta = cms.vdouble( 0.0, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),
        ##############
        Iso_abseta_tight = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoTight", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble( 0.0, 0.8, 1.2, 2.1, 2.4 ),
                #PF = cms.vstring("pass"),                 ## 
                Tight2012 = cms.vstring("pass"),
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## tag trigger matched
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                pt = cms.vdouble(10,1000),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),


        ##############
        Iso_pt_loose = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoLoose", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(10, 20, 30, 40, 60, 100),
                #PF = cms.vstring("pass"),                 ## 
                Tight2012 = cms.vstring("pass"),
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## tag trigger matched
                #pair_dz = cms.vdouble( -1.,1. ),          ## and for which -1.0 < dz < 1.0
                abseta = cms.vdouble( 0.0, 2.4 ),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo"), ## PDF to use, as defined below
        ),
        ##############
        Iso_abseta_loose = cms.PSet(
            UnbinnedVariables = cms.vstring("mass"),
            EfficiencyCategoryAndState = cms.vstring("PFIsoLoose", "below"), ## variable is below cut value 
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble( 0.0, 0.8, 1.2, 2.1, 2.4 ),
                #PF = cms.vstring("pass"),                 ## 
                Tight2012 = cms.vstring("pass"),
                tag_IsoMu24_eta2p1 = cms.vstring("pass"), ## tag trigger matched
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
