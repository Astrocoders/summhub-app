open AppConfigTypes;
let images =
  BsReactNative.{
    logoDark: `Required(Packager.require("./images/logo_dark.png")),
    logoWhite: `Required(Packager.require("./images/logo_white.png")),
  };

let theme = {
  primary: "#6970E4",
  primary100: "#98DDFE",
  secondary: "#2E3276",
  backgroundColor: "#E6E9F2",
  contrastDark: "#000",
  contrastWhite: "#F3F4F6",
  gray: "#C5C8D0",
  gray100: "#F9F9F9",
  error: "#AC3931",
  disabled: "#A1AAB4",
  transparent: "transparent",
};

let name = "SummHub";
