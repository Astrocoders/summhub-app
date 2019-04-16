open BsReactNative;

type position =
  | Initial
  | BottomCenter
  | BottomRight;

module Styles = {
  open Style;
  let buttonShadow = (~position_, ~disabled) =>
    style([
      backgroundColor(String(AppConfig.theme.transparent)),
      width(Pt(60.)),
      height(Pt(60.)),
      ...switch (position_) {
         | Initial => []
         | BottomCenter => [
             position(Absolute),
             bottom(Pt(18.)),
             left(Pct(45.)),
             right(Pct(50.)),
           ]
         | BottomRight => [
             position(Absolute),
             bottom(Pt(18.)),
             right(Pt(15.)),
           ]
         },
    ]);
  let wrapper =
    style([
      backgroundColor(String(AppConfig.theme.primary)),
      height(Pt(60.)),
      width(Pt(60.)),
      borderRadius(30.),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let disabledWrapper =
    style([
      height(Pt(60.)),
      width(Pt(60.)),
      borderRadius(30.),
      alignItems(Center),
      justifyContent(Center),
      backgroundColor(String(AppConfig.theme.disabled)),
    ]);
  let label =
    style([
      fontSize(Float(12.)),
      textAlign(Center),
      fontWeight(`Bold),
      color(String(AppConfig.theme.contrastWhite)),
    ]);
};

module Wrapper = {
  let component = ReasonReact.statelessComponent("Wrapper");

  let make = (~disabled, ~style, children) => {
    ...component,
    render: _self =>
      disabled
        ? <View style={Style.combine(Styles.disabledWrapper, style)}>
            ...children
          </View>
        : <View style={Style.combine(Styles.wrapper, style)}>
            ...children
          </View>,
  };
};

let component = ReasonReact.statelessComponent("AppFAB");

let make =
    (
      ~disabled=false,
      ~onPress=ignore,
      ~label="",
      ~icon=?,
      ~style=Style.(style([])),
      ~position=Initial,
      ~isLoading=false,
      _children,
    ) => {
  ...component,
  render: _self =>
    <TouchableOpacity
      activeOpacity={disabled ? 1. : 0.2}
      style={Styles.buttonShadow(~position_=position, ~disabled)}
      onPress={_ => disabled || isLoading ? () : onPress()}>
      <Wrapper disabled style>
        {switch (icon, isLoading) {
         | (_, true) => <ActivityIndicator color={String("white")} />
         | (Some(icon), _) => icon
         | (_, _) => <Paragraph value=label style=Styles.label />
         }}
      </Wrapper>
    </TouchableOpacity>,
};
