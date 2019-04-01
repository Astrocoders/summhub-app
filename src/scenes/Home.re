open BsReactNative;
open NavigationConfig.InApp;

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

module Query = [%graphql
  {|
query AppQuery {
  currentUser {
    id
    email
    role
    summary {
      unread
      total
      projects
      organizations
    }
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

let component = ReasonReact.statelessComponent("Home");

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
                title="Summ"
                renderLeft={_ => <BackButton onPress=ignore />}
              />
              <SummaryPanel
                date={Js.Date.make() |> Js.Date.toString}
                unread={
                  data##currentUser
                  ->Belt.Option.map(user => user##summary##unread)
                  ->Belt.Option.getWithDefault(0)
                }
                totalNotifications={
                  data##currentUser
                  ->Belt.Option.map(user => user##summary##total)
                  ->Belt.Option.getWithDefault(0)
                }
                organizationsCount={
                  data##currentUser
                  ->Belt.Option.map(user => user##summary##organizations)
                  ->Belt.Option.getWithDefault(0)
                }
                projectsCount={
                  data##currentUser
                  ->Belt.Option.map(user => user##summary##projects)
                  ->Belt.Option.getWithDefault(0)
                }
                onPress=ignore
              />
              <Tabs
                tabs=[
                  {
                    label: {j|All|j},
                    renderContent: () =>
                      <ScrollView
                        style=Styles.tabWrapper
                        contentContainerStyle=Styles.infoTabContent>
                        <AppList>
                          {data##currentUser
                           ->Belt.Option.map(user => user##notifications)
                           ->(
                               notifications =>
                                 switch (notifications) {
                                 | Some(notifications) =>
                                   Belt.Option.getWithDefault(
                                     notifications,
                                     [||],
                                   )
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
            </View>
          }
        </QueryRenderer>
      }
    </StackNavigator.Screen>;
  },
};
