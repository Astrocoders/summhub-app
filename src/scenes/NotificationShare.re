open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([flex(1.), backgroundColor(String("#fff"))]);
  let body = style([padding(Pt(20.))]);
  let footer = style([marginTop(Pt(15.)), alignItems(Center)]);
};

type field = {
  label: string,
  value: string,
};

type info =
  | Field(field)
  | Title(string);

let component = ReasonReact.statelessComponent("NotificationShare");

let make = (~title, ~eventId, ~date, ~fields, _children) => {
  ...component,
  render: _self => {
    let additionalFields =
      fields->Belt.Array.map(info =>
        switch (info) {
        | Field({label, value}) => <InfoField key=label label value />
        | Title(value) => <Title value />
        }
      );
    <View style=Styles.wrapper>
      <Shottable>
        ...{(~capture, ~renderShottable) =>
          <View>
            {renderShottable(() =>
               <View>
                 <AppBar
                   title
                   renderLeft={_ => <BackButton onPress=ignore />}
                   renderRight={_ =>
                     <TouchableOpacity
                       hitSlop={
                         "top": 30,
                         "bottom": 30,
                         "left": 40,
                         "right": 40,
                       }
                       onPress={() =>
                         Js.Promise.(
                           capture()
                           |> then_(uri =>
                                RNShare.openDialog(
                                  RNShare.openOptions(
                                    ~url=uri,
                                    ~title="Comprovante",
                                    ~failOnCancel=false,
                                    (),
                                  ),
                                )
                                |> resolve
                              )
                           |> ignore
                         )
                       }>
                       <ShareButton />
                     </TouchableOpacity>
                   }
                 />
                 <ScrollView style=Styles.body>
                   <Title value="What happened?" />
                   {ReasonReact.array(additionalFields)}
                   <InfoField label="Event ID" value=eventId />
                   <View style=Styles.footer>
                     <AppText
                       style=Style.(style([fontSize(Float(12.))]))
                       value={
                         "Notification Triggered at "
                         ++ Utils.Date.formatFullDate(
                              Js.Date.fromString(date),
                            )
                       }
                     />
                     <Logo
                       mode=Black
                       style=Style.(
                         style([height(Pt(80.)), width(Pt(120.))])
                       )
                     />
                   </View>
                 </ScrollView>
               </View>
             )}
          </View>
        }
      </Shottable>
    </View>;
  },
};
