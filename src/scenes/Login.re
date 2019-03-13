open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      backgroundColor(String(AppConfig.theme.backgroundColor)),
      flex(1.),
      justifyContent(Center),
      padding(Pt(30.)),
    ]);
  let logoStyle = style([height(Pt(150.)), marginTop(Pt(10.))]);
  let buttonWrapper = style([marginTop(Pct(10.))]);
};

let component = ReasonReact.statelessComponent("Login");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <Logo mode=Black style=Styles.logoStyle />
      <View style=Styles.buttonWrapper>
        <Input
          onChangeText=ignore
          placeholder="Preencha seu e-mail"
          autoCapitalize=`none
          keyboardType=`emailAddress
          style=Style.(style([marginBottom(Pt(10.))]))
        />
        <AppButton onPress=ignore text="Login" />
      </View>
    </View>,
};
