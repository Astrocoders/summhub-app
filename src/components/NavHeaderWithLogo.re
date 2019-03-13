open BsReactNative;
open NavigationConfig.OuterApp;

module Styles = {
  open Style;
  let wrapper = style([paddingHorizontal(Pt(15.))]);
  let logo = style([width(Pt(100.))]);
};

let component = ReasonReact.statelessComponent("NavHeaderWithLogo");

let make =
    (
      ~mode,
      ~navigation: StackNavigator.navigation,
      ~renderLeft=() => <BackButton onPress={_ => navigation.pop()} />,
      _children,
    ) => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <Header
        renderLeft
        renderCenter={() => <Logo mode style=Styles.logo />}
      />
    </View>,
};
