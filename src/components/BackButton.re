open BsReactNative;

module Styles = {
  open Style;
  let backButton = style([padding(Pt(10.))]);
};

let component = ReasonReact.statelessComponent("BackButton");

let make = (~onPress, _children) => {
  ...component,
  render: _self =>
    <TouchableOpacity
      onPress hitSlop={"top": 30, "bottom": 30, "left": 40, "right": 40}>
      <View style=Styles.backButton>
        <RNIcons.MaterialCommunityIcons
          name=`_arrowLeft
          size=20.
          color={AppConfig.theme.primary}
        />
      </View>
    </TouchableOpacity>,
};
