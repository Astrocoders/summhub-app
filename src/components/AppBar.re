open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      borderBottomWidth(1.),
      borderStyle(Solid),
      borderColor(String(AppConfig.theme.gray)),
      height(Pt(50.)),
      paddingVertical(Pt(5.)),
    ]);
  let header =
    style([
      flex(1.),
      alignItems(Center),
      backgroundColor(String(AppConfig.theme.contrastWhite)),
    ]);
  let headerTitle =
    style([
      color(String(AppConfig.theme.secondary)),
      fontWeight(`Bold),
      fontSize(Float(20.)),
    ]);
};

let component = ReasonReact.statelessComponent("AppBar");

let make = (~title, ~renderLeft=?, ~renderRight=?, _children) => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <Header
        style=Styles.header
        renderCenter={() => <Title style=Styles.headerTitle value=title />}
        ?renderLeft
        ?renderRight
      />
    </View>,
};
