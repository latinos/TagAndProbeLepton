//for MC Id and ISOandTrig are the same, don't change size of file much:
//for Muon ID, Golden json Run 271036-274421 and Madgraph
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && (tag_IsoMu20_eta2p1 || tag_IsoMu20) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 20 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu20_pt10.root") {
//void subTree(TString dir="tpTree", TString cut="Loose && (tag_IsoMu20_eta2p1 || tag_IsoMu20) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 20 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu20_pt10.root") {

// for ISO and Trigger study:
// for run>=274094
//void subTree(TString dir="tpTree", TString cut="(tag_IsoMu20_eta2p1 || tag_IsoMu20) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 20 && pt >= 10. && mass > 70 && mass < 130 && Medium==1 && run>=274094", TString newFile="subTree_IsoMu20_pt10.root") {
// for run<274094
void subTree(TString dir="tpTree", TString cut="(tag_IsoMu20_eta2p1 || tag_IsoMu20) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 20 && pt >= 10. && mass > 70 && mass < 130 && Medium==1 && run<274094", TString newFile="subTree_IsoMu20_pt10.root") {

    //open file
    ////TFile *f1 = TFile::Open("root://eoscms//eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v1/data/TnPTree_80X_Run2016B_v1_DCSOnly.root");
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016B_v1_DCSOnly.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016B_v2_DCSOnly_UptoRun273450.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_DYLL_M50_MadGraphMLM_part1.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("subTree_80X_MadGraphLikeRun2016B_IdStudy.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421.root");//much faster (x10 or even x100) compare to open from /store
    TFile *f1 = TFile::Open("subTree_80X_Run2016B_v2_GoldenJSON_Run271036to274421_IdStudy.root");//for Muon ISO and Trigger much faster (x10 or even x100) compare to open from /store

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
