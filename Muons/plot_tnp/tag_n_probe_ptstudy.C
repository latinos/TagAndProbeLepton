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
void tag_n_probe_ptstudy( bool isSave = true ) {
  
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
  TString png      = "/data/uftrig01b/kropiv/tnp/CMSSW_4_2_8_patch6/src/tnp/eff_tnp/tnp_plot/rootPlot/";
  TString rootPlot = "/data/uftrig01b/kropiv/tnp/CMSSW_4_2_8_patch6/src/tnp/eff_tnp/tnp_plot/rootPlot/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/data/uftrig01b/kropiv/tnp/CMSSW_4_2_8_patch6/src/tnp/eff_tnp/";

  TString MCPlot = "AP";//for Data
  //TString MCPlot = "A2";//for MC if you want <- not used now


  int Comparison = 2; 
   // 1  - MuonID DATA2011AB Tight vs Medium
   // 2  - MuonID DATA2011AB Tight vs MC_DY Tight
   // 3  - MuonID DATA2011AB Medium vs MC_DY Medium
   // 4  - MuonID MC_DY Tight vs MC_D_TagMedium Tight 
   // 11 - HLT DATA2011A vs DATA2011B
   // 21 - Iso DATA2011AB Tight vs Medium
   // 22 - Iso DATA2011AB Tight vs MC_DY Tight
   // 31 - Tracker DATA2011AB vs MC-DY 

  // DATA Tight vs Medium
  Float_t xmin = 0.96; 
  Float_t xmax = 1.01; 
  TString EffType = "muonEffs";
  TString index_data = "";//for Muon ID
  TString index_mc = "";//for Muon ID
  TString MuonAdd = "Muon";
  TString MuonType = "Tight";
  TString MCMuonType = "Medium";
  TString DataType = "data_Run2011AB"; 
  TString MCType = "data_Run2011AB"; 
  TString Title = "Tag #mu: is Tight, Probe #mu: "; 

  if(Comparison == 1){ // MuonID DATA2011AB Tight vs Medium 
     xmin = 0.8; 
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "";//for Muon ID
     index_mc = "";//for Muon ID
     MuonAdd = "Muon";
     MuonType = "Tight";
     MCMuonType = "Medium";
     DataType = "data_Run2011AB"; 
     MCType = "data_Run2011AB"; 
     Title = "Tag #mu: is Tight, Probe #mu: is Tracker & "; 
  }
  if(Comparison == 2){ // MuonID DATA2011AB Tight vs MC_DY Tight
     xmin = 0.8; 
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "";//for Muon ID
     index_mc = "";//for Muon ID
     MuonAdd = "Muon";
     MuonType = "Tight";
     MCMuonType = "Tight";
     DataType = "data_Run2011AB"; 
     MCType = "MC_DY"; 
     Title = "Tag #mu: is Tight, Probe #mu: is Tracker & "; 
  }
  if(Comparison == 3){ // MuonID DATA2011AB Medium vs MC_DY Medium
     xmin = 0.8; 
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "";//for Muon ID
     index_mc = "";//for Muon ID
     MuonAdd = "Muon";
     MuonType = "Medium";
     MCMuonType = "Medium";
     DataType = "data_Run2011AB"; 
     MCType = "MC_DY"; 
     Title = "Tag #mu: is Tight, Probe #mu: is Tracker & "; 
  }
  if(Comparison == 4){ // MuonID MC_DY Tight vs MC_D_TagMedium Tight
     xmin = 0.8;
     xmax = 1.01;
     EffType = "muonEffs";
     index_data = "";//for Muon ID
     index_mc = "";//for Muon ID
     MuonAdd = "Muon";
     MuonType = "Tight";
     MCMuonType = "Tight";
     DataType = "MC_DY_TagMedium";
     MCType = "MC_DY";
     Title = "Tag #mu: is Tight/Medium, Probe #mu: is Tracker & ";
  }
  if(Comparison == 5){ // MuonID DATA2011A Tight vs DATA2011B Tight 
     xmin = 0.8;  
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "";//for Muon ID
     index_mc = "";//for Muon ID
     MuonAdd = "Muon";
     MuonType = "Tight";
     MCMuonType = "Tight";
     DataType = "data_Run2011A";
     MCType = "data_Run2011B";
     Title = "Tag #mu: is Tight, Probe #mu: is Tracker & "; 
  }  

  if(Comparison == 11){ // HLT DATA2011A vs DATA2011B 
     xmin = 0.8; 
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "_&_isIsoTrkRel_true_&_isMuonTight_true";//for HLT 
     index_mc = "_&_isIsoTrkRel_true_&_isMuonTight_true";//for HLT 
     MuonAdd = "MuonTight";
     MuonType = "HLT30";
     MCMuonType = "HLT40_eta2p1";
     DataType = "data_Run2011A"; 
     MCType = "data_Run2011B"; 
     Title = "Tag & Probe #mu: are Tight, Probe #mu: TkrRelIso < 0.1 & "; 
  }
  if(Comparison == 21){ // Iso DATA2011AB Tight vs Medium
     xmin = 0.96; 
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "_&_tag_isoTrkRel_bin0_&_isMuonTight_true";//for ISO
     index_mc = "_&_tag_isoTrkRel_bin0_&_isMuonMedium_true";//for ISO
     MuonAdd = "Muon";
     MuonType = "Tight_ISO";
     MCMuonType = "Medium_ISO";
     DataType = "data_Run2011AB"; 
     MCType = "data_Run2011AB"; 
     Title = "Tag #mu: is Tight & TkrRelIso < 0.1, Probe #mu: "; 
  } 
  if(Comparison == 22){ // Iso DATA2011AB Tight vs MC_DY Tight
     xmin = 0.96; 
     xmax = 1.01; 
     EffType = "muonEffs";
     index_data = "_&_tag_isoTrkRel_bin0_&_isMuonTight_true";//for ISO
     index_mc = "_&_tag_isoTrkRel_bin0_&_isMuonTight_true";//for ISO
     MuonAdd = "Muon";
     MuonType = "Tight_ISO";
     MCMuonType = "Tight_ISO";
     DataType = "data_Run2011AB"; 
     MCType = "MC_DY"; 
     Title = "Tag #mu: is Tight & TkrRelIso < 0.1, Probe #mu: "; 
  } 
  if(Comparison == 31){ // Tracker DATA2011AB vs MC-DY 
     xmin = 0.96; 
     xmax = 1.01; 
     EffType = "staEffs";
     index_data = ""; 
     index_mc = ""; 
     MuonAdd = "Muonis";
     MuonType = "Tracker";
     MCMuonType = "Tracker";
     DataType = "data_Run2011AB"; 
     MCType = "MC_DY"; 
     Title = "Tag #mu: is Tight, Probe #mu: is SA & "; 
  }

  TString sample_data = MuonAdd+MuonType+"_"+DataType+"_"+EffType;
  TString sample_mc = MuonAdd+MCMuonType+"_"+MCType;

  TFile* tnpGblMuIdMC   = TFile::Open(pathAnna+"tagProbeFitTree_"+MuonAdd+MCMuonType+"_"+MCType+"_good.root" );
  TFile* tnpGblMuIdDATA   = TFile::Open(pathAnna+"tagProbeFitTree_"+MuonAdd+MuonType+"_"+DataType+"_good.root" );


  std::cout << std::endl;
  std::cout<<" * GBLMUID MC   ="<<tnpGblMuIdMC  ->GetName()<<" >> "<<tnpGblMuIdMC  <<std::endl;
  std::cout<<" * GBLMUID DATA ="<<tnpGblMuIdDATA->GetName()<<" >> "<<tnpGblMuIdDATA<<std::endl;
  std::cout << std::endl;

  // ------------------------------------------------------------------------------
  // get the canvas first
  //TCanvas* cGblMuIdMC   = (TCanvas*) tnpGblMuIdMC  ->Get("muonEffs/pt/fit_eff_plots/pt_PLOT");
  //TCanvas* cGblMuIdDATA = (TCanvas*) tnpGblMuIdDATA->Get("muonEffs/pt/fit_eff_plots/pt_PLOT");
  TCanvas* cGblMuIdMC   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pt/fit_eff_plots/pt_PLOT_eta_bin0"+index_mc);
  TCanvas* cGblMuIdDATA = (TCanvas*) tnpGblMuIdDATA->Get(EffType+"/pt/fit_eff_plots/pt_PLOT_eta_bin0"+index_data);
  TCanvas* cGblMuIdMC_eta   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/eta_pt45/fit_eff_plots/eta_PLOT_pt_bin0"+index_mc);
  TCanvas* cGblMuIdDATA_eta = (TCanvas*) tnpGblMuIdDATA->Get(EffType+"/eta_pt45/fit_eff_plots/eta_PLOT_pt_bin0"+index_data);
  TCanvas* cGblMuIdMC_phi   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/phi_pt45/fit_eff_plots/phi_PLOT_eta_bin0_&_pt_bin0"+index_mc);
  TCanvas* cGblMuIdDATA_phi = (TCanvas*) tnpGblMuIdDATA->Get(EffType+"/phi_pt45/fit_eff_plots/phi_PLOT_eta_bin0_&_pt_bin0"+index_data);
  TCanvas* cGblMuIdMC_pair_deltaR   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pair_deltaR_isGlobal_pt45/fit_eff_plots/pair_deltaR_PLOT_eta_bin0_&_pt_bin0"+index_mc);
  TCanvas* cGblMuIdDATA_pair_deltaR   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/pair_deltaR_isGlobal_pt45/fit_eff_plots/pair_deltaR_PLOT_eta_bin0_&_pt_bin0"+index_data);
  TCanvas* cGblMuIdMC_tag_nVertices   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/tag_nVertices_pt45/fit_eff_plots/tag_nVertices_PLOT_eta_bin0_&_pt_bin0"+index_mc);
  TCanvas* cGblMuIdDATA_tag_nVertices   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/tag_nVertices_pt45/fit_eff_plots/tag_nVertices_PLOT_eta_bin0_&_pt_bin0"+index_data);

  // and the graph afterwards

  TGraphAsymmErrors* gGblMuIdMC   = (TGraphAsymmErrors*) cGblMuIdMC   -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdDATA = (TGraphAsymmErrors*) cGblMuIdDATA -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdMC_eta   = (TGraphAsymmErrors*) cGblMuIdMC_eta   -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdDATA_eta = (TGraphAsymmErrors*) cGblMuIdDATA_eta -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdMC_phi   = (TGraphAsymmErrors*) cGblMuIdMC_phi   -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdDATA_phi = (TGraphAsymmErrors*) cGblMuIdDATA_phi -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdMC_pair_deltaR   = (TGraphAsymmErrors*) cGblMuIdMC_pair_deltaR   -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdDATA_pair_deltaR   = (TGraphAsymmErrors*) cGblMuIdDATA_pair_deltaR   -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdMC_tag_nVertices   = (TGraphAsymmErrors*) cGblMuIdMC_tag_nVertices   -> GetListOfPrimitives()->At(2);
  TGraphAsymmErrors* gGblMuIdDATA_tag_nVertices   = (TGraphAsymmErrors*) cGblMuIdDATA_tag_nVertices   -> GetListOfPrimitives()->At(2);
  ErrorCheck(gGblMuIdMC);
  ErrorCheck(gGblMuIdDATA);
  ErrorCheck(gGblMuIdMC_eta);
  ErrorCheck(gGblMuIdDATA_eta);
  ErrorCheck(gGblMuIdMC_phi);
  ErrorCheck(gGblMuIdDATA_phi);
  ErrorCheck(gGblMuIdMC_pair_deltaR);
  ErrorCheck(gGblMuIdDATA_pair_deltaR);
  ErrorCheck(gGblMuIdMC_tag_nVertices);
  ErrorCheck(gGblMuIdDATA_tag_nVertices);

  // ------------------------------------------------------------------------------

  TLegend* tl = SetLegend(0.27, 0.12, 0.54, 0.36);
  // MuonID DATA2011AB Tight vs Medium
  // Iso DATA2011AB Tight vs Medium
  if(Comparison == 1 || Comparison == 21){ 
     tl->AddEntry(gGblMuIdMC, "DATA 2011, is "+MCMuonType+" #mu"     ,"lp");
     tl->AddEntry(gGblMuIdMC, "#int L=4.6 fb^{-1}, #sqrt{s} = 7 TeV"     ,"");
     tl->AddEntry(gGblMuIdDATA, "DATA 2011, is "+MuonType+" #mu"     ,"lp");
     tl->AddEntry(gGblMuIdDATA, "#int L=4.6 fb^{-1}, #sqrt{s} = 7 TeV"     ,"");
  }
  // MuonID DATA2011AB Tight vs MC_DY Tight
  // MuonID DATA2011AB Medium vs MC_DY Medium
  // Iso DATA2011AB Tight MC_DY Tight
  // Tracker DATA2011AB vs MC-DY
  if(Comparison == 2 || Comparison == 3 || Comparison == 22 || Comparison == 31){
     tl->AddEntry(gGblMuIdMC, "Drell-Yan 2011, is "+MCMuonType+" #mu, #sqrt{s} = 7 TeV"     ,"lp");
     tl->AddEntry(gGblMuIdDATA, "DATA 2011, is "+MuonType+" #mu"     ,"lp");
     tl->AddEntry(gGblMuIdDATA, "#int L=4.6 fb^{-1}, #sqrt{s} = 7 TeV"     ,"");
  }
  // MuonID MC_DY Tight vs MC_D_TagMedium Tight
  if(Comparison == 4){
     tl->AddEntry(gGblMuIdMC, "Drell-Yan 2011 Tight tag #mu, is "+MCMuonType+" #mu"     ,"lp");
     tl->AddEntry(gGblMuIdDATA, "Drell-Yan 2011 Medium tag #mu, is "+MuonType+" #mu"     ,"lp");
  }
  // MuonID DATA2011A Tight vs DATA2011B Tight
  // HLT DATA2011A vs DATA2011B 
  if(Comparison == 5 || Comparison == 11){ 
     tl->AddEntry(gGblMuIdMC, "DATA 2011B, is "+MCMuonType+" #mu"     ,"lp");
     tl->AddEntry(gGblMuIdMC, "#int L=2.5 fb^{-1}, #sqrt{s} = 7 TeV"     ,"");
     tl->AddEntry(gGblMuIdDATA, "DATA 2011A, is "+MuonType+" #mu"     ,"lp");
     tl->AddEntry(gGblMuIdDATA, "#int L=2.1 fb^{-1}, #sqrt{s} = 7 TeV"     ,"");
  }
//////////////////////////////
//////////////////////////////

//////////////////////////////
  // GBL + Muon ID
  TCanvas* cGblMuIdvsPt = new TCanvas("cGblMuIdvsPt", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC -> SetTitle(Title+"|#eta| < 2.1");
  gGblMuIdMC -> SetMinimum(xmin);
  gGblMuIdMC -> SetMaximum(xmax);
  gGblMuIdMC -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvsPt->SetLeftMargin(0.15);
  gGblMuIdMC ->GetXaxis() -> SetRangeUser(45., 300.);
     
  gGblMuIdMC -> SetFillColor(629);
  gGblMuIdMC -> SetLineColor(629);
     
  gGblMuIdMC -> GetXaxis()-> SetTitle("Probe P_{T}");
  gGblMuIdMC -> GetYaxis()-> SetTitle("Efficiency");
   
  gGblMuIdMC -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvsPt->SetGridx();
  cGblMuIdvsPt->SetGridy();

  //gGblMuIdMC   -> Draw(MCPlot);
  gGblMuIdMC   -> SetMarkerStyle(21);
  gGblMuIdMC   -> SetMarkerColor(kRed);
  gGblMuIdMC   -> Draw(MCPlot);
  gGblMuIdDATA -> Draw("P");

  tl->Draw("same");
  PrintIt(cGblMuIdvsPt, Title+"|#eta| < 2.1");
 
//////////////////////////////
 // eta pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_eta = new TCanvas("cGblMuIdvs_eta", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_eta -> SetTitle(Title+"p_{T} > 45 GeV/c");
  gGblMuIdMC_eta -> SetMinimum(xmin);
  gGblMuIdMC_eta -> SetMaximum(xmax);
  gGblMuIdMC_eta -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_eta->SetLeftMargin(0.15);
  gGblMuIdMC_eta ->GetXaxis() -> SetRangeUser(-2.1, 2.1);

  gGblMuIdMC_eta -> SetFillColor(629);
  gGblMuIdMC_eta -> SetLineColor(629);

  gGblMuIdMC_eta -> GetXaxis()-> SetTitle("Probe #eta");
  gGblMuIdMC_eta -> GetYaxis()-> SetTitle("Efficiency");

  gGblMuIdMC_eta -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_eta -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_eta->SetGridx();
  cGblMuIdvs_eta->SetGridy();

  gGblMuIdMC_eta   -> SetMarkerStyle(21);
  gGblMuIdMC_eta   -> SetMarkerColor(kRed);
  gGblMuIdMC_eta   -> Draw(MCPlot);
  gGblMuIdDATA_eta -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_eta, Title+"p_{T} > 45 GeV/c");
//////////////////////////////
 // phi pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_phi = new TCanvas("cGblMuIdvs_phi", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_phi -> SetTitle(Title+"p_{T} > 45 GeV/c & |#eta| < 2.1");
  gGblMuIdMC_phi -> SetMinimum(xmin);
  gGblMuIdMC_phi -> SetMaximum(xmax);
  gGblMuIdMC_phi -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_phi->SetLeftMargin(0.15);
  gGblMuIdMC_phi ->GetXaxis() -> SetRangeUser(-3.142, 3.142);

  gGblMuIdMC_phi -> SetFillColor(629);
  gGblMuIdMC_phi -> SetLineColor(629);

  gGblMuIdMC_phi -> GetXaxis()-> SetTitle("Probe #phi");
  gGblMuIdMC_phi -> GetYaxis()-> SetTitle("Efficiency");

  gGblMuIdMC_phi -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_phi -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_phi->SetGridx();
  cGblMuIdvs_phi->SetGridy();

  gGblMuIdMC_phi   -> SetMarkerStyle(21);
  gGblMuIdMC_phi   -> SetMarkerColor(kRed);
  gGblMuIdMC_phi   -> Draw(MCPlot);
  gGblMuIdDATA_phi -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_phi, Title+"p_{T} > 45 GeV/c & |#eta| < 2.1");
//////////////////////////////
 // pair_deltaR pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_pair_deltaR = new TCanvas("cGblMuIdvs_pair_deltaR", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_pair_deltaR -> SetTitle(Title+"p_{T} > 45 GeV/c & |#eta| < 2.1");
  gGblMuIdMC_pair_deltaR -> SetMinimum(xmin);
  gGblMuIdMC_pair_deltaR -> SetMaximum(xmax);
  gGblMuIdMC_pair_deltaR -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_pair_deltaR->SetLeftMargin(0.15);
  gGblMuIdMC_pair_deltaR ->GetXaxis() -> SetRangeUser(0.,3.);

  gGblMuIdMC_pair_deltaR -> SetFillColor(629);
  gGblMuIdMC_pair_deltaR -> SetLineColor(629);

  gGblMuIdMC_pair_deltaR -> GetXaxis()-> SetTitle("Pair #DeltaR");
  gGblMuIdMC_pair_deltaR -> GetYaxis()-> SetTitle("Efficiency");

  gGblMuIdMC_pair_deltaR -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_pair_deltaR -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_pair_deltaR->SetGridx();
  cGblMuIdvs_pair_deltaR->SetGridy();

  gGblMuIdMC_pair_deltaR   -> SetMarkerStyle(21);
  gGblMuIdMC_pair_deltaR   -> SetMarkerColor(kRed);
  gGblMuIdMC_pair_deltaR   -> Draw(MCPlot);
  gGblMuIdDATA_pair_deltaR -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_pair_deltaR, Title+"p_{T} > 45 GeV/c & |#eta| < 2.1");
//////////////////////////////

 // tag_nVertices pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_tag_nVertices = new TCanvas("cGblMuIdvs_tag_nVertices", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_tag_nVertices -> SetTitle(Title+"p_{T} > 45 GeV/c & |#eta| < 2.1");
  gGblMuIdMC_tag_nVertices -> SetMinimum(xmin);
  gGblMuIdMC_tag_nVertices -> SetMaximum(xmax);
  gGblMuIdMC_tag_nVertices -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_tag_nVertices->SetLeftMargin(0.15);
  gGblMuIdMC_tag_nVertices ->GetXaxis() -> SetRangeUser(0.5, 25.5);

  gGblMuIdMC_tag_nVertices -> SetFillColor(629);
  gGblMuIdMC_tag_nVertices -> SetLineColor(629);

  gGblMuIdMC_tag_nVertices -> GetXaxis()-> SetTitle("# Vertices");
  gGblMuIdMC_tag_nVertices -> GetYaxis()-> SetTitle("Efficiency");

  gGblMuIdMC_tag_nVertices -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_tag_nVertices -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_tag_nVertices->SetGridx();
  cGblMuIdvs_tag_nVertices->SetGridy();

  gGblMuIdMC_tag_nVertices   -> SetMarkerStyle(21);
  gGblMuIdMC_tag_nVertices   -> SetMarkerColor(kRed);
  gGblMuIdMC_tag_nVertices   -> Draw(MCPlot);
  gGblMuIdDATA_tag_nVertices -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_tag_nVertices, Title+"p_{T} > 45 GeV/c & |#eta| < 2.1");
//////////////////////////////




  if (!isSave) return;

  // print pictures
  cGblMuIdvsPt  -> SaveAs(png+sample_data+"_"+sample_mc+"_pt.png"); 
  cGblMuIdvs_eta  -> SaveAs(png+sample_data+"_"+sample_mc+"_eta.png"); 
  cGblMuIdvs_phi  -> SaveAs(png+sample_data+"_"+sample_mc+"_phi.png"); 
  cGblMuIdvs_tag_nVertices  -> SaveAs(png+sample_data+"_"+sample_mc+"_nVertices.png"); 
  cGblMuIdvs_pair_deltaR  -> SaveAs(png+sample_data+"_"+sample_mc+"_deltaR.png"); 
  // print root files

  cGblMuIdvsPt  -> SaveAs(rootPlot+sample_data+"_"+sample_mc+"_pt.root"); 
  cGblMuIdvs_eta  -> SaveAs(rootPlot+sample_data+"_"+sample_mc+"_eta.root"); 
  cGblMuIdvs_phi  -> SaveAs(rootPlot+sample_data+"_"+sample_mc+"_phi.root"); 
  cGblMuIdvs_tag_nVertices  -> SaveAs(rootPlot+sample_data+"_"+sample_mc+"_nVertices.root"); 
  cGblMuIdvs_pair_deltaR  -> SaveAs(rootPlot+sample_data+"_"+sample_mc+"_deltaR.root"); 
}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
  }

}
