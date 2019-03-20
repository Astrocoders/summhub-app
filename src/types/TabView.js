import React from 'react'
import { Dimensions, SafeAreaView } from 'react-native'
import { TabView, SceneMap } from 'react-native-tab-view'

export default class TabNavigation extends React.Component {
  constructor(props) {
    super(props)
    this.state = {
      index: 0,
      routes: props.scenes,
    }
  }

  render() {
    const sceneMapConfig = this.props.scenes.reduce(
      (config, scene) => ({ ...config, [scene.key]: scene.render }),
      {},
    )
    return (
      <TabView
        navigationState={this.state}
        renderScene={SceneMap(sceneMapConfig)}
        onIndexChange={index => this.setState({ index })}
        initialLayout={{
          width: Dimensions.get('window').width,
          height: Dimensions.get('window').height,
        }}
        {...this.props}
      />
    )
  }
}
