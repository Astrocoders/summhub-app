open BsReactNative;

type state = {isVisible: bool};

type action =
  | OpenModal
  | CloseModal;

let component = ReasonReact.reducerComponent("AppModal");

let make =
    (
      ~title,
      ~renderContent,
      ~renderActions=(~setVisibility as _) => ReasonReact.null,
      ~renderTrigger,
      ~isDismissable=true,
      _children,
    ) => {
  ...component,
  initialState: () => {isVisible: false},
  reducer: (action, _state) =>
    switch (action) {
    | OpenModal => ReasonReact.Update({isVisible: true})
    | CloseModal => ReasonReact.Update({isVisible: false})
    },
  render: self =>
    <View>
      <Paper.Dialog
        dismissable=isDismissable
        visible={self.state.isVisible}
        onDismiss={() => self.send(CloseModal)}>
        <Paper.Dialog.Title>
          <Text> {title |> ReasonReact.string} </Text>
        </Paper.Dialog.Title>
        <Paper.Dialog.Content>
          <View> {renderContent(~setVisibility=self.send)} </View>
        </Paper.Dialog.Content>
        <Paper.Dialog.Actions>
          {renderActions(~setVisibility=self.send)}
        </Paper.Dialog.Actions>
      </Paper.Dialog>
      {renderTrigger(~setVisibility=self.send)}
    </View>,
};
