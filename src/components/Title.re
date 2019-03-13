open BsReactNative;

module Styles = {
  open Style;
  let text =
    style([
      fontSize(Float(24.)),
      lineHeight(36.),
      color(String(AppConfig.theme.contrastDark)),
      fontWeight(`Bold),
    ]);
};

let component = ReasonReact.statelessComponent("Title");

let make = (~value, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self =>
    <Paper.Title style={Style.combine(Styles.text, style)}>
      {ReasonReact.string(value)}
    </Paper.Title>,
};
