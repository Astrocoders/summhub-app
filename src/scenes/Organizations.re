open BsReactNative;
open NavigationConfig.InApp;

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

module CreateOrganizationMutation = [%graphql
  {|
    mutation CreateOrganization {
      createOrganization {
        error
        organization {
          id
          name
          createdAt
        }
      }
    }
  |}
];

module CreateOrganizationMutationContainer =
  ReasonApollo.CreateMutation(CreateOrganizationMutation);

let component = ReasonReact.statelessComponent("Organizations");

let make = (~navigation, _children) => {
  ...component,
  render: _self => {
    let%Epitath {result, refetch} =
      c => <QueryContainer> ...c </QueryContainer>;

    let%Hook snackbar =
      Snackbar.make(
        ~action={
          Paper.Snackbar.snackbarAction(~label="Fechar", ~onPress=ignore);
        },
      );

    let%Epitath createOrganization = c =>
      <CreateOrganizationMutationContainer>
        ...{(mutate, _) => c(mutate)}
      </CreateOrganizationMutationContainer>;

    <StackNavigator.Screen navigation>
      ...{() =>
        <QueryRenderer result refetch>
          ...{data =>
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
              <AppList>
                {data##currentUser
                 ->Belt.Option.map(user => user##notifications)
                 ->(
                     notifications =>
                       switch (notifications) {
                       | Some(notifications) =>
                         Belt.Option.getWithDefault(notifications, [||])
                         ->Belt.Array.map(organization =>
                             <ListItem
                               key=organization##id
                               onPress=ignore
                               renderLeft={_ =>
                                 <Title
                                   value={j|Itaú|j}
                                   style=Styles.contentTitle
                                 />
                               }
                               renderCenter={_ =>
                                 <View style=Styles.content>
                                   <AppText
                                     value="123 members"
                                     style=Styles.contentDetail
                                   />
                                   <AppText
                                     value="4 projects"
                                     style=Styles.contentDetail
                                   />
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
              <AppFAB
                icon={
                  <RNIcons.MaterialCommunityIcons
                    name=`_plus
                    size=24.
                    color={AppConfig.theme.contrastWhite}
                  />
                }
                onPress={() =>
                  Js.Promise.(
                    createOrganization()
                    |> then_(result =>
                         CreateOrganizationMutationContainer.convertJsInputToReason(
                           result,
                         ).
                           data
                         ->Belt.Option.map(data => data##createOrganization)
                         ->Belt.Option.map(createOrganization =>
                             switch (createOrganization##error) {
                             | Some(error) =>
                               snackbar.send(Set(Open(error)));
                               Js.Promise.resolve();
                             | _ =>
                               snackbar.send(
                                 Set(Open("Organization Created")),
                               );
                               Js.Promise.resolve();
                             }
                           )
                         ->Belt.Option.getWithDefault(Js.Promise.resolve())
                       )
                    |> catch(_ => resolve())
                    |> ignore
                  )
                }
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
            </View>
          }
        </QueryRenderer>
      }
    </StackNavigator.Screen>;
  },
};
