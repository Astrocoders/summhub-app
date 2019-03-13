const { stripIndent } = require('common-tags')
const chalk = require('chalk')

module.exports.args = { name: 'Component name for the story' }

module.exports.where = ({ name }) => `storybook/stories/${name}Stories.re`

module.exports.postBuild = () =>
  console.log(
    '✅ ',
    chalk.green('Now require your story in storybook/stories/index'),
  )

module.exports.gen = ({ name }) => stripIndent`
open Rebolt;

Storybook.(
  storiesOf("${name}", module_)
  |> add("default", () => <${name} />)
);
`
