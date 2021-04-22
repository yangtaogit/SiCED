#include <TFile.h>
#include <TTree.h>
#include <RtypesCore.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>

void SiCEDAnalysis(){


    TFile *rootfile = new TFile("SiCED_5um.root");

    TTree *mytree = (TTree *)rootfile->Get("SiCED");

    Double_t Edep_device;

    mytree->SetBranchAddress("Edep_device", &Edep_device);

    Double_t energy_bin = 100;

    TH1F *h1 = new TH1F("Edep_device", "Energy deposition in SiC", energy_bin, 0., 0.01);



    for(Int_t i=0 ; i<mytree->GetEntries() ; i++){

        mytree->GetEntry(i);

        h1->Fill(Edep_device);

    }

    TFile *outfut_file = new TFile("Edep.root","RECREATE");
    outfut_file->cd();
    h1->Write();


    TCanvas *c1 = new TCanvas("c1","c1", 500, 500);

    c1->cd(1);
    h1->GetXaxis()->SetTitle("Energy (MeV)");
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->SetTitle("Events");
    h1->GetYaxis()->CenterTitle();
    h1->Draw();

    c1->SaveAs("Edep.png");

}