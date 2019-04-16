open BsReactNative;
open ReasonApolloTypes;
open NavigationConfig.InApp;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);
};

module OrganizationsQuery = [%graphql
  {|
    query OrganizationsQuery($before: String, $last: Int, $after: String, $first: Float) {
      currentUser {
        id
        email
        organizations(before: $before, last: $last, after: $after, first: $first) {
          pageInfo {
            startCursor
            endCursor
            hasNextPage
          }
          edges {
            cursor
            node {
              id
              name
            }
          }
        }
      }
    }
  |}
];

module OrganizationsQueryContainer =
  ReasonApollo.CreateQuery(OrganizationsQuery);

let renderOrganizations = (~fetchMore, ~data, organizations) =>
  <FlatList
    data=organizations
    keyExtractor={(item, _idx) => "organization_" ++ item##node##id}
    onEndReached={_ =>
      if (Belt.Option.getWithDefault(
            data##currentUser##organizations##pageInfo##hasNextPage,
            false,
          )) {
        let variables =
          OrganizationsQuery.make(
            ~before=?data##currentUser##organizations##pageInfo##startCursor,
            ~after=?data##currentUser##organizations##pageInfo##endCursor,
            (),
          )##variables;
        let concatResults: (Js.Json.t, option(Js.Json.t)) => Js.Json.t = [%raw
          {|
              function(prev, next) {
                return {
                  organizations: {
                    ...next.organizations,
                    edges: [
                      ...prev.organizations.edges,
                      ...next.organizations.edges
                    ]
                  }
                };
              }
              |}
        ];
        Js.Promise.(
          fetchMore(
            ~variables=?Some(variables),
            ~updateQuery=
              (prev, next) =>
                concatResults(
                  prev,
                  ReasonApolloQuery.(next->fetchMoreResultGet),
                ),
            (),
          )
          |> then_(_ => resolve())
          |> catch(_error => resolve())
        )
        |> ignore;
      } else {
        ();
      }
    }
    renderItem={FlatList.renderItem(({item}) =>
      item##node
      |> (
        organization =>
          <OrganizationItem
            id=organization##id
            name=organization##name
            members=15
            projects=4
          />
      )
    )}
  />;

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
    let%Epitath {result, refetch, fetchMore} =
      c => <OrganizationsQueryContainer> ...c </OrganizationsQueryContainer>;

    let%Hook snackbar =
      Snackbar.make(
        ~action={
          Paper.Snackbar.snackbarAction(~label="Close", ~onPress=ignore);
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
                {switch (result) {
                 | Error(_) => <Whoops />
                 | Data(data) =>
                   data
                   ->Belt.Option.flatMap(data =>
                       data##currentUser##organizations##edges
                     )
                   ->Belt.Option.getWithDefault([||])
                   ->(
                       organizations =>
                         renderOrganizations(~fetchMore, ~data, organizations)
                     )
                 | Loading =>
                   <View style=Styles.notFoundContentWrapper>
                     <FullLoader mode=Black />
                   </View>
                 }}
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
