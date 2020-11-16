import React, { Component } from "react";
import Card from "react-bootstrap/Card";
import Button from "react-bootstrap/Button";
import Form from "react-bootstrap/Form";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";

class GPS extends Component {
  constructor(props) {
    super(props);
    this.state = {
      autonomousCoordinates: ["input"],
      lat: [0],
      lon: [0],
      degreesLat: [0],
      degreesLon: [0],
      minsLat: [0],
      minsLon: [0],
      secsLat: [0],
      secsLon: [0],
      convertedDegreesLat: [0],
      convertedDegreesLon: [0],
      convertedMinsLat: [0],
      convertedMinsLon: [0],
      convertedSecsLat: [0],
      convertedSecsLon: [0],
      gpsArraySize: 1,
    };
  }

  addAutonomousCoordinates = () => {
    this.setState({
      autonomousCoordinates: [...this.state.autonomousCoordinates, "input"],
      lat: [...this.state.lat, 0],
      lon: [...this.state.lon, 0],
      degreesLat: [...this.state.degreesLat, 0],
      degreesLon: [...this.state.degreesLon, 0],
      minsLat: [...this.state.minsLat, 0],
      minsLon: [...this.state.minsLon, 0],
      secsLat: [...this.state.secsLat, 0],
      secsLon: [...this.state.secsLon, 0],
      convertedDegreesLat: [...this.state.convertedDegreesLat, 0],
      convertedDegreesLon: [...this.state.convertedDegreesLon, 0],
      convertedMinsLat: [...this.state.convertedMinsLat, 0],
      convertedMinsLon: [...this.state.convertedMinsLon, 0],
      convertedSecsLat: [...this.state.convertedSecsLat, 0],
      convertedSecsLon: [...this.state.convertedSecsLon, 0],
      gpsArraySize: this.state.gpsArraySize + 1,
    });
  };

  removeAutonomousCoordinates = () => {
    const removeAmount = (this.state.gpsArraySize === 1) ? 0 : 1;
    const newArraySize = this.state.gpsArraySize - removeAmount;
    this.setState({
      autonomousCoordinates: this.state.autonomousCoordinates.slice(0, newArraySize),
      lat: this.state.lat.slice(0, newArraySize),
      lon: this.state.lon.slice(0, newArraySize),
      degreesLat: this.state.degreesLat.slice(0, newArraySize),
      degreesLon: this.state.degreesLon.slice(0, newArraySize),
      minsLat: this.state.minsLat.slice(0, newArraySize),
      minsLon: this.state.minsLon.slice(0, newArraySize),
      secsLat: this.state.secsLat.slice(0, newArraySize),
      secsLon: this.state.secsLon.slice(0, newArraySize),
      convertedDegreesLat: this.state.convertedDegreesLat.slice(0, newArraySize),
      convertedDegreesLon: this.state.convertedDegreesLon.slice(0, newArraySize),
      convertedMinsLat: this.state.convertedMinsLat.slice(0, newArraySize),
      convertedMinsLon: this.state.convertedMinsLon.slice(0, newArraySize),
      convertedSecsLat: this.state.convertedSecsLat.slice(0, newArraySize),
      convertedSecsLon: this.state.convertedSecsLon.slice(0, newArraySize),
      gpsArraySize: newArraySize,
    })
  }

  convertLatToDMS(event, index) {
    const updatedLat = [...this.state.lat];
    const updatedDegrees = [...this.state.degreesLat];
    const updatedMins = [...this.state.minsLat];
    const updatedSecs = [...this.state.secsLat];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLat];
    const updatedConvertedMins = [...this.state.convertedMinsLat];
    const updatedConvertedSecs = [...this.state.convertedSecsLat];
    let remainder = event.target.value;
    updatedLat[index] = remainder;
    const degree = Math.floor(remainder);
    updatedDegrees[index] = degree;
    updatedConvertedDegrees[index] = degree;
    remainder -= degree;
    const min = Math.floor(remainder * 60);
    updatedMins[index] = min;
    updatedConvertedMins[index] = parseFloat(updatedMins[index]) / 60;
    remainder -= min / 60;
    const sec = remainder * 3600;
    updatedSecs[index] = sec;
    updatedConvertedSecs[index] = parseFloat(updatedSecs[index]) / 3600;
    this.setState({
      lat: updatedLat,
      degreesLat: updatedDegrees,
      minsLat: updatedMins,
      secsLat: updatedSecs,
      convertedDegreesLat: updatedConvertedDegrees,
      convertedMinsLat: updatedConvertedMins,
      convertedSecsLat: updatedConvertedSecs,
    });
  }

  convertDegreesToLat(event, index) {
    const updatedLat = [...this.state.lat];
    const updatedDegrees = [...this.state.degreesLat];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLat];
    const updatedConvertedMins = [...this.state.convertedMinsLat];
    const updatedConvertedSecs = [...this.state.convertedSecsLat];
    const calculatedDegree = parseFloat(event.target.value);
    updatedDegrees[index] = event.target.value;
    updatedConvertedDegrees[index] = calculatedDegree;
    updatedLat[index] = updatedConvertedDegrees[index] + updatedConvertedMins[index] + updatedConvertedSecs[index];
    this.setState({
      lat: updatedLat,
      convertedDegreesLat: updatedConvertedDegrees,
      degreesLat: updatedDegrees,
    });
  }

  convertMinutesToLat(event, index) {
    const updatedLat = [...this.state.lat];
    const updatedMins = [...this.state.minsLat];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLat];
    const updatedConvertedMins = [...this.state.convertedMinsLat];
    const updatedConvertedSecs = [...this.state.convertedSecsLat];
    const calculatedMinutes = parseFloat(event.target.value) / 60;
    updatedMins[index] = event.target.value;
    updatedConvertedMins[index] = calculatedMinutes;
    updatedLat[index] = updatedConvertedDegrees[index] + updatedConvertedMins[index] + updatedConvertedSecs[index];
    this.setState({
      lat: updatedLat,
      convertedMinsLat: updatedConvertedMins,
      minsLat: updatedMins,
    });
  }

  convertSecondsToLat(event, index) {
    const updatedLat = [...this.state.lat];
    const updatedSecs = [...this.state.secsLat];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLat];
    const updatedConvertedMins = [...this.state.convertedMinsLat];
    const updatedConvertedSecs = [...this.state.convertedSecsLat];
    const calculatedSeconds = parseFloat(event.target.value) / 3600;
    updatedSecs[index] = event.target.value;
    updatedConvertedSecs[index] = calculatedSeconds;
    updatedLat[index] = updatedConvertedDegrees[index] + updatedConvertedMins[index] + updatedConvertedSecs[index];
    this.setState({
      lat: updatedLat,
      convertedSecsLat: updatedConvertedSecs,
      secsLat: updatedSecs,
    });
  }

  convertLonToDMS(event, index) {
    const updatedLon = [...this.state.lon];
    const updatedDegrees = [...this.state.degreesLon];
    const updatedMins = [...this.state.minsLon];
    const updatedSecs = [...this.state.secsLon];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLon];
    const updatedConvertedMins = [...this.state.convertedMinsLon];
    const updatedConvertedSecs = [...this.state.convertedSecsLon];
    let remainder = event.target.value;
    updatedLon[index] = remainder;
    const degree = Math.floor(remainder);
    updatedDegrees[index] = degree;
    updatedConvertedDegrees[index] = degree;
    remainder -= degree;
    const min = Math.floor(remainder * 60);
    updatedMins[index] = min;
    updatedConvertedMins[index] = parseFloat(updatedMins[index]) / 60;
    remainder -= min / 60;
    const sec = remainder * 3600;
    updatedSecs[index] = sec;
    updatedConvertedSecs[index] = parseFloat(updatedSecs[index]) / 3600;
    this.setState({
      lon: updatedLon,
      degreesLon: updatedDegrees,
      minsLon: updatedMins,
      secsLon: updatedSecs,
      convertedDegreesLon: updatedConvertedDegrees,
      convertedMinsLon: updatedConvertedMins,
      convertedSecsLon: updatedConvertedSecs,
    });
  }

  convertDegreesToLon(event, index) {
    const updatedLon = [...this.state.lon];
    const updatedDegrees = [...this.state.degreesLon];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLon];
    const updatedConvertedMins = [...this.state.convertedMinsLon];
    const updatedConvertedSecs = [...this.state.convertedSecsLon];
    const calculatedDegree = parseFloat(event.target.value);
    updatedDegrees[index] = event.target.value;
    updatedConvertedDegrees[index] = calculatedDegree;
    updatedLon[index] = updatedConvertedDegrees[index] + updatedConvertedMins[index] + updatedConvertedSecs[index];
    this.setState({
      lon: updatedLon,
      convertedDegreesLon: updatedConvertedDegrees,
      degreesLon: updatedDegrees,
    });
  }

  convertMinutesToLon(event, index) {
    const updatedLon = [...this.state.lon];
    const updatedMins = [...this.state.minsLon];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLon];
    const updatedConvertedMins = [...this.state.convertedMinsLon];
    const updatedConvertedSecs = [...this.state.convertedSecsLon];
    const calculatedMinutes = parseFloat(event.target.value) / 60;
    updatedMins[index] = event.target.value;
    updatedConvertedMins[index] = calculatedMinutes;
    updatedLon[index] = updatedConvertedDegrees[index] + updatedConvertedMins[index] + updatedConvertedSecs[index];
    this.setState({
      lon: updatedLon,
      convertedMinsLon: updatedConvertedMins,
      minsLon: updatedMins,
    });
  }

  convertSecondsToLon(event, index) {
    const updatedLon = [...this.state.lon];
    const updatedSecs = [...this.state.secsLon];
    const updatedConvertedDegrees = [...this.state.convertedDegreesLon];
    const updatedConvertedMins = [...this.state.convertedMinsLon];
    const updatedConvertedSecs = [...this.state.convertedSecsLon];
    const calculatedSeconds = parseFloat(event.target.value) / 3600;
    updatedSecs[index] = event.target.value;
    updatedConvertedSecs[index] = calculatedSeconds;
    updatedLon[index] = updatedConvertedDegrees[index] + updatedConvertedMins[index] + updatedConvertedSecs[index];
    this.setState({
      lon: updatedLon,
      convertedSecsLon: updatedConvertedSecs,
      secsLon: updatedSecs,
    });
  }

  submitGPSInputs() {
  }

  render() {
    const {lat, lon, degreesLat, degreesLon, minsLat, minsLon, secsLat, secsLon} = this.state;
    return (
      <Card className="text-center">
        <Card.Header>Autonomous GPS Coordinates</Card.Header>
        <Card.Body>
      <Form>
      <Form.Group controlId="formGroupEmail">
        <Row style={{justifyContent: 'space-around'}}>
          {this.state.autonomousCoordinates.map((input, index) => (
          <Row>
            <Col>
            <Col>
            GPS Input: {index+1}
            </Col>
            <Row>
          <Col>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Latitude</span>
              </div>
              <Form.Control type="input" 
                value={lat[index]} 
                onChange={(event) => {this.convertLatToDMS(event, index);}}
                />
            </div>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Degrees</span>
              </div>
              <Form.Control type="input"
                value={degreesLat[index]}
                onChange={(event) => {this.convertDegreesToLat(event, index);}}
                />
            </div>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Minutes</span>
              </div>
              <Form.Control type="input"
                value={minsLat[index]}
                onChange={(event) => {this.convertMinutesToLat(event, index);}}
                />
            </div>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Seconds</span>
              </div>
            <Form.Control type="input"
              value={secsLat[index]}
              onChange={(event) => {this.convertSecondsToLat(event, index);}}
              />
            </div>
          </Col>          
          <Col>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Longitude</span>
              </div>
              <Form.Control type="input" 
                value={lon[index]} 
                onChange={(event) => {this.convertLonToDMS(event, index);}}
                />
            </div>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Degrees</span>
              </div>
              <Form.Control type="input"
                value={degreesLon[index]}
                onChange={(event) => {this.convertDegreesToLon(event, index);}}
                />
            </div>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Minutes</span>
              </div>
              <Form.Control type="input"
                value={minsLon[index]}
                onChange={(event) => {this.convertMinutesToLon(event, index);}}
                />
            </div>
            <div class="input-group mb-3">
              <div class="input-group-prepend">
                <span class="input-group-text" id="basic-addon1">Seconds</span>
              </div>
            <Form.Control type="input"
              value={secsLon[index]}
              onChange={(event) => {this.convertSecondsToLon(event, index);}}
              />
            </div>
          </Col>
          </Row>
          </Col>
          </Row>
          ))}
        </Row>
      </Form.Group>
    </Form>  
    <Button type="button" variant="primary" onClick={this.addAutonomousCoordinates}>
      Add 
    </Button>
    <Button type="button" variant="primary" onClick={this.removeAutonomousCoordinates}>
      Remove 
    </Button>
    <Button type="submit" variant="primary" onClick={this.submitGPSInputs}>
      Submit
    </Button> 
  </Card.Body>
  </Card>
  );
  }
}

export default GPS;
