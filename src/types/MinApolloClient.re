type apolloClient = {
  .
  "resetStore": [@bs.meth] (unit => Js.Promise.t(unit)),
};

[@bs.module "../../apollo"] external apolloClient: apolloClient = "default";

let resetStore = () => apolloClient##resetStore();
