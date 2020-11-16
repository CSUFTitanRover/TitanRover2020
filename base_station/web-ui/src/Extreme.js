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
import IMU from "./components/IMU";
import MapTile from "./components/MapTile";
import Compass from "./components/Compass";
import UltraSonicSensor from "./components/UltrasonicSensor";
import GPS from "./components/GPS";
import AntennaSignal from "./components/AntennaSignal";
import MobilityCurrentDraw from "./components/MobilityCurrentDraw";
import ROSLIB from "roslib";

class Extreme extends Component {
  constructor(props) {
    super(props);

    this.state = {
      imu: {
        rotation: null,
        heading: null
      },
      gps: {
        currentPosition: [null, null]
      },
      antenna: {
        decibals: null
      },
      ultrasonic: {
        distance: null
      },

      roboclaw: {
        a: {
          amps: null
        },
        b: {
          amps: null
        }
      }
    };

    this.connectRosBridge("ws://localhost:9090");
    this.createListeners();
    this.createPublishers();
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
    if (this.antenna_listener) {
      this.antenna_listener.subscribe(m => {
        this.setState({
          decibels: m.signal_strength
        });
      });
    }

    if (this.gps_listener) {
      this.gps_listener.subscribe(m => {
        this.setState({
          latitude: m.roverLat,
          longitude: m.roverLon
        });
      });
    }

    if (this.imu_listener) {
      this.imu_listener.subscribe(m => {
        this.setState({
          yaw: m.yaw,
          pitch: m.pitch,
          roll: m.roll
        });
      });
    }

    if (this.mobility_listener) {
      this.mobility_listener.subscribe(m => {
        this.setState({
          amperage: m.current_draw
        });
      });
    }

    if (this.ultrasonic_listener) {
      this.ultrasonic_listener.subscribe(m => {
        this.setState({
          distance: m.max_distance
        });
      });
    }
  }

  createPublishers() {
    try {
      this.gps_publisher = new ROSLIB.Topic({
        ros: this.ros,
        name: "/gnss",
        messageType: "gnss/gps"
      });
    } catch (e) {
      //Fail to create ROS object
      this.setState({
        status: "Error"
      });
      console.log("Error: Failed to create ros publisher");
    }
  }

  createListeners() {
    try {
      this.antenna_listener = new ROSLIB.Topic({
        ros: this.ros,
        name: "/antenna",
        messageType: "fake_sensor_test/antenna"
      });

      this.gps_listener = new ROSLIB.Topic({
        ros: this.ros,
        name: "/gnss",
        messageType: "gnss/gps"
      });

      this.imu_listener = new ROSLIB.Topic({
        ros: this.ros,
        name: "/imu",
        messageType: "imu/axes"
      });

      this.mobility_listener = new ROSLIB.Topic({
        ros: this.ros,
        name: "/mobility",
        messageType: "fake_sensor_test/mobility"
      });

      this.ultrasonic_listener = new ROSLIB.Topic({
        ros: this.ros,
        name: "/ultrasonic",
        messageType: "fake_sensor_test/ultrasonic"
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
    return (
      <Container fluid={true} className="pt-2">
        <Row>
          <Col>
            <IMU rotation={this.state.imu.rotation} />
          </Col>
          <Col>
            <MapTile currentPosition={this.state.gps.currentPosition} />
          </Col>
          <Col>
            <Compass heading={this.state.imu.heading} />
          </Col>
          <Col>
            <UltraSonicSensor distance={this.state.ultrasonic.distance} />
          </Col>
        </Row>
        <ToastContainer autoClose={3000} />
      </Container>
    );
  }
}

export default Extreme;
