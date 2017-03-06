
Run lxbatch jobs:
-----------------------

change mode

chmod 744 myJob.sh

to run:

     bsub -q 1nh -J job1 < myJob.sh 

     bsub -q 2nd -J j1_IDISO_1D < mylxbatch_fitMuon_MediumIDandISO_1Deff.sh

     bsub -q 2nd  -J j2_ID < mylxbatch_fitMuon_ID_PTvsETA.sh

     bsub -q 2nd -J j2_ID_MC < mylxbatch_fitMuon_ID_MC_PTvsETA.sh

     bsub -q 2nd -J j3_ISO < mylxbatch_fitMuon_ISO_PTvsETA.sh

     bsub -q 2nd -J j3_ISO_MC < mylxbatch_fitMuon_ISO_MC_PTvsETA.sh

     bsub -q 2nd -J j4_IDISO < mylxbatch_fitMuon_MediumIDandISO_PTvsETA.sh

     bsub -q 2nd  -J j5_Trig < mylxbatch_fitMuon_MuTrigger_PTvsETA.sh


Info:
-------------------

we have memory leak in code, so should request big memory until fix bug
but it is doesn't work, I try different ways, but they don't set up memory:

bsub -M 4000000 -> run with 4 GB memory at least (5 GB is not exist)
bsub -q 2nd -R "rusage[mem=4000000]"

No we fix it, just by using only part statistics (part3)

