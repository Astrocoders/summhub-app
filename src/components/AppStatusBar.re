open BsReactNative;

module Styles = {
  open Style;
  let wrapper = color =>
    style([
      width(Pct(100.)),
      backgroundColor(String(color)),
      paddingTop(
        switch (Platform.os()) {
        | Android => Pt(0.)
        | IOS(_) => Pt(0.)
        },
      ),
    ]);
};

type mode =
  | Dark
  | Light;

let component = ReasonReact.statelessComponent("AppStatusBar");

let make = (~mode=Light, _children) => {
  ...component,
  render: _self =>
    <View
      style={Styles.wrapper(
        mode == Dark ? AppConfig.theme.primary : AppConfig.theme.secondary,
      )}>
      {switch (mode) {
       | Dark =>
         <StatusBar
           backgroundColor={AppConfig.theme.contrastDark}
           barStyle=`lightContent
         />
       | Light =>
         <StatusBar
           backgroundColor={AppConfig.theme.contrastWhite}
           barStyle=`darkContent
         />
       }}
    </View>,
};
