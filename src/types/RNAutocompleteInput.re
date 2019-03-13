[@bs.module "react-native-autocomplete-input"]
external reactClass: ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type props('a) = {
  [@bs.optional]
  hideResults: bool,
  data: array('a),
  [@bs.optional]
  style: BsReactNative.Style.t,
  [@bs.optional]
  containerStyle: BsReactNative.Style.t,
  [@bs.optional]
  inputContainerStyle: BsReactNative.Style.t,
  [@bs.optional]
  listContainerStyle: BsReactNative.Style.t,
  [@bs.optional]
  listStyle: BsReactNative.Style.t,
  [@bs.optional]
  onShowResult: unit => unit,
  [@bs.optional]
  onStartShouldSetResponderCapture: unit => unit,
  renderItem: 'a => ReasonReact.reactElement,
  [@bs.optional]
  renderSeparator: unit => ReasonReact.reactElement,
  [@bs.optional]
  renderTextInput: unit => ReasonReact.reactElement,
  [@bs.optional]
  value: string,
  [@bs.optional]
  onChangeText: string => unit,
  [@bs.optional]
  placeholder: string,
};

let make =
    (
      ~hideResults=?,
      ~data,
      ~style=?,
      ~containerStyle=?,
      ~inputContainerStyle=?,
      ~listContainerStyle=?,
      ~listStyle=?,
      ~onShowResult=?,
      ~onStartShouldSetResponderCapture=?,
      ~renderItem,
      ~renderSeparator=?,
      ~renderTextInput=?,
      ~value=?,
      ~onChangeText=?,
      ~placeholder=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      props(
        ~hideResults?,
        ~data,
        ~style?,
        ~containerStyle?,
        ~inputContainerStyle?,
        ~listContainerStyle?,
        ~listStyle?,
        ~onShowResult?,
        ~onStartShouldSetResponderCapture?,
        ~renderItem,
        ~renderSeparator?,
        ~renderTextInput?,
        ~value?,
        ~onChangeText?,
        ~placeholder?,
        (),
      ),
    children,
  );
