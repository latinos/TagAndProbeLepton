CRAB3
====

We use crab only for PromptReco Run2015. For Re-reco we are using standard Muon POG trees.

See details here:

    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial#CRAB_configuration_parameters
    https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile

Check if you have writing permissions:

    source /cvmfs/cms.cern.ch/crab3/crab.sh
    source /cvmfs/cms.cern.ch/crab3/crab.csh

    crab checkwrite --site=T2_CH_CERN
    crab checkwrite --site=T2_CH_CERN --lfn=/store/group/phys_higgs/cmshww/amassiro/RunII/test/

Send the jobs:

    crab submit -c crab_example1.py
    crab status

MultiCRAB
====

    cmsenv


    python multicrab.py samples/samples_spring15.py - it is not working version

    working versions:

    python multicrab_Run2015B.py samples/samples_Run2015B.py 

    python multicrab_Run2015C_Prompt_50ns.py samples/samples_Run2015C_50ns.py

    python multicrab_Run2015C_Prompt_25ns.py samples/samples_Run2015C_25ns.py

    python multicrab_Run2015D_Prompt_25ns.py samples/samples_Run2015D_25ns.py

    python multicrab_MClikeData.py samples/samples_spring15.py

    crab status -d folder_name
