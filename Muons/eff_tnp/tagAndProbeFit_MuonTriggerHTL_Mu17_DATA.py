import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )    


#filename = 'data_Run2012_22Jan2013_v1' 
#filename = 'data_Run2012_22Jan2013_JPsi' 
#filename = 'mc_WJDmcTnP' 
#filename = 'mc2012_DY' 
filename = 'mc2012_DY_small' 
#filename = 'data_Run2012_22Jan_Z' 
##Cust:
# J/psi: 
mass_min = "2.5"
mass_max = "3.5"
FitFunction = "gaussPlusLinear"
isTrigger = "isHLTCut_Mu17_MuTk8"
if filename == 'mc_WJDmcTnP':
   FitFunction = "DoubleGaussPlusLinear"
if filename == 'mc2012_DY' or filename == 'mc2012_DY_small' or filename == 'data_Run2012_22Jan_Z':
   FitFunction = "CBconvBWPlusLinear"
   # Z boson:
   mass_min = "80."
   #mass_max = "110."
   mass_max = "100."
   isTrigger = "isHLTCut_Mu17"
print "FitFunction = ", FitFunction 
print "mass_min    = ", mass_min
print "isTrigger   = ", isTrigger

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("/afs/cern.ch/work/k/kropiv/SMP/Trigger_HLT_Mu17_MuTr18/CMSSW_5_3_9/src/tnp/Data/"+filename+".root"),
    #InputFileNames = cms.vstring("/afs/cern.ch/work/k/kropiv/SMP/Trigger_HLT_Mu17_MuTr18/CMSSW_5_3_9/src/tnp/Data/v2/"+filename+".root"),
#    InputFileNames = cms.vstring("/afs/cern.ch/work/t/taehoon/public/Muon_Root/Z_boson/Root_DoubleMu/DYToMuMu/"+filename+".root"),
#    InputFileNames = cms.vstring("/afs/cern.ch/work/t/taehoon/public/Muon_Root/Z_boson/Root_DoubleMu/Run2012/"+filename+".root"),
#    InputFileNames = cms.vstring("/afs/cern.ch/work/t/taehoon/public/Muon_Root/Z_boson/Root_DoubleMu/DYToMuMu/New_MC/"+filename+".root"),
#    InputFileNames = cms.vstring("/afs/cern.ch/work/k/kropiv/SMP/Trigger_HLT_Mu17_MuTr18/CMSSW_5_3_9/src/tnp/Data/v3/"+filename+".root"),
    InputFileNames = cms.vstring("/afs/cern.ch/work/k/kropiv/SMP/Trigger_HLT_Mu17_MuTr18/CMSSW_5_3_9/src/tnp/Data/v4/"+filename+".root"),

    InputDirectoryName = cms.string("muonEffs"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tagProbeFitTree_HLT_Mu17_dRIDM_"+filename+".root"),
    #number of CPUs to use for fitting
    NumCPU = cms.uint32(1),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    ## to performe binned fit :
    binnedFit = cms.bool(True),
    binsForFit =cms.uint32(100),
    ## end set up of binned fit 
    #fix in the beginning variables in fit 
    #fixVars = cms.vstring("alphaCB", "nCB", "sigmaCB"),
    #fixVars = cms.vstring("alphaCB", "nCB", "sigmaCB", "cPass", "cFail"),
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        #mass = cms.vstring("Tag-Probe Mass", "2.5", "3.5", "GeV/c^{2}"),
        mass = cms.vstring("Tag-Probe Mass", mass_min, mass_max, "GeV/c^{2}"),
        tag_isoTrkRel = cms.vstring("Tag isoTrk", "0.", "100.", ""), #dpt/pt track only 
        tag_nVertices = cms.vstring("Tag nVertices", "0.", "100.", ""),
        tag_eta = cms.vstring("Tag #eta", "-2.4", "2.4", ""),
        tag_pt = cms.vstring("Tag p_{T}", "0", "5000", "GeV/c"),
        pair_deltaR = cms.vstring("Pair deltaR", "0.", "10.", ""),
        pair_pt = cms.vstring("Pair p_{T}", "0", "5000", "GeV/c"),
        pt = cms.vstring("Probe p_{T}", "0", "5000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
        phi = cms.vstring("Probe #phi", "-3.142", "3.142", ""),
        ),

    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
        #isMuon = cms.vstring("isMuonMedium", "dummy[true=1,false=0]"),
        #isIsoTrkRel = cms.vstring("isIsoTrkRel", "dummy[true=1,false=0]"),
        isHLTCut_Mu17 = cms.vstring("isHLTCut_Mu17", "dummy[true=1,false=0]"),
        isHLTCut_Mu17_MuTk8 = cms.vstring("isHLTCut_Mu17_MuTk8", "dummy[true=1,false=0]"),
        isMuonTight = cms.vstring("isMuonTight", "dummy[true=1,false=0]"),
        isMuonMedium = cms.vstring("isMuonMedium", "dummy[true=1,false=0]"),
        isMuonMedium_arbitrate = cms.vstring("isMuonMedium_arbitrate", "dummy[true=1,false=0]"),
        isMuonMedium_tight = cms.vstring("isMuonMedium_tight", "dummy[true=1,false=0]"),
        isMuonMedium_loose = cms.vstring("isMuonMedium_loose", "dummy[true=1,false=0]"),
        isMuonMedium_stMatch = cms.vstring("isMuonMedium_stMatch", "dummy[true=1,false=0]"),
        #tag_isHLTCut_Mu17 = cms.vstring("tag_isHLTCut_Mu17", "dummy[true=1,false=0]"),
        #tag_isHLTCut_IsoMu24 = cms.vstring("tag_isHLTCut_IsoMu24", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        gaussPlusLinear = cms.vstring(
            #"Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[1.8,1,20])",
           #"RooCBShape::signal(mass, meanCB[90,80,100], sigmaCB[2.495, 1.5, 5.], alphaCB[1., 0.2, 10.], nCB[5., 0.01, 20.])",
            #"Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigmac[2.3, 0.5, 10.0])",
           "Gaussian::signal(mass, mean[3.1,3.0,3.2], sigma[0.03,0.01,0.1])",
            "Chebychev::backgroundPass(mass, cPass[0,-1,1])",
            "Chebychev::backgroundFail(mass, cFail[0,-1,1])",            
           #    "FCONV::signalFail(mass, signalPhy, signalResFail)",     
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),

        DoubleGaussPlusLinear = cms.vstring(
            "Gaussian::signal1(mass, mean1[3.1,3.0,3.2], sigma1[0.03,0.01,0.1])",
            "Gaussian::signal2(mass, mean1[3.1,3.0,3.2], sigma2[0.06,0.02,0.3])",# the same mean1 as in signal1
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, cPass[0,-1,1])",
            "Chebychev::backgroundFail(mass, cFail[0,-1,1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),


        CBconvBWPlusLinear = cms.vstring(
            #"RooCBShape::signalRes(mass, meanCB[0], sigmaCB[1.5, 0.5, 5.], alphaCB[1.9, 0.2, 10.], nCB[0.35])", #DATA fit
            #"RooCBShape::signalRes(mass, meanCB[0], sigmaCB[1.5, 0.5, 5.], alphaCB[1.9, 0.2, 10.], nCB[0.35, 0.01, 10.])", #MC fit
            "Chebychev::backgroundPass(mass, cPass[-0.4, -1, 1])",
            "Chebychev::backgroundFail(mass, cFail[-0.4, -1, 1])",            
            #"RooCBShape::signalRes(mass, meanCB[0], sigmaCB[1.5, 0.5, 3.5], alphaCB[1.9, 0.2, 10.], nCB[0.35, 0.01, 10.])", #MC fit
            #"RooBreitWigner::signalPhy(mass, meanbw[90.66, 80, 100], sigmabw[2.495])",
            #"FCONV::signal(mass, signalPhy, signalRes)",
            "RooBreitWigner::signal(mass, meanbw[90.66, 85, 100], sigmabw[2.495, 1., 4.])",
            #"Chebychev::backgroundPass(mass, {cPass1[-0.4, -1, 1], cPass2[0, -1, 1],cPass3[0., -1, 1]})",
            #"Chebychev::backgroundFail(mass, {cFail1[-0.4, -1, 1], cFail2[0., -1, 1],cFail3[0., -1, 1]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),  
    ),


    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
########
#        pt = cms.PSet(
#            #EfficiencyCategoryAndState = cms.vstring("probe_passConvRej","pass","probe_isWP80","pass"), #example 
#            EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonMedium_arbitrate =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                pair_deltaR = cms.vdouble(0.1,10.), #cut for Trigger acceptence 
#                eta = cms.vdouble(-2.4, 2.4),
#                #pt = cms.vdouble(5.,7.,8.,9.,10.,15.,30),
#                pt = cms.vdouble(5.,16., 17., 18., 20., 25., 30., 40.),
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
########
#        eta = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonMedium_arbitrate =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                pair_deltaR = cms.vdouble(0.1,10.), #cut for Trigger acceptence 
#                pt = cms.vdouble(18, 5000),
#                #abseta = cms.vdouble(0.,0.8,2.1,2.4),
#                eta = cms.vdouble(-2.4,-2.1,-0.8,0.,0.8,2.1,2.4)
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
########
#        phi = cms.PSet(
#           EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonMedium_arbitrate =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                pair_deltaR = cms.vdouble(0.1,10.), #cut for Trigger acceptence 
#                eta = cms.vdouble(-2.4, 2.4),
#                pt = cms.vdouble(18, 5000),
#                phi = cms.vdouble(-3.142, -1.5, 0., 1.5, 3.142), # for GI or CI MC only
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
#
########
#        pt_sum = cms.PSet(
#            #EfficiencyCategoryAndState = cms.vstring("probe_passConvRej","pass","probe_isWP80","pass"), #example 
#            EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonMedium_arbitrate =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                pair_deltaR = cms.vdouble(0.1,10.), #cut for Trigger acceptence 
#                eta = cms.vdouble(-2.4, 2.4),
#                pt = cms.vdouble(18,5000),
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
#########
#        tag_nVertices = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonMedium_arbitrate =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                pair_deltaR = cms.vdouble(0.1,10.), #cut for Trigger acceptence 
#                eta = cms.vdouble(-2.4, 2.4),
#                pt = cms.vdouble(18, 5000),
#                #tag_nVertices = cms.vdouble(0.5, 10.5, 15.5, 20.5, 30.5),
#                tag_nVertices = cms.vdouble(0.5, 15.5, 30.5),
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
########
#        pair_deltaR = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonMedium_arbitrate =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                eta = cms.vdouble(-2.4, 2.4),
#                pt = cms.vdouble(18, 5000),
#                #pair_deltaR = cms.vdouble(0., 0.08, 0.1, 0.12, 0.14, 0.17, 0.2, 0.3),#Data    
#                pair_deltaR = cms.vdouble(0., 2., 3., 3.5, 4., 6.),#Data  
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
########
#        pair_deltaR_Tight = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring(isTrigger,"true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                isMuonTight =  cms.vstring("true"), #requir pass MuonID for probe track
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                eta = cms.vdouble(-2.4, 2.4),
#                pt = cms.vdouble(18, 5000),
#                #pair_deltaR = cms.vdouble(0., 0.08, 0.1, 0.12, 0.14, 0.17, 0.2, 0.3),#Data    
#                pair_deltaR = cms.vdouble(0., 2., 3., 3.5, 4., 6.),#Data  
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
########
#        pair_deltaR_MuonIDisTight = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("isMuonTight","true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
#                eta = cms.vdouble(-2.4, 2.4),
#                pt = cms.vdouble(18, 5000),
#                #pair_deltaR = cms.vdouble(0., 0.1, 0.2, 0.3),#Data    
#                pair_deltaR = cms.vdouble(0., 2., 3., 3.5, 4., 6.),#Data  
#            ),
#            BinToPDFmap = cms.vstring(FitFunction)
#        ),
########
        pair_deltaR_MuonIDisMedium = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isMuonMedium_arbitrate","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #tag_isHLTCut_IsoMu24 = cms.vstring("true"), #requir tag muon to be match to HLT_Mu17
                eta = cms.vdouble(-2.4, 2.4),
                pt = cms.vdouble(18, 5000),
                #pair_deltaR = cms.vdouble(0., 0.1, 0.2, 0.3),#Data    
                pair_deltaR = cms.vdouble(0., 2., 3., 3.5, 4., 6.),#Data  
            ),
            BinToPDFmap = cms.vstring(FitFunction)
        ),
########
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

