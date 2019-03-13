module OrganizationModals = {
  type route =
    | OrganizationView;
};

include StackModalNavigator.Make(OrganizationModals);
