#define AddBack_cxx
#include "AddBack.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>

void AddBack::Loop()
{
    //   In a ROOT session, you can do:
    //      Root > .L AddBack.C
    //      Root > AddBack t
    //      Root > t.GetEntry(12); // Fill t data members with entry number 12
    //      Root > t.Show();       // Show values of entry 12
    //      Root > t.Show(16);     // Read and show values of entry 16
    //      Root > t.Loop();       // Loop on all entries
    //

    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    //by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Double_t EventPrev = 0;
    Double_t CrystNbPrev = 0;
    Double_t EdepResPrev = 0;
    Double_t EdepResSum = 0;
    Double_t EdepResAddBackArray[3000000];

    static const Int_t NbCrystInRing = 15;
    static const Int_t NbRings = 2;

    Long64_t nbytes = 0, nb = 0;
    Long64_t itr = 0;

    Int_t counter = 1;
    Int_t CrystArray[NbCrystInRing][NbRings];
    for (Int_t i=0; i<NbCrystInRing; i++) {
        for (Int_t j=0; j<NbRings; j++) {
            CrystArray[i][j] = counter;
            counter += 1;
        }
    }

    Int_t PositionI1, PositionI2, PositionJ1, PositionJ2;

    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        itr += 1;
        if (Event == EventPrev) {

            for (Int_t i=0; i<NbCrystInRing; i++) {
                for (Int_t j=0; j<NbRings; j++) {
                    if (CrystArray[i][j] == CrystNb) {
                        PositionI1 = i;
                        PositionJ1 = j;
                    }
                    if (CrystArray[i][j] == CrystNbPrev) {
                        PositionI2 = i;
                        PositionJ2 = j;
                    }
                }
            }
            if ((fabs(PositionI1-PositionI2)<=1) && (fabs(PositionJ1-PositionJ2)<=1)) {
                EdepResSum = EdepRes + EdepResPrev;
                itr -= 1;
            }
            else {
                EdepResSum = EdepRes;
            }
        }

        else {
            EdepResSum = EdepRes;
        }

        EdepResAddBackArray[itr] = EdepResSum;
        EventPrev = Event;
        CrystNbPrev = CrystNb;
        EdepResPrev = EdepRes;
        /*
        if (Event%10000 == 0) {
          cout<<"Event "<<Event<<"; "<<"CrystNb "<<CrystNb<<"; "<<"EdepRes "<<EdepRes<<"; "<<EdepResSum<<endl;
          cout<<EdepResAddBackArray[itr]<<" length ="<<itr<<endl;
        }*/

    }

    TFile *File = new TFile(Form("AddBack_%s", fileN.c_str()),"recreate");
    TTree *Tree = new TTree("Total","Total EdepRes after AddBack");
    TH1F *h1 = new TH1F("TotalHistAB","Total EdepRes after AddBack", 1500, 0., 1500);
    Double_t EdepResAddBack;
    Tree->Branch("EdepNoRes", &EdepResAddBack, "EdepResAddBack/D");

    for (Int_t ij=0; ij<itr; ij++) {
        EdepResAddBack=EdepResAddBackArray[ij];
        Tree->Fill();
        h1->Fill(EdepResAddBack);
    }

    Tree->Write();
    h1->Write();
    File->Close();
}
