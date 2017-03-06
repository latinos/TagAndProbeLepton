//for MC Id and ISOandTrig are the same, don't change size of file much:
//for Muon ID, Golden json Run 271036-275783 and Madgraph
//
//Moriond 2017
//data
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && (tag_IsoMu24 || tag_IsoTkMu24) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 24 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu24_ID_pt10.root") {
// L1 EMTF fixed from run 278167:
//void subTree(TString dir="tpTree", TString cut="run < 278167 && (Glb || TM) && (tag_IsoMu24 || tag_IsoTkMu24) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 24 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu24_ID_pt10.root") {
void subTree(TString dir="tpTree", TString cut="run >= 278167 && (Glb || TM) && (tag_IsoMu24 || tag_IsoTkMu24) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 24 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu24_ID_pt10.root") {
//MC
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 24 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu24_ID_pt10.root") {
//

    //open file
    // Moriond 2017
    //
    //for Data
    // 2016B
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root");
    // 2016C      
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016C_GoldenJSON_Run276098to276384.root");
    // 2016D      
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016D_GoldenJSON_Run276098to276384.root");
    // 2016E      
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016E_GoldenJSON_Run276098to276384.root");
    // 2016F      
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016F_GoldenJSON_Run276098to276384.root");
    TFile *f1 = TFile::Open("subTree_80XRereco_Run2016F_GoldenJSON_Run276098to276384.root");
    // 2016G      
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016G_GoldenJSON_Run278819to280384.root");
    // 2016H      
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016H_v2_GoldenJSON_Run281613to284035.root");
    //TFile *f1 = TFile::Open("TnPTree_80XRereco_Run2016H_GoldenJSON_Run284036to284044.root");
    //
    // MC      
    //TFile *f1 = TFile::Open("MC_Moriond17_DY_tranch4Premix_part1_5.root");
    //TFile *f1 = TFile::Open("MC_Moriond17_DY_tranch4Premix_part6_10.root");

    TTree *in  = (TTree *)f1->Get(dir+"/fitter_tree");
    TFile *fout = new TFile(newFile, "RECREATE");
    TDirectory *dout = fout->mkdir(dir); dout->cd();

    TTree *out = in->CopyTree(cut);
    std::cout << "INPUT TREE (" << in->GetEntries() << " ENTRIES)" << std::endl;
    //in->Print();
    std::cout << "OUTPUT TREE (" << out->GetEntries() << " ENTRIES)" << std::endl;
    //out->Print();
    dout->WriteTObject(out, "fitter_tree");
    fout->Close();
}
