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

  //detailed bins -> not enought stat. for MediumID + ISO 
  double BinPt[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 30, 35, 40, 50, 60, 80, 120, 200};
  double BinEta[] = {-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, -0.2, 0.0, 0.2, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4}; 
  // less detailed binning 
  //double BinPt[] = {10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 60, 100, 200};
  //double BinEta[] = {-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4}; 

  int BinPtSize = int(sizeof(BinPt)/sizeof(BinPt[0]));
  int BinEtaSize = int(sizeof(BinEta)/sizeof(BinEta[0]));
  cout << "BinPtSize = " << BinPtSize << endl;
  cout << "BinEtaSize = " << BinEtaSize << endl;

  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_4_14/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_4_14/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_4_14/src/TagAndProbeLepton/Muons/eff_tnp/";

  TString sample_data = "TnP_IsoMu18_Run2015D_25ns_PTvsETA_binSmall";

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
  




  // and the graph afterwards


////////////////////////////////
  for (int ipt=0; ipt<BinPtSize-1; ipt++){

     TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d_&_Medium_pass_&_tag_IsoMu18_pass",ipt));
     //cout << tDATA << " ipt = " << ipt << endl;
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     Double_t *eff       = grDATA->GetY();
     Double_t *deff_high = grDATA->GetEYhigh();
     Double_t *deff_low  = grDATA->GetEYlow();

     TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta_ptGt20/fit_eff_plots/eta_PLOT_pt_bin%d_&_Medium_pass_&_tag_IsoMu18_pass",ipt));
     TGraphAsymmErrors* grDATA_ptGt20 = (TGraphAsymmErrors*) tDATA_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptGt20);
     Double_t *eff_ptGt20       = grDATA_ptGt20->GetY();
     Double_t *deff_high_ptGt20 = grDATA_ptGt20->GetEYhigh();
     Double_t *deff_low_ptGt20  = grDATA_ptGt20->GetEYlow();

     TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/Trigger_ptVSeta_ptLt20/fit_eff_plots/eta_PLOT_pt_bin%d_&_Medium_pass_&_tag_IsoMu18_pass",ipt));
     TGraphAsymmErrors* grDATA_ptLt20 = (TGraphAsymmErrors*) tDATA_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptLt20);
     Double_t *eff_ptLt20       = grDATA_ptLt20->GetY();
     Double_t *deff_high_ptLt20 = grDATA_ptLt20->GetEYhigh();
     Double_t *deff_low_ptLt20  = grDATA_ptLt20->GetEYlow();


     for (int ieta=0; ieta<BinEtaSize-1; ieta++){

        Double_t Eff = eff[ieta];
        Double_t dEff_high = deff_high[ieta];
        Double_t dEff_low = deff_low[ieta];
        if (Eff < 0.005) {Eff = 0.; dEff_high = 0.; dEff_low =0.;}
        if (Eff > 0.5 && dEff_high > 3*dEff_low) dEff_high = dEff_low;

        Double_t Eff_ptGt20 = eff_ptGt20[ieta];
        Double_t dEff_high_ptGt20 = deff_high_ptGt20[ieta];
        Double_t dEff_low_ptGt20 = deff_low_ptGt20[ieta];
        if (Eff_ptGt20 < 0.005) {Eff_ptGt20 = 0.; dEff_high_ptGt20 = 0.; dEff_low_ptGt20 =0.;}
        if (Eff_ptGt20 > 0.5 && dEff_high_ptGt20 > 3*dEff_low_ptGt20) dEff_high_ptGt20 = dEff_low_ptGt20;

        Double_t Eff_ptLt20 = eff_ptLt20[ieta];
        Double_t dEff_high_ptLt20 = deff_high_ptLt20[ieta];
        Double_t dEff_low_ptLt20 = deff_low_ptLt20[ieta];
        if (Eff_ptLt20 < 0.005) {Eff_ptLt20 = 0.; dEff_high_ptLt20 = 0.; dEff_low_ptLt20 =0.;}
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
        }
        else{
           myfile_HWW
                  << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t"
                  << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"
                  << Eff_ptGt20    << "\t" << dEff_high_ptGt20      << "\t " << dEff_low_ptGt20 <<"\n";
        }


     }
  }

  myfile.close();
////////////////////////////////
//  if (!isSave) return;

}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     //if( (histo -> GetErrorYhigh(i)) > 2.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(3));
  }

}
