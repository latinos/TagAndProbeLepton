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
void tnp_PrintEff( bool isSave = true ) {
  
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
  // less detailed binning
  double PTmax = 10.; // plot efficiency only from pT > PTmax  
  double BinPt[] = {5, 8, 10, 13, 16, 20, 25, 30, 35, 40, 60, 100, 200};
  double BinEta[] = {-2.4, -2.1, -1.6, -1.2, -0.8, -0.3, 0.3, 0.8, 1.2, 1.6, 2.1, 2.4};

  int BinPtSize = int(sizeof(BinPt)/sizeof(BinPt[0]));
  int BinEtaSize = int(sizeof(BinEta)/sizeof(BinEta[0]));
  cout << "BinPtSize = " << BinPtSize << endl;
  cout << "BinEtaSize = " << BinEtaSize << endl;

  // ---------------------------------------------------------------------------
  // general variables
  TString png      = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  TString rootPlot = "/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/plot_tnp/Plots/";
  // ---------------------------------------------------------------------------


  // ---- open the MC files ----
  TString pathAnna="/afs/cern.ch/work/k/kropiv/MuonPOG/CMSSW_7_6_3_patch2/src/TagAndProbeLepton/Muons/eff_tnp/";

  //TString sample_data = "TnP_Medium_DY_madgraph25nsLikeRun2015D_25ns_PTvsETA";
  TString sample_data = "TnP_Medium_Run2015D_25ns_PTvsETA_part3";

  TString Tag_trig = "_&_tag_IsoMu20_pass";
  if (sample_data == "TnP_Medium_DY_madgraph25nsLikeRun2015D_25ns_PTvsETA") Tag_trig = "";

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


  ofstream myfile_HWW_tex;
  myfile_HWW_tex.open (sample_data+"_HWW_tex.txt");
  myfile_HWW_tex << "\\begin{sidewaystable}\n";
  if (sample_data == "TnP_Medium_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\caption{Muon ID (\"MediumHWW\") Efficiency for DATA}\n";
  if (sample_data == "TnP_Medium_Run2015D_25ns_PTvsETA_part3") myfile_HWW_tex << "\\label{table:MuonID:DATA}\n";
  if (sample_data == "TnP_Medium_DY_madgraph25nsLikeRun2015D_25ns_PTvsETA") myfile_HWW_tex << "\\caption{Muon ID (\"MediumHWW\") Efficiency for Madgraph MC}\n";
  if (sample_data == "TnP_Medium_DY_madgraph25nsLikeRun2015D_25ns_PTvsETA") myfile_HWW_tex << "\\label{table:MuonID:MC}\n";
  myfile_HWW_tex << "\\begin{tabular}{|l|l|l|l|l|l|l|l|l|l|l|l|}\n";
  myfile_HWW_tex << "\\hline\n";
  for (int ieta=0; ieta<BinEtaSize-1; ieta++){
      if(ieta == 0)              myfile_HWW_tex <<"$p_{T}/\\eta$ & " << BinEta[ieta] << ":" << BinEta[ieta+1];
      if(ieta > 0)               myfile_HWW_tex <<             " & " << BinEta[ieta] << ":" << BinEta[ieta+1];
      if(ieta == (BinEtaSize-2)) myfile_HWW_tex <<"\\\\ \n\\hline\n";
  }

////////////////////////////////
  




  // and the graph afterwards


////////////////////////////////
  for (int ipt=0; ipt<BinPtSize-1; ipt++){
     if (BinPt[ipt] < PTmax-0.0001) continue; // plot efficiency only with pT > PTmax
     TCanvas* tDATA = (TCanvas*) DATA->Get(Form("tpTree/Medium_ID_ptVSeta/fit_eff_plots/eta_PLOT_pt_bin%d%s",ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA = (TGraphAsymmErrors*) tDATA -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA);
     Double_t *eff       = grDATA->GetY();
     Double_t *deff_high = grDATA->GetEYhigh();
     Double_t *deff_low  = grDATA->GetEYlow();

     //TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/Medium_ID_ptVSeta_ptGt20/fit_eff_plots/eta_PLOT_pt_bin%d_&_tag_IsoMu18_pass",ipt));
     TCanvas* tDATA_ptGt20 = (TCanvas*) DATA->Get(Form("tpTree/Medium_ID_ptVSeta_ptGt20/fit_eff_plots/eta_PLOT_pt_bin%d%s",ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptGt20 = (TGraphAsymmErrors*) tDATA_ptGt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptGt20);
     Double_t *eff_ptGt20       = grDATA_ptGt20->GetY();
     Double_t *deff_high_ptGt20 = grDATA_ptGt20->GetEYhigh();
     Double_t *deff_low_ptGt20  = grDATA_ptGt20->GetEYlow();

     //TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/Medium_ID_ptVSeta_ptLt20/fit_eff_plots/eta_PLOT_pt_bin%d_&_tag_IsoMu18_pass",ipt));
     TCanvas* tDATA_ptLt20 = (TCanvas*) DATA->Get(Form("tpTree/Medium_ID_ptVSeta_ptLt20/fit_eff_plots/eta_PLOT_pt_bin%d%s",ipt,Tag_trig.Data() ));
     TGraphAsymmErrors* grDATA_ptLt20 = (TGraphAsymmErrors*) tDATA_ptLt20 -> GetListOfPrimitives()->At(1);
     ErrorCheck(grDATA_ptLt20);
     Double_t *eff_ptLt20       = grDATA_ptLt20->GetY();
     Double_t *deff_high_ptLt20 = grDATA_ptLt20->GetEYhigh();
     Double_t *deff_low_ptLt20  = grDATA_ptLt20->GetEYlow();


     for (int ieta=0; ieta<BinEtaSize-1; ieta++){

        myfile 
               //<< setprecision(4)
               << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t" 
               << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"  
               << eff[ieta]    << "\t" << deff_high[ieta]      << "\t " << deff_low[ieta] <<"\n"; //write to file
        myfile_ptGt20 
               << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t" 
               << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"  
               << eff_ptGt20[ieta]    << "\t" << deff_high_ptGt20[ieta]      << "\t " << deff_low_ptGt20[ieta] <<"\n"; //write to file
        myfile_ptLt20 
               << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t" 
               << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"  
               << eff_ptLt20[ieta]    << "\t" << deff_high_ptLt20[ieta]      << "\t " << deff_low_ptLt20[ieta] <<"\n"; //write to file
        if (BinPt[ipt+1] < 20.001){
           myfile_HWW
                  << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t"
                  << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"
                  << eff_ptLt20[ieta]    << "\t" << deff_high_ptLt20[ieta]      << "\t " << deff_low_ptLt20[ieta] <<"\n"; //write to file
        }
        else{
           myfile_HWW
                  << BinEta[ieta] << "\t" << BinEta[ieta+1] << "\t"
                  << BinPt[ipt]   << "\t" << BinPt[ipt+1]   << "\t"
                  << eff_ptGt20[ieta]    << "\t" << deff_high_ptGt20[ieta]      << "\t " << deff_low_ptGt20[ieta] <<"\n"; //write to file
        }

        if(ieta == 0)  myfile_HWW_tex << setprecision(4) << BinPt[ipt]   << ":" << BinPt[ipt+1];
        if (BinPt[ipt+1] < 20.001) {
           myfile_HWW_tex << " & ";
           if(eff_ptLt20[ieta] > 0.95) myfile_HWW_tex << "\\cellcolor{red} ";
           if(eff_ptLt20[ieta] > 0.90 && eff_ptLt20[ieta] <= 0.95) myfile_HWW_tex << "\\cellcolor{Maroon!80} ";
           if(eff_ptLt20[ieta] > 0.80 && eff_ptLt20[ieta] <= 0.90) myfile_HWW_tex << "\\cellcolor{Orange} ";
           if(eff_ptLt20[ieta] > 0.70 && eff_ptLt20[ieta] <= 0.80) myfile_HWW_tex << "\\cellcolor{Yellow} ";
           if(eff_ptLt20[ieta] > 0.50 && eff_ptLt20[ieta] <= 0.70) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
           if(eff_ptLt20[ieta] > 0.01 && eff_ptLt20[ieta] <= 0.50) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
           if (eff_ptLt20[ieta] < 0.10)myfile_HWW_tex << setprecision(2) <<  eff_ptLt20[ieta];
           else myfile_HWW_tex << setprecision(3) <<  eff_ptLt20[ieta];
        }
        else {
           myfile_HWW_tex << " & ";
           if(eff_ptGt20[ieta] > 0.95) myfile_HWW_tex << "\\cellcolor{red} ";
           if(eff_ptGt20[ieta] > 0.90 && eff_ptGt20[ieta] <= 0.95) myfile_HWW_tex << "\\cellcolor{Maroon!80} ";
           if(eff_ptGt20[ieta] > 0.80 && eff_ptGt20[ieta] <= 0.90) myfile_HWW_tex << "\\cellcolor{Orange} ";
           if(eff_ptGt20[ieta] > 0.70 && eff_ptGt20[ieta] <= 0.80) myfile_HWW_tex << "\\cellcolor{Yellow} ";
           if(eff_ptGt20[ieta] > 0.50 && eff_ptGt20[ieta] <= 0.70) myfile_HWW_tex << "\\cellcolor{YellowGreen} ";
           if(eff_ptGt20[ieta] > 0.01 && eff_ptGt20[ieta] <= 0.50) myfile_HWW_tex << "\\cellcolor{SkyBlue} ";
           if (eff_ptGt20[ieta] < 0.10) myfile_HWW_tex << setprecision(2) << eff_ptGt20[ieta];
           else myfile_HWW_tex << setprecision(3) << eff_ptGt20[ieta];
        }
        if (ieta == (BinEtaSize-2)) myfile_HWW_tex <<" \\\\ \n\\hline\n";

     }
  }
  myfile_HWW_tex << "\\end{tabular}\n\\end{sidewaystable}\n";

  myfile.close();
  myfile_ptGt20.close();
  myfile_ptLt20.close();
  myfile_HWW.close();
  myfile_HWW_tex.close();
////////////////////////////////
  if (!isSave) return;

}

//////////////////////////////////////////

void ErrorCheck(TGraphAsymmErrors* histo){
  /// check that up error are calculated properly because of problems in tag and probe fit 
  int nbin = histo -> GetN();
  for(int i = 0; i < nbin; i++){
     if( (histo -> GetErrorYhigh(i)) > 3.*(histo -> GetErrorYlow(i)) ) histo -> SetPointEYhigh(i,histo -> GetErrorYlow(i));
     if ( (histo -> GetErrorYhigh(i)) < 0.000001) histo -> SetPointEYhigh(i,0 );// very small error set to 0
     if ( (histo -> GetErrorYlow(i))  < 0.000001) histo -> SetPointEYlow(i,0 ); // very small error set to 0
  }

}
