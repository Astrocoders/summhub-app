[@bs.module "react-native-egg"]
external reactClass: ReasonReact.reactClass = "default";

let make =
    (
      ~style: option(BsReactNative.Style.t)=?,
      ~setps: string,
      ~onCatch: unit => unit,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      Js.Null_undefined.{
        "setps": setps,
        "onCatch": onCatch,
        "style": fromOption(style),
      },
    children,
  );
