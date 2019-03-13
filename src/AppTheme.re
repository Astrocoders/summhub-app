module Helpers = {
  open BsReactNative.Style;
  let fullCenter = [justifyContent(Center), alignItems(Center)];
  let stackScreenPure =
    style([
      backgroundColor(String("transparent")),
      shadowColor(String("transparent")),
      shadowOffset(~width=0.0, ~height=0.0),
      shadowOpacity(0.),
      shadowRadius(0.),
    ]);
};
