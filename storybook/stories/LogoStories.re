open BsReactNative;

Storybook.(
  storiesOf("Logo", module_)
  |> add("black", () => <Logo mode=Black />)
  |> add("white", () =>
       <View style=Style.(style([backgroundColor(String("#ccc"))]))>
         <Logo mode=White />
       </View>
     )
);
