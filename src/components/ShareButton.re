open BsReactNative;

module Styles = {
  open Style;
  let backButton = style([padding(Pt(10.))]);
};

let component = ReasonReact.statelessComponent("ShareButton");

let make = (~color=AppConfig.theme.primary, _children) => {
  ...component,
  render: _self =>
    <View style=Styles.backButton>
      <RNIcons.Ionicons name=`_mdShare size=20. color />
    </View>,
};
