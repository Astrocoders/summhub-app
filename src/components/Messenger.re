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

let component = ReasonReact.statelessComponent("Messenger");

let make = (~style=Style.(style([])), children) => {
  ...component,
  render: _self =>
    <View style={Style.combine(Styles.wrapper, style)}>
      <View> ...children </View>
      <View style=Styles.sendRow>
        <View style=Styles.input>
          <Input
            onChangeText=ignore
            placeholder="Write your message here"
            autoCapitalize=`none
            keyboardType=`default
          />
        </View>
        <TouchableOpacity onPress=ignore>
          <View style=Styles.sendBtn>
            <RNIcons.MaterialCommunityIcons
              name=`_send
              size=24.
              color={AppConfig.theme.contrastWhite}
            />
          </View>
        </TouchableOpacity>
      </View>
    </View>,
};
