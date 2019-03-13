Storybook.(
  storiesOf("AppButton", module_)
  |> add("default", () => <AppButton onPress=ignore text="Click me" />)
);
