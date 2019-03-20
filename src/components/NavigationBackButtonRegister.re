/* Hooks up to a Navigator instance the proper popping behavior */

type state = {
  unregister: unit => unit,
  pop: unit => unit,
};

type action =
  | Set(state)
  | Pop;

let component = ReasonReact.reducerComponent(__MODULE__);

let make = children => {
  ...component,
  initialState: () => {unregister: ignore, pop: ignore},
  reducer: (action, _state) =>
    switch (action) {
    | Set(newState) => Update(newState)
    | Pop => SideEffects(self => self.state.pop())
    },
  willUnmount: self => self.state.unregister(),
  render: self =>
    children(pop =>
      self.send(
        Set({
          pop,
          unregister: AppBackHandler.register(() => self.send(Pop)),
        }),
      )
    ),
};
