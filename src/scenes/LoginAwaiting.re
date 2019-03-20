open BsReactNative;
open NavigationConfig.OuterApp;

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
  let logoStyle = style([height(Pt(150.))]);
  let text = style([marginTop(Pt(10.)), marginBottom(Pct(10.))]);
};

let component = ReasonReact.statelessComponent("LoginAwaiting");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen navigation>
      ...{() =>
        <View style=Styles.wrapper>
          <Logo mode=Black style=Styles.logoStyle />
          <AppText value="Enviado para seu email" style=Styles.text />
          <AppButton
            onPress={_ => navigation.push(Login)}
            text="Fazer Login novamente"
          />
        </View>
      }
    </StackNavigator.Screen>,
};
