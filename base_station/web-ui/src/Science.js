// React imports
import React, { Component } from "react";

// Bootstrap imports
import "./darkly-bootstrap.min.css";
import Container from "react-bootstrap/Container";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";

// Toastify imports
import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";

// Custom components
import MapTile from "./components/MapTile";
import Compass from "./components/Compass";
import UVSensor from "./components/UVSensor";
import TemperatureSensor from "./components/TemperatureSensor";
import HumiditySensor from "./components/HumiditySensor";
import ROSLIB from "roslib";
import CO2Sensor from "./components/CO2Sensor";

class Science extends Component {
  constructor(props) {
    super(props);

    this.state = {
      temperature: {
        ambientC: Array(20).fill(null),
        ambientF: Array(20).fill(null),
        objectC: Array(20).fill(null),
        objectF: Array(20).fill(null)
      },

      co2: {ppm: null},

      uv: {
        uv_visible: null,
        uv_infared: null,
        uv_index: null
      },

      humidity: {
        humidity_temperature: null,
        humidity: null
      }
    };

    this.connectRosBridge("ws://192.168.1.103:9090");
    this.createListeners();
    //this.createPublishers();
    this.registerCallbacks();
  }

  registerCallbacks() {
    // Register ros callbacks
    this.ros.on("connection", () => {
      this.setState({
        status: "Connected"
      });
    });
    this.ros.on("error", error => {
      this.setState({
        status: "Error"
      });
    });
    this.ros.on("closed", () => {
      this.setState({
        status: "Closed"
      });
    });

    // Register listener callbacks
    if (this.sensor_listener) {
      this.sensor_listener.subscribe(m => {
          const hist0 = this.state.temperature.ambientC.slice(1);
          const hist1 = this.state.temperature.ambientF.slice(1);
          const hist2 = this.state.temperature.objectC.slice(1);
          const hist3 = this.state.temperature.objectF.slice(1);
        this.setState({
          temperature: {
             ambientC: hist0.concat([m.ambientC]),
             ambientF: hist1.concat([m.ambientF]),
             objectC: hist2.concat([m.objectC]),
             objectF: hist3.concat([m.objectF])
          },
          co2: {ppm: m.co2_ppm},

          uv: {
            uv_intensity: m.uv_intensity
            //uv_visible: m.uv_visible,
            //uv_infared: m.uv_infared,
            //uv_index: m.uv_index
          },

          humidity: {
            humidity_temperature: m.humidity_temperature,
            humidity: m.humidity
          }
        });
      });
    }
  }

  // createPublishers() {
  //   try {
  //     this.gps_publisher = new ROSLIB.Topic({
  //       ros: this.ros,
  //       name: "/gnss",
  //       messageType: "gnss/gps"
  //     });
  //   } catch (e) {
  //     //Fail to create ROS object
  //     this.setState({
  //       status: "Error"
  //     });
  //     console.log("Error: Failed to create ros publisher");
  //   }
  // }

  createListeners() {
    try {
      this.sensor_listener = new ROSLIB.Topic({
        ros: this.ros,
        name: "/sensors",
        messageType: "science_sensors/sci_msgs"
      });
      
    } catch (e) {
      //Fail to create ROS object
      this.setState({
        status: "Error"
      });
      console.log("Error: Failed to create ros listener");
    }
  }

  connectRosBridge(url) {
    try {
      this.ros = new ROSLIB.Ros({
        url: url //connect to the local host to test on my machine
      });
    } catch (e) {
      //Fail to create ROS object
      this.setState({
        status: "Error"
      });
      console.log("Error: Failed to create ros object");
      return false;
    }
  }

  render() {
    const ambientC = this.state.temperature.ambientC[0];
    const ppm = this.state.co2.ppm;
    const uv_intensity = this.state.uv.uv_intensity;
    const humidity = this.state.humidity.humidity;
    const humidity_temperature = this.state.humidity.humidity_temperature;
    return (
      <Container fluid={true} className="pt-2">
        <Row>
          <Col>
            <TemperatureSensor temperature={this.state.temperature}/>
            <HumiditySensor humidity={humidity} humidity_temperature={humidity_temperature}/>
          </Col>
          <Col>
            <CO2Sensor ppm={ppm}/>
            <UVSensor uv_intensity={uv_intensity}/>
          </Col>
        </Row>
        <ToastContainer autoClose={3000} />
      </Container>
    );
  }
}

export default Science;
