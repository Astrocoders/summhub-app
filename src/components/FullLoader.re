open BsReactNative;

module Styles = {
  open Style;

  let wrapper = style([flex(1.), ...AppTheme.Helpers.fullCenter]);
  let logoContainer = style([alignItems(Center)]);
  let logo = style([width(Pt(200.))]);
};

let component = ReasonReact.statelessComponent("FullLoader");

let make = (~mode, ~message=?, _children) => {
  ...component,
  render: _self =>
    <Shimmer style=Styles.wrapper>
      <View style=Styles.logoContainer>
        <Logo mode style=Styles.logo />
        {switch (message) {
         | Some(message) => <Paragraph value=message />
         | None => ReasonReact.null
         }}
      </View>
    </Shimmer>,
};
