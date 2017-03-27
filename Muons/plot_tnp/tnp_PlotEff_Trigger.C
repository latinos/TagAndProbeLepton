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
void tnp_PlotEff_Trigger( bool isSave = true ) {
  
  gROOT->Clear();
  gStyle->SetOptStat(0);  
  //gStyle->SetTitleSize(0.5);
  //gStyle->SetTitleFont(60);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetCanvasColor(kWhite); 
  //gStyle->SetFillColor(0);
  gStyle->SetOptTitle(kFALSE);

  //double BinEta[] = {-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4}; 
  //// binning for Mu17, Mu18, Mu20 
  ////double BinPt[] = {10, 15, 16, 17, 18, 19, 20, 21, 22,  24,  26, 30, 35, 40, 60, 100, 200};
  //// binning for Mu8
  //double BinPt[] = {10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 60, 100, 200};

  double BinPt[] = {0, 14, 17, 20, 22, 30, 50, 80, 200};
  double BinEta[] = {-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4};


  int BinPtSize = int(sizeof(BinPt)/sizeof(BinPt[0]));
  int BinEtaSize = int(sizeof(BinEta)/sizeof(BinEta[0]));
  cout << "BinPtSize = " << BinPtSize << endl;
  cout << "BinEtaSize = " << BinEtaSize << endl;

  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_25_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_25_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_25_patch2/src/TagAndProbeLepton/Muons/eff_tnp/";

  //change only name of file, check that you use correct pt and eta binning: 

  // for Run2016B:
  //TString sample_data = "TnP_IsoMu18orIsoTkMu18_Run2016B_PTvsETA"; 
  //TString sample_data = "TnP_IsoMu20orIsoTkMu20_Run2016B_PTvsETA"; 
  TString sample_data = "TnP_IsoMu22orIsoTkMu22_Run2016B_PTvsETA"; 
  //TString sample_data = "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2016B_PTvsETA";
  //TString sample_data = "TnP_IsoMu8orIsoTkMu8leg_Run2016B_PTvsETA";
  //TString sample_data = "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2016B_PTvsETA";


  // for 76X

  //TString sample_data = "TnP_IsoMu18_Run2015D_25ns_PTvsETA_binSmall";
  //TString sample_data = "TnP_IsoTkMu20_Run2015D_25ns_PTvsETA_binSmall";
  //TString sample_data = "TnP_IsoTkMu18_Run2015D_25ns_PTvsETA_binSmall";

  //TString sample_data = "TnP_Mu17_IsoTrkVVL_Run2015D_25ns_PTvsETA_binVeryBig";

  //TString sample_data = "TnP_Mu8_IsoTrkVVL_Run2015D_25ns_PTvsETA_binVeryBig";
  //TString sample_data = "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binVeryBig";

  //TString sample_data = "TnP_IsoMu8orIsoTkMu8leg_Run2015D_25ns_PTvsETA_binSmall";
  //TString sample_data = "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2015D_25ns_PTvsETA_binSmall";
  //TString sample_data = "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binVeryBig";

  TString Tag_trig = "_&_tag_IsoMu20_pass";

  TFile* DATA   = TFile::Open(pathAnna+sample_data+".root" );

////////////////////////////////

//  if (sample_data == "TnP_IsoMu18orIsoTkMu20_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu18 or HLT\\_IsoTkMu20}\n";
//  if (sample_data == "TnP_IsoMu18orIsoTkMu20_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu18orIsoTkMu20}\n";
//  if (sample_data == "TnP_IsoMu18_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoMu18}\n";
//  if (sample_data == "TnP_IsoMu18_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoMu18}\n";
//  if (sample_data == "TnP_IsoTkMu18_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoTkMu18}\n";
//  if (sample_data == "TnP_IsoTkMu18_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoTkMu18}\n";
//  if (sample_data == "TnP_IsoTkMu20_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_IsoTkMu20}\n";
//  if (sample_data == "TnP_IsoTkMu20_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_IsoTkMu20}\n";
//
//  if (sample_data == "TnP_IsoMu8orIsoTkMu8leg_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL or HLT\\_TkMu8\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_IsoMu8orIsoTkMu8leg_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8orTkMu8_TrkIsoVVL}\n";
//  if (sample_data == "TnP_IsoMu8orIsoTkMu8leg_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL or HLT\\_TkMu8\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_IsoMu8orIsoTkMu8leg_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8orTkMu8_TrkIsoVVL}\n";
//
//  if (sample_data == "TnP_Mu17_IsoTrkVVL_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu17\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_Mu17_IsoTrkVVL_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu17_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu17\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu17_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu17\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2015D_25ns_PTvsETA_binSmall") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu17_TrkIsoVVL}\n";
//
//  if (sample_data == "TnP_Mu8_IsoTrkVVL_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_Mu8_IsoTrkVVL_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_Mu8\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_Mu8_TrkIsoVVL}\n";
//
//  if (sample_data == "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\caption{Efficiency of HLT\\_TkMu8\\_TrkIsoVVL}\n";
//  if (sample_data == "TnP_DoubleIsoMu17TkMu8_IsoMu8leg_Run2015D_25ns_PTvsETA_binVeryBig") myfile_HWW_tex << "\\label{table:TriggerMuon:HLT_TkMu8_TrkIsoVVL}\n";

////////////////////////////////
  for (int ieta=0; ieta<BinEtaSize-1; ieta++){

     TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta/fit_eff_plots/pt_PLOT_eta_bin%d_&_Medium_pass%s",ieta,Tag_trig.Data() ));
     if(tDATA == 0)cout << "check code: ERROR Canvas = " << tDATA << " ieta = " << ieta << endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     if(grDATA == 0) cout << "check code: ERROR grDATA = " << grDATA << " ieta = " << ieta << endl;

     TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta_ptGt20/fit_eff_plots/pt_PLOT_eta_bin%d_&_Medium_pass%s",ieta,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptGt20 = (TGraphAsymmErrors*) tDATA_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptGt20);

     TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta_ptLt20/fit_eff_plots/pt_PLOT_eta_bin%d_&_Medium_pass%s",ieta,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptLt20 = (TGraphAsymmErrors*) tDATA_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptLt20);


         TCanvas* CanvPlot = new TCanvas("CanvPlot", "", 650, 0, 600, 600);
         grDATA -> SetMinimum(0.0);
         grDATA -> SetMaximum(1.0);
         grDATA -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot->SetLeftMargin(0.15);
         grDATA ->GetXaxis() -> SetRangeUser(10., 80.);

         grDATA -> SetFillColor(629);
         grDATA -> SetLineColor(629);

         grDATA -> GetXaxis()-> SetTitle("Probe P_{T} [GeV]");
         grDATA -> GetYaxis()-> SetTitle("Efficiency");

         grDATA -> GetXaxis()-> SetNdivisions(509);
         grDATA -> GetYaxis()-> SetNdivisions(514);


         CanvPlot->SetGridx();
         CanvPlot->SetGridy();

         grDATA   -> SetMarkerStyle(21);
         grDATA   -> SetMarkerColor(kRed);
         grDATA   -> Draw("AP");
         //gGblMuIdDATA -> Draw("P");

         //if ( ptCut== "_ptGt20") PrintIt(CanvPlot, Title+"|#eta| < 2.4 && p_T > 20 GeV");
         //else if ( ptCut== "_ptLt20") PrintIt(CanvPlot, Title+"|#eta| < 2.4 && 10 < p_T < 20 GeV");
         //else PrintIt(CanvPlot, Title+"|#eta| < 2.4 && p_T > 10 GeV");
         TString PicName = sample_data;
         TLegend* tl = SetLegend(0.32, 0.25, 0.7, 0.4);    
         if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu8leg_Run2016B_PTvsETA") {
             PicName = "DoubleMu_IsoMu8leg_Run2016B_PTvsETA";
             tl->AddEntry(grDATA, "Run 2016B, run>=273423, 120 /pb"           ,"lp");
             tl->AddEntry(grDATA, "IsoMu8 leg eff."     ,"");
         }
         else if (sample_data == "TnP_IsoMu8orIsoTkMu8leg_Run2016B_PTvsETA"){
             PicName = "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016B_PTvsETA";
             tl->AddEntry(grDATA, "Run 2016B, run>=273423, 120 /pb"                     ,"lp");
             tl->AddEntry(grDATA, "IsoMu8||IsoTkMu8 leg eff."     ,"");
         }
         else if (sample_data == "TnP_DoubleIsoMu17Mu8_IsoMu17leg_Run2016B_PTvsETA"){
             PicName = "DoubleMu_IsoMu17leg_Run2016B_PTvsETA";
             tl->AddEntry(grDATA, "Run 2016B, run>=273423, 120 /pb"            ,"lp");
             tl->AddEntry(grDATA, "IsoMu17 leg eff."     ,"");
         }
         else if (sample_data == "TnP_IsoMu20orIsoTkMu20_Run2016B_PTvsETA"){
             PicName = "SingleMu_IsoMu20orIsoTkMu20_Run2016B_PTvsETA";
             tl->AddEntry(grDATA, "Run 2016B, run>=273423, 120 /pb"                          ,"lp");
             tl->AddEntry(grDATA, "HLT_IsoMu20||HLT_IsoTkMu20 eff."     ,"");
         }
         else if (sample_data == "TnP_IsoMu22orIsoTkMu22_Run2016B_PTvsETA"){
             PicName = "SingleMu_IsoMu22orIsoTkMu22_Run2016B_PTvsETA";
             tl->AddEntry(grDATA, "Run 2016B, run>=273423, 120 /pb"                          ,"lp");
             tl->AddEntry(grDATA, "HLT_IsoMu20||HLT_IsoTkMu20 eff."     ,"");
         }
         else if (sample_data == "TnP_IsoMu18orIsoTkMu18_Run2016B_PTvsETA"){
             PicName = "SingleMu_IsoMu18orIsoTkMu18_Run2015D_25ns_PTvsETA";
             tl->AddEntry(grDATA, "Run 2016B, run>=273423,120 /pb"                          ,"lp");
             tl->AddEntry(grDATA, "HLT_IsoMu18||HLT_IsoTkMu18 eff."     ,"");
         }
         else {tl->AddEntry(grDATA, "Run 2016B, Trigger eff."     ,"lp");}

         tl->AddEntry(grDATA, Form("%2.1f<#eta<%2.1f",BinEta[ieta],BinEta[ieta+1])     ,"");
      
         tl->Draw("same");

         CanvPlot -> SaveAs(Form("Plots/%s_eta_bin%d.png",PicName.Data(),ieta));
  }

////////////////////////////////
  if (!isSave) return;

}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     //if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
  }

}
