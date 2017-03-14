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
void tnp_SFtrial( bool isSave = true ) {
  
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
  TString pathAnna="";

  //change only name of file, check that you use correct pt and eta binning: 

  // for Run2016B:
  
  TString sample_data = "TnP_realData_Tight";
  TString sample_data_2 = "TnP_newData_Tight";


  TString DATA_String = pathAnna+sample_data+".root";
  TFile* DATA   = TFile::Open(DATA_String);
  TString DATA_2_String = pathAnna+sample_data_2+".root";
  TFile* DATA_2   = TFile::Open(DATA_2_String);

////////////////////////////////

////////////////////////////////

// open DATA:
  //std::cout << "TEST!!! " << std::endl;
     TCanvas* tDATA1 = (TCanvas*) DATA->Get("tpTree/tag_nVertices_Tight/fit_eff_plots/tag_nVertices_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAETA1 = (TCanvas*) DATA->Get("tpTree/Tag_Eta_Tight/fit_eff_plots/eta_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAPT1 = (TCanvas*) DATA->Get("tpTree/Tag_Pt_Tight/fit_eff_plots/pt_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAPHI1 = (TCanvas*) DATA->Get("tpTree/Tag_Phi_Tight/fit_eff_plots/phi_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAETA_M = (TCanvas*) DATA_2->Get("tpTree/Tag_Eta_Tight/fit_eff_plots/eta_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAPT_M = (TCanvas*) DATA_2->Get("tpTree/Tag_Pt_Tight/fit_eff_plots/pt_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAPHI_M = (TCanvas*) DATA_2->Get("tpTree/Tag_Phi_Tight/fit_eff_plots/phi_PLOT_tag_IsoMu20_pass");
     TCanvas* tDATAVER_M = (TCanvas*) DATA_2->Get("tpTree/tag_nVertices_Tight/fit_eff_plots/tag_nVertices_PLOT_tag_IsoMu20_pass");
 //TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d_&_Tight2012_pass%s",ipt,Tag_trig.Data() ));


     if(tDATA1 == 0)cout << "check code: ERROR Canvas = " << tDATA1  << endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA1 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     if(grDATA == 0) cout << "check code: ERROR grDATA = " << tDATA1 << endl;

     if(tDATAVER_M ==0)cout << "check code: ERROR ver2Canvas = " << tDATAVER_M << endl;
     TGraphAsymmErrors* grDataVer_M = (TGraphAsymmErrors*) tDATAVER_M -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataVer_M);
     if(grDataVer_M == 0) cout << "check code ERROR grDataVer_M = " << tDATAVER_M << endl;

     if(tDATAETA1 == 0)cout << "check code: ERROR ETACANVAS = " << tDATAETA1 << endl;
     TGraphAsymmErrors* grDataEta = (TGraphAsymmErrors*) tDATAETA1 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataEta);
     if(grDataEta == 0) cout <<"check code:Error grDataEta = " << grDataEta << endl;

     if(tDATAPT1 == 0)cout << "check code: ERROR PT CANVAS = " << tDATAPT1 << endl;
     TGraphAsymmErrors* grDataPt = (TGraphAsymmErrors*) tDATAPT1 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataPt);
     if(grDataPt == 0) cout <<"check code:Error grDataPt = " << grDataPt << endl;

     if (tDATAPHI1 == 0)cout << "check code: ERROR PHI CANVAS = " << tDATAPHI1 << endl;
     TGraphAsymmErrors* grDataPhi = (TGraphAsymmErrors*) tDATAPHI1 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataPhi);
     if(grDataPhi == 0) cout <<"check code:Error grDataPhi = " << grDataPhi << endl;


     if(tDATAETA_M == 0)cout << "check code: ERROR ETACANVAS = " << tDATAETA_M << endl;
     TGraphAsymmErrors* grDataEta_M = (TGraphAsymmErrors*) tDATAETA_M -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataEta_M);
     if(grDataEta_M == 0) cout <<"check code:Error grDataEta = " << grDataEta_M << endl;

     if(tDATAPT_M == 0)cout << "check code: ERROR PT CANVAS = " << tDATAPT_M << endl;
     TGraphAsymmErrors* grDataPt_M = (TGraphAsymmErrors*) tDATAPT_M -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataPt_M);
     if(grDataPt_M == 0) cout <<"check code:Error grDataPt = " << grDataPt_M << endl;

     if (tDATAPHI_M == 0)cout << "check code: ERROR PHI CANVAS = " << tDATAPHI_M << endl;
     TGraphAsymmErrors* grDataPhi_M = (TGraphAsymmErrors*) tDATAPHI_M -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDataPhi_M);
     if(grDataPhi_M == 0) cout <<"check code:Error grDataPhi = " << grDataPhi_M << endl;


         TCanvas* CanvPlot1 = new TCanvas("CanvPlot1", "", 650, 0, 600, 600);
         grDATA -> SetMinimum(0.95);
         grDATA -> SetMaximum(1.02);
         grDATA -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot1->SetLeftMargin(0.15);
         grDATA ->GetXaxis() -> SetRangeUser(0., 40.);

         grDATA -> SetFillColor(629);
         grDATA -> SetLineColor(629);

         grDATA -> GetXaxis()-> SetTitle("# Vertices");
         grDATA -> GetYaxis()-> SetTitle("Efficiency");

         grDATA -> GetXaxis()-> SetNdivisions(509);
         grDATA -> GetYaxis()-> SetNdivisions(514);


         CanvPlot1->SetGridx();
         CanvPlot1->SetGridy();

         grDATA   -> SetMarkerStyle(21);
         grDATA   -> SetMarkerColor(kRed);
         grDATA   -> Draw("AP");
	
	 TString PicName = sample_data;
         TLegend* tl = SetLegend(0.15, 0.2, 0.7, 0.4);
         tl->AddEntry(grDATA, "Data 2016, Tight ID eff."     ,"lp");
         PicName = sample_data;

         tl->Draw("same");

	 CanvPlot1 -> SaveAs(Form("Plots/%s_nVer_TIGHT.png",PicName.Data()));	 

	 TCanvas* CanvEta1 = new TCanvas("CanvEta1", "Eta Distribution, Tight Muon ID", 650, 0, 600, 600);
         grDataEta -> SetMinimum(0.95);
         grDataEta -> SetMaximum(1.02);
         grDataEta -> GetYaxis()-> SetTitleOffset(1.7);
         CanvEta1->SetLeftMargin(0.15);
         grDataEta->GetXaxis() -> SetRangeUser(-2.5, 2.5);

         grDataEta -> SetFillColor(629);
         grDataEta -> SetLineColor(629);

         grDataEta -> GetXaxis() -> SetTitle("Eta");
         grDataEta -> GetYaxis() -> SetTitle("Efficiency");

         grDataEta -> GetXaxis()-> SetNdivisions(509);
         grDataEta -> GetYaxis()-> SetNdivisions(514);
	 CanvEta1 -> SetTitle("Eta Distribution, Tight Muon ID");

         CanvEta1->SetGridx();
         CanvEta1->SetGridy();

         grDataEta   -> SetMarkerStyle(21);
         grDataEta   -> SetMarkerColor(kRed);
         grDataEta   -> Draw("AP");
         

	 TString EtaEff = sample_data;
         TLegend* t2 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t2->AddEntry(grDataEta, "Data 2016, Tight ID eff."     ,"lp");
	 EtaEff = sample_data;

         t2->Draw("same");

	 CanvEta1 -> SaveAs(Form("Plots/%seff_eta_TIGHT.png",EtaEff.Data()));	 

	 TCanvas* CanvPt1 = new TCanvas("CanvPt1", "", 650, 0,600, 600);
	 grDataPt -> SetMinimum(0.95);
         grDataPt -> SetMaximum(1.02);
         grDataPt -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvPt1->SetLeftMargin(0.15);
	 grDataPt -> GetXaxis() -> SetRangeUser(0., 200.);

	 grDataPt -> SetFillColor(629);
         grDataPt -> SetLineColor(629);

	 grDataPt -> GetXaxis() -> SetTitle("Pt");
         grDataPt -> GetYaxis() -> SetTitle("Efficiency");

	 grDataPt -> GetXaxis()-> SetNdivisions(509);
         grDataPt -> GetYaxis()-> SetNdivisions(514);
         
         CanvPt1->SetGridx();
	 CanvPt1->SetGridy();

	 grDataPt   -> SetMarkerStyle(21);
         grDataPt   -> SetMarkerColor(kRed);
         grDataPt   -> Draw("AP");

	 TString PtEff = sample_data;
         TLegend* t3 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t3->AddEntry(grDataPt, "Data 2016, Tight ID eff.", "lp");
         PtEff = sample_data;
         t3->Draw("same");

	 CanvPt1 -> SaveAs(Form("Plots/%seff_pt_TIGHT.png",PtEff.Data()));	 

	 TCanvas* CanvPhi1 = new TCanvas("CanvPhi1", "Phi Distribution, Tight Muon ID", 650, 0, 600, 600);
	 grDataPhi -> SetMinimum(0.95);
         grDataPhi -> SetMaximum(1.02);
         grDataPhi -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvPhi1->SetLeftMargin(0.15);
 	 grDataPhi->GetXaxis() -> SetRangeUser(-3.15,3.15);

	 grDataPhi -> SetFillColor(629);
         grDataPhi -> SetLineColor(629);

	 grDataPhi -> GetXaxis() -> SetTitle("Phi");
         grDataPhi -> GetYaxis() -> SetTitle("Efficiency");

	 grDataPhi -> GetXaxis()-> SetNdivisions(509);
         grDataPhi -> GetYaxis()-> SetNdivisions(514);
	 CanvPhi1 -> SetTitle("Phi Distribution, Tight Muon ID");

	 CanvPhi1->SetGridx();
         CanvPhi1->SetGridy();

	 grDataPhi   -> SetMarkerStyle(21);
         grDataPhi   -> SetMarkerColor(kRed);
         grDataPhi   -> Draw("AP");


	cout << "test" << endl;
        	
	 TString PhiEff = sample_data;
	 TLegend* t4 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t4->AddEntry(grDataPhi, "Data 2016, Tight ID eff."     ,"lp");
         PhiEff = sample_data;
	 t4->Draw("same");	

	 CanvPhi1 -> SaveAs(Form("Plots/%seff_phi_TIGHT.png",PhiEff.Data()));	 


         TCanvas* CanvPlot2 = new TCanvas("CanvPlot2", "", 650, 0, 600, 600);
         grDataVer_M -> SetMinimum(0.95);
         grDataVer_M -> SetMaximum(1.02);
         grDataVer_M -> GetYaxis()-> SetTitleOffset(1.7);
         //cout << "Test1" << endl;
         CanvPlot1->SetLeftMargin(0.15);
         grDATA ->GetXaxis() -> SetRangeUser(0., 40.);

         grDataVer_M -> SetFillColor(629);
         grDataVer_M -> SetLineColor(629);

         grDataVer_M -> GetXaxis()-> SetTitle("# Vertices");
         grDataVer_M -> GetYaxis()-> SetTitle("Efficiency");

         grDataVer_M -> GetXaxis()-> SetNdivisions(509);
         grDataVer_M -> GetYaxis()-> SetNdivisions(514);


         CanvPlot2->SetGridx();
         CanvPlot2->SetGridy();

         grDataVer_M   -> SetMarkerStyle(21);
         grDataVer_M   -> SetMarkerColor(kRed);
         grDataVer_M   -> Draw("AP");
	
	 TString PicName2 = sample_data;
         TLegend* t5 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t5->AddEntry(grDataVer_M, "MC 2016, Tight ID eff."     ,"lp");
         PicName2 = sample_data;

         t5->Draw("same");

	 CanvPlot2 -> SaveAs(Form("Plots/%s_nVer_TIGHT.png",PicName2.Data()));	 

	 TCanvas* CanvEta2 = new TCanvas("CanvEta2", "Eta Distribution, Tight Muon ID", 650, 0, 600, 600);
         grDataEta_M -> SetMinimum(0.95);
         grDataEta_M -> SetMaximum(1.02);
         grDataEta_M -> GetYaxis()-> SetTitleOffset(1.7);
         CanvEta2->SetLeftMargin(0.15);
         grDataEta_M->GetXaxis() -> SetRangeUser(-2.5, 2.5);

         grDataEta_M -> SetFillColor(629);
         grDataEta_M -> SetLineColor(629);

         grDataEta_M -> GetXaxis() -> SetTitle("Eta");
         grDataEta_M -> GetYaxis() -> SetTitle("Efficiency");

         grDataEta_M -> GetXaxis()-> SetNdivisions(509);
         grDataEta_M -> GetYaxis()-> SetNdivisions(514);
	 CanvEta2 -> SetTitle("Eta Distribution, Tight Muon ID");

         CanvEta2->SetGridx();
         CanvEta2->SetGridy();

         grDataEta_M   -> SetMarkerStyle(21);
         grDataEta_M   -> SetMarkerColor(kRed);
         grDataEta_M   -> Draw("AP");
         

	 TString EtaEff1 = sample_data;
         TLegend* t6 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t6->AddEntry(grDataEta_M, "MC 2016, Tight ID eff."     ,"lp");
	 EtaEff1 = sample_data;

         t2->Draw("same");

	 CanvEta2 -> SaveAs(Form("Plots/%seff_eta_TIGHT.png",EtaEff1.Data()));	 

	 TCanvas* CanvPt2 = new TCanvas("CanvPt2", "", 650, 0,600, 600);
	 grDataPt_M -> SetMinimum(0.95);
         grDataPt_M -> SetMaximum(1.02);
         grDataPt_M -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvPt2->SetLeftMargin(0.15);
	 grDataPt_M -> GetXaxis() -> SetRangeUser(0., 200.);

	 grDataPt_M -> SetFillColor(629);
         grDataPt_M -> SetLineColor(629);

	 grDataPt_M -> GetXaxis() -> SetTitle("Pt");
         grDataPt_M -> GetYaxis() -> SetTitle("Efficiency");

	 grDataPt_M -> GetXaxis()-> SetNdivisions(509);
         grDataPt_M -> GetYaxis()-> SetNdivisions(514);
         
         CanvPt2->SetGridx();
	 CanvPt2->SetGridy();

	 grDataPt_M   -> SetMarkerStyle(21);
         grDataPt_M   -> SetMarkerColor(kRed);
         grDataPt_M   -> Draw("AP");

	 TString PtEff1 = sample_data;
         TLegend* t7 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t7->AddEntry(grDataPt_M, "MC 2016, Tight ID eff.", "lp");
         PtEff1 = sample_data;
         t7->Draw("same");

	 CanvPt2 -> SaveAs(Form("Plots/%seff_pt_TIGHT.png",PtEff1.Data()));	 

	 TCanvas* CanvPhi2 = new TCanvas("CanvPhi2", "Phi Distribution, Tight Muon ID", 650, 0, 600, 600);
	 grDataPhi_M -> SetMinimum(0.95);
         grDataPhi_M -> SetMaximum(1.02);
         grDataPhi_M -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvPhi2->SetLeftMargin(0.15);
	 grDataPhi_M->GetXaxis() -> SetRangeUser(-3.15,3.15);

	 grDataPhi_M -> SetFillColor(629);
         grDataPhi_M -> SetLineColor(629);

	 grDataPhi_M -> GetXaxis() -> SetTitle("Phi");
         grDataPhi_M -> GetYaxis() -> SetTitle("Efficiency");

	 grDataPhi_M -> GetXaxis()-> SetNdivisions(509);
         grDataPhi_M -> GetYaxis()-> SetNdivisions(514);
	 CanvPhi2 -> SetTitle("Phi Distribution, Tight Muon ID");

	 CanvPhi2->SetGridx();
         CanvPhi2->SetGridy();

	 grDataPhi_M   -> SetMarkerStyle(21);
         grDataPhi_M   -> SetMarkerColor(kRed);
         grDataPhi_M   -> Draw("AP");


	cout << "test" << endl;
        	
	 TString PhiEff2 = sample_data;
	 TLegend* t8 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t8->AddEntry(grDataPhi_M, "MC 2016, Tight ID eff."     ,"lp");
         PhiEff2 = sample_data;
	 t8->Draw("same");	

	 CanvPhi2 -> SaveAs(Form("Plots/%seff_phi_TIGHT.png",PhiEff2.Data()));	 

	 //SCALE FACTOR STUF
	 //cout << "number of bins" << endl;
	 int nbinv = grDATA -> GetN();
//	 cout << nbinv << endl;
	 int nbine = grDataEta -> GetN();
//	 cout << nbine << endl;
	 int nbinpt = grDataPt -> GetN();
//	 cout << nbinpt << endl;
	 int nbinph = grDataPhi -> GetN();
//	 cout << nbinph << endl;
	 int nbinv1 = grDataVer_M -> GetN();
//	 cout << nbinv1 << endl;
         int nbine1 = grDataEta_M -> GetN();
//	 cout << nbine1 << endl;
	 int nbinpt1 = grDataPt_M -> GetN();
//	 cout << nbinpt1 << endl;
	 int nbinph1 = grDataPhi_M -> GetN();
//	 cout << nbinph1 << endl;
//getting error values for x:


double_t dat_nv_xh[nbinv];
double_t dat_nv_xl[nbinv];
for(int i = 1; i < nbinv; i++){
 if( (grDATA -> GetErrorXhigh(i)) > 2.*(grDATA -> GetErrorYlow(i)) )
 grDATA -> SetPointEXhigh(i,grDATA -> GetErrorXlow(i));
cout << "nv: " << i << endl;
cout << "errorxh: " << grDATA->GetErrorX(i)<< endl;
cout << "errorxl: " << grDATA->GetErrorX(i) << endl; 
 dat_nv_xh[i] = grDATA->GetErrorXhigh(i);
 dat_nv_xl[i] = grDATA->GetErrorXlow(i);
}
double_t dat_eta_xh[nbine];
double_t dat_eta_xl[nbine];
for(int i = 0; i < nbine; i++){
 if( (grDataEta -> GetErrorXhigh(i)) > 2.*(grDataEta -> GetErrorXlow(i)) )
 grDataEta -> SetPointEXhigh(i,grDataEta -> GetErrorXlow(i));
cout << "eta: " << i << endl;
cout << "errorxh: " << grDataEta->GetErrorXhigh(i)<< endl;
cout << "errorxl: " << grDataEta->GetErrorXlow(i) << endl;
 dat_eta_xh[i] = grDataEta->GetErrorXhigh(i);
 dat_eta_xl[i] = grDataEta->GetErrorXlow(i); 
 }
double_t dat_pt_xh[nbinpt];
double_t dat_pt_xl[nbinpt];
for(int i = 0; i < nbinpt; i++){
if( (grDataPt -> GetErrorXhigh(i)) > 2.*(grDataPt -> GetErrorXlow(i)) )
 grDataPt -> SetPointEXhigh(i,grDataPt -> GetErrorXlow(i));
cout << "pt: " << i << endl;
cout << "errorxh: " << grDataPt->GetErrorXhigh(i)<< endl;
cout << "errorxl: " << grDataPt->GetErrorXlow(i) << endl;
 dat_pt_xh[i] = grDataPt->GetErrorXhigh(i);
 dat_pt_xl[i] = grDataPt->GetErrorXlow(i);
 }
double_t dat_phi_xh[nbinph];
double_t dat_phi_xl[nbinph];
for(int i = 0; i < nbinph; i++){
// if( (grDataPhi -> GetErrorYhigh(i)) > 2.*(grDataPhi -> GetErrorYlow(i)) )
// grDataPhi -> SetPointEXhigh(i,grDataPhi -> GetErrorXlow(i));
cout << "phi: " << i << endl;
cout << "errorxh: " << grDataPhi->GetErrorXhigh(i)<< endl;
cout << "errorxl: " << grDataPhi->GetErrorXlow(i) << endl;
 dat_phi_xh[i] = grDataPhi->GetErrorXhigh(i);
 dat_phi_xl[i] = grDataPhi->GetErrorXlow(i);  
}
double_t mc_nv_xh[nbinv1];
double_t mc_nv_xl[nbinv1];
for(int i = 1; i < nbinv1; i++){
 if( (grDataVer_M -> GetErrorXhigh(i)) > 2.*(grDataVer_M -> GetErrorXlow(i)) )
 grDataVer_M -> SetPointEXhigh(i,grDataVer_M -> GetErrorXlow(i));
cout << "Nv(x): " << endl;
cout << "errorxh: " << grDataVer_M->GetErrorXhigh(i)<< endl;
cout << "errorxl: "<< grDataVer_M->GetErrorXlow(i) << endl;
 mc_nv_xh[i] = grDataVer_M->GetErrorXhigh(i);
 mc_nv_xl[i] = grDataVer_M->GetErrorXlow(i); 
 }
double_t mc_eta_xh[nbine1];
double_t mc_eta_xl[nbine1];
for(int i = 0; i < nbine1; i++){
 if( (grDataEta_M -> GetErrorXhigh(i)) > 2.*(grDataEta_M -> GetErrorXlow(i)) )
 grDataEta_M -> SetPointEXhigh(i,grDataEta_M -> GetErrorXlow(i));
 cout << "eta(x): " << endl;
cout << "errorxh: " << grDataEta_M->GetErrorXhigh(i)<< endl;
cout << "errorxl: "<< grDataEta_M->GetErrorXlow(i) << endl;
 mc_eta_xh[i] = grDataEta_M->GetErrorXhigh(i);
 mc_eta_xl[i] = grDataEta_M->GetErrorXlow(i);
 }
double_t mc_pt_xh[nbinpt1];
double_t mc_pt_xl[nbinpt1];
for(int i = 0; i < nbinpt1; i++){
if( (grDataPt_M -> GetErrorXhigh(i)) > 2.*(grDataPt_M -> GetErrorXlow(i)) )
 grDataPt_M -> SetPointEXhigh(i,grDataPt_M -> GetErrorXlow(i));
  cout << "Pt(x): " << endl;
cout << "errorxh: " << grDataPt_M->GetErrorXhigh(i)<< endl;
cout << "errorxl: "<< grDataPt_M->GetErrorXlow(i) << endl;
 mc_pt_xh[i] = grDataPt_M->GetErrorXhigh(i);
 mc_pt_xl[i] = grDataPt_M->GetErrorXlow(i); 
}
double_t mc_phi_xh[nbinph1];
double_t mc_phi_xl[nbinph1];
for(int i = 0; i < nbinph1; i++){
 if( (grDataPhi_M -> GetErrorXhigh(i)) > 2.*(grDataPhi_M -> GetErrorXlow(i)) )
grDataPhi_M -> SetPointEXhigh(i,grDataPhi_M -> GetErrorXlow(i));
  cout << "Phi(x): " << endl;
cout << "errorxh: " << grDataPhi_M->GetErrorXhigh(i)<< endl;
cout << "errorxl: "<< grDataPhi_M->GetErrorXlow(i) << endl;
 mc_phi_xh[i] = grDataPhi_M->GetErrorXhigh(i);
 mc_phi_xl[i] = grDataPhi_M->GetErrorXlow(i);
 }
//getting error values for y:
double_t dat_nv_yh[nbinv];
double_t dat_nv_yl[nbinv];
for(int i = 0; i < nbinv; i++){
 if( (grDATA -> GetErrorYhigh(i)) > 2.*(grDATA -> GetErrorYlow(i)) )
 grDATA -> SetPointEYhigh(i,grDATA -> GetErrorYlow(i));
cout << "nv(y): " << endl;
cout << "erroryh: " << grDATA->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDATA->GetErrorYlow(i) << endl; 
 dat_nv_yh[i] = grDATA->GetErrorYhigh(i);
 dat_nv_yl[i] = grDATA->GetErrorYlow(i);
}
double_t dat_eta_yh[nbine];
double_t dat_eta_yl[nbine];
for(int i = 0; i < nbine; i++){
 if( (grDataEta -> GetErrorYhigh(i)) > 2.*(grDataEta -> GetErrorYlow(i)) )
 grDataEta -> SetPointEYhigh(i,grDataEta -> GetErrorYlow(i));
cout << "eta(y): " << endl;
cout << "erroryh: " << grDataEta->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataEta->GetErrorYlow(i) << endl;
 dat_eta_yh[i] = grDataEta->GetErrorYhigh(i);
 dat_eta_yl[i] = grDataEta->GetErrorYlow(i);
  }
double_t dat_pt_yh[nbinpt];
double_t dat_pt_yl[nbinpt];
for(int i = 0; i < nbinpt; i++){
if( (grDataPt -> GetErrorYhigh(i)) > 2.*(grDataPt -> GetErrorYlow(i)) )
 grDataPt -> SetPointEYhigh(i,grDataPt -> GetErrorYlow(i));
cout << "Pt(y): " << endl;
cout << "erroryh: " << grDataPt->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataPt->GetErrorYlow(i) << endl;
 dat_pt_yh[i] = grDataPt->GetErrorYhigh(i);
 dat_pt_yl[i] = grDataPt->GetErrorYlow(i); 
 }
double_t dat_phi_yh[nbinph];
double_t dat_phi_yl[nbinph];
for(int i = 0; i < nbinph; i++){
 if( (grDataPhi -> GetErrorYhigh(i)) > 2.*(grDataPhi -> GetErrorYlow(i)) )
 grDataPhi -> SetPointEYhigh(i,grDataPhi -> GetErrorYlow(i));
  cout << "Phi(y): " << endl;
cout << "erroryh: " << grDataPhi->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataPhi->GetErrorYlow(i) << endl;
 dat_phi_yh[i] = grDataPhi->GetErrorYhigh(i);
 dat_phi_yl[i] = grDataPhi->GetErrorYlow(i);
}
double_t mc_nv_yh[nbinv1];
double_t mc_nv_yl[nbinv1];
for(int i = 0; i < nbinv1; i++){
 if( (grDataVer_M -> GetErrorYhigh(i)) > 2.*(grDataVer_M -> GetErrorYlow(i)) )
 grDataVer_M -> SetPointEYhigh(i,grDataVer_M -> GetErrorYlow(i));
  cout << "Nv(y): " << endl;
cout << "erroryh: " << grDataVer_M->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataVer_M->GetErrorYlow(i) << endl;
 mc_nv_yh[i] = grDataVer_M->GetErrorYhigh(i);
 mc_nv_yl[i] = grDataVer_M->GetErrorYlow(i);
}
double_t mc_eta_yh[nbine1];
double_t mc_eta_yl[nbine1];
for(int i = 0; i < nbine1; i++){
 if( (grDataEta_M -> GetErrorYhigh(i)) > 2.*(grDataEta_M -> GetErrorYlow(i)) )
 grDataEta_M -> SetPointEYhigh(i,grDataEta_M -> GetErrorYlow(i));
  cout << "Eta(y): " << endl;
cout << "erroryh: " << grDataEta_M->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataEta_M->GetErrorYlow(i) << endl;
 mc_eta_yh[i] = grDataEta_M->GetErrorYhigh(i);
 mc_eta_yl[i] = grDataEta_M->GetErrorYlow(i);
 }
double_t mc_pt_yh[nbinpt1];
double_t mc_pt_yl[nbinpt1];
for(int i = 0; i < nbinpt1; i++){
if( (grDataPt_M -> GetErrorYhigh(i)) > 2.*(grDataPt_M -> GetErrorYlow(i)) )
 grDataPt_M -> SetPointEYhigh(i,grDataPt_M -> GetErrorYlow(i));
   cout << "Pt(y): " << endl;
cout << "erroryh: " << grDataPt_M->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataPt_M->GetErrorYlow(i) << endl;
 mc_pt_yh[i] = grDataPt_M->GetErrorYhigh(i);
 mc_pt_yl[i] = grDataPt_M->GetErrorYlow(i);
}
double_t mc_phi_yh[nbinph1];
double_t mc_phi_yl[nbinph1];
for(int i = 0; i < nbinph1; i++){
 if( (grDataPhi_M -> GetErrorYhigh(i)) > 2.*(grDataPhi_M -> GetErrorYlow(i)) ) 
grDataPhi_M -> SetPointEYhigh(i,grDataPhi_M -> GetErrorYlow(i));
  cout << "Phi(y): " << endl;
cout << "erroryh: " << grDataPhi_M->GetErrorYhigh(i)<< endl;
cout << "erroryl: "<< grDataPhi_M->GetErrorYlow(i) << endl;
 mc_phi_yh[i] = grDataPhi_M->GetErrorYhigh(i);
 mc_phi_yl[i] = grDataPhi_M->GetErrorYlow(i);
 }

///cout << "X Vector (data) :" << endl;

double_t *X_VECNV= grDATA->GetX();
for(int i = 0; i < nbinv; i++){
//	 cout<<"i= "<< i <<" NV " << X_VECNV[i] << endl;
 }
double_t *X_VECE= grDataEta->GetX();
for(int i = 0; i < nbine; i++){
  //       cout <<"Eta "<< X_VECE[i] << endl;
 }
double_t *X_VECPT= grDataPt->GetX();
for(int i = 0; i < nbinpt; i++){
  //       cout <<"PT " << X_VECPT[i] << endl;
 }
double_t *X_VECPH= grDataPhi->GetX();
for(int i = 0; i < nbinph; i++){
  //       cout <<"Phi " << X_VECPH[i] << endl;
 }
//cout <<"X Vector (MC) :" << endl;
//cout << "Data bin " << nbinv <<endl;
//cout << "MC bin " << nbinv1 << endl;
double_t *X_VECNV1= grDataVer_M->GetX();
for(int i = 0; i < nbinv1; i++){
//	 cout <<"NV "<< X_VECNV1[i] << endl;
 }
double_t *X_VECE1= grDataEta_M->GetX();
for(int i = 0; i < nbine1; i++){
  //       cout <<"Eta "<< X_VECE1[i] << endl;
 }
double_t *X_VECPT1= grDataPt_M->GetX();
for(int i = 0; i < nbinpt1; i++){
  //       cout << "PT "<< X_VECPT1[i] << endl;
 }
double_t *X_VECPH1= grDataPhi_M->GetX();
for(int i = 0; i < nbinph1; i++){
  //       cout << "Phi "<< X_VECPH1[i] << endl;
 }


cout << "YVEC DATA" << endl;


double_t *Y_VECNV= grDATA->GetY();
for(int i = 0; i < nbinv; i++){
  //       cout<<"i= "<< i <<" NV " << Y_VECNV[i] << endl;
 }
double_t *Y_VECE= grDataEta->GetY();
for(int i = 0; i < nbine; i++){
  //       cout <<"Eta "<< Y_VECE[i] << endl;
 }
double_t *Y_VECPT= grDataPt->GetY();
for(int i = 0; i < nbinpt; i++){
  //       cout <<"PT " << Y_VECPT[i] << endl;
 }
double_t *Y_VECPH= grDataPhi->GetY();
for(int i = 0; i < nbinph; i++){
//         cout <<"Phi " << Y_VECPH[i] << endl;
 }
//cout <<"Y Vector (MC) :" << endl;
//cout << "Data bin " << nbinv <<endl;
//cout << "MC bin " << nbinv1 << endl;
double_t *Y_VECNV1= grDataVer_M->GetY();
for(int i = 0; i < nbinv1; i++){
//         cout <<"NV "<< Y_VECNV1[i] << endl;
 }
double_t *Y_VECE1= grDataEta_M->GetY();
for(int i = 0; i < nbine1; i++){
  ///       cout <<"Eta "<< Y_VECE1[i] << endl;
 }
double_t *Y_VECPT1= grDataPt_M->GetY();
for(int i = 0; i < nbinpt1; i++){
  //       cout << "PT "<< Y_VECPT1[i] << endl;
 }
double_t *Y_VECPH1= grDataPhi_M->GetY();
for(int i = 0; i < nbinph1; i++){
 //        cout << "Phi "<< Y_VECPH1[i] << endl;
}
//cout << " Scale Factors:" << endl;
cout << "NV"<<endl;
double_t Y_VECNV_SF[nbinv];
for(int i = 0; i < nbinv; i++){
	 Y_VECNV_SF[i] = Y_VECNV[i]/Y_VECNV1[i];
	cout<< Y_VECNV_SF[i]<<endl;
}
cout <<"Eta"<<endl;
double_t Y_VECE_SF[nbine];
for(int i = 0; i < nbine; i++){
	 Y_VECE_SF[i] = Y_VECE[i]/Y_VECE1[i];
	cout<< Y_VECE_SF[i]<<endl;
}
cout << "PT"<<endl;
double_t Y_VECPT_SF[nbinpt];
for(int i = 0; i < nbinpt; i++){
	 Y_VECPT_SF[i] = Y_VECPT[i]/Y_VECPT1[i];
	cout<< Y_VECPT_SF[i]<<endl;
}
cout <<"Phi "<<endl;
double_t Y_VECPH_SF[nbinph];
for(int i = 0; i < nbinph; i++){
	 Y_VECPH_SF[i] = Y_VECPH[i]/Y_VECPH1[i];
	cout<< Y_VECPH_SF[i]<<endl;
}
//creating total error bars x
double_t sf_nv_xh[nbinv];
double_t sf_nv_xl[nbinv];
double_t sf_nv_yh[nbinv];
double_t sf_nv_yl[nbinv];
for(int i = 0; i < nbinv; i++){
sf_nv_xh[i]= (dat_nv_xh[i]);
sf_nv_xl[i]= (dat_nv_xl[i]);
sf_nv_yh[i]= sqrt((dat_nv_yh[i] * dat_nv_yh[i]) + (mc_nv_yh[i] * mc_nv_yh[i]));
sf_nv_yl[i]= sqrt((dat_nv_yl[i] * dat_nv_yl[i]) + (mc_nv_yl[i] * mc_nv_yl[i]));
}

double_t sf_eta_xh[nbine];
double_t sf_eta_xl[nbine];
double_t sf_eta_yh[nbine];
double_t sf_eta_yl[nbine];
for(int i = 0; i < nbine; i++){
sf_eta_xh[i]= (dat_eta_xl[i]);
sf_eta_xl[i]= (dat_eta_xh[i]);
sf_eta_yh[i]= sqrt((dat_eta_yh[i] * dat_eta_yh[i]) + (mc_eta_yh[i] * mc_eta_yh[i]));
sf_eta_yl[i]= sqrt((dat_eta_yl[i] * dat_eta_yl[i]) + (mc_eta_yl[i] * mc_eta_yl[i]));
}
double_t sf_pt_xh[nbinpt];
double_t sf_pt_xl[nbinpt];
double_t sf_pt_yh[nbinpt];
double_t sf_pt_yl[nbinpt];
for(int i = 0; i < nbinpt; i++){
sf_pt_xh[i]= (dat_pt_xh[i]);
sf_pt_xl[i]= (dat_pt_xl[i]);
sf_pt_yh[i]= sqrt((dat_pt_yh[i] * dat_pt_yh[i]) + (mc_pt_yh[i] * mc_pt_yh[i]));
sf_pt_yl[i]= sqrt((dat_pt_yl[i] * dat_pt_yl[i]) + (mc_pt_yl[i] * mc_pt_yl[i]));
}
double_t sf_phi_xh[nbinph];
double_t sf_phi_xl[nbinph];
double_t sf_phi_yh[nbinph];
double_t sf_phi_yl[nbinph];
for(int i = 0; i < nbinph; i++){
sf_phi_xh[i]= (dat_phi_xh[i]);
sf_phi_xl[i]= (dat_phi_xl[i]);
sf_phi_yh[i]= sqrt((dat_phi_yh[i] * dat_phi_yh[i]) + (mc_phi_yh[i] * mc_phi_yh[i]));
sf_phi_yl[i]= sqrt((dat_phi_yl[i] * dat_phi_yl[i]) + (mc_phi_yl[i] * mc_phi_yl[i]));
}

//cout << "TGraph Numbers:" << endl;
//cout << "NV " << endl;
Double_t x[nbinv], y[nbinv],exl[nbinv],exh[nbinv],eyl[nbinv],eyh[nbinv];
   for (Int_t i=0; i<nbinv; i++) {
      x[i] = X_VECNV[i];
      y[i] = Y_VECNV_SF[i];
      exl[i] = sf_nv_xl[i];
      exh[i] = sf_nv_xh[i];
      eyl[i] = sf_nv_yl[i];
      eyh[i] = sf_nv_yl[i];
//cout << "NV " << endl;
//cout << "x: "<< x[i] << endl;
//cout << "y: "<< y[i] << endl;
   }
   TGraphAsymmErrors *gr1 = new TGraphAsymmErrors (nbinv, x, y,exl,exh,eyl,eyh);
   gr1->Draw();
//cout << "Eta " << endl;
Double_t x1[nbine], y1[nbine],exl1[nbine],exh1[nbine],eyl1[nbine],eyh1[nbine];
   for (Int_t i=0; i<nbine; i++) {
      x1[i] = X_VECE[i];
      y1[i] = Y_VECE_SF[i];
      exl1[i] = sf_eta_xl[i];
      exh1[i] = sf_eta_xh[i];
      eyl1[i] = sf_eta_yl[i];
      eyh1[i] = sf_eta_yh[i];
//cout << "x: "<< x1[i] << endl;
//cout << "y: "<< y1[i] << endl;
   }
   TGraphAsymmErrors *gr2 = new TGraphAsymmErrors (nbine, x1, y1,exl1,exh1,eyl1,eyh1);
   gr2->Draw();

//cout << "PT "<< endl;
Double_t x2[nbinpt], y2[nbinpt],exl2[nbinpt],exh2[nbinpt],eyl2[nbinpt],eyh2[nbinpt];
   for (Int_t i=0; i<nbinpt; i++) {
      x2[i] = X_VECPT[i];
      y2[i] = Y_VECPT_SF[i];
      exl2[i] = sf_pt_xl[i];
      exh2[i] = sf_pt_xh[i];
      eyl2[i] = sf_pt_yl[i];
      eyh2[i] = sf_pt_yh[i];
//cout << "x: "<< x2[i] << endl;
//cout << "y: "<< y2[i] << endl;
   }
   TGraphAsymmErrors *gr3 = new TGraphAsymmErrors (nbinpt, x2, y2,exl2,exh2,eyl2,eyh2);
   gr3->Draw();

//cout << "Phi " << endl;
Double_t x3[nbinph], y3[nbinph],exl3[nbinpt],exh3[nbinpt],eyl3[nbinpt],eyh3[nbinpt];
   for (Int_t i=0; i<nbinph; i++) {
      x3[i] = X_VECPH[i];
      y3[i] = Y_VECPH_SF[i];
      exl3[i] = sf_phi_xl[i];
      exh3[i] = sf_phi_xh[i];
      eyl3[i] = sf_phi_yl[i];
      eyh3[i] = sf_phi_yh[i];

cout << "exh3: "<< exh3[i] << endl;
cout << "exl3: "<< exl3[i]<<  "  i = " << i << endl;
cout << "x3: "<<x3[i]<<endl;
cout << "y3: "<<y3[i]<<endl;
cout << "eyh3: "<< eyh3[i] << endl;
cout << "eyl3: "<< eyl3[i]<<  "  i = " << i << endl; 
 }
   //TGraphAsymmErrors *gr4 = new TGraphAsymmErrors (nbinph, x3, y3,exl3,exh3,eyl3,eyh3);
   TGraphAsymmErrors *gr4 = new TGraphAsymmErrors (nbinph, x3, y3);
   gr4->Draw();
Double_t *xcheck=gr4->GetX();
Double_t *ycheck=gr4->GetY();
for (Int_t i=0; i<nbinph; i++) {
//xcheck[i] =grDataPhi->GetX();
cout<< "xcheck " << xcheck[i] << " i= "<< i << endl;
//ycheck[i] =grDataPhi->GetY();
cout<< "ycheck " <<ycheck[i] << " i= " << i << endl;
} 

	 TCanvas* CanvSFNV = new TCanvas("CanvSFNV", "nVertices Distribution, Tight Muon ID", 650, 0, 600, 600);
	 gr1 -> SetMinimum(0.90);
         gr1 -> SetMaximum(1.10);
         gr1 -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvSFNV->SetLeftMargin(0.15);
 	 gr1->GetXaxis() -> SetRangeUser(0.,40.);

	 gr1 -> SetFillColor(629);
         gr1 -> SetLineColor(629);

	 gr1 -> GetXaxis() -> SetTitle("nVertices");
         gr1 -> GetYaxis() -> SetTitle("SCALE FACTOR");

	 gr1 -> GetXaxis()-> SetNdivisions(509);
         gr1 -> GetYaxis()-> SetNdivisions(514);
	 CanvSFNV -> SetTitle("nVertices Distribution, Tight Muon ID");

	 CanvSFNV->SetGridx();
         CanvSFNV->SetGridy();

	 gr1   -> SetMarkerStyle(21);
         gr1   -> SetMarkerColor(kRed);
         gr1   -> Draw("AP");


	cout << "test" << endl;
        	
	 TString SFNV = sample_data;
	 TLegend* t9 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t9->AddEntry(gr1, "SF 2016, Tight ID eff."     ,"lp");
         SFNV = sample_data;
	 t9->Draw("same");

	CanvSFNV -> SaveAs(Form("NewPlots/%ssf_nv_TIGHT.png",SFNV.Data()));

	
	 TCanvas* CanvSFE = new TCanvas("CanvSFE", "ETA Distribution, Tight Muon ID", 650, 0, 600, 600);
	 gr2 -> SetMinimum(0.90);
         gr2 -> SetMaximum(1.00);
         gr2 -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvSFE->SetLeftMargin(0.15);
 	 gr2->GetXaxis() -> SetRangeUser(-2.5,2.5);

	 gr2 -> SetFillColor(629);
         gr2 -> SetLineColor(629);

	 gr2 -> GetXaxis() -> SetTitle("ETA");
         gr2 -> GetYaxis() -> SetTitle("SCALE FACTOR");

	 gr2 -> GetXaxis()-> SetNdivisions(509);
         gr2 -> GetYaxis()-> SetNdivisions(514);
	 CanvSFE -> SetTitle("ETA Distribution, Tight Muon ID");

	 CanvSFE->SetGridx();
         CanvSFE->SetGridy();

	 gr2   -> SetMarkerStyle(21);
         gr2   -> SetMarkerColor(kRed);
         gr2   -> Draw("AP");


	//cout << "test" << endl;
        	
	 TString SFE = sample_data;
	 TLegend* t10 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t10->AddEntry(gr2, "SF 2016, Tight ID eff."     ,"lp");
         SFE = sample_data;
	 t10->Draw("same");

	CanvSFE -> SaveAs(Form("NewPlots/%ssf_eta_TIGHT.png",SFE.Data()));

	
	 TCanvas* CanvSFPT = new TCanvas("CanvSFPT", "PT Distribution, Tight Muon ID", 650, 0, 600, 600);
	 gr3 -> SetMinimum(0.90);
         gr3 -> SetMaximum(1.00);
         gr3 -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvSFPT->SetLeftMargin(0.15);
 	 gr3->GetXaxis() -> SetRangeUser(0.,200.);

	 gr3 -> SetFillColor(629);
         gr3 -> SetLineColor(629);

	 gr3 -> GetXaxis() -> SetTitle("PT");
         gr3 -> GetYaxis() -> SetTitle("SCALE FACTOR");

	 gr3 -> GetXaxis()-> SetNdivisions(509);
         gr3 -> GetYaxis()-> SetNdivisions(514);
	 CanvSFPT -> SetTitle("PT Distribution, Tight Muon ID");

	 CanvSFPT->SetGridx();
         CanvSFPT->SetGridy();

	 gr3   -> SetMarkerStyle(21);
         gr3   -> SetMarkerColor(kRed);
         gr3   -> Draw("AP");


	//cout << "test" << endl;
        	
	 TString SFPT = sample_data;
	 TLegend* t11 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t11->AddEntry(gr3, "SF 2016, Tight ID eff."     ,"lp");
         SFPT = sample_data;
	 t11->Draw("same");

	CanvSFPT -> SaveAs(Form("NewPlots/%ssf_pt_TIGHT.png",SFPT.Data()));

	
	 TCanvas* CanvSFPH = new TCanvas("CanvSFPH", "PHI Distribution, Tight Muon ID", 650, 0, 600, 600);
	 gr4 -> SetMinimum(0.00);
         gr4 -> SetMaximum(1.05);
         gr4 -> GetYaxis()-> SetTitleOffset(1.7);
	 CanvSFPH->SetLeftMargin(0.15);
 	 gr4->GetXaxis() -> SetRangeUser(-3.15,3.15);

	 gr4 -> SetFillColor(629);
         gr4 -> SetLineColor(629);

	 gr4 -> GetXaxis() -> SetTitle("PHI");
         gr4 -> GetYaxis() -> SetTitle("SCALE FACTOR");

	 gr4 -> GetXaxis()-> SetNdivisions(509);
         gr4 -> GetYaxis()-> SetNdivisions(514);
	 CanvSFPH -> SetTitle("PHI Distribution, Tight Muon ID");

	 CanvSFPH->SetGridx();
         CanvSFPH->SetGridy();

	 gr4   -> SetMarkerStyle(21);
         gr4   -> SetMarkerColor(kRed);
         gr4   -> Draw("AP");


	//cout << "test" << endl;
        	
	 TString SFPH = sample_data;
	 TLegend* t12 = SetLegend(0.15, 0.2, 0.7, 0.4);
         t12->AddEntry(gr4, "SF 2016, Tight ID eff."     ,"lp");
         SFPH = sample_data;
	 t12->Draw("same");

	CanvSFPH -> SaveAs(Form("NewPlots/%ssf_phi_TIGHT.png",SFPH.Data()));	
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
