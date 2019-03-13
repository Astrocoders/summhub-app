let let_ = (promise, continuation) =>
  Js.Promise.then_(continuation, promise);
