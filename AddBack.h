///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
/// Implementation of the add-back algorithm for
/// the data simulated with the SpecMATscint GEANT4 simulation
///
/// \file AddBack.h
///

#ifndef AddBack_h
#define AddBack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
// Fixed size dimensions of array or collections stored in the TTree if any.

class AddBack {
  public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Double_t        Event;
  Double_t        CrystNb;
  Double_t        EdepRes;
  Double_t        EdepRes30Cryst;
  Double_t        EdepRes40Cryst;
  Double_t        EdepNoRes;
  Double_t        EdepNoRes30Cryst;
  Double_t        EdepNoRes40Cryst;

  string fileN;

  // List of branches
  TBranch        *b_Event;   //!
  TBranch        *b_CrystNb;   //!
  TBranch        *b_EdepRes;   //!
  TBranch        *b_EdepRes30Cryst;   //!
  TBranch        *b_EdepRes40Cryst;   //!
  TBranch        *b_EdepNoRes;   //!
  TBranch        *b_EdepNoRes30Cryst;   //!
  TBranch        *b_EdepNoRes40Cryst;   //!

  AddBack(TTree *tree=0);
  virtual ~AddBack();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef AddBack_cxx
AddBack::AddBack(TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.

  fileN = "CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma0.01MeV_Aluminum5083_Chamber_wallThick_3mm_linear_sourcePosition_129mm_FCEpoxy_epoxy_gap3mm.root";
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fileN.c_str());
    if (!f || !f->IsOpen()) {
      f = new TFile(fileN.c_str());
    }
    TDirectory * dir = (TDirectory*)f->Get(Form("%s:/ntuple", fileN.c_str()));
    dir->GetObject("Total",tree);
  }
  Init(tree);

}

AddBack::~AddBack()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t AddBack::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t AddBack::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void AddBack::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Event", &Event, &b_Event);
  fChain->SetBranchAddress("CrystNb", &CrystNb, &b_CrystNb);
  fChain->SetBranchAddress("EdepRes", &EdepRes, &b_EdepRes);
  fChain->SetBranchAddress("EdepRes30Cryst", &EdepRes30Cryst, &b_EdepRes30Cryst);
  fChain->SetBranchAddress("EdepRes40Cryst", &EdepRes40Cryst, &b_EdepRes40Cryst);
  fChain->SetBranchAddress("EdepRes", &EdepRes, &b_EdepRes);
  fChain->SetBranchAddress("EdepNoRes", &EdepNoRes, &b_EdepNoRes);
  fChain->SetBranchAddress("EdepNoRes30Cryst", &EdepNoRes30Cryst, &b_EdepNoRes30Cryst);
  fChain->SetBranchAddress("EdepNoRes40Cryst", &EdepNoRes40Cryst, &b_EdepNoRes40Cryst);
  Notify();
}

Bool_t AddBack::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void AddBack::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t AddBack::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef AddBack_cxx
