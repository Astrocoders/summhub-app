open BsReactNative;

module Styles = {
  open Style;
  let text = dark =>
    style([
      color(
        String(
          dark ? AppConfig.theme.contrastWhite : AppConfig.theme.primary,
        ),
      ),
      fontSize(Float(16.)),
    ]);
  let button = (~color, ~mode, ~disabled) =>
    style([
      backgroundColor(String(mode == `outlined ? "transparent" : color)),
      borderColor(String(AppConfig.theme.primary)),
      borderWidth(mode == `outlined ? 1. : 0.),
      borderStyle(Solid),
      borderRadius(4.),
      opacity(disabled ? Float(0.4) : Float(1.0)),
      paddingVertical(Pt(5.)),
      marginHorizontal(Pt(0.)),
    ]);
};

let component = ReasonReact.statelessComponent("AppButton");

let make =
    (
      ~mode=`text,
      ~onPress,
      ~color=AppConfig.theme.primary,
      ~dark=true,
      ~theme=?,
      ~text,
      ~loading=false,
      ~style=Style.(style([])),
      ~labelStyle=Style.style([]),
      ~raised=false,
      ~disabled=false,
      _children,
    ) => {
  ...component,
  render: _self =>
    <Paper.Button
      onPress
      ?theme
      dark
      color
      mode
      icon=?{
        loading
          ? Some(
              Element(
                _ =>
                  <ActivityIndicator
                    color={
                      mode == `outlined ? String("#000") : String("#fff")
                    }
                  />,
              ),
            )
          : None
      }
      style={Style.combine(Styles.button(~mode, ~color, ~disabled), style)}
      disabled={loading || disabled}
      raised>
      <Paper.Text style={Style.combine(Styles.text(dark), labelStyle)}>
        {ReasonReact.string(text)}
      </Paper.Text>
    </Paper.Button>,
};
