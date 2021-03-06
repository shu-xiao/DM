import os

### Preparing the dataset, crab and pset configuration files
def prepare(dataset):
    os.system('rm -rf step0_inputdataset.txt')
    f = open(dataset,'r')
    for line in f:
        print line
        a=[]
        b=[]
        a,b = line.split()
        datasetdetail=[a,b]
        print datasetdetail
        name='crab status -d crab_projects_MonoHStepLHE/crab_stepLHE-'+datasetdetail[1]+' | grep -a "Output dataset:" | awk -v my_var='+datasetdetail[1]+' \'{print $3,my_var}\'>> step0_inputdataset.txt'
        print name
        os.system(name)


def submit():
    print "submitting"
    f = open('step0_inputdataset.txt','r')
    for line in f:
        print line
        a=[]
        b=[]
        a,b = line.split()
        datasetdetail=[a,b]
        print datasetdetail
        name='crab submit -c crabConfig_step0.py General.requestName=step0-'+datasetdetail[1]+' Data.inputDataset='+datasetdetail[0]
        print name
        os.system(name)


def status(crabdirname):
    import os
    os.system ("./Statusall.sh "+crabdirname)
    

## Add a help or usage function here 
def help() :
    print "this is under progress"

    


####################################################################################################################################################
####################################################################################################################################################
## this will control the functions   ##
## convert this to python main.      ##
####################################################################################################################################################
####################################################################################################################################################
import os
import sys
print sys.argv

## safety check
## improve this
if len(sys.argv) < 2 :
    print "insufficient options provided see help function "
    help()
    exit (1)




## prepare jobs
if sys.argv[1] == "prepare" :
    if len(sys.argv) != 3 :
        print "Usuage: python MultiCrab_step0.py prepare dataset.txt"
        exit (1)
    else:
        print "preparing for the submission"
        datasetTxt = sys.argv[2]
        prepare(datasetTxt)


## submit jobs 
if len(sys.argv) == 2 :
    if sys.argv[1] == "submit" :
        submit()


## check status of jobs 
## send the crab directory 
if len(sys.argv) == 3 : 
    if sys.argv[1] == "status" :
        crabdir = sys.argv[2]
        status(crabdir)




