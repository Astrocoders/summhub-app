open BsReactNative;

let app = () => <SafeAreaView> <AppText value="Hello World" /> </SafeAreaView>;

/* let app = () =>
     <Paper.PaperProvider>

         {let%Epitath {state, send} =
            c =>
              <State
                initialState=Deeplinking.{
                  initialURL: None,
                  outerAppInitialState: [|Startup|],
                  rootInitialState: [|OuterApp|],
                  finishedSettingUp: false,
                }>
                ...c
              </State>

          state.finishedSettingUp
            ? <StackNavigator
                initialState={state.rootInitialState}
                headerComponent=HeaderNull.make>
                ...{(~currentRoute, ~navigation) =>
                  switch (currentRoute) {
                  | OuterApp =>
                    <OuterAppNavigator
                      navigation
                      initialState={state.outerAppInitialState}
                    />
                  | InApp => <InAppNavigator navigation />
                  }
                }
              </StackNavigator>
            : <FullLoader />}
       </Paper.PaperProvider>;
   */
