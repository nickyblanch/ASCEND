/**
 * plugins/vuetify.js
 *
 * Framework documentation: https://vuetifyjs.com`
 */

// Styles
import '@mdi/font/css/materialdesignicons.css'
import 'vuetify/styles'

// Composables
import { createVuetify } from 'vuetify'

// https://vuetifyjs.com/en/introduction/why-vuetify/#feature-guides
export default createVuetify({
  theme: {
    themes: {
      dark: {
        colors: {
          primary: '#0C234B',
          secondary: '#AB2520',
        }
      },
      light: {
        colors: {
          primary: '#1e5288',
          secondary: '#AB2520',
          background: '#e2e9eb',
          surface: '#f4ede5',
        }
      }
    }
    // defaultTheme: 'dark',
  },
})
