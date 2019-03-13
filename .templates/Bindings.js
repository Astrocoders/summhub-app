const { stripIndent } = require('common-tags')
const chalk = require('chalk')

module.exports.args = {
  name: 'Binding name',
  path: 'Path to the module being imported',
  module: 'Module being imported',
}

module.exports.where = ({ name }) => `re/types/${name}.re`

module.exports.postBuild = () =>
  console.log('✅ ', chalk.green('Bindings successfully created'))

module.exports.gen = ({ path, module = 'default' }) => stripIndent`
open Rebolt;

[@bs.module "${path}"]
external reactClass: ReasonReact.reactClass = "${module}";

let make =
    (
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    children,
  );
`
