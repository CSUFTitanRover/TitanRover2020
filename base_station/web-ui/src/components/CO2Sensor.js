import React, { Component } from "react";
import HighchartsReact from "highcharts-react-official";
import Highcharts from "highcharts";
import DarkUnica from "highcharts/themes/dark-unica";

DarkUnica(Highcharts);

class CO2Sensor extends Component {
  componentWillReceiveProps() {
    this.setState({
      chartOptions: {
        chart: {
          type: "column",
        },

        title: {
          text: "CO2 Sensor"
        },

        xAxis: {
          type: "datetime",
          visible: true
        },
        
        yAxis: [
          { 
            min: 0, max: 5000,
            title: {
              // text: "CO2 Sensor"
              text: ""
            },
            opposite: true
          }
        ],
        series: [
          { yAxis: 0, name: "ppm", data: [this.props.ppm], color: '#2f7ed8' },
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

export default CO2Sensor;
