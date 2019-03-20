open BsReactNative;
module Styles = {
  open Style;
  let textDescriptionLabel =
    style([
      color(String(AppConfig.theme.secondary)),
      fontWeight(`Bold),
      fontSize(Float(13.)),
      marginBottom(Pt(5.)),
    ]);

  let textDescription =
    style([
      color(String(AppConfig.theme.contrastDark)),
      fontSize(Float(14.)),
      marginBottom(Pt(10.)),
    ]);
};
let component = ReasonReact.statelessComponent("InfoField");

let make = (~label, ~value, _children) => {
  ...component,
  render: _self =>
    <View style=Style.(style([marginTop(Pt(5.))]))>
      <Paragraph value=label style=Styles.textDescriptionLabel />
      <Paragraph value style=Styles.textDescription />
    </View>,
};
