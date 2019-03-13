open BsReactNative;

Storybook.(
  storiesOf("Header", module_)
  |> add("default", () =>
       <Header
         renderCenter={_ =>
           <Text> {ReasonReact.string("Center Element")} </Text>
         }
         renderLeft={_ => <Text> {ReasonReact.string("Left Element")} </Text>}
         renderRight={_ =>
           <Text> {ReasonReact.string("Right Element")} </Text>
         }
       />
     )
  |> add("app bar", () =>
       <AppBar
         title="Example"
         renderLeft={_ => <BackButton onPress=ignore />}
         renderRight={_ => <CheckButton onPress=ignore />}
       />
     )
);
