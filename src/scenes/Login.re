open BsReactNative;
open NavigationConfig.OuterApp;

module Styles = {
  open Style;
  let wrapper =
    style([
      backgroundColor(String(AppConfig.theme.backgroundColor)),
      flex(1.),
      justifyContent(Center),
      padding(Pt(30.)),
    ]);
  let logoStyle = style([height(Pt(150.)), marginTop(Pt(10.))]);
  let buttonWrapper = style([marginTop(Pct(10.))]);
};

module RequestSignInLinkParams = {
  type state = {email: string};
  type fields = [ | `email];
  let lens = [(`email, s => s.email, (_s, v) => {email: v})];
};

module RequestSignInLinkForm = ReForm.Create(RequestSignInLinkParams);

module Mutation = [%graphql
  {|
    mutation RequestSignInLinkMutation($input: RequestSignInLinkInput!) {
      requestSignInLink(input: $input) {
        error
      }
    }
|}
];

module RequestSignInLinkMutationContainer =
  ReasonApollo.CreateMutation(Mutation);

let component = ReasonReact.statelessComponent("Login");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen navigation>
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
          <RequestSignInLinkMutationContainer>
            ...{(mutate, _) => c(mutate)}
          </RequestSignInLinkMutationContainer>;

        <RequestSignInLinkForm
          onSubmit={({values, setSubmitting}) =>
            Js.Promise.(
              mutate(
                ~variables=
                  Mutation.make(~input={"email": values.email}, ())##variables,
                (),
              )
              |> then_(result =>
                   RequestSignInLinkMutationContainer.convertJsInputToReason(
                     result,
                   ).
                     data
                   ->Belt.Option.map(data => data##requestSignInLink)
                   ->Belt.Option.map(requestSignInLink =>
                       switch (requestSignInLink##error) {
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
            | None => snackbar.send(Set(Open({j|Email inválido|j})))
            }
          }
          initialState={email: ""}
          i18n=ReForm.Validation.I18n.ptBR
          schema=[
            (
              `email,
              Custom(
                values =>
                  Js.Re.test(values.email, [%bs.re {|/\S+@\S+\.\S+/|}])
                    ? None : Some({j|Email inválido|j}),
              ),
            ),
          ]>
          ...{({handleChange, handleSubmit, form, getErrorForField}) =>
            <View style=Styles.wrapper>
              <Logo mode=Black style=Styles.logoStyle />
              <View style=Styles.buttonWrapper>
                <Input
                  onChangeText={handleChange(`email)}
                  placeholder="Preencha seu e-mail"
                  autoCapitalize=`none
                  keyboardType=`emailAddress
                  value={form.values.email}
                  style=Style.(style([marginBottom(Pt(10.))]))
                />
                <AppButton
                  onPress={_ => handleSubmit()}
                  text="Login"
                  disabled={
                    Belt.Option.isSome(getErrorForField(`email))
                    || String.length(form.values.email) < 0
                  }
                />
              </View>
            </View>
          }
        </RequestSignInLinkForm>;
      }}
    </StackNavigator.Screen>,
};
