open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([flex(1.), paddingHorizontal(Pt(20.))]);
  let sendRow =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      marginBottom(Pt(10.)),
      marginTop(Pt(20.)),
    ]);
  let input = style([width(Pct(80.))]);
  let sendBtn =
    style([
      alignItems(Center),
      backgroundColor(String(AppConfig.theme.primary)),
      borderRadius(50.),
      display(Flex),
      justifyContent(Center),
      paddingHorizontal(Pt(12.)),
      paddingVertical(Pt(10.)),
      marginLeft(Pt(10.)),
    ]);
};

module SendMessageParams = {
  type state = {
    message: string,
    notificationId: string,
  };
  type fields = [ | `message | `notificationId];
  let lens = [
    (`message, state => state.message, (s, v) => {...s, message: v}),
    (
      `notificationId,
      state => state.notificationId,
      (s, v) => {...s, notificationId: v},
    ),
  ];
};

module SendMessageForm = ReForm.Create(SendMessageParams);

module Mutation = [%graphql
  {|
    mutation SendMessageMutation($input: SendMessageInput!) {
      sendMessage(input: $input) {
        error
        message {
          id
          email
        }
      }
    }
|}
];

module SendMessageContainer = ReForm.Create(SendMessageParams);

module SendMessageMutationContainer = ReasonApollo.CreateMutation(Mutation);

let component = ReasonReact.statelessComponent("Messenger");

let make = (~style=Style.(style([])), children) => {
  ...component,
  render: _self => {
    let%Epitath snackbar = c =>
      <Snackbar
        action={Paper.Snackbar.snackbarAction(
          ~label="Fechar",
          ~onPress=ignore,
        )}>
        ...c
      </Snackbar>;

    let%Epitath mutate = c =>
      <SendMessageMutationContainer>
        ...{(mutate, _) => c(mutate)}
      </SendMessageMutationContainer>;

    <SendMessageContainer
      onSubmit={({values, setSubmitting}) =>
        Js.Promise.(
          mutate(
            ~variables=
              Mutation.make(
                ~input={
                  "message": values.message,
                  "notificationId": values.notificationId,
                },
                (),
              )##variables,
            (),
          )
          |> then_(result =>
               SendMessageMutationContainer.convertJsInputToReason(result).
                 data
               ->Belt.Option.map(data => data##sendMessage)
               ->Belt.Option.map(sendMessage =>
                   switch (sendMessage##error) {
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
          snackbar.send(Set(Open(Belt.Option.getWithDefault(error, ""))))
        | None =>
          snackbar.send(
            Set(
              Open(
                {j|Não foi possível enviar sua mensagem, por favor tente novamente|j},
              ),
            ),
          )
        }
      }
      initialState={message: "", notificationId: ""}
      i18n=ReForm.Validation.I18n.ptBR
      schema=[(`message, Required), (`notificationId, Required)]>
      ...{({handleChange, handleSubmit, form}) =>
        <View style={Style.combine(Styles.wrapper, style)}>
          <View> ...children </View>
          <View style=Styles.sendRow>
            <View style=Styles.input>
              <Input
                onChangeText={handleChange(`message)}
                placeholder="Write your message here"
                autoCapitalize=`none
                keyboardType=`default
                value={form.values.message}
              />
            </View>
            <TouchableOpacity onPress={_ => handleSubmit()}>
              <View style=Styles.sendBtn>
                <RNIcons.MaterialCommunityIcons
                  name=`_send
                  size=24.
                  color={AppConfig.theme.contrastWhite}
                />
              </View>
            </TouchableOpacity>
          </View>
        </View>
      }
    </SendMessageContainer>;
  },
};
