Storybook.(
  storiesOf("Snackbar", module_)
  |> add("default", () =>
       <Snackbar
         action={Paper.Snackbar.snackbarAction(
           ~label="Hello",
           ~onPress=ignore,
         )}>
         ...{self =>
           <AppButton
             text="Open snackbar"
             onPress={_ => self.send(Set(Open("Fix X to do Y")))}
           />
         }
       </Snackbar>
     )
);
