import { AppRegistry } from 'react-native'
import { STORYBOOKS } from 'react-native-dotenv'
import SplashScreen from 'react-native-splash-screen'
import moment from 'moment'
import 'moment/locale/pt-br'

import { name } from './app.json'

moment.locale('pt-BR')

import App from './App'

if (STORYBOOKS === 'true') {
  SplashScreen.hide()
  console.disableYellowBox = true
  require('./storybook')
} else {
  AppRegistry.registerComponent(name, () => App)
}
