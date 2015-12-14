#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <vector>
#include <iostream>

//void addNVtxWeight(TString treeName="tpTree", TString cut = "") { //, TString cut="(tag_IsoMu24_eta2p1 || tag_IsoMu24) && tag_combRelIso < 0.15") {
//void addNVtxWeight(TString treeName="tpTree", TString cut = "pt>10") { //, TString cut="(tag_IsoMu24_eta2p1 || tag_IsoMu24) && tag_combRelIso < 0.15") {
void addNVtxWeight(TString treeName="tpTree", TString cut = "pt>10 && combRelIsoPF04dBeta < 0.15 && (tag_IsoMu20 || tag_IsoTkMu20) && tag_pt>22") { //, TString cut="(tag_IsoMu24_eta2p1 || tag_IsoMu24) && tag_combRelIso < 0.15") {
    if (gROOT->GetListOfFiles()->GetSize() < 2) {
        std::cerr << "USAGE: root.exe -b -l -q mcFile.root dataFile.root [more data files...] addNVtxWeight.cxx+" << std::endl;
        return;
    }
    std::cout << "Gathering trees ..." << std::endl;
    TTree  &tMC = * (TTree *) ((TFile*)gROOT->GetListOfFiles()->At(0))->Get(treeName+"/fitter_tree");
    TChain tData( treeName+"/fitter_tree" );
    for (int i = 1; i < gROOT->GetListOfFiles()->GetSize(); ++i) {
        tData.AddFile(((TFile*)gROOT->GetListOfFiles()->At(i))->GetName());
    }

    TCanvas *c1 = new TCanvas("c1","c1");
    c1->Divide(2,1); c1->cd(1);
    std::cout << "Filling distributions of vertices ..." << std::endl;
    tData.Draw("tag_nVertices>>hData(100,-0.5,99.5)", cut);
    c1->cd(2);
    tMC.Draw("tag_nVertices>>hMC(100,-0.5,99.5)", cut);
    c1->Print("nVtx.png");

    std::cout << "Computing weights ..." << std::endl;
    TH1F *hData = (TH1F*) gROOT->FindObject("hData");
    TH1F *hMC = (TH1F*) gROOT->FindObject("hMC");
    hData->Sumw2();
    hMC->Sumw2();
    hData->Scale(1.0/hData->Integral());
    hMC->Scale(1.0/hMC->Integral());
    std::vector<double> weights(hData->GetNbinsX()+1, 1.0);
    for (int i = 1, n = weights.size(); i < n; ++i) {
        double nMC = hMC->GetBinContent(i), nData = hData->GetBinContent(i);
        double d_nMC = hMC->GetBinError(i), d_nData = hData->GetBinError(i);
        double d_weight = 0;
        if(nData > 0 && nMC > 0) d_weight = nData/nMC *sqrt(d_nMC*d_nMC/nMC/nMC + d_nData*d_nData/nData/nData);
        weights[i-1] = (nMC > 0 ? nData/nMC : 1.0);
        if(nData == 0) weights[i-1] =0;
        printf("event with %d primary vertices gets a weight of %.4f +- %.4f \n", int(i-1), weights[i-1], d_weight);
        if(nData > 0 && nMC > 0) printf("event with %d primary vertices gets d_nMC/nMC = %.4f with d_nData/nData = %.6f \n", int(i-1), float(d_nMC/nMC), float(d_nData/nData));
    }

    std::cout << "Adding weight column ..." << std::endl;
    Float_t nVtx, weight;
    tMC.SetBranchAddress("tag_nVertices", &nVtx);
    TFile *fOut = new TFile("tnpZ_withNVtxWeights.root", "RECREATE");
    fOut->mkdir("tpTree")->cd();
    TTree *tOut = tMC.CloneTree(0);
    tOut->Branch("weight", &weight, "weight/F");
    int step = tMC.GetEntries()/100;
    double evDenom = 100.0/double(tMC.GetEntries());
    TStopwatch timer; timer.Start();
    for (int i = 0, n = tMC.GetEntries(); i < n; ++i) {
        tMC.GetEntry(i);
        weight = weights[int(nVtx)];
        if (i < 20) {
            printf("event with %d primary vertices gets a weight of %.4f\n", int(nVtx), weight);
        }
        tOut->Fill();
        if ((i+1) % step == 0) { 
            double totalTime = timer.RealTime()/60.; timer.Continue();
            double fraction = double(i+1)/double(n+1), remaining = totalTime*(1-fraction)/fraction;
            printf("Done %9d/%9d   %5.1f%%   (elapsed %5.1f min, remaining %5.1f min)\n", i, n, i*evDenom, totalTime, remaining); 
            fflush(stdout); 
        }
    }

    tOut->AutoSave(); // according to root tutorial this is the right thing to do

    std::cout << "Wrote output to " << fOut->GetName() << std::endl;
    fOut->Close();
}
