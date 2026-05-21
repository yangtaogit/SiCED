#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>

// Usage:
//   root -l -q 'SiCEDAnalysis.C("2200keV")'
//   root -l -q 'SiCEDAnalysis.C("546keV")'
void SiCEDAnalysis(const char* energyTag = "2200keV") {

    TString fSiName  = TString::Format("SiCED_100um_Si_%s.root",  energyTag);
    TString fSiCName = TString::Format("SiCED_100um_SiC_%s.root", energyTag);

    TFile *fSi  = new TFile(fSiName);
    TFile *fSiC = new TFile(fSiCName);

    if (!fSi->IsOpen()  || fSi->IsZombie())  { printf("Cannot open %s\n", fSiName.Data());  return; }
    if (!fSiC->IsOpen() || fSiC->IsZombie()) { printf("Cannot open %s\n", fSiCName.Data()); return; }

    TTree *treeSi  = (TTree*)fSi->Get("SiCED");
    TTree *treeSiC = (TTree*)fSiC->Get("SiCED");

    Double_t Edep;
    const Int_t    nbins = 200;
    const Double_t emin  = 0.0, emax = 0.1;   // MeV

    TH1F *hSi  = new TH1F("hSi",  "", nbins, emin, emax);
    TH1F *hSiC = new TH1F("hSiC", "", nbins, emin, emax);

    treeSi->SetBranchAddress("Edep_device", &Edep);
    for (Long64_t i = 0; i < treeSi->GetEntries(); i++) {
        treeSi->GetEntry(i);
        hSi->Fill(Edep);
    }

    treeSiC->SetBranchAddress("Edep_device", &Edep);
    for (Long64_t i = 0; i < treeSiC->GetEntries(); i++) {
        treeSiC->GetEntry(i);
        hSiC->Fill(Edep);
    }

    // --- Style ---
    gStyle->SetOptStat(0);
    gStyle->SetGridStyle(3);          // dotted grid
    gStyle->SetTitleSize(0.050, "xyz");
    gStyle->SetLabelSize(0.048, "xyz");
    gStyle->SetTitleFontSize(0.052);

    // Square canvas
    TCanvas *c1 = new TCanvas("c1", "Energy Deposition Comparison", 600, 600);
    c1->SetGrid();
    c1->SetLeftMargin(0.16);
    c1->SetRightMargin(0.05);
    c1->SetBottomMargin(0.13);
    c1->SetTopMargin(0.09);

    // Si: blue semi-transparent
    hSi->SetFillColorAlpha(kBlue+2, 0.5);
    hSi->SetLineColor(kBlue+2);
    hSi->SetLineWidth(1);

    // SiC: yellow semi-transparent
    hSiC->SetFillColorAlpha(kYellow, 0.5);
    hSiC->SetLineColor(kOrange-3);
    hSiC->SetLineWidth(1);

    Double_t ymax = TMath::Max(hSi->GetMaximum(), hSiC->GetMaximum()) * 1.1;

    TString title = TString::Format("Energy deposition in 100 #mum Si & SiC");
    hSi->SetTitle(title);

    hSi->GetXaxis()->SetTitle("Energy (MeV)");
    hSi->GetXaxis()->CenterTitle();
    hSi->GetXaxis()->SetRangeUser(emin, emax);
    hSi->GetXaxis()->SetNdivisions(-5);       // exactly 5 major ticks: 0.02 MeV/div

    hSi->GetYaxis()->SetTitle("Counts");
    hSi->GetYaxis()->CenterTitle();
    hSi->GetYaxis()->SetTitleOffset(1.4);
    hSi->SetMaximum(ymax);

    hSi->Draw("HIST");
    hSiC->Draw("HIST SAME");

    TString outPng  = TString::Format("Edep_comparison_%s.png",  energyTag);
    TString outRoot = TString::Format("Edep_comparison_%s.root", energyTag);

    c1->SaveAs(outPng);
    printf("Saved %s\n", outPng.Data());

    TFile *outfile = new TFile(outRoot, "RECREATE");
    hSi->Write();
    hSiC->Write();
    outfile->Close();
}
