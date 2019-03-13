open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      position(Absolute),
      bottom(Pt(45.)),
      borderRadius(50.),
      right(Pt(15.)),
      padding(Pt(10.)),
      backgroundColor(String(AppConfig.theme.primary)),
    ]);
};

let component = ReasonReact.statelessComponent("AppFAB");

let make = (~style=Style.style([])) =>
  Paper.FAB.make(~style=Style.combine(style, Styles.wrapper));
