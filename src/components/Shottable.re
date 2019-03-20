module StateConfig = {
  type state = {el: ref(option(ReasonReact.reactRef))};
};
module State = ReContainers.WithState.Make(StateConfig);

let component = ReasonReact.statelessComponent("Shottable");

let make = children => {
  ...component,
  render: _self => {
    let%Epitath {state} =
      c => <State initialState=StateConfig.{el: ref(None)}> ...c </State>;

    let capture = () =>
      switch (state.el^) {
      | Some(r) => ReasonReact.refToJsObj(r)##capture()
      | None => Js.Promise.reject(Js.Exn.raiseError("Not ready"))
      };

    children(~capture, ~renderShottable=children =>
      <ViewShot
        ref={ref => state.el := Js.Nullable.toOption(ref)}
        options={format: `png, quality: 1.0, result: `base64}>
        {children()}
      </ViewShot>
    );
  },
};
