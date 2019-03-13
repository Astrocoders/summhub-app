[@bs.deriving jsConverter]
type socialValues = [
  | [@bs.as "WHATSAPP"] `whatsapp
  | [@bs.as "PAGESMANAGER"] `pagesmanager
  | [@bs.as "FACEBOOK"] `facebook
  | [@bs.as "INSTAGRAM"] `instagram
  | [@bs.as "GOOGLEPLUS"] `googleplus
  | [@bs.as "EMAIL"] `email
  | [@bs.as "PINTEREST"] `pinterest
];

[@bs.deriving abstract]
type openOptions = {
  [@bs.optional]
  url: string,
  [@bs.optional]
  urls: array(string),
  [@bs.optional] [@bs.as "type"]
  contentType: string,
  [@bs.optional]
  message: string,
  [@bs.optional]
  title: string,
  [@bs.optional]
  subject: string,
  [@bs.optional]
  excludedActivityTypes: string,
  [@bs.optional]
  failOnCancel: string,
  [@bs.optional]
  showAppsToView: string,
};

[@bs.deriving abstract]
type singleShareOptions = {
  url: string,
  message: string,
  social: string,
  [@bs.optional] [@bs.as "type"]
  contentType: string,
  [@bs.optional]
  title: string,
  [@bs.optional]
  subject: string,
};

[@bs.module "react-native-share"]
external openDialog: openOptions => Js.Promise.t(Js.Json.t) = "open";

[@bs.module "react-native-share"]
external shareSingle: singleShareOptions => Js.Promise.t(Js.Json.t) =
  "shareSingle";

[@bs.module "react-native-share"]
external socialValues: Js.Dict.t(string) = "Social";

let getSocial = (value: socialValues) =>
  Js.Dict.get(socialValues, socialValuesToJs(value))
  ->Belt.Option.getWithDefault("");
