import React, { Component } from "react";
import HighchartsReact from "highcharts-react-official";
import Highcharts from "highcharts";
import DarkUnica from "highcharts/themes/dark-unica";

DarkUnica(Highcharts);

class TemperatureSensor extends Component {
  componentWillReceiveProps() {
    this.setState({
      chartOptions: {
        title: {
          text: "Temperature Sensor"
        },

        chart: {
          type: "spline",
        },

        xAxis: {
          type: "datetime",
          visible: false
        },
        //Each Series requires its own yAxis
        yAxis: [
          { 
            min: -40, max: 125,
            title: {
              text: "Degrees"
            }
          },
          {
            min: -40, max: 125,
            visible: false
          },
          {
            min: -40, max: 125,
            visible: false
          },
          {
            min: -40, max: 125,
            visible: false
          }
        ],
        series: [
          { yAxis: 0, name: "Ambient (C)", data: this.props.temperature.ambientC, color: '#2f7ed8' },
          { yAxis: 1, name: "Ambient (F)", data: this.props.temperature.ambientF, color: '#fef65b' },
          { yAxis: 2, name: "Object (C)", data: this.props.temperature.objectC, color: '#8bbc21' },
          { yAxis: 3, name: "Object (F)", data: this.props.temperature.objectF, color: '#910000' }
        ]
      }
    });
  }

  constructor(props) {
    super(props);

    this.state = {
      count: 0,
      chartOptions: {}
    };
  }

  render() {
    return (
      <div>
        <HighchartsReact
          ref='chart'
          highcharts={Highcharts}
          options={this.state.chartOptions}
        />
      </div>
    );
  }
}

export default TemperatureSensor;
