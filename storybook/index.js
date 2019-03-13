import React, { Component } from 'react'
import { AppRegistry } from 'react-native'
import { DefaultTheme, Provider as PaperProvider } from 'react-native-paper'
import { getStorybookUI, configure } from '@storybook/react-native'

import { name } from '../app.json'

import './addons'

configure(() => {
  require('./stories')
}, module)

const theme = {
  ...DefaultTheme,
  roundness: 0,
  colors: {
    primary: '#6970E4',
    accent: '#2E3276',
  },
}

const StorybookUIRoot = getStorybookUI({})

class StorybookUIHMRRoot extends Component {
  render() {
    return (
      <PaperProvider theme={theme}>
        <StorybookUIRoot />
      </PaperProvider>
    )
  }
}

AppRegistry.registerComponent(name, () => StorybookUIHMRRoot)
export default StorybookUIHMRRoot
