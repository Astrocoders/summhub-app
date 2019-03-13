Storybook.(
  storiesOf("Input", module_)
  |> add("default", () =>
       <Input
         onChangeText=ignore
         placeholder="Placeholder"
         autoCapitalize=`none
         keyboardType=`default
       />
     )
  |> add("password", () =>
       <Input
         onChangeText=ignore
         placeholder="Password"
         autoCapitalize=`none
         secureTextEntry=true
         keyboardType=`default
       />
     )
);
