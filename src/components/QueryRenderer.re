open BsReactNative;

module Styles = {
  open Style;
  let errorWrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.secondary)),
      paddingHorizontal(Pt(20.)),
      ...AppTheme.Helpers.fullCenter,
    ]);

  let text =
    style([color(String(AppConfig.theme.primary)), textAlign(Center)]);

  let retry = style([minWidth(Pt(200.)), marginTop(Pt(40.))]);
};

let component = ReasonReact.statelessComponent("QueryRenderer");

let make =
    (
      ~result: ReasonApolloTypes.queryResponse('a),
      ~refetch,
      ~renderLoader=() => <FullLoader mode=Black />,
      children,
    ) => {
  ...component,
  render: _self =>
    switch (result) {
    | Error(error) =>
      <View style=Styles.errorWrapper>
        <Egg
          setps="TTTT"
          onCatch={() => {
            let formatError: ReasonApolloTypes.apolloError => string = [%bs.raw
              {|
                function(error) {
                  return process.env.SERVER_LOCATION + JSON.stringify(error, null, 1)
                }
              |}
            ];
            Alert.alert(~title="Error", ~message=formatError(error), ());
          }}>
          <Title
            value={j|Infelizmente, nosso servidor não foi capaz de completar essa operação|j}
            style=Styles.text
          />
        </Egg>
        <AppButton
          onPress={_ => refetch(None) |> ignore}
          text="Tentar novamente"
          style=Styles.retry
        />
      </View>

    | Loading => renderLoader()
    | Data(data) => children(data)
    },
};
