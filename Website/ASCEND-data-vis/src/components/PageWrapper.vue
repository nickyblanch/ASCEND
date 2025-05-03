<template>
  <v-responsive class="pa-4 h-100">
    <v-row class="h-100">
      <!-- x axis picker -->
      <v-col cols="2" class="h-100 py-0 mt-3 d-flex flex-column">
        <v-card v-if="data">
          <v-card-title class="bg-secondary">Select Axes</v-card-title>
          <v-card-text class="mt-4">
            <v-select
              clearable
              v-model="xAxis"
              :items="Object.keys(data)"
              variant="solo"
              label="X Axis"
            />
            <v-select
              clearable
              v-model="yAxis"
              :items="Object.keys(data)"
              variant="solo"
              label="Y Axis"
            />
            <v-select
              clearable
              v-model="zAxis"
              :items="Object.keys(data)"
              variant="solo"
              label="Z Axis"
            />
          </v-card-text>
        </v-card>

        <!-- <v-spacer /> -->

        <v-card class="mt-4" variant="outlined">
          <v-card-title class="">Configuration</v-card-title>
          <v-card-text class="mt-2">
            <row>
              <v-select
                class="mr-4 mb-4"
                v-model="csv_file"
                :items="files"
                label="Select or Upload Data"
                hide-details="auto"
                variant="outlined"
                append-icon="mdi-paperclip"
                @click:append="promptFile"
              />
            </row>

            <v-checkbox label="Lines?" v-model="line" hide-details="auto" />
            <div class="text-subtitle-1">
              Data Smoothing: {{ Math.floor(blurAmount) }}
            </div>
            <v-slider v-model="blurAmount" min="0" max="50" />
            <div class="text-subtitle-1">Derivative: {{ derivative }}</div>
            <v-slider
              min="0"
              max="3"
              step="1"
              v-model="derivative"
              :disabled="!!zAxis"
            />
          </v-card-text>
        </v-card>
      </v-col>

      <v-col cols="10">
        <!-- <ChartScatter
          v-if="xAxis && yAxis && !zAxis"
          :xAxis="xAxis"
          :yAxis="yAxis"
          :passedData="chartData"
          :line="line"
        /> -->
        <Chart3d
          v-if="xAxis && yAxis"
          :xAxis="xAxis"
          :yAxis="yAxis"
          :zAxis="zAxis"
          :passedData="chartData3d"
          :line="line"
        />
      </v-col>
    </v-row>
  </v-responsive>
</template>

<script setup>
import { ref, onMounted, computed, watch } from "vue";
import { blur } from "d3-array";
// import ChartScatter from "@/components/ChartScatter.vue";
import Chart3d from "@/components/Chart3d.vue";

// open the file at Data/Fall_2022.csv and read it into a variable
// called data

const data = ref(null);
const chartData = ref(null);
const xAxis = ref("minutes");
const yAxis = ref(null);
const zAxis = ref(null);
const blurAmount = ref(0);
const derivative = ref(0);

const csv_file = ref("2024_Fall.csv");
const line = ref(false);

const fileInput = document.createElement("input");
fileInput.type = "file";

const files = [
  "2022_Fall.csv",
  "2023_Spring.csv",
  "2023_Fall.csv",
  "2024_Fall.csv",
];

const updateSmoothing = (newVal) => {
  console.log(newVal);
  blurAmount.value = newVal;
};

const unpackText = (text) => {
  xAxis.value = null;
  yAxis.value = null;
  zAxis.value = null;
  const cols = {};
  const rows = text.trim().split("\n");
  const headers = rows[0].split(",");
  for (let i = 1; i < rows.length; i++) {
    const row = rows[i].split(",");
    for (let j = 0; j < row.length; j++) {
      const col = headers[j];
      if (!cols[col]) {
        cols[col] = [];
      }
      cols[col].push(Number(row[j]));
    }
  }
  delete cols[""];
  delete cols[" "];

  // create rows for seconds, minutes, and hours
  if (cols["millis"]) {
    cols["seconds"] = cols["millis"].map((x) => x / 1000);
    cols["minutes"] = cols["millis"].map((x) => x / 1000 / 60);
    cols["hours"] = cols["millis"].map((x) => x / 1000 / 60 / 60);
  }

  xAxis.value == xAxis.value in cols ? xAxis.value : null;
  yAxis.value == yAxis.value in cols ? yAxis.value : null;
  zAxis.value == zAxis.value in cols ? zAxis.value : null;

  data.value = Object.assign(
    { millis: null, seconds: null, minutes: null, hours: null },
    cols
  );

  console.log(cols);
};

fileInput.onchange = (e) => {
  const file = e.target.files[0];
  const reader = new FileReader();
  reader.onload = (e2) => {
    const text = e2.target.result;
    unpackText(text);
  };
  reader.readAsText(file);

  chartData.value = null;
};

const promptFile = () => {
  fileInput.click();
};

const unpackCSV = () => {
  fetch("Data/" + csv_file.value)
    .then((response) => response.text())
    .then(unpackText);

  chartData.value = null;
};

unpackCSV();

const chartData3d = computed(() => {
  if (xAxis.value && yAxis.value) {
    console.log(data);
    const xData = xAxis.value ? data.value[xAxis.value].slice() : [];
    const yData = yAxis.value ? data.value[yAxis.value].slice() : [];
    const zData = zAxis.value ? data.value[zAxis.value].slice() : [];

    blur(xData, blurAmount.value);
    blur(yData, blurAmount.value);
    blur(zData, blurAmount.value);

    //do our derivative if the graph is in 2d
    if (!zAxis.value) {
      for (let i = 0; i < derivative.value; i++) {
        for (let j = 0; j < xData.length - 1; j++) {
          yData[j] = (yData[j + 1] - yData[j]) / (xData[j + 1] - xData[j]);
        }
        yData[yData.length - 1] = yData[yData.length - 2];
      }
    }

    return { x: xData, y: yData, z: zData, minutes: data.value.minutes };
  }
});

function updateChartData() {
  const xData = data.value[xAxis.value].slice();
  const yData = data.value[yAxis.value].slice();

  // console.log(xData);
  blur(xData, blurAmount.value);
  blur(yData, blurAmount.value);

  for (let i = 0; i < derivative.value; i++) {
    for (let j = 0; j < xData.length - 1; j++) {
      yData[j] = (yData[j + 1] - yData[j]) / (xData[j + 1] - xData[j]);
    }
    yData[yData.length - 1] = yData[yData.length - 2];
  }

  for (let i = 0; i < xData.length; i++) {
    chartData.value[i].x = xData[i];
    chartData.value[i].y = yData[i];
  }
}

function createChartData() {
  chartData.value = [];
  for (let i = 0; i < data.value[xAxis.value].length; i++) {
    chartData.value.push({
      x: data.value[xAxis.value][i],
      y: data.value[yAxis.value][i],
    });
  }
}

watch([blurAmount, xAxis, yAxis, derivative], () => {
  if (xAxis.value && yAxis.value) {
    if (chartData.value) updateChartData();
    else createChartData();
  }
});

watch(csv_file, () => {
  console.log("file changed");
  unpackCSV();
});

onMounted(() => {});
</script>
