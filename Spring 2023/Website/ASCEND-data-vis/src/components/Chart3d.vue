<template>
  <v-card class="h-100">
    <div id="scatter3D" class="h-100" />
  </v-card>
</template>

<script setup>
// import "plotly.js-dist-min";
import { onMounted, defineProps, watch, computed } from "vue";

const p = defineProps(["passedData", "xAxis", "yAxis", "line", "zAxis"]);

const plotData = computed(() => {
  return p.zAxis
    ? [
        {
          x: p.passedData.x,
          y: p.passedData.y,
          z: p.passedData.z,

          mode: p.line ? "lines" : "markers",
          marker: {
            size: 4,
            opacity: 1.0,
            color: p.passedData.minutes,
            colorscale: "Picnic",
          },
          line: {
            width: 4,
            opacity: 0.8,
            color: p.passedData.minutes,
            colorscale: "Picnic",
          },
          type: "scatter3d",
        },
      ]
    : [
        {
          x: p.passedData.x,
          y: p.passedData.y,

          mode: p.line ? "lines" : "markers",
          marker: {
            size: 4,
            opacity: 0.8,
            color: p.passedData.minutes,
            colorscale: "Picnic",
          },
          line: {
            // color: p.passedData.minutes,
            // colorscale: "Picnic",
          },
          type: "scatter",
        },
      ];
});

const layout = computed(() => {
  return {
    plot_bgcolor: "rgba(0,0,0,0)",
    paper_bgcolor: "rgba(0,0,0,0)",
    title: {
      text: p.yAxis + " vs. " + p.xAxis + (p.zAxis ? " vs. " + p.zAxis : ""),
      font: {
        color: "#AB2520",
        family: "Courier New, monospace",
        size: 36,
      },
      xref: "paper",
      x: 0.05,
    },
  };
});

onMounted(() => {
  Plotly.newPlot("scatter3D", plotData.value, layout.value);
});
watch(
  () => [p.zAxis],
  () => {
    Plotly.newPlot("scatter3D", plotData.value, layout.value);
  }
);

watch(
  () => [p.passedData, p.line],
  (newData) => {
    // Plotly.animate("scatter3D", plotData.value, layout);
    // Plotly.react("scatter3D", plotData.value, layout);
    if (p.zAxis) {
      Plotly.react("scatter3D", plotData.value, layout.value);
    } else {
      Plotly.animate(
        "scatter3D",
        {
          data: plotData.value,
          layout: layout.value,
        },
        {
          transition: {
            duration: 500,
            easing: "cubic-in-out",
          },
          frame: {
            duration: 500,
            redraw: false,
          },
        }
      ).then(() => {
        Plotly.react("scatter3D", plotData.value, layout.value);
      });
    }
  }
);
</script>
