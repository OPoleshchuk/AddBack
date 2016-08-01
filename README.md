# AddBack
AddBack algorithm for SpecMATscint

AddBack will consider an event as a "good" event and add together the first and the second deposited energies in crystals if:
- A gamma-ray have scattered multiple times within one event.
- At the second time the gamma-ray have deposited energy not far than one crystal away from the first scattering.

<div align="center"><img src="https://cloud.githubusercontent.com/assets/17125100/17292796/6b877052-57ec-11e6-9361-4065aeac6c14.png"></div>

To perform "Add Back" algorithm on a data simulated with SpecMATscint one should follow the next instruction:

1. Copy the script into a folder with generated data

2. Hardcode (three times) a name of the file in ***AddBack.h***
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

3. Hardcode the number of events generated in the simulation and the number of crystals in the ring and the number of rings used in the simulation
 ```
  41    Double_t EdepAddBackArray[3000000];
  42
  43    static const Int_t NbCrystInRing = 18;
  44    static const Int_t NbRings = 3;
 ```

4. Open the file with a data in ROOT
 ```
 $ root -l file_name.root
 ```

5. In ROOT
 ```
root [0]
Attaching file file_name.root as _file0...
root [1] .L AddBack.c
root [2] AddBack y
root [3] y.Loop()
 ```

6. If everything is fine you will see smth like:
 ```
Event 2; CrystNb 40; Edep 197.903; 197.903
197.903 length =1
Event 5; CrystNb 48; Edep 856.259; 856.259
856.259 length =2
...
 ```

7. As an output a ***AddBack.root*** file will be generated
