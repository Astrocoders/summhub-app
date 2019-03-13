open BsReactNative;

module Styles = {
  open Style;
  let text = style([fontFamily("Open Sans"), fontSize(Float(14.))]);
};

let component = ReasonReact.statelessComponent("Paragraph");

let make = (~value, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self =>
    <Paper.Text elipsizeMode="tail" style={Style.combine(Styles.text, style)}>
      {ReasonReact.string(value)}
    </Paper.Text>,
};
