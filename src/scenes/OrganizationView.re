open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);

  let fieldsWrapper =
    style([marginTop(Pt(30.)), paddingHorizontal(Pt(20.))]);

  let tagWrapper =
    style([
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      borderRadius(0.),
      color(String(AppConfig.theme.contrastDark)),
      marginLeft(Pt(0.)),
      marginRight(Pt(10.)),
    ]);
  let content =
    style([alignItems(FlexEnd), flexDirection(Column), width(Pct(90.))]);

  let contentTitle = style([fontSize(Float(16.))]);

  let contentDetail = style([fontSize(Float(14.))]);

  let buttonWrapper = style([marginTop(Pct(10.))]);
};

module OrganizationFormParams = {
  type state = {name: string};
  type fields = [ | `name];
  let lens = [(`name, s => s.name, (_s, v) => {name: v})];
};

module OrganizationForm = ReForm.Create(OrganizationFormParams);

module UpdateOrganizationNameMutation = [%graphql
  {|
    mutation UpdateOrganizationName($input: UpdateOrganizationNameInput!) {
      updateOrganizationName(input: $input) {
        error
        organization {
          id
          name
        }
      }
    }
  |}
];

module UpdateOrganizationNameMutationContainer =
  ReasonApollo.CreateMutation(UpdateOrganizationNameMutation);

module RemoveOrganizationMutation = [%graphql
  {|
    mutation RemoveOrganization($input: RemoveOrganizationInput!) {
      removeOrganization(input: $input) {
        error
      }
    }
  |}
];

module RemoveOrganizationMutationContainer =
  ReasonApollo.CreateMutation(RemoveOrganizationMutation);

module StateConfig = {
  type state = {tags: array(string)};
};

module State = ReContainers.WithState.Make(StateConfig);

let component = ReasonReact.statelessComponent("OrganizationView");

let make =
    (
      ~organizationId,
      ~navigation: OrganizationModalNavigatorConfig.ModalNavigator.navigation,
      ~closeModal,
      _children,
    ) => {
  ...component,
  render: _self => {
    <OrganizationModalNavigatorConfig.StackNavigator.Screen navigation>
      ...{() => {
        let%Epitath snackbar = c =>
          <Snackbar
            action={Paper.Snackbar.snackbarAction(
              ~label="Fechar",
              ~onPress=ignore,
            )}>
            ...c
          </Snackbar>;

        let%Epitath mutate = c =>
          <UpdateOrganizationNameMutationContainer>
            ...{(mutate, _) => c(mutate)}
          </UpdateOrganizationNameMutationContainer>;

        let%Epitath removeOrganization = c =>
          <RemoveOrganizationMutationContainer>
            ...{(mutate, _) => c(mutate)}
          </RemoveOrganizationMutationContainer>;

        <OrganizationForm
          onSubmit={({values, setSubmitting}) =>
            Js.Promise.(
              mutate(
                ~variables=
                  UpdateOrganizationNameMutation.make(
                    ~input={
                      "name": values.name,
                      "organizationId": organizationId,
                    },
                    (),
                  )##variables,
                (),
              )
              |> then_(result =>
                   UpdateOrganizationNameMutationContainer.convertJsInputToReason(
                     result,
                   ).
                     data
                   ->Belt.Option.map(data => data##updateOrganizationName)
                   ->Belt.Option.map(updateOrganizationName =>
                       switch (updateOrganizationName##error) {
                       | Some(error) =>
                         snackbar.send(Set(Open(error)));
                         Js.Promise.resolve();
                       | _ =>
                         snackbar.send(
                           Set(
                             Open(
                               {j|Infelizmente, nosso servidor não conseguiu processar essa requisição. Por favor, tente novamente.|j},
                             ),
                           ),
                         );
                         Js.Promise.resolve();
                       }
                     )
                   ->Belt.Option.getWithDefault(Js.Promise.resolve())
                 )
              |> then_(() => setSubmitting(false) |> Js.Promise.resolve)
              |> ignore
            )
          }
          onSubmitFail={errors =>
            switch (Belt.List.head(errors)) {
            | Some((_field, error)) =>
              snackbar.send(
                Set(Open(Belt.Option.getWithDefault(error, ""))),
              )
            | None =>
              snackbar.send(
                Set(
                  Open({j|Não foi possível processar essa alteração|j}),
                ),
              )
            }
          }
          initialState={name: ""}
          i18n=ReForm.Validation.I18n.ptBR
          schema=[(`name, Required)]>
          ...{({handleChange, form}) =>
            <View style=Styles.wrapper>
              <AppBar
                title="Organization"
                renderLeft={_ => <BackButton onPress={_ => closeModal()} />}
                renderRight={_ =>
                  <DeleteButton
                    onPress={() =>
                      Js.Promise.(
                        removeOrganization(
                          ~variables=
                            RemoveOrganizationMutation.make(
                              ~input={"organizationId": organizationId},
                              (),
                            )##variables,
                          (),
                        )
                        |> then_(result =>
                             RemoveOrganizationMutationContainer.convertJsInputToReason(
                               result,
                             ).
                               data
                             ->Belt.Option.map(data =>
                                 data##removeOrganization
                               )
                             ->Belt.Option.map(removeOrganization =>
                                 switch (removeOrganization##error) {
                                 | Some(error) =>
                                   snackbar.send(Set(Open(error)));
                                   Js.Promise.resolve();
                                 | _ =>
                                   snackbar.send(
                                     Set(
                                       Open(
                                         {j|Infelizmente, nosso servidor não conseguiu processar essa requisição. Por favor, tente novamente.|j},
                                       ),
                                     ),
                                   );
                                   Js.Promise.resolve();
                                 }
                               )
                             ->Belt.Option.getWithDefault(
                                 Js.Promise.resolve(),
                               )
                           )
                        |> then_(() =>
                             snackbar.send(
                               Set(Open({j|Organização Deletada|j})),
                             )
                             |> Js.Promise.resolve
                           )
                        |> ignore
                      )
                    }
                  />
                }
              />
              <View style=Styles.fieldsWrapper>
                <Input
                  onChangeText={handleChange(`name)}
                  placeholder="Nome"
                  autoCapitalize=`words
                  keyboardType=`default
                  value={form.values.name}
                  style=Style.(style([marginBottom(Pt(10.))]))
                />
                <SectionTitle value="Members" />
                <RNTags
                  tagContainerStyle=Styles.tagWrapper
                  inputPlaceholderColor="#B1B1B1"
                  initialTags=[|"guilherme.decampo@astrocoders.com", "test"|]
                  readonly=true
                />
                <SectionTitle value="Projects" />
              </View>
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
            </View>
          }
        </OrganizationForm>;
      }}
    </OrganizationModalNavigatorConfig.StackNavigator.Screen>;
  },
};
