open BsReactNative;

module type Config = {type route;};

module HeaderNull = {
  let component = ReasonReact.statelessComponent("HeaderNull");
  let make = (~headerProps as _, _children) => {
    ...component,
    render: _self => ReasonReact.null,
  };
};

module Make = (Config: Config) => {
  module StackNavigatorConfig =
    Nautilus.StackNavigator.CreateStackNavigator(Config);

  module StackNavigator = StackNavigatorConfig.StackNavigator;

  module ModalNavigator = {
    type action =
      | Open(array(Config.route))
      | Close;

    type state = {
      screens: array(Config.route),
      isVisible: bool,
    };

    type navigation = StackNavigator.navigation;

    let component = ReasonReact.reducerComponent("StackModalNavigator");

    let make = (~initialState, ~renderScene, children) => {
      ...component,
      initialState: () => {screens: initialState, isVisible: false},
      reducer: (action, _state) =>
        switch (action) {
        | Open(screens) => Update({screens, isVisible: true})
        | Close => Update({isVisible: false, screens: initialState})
        },
      render: self =>
        <>
          <Modal
            onRequestClose={() => ()}
            visible={self.state.isVisible}
            transparent=true
            animationType=`slide>
            <Overlay>
              <SafeAreaView
                style=Style.(
                  style([flex(1.), backgroundColor(String("transparent"))])
                )>
                <View
                  style=Style.(
                    style([flex(1.), paddingHorizontal(Pt(0.5))])
                  )>
                  <StackNavigator
                    initialState={self.state.screens}
                    headerComponent=HeaderNull.make>
                    ...{(~currentRoute, ~navigation) =>
                      renderScene(
                        ~currentRoute,
                        ~navigation,
                        ~openModal=screens => self.send(Open(screens)),
                        ~closeModal=() => self.send(Close),
                      )
                    }
                  </StackNavigator>
                </View>
              </SafeAreaView>
            </Overlay>
          </Modal>
          {children(~openModal=screen => self.send(Open([|screen|])))}
        </>,
    };
  };
};
