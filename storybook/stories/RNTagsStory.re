open BsReactNative;

module Styles = {
  open Style;
  let tagWrapper =
    style([
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      borderRadius(0.),
      color(String(AppConfig.theme.contrastDark)),
      marginLeft(Pt(0.)),
      marginRight(Pt(10.)),
    ]);
};

Storybook.(
  storiesOf("Tags", module_)
  |> add("default", () =>
       <RNTags
         tagContainerStyle=Styles.tagWrapper
         inputPlaceholderColor="#B1B1B1"
         initialTags=[|"guilherme.decampo@astrocoders.com", "test"|]
         readonly=true
       />
     )
);
