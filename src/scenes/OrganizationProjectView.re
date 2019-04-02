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

module OrganizationProjectFormParams = {
  type state = {name: string};
  type fields = [ | `name];
  let lens = [(`name, s => s.name, (_s, v) => {name: v})];
};

module OrganizationProjectForm = ReForm.Create(OrganizationProjectFormParams);

module UpdateOrganizationProjectNameMutation = [%graphql
  {|
    mutation UpdateOrganizationProjectName($input: UpdateOrganizationProjectNameInput!) {
      updateOrganizationProjectName(input: $input) {
        error
        project {
          id
          name
          webhook
        }
      }
    }
  |}
];

module UpdateOrganizationProjectNameMutationContainer =
  ReasonApollo.CreateMutation(UpdateOrganizationProjectNameMutation);

module RemoveOrganizationProjectMutation = [%graphql
  {|
    mutation RemoveOrganizationProject($input: RemoveOrganizationProjectInput!) {
      removeOrganizationProject(input: $input) {
        error
      }
    }
  |}
];

module RemoveOrganizationProjectMutationContainer =
  ReasonApollo.CreateMutation(RemoveOrganizationProjectMutation);

let component = ReasonReact.statelessComponent("OrganizationProjectView");

let make =
    (
      ~organizationId,
      ~projectId,
      ~navigation: OrganizationModalNavigatorConfig.ModalNavigator.navigation,
      ~closeModal,
      _children,
    ) => {
  ...component,
  render: _self => {
    <OrganizationModalNavigatorConfig.StackNavigator.Screen navigation>
      ...{() => {
        let%Hook snackbar =
          Snackbar.make(
            ~action={
              Paper.Snackbar.snackbarAction(~label="Fechar", ~onPress=ignore);
            },
          );

        let%Epitath mutate = c =>
          <UpdateOrganizationProjectNameMutationContainer>
            ...{(mutate, _) => c(mutate)}
          </UpdateOrganizationProjectNameMutationContainer>;

        let%Epitath removeOrganizationProject = c =>
          <RemoveOrganizationProjectMutationContainer>
            ...{(mutate, _) => c(mutate)}
          </RemoveOrganizationProjectMutationContainer>;

        <OrganizationProjectForm
          onSubmit={({values, setSubmitting}) =>
            Js.Promise.(
              mutate(
                ~variables=
                  UpdateOrganizationProjectNameMutation.make(
                    ~input={"name": values.name, "projectId": projectId},
                    (),
                  )##variables,
                (),
              )
              |> then_(result =>
                   UpdateOrganizationProjectNameMutationContainer.convertJsInputToReason(
                     result,
                   ).
                     data
                   ->Belt.Option.map(data =>
                       data##updateOrganizationProjectName
                     )
                   ->Belt.Option.map(updateOrganizationProjectName =>
                       switch (updateOrganizationProjectName##error) {
                       | Some(error) =>
                         snackbar.send(Set(Open(error)));
                         Js.Promise.resolve();
                       | _ =>
                         snackbar.send(
                           Set(
                             Open(
                               "Unfortunately, our server was unable to process this request. Please try again.",
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
              snackbar.send(Set(Open("This change could not be processed")))
            }
          }
          initialState={name: ""}
          i18n=ReForm.Validation.I18n.ptBR
          schema=[(`name, Required)]>
          ...{({handleChange, form}) =>
            <View style=Styles.wrapper>
              <AppBar
                title="Project"
                renderLeft={_ => <BackButton onPress={_ => closeModal()} />}
                renderRight={_ =>
                  <DeleteButton
                    onPress={() =>
                      Js.Promise.(
                        removeOrganizationProject(
                          ~variables=
                            RemoveOrganizationProjectMutation.make(
                              ~input={
                                "organizationId": organizationId,
                                "projectId": projectId,
                              },
                              (),
                            )##variables,
                          (),
                        )
                        |> then_(result =>
                             RemoveOrganizationProjectMutationContainer.convertJsInputToReason(
                               result,
                             ).
                               data
                             ->Belt.Option.map(data =>
                                 data##removeOrganizationProject
                               )
                             ->Belt.Option.map(removeOrganizationProject =>
                                 switch (removeOrganizationProject##error) {
                                 | Some(error) =>
                                   snackbar.send(Set(Open(error)));
                                   Js.Promise.resolve();
                                 | _ =>
                                   snackbar.send(
                                     Set(Open("Project Deleted")),
                                   );
                                   Js.Promise.resolve();
                                 }
                               )
                             ->Belt.Option.getWithDefault(
                                 Js.Promise.resolve(),
                               )
                           )
                        |> catch(_ => resolve())
                        |> ignore
                      )
                    }
                  />
                }
              />
              <View style=Styles.fieldsWrapper>
                <Webhook text="https://summ.link/234234234234" />
                <Input
                  onChangeText={handleChange(`name)}
                  placeholder="Nome"
                  autoCapitalize=`words
                  keyboardType=`default
                  value={form.values.name}
                  style=Style.(style([marginBottom(Pt(10.))]))
                />
              </View>
            </View>
          }
        </OrganizationProjectForm>;
      }}
    </OrganizationModalNavigatorConfig.StackNavigator.Screen>;
  },
};
