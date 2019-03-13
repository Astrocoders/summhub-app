open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([marginBottom(Pt(20.))]);
  let column = style([flexDirection(Column), marginBottom(Pt(10.))]);
  let row = style([flexDirection(Row), marginBottom(Pt(10.))]);
  let avatar = style([marginRight(Pt(15.))]);
  let senderName = style([fontWeight(`Bold)]);
  let timestamp = style([fontSize(Float(12.))]);
};

let component = ReasonReact.statelessComponent("MessengerMessage");

let make = (~content, ~sender, ~style=Style.(style([])), _children) => {
  ...component,
  render: _self =>
    <View style={Style.combine(Styles.wrapper, style)}>
      <View style=Styles.row>
        <Avatar
          name={Utils.Str.firstLetter(sender)}
          size=30.
          style=Styles.avatar
        />
        <View style=Styles.column>
          <AppText style=Styles.senderName value=sender />
          <AppText style=Styles.timestamp value="25 minutes ago" />
        </View>
      </View>
      <View> <AppText value=content /> </View>
    </View>,
};
