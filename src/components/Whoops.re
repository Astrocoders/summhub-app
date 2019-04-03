open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      flexDirection(Column),
      justifyContent(Center),
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      overflow(Hidden),
    ]);
  let image =
    style([
      height(Pt(140.)),
      width(Pt(97.)),
      alignSelf(Center),
      marginBottom(Pt(40.)),
    ]);
  let title =
    style([textAlign(Center), fontSize(Float(20.)), fontWeight(`_700)]);
  let subtitle =
    style([textAlign(Center), fontWeight(`_400), marginTop(Pt(12.))]);
};

let component = ReasonReact.statelessComponent("Whoops");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <RNIcons.Ionicons
        name=`_iosAlert
        size=30.
        color={AppConfig.theme.error}
      />
      <Title style=Styles.title value="Whoops!" />
      <Paragraph style=Styles.subtitle value="Please, try again later" />
    </View>,
};
