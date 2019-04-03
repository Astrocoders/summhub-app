open BsReactNative;

module Styles = {
  open Style;
  let content = style([width(Pct(80.))]);

  let contentTitle = style([fontWeight(`_700), fontSize(Float(16.))]);

  let contentDetail = style([fontSize(Float(14.))]);

  let contentDate = style([fontSize(Float(12.))]);
};

let component = ReasonReact.statelessComponent("OrganizationItem");

let make = (~id, ~name, ~members, ~projects, ~onPress=ignore, _children) => {
  ...component,
  render: _self =>
    <ListItem
      key=id
      onPress
      renderLeft={_ => <Title value=name style=Styles.contentTitle />}
      renderCenter={_ =>
        <View style=Styles.content>
          <AppText
            value={string_of_int(members) ++ "members"}
            style=Styles.contentDetail
          />
          <AppText
            value={string_of_int(projects) ++ "projects"}
            style=Styles.contentDetail
          />
        </View>
      }
      renderRight={_ => <ListItemMoreInfo direction=Right />}
    />,
};
