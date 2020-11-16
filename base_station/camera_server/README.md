# Folder Structure
* Main Directory: Contains the config file and necessary headers for networking
* Client: Contains code for interfacing with the cameras
* Server: Contains code for running the UI
# Compile
* Client: enter the client directory and run `make`.
* Server:
    1. Open QtCreator.
    2. Press Ctrl+O (File -> Open Project).
    3. Navigate to the server folder.
    4. Select the uicamera.pro file.
    5. Press Ctrl+B (Build -> Build).

# Example Usage
Start the server first using the instructions above.

To start the client and connect to the server
```Bash 
./client camera1 127.0.0.1 12345 
```

Once the camera has connected to the server it will populate the `select camera` dropdown in the upper left corner of the GUI.

# Usage
* Client: The compiled file `client` accepts the following arguments 
    1. \<cameraId\> - camera1 
    2. \<serverIp\> - 127.0.0.1
    3. \<serverPort\> - 12345
* Server:
    1. While inside the opened project in QtCreator..
    5. Press Ctrl+R (Build -> Run).

# Selecting your camera
In the terminal type `ls /dev`.  The available cameras will be prefixed with video* and followed by an integer value starting at 0.  In the config.json file, this integer value can be set in the `device` attribute of a camera.  Note that each camera adds two video*'s to /dev.  Use the even values only (camera1 -> 0, camera1 -> 2, etc).

# Changing settings in config.json
* connPort - TCP port used by the server.
* configurations - Defined as an object, keys represent the names of the camera group, and the value is an array of up to 4 strings representing the cameraId's to use in the configuration. 
* devices - Object containing the individual camera settings
* device - This string is passed to openCV to open the camera or stream.  If using /dev/video0, use "0".
* quality - Array holding 3 elements.  Key 0 -> low quality, 1 -> medium quality, 2 -> high quality
* jpgQuality - integer ranging from 0 to 100, setting used by openCV jpeg compression.  0 is worst, 100 is best.
* fps - frames per second.  
* resolutionX - integer value for resolution on x-axis.  Actual results depend on camera.
* resolutionY - integer value for resolution on y-axis.  Actual results depend on camera.