///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
/// Implementation of the add-back algorithm for
/// the data simulated with the SpecMATscint GEANT4 simulation
///
/// \file AddBack.c
///
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
    Double_t EdepRes30CrystPrev = 0;
    Double_t EdepRes40CrystPrev = 0;
    Double_t EdepNoResPrev = 0;
    Double_t EdepNoRes30CrystPrev = 0;
    Double_t EdepNoRes40CrystPrev = 0;
    Double_t EdepResSum = 0;
    Double_t EdepRes30CrystSum = 0;
    Double_t EdepRes40CrystSum = 0;
    Double_t EdepNoResSum = 0;
    Double_t EdepNoRes30CrystSum = 0;
    Double_t EdepNoRes40CrystSum = 0;
    Double_t EdepResAddBackArray[3000000];
    Double_t EdepRes30CrystAddBackArray[3000000];
    Double_t EdepRes40CrystAddBackArray[3000000];
    Double_t EdepNoResAddBackArray[3000000];
    Double_t EdepNoRes30CrystAddBackArray[3000000];
    Double_t EdepNoRes40CrystAddBackArray[3000000];

    static const Int_t NbCrystInRing = 15;
    static const Int_t NbRings = 3;

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
                EdepNoResSum = EdepNoRes + EdepNoResPrev;
                //if ((PositionJ1<NbRings)&&(PositionJ2<NbRings)) {
                  EdepRes30CrystSum = EdepRes30Cryst + EdepRes30CrystPrev;
                  EdepNoRes30CrystSum = EdepNoRes30Cryst + EdepNoRes30CrystPrev;
                //}
                //if (((PositionJ1<NbRings)&&(PositionJ2<NbRings))||((PositionJ1==2)&&(PositionI1<10))||((PositionJ2==2)&&(PositionI2<10))) {
                  EdepRes40CrystSum = EdepRes40Cryst + EdepRes40CrystPrev;
                  EdepNoRes40CrystSum = EdepNoRes40Cryst + EdepNoRes40CrystPrev;
		  //cout << EdepNoResSum << " " << EdepNoRes30CrystSum << " " << EdepNoRes40CrystSum << endl;
                //}
                itr -= 1;
            }
            else {
                EdepResSum = EdepRes;
                EdepRes30CrystSum = EdepRes30Cryst;
		EdepRes40CrystSum = EdepRes40Cryst;

                EdepNoResSum = EdepNoRes;
                EdepNoRes30CrystSum = EdepNoRes30Cryst;
		EdepNoRes40CrystSum = EdepNoRes40Cryst;

            }
        }

        else {
            EdepResSum = EdepRes;
            EdepRes30CrystSum = EdepRes30Cryst;
	    EdepRes40CrystSum = EdepRes40Cryst;

            EdepNoResSum = EdepNoRes;
            EdepNoRes30CrystSum = EdepNoRes30Cryst;
	    EdepNoRes40CrystSum = EdepNoRes40Cryst;

        }

        EdepResAddBackArray[itr] = EdepResSum;
        EdepRes30CrystAddBackArray[itr] = EdepRes30CrystSum;
        EdepRes40CrystAddBackArray[itr] = EdepRes40CrystSum;
        EdepNoResAddBackArray[itr] = EdepNoResSum;
        EdepNoRes30CrystAddBackArray[itr] = EdepNoRes30CrystSum;
        EdepNoRes40CrystAddBackArray[itr] = EdepNoRes40CrystSum;
        EventPrev = Event;
        CrystNbPrev = CrystNb;
        EdepResPrev = EdepRes;
        EdepNoResPrev = EdepNoRes;
	EdepNoRes30CrystPrev = EdepNoRes30Cryst;
	EdepNoRes40CrystPrev = EdepNoRes40Cryst;
        /*
        if (Event%10000 == 0) {
          cout<<"Event "<<Event<<"; "<<"CrystNb "<<CrystNb<<"; "<<"EdepRes "<<EdepRes<<"; "<<EdepResSum<<endl;
          cout<<EdepResAddBackArray[itr]<<" length ="<<itr<<endl;
        }*/

    }

    TFile *File = new TFile(Form("AddBack_%s", fileN.c_str()),"recreate");
    TTree *Tree = new TTree("Total","Total Edep after AddBack");
    TH1F *h1 = new TH1F("TotalHistAB","Total EdepRes after AddBack", 16000, 0., 16000);
    TH1F *h2 = new TH1F("TotalHistAB30Cryst","Total EdepRes after AddBack for 30Crsyt", 16000, 0., 16000);
    TH1F *h3 = new TH1F("TotalHistAB40Cryst","Total EdepRes after AddBack for 40Crsyt", 16000, 0., 16000);
    TH1F *h4 = new TH1F("TotalHistABNoRes","Total EdepNoRes after AddBack", 16000, 0., 16000);
    TH1F *h5 = new TH1F("TotalHistAB30CrystNoRes","Total EdepNoRes after AddBack for 30Crsyt", 16000, 0., 16000);
    TH1F *h6 = new TH1F("TotalHistAB40CrystNoRes","Total EdepNoRes after AddBack for 40Crsyt", 16000, 0., 16000);
    Double_t EdepResAddBack;
    Double_t EdepRes30CrystAddBack;
    Double_t EdepRes40CrystAddBack;
    Double_t EdepNoResAddBack;
    Double_t EdepNoRes30CrystAddBack;
    Double_t EdepNoRes40CrystAddBack;
    Tree->Branch("EdepResAB", &EdepResAddBack, "EdepResAddBack/D");
    Tree->Branch("EdepRes30CrystAB", &EdepRes30CrystAddBack, "EdepRes30CrystAddBack/D");
    Tree->Branch("EdepRes40CrystAB", &EdepRes40CrystAddBack, "EdepRes40CrystAddBack/D");
    Tree->Branch("EdepNoRes", &EdepNoResAddBack, "EdepNoResAddBack/D");
    Tree->Branch("EdepNoRes30CrystAB", &EdepNoRes30CrystAddBack, "EdepNoRes30CrystAddBack/D");
    Tree->Branch("EdepNoRes40CrystAB", &EdepNoRes40CrystAddBack, "EdepNoRes40CrystAddBack/D");

    for (Int_t ij=0; ij<itr; ij++) {
        EdepResAddBack=EdepResAddBackArray[ij];
        EdepRes30CrystAddBack=EdepRes30CrystAddBackArray[ij];
        EdepRes40CrystAddBack=EdepRes40CrystAddBackArray[ij];

        EdepNoResAddBack=EdepNoResAddBackArray[ij];
        EdepNoRes30CrystAddBack=EdepNoRes30CrystAddBackArray[ij];
        EdepNoRes40CrystAddBack=EdepNoRes40CrystAddBackArray[ij];
        Tree->Fill();
        h1->Fill(EdepResAddBack);
        h2->Fill(EdepRes30CrystAddBack);
        h3->Fill(EdepRes40CrystAddBack);
        h4->Fill(EdepNoResAddBack);
        h5->Fill(EdepNoRes30CrystAddBack);
        h6->Fill(EdepNoRes40CrystAddBack);
    }

    Tree->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();
    h6->Write();
    File->Close();
}
