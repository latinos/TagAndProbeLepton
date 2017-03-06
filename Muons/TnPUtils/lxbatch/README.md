
Run lxbatch jobs:
-----------------------

change mode

chmod 744 myJob.sh

to run:

     bsub -q 2nd -J job_2017B < mylxbatch_2017B.sh 
     bsub -q 2nd -J job_2017C < mylxbatch_2017C.sh 
     bsub -q 2nd -J job_2017D < mylxbatch_2017D.sh 
     bsub -q 2nd -J job_2017E < mylxbatch_2017E.sh 
     bsub -q 2nd -J job_2017F2 < mylxbatch_2017F2.sh 
     bsub -q 2nd -J job_2017F3 < mylxbatch_2017F3.sh 
     bsub -q 2nd -J job_2017G < mylxbatch_2017G.sh 
     bsub -q 2nd -J job_2017H1 < mylxbatch_2017H1.sh 
     bsub -q 2nd -J job_2017H2 < mylxbatch_2017H2.sh 


Info:
-------------------

we have memory leak in code, so should request big memory until fix bug
but it is doesn't work, I try different ways, but they don't set up memory:

bsub -M 4000000 -> run with 4 GB memory at least (5 GB is not exist)
bsub -q 2nd -R "rusage[mem=4000000]"

No we fix it, just by using only part statistics (part3)

