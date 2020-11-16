import React, { Component } from "react";
import Card from "react-bootstrap/Card";

class Compass extends Component {
  constructor(props) {
    super(props);

    this.state = {};
  }

  render() {
    return (
      <Card className="text-center" bg="danger">
        <Card.Header>Compass Component</Card.Header>
        <Card.Body>
          <Card.Title>Special title treatment</Card.Title>
          <Card.Text>
            With supporting text below as a natural lead-in to additional
            content.
          </Card.Text>
        </Card.Body>
      </Card>
    );
  }
}

export default Compass;
