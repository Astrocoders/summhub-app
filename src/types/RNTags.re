[@bs.module "react-native-tags"]
external reactClass: ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type props = {
  [@bs.optional]
  initialText: string,
  [@bs.optional]
  initialTags: array(string),
  [@bs.optional]
  onChangeTags: array(string) => unit,
  [@bs.optional]
  readonly: bool,
  [@bs.optional]
  maxNumberOfTags: int,
  [@bs.optional]
  deleteOnTagPress: bool,
  [@bs.optional]
  containerStyle: BsReactNative.Style.t,
  [@bs.optional]
  style: BsReactNative.Style.t,
  [@bs.optional]
  inputContainerStyle: BsReactNative.Style.t,
  [@bs.optional]
  inputStyle: BsReactNative.Style.t,
  [@bs.optional]
  tagContainerStyle: BsReactNative.Style.t,
  [@bs.optional]
  tagTextStyle: BsReactNative.Style.t,
  [@bs.optional]
  inputPlaceholder: string,
  [@bs.optional]
  inputPlaceholderColor: string,
};

let make =
    (
      ~initialText=?,
      ~initialTags=?,
      ~onChangeTags=?,
      ~readonly=?,
      ~maxNumberOfTags=?,
      ~deleteOnTagPress=?,
      ~containerStyle=?,
      ~style=?,
      ~inputContainerStyle=?,
      ~inputStyle=?,
      ~tagContainerStyle=?,
      ~tagTextStyle=?,
      ~inputPlaceholder=?,
      ~inputPlaceholderColor=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      props(
        ~initialText?,
        ~initialTags?,
        ~onChangeTags?,
        ~readonly?,
        ~maxNumberOfTags?,
        ~deleteOnTagPress?,
        ~containerStyle?,
        ~style?,
        ~inputContainerStyle?,
        ~inputStyle?,
        ~tagContainerStyle?,
        ~tagTextStyle?,
        ~inputPlaceholder?,
        ~inputPlaceholderColor?,
        (),
      ),
    children,
  );
