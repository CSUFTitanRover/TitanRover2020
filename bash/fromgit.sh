#!/bin/bash

#NOTE: systemd service to start this at boot is called roverui.service
#TODO: update script and accompanying js file to write the PID to /tmp and have this bash script check it as to not create multiple instances

cd /home/$HOSTNAME
mkdir gittemp #make a folder, clone the given repo into it
cd gittemp
git clone https://github.com/titan-rover/base_station.git
SRC="/home/$HOSTNAME/catkin_ws/src" #set SRC var to path of local SRC
GIT="/home/$HOSTNAME/gittemp/base_station/src" #make temp path to temp folder
DIFF=$(diff -r $GIT $SRC) #compare contents of local src folder to git clone using DIFF

echo "Finding difference between GIT repo and local SRC ..."
echo $DIFF 
if [ "$DIFF" != "" ] 
then
    printf "\n"; echo "$(tput bel) $(tput setaf 2)---Changes in directory contents found.---$(tput sgr0)"; printf "\n";
else
    printf "\n"; echo "$(tput setaf 3)---No changes in directories found.---$(tput sgr0)"; printf "\n";
fi

while true; do
        read -p "Replace local SRC with GIT (Y\N)? $(tput setaf 1) warning this will overwrite current SRC contents $(tput sgr0): " yn
        case $yn in
                [Yy]* ) rm -R /home/$HOSTNAME/catkin_ws/src;mv -T $GIT $SRC; rm -R /home/$HOSTNAME/gittemp/; printf "\n$(tput setaf 3)---Initiating catkin_make---\n$(tput sgr0)";  cd /home/gordon/catkin_ws; source devel/setup.bash; catkin_make;break;;
                [Nn]* ) echo "exiting.";rm -R /home/$HOSTNAME/gittemp;exit;; #if no then remove the temp GIT clone folder
                *) echo "Please answer Y or N.";;
        esac
done


 
