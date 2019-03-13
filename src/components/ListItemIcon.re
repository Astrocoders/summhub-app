open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([alignItems(Center)]);
};

let component = ReasonReact.statelessComponent("ListItemIcon");

let make =
    (~style=Style.(style([])), ~onPress=?, ~icon, ~size=36., _children) => {
  ...component,
  render: _self =>
    <TouchableOpacity ?onPress>
      <View style={Style.combine(Styles.wrapper, style)}>
        <RNIcons.Ionicons name=icon size color={AppConfig.theme.primary} />
      </View>
    </TouchableOpacity>,
};
