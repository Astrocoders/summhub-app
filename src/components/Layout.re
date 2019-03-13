open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([flex(1.)]);
};

let component = ReasonReact.statelessComponent("Layout");

let make = (~style=Style.(style([])), children) => {
  ...component,
  render: _self =>
    <SafeAreaView style={Style.combine(Styles.wrapper, style)}>
      <ScrollView> ...children </ScrollView>
    </SafeAreaView>,
};
