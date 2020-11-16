import React, { Component } from "react";
import HighchartsReact from "highcharts-react-official";
import Highcharts from "highcharts";
import DarkUnica from "highcharts/themes/dark-unica";

DarkUnica(Highcharts);

class HumiditySensor extends Component {
  componentWillReceiveProps() {
    this.setState({
      chartOptions: {

        title: {
          text: "Humidity Sensor"
        },

        xAxis: {
          categories: ["Humidity","Temperature"],
          visible: true
        },
        
        yAxis: [
          { 
            min: 20, max: 90,
            title: {
              // text: "Humidity"
              text: null
            },
            labels: {
              format: "{value}%"
            }
          },
          {
            min: 0, max: 50,
            title: {
              // text: "Temperature"
              text: null
            },
            opposite: true
          },
        ],
        series: [
          { yAxis: 0, type:"column", name: "Humidity", data: [this.props.humidity], color: '#2f7ed8' },
          { yAxis: 1, type:"column", name: "Humidity Temp", data: [this.props.humidity_temperature], color: '#fd873a' }
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

export default HumiditySensor;
