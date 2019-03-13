open BsReactNative;

let basePadding = Style.(paddingHorizontal(Pt(10.)));

module Styles = {
  open Style;
  let wrapper =
    style([
      alignItems(Center),
      basePadding,
      flexDirection(Row),
      height(Pt(50.)),
      justifyContent(SpaceBetween),
      width(Pct(100.)),
    ]);
  let rightItem =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(FlexStart),
      width(Pct(20.)),
    ]);
  let leftItem =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(FlexEnd),
      width(Pct(20.)),
    ]);
  let centerItem =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(Center),
      width(Pct(60.)),
    ]);
};

let component = ReasonReact.statelessComponent("Header");

let make =
    (
      ~style=Style.(style([])),
      ~renderLeft=() => ReasonReact.null,
      ~renderCenter=() => ReasonReact.null,
      ~renderRight=() => ReasonReact.null,
      _children,
    ) => {
  ...component,
  render: _self =>
    <View style={Style.combine(Styles.wrapper, style)}>
      <View style=Styles.rightItem> {renderLeft()} </View>
      <View style=Styles.centerItem> {renderCenter()} </View>
      <View style=Styles.leftItem> {renderRight()} </View>
    </View>,
};
