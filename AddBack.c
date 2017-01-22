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
   Double_t EdepPrev = 0;
   Double_t EdepSum = 0;
   Double_t EdepAddBackArray[3000000];

   static const Int_t NbCrystInRing = 24;
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
	   EdepSum = Edep + EdepPrev;
           itr -= 1;
	}
	else {
	   EdepSum = Edep;
	}
      }

      else {
         EdepSum = Edep;
      }

      EdepAddBackArray[itr] = EdepSum;
      EventPrev = Event;
      CrystNbPrev = CrystNb;
      EdepPrev = Edep;

      cout<<"Event "<<Event<<"; "<<"CrystNb "<<CrystNb<<"; "<<"Edep "<<Edep<<"; "<<EdepSum<<endl;
      cout<<EdepAddBackArray[itr]<<" length ="<<itr<<endl;

   }

   TFile *File = new TFile("AddBack.root","recreate");
   TTree *Tree = new TTree("Total","Total Edep after AddBack");
   TH1F *h1 = new TH1F("TotalHist","Total Edep after AddBack", 15501, 0., 15500);
   Double_t EdepAddBack;
   Tree->Branch("Edep", &EdepAddBack, "EdepAddBack/D");

   for (Int_t ij=0; ij<itr; ij++) {
	 EdepAddBack=EdepAddBackArray[ij];
	 Tree->Fill();
     h1->Fill(EdepAddBack);
   }

   Tree->Write();
   h1->Write();
   File->Close();
}
