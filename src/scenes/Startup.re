open BsReactNative;
open NavigationConfig.OuterApp;

module Styles = {
  open Style;
  let w = style([flex(1.)]);
  let wrapper =
    style([flex(1.), flexDirection(Column), paddingTop(Pt(40.))]);
  let descriptionWrapper =
    style([
      flexDirection(Column),
      alignItems(Center),
      flex(1.),
      justifyContent(Center),
    ]);
  let logoStyle = style([height(Pt(150.)), marginTop(Pt(10.))]);
  let descriptionItem =
    style([
      paddingHorizontal(Pt(5.)),
      marginTop(Pt(20.)),
      textAlign(Center),
      fontSize(Float(20.)),
      color(String(AppConfig.theme.primary)),
    ]);
  let actionsWrapper =
    style([
      flex(1.),
      width(Pct(100.)),
      flexDirection(Column),
      justifyContent(FlexEnd),
      alignItems(Center),
      marginBottom(Pt(10.)),
    ]);
  let actionButton = style([width(Pct(90.)), borderRadius(0.)]);
};

let component = ReasonReact.statelessComponent("Startup");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen navigation>
      ...{() =>
        <SafeAreaView style=Styles.wrapper>
          <View style=Styles.descriptionWrapper>
            <Logo mode=Black style=Styles.logoStyle />
            <Title style=Styles.descriptionItem value="Hello" />
          </View>
          <View style=Styles.actionsWrapper>
            <AppButton
              style=Styles.actionButton
              onPress={_ => navigation.push(Startup)}
              text="Login"
              mode=`text
              color={AppConfig.theme.primary}
            />
          </View>
        </SafeAreaView>
      }
    </StackNavigator.Screen>,
};
