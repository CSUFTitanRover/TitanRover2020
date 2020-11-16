Web-based UI for CSUF Titan Rover 2020 Competition.

## UI Window responsible for:
- Displaying various data received over ROS
- Input to sends GPS destination coordinates over ROS, where destLat and destLon are both string[] types

## Editting and Testing:
**Requirements:**
- Nodejs installed (nvm recommended - [Link](https://github.com/nvm-sh/nvm#installation-and-update))
**Setup**
- Install dependencies `npm install`
- Start the app `npm start`
- Verify it's working, `Ctrl C` to stop hosting the app

Any time you need to edit and test now just run `npm start`, any changes to the src files will automatically reload the app while it's being hosted

## Deploying the App to the Base Station
**Build the App**
- Run `npm run build` to create the build production of the app, stored in the build directory
- Copy the build directory and the Launch.js file to the Base Station

**Basestation Setup**
- Has node installed
- In the app directory make sure express is installed `npm install express`
- Run `node Launch.js` or use the shortcut on the desktop
- Open browser to localhost:9000

You can edit the port within the Launch.js file