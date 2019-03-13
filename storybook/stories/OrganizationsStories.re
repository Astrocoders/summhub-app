open BsReactNative;

let navigation: OrganizationModalNavigatorConfig.ModalNavigator.navigation = {
  push: ignore,
  pop: ignore,
  replace: ignore,
  setOptions: ignore,
};

Storybook.(
  storiesOf("Organization", module_)
  |> add("default", () => <Organizations />)
  |> add("organization modal", () =>
       <SafeAreaView style=Style.(style([flex(1.)]))>
         <OrganizationView navigation closeModal=ignore />
       </SafeAreaView>
     )
  |> add("organization project modal", () =>
       <SafeAreaView style=Style.(style([flex(1.)]))>
         <OrganizationProjectView navigation closeModal=ignore />
       </SafeAreaView>
     )
);
