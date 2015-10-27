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
void tnp_nVer( bool isSave = true ) {
  
  gROOT->Clear();
  gStyle->SetOptStat(0);  
  //gStyle->SetTitleSize(0.5);
  //gStyle->SetTitleFont(60);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetCanvasColor(kWhite); 
  //gStyle->SetFillColor(0);
  gStyle->SetOptTitle(kFALSE);

  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_4_14/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_4_14/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_4_14/src/TagAndProbeLepton/Muons/eff_tnp/";


  //TString PU = "noPU";//for Data
  TString PU = "withPU";//for Data

  TString Run = "Run2015B50ns";
  //TString Run = "Run2015C50ns";
  //TString Run = "Run2015C25ns";
  //TString Run = "Run2015D25ns";

  TString MC = "DY50ns";
  //TString MC = "DY25ns";

  TString MCPlot = "AP";//for Data
  //TString MCPlot = "A2";//for MC if you want <- not used now


  TFile* tnpGblMuIdMC = TFile::Open(pathAnna+"tnp_50nsDY_v3_PUlikeRun2015B_50ns.root" );
  TFile* tnpGblMuIdDATA = TFile::Open(pathAnna+"tnp_Run2015B_PromptReco_50ns_v3.root" );
  if (MC == "DY50ns" && Run == "Run2015B50ns")tnpGblMuIdMC   = TFile::Open(pathAnna+"tnp_50nsDY_v3_PUlikeRun2015B_50ns.root" );
  if (MC == "DY50ns" && Run == "Run2015C50ns")tnpGblMuIdMC   = TFile::Open(pathAnna+"tnp_50nsDY_v3_PUlikeRun2015C_50ns.root" );
  if (MC == "DY25ns" && Run == "Run2015C25ns")tnpGblMuIdMC   = TFile::Open(pathAnna+"tnp_25nsDY_v3_PUlikeRun2015C_25ns.root" );
  if (MC == "DY25ns" && Run == "Run2015D25ns")tnpGblMuIdMC   = TFile::Open(pathAnna+"tnp_25nsDY_v3_PUlikeRun2015D_25ns.root" );
  if (Run == "Run2015B50ns") tnpGblMuIdDATA   = TFile::Open(pathAnna+"tnp_Run2015B_PromptReco_50ns_v3.root" );
  if (Run == "Run2015C50ns") tnpGblMuIdDATA   = TFile::Open(pathAnna+"tnp_Run2015C_PromptReco_50ns_v3.root" );
  if (Run == "Run2015C25ns") tnpGblMuIdDATA   = TFile::Open(pathAnna+"tnp_Run2015C_PromptReco_25ns_v3.root" );
  if (Run == "Run2015D25ns") tnpGblMuIdDATA   = TFile::Open(pathAnna+"tnp_Run2015D_PromptReco_25ns_v3.root" );


  TTree  &tMC =     * (TTree *) tnpGblMuIdMC    ->Get("tpTree/fitter_tree");
  TTree  &tData =   * (TTree *) tnpGblMuIdDATA  ->Get("tpTree/fitter_tree");


   TH1F *hMC_nVer = new TH1F("hMC_nVer","MC #Vertices",50,-0.5,49.5);
   hMC_nVer->Sumw2();
   TH1F *hData_nVer = new TH1F("hData_nVer","Data #Vertices",50,-0.5,49.5);
   hData_nVer->Sumw2();


   //if(PU == "noPU")tMC.Draw("tag_nVertices>>hMC_nVer");
   //if(PU== "withPU")tMC.Draw("tag_nVertices>>hMC_nVer","weight*(tag_nVertices>0)");
   //tData.Draw("tag_nVertices>>hData_nVer");

   if(PU == "noPU")tMC.Draw("tag_nVertices>>hMC_nVer","IsoMu20>0");
   if(PU== "withPU")tMC.Draw("tag_nVertices>>hMC_nVer","weight*(IsoMu20>0)");
   tData.Draw("tag_nVertices>>hData_nVer","IsoMu20>0");


   hMC_nVer->Scale(1.0/hMC_nVer->Integral());
   hData_nVer->Scale(1.0/hData_nVer->Integral());
  // ------------------------------------------------------------------------------

  //TLegend* tl = SetLegend(0.27, 0.12, 0.54, 0.36);
  TLegend* tl = SetLegend(0.45, 0.65, 0.75, 0.85);
     if(PU == "noPU")tl->AddEntry(hMC_nVer, "no PU weight"     ,"");
     if(PU == "withPU")tl->AddEntry(hMC_nVer, "with PU weight"     ,"");
     tl->AddEntry(hMC_nVer, "#sqrt{s} = 13 TeV"     ,"");
     if(MC == "DY50ns")tl->AddEntry(hMC_nVer, "Drell-Yan Spring15, 50 ns"  ,"lp");
     if(MC == "DY25ns")tl->AddEntry(hMC_nVer, "Drell-Yan Spring15, 25 ns"  ,"lp");
     if(Run == "Run2015B50ns")tl->AddEntry(hData_nVer, "DATA 2015B, 50 ns"     ,"lp");
     if(Run == "Run2015C50ns")tl->AddEntry(hData_nVer, "DATA 2015C, 50 ns"     ,"lp");
     if(Run == "Run2015C25ns")tl->AddEntry(hData_nVer, "DATA 2015C, 25 ns"     ,"lp");
     if(Run == "Run2015D25ns")tl->AddEntry(hData_nVer, "DATA 2015D, 25 ns"     ,"lp");
//////////////////////////////
  std::cout <<"test2"<< std::endl;

//////////////////////////////

 // tag_nVertices pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_tag_nVertices = new TCanvas("cGblMuIdvs_tag_nVertices", "", 650, 0, 600, 600);
  //cGblMuIdvs_tag_nVertices->Divide(1,1,0.05,0.05);
  cGblMuIdvs_tag_nVertices->Divide(1,1);
  cGblMuIdvs_tag_nVertices->cd(1);
  //cGblMuIdvs_tag_nVertices->SetLeftMargin(0.25);
  TPad* pad = (TPad*)cGblMuIdvs_tag_nVertices->GetPad(1);
  pad->SetLeftMargin(0.15);
  //gPad -> SetLogx();
  hData_nVer -> SetTitle("p_{T} > 45 GeV/c & |#eta| < 2.1");
  hData_nVer -> GetYaxis()-> SetTitleOffset(1.5);
  hData_nVer -> GetXaxis()-> SetTitleOffset(1.2);
  hData_nVer -> GetYaxis()->SetTitleSize(0.04);
  hData_nVer -> GetXaxis()->SetTitleSize(0.04);
  //hData_nVer -> GetXaxis() -> SetRangeUser(0.5, 25.5);

  //hData_nVer -> SetFillColor(629);
  //hData_nVer -> SetLineColor(629);

  hData_nVer -> GetXaxis()-> SetTitle("# Vertices");
  hData_nVer -> GetYaxis()-> SetTitle("Entries, normalized to 1");

  hData_nVer -> GetXaxis()-> SetNdivisions(509);
  hData_nVer -> GetYaxis()-> SetNdivisions(514);


  //cGblMuIdvs_tag_nVertices->SetGridx();
  //cGblMuIdvs_tag_nVertices->SetGridy();

  hData_nVer   -> SetMarkerStyle(22);
  hData_nVer   -> SetMarkerColor(kBlue);
  //hData_nVer   -> Draw(MCPlot);
  hData_nVer   -> Draw("e");
/////  hData_nVer -> Draw("P");
//

  hMC_nVer -> SetFillColor(629);
  hMC_nVer -> SetLineColor(629);
  hMC_nVer   -> SetMarkerStyle(21);
  hMC_nVer   -> SetMarkerColor(kRed);
  hMC_nVer -> Draw("esame");
  tl->Draw("same");

  //PrintIt(cGblMuIdvs_tag_nVertices, +"|#eta| < 2.4 && p_T > 20 GeV");


////////////////////////////////




  if (!isSave) return;

  // print pictures
  cGblMuIdvs_tag_nVertices  -> SaveAs(png+"nVertices_"+Run+"_"+MC+"_"+PU+".png"); 
}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
  }

}
