[@genType]
type captureMode = [ | `mount | `continous | `update | `none];

[@genType]
type imageFormat = [ | `jpg | `png | `webm];

[@genType]
type result = [ | `tmpfile | `base64 | [@genType.as "data-uri"] `dataUri];

[@genType]
type options = {
  format: imageFormat,
  quality: float,
  result,
};

[@genType.import "react-native-view-shot"]
[@genType.as "react_native_view_shot"]
[@bs.module "./ViewShot.gen"]
external make:
  (
    ~captureMode: captureMode=?,
    ~options: options=?,
    ~onCapture: string => unit=?,
    ~onCaptureFail: unit => unit=?,
    array(ReasonReact.reactElement)
  ) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  ) =
  "";

let make = make;
