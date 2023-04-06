<template>
  <v-card class="h-100">
    <div id="scatter3D" class="h-100" />
  </v-card>
</template>

<script setup>
// import "plotly.js-dist-min";
import { onMounted, defineProps, watch, computed } from "vue";

const p = defineProps(["passedData", "xAxis", "yAxis", "line"]);

const plotData = computed(() => {
  return [
    {
      x: p.passedData.x,
      y: p.passedData.y,
      z: p.passedData.z,

      mode: p.line ? "lines" : "markers",
      marker: {
        size: 4,
        opacity: 0.8,
        color: p.passedData.minutes,
      },
      line: {
        width: 4,
        opacity: 0.8,
        color: p.passedData.minutes,
      },
      type: "scatter3d",
    },
  ];
});

const layout = {
  plot_bgcolor: "rgba(0,0,0,0)",
  paper_bgcolor: "rgba(0,0,0,0)",
};

onMounted(() => {
  Plotly.newPlot("scatter3D", plotData.value, layout);
});

watch(
  () => [p.passedData, p.line],
  (newData) => {
    Plotly.react("scatter3D", plotData.value, layout);
  }
);
</script>