open BsReactNative;

[@bs.deriving abstract]
type scene = {
  [@bs.as "key"]
  key_: string,
  title: string,
  render: unit => ReasonReact.reactElement,
};

[@bs.module "./TabView"] external tabView: ReasonReact.reactClass = "default";

[@bs.deriving jsConverter]
type tabBarPosition = [ | `top | `bottom];

let make =
    (
      ~scenes: array(scene),
      ~tabBarPosition=`top,
      ~renderTabBar: option('a => ReasonReact.reactElement)=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=tabView,
    ~props={
      "tabBarPosition": tabBarPositionToJs(tabBarPosition),
      "scenes": scenes,
      "renderTabBar": Js.Nullable.fromOption(renderTabBar),
    },
    children,
  );

module TabBar = {
  [@bs.module "react-native-tab-view"]
  external tabBar: ReasonReact.reactClass = "TabBar";

  let make =
      (
        ~labelStyle=Style.style([]),
        ~indicatorStyle=Style.style([]),
        ~style=Style.style([]),
        ~rest,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=tabBar,
      ~props=
        Js.Obj.assign(
          {
            "labelStyle": labelStyle,
            "indicatorStyle": indicatorStyle,
            "style": style,
          },
          rest,
        ),
      children,
    );
};
