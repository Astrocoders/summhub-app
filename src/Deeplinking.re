open BsReactNative;
open NavigationConfig;

let getOuterAppInitialState = (~url) =>
  switch (url) {
  | Some(url) =>
    let route = Utils.Linking.getRoute(url);
    let token = Utils.Linking.getParams(route);
    Js.log(route);
    Js.log(token);
    [|ConfigOuterApp.Login|];
  | _ => [|ConfigOuterApp.Login|]
  };
type state = {
  finishedSettingUp: bool,
  initialURL: option(string),
  outerAppInitialState: array(ConfigOuterApp.route),
  rootInitialState: array(Config.route),
};

let getInitialRouterStates = (~data, ~state) =>
  switch (data##currentUser) {
  | Some(_user) =>
    Js.Promise.resolve({...state, rootInitialState: [|Config.InApp|]})
  | None =>
    Js.Promise.(
      Linking.getInitialURL()
      |> then_(url =>
           {
             ...state,
             outerAppInitialState: getOuterAppInitialState(~url),
             initialURL: Some(Belt.Option.getWithDefault(url, "")),
           }
           |> resolve
         )
    )
  };

/* TODO move this to Nautilus */
module NavigationLinkingListener = {
  type getNavigation =
    (NavigationConfig.OuterApp.StackNavigator.navigation => unit) => unit;
  type state = {getNavigation: option(getNavigation)};

  type action =
    | LoadGetNavigation(getNavigation)
    | HandleIncomingURL(string);

  let urlToArray: (. string) => array(string) = [%bs.raw
    {|
  function(url) {
    return url.replace((/.*?:\/\//g), '').split('/').slice(1)
  }
  |}
  ];

  let component = ReasonReact.reducerComponent("NavigationLinkingListener");

  let make = (~resolve, children) => {
    ...component,
    initialState: () => {getNavigation: None},
    reducer: (action, _state) =>
      switch (action) {
      | LoadGetNavigation(getNavigation) =>
        Update({getNavigation: Some(getNavigation)})
      | HandleIncomingURL(url) =>
        SideEffects(
          self =>
            switch (self.state.getNavigation) {
            | Some(getNavigation) =>
              getNavigation(navigation =>
                resolve(navigation, urlToArray(. url))
              )
            | None => ()
            },
        )
      },
    didMount: self => {
      let listener = data => self.send(HandleIncomingURL(data##url));
      Linking.addEventListener("url", listener);

      Platform.os() == Android
        ? Linking.getInitialURL()
          |> Js.Promise.then_(url =>
               self.send(
                 HandleIncomingURL(Belt.Option.getWithDefault(url, "")),
               )
               |> Js.Promise.resolve
             )
          |> ignore
        : ();
      self.onUnmount(() => Linking.removeEventListener("url", listener));
    },
    render: self =>
      children(getNavigation => self.send(LoadGetNavigation(getNavigation))),
  };
};
