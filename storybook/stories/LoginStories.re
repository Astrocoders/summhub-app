open BsReactNative;

let navigation: Summhub.NavigationConfig.OuterApp.StackNavigator.navigation = {
  push: ignore,
  pop: ignore,
  replace: ignore,
  setOptions: ignore,
};

Storybook.(
  storiesOf("Login", module_)
  |> add("default", () => <Login navigation />)
  |> add("awaiting", () =>
       <View style=Style.(style([flex(1.)]))>
         <LoginAwaiting navigation />
       </View>
     )
);
