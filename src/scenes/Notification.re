open BsReactNative;
open NavigationConfig;

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

module Query = [%graphql
  {|
query AppQuery {
  currentUser {
    notifications {
      id
      title
      createdAt
      icon
      link
    }
  }
}
|}
];

module QueryContainer = ReasonApollo.CreateQuery(Query);

module StateConfig = {
  type state = Deeplinking.state;
};

module State = ReContainers.WithState.Make(StateConfig);

let data = {"name": "Foo", "age": 12};

let component = ReasonReact.statelessComponent("Notification");

let make = (~navigation, _children) => {
  ...component,
  render: _self => {
    let%Epitath {result, refetch} =
      c => <QueryContainer> ...c </QueryContainer>;

    <StackNavigator.Screen navigation>
      ...{() =>
        <QueryRenderer result refetch>
          ...{data =>
            <View style=Styles.wrapper>
              <AppStatusBar mode=Light />
              <AppBar
                title="Notification"
                renderLeft={_ => <BackButton onPress=ignore />}
              />
              <Layout>
                <SectionTitle value="Organizations" style=Styles.title />
                <AppList style=Style.(style([marginBottom(Pt(20.))]))>
                  {data##currentUser
                   ->Belt.Option.map(user => user##notifications)
                   ->(
                       notification =>
                         switch (notification) {
                         | Some(notification) =>
                           Belt.Option.getWithDefault(notification, [||])
                           ->Belt.Array.map(notification =>
                               <ListItem
                                 key=notification##id
                                 onPress=ignore
                                 renderLeft={_ =>
                                   <ListItemIcon icon=`_iosCheckmark />
                                 }
                                 renderCenter={_ =>
                                   <View style=Styles.content>
                                     <View>
                                       <AppText
                                         value=notification##title
                                         style=Styles.contentTitle
                                       />
                                       <AppText
                                         value="grsabreu+lionnn@gmail.com"
                                         style=Styles.contentDetail
                                       />
                                       <AppText
                                         value=notification##createdAt
                                         style=Styles.contentDate
                                       />
                                     </View>
                                   </View>
                                 }
                                 renderRight={_ =>
                                   <ListItemMoreInfo direction=Right />
                                 }
                               />
                             )
                         | None => [||]
                         }
                     )}
                </AppList>
                <JSONViewer data />
                <Title value="Discussion" style=Styles.title />
                <Messenger>
                  <MessengerMessage
                    sender="guilherme.decampo@astrocoders.com"
                    content="wtf is these dudes! These guys need to fix these issues!"
                  />
                </Messenger>
              </Layout>
            </View>
          }
        </QueryRenderer>
      }
    </StackNavigator.Screen>;
  },
};
