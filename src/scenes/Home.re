open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);
  let tabWrapper = style([marginTop(Pt(10.))]);
  let infoTabContent =
    style([flexDirection(Column), justifyContent(SpaceBetween)]);
  let content = style([width(Pct(80.))]);
  let contentTitle = style([fontWeight(`_700), fontSize(Float(16.))]);
  let contentDetail = style([fontSize(Float(14.))]);
  let contentDate = style([fontSize(Float(12.))]);
};

let component = ReasonReact.statelessComponent("Home");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <AppStatusBar mode=Light />
      <AppBar title="Summ" renderLeft={_ => <BackButton onPress=ignore />} />
      <SummaryPanel onPress=ignore style=Style.(style([margin(Pt(20.))])) />
      <Tabs
        tabs=[
          {
            label: {j|All|j},
            renderContent: () =>
              <ScrollView
                style=Styles.tabWrapper
                contentContainerStyle=Styles.infoTabContent>
                <AppList
                  renderItems={_ =>
                    <ScrollView>
                      <ListItem
                        onPress=ignore
                        renderLeft={_ => <ListItemIcon icon=`_iosCheckmark />}
                        renderCenter={_ =>
                          <View style=Styles.content>
                            <AppText
                              value="R$ 79,90 refunded"
                              style=Styles.contentTitle
                            />
                            <AppText
                              value="grsabreu+lionnn@gmail.com"
                              style=Styles.contentDetail
                            />
                            <AppText
                              value="7 dec 22:21"
                              style=Styles.contentDate
                            />
                          </View>
                        }
                        renderRight={_ => <ListItemMoreInfo direction=Right />}
                      />
                      <ListItem
                        onPress=ignore
                        renderLeft={_ => <ListItemIcon icon=`_iosCheckmark />}
                        renderCenter={_ =>
                          <View style=Styles.content>
                            <AppText
                              value="R$ 79,90 refunded"
                              style=Styles.contentTitle
                            />
                            <AppText
                              value="grsabreu+lionnn@gmail.com"
                              style=Styles.contentDetail
                            />
                            <AppText
                              value="7 dec 22:21"
                              style=Styles.contentDate
                            />
                          </View>
                        }
                        renderRight={_ => <ListItemMoreInfo direction=Right />}
                      />
                    </ScrollView>
                  }
                />
              </ScrollView>,
          },
          {
            label: {j|1w|j},
            renderContent: () =>
              <ScrollView
                style=Styles.tabWrapper
                contentContainerStyle=Styles.infoTabContent>
                <Title value="1" />
              </ScrollView>,
          },
          {
            label: {j|4w|j},
            renderContent: () =>
              <ScrollView
                style=Styles.tabWrapper
                contentContainerStyle=Styles.infoTabContent>
                <Title value="2" />
              </ScrollView>,
          },
          {
            label: {j|1y|j},
            renderContent: () =>
              <ScrollView
                style=Styles.tabWrapper
                contentContainerStyle=Styles.infoTabContent>
                <Title value="3" />
              </ScrollView>,
          },
          {
            label: {j|Qtd|j},
            renderContent: () =>
              <ScrollView
                style=Styles.tabWrapper
                contentContainerStyle=Styles.infoTabContent>
                <Title value="4" />
              </ScrollView>,
          },
          {
            label: {j|Ytd|j},
            renderContent: () =>
              <ScrollView
                style=Styles.tabWrapper
                contentContainerStyle=Styles.infoTabContent>
                <Title value="5" />
              </ScrollView>,
          },
        ]
      />
    </View>,
};
