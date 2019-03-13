open BsReactNative;

module Config = {
  type state =
    | Open(string)
    | Closed;
};

module WithState = ReContainers.WithState.Make(Config);

module Styles = {
  open Style;
  let wrapper = style([flex(1.), width(Pct(100.))]);
  let snackbar = style([backgroundColor(String(AppConfig.theme.primary))]);
  let label = style([color(String(AppConfig.theme.secondary))]);
};

let component = ReasonReact.statelessComponent("Snackbar");

let make = (~action, children) => {
  ...component,
  render: _self =>
    <WithState initialState=Config.Closed>
      ...{
           self =>
             <View style=Styles.wrapper>
               <Paper.Snackbar
                 visible={
                   switch (self.state) {
                   | Open(_message) => true
                   | Closed => false
                   }
                 }
                 style=Styles.snackbar
                 onDismiss={() => self.send(Set(Closed))}
                 action>
                 {
                   switch (self.state) {
                   | Open(message) =>
                     <Text style=Styles.label>
                       {ReasonReact.string(message)}
                     </Text>
                   | Closed => ReasonReact.null
                   }
                 }
               </Paper.Snackbar>
               {children(self)}
             </View>
         }
    </WithState>,
};
