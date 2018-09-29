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
    Double_t EventCSPrev = 0;
    Double_t CrystNbPrev = 0;
    Double_t EdepPrev = 0;
    Double_t EdepSum = 0;
    Double_t EdepOriginalArray[3000000];
    Double_t EdepAddBackArray[3000000];
    Double_t EdepComptSuppArray[3000000];

    Double_t EdepAddBackArrayCrystNb[3000000];
    Double_t EdepComptSuppArrayComptSupNb[3000000];

    static const Int_t NbCrystInRing = 15;
    static const Int_t NbRings = 3;

    Long64_t nbytes = 0, nb = 0;
    Long64_t itr = 0;
    Long64_t itr2 = 0;
    Long64_t itr3 = 0;
    Long64_t GoodEventCounter = 0;
    Long64_t GoodEventCounterPrev = 0;
    Long64_t GoodEventCounterPrevPrev = 0;
    Long64_t jentry;
    Long64_t ientry;
    Int_t i;
    Int_t j;

    Int_t counter = 1;
    Int_t CrystArray[NbCrystInRing][NbRings];
    for (i=0; i<NbCrystInRing; i++) {
        for (j=0; j<NbRings; j++) {
            CrystArray[i][j] = counter;
            counter += 1;
        }
    }

    Int_t PositionI1, PositionI2, PositionJ1, PositionJ2;

    for (jentry=0; jentry<nentries;jentry++) {
        ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        EdepOriginalArray[itr3] = EdepRes;
        itr3 += 1;
        if (Event - EventPrev != 0) {
            GoodEventCounterPrev = 0;
            GoodEventCounter = 0;
        }
        if ((CrystNbPrev == 0) && (CrystNb > 0)) {

            GoodEventCounterPrev = 0;
            GoodEventCounter = 0;
        }
        if (CrystNb != 0) {
            itr += 1;
            itr2 += 1;
                if (Event == EventPrev) {
                    for (i=0; i<NbCrystInRing; i++) {
                        for (j=0; j<NbRings; j++) {
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
                    if ((fabs(PositionI1-PositionI2) <= 1) && (fabs(PositionJ1-PositionJ2) <= 1)) {
                        EdepSum = EdepRes + EdepPrev;
                        itr -= 1;
                        itr2 -= 1;
                        GoodEventCounter -= 1;
                    }
                    else {
                        EdepSum = EdepRes;
                    }
                }
                else {
                    EdepSum = EdepRes;
                }

            EdepAddBackArray[itr] = EdepSum;
            EdepComptSuppArray[itr2] = EdepSum;

            EdepAddBackArrayCrystNb[itr2] = CrystNb;
            GoodEventCounter += 1;

        }

        if ((CrystNbPrev == 0) && (CrystNb == 0)){
            GoodEventCounter = GoodEventCounterPrev;
        }

        if (CrystNb == 0){
            for (i = 0; i < GoodEventCounter; i++) {
                if ((EventCS != 0) && (EventCS == EventPrev)) {
                    if ((ComptSuppNb - 100 == 1) && (EdepAddBackArrayCrystNb[itr2-i] >= 1) && (EdepAddBackArrayCrystNb[itr2-i] <= 6)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 2) && (EdepAddBackArrayCrystNb[itr2-i] >= 4) && (EdepAddBackArrayCrystNb[itr2-i] <= 9)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 3) && (EdepAddBackArrayCrystNb[itr2-i] >= 7) && (EdepAddBackArrayCrystNb[itr2-i] <= 12)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 4) && (EdepAddBackArrayCrystNb[itr2-i] >= 10) && (EdepAddBackArrayCrystNb[itr2-i] <= 15)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 5) && (EdepAddBackArrayCrystNb[itr2-i] >= 13) && (EdepAddBackArrayCrystNb[itr2-i] <= 18)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 6) && (EdepAddBackArrayCrystNb[itr2-i] >= 16) && (EdepAddBackArrayCrystNb[itr2-i] <= 21)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 7) && (EdepAddBackArrayCrystNb[itr2-i] >= 19) && (EdepAddBackArrayCrystNb[itr2-i] <= 24)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 8) && (EdepAddBackArrayCrystNb[itr2-i] >= 22) && (EdepAddBackArrayCrystNb[itr2-i] <= 27)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 9) && (EdepAddBackArrayCrystNb[itr2-i] >= 25) && (EdepAddBackArrayCrystNb[itr2-i] <= 30)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 10) && (EdepAddBackArrayCrystNb[itr2-i] >= 28) && (EdepAddBackArrayCrystNb[itr2-i] <= 33)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 11) && (EdepAddBackArrayCrystNb[itr2-i] >= 31) && (EdepAddBackArrayCrystNb[itr2-i] <= 36)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 12) && (EdepAddBackArrayCrystNb[itr2-i] >= 34) && (EdepAddBackArrayCrystNb[itr2-i] <= 39)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 13) && (EdepAddBackArrayCrystNb[itr2-i] >= 37) && (EdepAddBackArrayCrystNb[itr2-i] <= 42)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 14) && (EdepAddBackArrayCrystNb[itr2-i] >= 40) && (EdepAddBackArrayCrystNb[itr2-i] <= 45)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 15) && (EdepAddBackArrayCrystNb[itr2-i] >= 43) && (EdepAddBackArrayCrystNb[itr2-i] <= 45)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    else if ((ComptSuppNb - 100 == 15) && (EdepAddBackArrayCrystNb[itr2-i] >= 1) && (EdepAddBackArrayCrystNb[itr2-i] <= 3)) {
                        EdepComptSuppArray[itr2-i] = 0;
                    }
                    //else continue;

                    /*cout<<" Event deleted!!!"<<endl;
                    cout<<" Event deleted!!!"<<endl;
                    cout<<" Event deleted!!!"<<endl;*/
                }
            }

        }

        //cout<<"Event "<<Event<<"; "<<"CrystNb "<<CrystNb<<"; "<<"Edep "<<EdepRes<<"; "<<EdepSum<<endl;
        //cout<<EdepAddBackArray[itr]<<" length AB ="<<itr<<endl;
        //cout<<EdepComptSuppArray[itr2]<<" length CS ="<<itr2<<endl;
        /*cout<<" Event "<< Event<<endl;
        cout<<" EventPrev "<< EventPrev<<endl;
        cout<<" EventCS "<< EventCS<<endl;
        cout<<" EventCSPrev "<< EventCSPrev<<endl;*/
        //GoodEventCounterPrevPrev = GoodEventCounterPrev;
        GoodEventCounterPrev = GoodEventCounter;
        EventPrev = Event;
        EventCSPrev = EventCS;
        CrystNbPrev = CrystNb;
        EdepPrev = EdepRes;

    }

    TFile *File = new TFile("AddBack.root","recreate");
    TTree *Tree = new TTree("Total","Total Edep after AddBack");
    TH1F *h1 = new TH1F("TotalHistAB","Total Edep after AddBack", 2000, 0., 2000);
    TH1F *h2 = new TH1F("TotalHistCS","Total Edep after AddBack and Compton Suppression", 2000, 0., 2000);
    TH1F *h3 = new TH1F("TotalHistOriginal","Total Edep", 2000, 0., 2000);
    Double_t EdepAddBack;
    Tree->Branch("Edep", &EdepAddBack, "EdepAddBack/D");

    for (Int_t ij=0; ij<itr; ij++) {
        if (EdepAddBackArray[ij]>0) {
            EdepAddBack=EdepAddBackArray[ij];
            Tree->Fill();
            h1->Fill(EdepAddBack);
        }
    }

    Double_t EdepComptSupp;
    for (Int_t ij=0; ij<itr2; ij++) {
        if (EdepComptSuppArray[ij]>0) {
            EdepComptSupp=EdepComptSuppArray[ij];
            Tree->Fill();
            h2->Fill(EdepComptSupp);
        }
    }

    Double_t EdepOriginal;
    for (Int_t ij=0; ij<itr3; ij++) {
        if (EdepOriginalArray[ij]>0) {
            EdepOriginal=EdepOriginalArray[ij];
            Tree->Fill();
            h3->Fill(EdepOriginal);
        }
    }

    Tree->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    File->Close();
}
