##########################################################
# Magic to configure Linux environment ###################

Extend file /home/<username>/.bashrc with next variables:

export POCO_BASE=/home/olehk/projects/02.06.02.05/package/aivc/aivc-macchina
export PATH=$PATH:$POCO_BASE/platform/RemotingNG/RemoteGen/bin/Linux/x86_64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$POCO_BASE/platform/lib/Linux/x86_64

##########################################################
# WINDOWS: Invoke this command from msvc command prompt ##

RemoteGenNGd RemoteGen.xml /compiler=msvc /define=POCO_BASE=c:/POCOpro
RemoteGenNGd RemotingServiceGen.xml /compiler=msvc /define=POCO_BASE=c:/POCOpro /define=PROJECT_ROOT=../../

RemoteGenNGd RemotingServiceGen.xml /compiler=msvc /define=POCO_BASE=c:/POCOpro /define=PROJECT_ROOT=../../ /define=OUTPUT_PATH=./

##########################################################
# LUNUX: Invoke this command from terminal ###############

RemoteGenNG --compiler=gcc --define=POCO_BASE=$POCO_BASE --osp EmergencyCallRemotingDef.xml
RemoteGenNG --compiler=gcc --define=POCO_BASE=$POCO_BASE --osp EmergencyCallRemoting.xml