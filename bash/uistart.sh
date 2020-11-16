#!/usr/bin/env bash
NODEPATH="$HOME/$HOSTNAME/Programs/UI_Data"
GREP=$(ps a | grep "Launch.js" | grep -v "grep")
BRIDGE=$(ps -x | grep "rosbridge_websocket" | grep -v "grep")
#PID=$(ps -e | grep $CAT)
#setPID () {
#    cd /
#    cd tmp
#    echo $$ > rosuiserver
#}
set -x #comment this to see process steps output to terminal
CHECK=$(systemctl is-active roverui.service)
BCHECK=$(systemctl is-active rosbridge.service)
checkBridge () {
    if [[ "$BRIDGE" == "" ]]
    then
        WINDOW1=$(zenity --question --text "Rosbridge inactive, start?" --no-wrap --ok-label "Okay!" --cancel-label "No thanks!"; echo $?)
        if [ $WINDOW1 == 0 ]
        then 
            printf "\n"; echo "$(tput setaf 3)Starting ROSbridge ...$(tput sgr0)";cd $HOME/catkin_ws ; source devel/setup.bash; nohup roslaunch rosbridge_server rosbridge_websocket.launch &
            printf "\n"; echo "exiting...";break;
        fi
    else
        printf "\n"; echo "ROSbridge Running"; break;
    fi
}

checkBridge
if [[ "$CHECK" != "active" ]] && [[ "$GREP" == "" ]]
then
    WINDOW2=$(zenity --question --text "RoverUI daemon inactive, start service?" --no-wrap --ok-label "Yes" --cancel-label "No"; echo $?)
    if [ $WINDOW2 == 0 ]
    then
        printf "\n"; echo "$(tput setaf 3)Starting server...$(tput srgr0)"; source $HOME/.nvm/nvm.sh; cd /; cd home/$HOSTNAME/Programs/UI_Data ;nvm use node; node Launch.js & xdg-open http://localhost:9000 ; exit;
    elif [ $WINDOW2 == 1 ]
    then
        printf "\n"; echo "exiting...";exit;
    fi
else
    printf "\n"; echo "JS server running";xdg-open http://localhost:9000; exit;
fi
