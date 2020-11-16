1.Run the commands
    mkdir -p ~/catkin_ws/src
    cd ~/catkin_ws/
    catkin_make

2. Download from github.com/titan-rover/base_station
   Open up the files until you the folder called src
   Open up the folder src
   Transfer the folder simple_test to your newly created src folder in catkin_ws
   run the command catkin_make again 
3. Open up terminal on your desktop
   right click on your desktop and click on open terminal
   run the code:
     roscore

4. Now go back to the folder catkin_make
   Open a terminal there
   run the code:
     source devel/setup.bash
   after that is done run the code:
     cd /src
     roslaunch simple_test ros9-15run.launch
