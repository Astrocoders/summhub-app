let active = ref(0);
let registeredCallbacks: Belt.MutableMap.Int.t(unit => unit) =
  Belt.MutableMap.Int.make();

let register = callback => {
  let newIndex = active^ + 1;
  registeredCallbacks->Belt.MutableMap.Int.set(newIndex, callback);
  active := newIndex;

  () => registeredCallbacks->Belt.MutableMap.Int.remove(newIndex);
};

BsReactNative.BackHandler.addEventListener("hardwareBackPress", () => {
  registeredCallbacks->Belt.MutableMap.Int.forEach((key, callback) =>
    active^ == key ? callback() : ()
  );
  true;
});
