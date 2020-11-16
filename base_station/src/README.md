# How to use this src folder
1. Copy the contents of this folder to your catkin workspace src folder.
2. Run catkin_make in the catkin workspace root directory.
    ```console
    # catkin_make
    ```

# How to use fake_sensor_test

1. Source your catkin workspace
    ```console
    # source [your catkin workspace]/devel/setup.bash
    # source ~/catkin_ws/devel/setup.bash
    ```
2. Start ros
    ```console
    # roscore
    ```
3. Start a test from the terminal 
    ```console
    # rosrun fake_sensor_test [filename]
    # rosrun fake_sensor_test mobility.py  
    ```
4. Useful commands
    ```console
    # rosnode info /gnss
    # rostopic list
    # rostopic echo /gnss
    ```

# How to start rosbridge

1. Start the rosbridge_server 
    ```console
    # roslaunch rosbridge_server rosbridge_websocket.launch
    ```