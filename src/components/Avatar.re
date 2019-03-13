open BsReactNative;

module Styles = {
  open Style;
  let image = (~getSize) =>
    style([width(Pt(getSize)), height(Pt(getSize)), borderRadius(30.)]);
  let placeholder = (~getSize) =>
    style([
      width(Pt(getSize)),
      height(Pt(getSize)),
      borderRadius(30.),
      backgroundColor(String(AppConfig.theme.primary)),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let placeholderInitials =
    style([
      color(String(AppConfig.theme.contrastWhite)),
      textAlign(Center),
      letterSpacing(-0.1),
      fontSize(Float(13.)),
    ]);
};

let component = ReasonReact.statelessComponent("Avatar");

let make =
    (
      ~name,
      ~source=?,
      ~onPress=?,
      ~size=60.,
      ~style=Style.(style([])),
      _children,
    ) => {
  ...component,
  render: _self =>
    <TouchableOpacity ?onPress>
      {switch (source) {
       | Some(src) =>
         <Image
           style={Style.combine(Styles.image(~getSize=size), style)}
           source=src
         />
       | None =>
         <View
           style={Style.combine(Styles.placeholder(~getSize=size), style)}>
           <Paragraph value=name style=Styles.placeholderInitials />
         </View>
       }}
    </TouchableOpacity>,
};
