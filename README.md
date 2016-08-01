# AddBack
AddBack algorithm for SpecMATscint

To perform "Add Back" algorithm on a data simulated with SpecMATscint one should follow the next instruction:

1. Copy the script into a folder with generated data

2. Hardcode (tree times) a name of the file which have to be "AddedBack" in ***AddBack.h***
 ```
  53 if (tree == 0) {
  54       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("file_name.root");
  55       if (!f || !f->IsOpen()) {
  56          f = new TFile("file_name.root");
  57       }
  58       TDirectory * dir = (TDirectory*)f->Get("file_name.root:/ntuple");
  59       dir->GetObject("Total",tree);
  60
  61 }
 ```

3. Hardcode the number of events in the simulation, the number of crystals in the ring and the number of rings used in the simulation
 ```
  41    Double_t EdepAddBackArray[3000000];
  42
  43    static const Int_t NbCrystInRing = 18;
  44    static const Int_t NbRings = 3;
 ```

4. Open the file in ROOT:
  ```
 $ root -l file_name.root
 ```

5. Hardcode (tree times) a name of the file which have to be "AddedBack" in ***AddBack.h***
 ```
  53 if (tree == 0) {
  54       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("file_name.root");
  55       if (!f || !f->IsOpen()) {
  56          f = new TFile("file_name.root");
  57       }
  58       TDirectory * dir = (TDirectory*)f->Get("file_name.root:/ntuple");
  59       dir->GetObject("Total",tree);
  60
  61    }
 ```

6. Hardcode the number of events in the simulation, number of crystals in the ring and the number of rings in the simulation
 ```
  41    Double_t EdepAddBackArray[3000000];
  42
  43    static const Int_t NbCrystInRing = 18;
  44    static const Int_t NbRings = 3;
 ```

7. Open the file with a data in ROOT
 ```
 $ root -l file_name.root
 ```
8. In ROOT
 ```
root [0]
Attaching file file_name.root as _file0...
root [1] .L AddBack.c
root [2] AddBack y
root [3] y.Loop()
 ```

9. If everything is fine you will see smth like:
 ```
Event 2; CrystNb 40; Edep 197.903; 197.903
197.903 length =1
Event 5; CrystNb 48; Edep 856.259; 856.259
856.259 length =2
...
 ```

10. As an output a ***AddBack.root*** file will be generated
