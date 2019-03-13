open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String(AppConfig.theme.backgroundColor)),
    ]);

  let fieldsWrapper =
    style([marginTop(Pt(30.)), paddingHorizontal(Pt(20.))]);

  let tagWrapper =
    style([
      backgroundColor(String(AppConfig.theme.contrastWhite)),
      borderRadius(0.),
      color(String(AppConfig.theme.contrastDark)),
      marginLeft(Pt(0.)),
      marginRight(Pt(10.)),
    ]);
  let content =
    style([alignItems(FlexEnd), flexDirection(Column), width(Pct(90.))]);

  let contentTitle = style([fontSize(Float(16.))]);

  let contentDetail = style([fontSize(Float(14.))]);

  let buttonWrapper = style([marginTop(Pct(10.))]);
};

let component = ReasonReact.statelessComponent("OrganizationView");

let make =
    (
      ~navigation: OrganizationModalNavigatorConfig.ModalNavigator.navigation,
      ~closeModal,
      _children,
    ) => {
  ...component,
  render: _self =>
    <OrganizationModalNavigatorConfig.StackNavigator.Screen navigation>
      ...{() =>
        <View style=Styles.wrapper>
          <AppBar
            title="Organization"
            renderLeft={_ => <BackButton onPress={_ => closeModal()} />}
            renderRight={_ => <DeleteButton onPress={_ => closeModal()} />}
          />
          <View style=Styles.fieldsWrapper>
            <Input
              onChangeText=ignore
              placeholder="Nome"
              autoCapitalize=`words
              keyboardType=`default
              value="Astrocoders"
              style=Style.(style([marginBottom(Pt(10.))]))
            />
            <SectionTitle value="Members" />
            <RNTags
              tagContainerStyle=Styles.tagWrapper
              inputPlaceholderColor="#B1B1B1"
              initialTags=[|"guilherme.decampo@astrocoders.com", "test"|]
              readonly=true
            />
            <SectionTitle value="Projects" />
          </View>
          <AppList
            renderItems={_ =>
              <ScrollView>
                <ListItem
                  onPress=ignore
                  renderLeft={_ =>
                    <Title value={j|Itaú|j} style=Styles.contentTitle />
                  }
                  renderCenter={_ =>
                    <View style=Styles.content>
                      <AppText
                        value="123 members"
                        style=Styles.contentDetail
                      />
                      <AppText value="4 projects" style=Styles.contentDetail />
                    </View>
                  }
                  renderRight={_ => <ListItemMoreInfo direction=Right />}
                />
              </ScrollView>
            }
          />
          <AppFAB
            icon={
              Element(
                _ =>
                  <RNIcons.MaterialCommunityIcons
                    name=`_plus
                    size=24.
                    color={AppConfig.theme.contrastWhite}
                  />,
              )
            }
            small=true
          />
        </View>
      }
    </OrganizationModalNavigatorConfig.StackNavigator.Screen>,
};
