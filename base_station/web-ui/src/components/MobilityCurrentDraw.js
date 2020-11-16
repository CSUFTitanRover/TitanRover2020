import React, { Component } from "react";
import HighchartsReact from "highcharts-react-official";
import Highcharts from "highcharts";
import DarkUnica from "highcharts/themes/dark-unica";
import { toast } from "react-toastify";

DarkUnica(Highcharts);

class MobilityCurrentDraw extends Component {
  componentWillReceiveProps() {
    this.setState({
      chartOptions: {
        series: [
          {
            data: this.props.current_draw
          },
          // {
          //   data: this.props.ampsB
          // }
        ]
      }
    });
  }

  componentDidMount() {
    // setInterval(() => {
    //   let prevDataA = this.state.chartOptions.series[0].data;
    //   let prevDataB = this.state.chartOptions.series[1].data;

    //   if (prevDataA.length > 5) {
    //     prevDataA.shift();
    //   }

    //   if (prevDataB.length > 5) {
    //     prevDataB.shift();
    //   }

    //   prevDataA.push([new Date().getTime(), Math.random() * 20]);
    //   prevDataB.push([new Date().getTime(), Math.random() * 20]);

    //   // if (
    //   //   prevDataA[prevDataA.length - 1][1] < 5 &&
    //   //   !toast.isActive(this.POOR_SIGNAL_ID)
    //   // ) {
    //   //   toast.error("Signal Strength Critical!", {
    //   //     position: toast.POSITION.BOTTOM_RIGHT,
    //   //     toastId: this.POOR_SIGNAL_ID
    //   //   });
    //   // }

    //   this.setState({
    //     chartOptions: {
    //       series: [
    //         {
    //           data: [...prevDataA]
    //         },
    //         {
    //           data: [...prevDataB]
    //         }
    //       ]
    //     }
    //   });
    // }, 1000);
  }

  constructor(props) {
    super(props);

    this.state = {
      count: 0,
      chartOptions: {
        chart: {
          type: "spline"
        },

        time: {
          useUTC: false
        },

        title: {
          text: "Mobility Current Draw"
        },

        xAxis: {
          type: "datetime"
        },

        yAxis: {
          min: 0,
          max: 80,
          title: {
            text: "Value"
          },
          plotLines: [
            {
              value: 0,
              width: 1,
              color: "#808080"
            }
          ],
          // plotBands: [
          //   {
          //     color: "#FFCCCB",
          //     from: 15,
          //     to: 20
          //   }
          // ]
        },

        legend: {
          enabled: true
        },

        plotOptions: {
          series: {
            marker: {
              enabled: false
            }
          }
        },

        series: [
          {
            // zoneAxis: "y",
            // zones: [
            //   { value: 5, color: "red" },
            //   { value: 15, color: "orange" },
            //   { color: "green" }
            // ],
            name: "Current",
            data: []
          }
          // {
            // zoneAxis: "y",
            // zones: [
            //   { value: 5, color: "red" },
            //   { value: 15, color: "blue" },
            //   { color: "green" }
            // ],
          //  name: "Roboclaw B",
          //   data: []
          // }
        ]
      }
    };
  }

  render() {
    return (
      <div>
        <HighchartsReact
          ref={this.chartComponent}
          highcharts={Highcharts}
          options={this.state.chartOptions}
        />
      </div>
    );
  }
}

export default MobilityCurrentDraw;
