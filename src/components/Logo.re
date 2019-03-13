open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([width(Pct(100.)), padding(Pt(0.))]);
};

type mode =
  | Black
  | White;

let component = ReasonReact.statelessComponent("Logo");

let make = (~mode, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self => {
    let renderImage = (~source) =>
      <Image
        style={Style.combine(Styles.wrapper, style)}
        resizeMode=`contain
        source
      />;

    switch (mode) {
    | Black => renderImage(~source=AppConfig.images.logoDark)
    | White => renderImage(~source=AppConfig.images.logoWhite)
    };
  },
};
