import React from 'react'
import { View, Text } from 'react-native'
import { ApolloProvider } from 'react-apollo'
import SplashScreen from 'react-native-splash-screen'

import { app as StackRouter } from './src/App.bs'
import apolloClient from './apollo'

export default class App extends React.Component {
  state = {
    hasError: false,
  }

  componentDidMount = () => {
    SplashScreen.hide()
  }

  componentDidCatch = () => {
    this.setState({ hasError: true })
  }

  render() {
    if (this.state.hasError) {
      return (
        <View>
          <Text>Error!</Text>
        </View>
      )
    }

    return (
      <ApolloProvider client={apolloClient}>
        <StackRouter />
      </ApolloProvider>
    )
  }
}
