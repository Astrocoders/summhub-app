open BsReactNative;

let data = {"name": "Foo", "age": 12};

Storybook.(
  storiesOf("Notification", module_)
  |> add("default", () => <Notification />)
  |> add("notification share", () =>
       <View style=Style.(style([flex(1.)]))>
         <NotificationShare
           title={j|Notificação 012345|j}
           eventId="AKDJF19939399291DKD"
           date={Js.Date.make() |> Js.Date.toString}
           fields=[|
             Title("Who?"),
             Field({label: "Name", value: "Gabriel Rubens"}),
             Field({label: "Email", value: "grsabreu@gmail.com"}),
             Field({label: "Project", value: "Itau"}),
             Title("When?"),
             Field({label: "Event Time", value: "7 dec 22:21"}),
           |]
           data
         />
       </View>
     )
);
