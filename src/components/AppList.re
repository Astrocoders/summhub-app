open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      alignItems(FlexStart),
      backgroundColor(String("#fff")),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      width(Pct(100.)),
    ]);
};

let component = ReasonReact.statelessComponent("List");

let make =
    (
      ~style=Style.(style([])),
      ~renderItems=() => ReasonReact.null,
      _children,
    ) => {
  ...component,
  render: _self =>
    <View style={Style.combine(Styles.wrapper, style)}>
      {renderItems()}
    </View>,
};
