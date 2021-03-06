import os
from WMCore.Configuration import Configuration
config = Configuration()

pyCfgParams = ['outputFile=tnp_MC.root']

config.section_('General')
config.General.transferLogs = True
config.General.workArea     = 'crab_projects_tnp_v2'  # Make sure you set this parameter

config.section_('JobType')
config.JobType.pluginName       = 'Analysis'
#config.JobType.pluginName       = 'PrivateMC'
config.JobType.psetName         = '../tnpTreeProduction/tp_from_aod_MC_crab.py'
config.JobType.maxJobRuntimeMin = 2800
config.JobType.outputFiles      = ['tnp_MC.root']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')    
config.Data.inputDBS      = 'global'
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 5 # number of files, lumi sec. or events depending of "splitting"
#config.Data.totalUnits    = 1 # total number of files, lumi sec. or events depending of "splitting"
#config.Data.outLFNDirBase = '/store/group/phys_higgs/cmshww/amassiro/RunII/test/'
config.Data.outLFNDirBase = '/store/group/phys_higgs/cmshww/kropiv/TnP_Muons/'
config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/AODSIM'

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'


import sys

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand

    def submit(config):
        print " to do: ",config
        res = crabCommand('submit', config = config)

    ######### From now on this is what users should modify. It is the a-la-CRAB2 configuration part.
   
    print sys.argv
    if len(sys.argv) <= 1 :
       print "no arguments?"
       print "Usage: python multicrab_template.py test.py"
       exit()
       

    samples = {}
    SamplesFile = sys.argv[1]
    print " SamplesFile = ", SamplesFile
    
    if os.path.exists(SamplesFile):
       handle = open(SamplesFile,'r')
       exec(handle)
       handle.close()
                
    # samples to be analysed
                   
    for key, value in samples.iteritems():
        print key, ' -> ', value
        
        config.General.requestName = key
        config.JobType.pyCfgParams = list(pyCfgParams)
        config.JobType.pyCfgParams.extend(value[1])
        submit(config)

