open BsReactNative;

module Styles = {
  open Style;
  let title = style([fontSize(Float(16.)), paddingVertical(Pt(10.))]);
};

let component = ReasonReact.statelessComponent("Title");

let make = (~value, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self => <Title value style={Style.combine(Styles.title, style)} />,
};
