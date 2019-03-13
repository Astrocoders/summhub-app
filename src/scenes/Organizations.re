open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);
  let content =
    style([alignItems(FlexEnd), flexDirection(Column), width(Pct(90.))]);

  let contentTitle = style([fontSize(Float(16.))]);

  let contentDetail = style([fontSize(Float(14.))]);

  let buttonWrapper = style([marginTop(Pct(10.))]);
};

let component = ReasonReact.statelessComponent("Organizations");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <AppStatusBar mode=Light />
      <AppBar
        title="Settings"
        renderLeft={_ => <BackButton onPress=ignore />}
      />
      <SectionTitle
        value="Organizations"
        style=Style.(style([paddingHorizontal(Pt(20.))]))
      />
      <AppList
        renderItems={_ =>
          <ScrollView>
            <ListItem
              onPress=ignore
              renderLeft={_ =>
                <Title value={j|Itaú|j} style=Styles.contentTitle />
              }
              renderCenter={_ =>
                <View style=Styles.content>
                  <AppText value="123 members" style=Styles.contentDetail />
                  <AppText value="4 projects" style=Styles.contentDetail />
                </View>
              }
              renderRight={_ => <ListItemMoreInfo direction=Right />}
            />
          </ScrollView>
        }
      />
      <AppFAB
        icon={
          Element(
            _ =>
              <RNIcons.MaterialCommunityIcons
                name=`_plus
                size=24.
                color={AppConfig.theme.contrastWhite}
              />,
          )
        }
        small=true
      />
      <SectionTitle
        value="Version"
        style=Style.(style([paddingHorizontal(Pt(20.))]))
      />
      <SectionTitle
        value="Helper"
        style=Style.(style([paddingHorizontal(Pt(20.))]))
      />
      <SectionTitle
        value="Whatever"
        style=Style.(style([paddingHorizontal(Pt(20.))]))
      />
    </View>,
};
