open BsReactNative;

module Styles = {
  open Style;
  let wrapper = (~isActive) =>
    style([
      alignItems(Center),
      backgroundColor(
        isActive
          ? String(AppConfig.theme.primary)
          : String(AppConfig.theme.transparent),
      ),
      borderRadius(50.),
      flexDirection(Row),
    ]);
  let label =
    style([
      fontSize(Float(14.)),
      paddingHorizontal(Pt(15.)),
      paddingVertical(Pt(10.)),
      overflow(Hidden),
      textAlign(Center),
    ]);
};

let component = ReasonReact.statelessComponent("Tab");

let make =
    (
      ~label,
      ~isActive,
      ~labelStyle=(~isActive as _) => Style.(style([])),
      ~style=Style.(style([])),
      ~onPress=ignore,
      _children,
    ) => {
  ...component,
  render: _self =>
    <TouchableOpacity
      onPress style={Style.combine(Styles.wrapper(~isActive), style)}>
      <Paragraph
        value=label
        style={Style.combine(Styles.label, labelStyle(~isActive))}
      />
    </TouchableOpacity>,
};
