open BsReactNative;

module Styles = {
  open Style;
  let text = style([color(String(AppConfig.theme.primary))]);
};

let component = ReasonReact.statelessComponent("Link");

let make = (~onPress, ~value, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self =>
    <Paper.Text style={Style.combine(Styles.text, style)} onPress>
      {ReasonReact.string(value)}
    </Paper.Text>,
};
