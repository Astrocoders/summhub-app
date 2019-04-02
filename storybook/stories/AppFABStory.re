Storybook.(
  storiesOf("FAB", module_)
  |> add("default", () =>
       <AppFAB
         icon={
           <RNIcons.MaterialCommunityIcons
             name=`_plus
             size=24.
             color={AppConfig.theme.contrastWhite}
           />
         }
       />
     )
);
