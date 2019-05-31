# AddBack
AddBack algorithm for SpecMATscint

AddBack will consider an event as a "good" event and add together deposited energies after the scattering and the following either next scattering or full absorption in crystals if:
- A gamma-ray have scattered multiple times within one event.
- The second interaction of the gamma-ray with the detectors array has happened not far than one crystal away from the first scattering.

<div align="center"><img src="https://cloud.githubusercontent.com/assets/17125100/17292796/6b877052-57ec-11e6-9361-4065aeac6c14.png"></div>

To apply the AddBack algorithm to the simulated data with SpecMATscint, one should follow the next instruction:

1. Copy the script into a folder with the generated data

2. Input the filename into ***AddBack.h***
 ```
 55 fileN = "filename.root";
 ```

3. Input the number of events generated in the SpecMATscint simulation as well as the number of crystals in the ring and the number of rings used in the simulation
 ```
  41    Double_t EdepAddBackArray[3000000];
  42
  43    static const Int_t NbCrystInRing = 15;
  44    static const Int_t NbRings = 2;
 ```

4. Open the file with the simulated data in ROOT
 ```
 $ root -l filename.root
 ```

5. In ROOT
 ```
root [0]
Attaching file filename.root as _file0...
root [1] .L AddBack.c
root [2] AddBack y
root [3] y.Loop()
 ```

6. Example:
 ```
ksf165:~/SpecMATscint_build> root -l CeBr3_48mmx48mmx48mm_15x1x2crystals_R131.25mm_gamma0.19MeV_Al_Chamber_pos2_pointSource_gap_3.root
root [0]
Attaching file CeBr3_48mmx48mmx48mm_15x1x2crystals_R131.25mm_gamma0.19MeV_Al_Chamber_pos2_pointSource_gap_3.root as _file0...
root [1] .L AddBack.c
root [2] AddBack y
root [3] y.Loop()
root [4] .q
 ```

7. A ***AddBack_filename.root*** file will be generated as an output.
