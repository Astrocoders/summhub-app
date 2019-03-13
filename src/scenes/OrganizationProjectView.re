open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);

  let fieldsWrapper =
    style([marginTop(Pt(30.)), paddingHorizontal(Pt(20.))]);

  let tagWrapper =
    style([
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      borderRadius(0.),
      color(String(AppConfig.theme.contrastDark)),
      marginLeft(Pt(0.)),
      marginRight(Pt(10.)),
    ]);
  let content =
    style([alignItems(FlexEnd), flexDirection(Column), width(Pct(90.))]);

  let contentTitle = style([fontSize(Float(16.))]);

  let contentDetail = style([fontSize(Float(14.))]);

  let buttonWrapper = style([marginTop(Pct(10.))]);
};

let component = ReasonReact.statelessComponent("OrganizationProjectView");

let make =
    (
      ~navigation: OrganizationModalNavigatorConfig.ModalNavigator.navigation,
      ~closeModal,
      _children,
    ) => {
  ...component,
  render: _self =>
    <OrganizationModalNavigatorConfig.StackNavigator.Screen navigation>
      ...{() =>
        <View style=Styles.wrapper>
          <AppBar
            title="Project"
            renderLeft={_ => <BackButton onPress={_ => closeModal()} />}
            renderRight={_ => <DeleteButton onPress={_ => closeModal()} />}
          />
          <View style=Styles.fieldsWrapper>
            <Webhook text="https://summ.link/234234234234" />
            <Input
              onChangeText=ignore
              placeholder="Nome"
              autoCapitalize=`words
              keyboardType=`default
              value="Astrocoders"
              style=Style.(style([marginBottom(Pt(10.))]))
            />
          </View>
        </View>
      }
    </OrganizationModalNavigatorConfig.StackNavigator.Screen>,
};
