open BsReactNative;

Storybook.(
  storiesOf("Login", module_)
  |> add("default", () => <Login />)
  |> add("awaiting", () =>
       <View style=Style.(style([flex(1.)]))> <LoginAwaiting /> </View>
     )
);
