open NavigationConfig;
open BsReactNative;

let component = ReasonReact.statelessComponent("InAppNavigator");

let make = (~navigation as mainNavigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen
      headerTitle="InAppNavigator" navigation=mainNavigation>
      ...{() =>
        <SafeAreaView
          style=Style.(
            style([
              flex(1.),
              backgroundColor(String(AppConfig.theme.primary)),
            ])
          )>
          <RNTabView
            tabBarPosition=`bottom
            renderTabBar={rest =>
              <RNTabView.TabBar
                rest
                indicatorStyle=Style.(
                  style([
                    backgroundColor(String(AppConfig.theme.primary)),
                    marginBottom(Pt(5.)),
                  ])
                )
                style=Style.(
                  style([
                    backgroundColor(String(AppConfig.theme.secondary)),
                  ])
                )
                labelStyle=Style.(
                  style([
                    color(String(AppConfig.theme.primary)),
                    marginHorizontal(Pt(0.)),
                    fontSize(Float(10.)),
                  ])
                )
              />
            }
            scenes=RNTabView.(
              [|
                scene(~key_="home", ~title="Home", ~render=() =>
                  <View style=Style.(style([flex(1.)]))> <Home /> </View>
                ),
              |]
            )
          />
        </SafeAreaView>
      }
    </StackNavigator.Screen>,
};
