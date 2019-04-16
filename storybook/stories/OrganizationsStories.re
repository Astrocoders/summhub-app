open BsReactNative;

let inAppNavigation: Summhub.NavigationConfig.InApp.StackNavigator.navigation = {
  push: ignore,
  pop: ignore,
  replace: ignore,
  setOptions: ignore,
};

let navigation: OrganizationModalNavigatorConfig.ModalNavigator.navigation = {
  push: ignore,
  pop: ignore,
  replace: ignore,
  setOptions: ignore,
};

Storybook.(
  storiesOf("Organization", module_)
  |> add("default", () => <Organizations navigation=inAppNavigation />)
  |> add("organization modal", () =>
       <SafeAreaView style=Style.(style([flex(1.)]))>
         <OrganizationView
           organizationId="1234567890"
           navigation
           closeModal=ignore
         />
       </SafeAreaView>
     )
  |> add("organization project modal", () =>
       <SafeAreaView style=Style.(style([flex(1.)]))>
         <OrganizationProjectView
           organizationId="1234567890"
           projectId="0987654321"
           navigation
           closeModal=ignore
         />
       </SafeAreaView>
     )
);
