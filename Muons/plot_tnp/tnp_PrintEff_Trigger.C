// ------------------------------------------------------------------------------
//////////////////////////////
// TTree
// ------------------------------------------------------------------------------
#include<TFile.h>
#include<TTree.h>
#include<TH1.h>
#include<TH2.h>
#include<TCanvas.h>
#include<TFrame.h>
#include<TLegend.h>
#include<vector>
#include<iostream>
#include<TMath.h>
#include<TROOT.h>
#include<TInterpreter.h>
#include<TStyle.h>
#include<TChain.h>
#include<TString.h>
#include<TPaveStats.h>
#include<TPad.h>
#include<TLatex.h>
#include <TGraphAsymmErrors.h>

using namespace std;

#include "modifiedStyle.C"

/// check that up error are calculated properly because of problems in tag and probe fit 
void ErrorCheck(TGraphAsymmErrors* histo);


//void tag_n_probe( bool isSave = !true ) {
void tnp_PrintEff_Trigger( bool isSave = true ) {
  
  gROOT->Clear();
  gStyle->SetOptStat(0);  
  //gStyle->SetTitleSize(0.5);
  //gStyle->SetTitleFont(60);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetCanvasColor(kWhite); 
  //gStyle->SetFillColor(0);
  gStyle->SetOptTitle(kFALSE);

  double BinEta[] = {-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4}; 
  // binning for Mu17 
  //double BinPt[] = {10, 15, 16, 17, 18, 19, 20, 25, 30, 40, 60, 100, 200};
  // binning for Mu22, Mu24 
  double BinPt[] = {10, 20, 21, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200};
  // binning for Mu8
  //double BinPt[] = {10, 13, 16, 20, 25, 30, 40, 60, 100, 200};

  int BinPtSize = int(sizeof(BinPt)/sizeof(BinPt[0]));
  int BinEtaSize = int(sizeof(BinEta)/sizeof(BinEta[0]));
  cout << "BinPtSize = " << BinPtSize << endl;
  cout << "BinEtaSize = " << BinEtaSize << endl;

  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_12/src/TagAndProbeLepton/Muons/eff_tnp/";

  //change only name of file, check that you use correct pt and eta binning: 

  // for Run2016B

  //TString sample_data = "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunGe274094";
  TString sample_data = "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunLt274094";

  //TString sample_data = "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunGe274094";
  //TString sample_data = "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunLt274094";

  //TString sample_data = "DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunGe274094";
  //TString sample_data = "DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunLt274094";

  //TString sample_data = "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunGe274094";
  //TString sample_data = "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunLt274094";

  //TString sample_data = "DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunGe274094";
  //TString sample_data = "DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunLt274094";

  //TString sample_data = "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2016B_PTvsETA_RunGe274094";
  //TString sample_data = "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2016B_PTvsETA_RunLt274094";

  //TString Tag_trig = "_&_tag_IsoMu20_pass";
  TString Tag_trig = "";

  TFile* DATA   = TFile::Open(pathAnna+sample_data+".root" );

////////////////////////////////
  ofstream myfile;
  myfile.open (sample_data+".txt");
  myfile << "etamin\tetamax\tptmin\tptmax\teff\tdeff_high\tdeff_low\n";

  ofstream myfile_ptGt20;
  myfile_ptGt20.open (sample_data+"_ptGt20.txt");
  myfile_ptGt20 << "etamin\tetamax\tptmin\tptmax\teff\tdeff_high\tdeff_low\n";

  ofstream myfile_ptLt20;
  myfile_ptLt20.open (sample_data+"_ptLt20.txt");
  myfile_ptLt20 << "etamin\tetamax\tptmin\tptmax\teff\tdeff_high\tdeff_low\n";

  ofstream myfile_HWW;
  myfile_HWW.open (sample_data+"_HWW.txt");
  myfile_HWW << "etamin\tetamax\tptmin\tptmax\teff\tdeff_high\tdeff_low\n";



////////////////////////////////
  ofstream myfile_HWW_tex;
  myfile_HWW_tex.open (sample_data+"_HWW_tex.txt");
  myfile_HWW_tex << "\\begin{sidewaystable}\n";

  if (sample_data == "TnP_IsoMu20orIsoTkMu20_Run2016B_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu20 or HLT\\_IsoTkMu20 for Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "TnP_IsoMu20orIsoTkMu20_Run2016B_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu20orIsoTkMu20_Ge274094}\n";
  if (sample_data == "TnP_IsoMu20orIsoTkMu20_Run2016B_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu20 or HLT\\_IsoTkMu20 for Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "TnP_IsoMu20orIsoTkMu20_Run2016B_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu20orIsoTkMu20_Lt274094}\n";

  if (sample_data == "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu22 or HLT\\_IsoTkMu22 for Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu22orIsoTkMu22_Ge274094}\n";
  if (sample_data == "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu22 or HLT\\_IsoTkMu22 for Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu22orIsoTkMu22_Lt274094}\n";

  if (sample_data == "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu24 or HLT\\_IsoTkMu24 for Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu24orIsoTkMu24_Ge274094}\n";
  if (sample_data == "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu24 or HLT\\_IsoTkMu24 for Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu24orIsoTkMu24_Lt274094}\n";

  if (sample_data == "DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu17\\_TrkIsoVVL for Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu17_TrkIsoVVL_Ge274094}\n";
  if (sample_data == "DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu17\\_TrkIsoVVL for Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "DoubleMu_IsoMu17leg_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu17_TrkIsoVVL_Lt274094}\n";

  if (sample_data == "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL or HLT\\_TkMu8\\_TrkIsoVVL for Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8orTkMu8_TrkIsoVVL_Ge274094}\n";
  if (sample_data == "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL or HLT\\_TkMu8\\_TrkIsoVVL for Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8orTkMu8_TrkIsoVVL_Lt274094}\n";


  if (sample_data == "DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL for Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8_TrkIsoVVL_Ge274094}\n";
  if (sample_data == "DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL for Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "DoubleMu_IsoMu8leg_Run2016_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8_TrkIsoVVL_Lt274094}\n";

  if (sample_data == "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2016B_PTvsETA_RunGe274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_TkMu8\\_TrkIsoVVLfor Runs $\\ge 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2016B_PTvsETA_RunGe274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_TkMu8_TrkIsoVVL_Ge274094}\n";
  if (sample_data == "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2016B_PTvsETA_RunLt274094") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_TkMu8\\_TrkIsoVVLfor Runs $< 274094$. From max relative statistic error calculation we have removed $0.2<|\\eta|<0.3$ bin, because, due to small statistics, stat. error is 2 times larger in average than calculated value.}\n";
  if (sample_data == "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2016B_PTvsETA_RunLt274094") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_TkMu8_TrkIsoVVL_Ge274094}\n";

  //myfile_HWW_tex << "\\begin{tabular}{|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|}\n";
  myfile_HWW_tex << "\\begin{tabular}{|l|l|l|l|l|l|l|l|l|l|l|l|l|l||l|}\n";
  myfile_HWW_tex << "\\hline\n";

  for (int ieta=0; ieta<BinEtaSize-1; ieta++){
      if(ieta == 0)              myfile_HWW_tex <<"$p_{T}/\\eta$ & \\small{" << BinEta[ieta] << ":" << BinEta[ieta+1] << "}";
      if(ieta > 0)               myfile_HWW_tex <<             " & \\small{" << BinEta[ieta] << ":" << BinEta[ieta+1] << "}"; 
      //if(ieta == (BinEtaSize-2)) myfile_HWW_tex <<"\\\\ \n\\hline\n";
  }
  myfile_HWW_tex << " & \\small{max rel.} \\\\ \n"  ;
  myfile_HWW_tex << " & & & & & & & & & & & & & & \\small{st. error} \\\\ \n\\hline\n"  ;
  //end 1 tex file:
////////////////////////////////
  for (int ipt=0; ipt<BinPtSize-1; ipt++){

     TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d_&_Tight2012_pass%s",ipt,Tag_trig.Data() ));
     if(tDATA == 0)cout << "check code: ERROR Canvas = " << tDATA << " ipt = " << ipt << endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     Double_t *eff       = grDATA->GetY();
     Double_t *deff_high = grDATA->GetEYhigh();
     Double_t *deff_low  = grDATA->GetEYlow();

     TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta_ptGt20/fit_eff_plots/eta_PLOT_pt_bin%d_&_Tight2012_pass%s",ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptGt20 = (TGraphAsymmErrors*) tDATA_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptGt20);
     Double_t *eff_ptGt20       = grDATA_ptGt20->GetY();
     Double_t *deff_high_ptGt20 = grDATA_ptGt20->GetEYhigh();
     Double_t *deff_low_ptGt20  = grDATA_ptGt20->GetEYlow();

     TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta_ptLt20/fit_eff_plots/eta_PLOT_pt_bin%d_&_Tight2012_pass%s",ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptLt20 = (TGraphAsymmErrors*) tDATA_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptLt20);
     Double_t *eff_ptLt20       = grDATA_ptLt20->GetY();
     Double_t *deff_high_ptLt20 = grDATA_ptLt20->GetEYhigh();
     Double_t *deff_low_ptLt20  = grDATA_ptLt20->GetEYlow();

     Double_t Max_StError = 0.;

     for (int ieta=0; ieta<BinEtaSize-1; ieta++){

        Double_t Eff = eff[ieta];
        Double_t dEff_high = deff_high[ieta];
        Double_t dEff_low = deff_low[ieta];
        //if (Eff < 0.005) {Eff = 0.; dEff_high = 0.; dEff_low =0.;}
        if (Eff < 0.01) {Eff = 0.; dEff_high = 0.; dEff_low =0.;}
        if (Eff > 0.5 && dEff_high > 3*dEff_low) dEff_high = dEff_low;

        Double_t Eff_ptGt20 = eff_ptGt20[ieta];
        Double_t dEff_high_ptGt20 = deff_high_ptGt20[ieta];
        Double_t dEff_low_ptGt20 = deff_low_ptGt20[ieta];
        //if (Eff_ptGt20 < 0.005) {Eff_ptGt20 = 0.; dEff_high_ptGt20 = 0.; dEff_low_ptGt20 =0.;}
        if (Eff_ptGt20 < 0.01) {Eff_ptGt20 = 0.; dEff_high_ptGt20 = 0.; dEff_low_ptGt20 =0.;}
        if (Eff_ptGt20 > 0.5 && dEff_high_ptGt20 > 3*dEff_low_ptGt20) dEff_high_ptGt20 = dEff_low_ptGt20;

        Double_t Eff_ptLt20 = eff_ptLt20[ieta];
        Double_t dEff_high_ptLt20 = deff_high_ptLt20[ieta];
        Double_t dEff_low_ptLt20 = deff_low_ptLt20[ieta];
        //if (Eff_ptLt20 < 0.005) {Eff_ptLt20 = 0.; dEff_high_ptLt20 = 0.; dEff_low_ptLt20 =0.;}
        if (Eff_ptLt20 < 0.01) {Eff_ptLt20 = 0.; dEff_high_ptLt20 = 0.; dEff_low_ptLt20 =0.;}
        if (Eff_ptLt20 > 0.5 && dEff_high_ptLt20 > 3*dEff_low_ptLt20) dEff_high_ptLt20 = dEff_low_ptLt20;
 
        myfile 
               //<< setprecision(4)
               << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t" 
               << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"  
               << Eff    << "\t" << dEff_high      << "\t " << dEff_low <<"\n"; //write to file
        myfile_ptGt20 
               << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t" 
               << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"  
               << Eff_ptGt20    << "\t" << dEff_high_ptGt20      << "\t " << dEff_low_ptGt20 <<"\n"; //write to file
        myfile_ptLt20 
               << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t" 
               << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"  
               << Eff_ptLt20    << "\t" << dEff_high_ptLt20      << "\t " << dEff_low_ptLt20 <<"\n"; //write to file
        if (BinPt[ipt+1] < 20.001){
           myfile_HWW
                  << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t"
                  << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"
                  << Eff_ptLt20    << "\t" << dEff_high_ptLt20      << "\t " << dEff_low_ptLt20 <<"\n"; 
           if(Eff_ptLt20 >= 0.001  
              && ( (BinEta[ieta] < -0.31) || (BinEta[ieta] > -0.21 && BinEta[ieta] < 0.19) || (BinEta[ieta] > 0.29) ) 
             ){
              if (Max_StError < dEff_high_ptLt20/Eff_ptLt20) Max_StError = dEff_high_ptLt20/Eff_ptLt20;
              if (Max_StError < dEff_low_ptLt20/Eff_ptLt20) Max_StError = dEff_low_ptLt20/Eff_ptLt20;
           }
        }
        else{
           myfile_HWW
                  << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t"
                  << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"
                  << Eff_ptGt20    << "\t" << dEff_high_ptGt20      << "\t " << dEff_low_ptGt20 <<"\n";
           if(Eff_ptGt20 >= 0.001
              && ( (BinEta[ieta] < -0.31) || (BinEta[ieta] > -0.21 && BinEta[ieta] < 0.19) || (BinEta[ieta] > 0.29) ) 
             ){
              if (Max_StError < dEff_high_ptGt20/Eff_ptGt20) Max_StError = dEff_high_ptGt20/Eff_ptGt20;
              if (Max_StError < dEff_low_ptGt20/Eff_ptGt20) Max_StError = dEff_low_ptGt20/Eff_ptGt20;
           }
        }
        //start tex file:
        if(ieta == 0)  myfile_HWW_tex << setprecision(4) << "\\small{" << BinPt[ipt] << ":" << BinPt[ipt+1] << "}";
        if (BinPt[ipt+1] < 20.001) {
           myfile_HWW_tex << " & ";  
           //if(Eff_ptLt20 > 0.95) myfile_HWW_tex << "\\cellcolor{red} ";
           //if(Eff_ptLt20 > 0.90 && Eff_ptLt20 <= 0.95) myfile_HWW_tex << "\\cellcolor{Maroon!80} ";
           //if(Eff_ptLt20 > 0.80 && Eff_ptLt20 <= 0.90) myfile_HWW_tex << "\\cellcolor{Orange} ";
           //if(Eff_ptLt20 > 0.70 && Eff_ptLt20 <= 0.80) myfile_HWW_tex << "\\cellcolor{Yellow} ";
           //if(Eff_ptLt20 > 0.50 && Eff_ptLt20 <= 0.70) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
           //if(Eff_ptLt20 > 0.01 && Eff_ptLt20 <= 0.50) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
           if(Eff_ptLt20 >= 0.945) myfile_HWW_tex << "\\cellcolor{Green} ";
           if(Eff_ptLt20 >= 0.895 && Eff_ptLt20 < 0.945) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
           if(Eff_ptLt20 >= 0.795 && Eff_ptLt20 < 0.895) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
           if(Eff_ptLt20 >= 0.695 && Eff_ptLt20 < 0.795) myfile_HWW_tex << "\\cellcolor{Yellow} ";
           if(Eff_ptLt20 >= 0.495 && Eff_ptLt20 < 0.695) myfile_HWW_tex << "\\cellcolor{Orange} ";
           if(Eff_ptLt20 >= 0.01  && Eff_ptLt20 < 0.495) myfile_HWW_tex << "\\cellcolor{Red} ";
           //if (Eff_ptLt20 < 0.10)myfile_HWW_tex << setprecision(2) <<  Eff_ptLt20;  
           //else myfile_HWW_tex << setprecision(3) <<  Eff_ptLt20;  
           myfile_HWW_tex << setprecision(2) <<  Eff_ptLt20;  
        }
        else {
           myfile_HWW_tex << " & ";  
           //if(Eff_ptGt20 > 0.95) myfile_HWW_tex << "\\cellcolor{red} ";
           //if(Eff_ptGt20 > 0.90 && Eff_ptGt20 <= 0.95) myfile_HWW_tex << "\\cellcolor{Maroon!80} ";
           //if(Eff_ptGt20 > 0.80 && Eff_ptGt20 <= 0.90) myfile_HWW_tex << "\\cellcolor{Orange} ";
           //if(Eff_ptGt20 > 0.70 && Eff_ptGt20 <= 0.80) myfile_HWW_tex << "\\cellcolor{Yellow} ";
           //if(Eff_ptGt20 > 0.50 && Eff_ptGt20 <= 0.70) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
           //if(Eff_ptGt20 > 0.01 && Eff_ptGt20 <= 0.50) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
           if(Eff_ptGt20 >= 0.945) myfile_HWW_tex << "\\cellcolor{Green} ";
           if(Eff_ptGt20 >= 0.895 && Eff_ptGt20 < 0.945) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
           if(Eff_ptGt20 >= 0.795 && Eff_ptGt20 < 0.895) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
           if(Eff_ptGt20 >= 0.695 && Eff_ptGt20 < 0.795) myfile_HWW_tex << "\\cellcolor{Yellow} ";
           if(Eff_ptGt20 >= 0.495 && Eff_ptGt20 < 0.695) myfile_HWW_tex << "\\cellcolor{Orange} ";
           if(Eff_ptGt20 >= 0.01  && Eff_ptGt20 < 0.495) myfile_HWW_tex << "\\cellcolor{Red} ";
           //if (Eff_ptGt20 < 0.10) myfile_HWW_tex << setprecision(2) << Eff_ptGt20;  
           //else myfile_HWW_tex << setprecision(3) << Eff_ptGt20;  
           myfile_HWW_tex << setprecision(2) << Eff_ptGt20;  
        }
        //if (ieta == (BinEtaSize-2)) myfile_HWW_tex <<" \\\\ \n\\hline\n";
        //end tex file:

     } //end ieta
     myfile_HWW_tex <<" & ";
     if(Max_StError <=0.01 && Max_StError > 0.0000001) myfile_HWW_tex << "\\cellcolor{Green} ";
     if(Max_StError > 0.01 && Max_StError <=0.03) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
     if(Max_StError > 0.03 && Max_StError <=0.05) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
     if(Max_StError > 0.05 && Max_StError <=0.07) myfile_HWW_tex << "\\cellcolor{Yellow} ";
     if(Max_StError > 0.07 && Max_StError <=0.1) myfile_HWW_tex << "\\cellcolor{Orange} ";
     if(Max_StError >0.10) myfile_HWW_tex << "\\cellcolor{Red} ";
     if(Max_StError >=0.01) myfile_HWW_tex << setprecision(2) << Max_StError << "\\\\ \n\\hline\n";
     else{myfile_HWW_tex << setprecision(1) << Max_StError  << "\\\\ \n\\hline\n";}

  } //end ipt
  // set color defenition
  //myfile_HWW_tex << "\\multicolumn{6}{|c|}{Color Definition} & \\multicolumn{9}{c|}{} \\\\ \n\\hline\n"; 
  //myfile_HWW_tex << "\\multicolumn{3}{c|}{Efficiency} & \\multicolumn{3}{c|}{max rel. st. error} & \\multicolumn{9}{c|}{} \\\\ \n\\hline\n";
  //myfile_HWW_tex << "\\multicolumn{3}{c|}{\\cellcolor{Green} 0.95-1.00} & \\multicolumn{3}{c|}{\\cellcolor{Green} 0.00-0.01} & \\multicolumn{9}{c|}{} \\\\ \n\\hline\n"; 
  myfile_HWW_tex << "\\multicolumn{15}{|c|}{Color Definition} \\\\ \n\\hline\n"; 
  myfile_HWW_tex << "\\multicolumn{3}{|c|}{Efficiency} & \\multicolumn{2}{c|}{\\cellcolor{Green} 0.95-1.00} &  \\multicolumn{2}{c|}{\\cellcolor{YellowGreen} 0.90-0.95} & \\multicolumn{2}{c|}{\\cellcolor{SkyBlue} 0.80-0.90} & \\multicolumn{2}{c|}{\\cellcolor{Yellow} 0.70-0.80} & \\multicolumn{2}{c|}{\\cellcolor{Orange} 0.50-0.70} & \\multicolumn{2}{c|}{\\cellcolor{Red} $<$ 0.50} \\\\ \n\\hline\n";
  myfile_HWW_tex << "\\multicolumn{3}{|c|}{max rel. st. error} & \\multicolumn{2}{c|}{\\cellcolor{Green} 0.00-0.01} &  \\multicolumn{2}{c|}{\\cellcolor{YellowGreen} 0.01-0.03} & \\multicolumn{2}{c|}{\\cellcolor{SkyBlue} 0.03-0.05} & \\multicolumn{2}{c|}{\\cellcolor{Yellow} 0.05-0.07} & \\multicolumn{2}{c|}{\\cellcolor{Orange} 0.07-0.10} & \\multicolumn{2}{c|}{\\cellcolor{Red} $>$ 0.10} \\\\ \n\\hline\n";

  myfile_HWW_tex << "\\end{tabular}\n\\end{sidewaystable}\n"; 

  myfile.close();
  myfile_ptGt20.close();
  myfile_ptLt20.close();
  myfile_HWW.close();
  myfile_HWW_tex.close();
////////////////////////////////
//  if (!isSave) return;

}

//////////////////////////////////////////

//void ErrorCheck(TGraphAsymmErrors* histo){
//  /// check that up error are calculated properly because of problems in tag and probe fit 
//  int nbin = histo -> GetN();
//  for(int i = 0; i < nbin; i++){
//     //if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
//  }
//
//}
void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     if( (histo -> GetErrorYhigh(i)) > 3.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(i));
     Double_t YnewHigh = 0;
     Double_t YnewLow = 0;
     Double_t minError = 0.00001;
     if  ((histo -> GetErrorYhigh(i)) < minError) {
          if  ( (histo -> GetErrorYlow(i))  > minError) {YnewHigh = histo -> GetErrorYlow(i);}
          else if (i < (nbin - 1) && (histo -> GetErrorYhigh(i+1)) > minError) {YnewHigh = histo -> GetErrorYhigh(i+1);}
          else if (i > 1 && (histo -> GetErrorYhigh(i-1)) > minError){ YnewHigh = histo -> GetErrorYhigh(i-1);}
     }
     if  ((histo -> GetErrorYlow(i)) < minError) {
          if  ( (histo -> GetErrorYhigh(i))  > minError) {YnewLow = histo -> GetErrorYhigh(i);}
          else if (i < (nbin - 1) && (histo -> GetErrorYlow(i+1)) > minError) {YnewLow = histo -> GetErrorYlow(i+1);}
          else if (i > 1 && (histo -> GetErrorYlow(i-1)) > minError) {YnewLow = histo -> GetErrorYlow(i-1);}
     }
     if  ((histo -> GetErrorYhigh(i)) < minError) histo -> SetPointEYhigh(i,YnewHigh);
     if  ((histo -> GetErrorYlow(i)) < minError) histo -> SetPointEYlow(i,YnewLow);

  }

}
