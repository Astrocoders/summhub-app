open BsReactNative;

type inputState =
  | Blurred
  | Focused
  | Error;

module Styles = {
  open Style;
  let input = state =>
    style([
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      borderStyle(Solid),
      borderColor(
        switch (state) {
        | Blurred => String(AppConfig.theme.gray)
        | Focused => String(AppConfig.theme.primary)
        | Error => String(AppConfig.theme.error)
        },
      ),
      borderWidth(1.),
      letterSpacing(0.),
      color(String(AppConfig.theme.primary)),
      paddingLeft(Pt(21.)),
      paddingVertical(Pt(18.)),
      paddingRight(Pt(6.)),
      borderRadius(4.),
      textAlignVertical(Top),
    ]);
  let icon = style([position(Absolute), right(Pt(15.)), top(Pt(17.))]);
};

type state = {
  inputRef: ref(option(ReasonReact.reactRef)),
  isFocused: bool,
  hidePassword: bool,
};

type action =
  | Focused
  | Blurred
  | ShowPassword
  | HidePassword;

let setInputRef = (ref_, {ReasonReact.state}) =>
  state.inputRef := Js.Nullable.toOption(ref_);

let component = ReasonReact.reducerComponent("Input");

let make =
    (
      ~onChangeText,
      ~value=?,
      ~placeholder="",
      ~style=Style.(style([])),
      ~error=false,
      ~secureTextEntry=false,
      ~keyboardType=?,
      ~editable=true,
      ~autoCapitalize=?,
      ~multiline=?,
      ~numberOfLines=?,
      _children,
    ) => {
  ...component,
  initialState: () => {
    inputRef: ref(None),
    isFocused: false,
    hidePassword: secureTextEntry,
  },
  reducer: (action, state) =>
    switch (action) {
    | Focused => Update({...state, isFocused: true})
    | Blurred => Update({...state, isFocused: false})
    | ShowPassword =>
      UpdateWithSideEffects(
        {...state, hidePassword: false},
        self =>
          switch (self.state.inputRef^) {
          | Some(inputRef) =>
            ReasonReact.refToJsObj(inputRef)##focus() |> ignore
          | None => ()
          },
      )
    | HidePassword =>
      UpdateWithSideEffects(
        {...state, hidePassword: true},
        self =>
          switch (self.state.inputRef^) {
          | Some(inputRef) =>
            ReasonReact.refToJsObj(inputRef)##focus() |> ignore
          | None => ()
          },
      )
    },
  render: self =>
    <View>
      <TextInput
        style={Style.combine(
          Styles.input(
            error ? Error : self.state.isFocused ? Focused : Blurred,
          ),
          style,
        )}
        placeholder
        onChangeText
        ?value
        ref={self.handle(setInputRef)}
        onFocus={_ => self.send(Focused)}
        onBlur={_ => self.send(Blurred)}
        placeholderTextColor={AppConfig.theme.gray}
        underlineColorAndroid="transparent"
        secureTextEntry={self.state.hidePassword}
        ?keyboardType
        editable
        ?autoCapitalize
        ?multiline
        ?numberOfLines
      />
      {secureTextEntry
         ? <TouchableWithoutFeedback
             onPress={
               self.state.hidePassword
                 ? _ => self.send(ShowPassword)
                 : (_ => self.send(HidePassword))
             }>
             <RNIcons.Ionicons
               name={self.state.hidePassword ? `_iosEye : `_iosEyeOff}
               style=Styles.icon
               size=25.
               color={AppConfig.theme.contrastDark}
             />
           </TouchableWithoutFeedback>
         : ReasonReact.null}
    </View>,
};
