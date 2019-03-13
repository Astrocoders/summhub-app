open BsReactNative;

module Styles = {
  open Style;
  let text = style([fontFamily("Open Sans")]);
};

let component = ReasonReact.statelessComponent("AppText");

let make = (~value, ~style=Style.style([]), _children) => {
  ...component,
  render: _self =>
    <Paper.Text style={Style.combine(Styles.text, style)}>
      {ReasonReact.string(value)}
    </Paper.Text>,
};
