open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      alignItems(Center),
      borderColor(String(AppConfig.theme.gray100)),
      borderStyle(Solid),
      borderBottomWidth(1.),
      display(Flex),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      paddingHorizontal(Pt(25.)),
      paddingVertical(Pt(15.)),
      width(Pct(100.)),
    ]);

  let leftItem =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(FlexStart),
    ]);

  let centerItem =
    style([
      alignItems(FlexStart),
      flexDirection(Column),
      width(Pct(80.)),
    ]);

  let rightItem =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(FlexEnd),
    ]);
};

let component = ReasonReact.statelessComponent("ListItem");

let make =
    (
      ~onPress,
      ~style=Style.(style([])),
      ~renderLeft=() => ReasonReact.null,
      ~renderCenter=() => ReasonReact.null,
      ~renderRight=() => ReasonReact.null,
      _children,
    ) => {
  ...component,
  render: _self =>
    <TouchableOpacity onPress>
      <View style={Style.combine(Styles.wrapper, style)}>
        <View style=Styles.leftItem> {renderLeft()} </View>
        <View style=Styles.centerItem> {renderCenter()} </View>
        <View style=Styles.rightItem> {renderRight()} </View>
      </View>
    </TouchableOpacity>,
};
