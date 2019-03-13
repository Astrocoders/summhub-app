open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);
  let buttonWrapper = style([marginTop(Pct(10.))]);
  let content = style([width(Pct(80.))]);
  let contentTitle = style([fontWeight(`_700), fontSize(Float(16.))]);
  let contentDetail = style([fontSize(Float(14.))]);
  let contentDate = style([fontSize(Float(12.))]);
  let title = style([padding(Pt(20.))]);
};

let data = {"name": "Foo", "age": 12};

let component = ReasonReact.statelessComponent("Notification");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <AppStatusBar mode=Light />
      <AppBar
        title="Notification"
        renderLeft={_ => <BackButton onPress=ignore />}
      />
      <Layout>
        <SectionTitle value="Organizations" style=Styles.title />
        <AppList
          style=Style.(style([marginBottom(Pt(20.))]))
          renderItems={_ =>
            <View>
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
                    <AppText value="7 dec 22:21" style=Styles.contentDate />
                  </View>
                }
              />
            </View>
          }
        />
        <JSONViewer data />
        <Title value="Discussion" style=Styles.title />
        <Messenger>
          <MessengerMessage
            sender="guilherme.decampo@astrocoders.com"
            content="wtf is these dudes! These guys need to fix these issues!"
          />
        </Messenger>
      </Layout>
    </View>,
};
