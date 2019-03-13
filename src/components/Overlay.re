open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      paddingTop(Pt(40.)),
      backgroundColor(String("rgba(0,0,0,0.2)")),
    ]);
};

let component = ReasonReact.statelessComponent("Overlay");

let make = (~wrapperStyle=Style.(style([])), children) => {
  ...component,
  render: _self =>
    <View style={Style.combine(Styles.wrapper, wrapperStyle)}>
      ...children
    </View>,
};
