
To download CMS Muon POG Utiles:

     git clone https://github.com/cms-MuonPOG/TnPUtils.git

you could add new variables, built from other variables, in existing ntuple: addBranch.py

I have copied some useful tools to current directory

------


```bash
# We recreate the abseta branch using eta
# You can check the result afterwards using ROOT's TBrowser
./addBranch "examples/TnPTree.root" outputTree.root "abs(eta);eta" absetaNew

# You can even use numpy in the expression
./addBranch "examples/TnPTree.root" outputTree.root "numpy.log10(pt);pt" ptLog10

# Here some random, but complicated, expression
./addBranch "examples/TnPTree.root" outputTree.root "numpy.sqrt(pt*abs(eta))**3;pt;eta" randomVar


Examples:

    python addBranch "../filterTree/subTree_80XRereco_Run2016B_GoldenJSON_Run276098to276384.root" "output.root" "abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi" "pair_dPhi"



