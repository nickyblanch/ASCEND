<template>
  <v-theme-provider :theme="dark ? 'dark' : 'light'">
    <v-app style="height: 100vh">
      <v-app-bar
        title="University of Arizona ASCEND Data Visualization"
        color="primary"
        elevation="2"
        class="text-white"
      >
        <template v-slot:append>
          <v-btn icon="mdi-theme-light-dark" @click="dark = !dark" />
        </template>
      </v-app-bar>
      <v-main class="h-100">
        <PageWrapper />
      </v-main>
    </v-app>
  </v-theme-provider>
</template>

<script setup>
import PageWrapper from "@/components/PageWrapper.vue";
import { ref } from "vue";

const dark = ref(false);
</script>

<style>
html {
  overflow: hidden !important;
  scrollbar-width: none;
  -ms-overflow-style: none;
}

html::-webkit-scrollbar {
  width: 0;
  height: 0;
}
</style>
