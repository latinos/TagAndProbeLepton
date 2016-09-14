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

  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "Plots/";
  TString rootPlot = "Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="./";

  //change only name of file, check that you use correct pt and eta binning: 

  // for Run2016B:
  
  TString sample_data = "TnP_Medium_1Deff";

  TString DATA_String = pathAnna+sample_data+".root";
  TFile* DATA   = TFile::Open(DATA_String);

////////////////////////////////

////////////////////////////////

// open DATA:
  //std::cout << "TEST!!! " << std::endl;
     TCanvas* tDATA = (TCanvas*) DATA->Get("tpTree/tag_nVertices_Medium/fit_eff_plots/tag_nVertices_PLOT_tag_IsoMu20_pass");
     //TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d_&_Tight2012_pass%s",ipt,Tag_trig.Data() ));

     if(tDATA == 0)cout << "check code: ERROR Canvas = " << tDATA  << endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     if(grDATA == 0) cout << "check code: ERROR grDATA = " << grDATA  << endl;


         TCanvas* CanvPlot = new TCanvas("CanvPlot", "", 650, 0, 600, 600);
         grDATA -> SetMinimum(0.5);
         grDATA -> SetMaximum(1.0);
         grDATA -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot->SetLeftMargin(0.15);
         grDATA ->GetXaxis() -> SetRangeUser(0., 40.);

         grDATA -> SetFillColor(629);
         grDATA -> SetLineColor(629);

         grDATA -> GetXaxis()-> SetTitle("# Vertices");
         grDATA -> GetYaxis()-> SetTitle("Efficiency");

         grDATA -> GetXaxis()-> SetNdivisions(509);
         grDATA -> GetYaxis()-> SetNdivisions(514);


         CanvPlot->SetGridx();
         CanvPlot->SetGridy();

         grDATA   -> SetMarkerStyle(21);
         grDATA   -> SetMarkerColor(kRed);
         grDATA   -> Draw("AP");

         TString PicName = sample_data;
         TLegend* tl = SetLegend(0.15, 0.2, 0.7, 0.4);    
         tl->AddEntry(grDATA, "Data 2016, Medium ID eff."     ,"lp");
         PicName = sample_data;
      
         tl->Draw("same");

         CanvPlot -> SaveAs(Form("Plots/%s_nVer.png",PicName.Data()));

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
