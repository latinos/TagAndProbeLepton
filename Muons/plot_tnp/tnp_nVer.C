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
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/eff_tnp/";


  TString PU = "noPU";//for Data
  //TString PU = "withPU";//for Data

  //TString Bunch = "50ns";
  TString Bunch = "25ns";

  //TString Run = "Run2015B";
  //TString Run = "Run2015C";
  TString Run = "Run2015D";

  TString MC = "DY";

  TString MCPlot = "AP";//for Data
  //TString MCPlot = "A2";//for MC if you want <- not used now


  //TFile* tnpGblMuIdMC = TFile::Open(pathAnna+"tnp_"+Bunch+MC+"_v3_PUlike"+Run+"_"+Bunch+".root" );
  //TFile* tnpGblMuIdDATA = TFile::Open(pathAnna+"tnp_"+Run+"_PromptReco_"+Bunch+"_v3.root" );
  TFile* tnpGblMuIdMC = TFile::Open("/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_DYLL_M50_MadGraphMLM_LikeRun2015D.root");
  TFile* tnpGblMuIdDATA = TFile::Open("/afs/cern.ch/work/k/kropiv/MuonPOG/Samples/TnPTree_76X_RunD_part3.root" );

  TTree  &tMC =     * (TTree *) tnpGblMuIdMC    ->Get("tpTree/fitter_tree");
  TTree  &tData =   * (TTree *) tnpGblMuIdDATA  ->Get("tpTree/fitter_tree");


   TH1F *hMC_nVer = new TH1F("hMC_nVer","MC #Vertices",50,-0.5,49.5);
   hMC_nVer->Sumw2();
   TH1F *hData_nVer = new TH1F("hData_nVer","Data #Vertices",50,-0.5,49.5);
   hData_nVer->Sumw2();
   TH1F *hData_pt = new TH1F("hData_pt","Data probe pt",100,-0.5,199.5);
   hData_pt->Sumw2();
   TH1F *hData_dzPV = new TH1F("hData_dzPV","Data probe pt",100,-0.5,0.5);
   hData_pt->Sumw2();

   //TH1F *hData_IsoPF = new TH1F("hData_IsoPF","Data Iso PF Rel",100,0.,1.);
   //TH1F *hData_IsoPFandTrk = new TH1F("hData_IsoPFandTrk","Data Iso PF + Trk Rel",100,0.,1.);
   TH1F *hData_IsoPF = new TH1F("hData_IsoPF","Data Iso PF Rel",50,0.,0.15);
   TH1F *hData_IsoPFandTrk = new TH1F("hData_IsoPFandTrk","Data Iso PF + Trk Rel",50,0.,0.15);
   TH1F *hData_IsoPF_Loose = new TH1F("hData_IsoPF_Loose","Data Iso PF Rel",50,0.15,0.4);
   TH1F *hData_IsoPFandTrk_Loose = new TH1F("hData_IsoPFandTrk_Loose","Data Iso PF + Trk Rel",50,0.15,0.4);
   hData_IsoPF->Sumw2();
   hData_IsoPFandTrk->Sumw2();
   hData_IsoPF_Loose->Sumw2();
   hData_IsoPFandTrk_Loose->Sumw2();

   //TH2F *hData_IsoPFvsIsoTrk = new TH2F("hData_IsoPFvsIsoTrk","Data Iso PF vs. Iso TrkRel",50,0.,0.5, 50, 0., 0.5);
   TH2F *hData_IsoPFvsIsoTrk = new TH2F("hData_IsoPFvsIsoTrk","Data Iso PF vs. Iso TrkRel",50, 0.15 ,0.5, 50, 0., 0.5);

   //if(PU == "noPU")tMC.Draw("tag_nVertices>>hMC_nVer");
   //if(PU== "withPU")tMC.Draw("tag_nVertices>>hMC_nVer","weight*(tag_nVertices>0)");
   //tData.Draw("tag_nVertices>>hData_nVer");

   if(PU == "noPU")tMC.Draw("tag_nVertices>>hMC_nVer","tag_IsoMu20>0 && pt>10");
   if(PU== "withPU")tMC.Draw("tag_nVertices>>hMC_nVer","weight*(tag_IsoMu20>0 && pt>10)");
   tData.Draw("tag_nVertices>>hData_nVer","tag_IsoMu20>0 && pt>10");

   tData.Draw("pt>>hData_pt","tag_IsoMu20>0 && tag_pt>22 && Medium");
   tData.Draw("dzPV>>hData_dzPV","tag_IsoMu20>0 && tag_pt>22 && Medium");


   hMC_nVer->Scale(1.0/hMC_nVer->Integral());
   hData_nVer->Scale(1.0/hData_nVer->Integral());


    tData.Draw("combRelIsoPF04dBeta>>hData_IsoPF",       "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && combRelIsoPF04dBeta>=0 && combRelIsoPF04dBeta<0.15");
    tData.Draw("combRelIsoPF04dBeta>>hData_IsoPFandTrk", "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && combRelIsoPF04dBeta>=0 && combRelIsoPF04dBeta<0.15 && tkIso/pt<0.4");
    tData.Draw("combRelIsoPF04dBeta>>hData_IsoPF_Loose",       "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && combRelIsoPF04dBeta>=0.15 && combRelIsoPF04dBeta<0.4");
    tData.Draw("combRelIsoPF04dBeta>>hData_IsoPFandTrk_Loose", "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && combRelIsoPF04dBeta>=0.15 && combRelIsoPF04dBeta<0.4 && tkIso/pt<0.4");
    tData.Draw("combRelIsoPF04dBeta:tkIso/pt>>hData_IsoPFvsIsoTrk", "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && combRelIsoPF04dBeta>=0 && combRelIsoPF04dBeta<0.5");
    //tData.Draw("combRelIsoPF04dBeta>>hData_IsoPF",       "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && pt<15 && combRelIsoPF04dBeta>=0 && combRelIsoPF04dBeta<0.15");
    //tData.Draw("combRelIsoPF04dBeta>>hData_IsoPFandTrk", "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && pt<15 && combRelIsoPF04dBeta>=0 && combRelIsoPF04dBeta<0.15 && tkIso/pt<0.4");
    //tData.Draw("combRelIsoPF04dBeta>>hData_IsoPF_Loose",       "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && pt<15 && combRelIsoPF04dBeta>=0.15 && combRelIsoPF04dBeta<0.4");
    //tData.Draw("combRelIsoPF04dBeta>>hData_IsoPFandTrk_Loose", "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && pt<15 && combRelIsoPF04dBeta>=0.15 && combRelIsoPF04dBeta<0.4 && tkIso/pt<0.4");
    //tData.Draw("combRelIsoPF04dBeta:tkIso/pt>>hData_IsoPFvsIsoTrk", "tag_IsoMu20>0 && tag_pt>22 && Medium && pt>10 && pt<15 && combRelIsoPF04dBeta>=0 && combRelIsoPF04dBeta<0.5");

  // ------------------------------------------------------------------------------

  //TLegend* tl = SetLegend(0.27, 0.12, 0.54, 0.36);
  TLegend* tl = SetLegend(0.45, 0.65, 0.75, 0.85);
     if(PU == "noPU")tl->AddEntry(hMC_nVer, "no PU weight"     ,"");
     if(PU == "withPU")tl->AddEntry(hMC_nVer, "with PU weight"     ,"");
     tl->AddEntry(hMC_nVer, "#sqrt{s} = 13 TeV"     ,"");
     tl->AddEntry(hMC_nVer, "Drell-Yan Spring15, "+Bunch  ,"lp");
     if(Run == "Run2015B")tl->AddEntry(hData_nVer, "DATA 2015B, "+Bunch     ,"lp");
     if(Run == "Run2015C")tl->AddEntry(hData_nVer, "DATA 2015C, "+Bunch     ,"lp");
     if(Run == "Run2015D")tl->AddEntry(hData_nVer, "DATA 2015D, "+Bunch     ,"lp");
//////////////////////////////
  //std::cout <<"test2"<< std::endl;

//////////////////////////////

 // tag_nVertices pt45 GBL + Muon ID
  TCanvas* cPlot_tag_nVertices = new TCanvas("cPlot_tag_nVertices", "", 650, 0, 600, 600);
  //cPlot_tag_nVertices->Divide(1,1,0.05,0.05);
  cPlot_tag_nVertices->Divide(1,1);
  cPlot_tag_nVertices->cd(1);
  //cPlot_tag_nVertices->SetLeftMargin(0.25);
  TPad* pad = (TPad*)cPlot_tag_nVertices->GetPad(1);
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


  //cPlot_tag_nVertices->SetGridx();
  //cPlot_tag_nVertices->SetGridy();

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

  //PrintIt(cPlot_tag_nVertices, +"|#eta| < 2.4 && p_T > 20 GeV");
////////////////////////////////

  TCanvas* cPlot_Iso = new TCanvas("cPlot_Iso", "", 650, 0, 600, 600);
  cPlot_Iso->Divide(1,1);
  cPlot_Iso->cd(1);
  TPad* pad_Iso = (TPad*)cPlot_Iso->GetPad(1);
  pad_Iso->SetLeftMargin(0.15);
  hData_IsoPF -> SetTitle("Isolation");
  hData_IsoPF -> GetYaxis()-> SetTitleOffset(1.5);
  hData_IsoPF -> GetXaxis()-> SetTitleOffset(1.2);
  hData_IsoPF -> GetYaxis()->SetTitleSize(0.04);
  hData_IsoPF -> GetXaxis()->SetTitleSize(0.04);


  hData_IsoPF -> GetXaxis()-> SetTitle("Rel. PF ISO");
  hData_IsoPF -> GetYaxis()-> SetTitle("Entries");

  hData_IsoPF -> GetXaxis()-> SetNdivisions(509);
  hData_IsoPF -> GetYaxis()-> SetNdivisions(514);

  hData_IsoPF   -> SetMarkerStyle(21);
  hData_IsoPF   -> SetMarkerColor(kBlue);
  hData_IsoPF   -> Draw("e");

  hData_IsoPFandTrk -> SetFillColor(629);
  hData_IsoPFandTrk -> SetLineColor(629);
  hData_IsoPFandTrk   -> SetMarkerStyle(22);
  hData_IsoPFandTrk   -> SetMarkerColor(kRed);
  hData_IsoPFandTrk -> Draw("esame");

  TLegend* tl_Iso = SetLegend(0.2, 0.65, 0.75, 0.85);
     tl_Iso->AddEntry(hData_IsoPF, "Run2015D, HWW ID"     ,"lp");
     tl_Iso->AddEntry(hData_IsoPF, Form("Entries = %6.0f", hData_IsoPF->Integral())     ,"");
     tl_Iso->AddEntry(hData_IsoPFandTrk, "Run2015D, HWW ID && Rel. Trk. ISO < 0.4"     ,"lp");
     tl_Iso->AddEntry(hData_IsoPFandTrk, Form("Entries = %6.0f", hData_IsoPFandTrk->Integral())     ,"");
     tl_Iso->AddEntry(hData_IsoPFandTrk, Form("Eff. of Rel. Trk. ISO < 0.4 = %6.2f%%", hData_IsoPFandTrk->Integral()/hData_IsoPF->Integral()*100.)     ,"");

 tl_Iso->Draw("same");
////////////////////////////////

  TCanvas* cPlot_Iso_Loose = new TCanvas("cPlot_Iso_Loose", "", 650, 0, 600, 600);
  cPlot_Iso_Loose->Divide(1,1);
  cPlot_Iso_Loose->cd(1);
  TPad* pad_Iso_Loose = (TPad*)cPlot_Iso_Loose->GetPad(1);
  pad_Iso_Loose->SetLeftMargin(0.15);
  hData_IsoPF_Loose -> SetTitle("Isolation");
  hData_IsoPF_Loose -> GetYaxis()-> SetTitleOffset(1.5);
  hData_IsoPF_Loose -> GetXaxis()-> SetTitleOffset(1.2);
  hData_IsoPF_Loose -> GetYaxis()->SetTitleSize(0.04);
  hData_IsoPF_Loose -> GetXaxis()->SetTitleSize(0.04);


  hData_IsoPF_Loose -> GetXaxis()-> SetTitle("Rel. PF ISO");
  hData_IsoPF_Loose -> GetYaxis()-> SetTitle("Entries");

  hData_IsoPF_Loose -> GetXaxis()-> SetNdivisions(509);
  hData_IsoPF_Loose -> GetYaxis()-> SetNdivisions(514);

  hData_IsoPF_Loose   -> SetMarkerStyle(21);
  hData_IsoPF_Loose   -> SetMarkerColor(kBlue);
  hData_IsoPF_Loose   -> Draw("e");

  hData_IsoPFandTrk_Loose -> SetFillColor(629);
  hData_IsoPFandTrk_Loose -> SetLineColor(629);
  hData_IsoPFandTrk_Loose   -> SetMarkerStyle(22);
  hData_IsoPFandTrk_Loose   -> SetMarkerColor(kRed);
  hData_IsoPFandTrk_Loose -> Draw("esame");

  TLegend* tl_Iso_Loose = SetLegend(0.2, 0.65, 0.75, 0.85);
     tl_Iso_Loose->AddEntry(hData_IsoPF_Loose, "Run2015D, HWW ID"     ,"lp");
     tl_Iso_Loose->AddEntry(hData_IsoPF_Loose, Form("Entries = %6.0f", hData_IsoPF_Loose->Integral())     ,"");
     tl_Iso_Loose->AddEntry(hData_IsoPFandTrk_Loose, "Run2015D, HWW ID && Rel. Trk. ISO < 0.4"     ,"lp");
     tl_Iso_Loose->AddEntry(hData_IsoPFandTrk_Loose, Form("Entries = %6.0f", hData_IsoPFandTrk_Loose->Integral())     ,"");
     tl_Iso_Loose->AddEntry(hData_IsoPFandTrk_Loose, Form("Eff. of Rel. Trk. ISO < 0.4 = %6.2f%%", hData_IsoPFandTrk_Loose->Integral()/hData_IsoPF_Loose->Integral()*100.)     ,"");

 tl_Iso_Loose->Draw("same");
////////////////////////////////

  TCanvas* cPlot_Iso_2D = new TCanvas("cPlot_Iso_2D", "", 650, 0, 600, 600);
  cPlot_Iso_2D->Divide(1,1);
  cPlot_Iso_2D->cd(1);
  TPad* pad_Iso_2D = (TPad*)cPlot_Iso_2D->GetPad(1);
  pad_Iso_2D->SetLeftMargin(0.15);
  hData_IsoPFvsIsoTrk -> SetTitle("Isolation");
  hData_IsoPFvsIsoTrk -> GetYaxis()-> SetTitleOffset(1.5);
  hData_IsoPFvsIsoTrk -> GetXaxis()-> SetTitleOffset(1.2);
  hData_IsoPFvsIsoTrk -> GetYaxis()->SetTitleSize(0.04);
  hData_IsoPFvsIsoTrk -> GetXaxis()->SetTitleSize(0.04);


  hData_IsoPFvsIsoTrk -> GetXaxis()-> SetTitle("Rel. PF ISO");
  hData_IsoPFvsIsoTrk -> GetYaxis()-> SetTitle("Rel. Trk. ISO");

  hData_IsoPFvsIsoTrk -> GetXaxis()-> SetNdivisions(509);
  hData_IsoPFvsIsoTrk -> GetYaxis()-> SetNdivisions(514);

  //hData_IsoPFvsIsoTrk   -> SetMarkerStyle(21);
  hData_IsoPFvsIsoTrk   -> SetMarkerColor(kBlue);
  hData_IsoPFvsIsoTrk   -> Draw("HCOL");


  TLegend* tl_Iso_2D = SetLegend(0.2, 0.65, 0.75, 0.85);
     tl_Iso_2D->AddEntry(hData_IsoPFvsIsoTrk, "Run2015D, HWW ID"     ,"lp");

 tl_Iso_2D->Draw("same");



  if (!isSave) return;

  // print pictures
  cPlot_tag_nVertices  -> SaveAs(png+"nVertices_"+Run+"_"+Bunch+"_"+MC+"_"+PU+".png"); 
  cPlot_Iso  -> SaveAs(png+"ISO_Run2015D.png"); 
  cPlot_Iso_Loose  -> SaveAs(png+"ISO_Loose_Run2015D.png"); 
  cPlot_Iso_2D  -> SaveAs(png+"ISO_2D_Run2015D.png"); 
}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
  }

}
