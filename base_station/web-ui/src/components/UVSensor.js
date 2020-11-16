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
          text: "UV Sensor"
        },
        chart: {
          type: "column",
        },

        xAxis: {
          type: "datetime",
          visible: true
        },
        
        yAxis: [
          { 
            min: 0, max: 30,
            title: {
              text: ""
            },
            labels: {
              format: "{value}mV"
            },
            opposite: true
          }
        ],
        series: [
          { yAxis: 0, name: "UV Intensity", data: [this.props.uv_intensity], color: '#2f7ed8' },
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
