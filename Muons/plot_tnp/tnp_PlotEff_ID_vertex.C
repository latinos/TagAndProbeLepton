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


void tnp_PlotEff_ID_vertex( bool isSave = true ) {
  
  gROOT->Clear();
  gStyle->SetOptStat(0);  
  //gStyle->SetTitleSize(0.5);
  //gStyle->SetTitleFont(60);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetCanvasColor(kWhite); 
  //gStyle->SetFillColor(0);
  gStyle->SetOptTitle(kFALSE);

  double nVer[] = {0., 5., 10., 15., 20., 25., 30., 35., 40., 50.};


  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_7_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_7_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_8_0_7_patch2/src/TagAndProbeLepton/Muons/eff_tnp/";

  //change only name of file, check that you use correct pt and eta binning: 

  // for Run2016B:
  TString sample_data = "TnP_Medium_Run2016B_1Deff"; 


  TString Tag_trig = "_tag_IsoMu20_pass";

  TFile* DATA   = TFile::Open(pathAnna+sample_data+".root" );

////////////////////////////////


     TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/tag_nVertices_Medium/fit_eff_plots/tag_nVertices_PLOT%s",Tag_trig.Data() ));
     if(tDATA == 0)cout << "check code: ERROR Canvas tDATA = " << tDATA <<  endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     if(grDATA == 0) cout << "check code: ERROR grDATA = " << grDATA << endl;


     TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/tag_nVertices_Medium_ptGt20/fit_eff_plots/tag_nVertices_PLOT%s",Tag_trig.Data() ));
     if(tDATA_ptGt20 == 0)cout << "check code: ERROR Canvas tDATA_ptGt20 = " << tDATA_ptGt20 <<  endl;
     TGraphAsymmErrors* grDATA_ptGt20 = (TGraphAsymmErrors*) tDATA_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptGt20);
     if(grDATA_ptGt20 == 0) cout << "check code: ERROR grDATA_ptGt20 = " << grDATA_ptGt20 << endl;

     TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/tag_nVertices_Medium_ptLt20/fit_eff_plots/tag_nVertices_PLOT%s",Tag_trig.Data() ));
     if(tDATA_ptLt20 == 0)cout << "check code: ERROR Canvas tDATA_ptLt20 = " << tDATA_ptLt20 <<  endl;
     TGraphAsymmErrors* grDATA_ptLt20 = (TGraphAsymmErrors*) tDATA_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptLt20);
     if(grDATA_ptLt20 == 0) cout << "check code: ERROR grDATA_ptLt20 = " << grDATA_ptLt20 << endl;


     TCanvas* tDATA_tight = (TCanvas*) DATA->Get(Form("tpTree/tag_nVertices_Tight/fit_eff_plots/tag_nVertices_PLOT%s",Tag_trig.Data() ));
     if(tDATA_tight == 0)cout << "check code: ERROR Canvas tDATA_tight = " << tDATA_tight <<  endl;
     TGraphAsymmErrors* grDATA_tight = (TGraphAsymmErrors*) tDATA_tight -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_tight);
     if(grDATA_tight == 0) cout << "check code: ERROR grDATA_tight = " << grDATA_tight << endl;


     TCanvas* tDATA_tight_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/tag_nVertices_Tight_ptGt20/fit_eff_plots/tag_nVertices_PLOT%s",Tag_trig.Data() ));
     if(tDATA_tight_ptGt20 == 0)cout << "check code: ERROR Canvas tDATA_tight_ptGt20 = " << tDATA_tight_ptGt20 <<  endl;
     TGraphAsymmErrors* grDATA_tight_ptGt20 = (TGraphAsymmErrors*) tDATA_tight_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_tight_ptGt20);
     if(grDATA_tight_ptGt20 == 0) cout << "check code: ERROR grDATA_tight_ptGt20 = " << grDATA_tight_ptGt20 << endl;

     TCanvas* tDATA_tight_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/tag_nVertices_Tight_ptLt20/fit_eff_plots/tag_nVertices_PLOT%s",Tag_trig.Data() ));
     if(tDATA_tight_ptLt20 == 0)cout << "check code: ERROR Canvas tDATA_tight_ptLt20 = " << tDATA_tight_ptLt20 <<  endl;
     TGraphAsymmErrors* grDATA_tight_ptLt20 = (TGraphAsymmErrors*) tDATA_tight_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_tight_ptLt20);
     if(grDATA_tight_ptLt20 == 0) cout << "check code: ERROR grDATA_tight_ptLt20 = " << grDATA_tight_ptLt20 << endl;


////////////////////////////////
         TCanvas* CanvPlot = new TCanvas("CanvPlot", "", 650, 0, 600, 600);
         grDATA -> SetMinimum(0.9);
         grDATA -> SetMaximum(0.99);
         grDATA -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot->SetLeftMargin(0.15);
         grDATA ->GetXaxis() -> SetRangeUser(0., 35.);

         grDATA -> SetFillColor(629);
         grDATA -> SetLineColor(629);

         grDATA -> GetXaxis()-> SetTitle("#vertices");
         grDATA -> GetYaxis()-> SetTitle("Efficiency");

         grDATA -> GetXaxis()-> SetNdivisions(509);
         grDATA -> GetYaxis()-> SetNdivisions(514);


         CanvPlot->SetGridx();
         CanvPlot->SetGridy();

         grDATA   -> SetMarkerStyle(21);
         grDATA   -> SetMarkerColor(kRed);
         grDATA   -> Draw("AP");

         grDATA_tight   -> SetMarkerStyle(20);
         grDATA_tight   -> SetMarkerColor(kBlue);
         grDATA_tight   -> SetLineColor(kBlue);
         grDATA_tight   -> Draw("P");

         TString PicName = sample_data;
         TLegend* tl = SetLegend(0.15, 0.15, 0.7, 0.30);    
         if (sample_data == "TnP_Medium_Run2016B_1Deff") {
             PicName = "muonID_nver";
             tl->AddEntry(grDATA, "Run2016 #leq 274421, p_{T} > 20 GeV, |#eta| < 2.4"           ,"");
             tl->AddEntry(grDATA, "Medium muon ID "     ,"lp");
             tl->AddEntry(grDATA_tight, "Tight muon ID "     ,"lp");
         }

      
         tl->Draw("same");

         CanvPlot -> SaveAs(Form("Plots/%s.png",PicName.Data()));
////////////////////////////////
         TCanvas* CanvPlot_ptGt20 = new TCanvas("CanvPlot_ptGt20", "", 650, 0, 600, 600);
         grDATA_ptGt20 -> SetMinimum(0.9);
         grDATA_ptGt20 -> SetMaximum(0.99);
         grDATA_ptGt20 -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot_ptGt20->SetLeftMargin(0.15);
         grDATA_ptGt20 ->GetXaxis() -> SetRangeUser(0., 35.);

         grDATA_ptGt20 -> SetFillColor(629);
         grDATA_ptGt20 -> SetLineColor(629);

         grDATA_ptGt20 -> GetXaxis()-> SetTitle("#vertices");
         grDATA_ptGt20 -> GetYaxis()-> SetTitle("Efficiency");

         grDATA_ptGt20 -> GetXaxis()-> SetNdivisions(509);
         grDATA_ptGt20 -> GetYaxis()-> SetNdivisions(514);


         CanvPlot_ptGt20->SetGridx();
         CanvPlot_ptGt20->SetGridy();

         grDATA_ptGt20   -> SetMarkerStyle(21);
         grDATA_ptGt20   -> SetMarkerColor(kRed);
         grDATA_ptGt20   -> Draw("AP");

         grDATA_tight_ptGt20   -> SetMarkerStyle(20);
         grDATA_tight_ptGt20   -> SetMarkerColor(kBlue);
         grDATA_tight_ptGt20   -> SetLineColor(kBlue);
         grDATA_tight_ptGt20   -> Draw("P");

         PicName = sample_data;
         TLegend* tl_ptGt20 = SetLegend(0.15, 0.15, 0.7, 0.30);    
         if (sample_data == "TnP_Medium_Run2016B_1Deff") {
             PicName = "muonID_HWW_ptGt20_nver";
             tl_ptGt20->AddEntry(grDATA_ptGt20, "Run2016 #leq 274421, p_{T} > 20 GeV, |#eta| < 2.4"           ,"");
             tl_ptGt20->AddEntry(grDATA_ptGt20, "HWW Medium muon ID "     ,"lp");
             tl_ptGt20->AddEntry(grDATA_tight_ptGt20, "HWW Tight muon ID "     ,"lp");
         }

      
         tl_ptGt20->Draw("same");

         CanvPlot_ptGt20 -> SaveAs(Form("Plots/%s.png",PicName.Data()));
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
