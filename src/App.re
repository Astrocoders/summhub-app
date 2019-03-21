open NavigationConfig;

module HeaderNull = {
  let component = ReasonReact.statelessComponent("HeaderNull");
  let make = (~headerProps as _, _children) => {
    ...component,
    render: _self => ReasonReact.null,
  };
};

/* module Query = [%graphql */
/*   {| */
     /* query AppQuery { */
     /*   currentUser { */
     /*     _id */
     /*     onboardingState */
     /*   } */
     /* } */
     /* |} */
/* ]; */

/* module QueryContainer = ReasonApollo.CreateQuery(Query); */

module StateConfig = {
  type state = Deeplinking.state;
};

module State = ReContainers.WithState.Make(StateConfig);

let useSetupInitialRouteStates = (~data, ~state, ~send, c) =>
  <ReContainers.Component
    didMount={_self =>
      Deeplinking.getInitialRouterStates(~data, ~state)
      |> Js.Promise.then_(newState =>
           send(State.Set({...newState, finishedSettingUp: true}))
           |> Js.Promise.resolve
         )
      |> ignore
    }>
    ...c
  </ReContainers.Component>;

let app = () =>
  <Paper.PaperProvider>
    {let%Epitath {state, send} =
       c =>
         <State
           initialState=Deeplinking.{
             initialURL: None,
             outerAppInitialState: [|Login|],
             rootInitialState: [|OuterApp|],
             finishedSettingUp: true,
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
             | InApp => <InAppNavigator initialState=[|Home|] navigation />
             }
           }
         </StackNavigator>
       : <FullLoader mode=Black />}
  </Paper.PaperProvider>;
