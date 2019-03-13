open BsReactNative;

module Styles = {
  open Style;
  let webookAction =
    style([
      alignItems(Center),
      display(Flex),
      flexDirection(Row),
      justifyContent(Center),
      padding(Pt(10.)),
      marginBottom(Pt(15.)),
      marginTop(Pt(5.)),
    ]);
  let copyTitle =
    style([
      color(String(AppConfig.theme.contrastDark)),
      fontSize(Float(16.)),
      fontWeight(`_700),
      marginRight(Pt(10.)),
      textAlign(Center),
    ]);
  let copyText =
    style([
      color(String(AppConfig.theme.contrastDark)),
      fontSize(Float(14.)),
      fontWeight(`_300),
      marginRight(Pt(10.)),
    ]);
};

let component = ReasonReact.statelessComponent("Webhook");

let make = (~text, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self =>
    <TouchableOpacity onPress={() => Clipboard.setString(text)}>
      <AppText style=Styles.copyTitle value="webhook" />
      <View style={Style.combine(Styles.webookAction, style)}>
        <AppText style=Styles.copyText value=text />
        <RNIcons.MaterialIcons
          name=`_contentCopy
          color={AppConfig.theme.primary}
          size=20.
        />
      </View>
    </TouchableOpacity>,
};
