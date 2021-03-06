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
void tnp_PlotEff_ID( bool isSave = true ) {
  
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
  // binning for Mu22, Mu24, Mu23 
  double BinPt[] = {10, 20, 21, 22, 23, 24, 25, 26, 30, 40, 60, 100, 200};
  // binning for Mu8 and Muon ID and ISO
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

  // for Run2016B:
  
  //TString sample_data = "TightID_Run2016_PTvsETA"; 
  //TString sample_data = "ISOTight_Run2016_PTvsETA"; 
  //TString sample_data = "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA"; 
  //TString sample_data = "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA"; 
  //TString sample_data = "DoubleMu_IsoMu17leg_Run2016_PTvsETA";
  TString sample_data = "DoubleMu_IsoMu23leg_Run2016_PTvsETA";
  //TString sample_data = "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA";
  //TString sample_data = "DoubleMu_IsoMu8leg_Run2016_PTvsETA";


  TString Sample_extra = "";
  TString Tag_trig = "";
  TString MuonID = "Tight_ID";
  if (sample_data == "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA" || sample_data == "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA"
      || sample_data == "DoubleMu_IsoMu17leg_Run2016_PTvsETA"
      || sample_data == "DoubleMu_IsoMu23leg_Run2016_PTvsETA"
      || sample_data == "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA"
      || sample_data == "DoubleMu_IsoMu8leg_Run2016_PTvsETA"){
     MuonID = "Trigger";
     Tag_trig = "_&_Tight2012_pass";
     Sample_extra = "_Run274094to275000";
  }

  if (sample_data == "ISOTight_Run2016_PTvsETA" || sample_data == "ISOTight_DY_madgraphLikeRun2016_PTvsETA" ) {
          MuonID   = "Tight_ISO";
          Tag_trig = "_&_Tight2012_pass"+ Tag_trig;
  }
  if (sample_data == "ISOTight_DY_madgraphLikeRun2016_PTvsETA") MuonID   = "Medium_ISO_ptVSeta"; //forgot to change name to Tight

  //TFile* DATA   = TFile::Open(pathAnna+sample_data+"_Fill5043.root" );
  //TFile* DATA_start   = TFile::Open(pathAnna+"root_Run274421/"+sample_data+Sample_extra+".root" );

  TString DATA_String = pathAnna+sample_data+"_Run276501to276811.root";
  TString DATA_start_String = pathAnna+sample_data+Sample_extra+".root";
  if (sample_data == "TightID_Run2016_PTvsETA"){
     DATA_String = pathAnna+"TightID_Run2016_Run276501to276811_PTvsETA.root";
     DATA_start_String = pathAnna+"TightID_Run2016_Run271036to275783_PTvsETA.root";
  }
  if (sample_data == "ISOTight_Run2016_PTvsETA"){
     DATA_String = pathAnna+ "ISOTight_Run2016_Run276501to276811_PTvsETA.root";
     DATA_start_String = pathAnna+ "ISOTight_Run2016_Run271036to275783_PTvsETA.root";
  }
  //TFile* DATA   = TFile::Open(pathAnna+sample_data+"_Run276501to276811.root" );
  //TFile* DATA_start   = TFile::Open(pathAnna+sample_data+Sample_extra+".root" );
  TFile* DATA   = TFile::Open(DATA_String);
  TFile* DATA_start   = TFile::Open(DATA_start_String);

////////////////////////////////

////////////////////////////////
  for (int ipt=0; ipt<BinPtSize-1; ipt++){

// open DATA:
  //std::cout << "TEST!!! " << std::endl;
     TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/%s_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d%s",MuonID.Data(),ipt,Tag_trig.Data() ));
     //TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d_&_Tight2012_pass%s",ipt,Tag_trig.Data() ));

     if(tDATA == 0)cout << "check code: ERROR Canvas = " << tDATA << " ipt = " << ipt << endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     if(grDATA == 0) cout << "check code: ERROR grDATA = " << grDATA << " ipt = " << ipt << endl;

     TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/%s_ptVSeta_ptGt20/fit_eff_plots/eta_PLOT_pt_bin%d%s",MuonID.Data(),ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptGt20 = (TGraphAsymmErrors*) tDATA_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptGt20);

     TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/%s_ptVSeta_ptLt20/fit_eff_plots/eta_PLOT_pt_bin%d%s",MuonID.Data(),ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptLt20 = (TGraphAsymmErrors*) tDATA_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptLt20);

// open DATA_start
     TCanvas* tDATA_start = (TCanvas*) DATA_start->Get(Form("tpTree/%s_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d%s",MuonID.Data(),ipt,Tag_trig.Data() ));
     if(tDATA_start == 0)cout << "check code: ERROR Canvas start = " << tDATA_start << " ipt = " << ipt << endl;
     TGraphAsymmErrors* grDATA_start = (TGraphAsymmErrors*) tDATA_start -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_start);
     if(grDATA_start == 0) cout << "check code: ERROR grDATA_start = " << grDATA_start << " ipt = " << ipt << endl;

     TCanvas* tDATA_start_ptGt20 = (TCanvas*) DATA_start->Get(Form("tpTree/%s_ptVSeta_ptGt20/fit_eff_plots/eta_PLOT_pt_bin%d%s",MuonID.Data(),ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_start_ptGt20 = (TGraphAsymmErrors*) tDATA_start_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_start_ptGt20);

     TCanvas* tDATA_start_ptLt20 = (TCanvas*) DATA_start->Get(Form("tpTree/%s_ptVSeta_ptLt20/fit_eff_plots/eta_PLOT_pt_bin%d%s",MuonID.Data(),ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_start_ptLt20 = (TGraphAsymmErrors*) tDATA_start_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_start_ptLt20);

         TCanvas* CanvPlot = new TCanvas("CanvPlot", "", 650, 0, 600, 600);
         grDATA -> SetMinimum(0.5);
         grDATA -> SetMaximum(1.0);
         grDATA -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot->SetLeftMargin(0.15);
         grDATA ->GetXaxis() -> SetRangeUser(10., 100.);

         grDATA -> SetFillColor(629);
         grDATA -> SetLineColor(629);

         grDATA -> GetXaxis()-> SetTitle("Probe #eta");
         grDATA -> GetYaxis()-> SetTitle("Efficiency");

         grDATA -> GetXaxis()-> SetNdivisions(509);
         grDATA -> GetYaxis()-> SetNdivisions(514);


         CanvPlot->SetGridx();
         CanvPlot->SetGridy();

         grDATA   -> SetMarkerStyle(21);
         grDATA   -> SetMarkerColor(kRed);
         grDATA   -> Draw("AP");
         grDATA_start   -> SetMarkerStyle(20);
         grDATA_start   -> SetMarkerColor(kBlue);
         grDATA_start -> SetLineColor(kBlue);
         grDATA_start   -> Draw("P");
         //gGblMuIdDATA -> Draw("P");

         //if ( ptCut== "_ptGt20") PrintIt(CanvPlot, Title+"|#eta| < 2.4 && p_T > 20 GeV");
         //else if ( ptCut== "_ptLt20") PrintIt(CanvPlot, Title+"|#eta| < 2.4 && 10 < p_T < 20 GeV");
         //else PrintIt(CanvPlot, Title+"|#eta| < 2.4 && p_T > 10 GeV");
         TString PicName = sample_data;
         TLegend* tl = SetLegend(0.15, 0.2, 0.7, 0.4);    
         if (sample_data == "DoubleMu_IsoMu8leg_Run2016_PTvsETA") {
             tl->AddEntry(grDATA, "Data 2016, IsoMu8 leg eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 274094-275000"                          ,"lp");
         }
         else if (sample_data == "DoubleMu_IsoMu8orIsoTkMu8leg_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, IsoMu8||IsoTkMu8 leg eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 274094-275000"                          ,"lp");
         }
         else if (sample_data == "DoubleMu_IsoMu17leg_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, IsoMu17 leg eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 274094-275000"                          ,"lp");
         }
         else if (sample_data == "DoubleMu_IsoMu23leg_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, IsoMu23 leg eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 274094-275000"                          ,"lp");
         }
         else if (sample_data == "SingleMu_IsoMu22orIsoTkMu22_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, HLT_IsoMu22||HLT_IsoTkMu22 eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 274094-275000"                          ,"lp");
         }
         else if (sample_data == "SingleMu_IsoMu24orIsoTkMu24_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, HLT_IsoMu24||HLT_IsoTkMu24 eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 274094-275000"                          ,"lp");
         }
         else if (sample_data == "TightID_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, Tight ID eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 271036-275783"                          ,"lp");
         }
         else if (sample_data == "ISOTight_Run2016_PTvsETA"){
             tl->AddEntry(grDATA, "Data 2016, ISO Tight eff."     ,"");
             tl->AddEntry(grDATA, " end: Run 276501-276811"                          ,"lp");
             tl->AddEntry(grDATA_start, "start: Run 271036-275783"                          ,"lp");
         }
         else {tl->AddEntry(grDATA, "Run 2016, Trigger eff."     ,"lp");}

         PicName = sample_data;
         tl->AddEntry(grDATA, Form("%3.0f < p_{T} < %3.0f GeV/c",BinPt[ipt],BinPt[ipt+1])     ,"");
      
         tl->Draw("same");

         CanvPlot -> SaveAs(Form("Plots/%s_pt_bin%d.png",PicName.Data(),ipt));
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
