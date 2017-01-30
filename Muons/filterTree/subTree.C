//for MC Id and ISOandTrig are the same, don't change size of file much:
//for Muon ID, Golden json Run 271036-275783 and Madgraph
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && (tag_IsoMu22 || tag_IsoTkMu22) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 22 && pt >= 10. && mass > 70 && mass < 130 && run<=275783", TString newFile="subTree_IsoMu22_pt10.root") {
//fill 5043, runs 275757-275783 (latest fill in July 8 Golden json) 
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && (tag_IsoMu22 || tag_IsoTkMu22) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 22 && pt >= 10. && mass > 70 && mass < 130 && run>=275757 && run<=275783", TString newFile="subTree_IsoMu22_pt10.root") {
//for MC
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 22 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_80X_MadGraph_raw.root") {
//void subTree(TString dir="tpTree", TString cut="(Glb || TM) && (tag_IsoMu22 || tag_IsoTkMu22) && tag_combRelIsoPF04dBeta < 0.15 && tag_pt >= 22 && pt >= 10. && mass > 70 && mass < 130", TString newFile="subTree_IsoMu22_pt10.root") {

// for run>=276501 && run <=276811
//void subTree(TString dir="tpTree", TString cut="run>=276501 && run<=276811", TString newFile="subTree_IsoMu20_pt10.root") {
// for run>=275784 && run <=276500
void subTree(TString dir="tpTree", TString cut="run>=275784 && run<=276500", TString newFile="subTree_IsoMu20_pt10.root") {


// for Trigger study:
// for run>=276501 && run <=276811
//void subTree(TString dir="tpTree", TString cut=" Tight2012==1 && combRelIsoPF04dBeta < 0.15 && run>=276501 && run<=276811", TString newFile="subTree_IsoMu20_pt10.root") {
// for run>=275784 && run <=276500
//void subTree(TString dir="tpTree", TString cut=" Tight2012==1 && combRelIsoPF04dBeta < 0.15 && run>=275784 && run<=276500", TString newFile="subTree_IsoMu20_pt10.root") {
// for run>=275001 && run <=275783
//void subTree(TString dir="tpTree", TString cut=" Tight2012==1 && combRelIsoPF04dBeta < 0.15 && run>=275001 && run<=275783", TString newFile="subTree_IsoMu20_pt10.root") {
// for run>=274094 && run <=275000
//void subTree(TString dir="tpTree", TString cut=" Tight2012==1 && combRelIsoPF04dBeta < 0.15 && run>=274094 && run<=275000", TString newFile="subTree_IsoMu20_pt10.root") {
// for run<274094
//void subTree(TString dir="tpTree", TString cut=" Tight2012==1 && combRelIsoPF04dBeta < 0.15 && run<274094", TString newFile="subTree_IsoMu20_pt10.root") {

    //open file
    //for MC
    //TFile *f1 = TFile::Open("TnPTree_80X_DYLL_M50_MadGraphMLM_part1.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_DYLL_M50_MadGraphMLM_part2.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_DYLL_M50_MadGraphMLM_part3.root");//much faster (x10 or even x100) compare to open from /store
    // for Data
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016B_v2_GoldenJSON_Run271036to275125_incomplete.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016B_v2_GoldenJSON_Run275126to275783.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016C_v2_GoldenJSON_Run275126to275783.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016C_v2_GoldenJSON_Run275784to276097.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016C_v2_GoldenJSON_Run276098to276384.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016D_v2_GoldenJSON_Run276098to276384.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("TnPTree_80X_Run2016D_v2_GoldenJSON_Run276385to276811.root");//much faster (x10 or even x100) compare to open from /store
    //for Trigger Study:
    TFile *f1 = TFile::Open("subTree_80X_Run2016_Run275784to276811_IdStudy.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("subTree_80X_Run2016_Run271036to275783_IdStudy.root");//much faster (x10 or even x100) compare to open from /store
    //TFile *f1 = TFile::Open("subTree_80X_Run2016_Run275757to275783_IdStudy.root");//much faster (x10 or even x100) compare to open from /store

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
