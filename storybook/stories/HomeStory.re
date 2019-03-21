let navigation: Summhub.NavigationConfig.InApp.StackNavigator.navigation = {
  push: ignore,
  pop: ignore,
  replace: ignore,
  setOptions: ignore,
};

Storybook.(
  storiesOf("Home", module_) |> add("default", () => <Home navigation />)
);
