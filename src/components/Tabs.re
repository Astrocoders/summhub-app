open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([width(Pct(100.))]);
  let tabsWrapper =
    style([
      alignItems(Center),
      flexDirection(Row),
      justifyContent(SpaceBetween),
    ]);
  let tabWrapper = style([alignItems(Center), marginHorizontal(Pt(15.))]);
  let tabLabel = (~isActive) =>
    style([
      color(
        isActive
          ? String(AppConfig.theme.contrastWhite)
          : String(AppConfig.theme.primary),
      ),
    ]);
};

type state = {tabActive: int};

type action =
  | SetTabActive(int);

type tab = {
  label: string,
  renderContent: unit => ReasonReact.reactElement,
};

let component = ReasonReact.reducerComponent("Tabs");

let make = (~tabs: list(tab), _children) => {
  ...component,
  initialState: () => {tabActive: 0},
  reducer: (action, _state) =>
    switch (action) {
    | SetTabActive(newTab) => Update({tabActive: newTab})
    },
  render: self =>
    <View style=Styles.wrapper>
      <ScrollView
        contentContainerStyle=Styles.tabsWrapper
        horizontal=true
        showsHorizontalScrollIndicator=false>
        {List.mapi(
           (index, tab) =>
             <Tab
               style=Styles.tabWrapper
               labelStyle=Styles.tabLabel
               key={string_of_int(index)}
               label={tab.label}
               onPress={_ => self.send(SetTabActive(index))}
               isActive={index == self.state.tabActive}
             />,
           tabs,
         )
         |> Array.of_list
         |> ReasonReact.array}
      </ScrollView>
      {Belt.List.get(tabs, self.state.tabActive)
       |> (
         fun
         | Some(tab) => tab.renderContent()
         | None => ReasonReact.null
       )}
    </View>,
};
