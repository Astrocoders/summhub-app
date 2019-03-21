module Config = {
  type route =
    | OuterApp
    | InApp;
};

module ConfigInApp = {
  type route =
    | Home;
};

module ConfigOuterApp = {
  type route =
    | Login
    | LoginAwaiting;
};

module OuterApp =
  Nautilus.StackNavigator.CreateStackNavigator(ConfigOuterApp);

include Nautilus.StackNavigator.CreateStackNavigator(Config);
include Nautilus.TabNavigator.CreateTabNavigator(ConfigInApp);
