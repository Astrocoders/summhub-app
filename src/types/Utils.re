open BsReactNative;
[%bs.raw {|require('numeral/locales/pt-br')|}];

module UserSession = {
  let keyToken = "USER_TOKEN";
  let getToken = AsyncStorage.getItem(keyToken);
  let setToken = token => AsyncStorage.setItem(keyToken, token, ());
  let clearToken = () => AsyncStorage.removeItem(keyToken, ());
};

module Str = {
  /* Check for the Str module from OCaml, this is a temporary workaround */
  let replace': (string, string, string) => string = [%bs.raw
    {|
  function(pattern, replacer, str) {
    return str.replace(new RegExp(pattern, 'g'), replacer)
  }
  |}
  ];
  let replace = (~pattern, ~replacer, str) =>
    replace'(pattern, replacer, str);
  /* Check for the Str module from OCaml, this is a temporary workaround */
  let split': (string, string) => array(string) = [%bs.raw
    {|
  function(delimitter, str) {
    return str.split(delimitter)
  }
  |}
  ];
  let split = (~delimitter, str) => split'(delimitter, str) |> Array.to_list;
  let includes': (string, string) => bool = [%bs.raw
    {|
  function(query, str) {
    return str.toLowerCase().includes(query.toLowerCase())
  }
  |}
  ];
  let includes = (query, str) => includes'(query, str);
  let initials: string => string = [%bs.raw
    {|
  function(str) {
    return str.match(/\b(\w)/g).join('').toUpperCase()
  }
  |}
  ];
  let firstLetter: string => string = [%bs.raw
    {|
  function(str) {
    return str.toUpperCase().match(/(\s|^)([a-z])/gi)
  }
  |}
  ];
};

module Money = {
  module CustomNumeral = {
    type numeral;
    [@bs.module] external numeral: numeral = "numeral";
    [@bs.send] external locale: (numeral, string) => unit = "locale";
  };

  CustomNumeral.(numeral->locale("pt-br"));

  let format = value =>
    NumeralRe.(
      value
      |> float_of_int
      |> (x => x /. 100.)
      |> numeral(Float)
      |> Numeral.format("$0,0.00")
    );

  let formatNumber = format;

  let formatBRL = format;

  let intOfString = string =>
    switch (int_of_string(string)) {
    | exception _ => 0
    | n => n
    };
};

module Date = {
  let toJSON: Js.Date.t => Js.Json.t = [%bs.raw
    {|
  function(date) {
    return date.toJSON()
  }
  |}
  ];
  let fromJSON: Js.Json.t => Js.Date.t = [%bs.raw
    {|
  function(json) {
    return new Date(json)
  }
  |}
  ];
  let formatFullDate = date => {
    let momentWithDate = MomentRe.momentWithDate(date);
    let formatDate = format => MomentRe.Moment.format(format, momentWithDate);
    let day = formatDate("DD");
    let month = formatDate("MMMM");
    let year = formatDate("YYYY");
    let time = formatDate("HH:mm");

    {j|$day de $month de $year às $time|j};
  };
};

let onlyHasNumbers = value =>
  Js.Re.test(value, [%bs.re {|/^\d(?![A-Za-z])/|}]);

let getAppVersion: unit => string = [%bs.raw
  {|
function() {
  const json = require('../../package.json')
  return json.version
}
|}
];

module BrazilStates = {
  [@bs.deriving jsConverter]
  type t = [
    | `AC
    | `AL
    | `AM
    | `AP
    | `BA
    | `CE
    | `DF
    | `ES
    | `GO
    | `MA
    | `MG
    | `MS
    | `MT
    | `PA
    | `PB
    | `PE
    | `PI
    | `PR
    | `RJ
    | `RN
    | `RO
    | `RR
    | `RS
    | `SC
    | `SE
    | `SP
    | `TO
  ];
};

module Linking = {
  let getRoute = url =>
    Js.String.replaceByRe([%bs.re {|/.*?:\/\//g|}], "", url);

  let getParams = route =>
    Js.Re.exec(route, [%bs.re {|/\/([^\/]+)\/?$/|}])
    |> (
      fun
      | Some(result) => Js.Re.captures(result)
      | None => [||]
    )
    |> (
      params =>
        Belt.Array.get(params, 1)
        |> (
          fun
          | Some(param) =>
            param
            |> Js.toOption
            |> (
              fun
              | Some(result) => result
              | None => ""
            )
          | None => ""
        )
    );
};

module FormValidation = {
  let date = (fieldName, getValue) =>
    ReForm.Validation.Custom(
      values =>
        Js.Re.test(getValue(values), [%re "/\d{4}.\d{2}.\d{2}/"])
          ? None : Some(fieldName ++ {j| é inválido|j}),
    );
};

let safeIntOfString = n =>
  switch (int_of_string(n)) {
  | exception _ => None
  | n => Some(n)
  };
