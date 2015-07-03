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
void tag_n_probe_trigger( bool isSave = true ) {
  
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
  TString png      = "/afs/cern.ch/work/k/kropiv/SMP/Trigger_HLT_Mu17_MuTr18/CMSSW_5_3_9/src/tnp/eff_tnp/tnp_plot/rootPlot/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/SMP/Trigger_HLT_Mu17_MuTr18/CMSSW_5_3_9/src/tnp/eff_tnp/";

  TString MCPlot = "AP";//for Data
  //TString MCPlot = "A2";//for MC if you want <- not used now


  int Comparison = 12; 
   // 1  - MuonID DATA2011AB Tight vs Medium
   // 2  - MuonID DATA2011AB Tight vs MC_DY Tight
   // 3  - MuonID DATA2011AB Medium vs MC_DY Medium
   // 4  - MuonID MC_DY Tight vs MC_D_TagMedium Tight 
   // 11 - J/psi HLT DATA2012 vs MC
   // 21 - Iso DATA2011AB Tight vs Medium
   // 22 - Iso DATA2011AB Tight vs MC_DY Tight
   // 31 - Tracker DATA2011AB vs MC-DY 

  // DATA Tight vs Medium
  Float_t xmin = 0.96; 
  Float_t xmax = 1.01; 
  TString EffType = "muonEffs";
  TString index_base = "";//for Muon ID
  TString index_data = "";//for Muon ID
  TString index_title = "";//for pic title 
  TString index_mc = "";//for Muon ID
  TString MuonAdd = "Muon";
  TString MuonType = "Tight";
  TString MCMuonType = "Medium";
  TString DataType = "data_Run2011AB"; 
  TString MCType = "data_Run2011AB"; 
  TString Title = "Tag #mu: is Tight & matched to HLT_Mu17, Probe #mu: "; 
  TString titleX = "Efficiency";
  TString Extra = ""; 

  if(Comparison == 11 || Comparison == 12 || Comparison ==13 || Comparison == 14 || Comparison == 15){ // HLT DATA2011A vs DATA2011B 
     xmin = 0.0; 
     xmax = 1.05; 
     EffType = "muonEffs";
     //index_base = "_&_isMuonMedium_true";//for HLT 
     index_base = "_isMuonMedium_true";//for HLT 
     MuonAdd = "";
     if(Comparison == 12){
          MuonAdd = "MuonArbitrate_";
          index_base = "_isMuonMedium_arbitrate_true";//for HLT 
          index_base = index_base+"_&_tag_isHLTCut_Mu17_true";
          index_title = index_base+"_true_tag_isHLTCut_Mu17_true";//for picture title
     }
     if(Comparison == 13){
          MuonAdd = "MuonMediumTight_";
          index_base = "_isMuonMedium_tight_true";//for HLT 
     }
     if(Comparison == 14){
          MuonAdd = "MuonLoose_";
          index_base = "_isMuonMedium_loose_true";//for HLT 
     }
     if(Comparison == 15){
          MuonAdd = "MuonStMatch_";
          index_base = "_isMuonMedium_stMatch_true";//for HLT 
     }
     index_data = index_base;//for HLT 
     index_mc = index_base;//for HLT 
     MuonType = "HLT_Mu17_MuTk8";
     MCMuonType = MuonType;
     DataType = "data_Run2012_22Jan2013_JPsi"; 
     MCType = "mc_WJDmcTnP"; 
     Title = "Tag #mu: is Tight & matched to HLT_Mu17, Probe #mu: is Medium"; 
     titleX = "HLT #epsilon(MuTr8|Mu17)";
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
  TCanvas* cGblMuIdMC   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pt/fit_eff_plots/pt_PLOT"+index_mc);
  TCanvas* cGblMuIdDATA = (TCanvas*) tnpGblMuIdDATA->Get(EffType+"/pt/fit_eff_plots/pt_PLOT"+index_data);
  TCanvas* cGblMuIdMC_eta   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/eta/fit_eff_plots/abseta_PLOT"+index_mc);
  TCanvas* cGblMuIdDATA_eta = (TCanvas*) tnpGblMuIdDATA->Get(EffType+"/eta/fit_eff_plots/abseta_PLOT"+index_data);
  TCanvas* cGblMuIdMC_phi   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/phi/fit_eff_plots/phi_PLOT"+index_mc);
  TCanvas* cGblMuIdDATA_phi = (TCanvas*) tnpGblMuIdDATA->Get(EffType+"/phi/fit_eff_plots/phi_PLOT"+index_data);
  TCanvas* cGblMuIdMC_tag_nVertices   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/tag_nVertices/fit_eff_plots/tag_nVertices_PLOT"+index_mc);
  TCanvas* cGblMuIdDATA_tag_nVertices   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/tag_nVertices/fit_eff_plots/tag_nVertices_PLOT"+index_data);
  TCanvas* cGblMuIdMC_pair_deltaR   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pair_deltaR/fit_eff_plots/pair_deltaR_PLOT"+index_mc);
  TCanvas* cGblMuIdDATA_pair_deltaR   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/pair_deltaR/fit_eff_plots/pair_deltaR_PLOT"+index_data);
  // should be optimize later, not from the same selection category
  TCanvas* cGblMuIdMC_pair_deltaR_Tight   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pair_deltaR_Tight/fit_eff_plots/pair_deltaR_PLOT_isMuonTight_true_&_tag_isHLTCut_Mu17_true");
  TCanvas* cGblMuIdDATA_pair_deltaR_Tight   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/pair_deltaR_Tight/fit_eff_plots/pair_deltaR_PLOT_isMuonTight_true_&_tag_isHLTCut_Mu17_true");
  TCanvas* cGblMuIdMC_pair_deltaR_MuonIDisMedium   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pair_deltaR_MuonIDisMedium/fit_eff_plots/pair_deltaR_PLOT_tag_isHLTCut_Mu17_true");
  TCanvas* cGblMuIdDATA_pair_deltaR_MuonIDisMedium   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/pair_deltaR_MuonIDisMedium/fit_eff_plots/pair_deltaR_PLOT_tag_isHLTCut_Mu17_true");
  TCanvas* cGblMuIdMC_pair_deltaR_MuonIDisTight   = (TCanvas*) tnpGblMuIdMC  ->Get(EffType+"/pair_deltaR_MuonIDisTight/fit_eff_plots/pair_deltaR_PLOT_tag_isHLTCut_Mu17_true");
  TCanvas* cGblMuIdDATA_pair_deltaR_MuonIDisTight   = (TCanvas*) tnpGblMuIdDATA  ->Get(EffType+"/pair_deltaR_MuonIDisTight/fit_eff_plots/pair_deltaR_PLOT_tag_isHLTCut_Mu17_true");

  // and the graph afterwards

  TGraphAsymmErrors* gGblMuIdMC   = (TGraphAsymmErrors*) cGblMuIdMC   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA = (TGraphAsymmErrors*) cGblMuIdDATA -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdMC_eta   = (TGraphAsymmErrors*) cGblMuIdMC_eta   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA_eta = (TGraphAsymmErrors*) cGblMuIdDATA_eta -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdMC_phi   = (TGraphAsymmErrors*) cGblMuIdMC_phi   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA_phi = (TGraphAsymmErrors*) cGblMuIdDATA_phi -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdMC_tag_nVertices   = (TGraphAsymmErrors*) cGblMuIdMC_tag_nVertices   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA_tag_nVertices   = (TGraphAsymmErrors*) cGblMuIdDATA_tag_nVertices   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdMC_pair_deltaR   = (TGraphAsymmErrors*) cGblMuIdMC_pair_deltaR   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA_pair_deltaR   = (TGraphAsymmErrors*) cGblMuIdDATA_pair_deltaR   -> GetListOfPrimitives()->At(1);
  // should be optimize later, not from the same selection category
  TGraphAsymmErrors* gGblMuIdMC_pair_deltaR_Tight   = (TGraphAsymmErrors*) cGblMuIdMC_pair_deltaR_Tight   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA_pair_deltaR_Tight   = (TGraphAsymmErrors*) cGblMuIdDATA_pair_deltaR_Tight   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdMC_pair_deltaR_MuonIDisMedium   = (TGraphAsymmErrors*) cGblMuIdMC_pair_deltaR_MuonIDisMedium   -> GetListOfPrimitives()->At(1);
  std::cout<<" Test 0 "<<std::endl;
  TGraphAsymmErrors* gGblMuIdDATA_pair_deltaR_MuonIDisMedium   = (TGraphAsymmErrors*) cGblMuIdDATA_pair_deltaR_MuonIDisMedium   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdMC_pair_deltaR_MuonIDisTight   = (TGraphAsymmErrors*) cGblMuIdMC_pair_deltaR_MuonIDisTight   -> GetListOfPrimitives()->At(1);
  TGraphAsymmErrors* gGblMuIdDATA_pair_deltaR_MuonIDisTight   = (TGraphAsymmErrors*) cGblMuIdDATA_pair_deltaR_MuonIDisTight   -> GetListOfPrimitives()->At(1);
  std::cout<<" Test 1 "<<std::endl;
//  ErrorCheck(gGblMuIdMC);
//  ErrorCheck(gGblMuIdDATA);
//  ErrorCheck(gGblMuIdMC_eta);
//  ErrorCheck(gGblMuIdDATA_eta);
//  ErrorCheck(gGblMuIdMC_phi);
//  ErrorCheck(gGblMuIdDATA_phi);
//  ErrorCheck(gGblMuIdMC_pair_deltaR);
//  ErrorCheck(gGblMuIdDATA_pair_deltaR);
//  ErrorCheck(gGblMuIdMC_tag_nVertices);
//  ErrorCheck(gGblMuIdDATA_tag_nVertices);

  // ------------------------------------------------------------------------------

  TLegend* tl = SetLegend(0.32, 0.32, 0.59, 0.56);
  if( Comparison == 11 || Comparison == 12 || Comparison == 13 || Comparison == 14 || Comparison == 15){ 
     //tl->SetHeader("#epsilon_{MuTr8|Mu17}");
     tl->AddEntry(gGblMuIdMC, "MC W #rightarrow D_{s}J/#psi,"     ,"lp");
     tl->AddEntry(gGblMuIdMC, "is "+MCMuonType+", #sqrt{s} = 8 TeV"     ,"");
     tl->AddEntry(gGblMuIdDATA, "DATA 2012, is "+MuonType,"lp");
     tl->AddEntry(gGblMuIdDATA, "#int L~16 pb^{-1}, #sqrt{s} = 8 TeV on HLT_Mu17"     ,"");
  }
//////////////////////////////
//////////////////////////////

//////////////////////////////
  // GBL + Muon ID
  TCanvas* cGblMuIdvsPt = new TCanvas("cGblMuIdvsPt", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  //gGblMuIdMC -> SetTitle(Title+"|#eta| < 2.4");
  gGblMuIdMC -> SetMinimum(xmin);
  gGblMuIdMC -> SetMaximum(xmax);
  gGblMuIdMC -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvsPt->SetLeftMargin(0.15);
  //gGblMuIdMC ->GetXaxis() -> SetRangeUser(45., 300.);
     
  gGblMuIdMC -> SetFillColor(629);
  gGblMuIdMC -> SetLineColor(629);
     
  gGblMuIdMC -> GetXaxis()-> SetTitle("Probe P_{T} [GeV]");
  gGblMuIdMC -> GetYaxis()-> SetTitle(titleX);
   
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
  PrintIt(cGblMuIdvsPt, Title);
  //PrintIt(cGblMuIdvsPt, Title+"|#eta| < 2.4");
 
//////////////////////////////
 // eta pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_eta = new TCanvas("cGblMuIdvs_eta", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_eta -> SetTitle(Title);
  gGblMuIdMC_eta -> SetMinimum(xmin);
  gGblMuIdMC_eta -> SetMaximum(xmax);
  gGblMuIdMC_eta -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_eta->SetLeftMargin(0.15);
  gGblMuIdMC_eta ->GetXaxis() -> SetRangeUser(-2.4, 2.4);

  gGblMuIdMC_eta -> SetFillColor(629);
  gGblMuIdMC_eta -> SetLineColor(629);

  gGblMuIdMC_eta -> GetXaxis()-> SetTitle("Probe #eta");
  gGblMuIdMC_eta -> GetYaxis()-> SetTitle(titleX);

  gGblMuIdMC_eta -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_eta -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_eta->SetGridx();
  cGblMuIdvs_eta->SetGridy();

  gGblMuIdMC_eta   -> SetMarkerStyle(21);
  gGblMuIdMC_eta   -> SetMarkerColor(kRed);
  gGblMuIdMC_eta   -> Draw(MCPlot);
  gGblMuIdDATA_eta -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_eta, Title);
////////////////////////////
 // phi pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_phi = new TCanvas("cGblMuIdvs_phi", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_phi -> SetTitle(Title);
  gGblMuIdMC_phi -> SetMinimum(xmin);
  gGblMuIdMC_phi -> SetMaximum(xmax);
  gGblMuIdMC_phi -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_phi->SetLeftMargin(0.15);
  gGblMuIdMC_phi ->GetXaxis() -> SetRangeUser(-3.142, 3.142);

  gGblMuIdMC_phi -> SetFillColor(629);
  gGblMuIdMC_phi -> SetLineColor(629);

  gGblMuIdMC_phi -> GetXaxis()-> SetTitle("Probe #phi");
  gGblMuIdMC_phi -> GetYaxis()-> SetTitle(titleX);

  gGblMuIdMC_phi -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_phi -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_phi->SetGridx();
  cGblMuIdvs_phi->SetGridy();

  gGblMuIdMC_phi   -> SetMarkerStyle(21);
  gGblMuIdMC_phi   -> SetMarkerColor(kRed);
  gGblMuIdMC_phi   -> Draw(MCPlot);
  gGblMuIdDATA_phi -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_phi, Title);
//////////////////////////////

 // tag_nVertices pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_tag_nVertices = new TCanvas("cGblMuIdvs_tag_nVertices", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_tag_nVertices -> SetTitle(Title);
  gGblMuIdMC_tag_nVertices -> SetMinimum(xmin);
  gGblMuIdMC_tag_nVertices -> SetMaximum(xmax);
  gGblMuIdMC_tag_nVertices -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_tag_nVertices->SetLeftMargin(0.15);
  gGblMuIdMC_tag_nVertices ->GetXaxis() -> SetRangeUser(0.5, 25.5);

  gGblMuIdMC_tag_nVertices -> SetFillColor(629);
  gGblMuIdMC_tag_nVertices -> SetLineColor(629);

  gGblMuIdMC_tag_nVertices -> GetXaxis()-> SetTitle("# Vertices");
  gGblMuIdMC_tag_nVertices -> GetYaxis()-> SetTitle(titleX);

  gGblMuIdMC_tag_nVertices -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_tag_nVertices -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_tag_nVertices->SetGridx();
  cGblMuIdvs_tag_nVertices->SetGridy();

  gGblMuIdMC_tag_nVertices   -> SetMarkerStyle(21);
  gGblMuIdMC_tag_nVertices   -> SetMarkerColor(kRed);
  gGblMuIdMC_tag_nVertices   -> Draw(MCPlot);
  gGblMuIdDATA_tag_nVertices -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_tag_nVertices, Title);
//////////////////////////////
 // pair_deltaR pt45 GBL + Muon ID
  TCanvas* cGblMuIdvs_pair_deltaR = new TCanvas("cGblMuIdvs_pair_deltaR", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_pair_deltaR -> SetTitle(Title);
  gGblMuIdMC_pair_deltaR -> SetMinimum(xmin);
  gGblMuIdMC_pair_deltaR -> SetMaximum(xmax);
  gGblMuIdMC_pair_deltaR -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_pair_deltaR->SetLeftMargin(0.15);
  gGblMuIdMC_pair_deltaR ->GetXaxis() -> SetRangeUser(0.,3.);

  gGblMuIdMC_pair_deltaR -> SetFillColor(629);
  gGblMuIdMC_pair_deltaR -> SetLineColor(629);

  gGblMuIdMC_pair_deltaR -> GetXaxis()-> SetTitle("Pair #DeltaR");
  gGblMuIdMC_pair_deltaR -> GetYaxis()-> SetTitle(titleX);

  gGblMuIdMC_pair_deltaR -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_pair_deltaR -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_pair_deltaR->SetGridx();
  cGblMuIdvs_pair_deltaR->SetGridy();

  gGblMuIdMC_pair_deltaR   -> SetMarkerStyle(21);
  gGblMuIdMC_pair_deltaR   -> SetMarkerColor(kRed);
  gGblMuIdMC_pair_deltaR   -> Draw(MCPlot);
  gGblMuIdDATA_pair_deltaR -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_pair_deltaR, Title);
//////////////////////////////
 // pair_deltaR for tight MUon HLT
  TCanvas* cGblMuIdvs_pair_deltaR_Tight = new TCanvas("cGblMuIdvs_pair_deltaR_Tight", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_pair_deltaR_Tight -> SetTitle(Title);
  gGblMuIdMC_pair_deltaR_Tight -> SetMinimum(xmin);
  gGblMuIdMC_pair_deltaR_Tight -> SetMaximum(xmax);
  gGblMuIdMC_pair_deltaR_Tight -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_pair_deltaR_Tight->SetLeftMargin(0.15);
  gGblMuIdMC_pair_deltaR_Tight ->GetXaxis() -> SetRangeUser(0.,3.);

  gGblMuIdMC_pair_deltaR_Tight -> SetFillColor(629);
  gGblMuIdMC_pair_deltaR_Tight -> SetLineColor(629);

  gGblMuIdMC_pair_deltaR_Tight -> GetXaxis()-> SetTitle("Pair #DeltaR");
  gGblMuIdMC_pair_deltaR_Tight -> GetYaxis()-> SetTitle(titleX);

  gGblMuIdMC_pair_deltaR_Tight -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_pair_deltaR_Tight -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_pair_deltaR_Tight->SetGridx();
  cGblMuIdvs_pair_deltaR_Tight->SetGridy();

  gGblMuIdMC_pair_deltaR_Tight   -> SetMarkerStyle(21);
  gGblMuIdMC_pair_deltaR_Tight   -> SetMarkerColor(kRed);
  gGblMuIdMC_pair_deltaR_Tight   -> Draw(MCPlot);
  gGblMuIdDATA_pair_deltaR_Tight -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_pair_deltaR_Tight, "Tag #mu: is Tight & matched to HLT_Mu17, Probe #mu: is Tight");
//////////////////////////////
 // pair_deltaR for tight MUon HLT
  TCanvas* cGblMuIdvs_pair_deltaR_MuonIDisMedium = new TCanvas("cGblMuIdvs_pair_deltaR_MuonIDisMedium", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> SetTitle(Title);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> SetMinimum(xmin);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> SetMaximum(xmax);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_pair_deltaR_MuonIDisMedium->SetLeftMargin(0.15);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium ->GetXaxis() -> SetRangeUser(0.,3.);

  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> SetFillColor(629);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> SetLineColor(629);

  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> GetXaxis()-> SetTitle("Pair #DeltaR");
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> GetYaxis()-> SetTitle("MuonID(isMedium) #epsilon");

  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_pair_deltaR_MuonIDisMedium->SetGridx();
  cGblMuIdvs_pair_deltaR_MuonIDisMedium->SetGridy();

  gGblMuIdMC_pair_deltaR_MuonIDisMedium   -> SetMarkerStyle(21);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium   -> SetMarkerColor(kRed);
  gGblMuIdMC_pair_deltaR_MuonIDisMedium   -> Draw(MCPlot);
  gGblMuIdDATA_pair_deltaR_MuonIDisMedium -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_pair_deltaR_MuonIDisMedium, "Tag #mu: is Tight & matched to HLT_Mu17, Probe #mu: is Tracker");
//////////////////////////////
 // pair_deltaR for tight MUon HLT
  TCanvas* cGblMuIdvs_pair_deltaR_MuonIDisTight = new TCanvas("cGblMuIdvs_pair_deltaR_MuonIDisTight", "", 650, 0, 600, 600);
  //gPad -> SetLogx();
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> SetTitle(Title);
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> SetMinimum(xmin);
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> SetMaximum(xmax);
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> GetYaxis()-> SetTitleOffset(1.7);
  cGblMuIdvs_pair_deltaR_MuonIDisTight->SetLeftMargin(0.15);
  gGblMuIdMC_pair_deltaR_MuonIDisTight ->GetXaxis() -> SetRangeUser(0.,3.);

  gGblMuIdMC_pair_deltaR_MuonIDisTight -> SetFillColor(629);
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> SetLineColor(629);

  gGblMuIdMC_pair_deltaR_MuonIDisTight -> GetXaxis()-> SetTitle("Pair #DeltaR");
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> GetYaxis()-> SetTitle("MuonID(isTight) #epsilon");

  gGblMuIdMC_pair_deltaR_MuonIDisTight -> GetXaxis()-> SetNdivisions(509);
  gGblMuIdMC_pair_deltaR_MuonIDisTight -> GetYaxis()-> SetNdivisions(514);


  cGblMuIdvs_pair_deltaR_MuonIDisTight->SetGridx();
  cGblMuIdvs_pair_deltaR_MuonIDisTight->SetGridy();

  gGblMuIdMC_pair_deltaR_MuonIDisTight   -> SetMarkerStyle(21);
  gGblMuIdMC_pair_deltaR_MuonIDisTight   -> SetMarkerColor(kRed);
  gGblMuIdMC_pair_deltaR_MuonIDisTight   -> Draw(MCPlot);
  gGblMuIdDATA_pair_deltaR_MuonIDisTight -> Draw("P");

  tl->Draw("same");

  PrintIt(cGblMuIdvs_pair_deltaR_MuonIDisTight, "Tag #mu: is Tight & matched to HLT_Mu17, Probe #mu: is Tracker");
//////////////////////////////




  if (!isSave) return;

  //TString picName = png+sample_data+index_title+"_"+sample_mc+index_title; 
  TString picName = png+sample_data+index_title+"_"+sample_mc; 
  // print pictures
  cGblMuIdvsPt  -> SaveAs(picName+"_pt.png"); 
  cGblMuIdvs_eta  -> SaveAs(picName+"_eta.png"); 
  cGblMuIdvs_phi  -> SaveAs(picName+"_phi.png"); 
  cGblMuIdvs_tag_nVertices  -> SaveAs(picName+"_nVertices.png"); 
  cGblMuIdvs_pair_deltaR  -> SaveAs(picName+"_deltaR.png"); 
  cGblMuIdvs_pair_deltaR_Tight  -> SaveAs(picName+"_deltaR_Tight.png"); 
  cGblMuIdvs_pair_deltaR_MuonIDisMedium  -> SaveAs(picName+"_deltaR_MuonIDisMedium.png"); 
  cGblMuIdvs_pair_deltaR_MuonIDisTight  -> SaveAs(picName+"_deltaR_deltaR_MuonIDisTight.png"); 

  // print pdf files:
  cGblMuIdvsPt  -> SaveAs(picName+"_pt.pdf");
  cGblMuIdvs_eta  -> SaveAs(picName+"_eta.pdf");
  cGblMuIdvs_phi  -> SaveAs(picName+"_phi.pdf");
  cGblMuIdvs_tag_nVertices  -> SaveAs(picName+"_nVertices.pdf");
  cGblMuIdvs_pair_deltaR  -> SaveAs(picName+"_deltaR.pdf");
  cGblMuIdvs_pair_deltaR_Tight  -> SaveAs(picName+"_deltaR_Tight.pdf");
  cGblMuIdvs_pair_deltaR_MuonIDisMedium  -> SaveAs(picName+"_deltaR_MuonIDisMedium.pdf");
  cGblMuIdvs_pair_deltaR_MuonIDisTight  -> SaveAs(picName+"_deltaR_deltaR_MuonIDisTight.pdf"); 

  // print root files

  //cGblMuIdvsPt  -> SaveAs(picName+"_pt.root"); 
  //cGblMuIdvs_eta  -> SaveAs(picName+"_eta.root"); 
  //cGblMuIdvs_phi  -> SaveAs(picName+"_phi.root"); 
  //cGblMuIdvs_tag_nVertices  -> SaveAs(picName+"_nVertices.root"); 
  //cGblMuIdvs_pair_deltaR  -> SaveAs(picName+"_deltaR.root"); 
  //cGblMuIdvs_pair_deltaR_Tight  -> SaveAs(picName+"_deltaR_Tight.root"); 
  //cGblMuIdvs_pair_deltaR_MuonIDisMedium  -> SaveAs(picName+"_deltaR_MuonIDisMedium.root"); 
  //cGblMuIdvs_pair_deltaR_MuonIDisTight  -> SaveAs(picName+"_deltaR_deltaR_MuonIDisTight.root"); 
}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     // std::cout << "i = " << i << "ErrorYhigh = " << histo -> GetErrorYhigh(i) << std::endl;
     //if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
     if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(i));
  }

}
