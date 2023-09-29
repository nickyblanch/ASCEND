<template>
  <v-card class="h-100">
    <canvas id="scatterChart"></canvas>
  </v-card>
</template>

<script>
import { Chart } from "chart.js/auto";
// import { Scatter } from "vue-chartjs";
// import * as chartConfig from "./chartConfig.js";

// ChartJS.register(LinearScale, PointElement, LineElement, Tooltip, Legend);

export default {
  name: "App",
  props: ["passedData", "xAxis", "yAxis", "line"],
  data() {
    return {
      chart: undefined,
    };
  },
  mounted() {
    // console.log(this.options);
    Chart.defaults.font.size = 20;
    const ctx = document.getElementById("scatterChart");
    const chartObj = new Chart(ctx, this.config);
    // this.chart = new Chart(ctx, this.config);
    Object.seal(chartObj);
    this.chart = chartObj;
  },
  watch: {
    config(newConfig) {
      const ctx = document.getElementById("scatterChart");
      // this.chart.destroy();
      // this.chart = new Chart(ctx, newConfig);
    },
    line() {
      console.log(this.line);
      this.chart.data = this.chartData;
      this.chart.update();
    },
    passedData: {
      handler() {
        // console.log("Hello from watch (passedData)");
        this.chart.options = this.options;
        this.chart.data.datasets[0].label = this.yAxis + " vs " + this.xAxis;
        this.chart.update();
      },
      deep: true,
    },
  },
  computed: {
    chartData() {
      return {
        datasets: [
          {
            label: this.yAxis + " vs " + this.xAxis,
            fill: false,
            borderColor: "#AB2520",
            backgroundColor: "#AB2520",
            showLine: this.line,
            tension: 0.1,

            data: this.passedData,
          },
        ],
      };
    },
    options() {
      return {
        animation: true,
        responsive: true,
        maintainAspectRatio: false,
        plugins: {
          tooltip: {
            enabled: true,
          },
        },
        scales: {
          x: {
            title: {
              display: true,
              text: this.xAxis,
              size: 20,
            },
            grid: {
              color: "grey",
            },
          },
          y: {
            title: {
              display: true,
              text: this.yAxis,
            },
            grid: {
              color: "grey",
            },
          },
        },
        elements: {
          point: {
            radius: 1,
          },
        },
      };
    },
    config() {
      return {
        type: "scatter",
        data: this.chartData,
        options: this.options,
      };
    },
  },
};
</script>