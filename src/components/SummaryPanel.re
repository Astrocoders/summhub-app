open BsReactNative;

module Styles = {
  open Style;

  let wrapper =
    style([
      backgroundColor(String(AppConfig.theme.primary)),
      borderRadius(10.),
      height(Pt(100.)),
      padding(Pt(15.)),
      margin(Pt(20.)),
    ]);

  let summaryTitleWrapper =
    style([
      alignItems(Baseline),
      color(String(AppConfig.theme.contrastWhite)),
      flexDirection(Row),
      justifyContent(FlexStart),
      marginBottom(Pt(10.)),
    ]);

  let title =
    style([
      color(String(AppConfig.theme.contrastWhite)),
      fontWeight(`_500),
      fontSize(Float(16.)),
    ]);

  let dateTitle =
    style([
      color(String(AppConfig.theme.primary100)),
      fontWeight(`_500),
      fontSize(Float(16.)),
      marginHorizontal(Pt(10.)),
    ]);

  let columnTitle =
    style([
      color(String(AppConfig.theme.contrastWhite)),
      fontWeight(`_500),
      fontSize(Float(12.)),
    ]);
  let columnContent =
    style([
      color(String(AppConfig.theme.contrastWhite)),
      fontSize(Float(20.)),
      fontWeight(`_700),
    ]);

  let columnsWrapper =
    style([
      alignItems(Baseline),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      marginBottom(Pt(25.)),
    ]);

  let columnWrapper = style([marginRight(Pt(15.))]);
};

let component = ReasonReact.statelessComponent("SummaryPanel");

let make =
    (
      ~onPress,
      ~date,
      ~unread,
      ~projectsCount,
      ~organizationsCount,
      ~totalNotifications,
      ~style=Style.(style([])),
      _children,
    ) => {
  ...component,
  render: _self =>
    <Paper.Card style={Style.combine(Styles.wrapper, style)}>
      <TouchableOpacity onPress>
        <View style=Styles.summaryTitleWrapper>
          <AppText value="Today" style=Styles.title />
          <AppText value=date style=Styles.dateTitle />
        </View>
        <View style=Styles.columnsWrapper>
          <View style=Styles.columnWrapper>
            <AppText
              value={
                string_of_int(unread)
                ++ "/"
                ++ string_of_int(totalNotifications)
              }
              style=Styles.columnContent
            />
            <AppText value="Notifications" style=Styles.columnTitle />
          </View>
          <View style=Styles.columnWrapper>
            <AppText
              value={string_of_int(projectsCount)}
              style=Styles.columnContent
            />
            <AppText value="Projects" style=Styles.columnTitle />
          </View>
          <View style=Styles.columnWrapper>
            <AppText
              value={string_of_int(organizationsCount)}
              style=Styles.columnContent
            />
            <AppText value="Organizations" style=Styles.columnTitle />
          </View>
        </View>
      </TouchableOpacity>
    </Paper.Card>,
};
