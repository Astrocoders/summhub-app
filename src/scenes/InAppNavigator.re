open NavigationConfig.InApp;
open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([backgroundColor(String(AppConfig.theme.secondary))]);
  let indicator =
    style([
      backgroundColor(String(AppConfig.theme.primary)),
      marginBottom(Pt(5.)),
    ]);
  let label =
    style([
      color(String(AppConfig.theme.primary)),
      marginHorizontal(Pt(0.)),
      fontSize(Float(10.)),
    ]);
};

module HeaderNull = {
  let component = ReasonReact.statelessComponent("HeaderNull");
  let make = (~headerProps as _, _children) => {
    ...component,
    render: _self => ReasonReact.null,
  };
};

let component = ReasonReact.statelessComponent("InAppNavigator");

let make = (~navigation as mainNavigation, ~initialState, _children) => {
  ...component,
  render: _self => {
    <StackNavigator initialState headerComponent=HeaderNull.make>
      ...{(~currentRoute, ~navigation) =>
        switch (currentRoute) {
        | Home => <Home navigation />
        | Organizations => <Organizations navigation />
        }
      }
    </StackNavigator>;
  },
};
