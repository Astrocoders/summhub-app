open BsReactNative;

module Styles = {
  open Style;
  let wrapper = value => style([flex(1.), opacity(Animated(value))]);
  let element = style([backgroundColor(String("#ECEBEB"))]);
};

type state = {
  value: Animated.Value.t,
  animation: option(Animated.Animation.t),
};
type action =
  | Stop
  | Start
  | SetAnimation(Animated.Animation.t);

let component = ReasonReact.reducerComponent("Shimmer");

let make =
    (~initialValue=0.5, ~animated=true, ~style=Style.(style([])), children) => {
  ...component,
  initialState: () => {
    value: Animated.Value.create(initialValue),
    animation: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | SetAnimation(animation) =>
      Update({...state, animation: Some(animation)})
    | Start =>
      UpdateWithSideEffects(
        state,
        self => {
          let animation =
            Animated.loop(
              ~animation=
                Animated.sequence([|
                  Animated.timing(
                    ~value=self.state.value,
                    ~toValue=`raw(1.0),
                    ~duration=1000.0,
                    ~easing=Easing.ease,
                    (),
                  ),
                  Animated.timing(
                    ~value=self.state.value,
                    ~toValue=`raw(initialValue),
                    ~duration=1000.0,
                    ~easing=Easing.ease,
                    (),
                  ),
                |]),
              (),
            );
          Animated.start(animation, ());
          self.send(SetAnimation(animation));
        },
      )
    | Stop =>
      UpdateWithSideEffects(
        state,
        self =>
          switch (self.state.animation) {
          | Some(animation) => Animated.stop(animation)
          | None => ()
          },
      )
    },
  didMount: self => animated ? self.send(Start) : (),
  willUnmount: self =>
    switch (self.state.animation) {
    | Some(animation) => Animated.stop(animation)
    | None => ()
    },
  render: self =>
    <Animated.View
      style={Style.combine(Styles.wrapper(self.state.value), style)}>
      ...children
    </Animated.View>,
};

module Content = {
  let component = ReasonReact.statelessComponent("ShimmerContent");

  let make = (~width as elWidth, ~height as elHeight, children) => {
    ...component,
    render: _self =>
      <View
        style=Style.(style([width(Pt(elWidth)), height(Pt(elHeight))]))>
        ...children
      </View>,
  };
};

module Rect = {
  let component = ReasonReact.statelessComponent("ShimmerRect");

  let make =
      (
        ~x,
        ~y,
        ~rx,
        ~ry as _,
        ~width as elWidth,
        ~height as elHeight,
        _children,
      ) => {
    ...component,
    render: _self =>
      <View
        style={Style.combine(
          Styles.element,
          Style.(
            style([
              position(Absolute),
              top(Pt(y)),
              left(Pt(x)),
              width(Pt(elWidth)),
              height(Pt(elHeight)),
              borderRadius(rx),
            ])
          ),
        )}
      />,
  };
};

module Circle = {
  let component = ReasonReact.statelessComponent("ShimmerRect");

  let make = (~cx, ~cy, ~r, _children) => {
    ...component,
    render: _self =>
      <View
        style={Style.combine(
          Styles.element,
          Style.(
            style([
              position(Absolute),
              top(Pt(cy -. r)),
              left(Pt(cx -. r)),
              width(Pt(r *. 2.)),
              height(Pt(r *. 2.)),
              borderRadius(r),
            ])
          ),
        )}
      />,
  };
};
