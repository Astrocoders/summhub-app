open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      alignItems(Center),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
      flex(1.),
      justifyContent(Center),
      padding(Pt(30.)),
    ]);
  let logoStyle =
    style([
      height(Pt(150.)),
      marginTop(Pt(10.)),
      marginBottom(Pct(10.)),
    ]);
};

let component = ReasonReact.statelessComponent("LoginAwaiting");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <Logo mode=Black style=Styles.logoStyle />
      <AppText value="Enviado para seu email" />
    </View>,
};
