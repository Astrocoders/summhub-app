[@bs.module "react-native-json-tree"]
external reactClass: ReasonReact.reactClass = "default";

let theme = {
  "scheme": "monokai",
  "author": "wimer hazenberg (http://www.monokai.nl)",
  "base00": "#272822",
  "base01": "#383830",
  "base02": "#49483e",
  "base03": "#75715e",
  "base04": "#a59f85",
  "base05": "#f8f8f2",
  "base06": "#f5f4f1",
  "base07": "#f9f8f5",
  "base08": "#f92672",
  "base09": "#fd971f",
  "base0A": "#f4bf75",
  "base0B": "#a6e22e",
  "base0C": "#a1efe4",
  "base0D": "#66d9ef",
  "base0E": "#ae81ff",
  "base0F": "#cc6633",
};

let make =
    (
      ~data: Js.t({..}),
      ~theme: Js.t({..})=theme,
      ~invertTheme: bool=false,
      _children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"data": data, "theme": theme, "invertTheme": invertTheme},
    _children,
  );
