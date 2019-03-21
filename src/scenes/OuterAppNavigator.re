open NavigationConfig.OuterApp;
module HeaderNull = {
  let component = ReasonReact.statelessComponent("HeaderNull");
  let make = (~headerProps as _, _children) => {
    ...component,
    render: _self => ReasonReact.null,
  };
};

let component = ReasonReact.statelessComponent("OuterAppNavigator");

let make = (~navigation as mainNavigation, ~initialState, _children) => {
  ...component,
  render: _self => {
    let%Epitath setPop = c =>
      <NavigationBackButtonRegister> ...c </NavigationBackButtonRegister>;

    let%Epitath setNavigation = c =>
      <Deeplinking.NavigationLinkingListener
        resolve={(navigation, url) =>
          switch (url) {
          | [|token|] => navigation.push(Login)
          | [|"reset", token|] => navigation.push(Login)
          | _ => ()
          }
        }>
        ...c
      </Deeplinking.NavigationLinkingListener>;

    <StackNavigator
      initialState
      headerComponent=HeaderNull.make
      onNavigationReady={getNavigation => {
        setNavigation(getNavigation);
        setPop(() => getNavigation(navigation => navigation.pop()));
      }}>
      ...{(~currentRoute, ~navigation) =>
        switch (currentRoute) {
        | Login => <Login navigation />
        | LoginAwaiting => <LoginAwaiting navigation />
        }
      }
    </StackNavigator>;
  },
};
