open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([alignItems(Center)]);
};

type direction =
  | Right
  | Left;

let component = ReasonReact.statelessComponent("ListItemMoreInfo");

let make =
    (~style=Style.(style([])), ~onPress=?, ~direction, ~size=20., _children) => {
  ...component,
  render: _self => {
    let renderArrow = (~name) =>
      <TouchableOpacity ?onPress>
        <View style={Style.combine(Styles.wrapper, style)}>
          <RNIcons.Ionicons name size color={AppConfig.theme.gray} />
        </View>
      </TouchableOpacity>;

    switch (direction) {
    | Right => renderArrow(~name=`_iosArrowForward)
    | Left => renderArrow(~name=`_iosArrowBack)
    };
  },
};
