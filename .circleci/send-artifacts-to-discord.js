const fetch = require('node-fetch')

const SLEEP_SECONDS = 10000
const PROJECT = process.env.CIRCLE_PROJECT_REPONAME
const USERNAME = process.env.CIRCLE_PROJECT_USERNAME
const VCS_TYPE = 'github'

setTimeout(() => {
  fetch(
    `https://circleci.com/api/v1.1/project/${VCS_TYPE}/${USERNAME}/${PROJECT}/${
      process.env.CIRCLE_BUILD_NUM
    }/artifacts?circle-token=${process.env.CIRCLE_TOKEN}`,
  )
    .then(res => res.json())
    .then(data => {
      const artifact = data[0]

      console.log(artifact)

      if (!artifact) return

      fetch(process.env.DISCORD_WEBHOOK, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          embeds: [
            {
              title: artifact.path,
              url: artifact.url,
              description: `Project: ${PROJECT} - Build Number: ${
                process.env.CIRCLE_BUILD_NUM
              }`,
              author: { name: 'CircleCI Bot' },
            },
          ],
        }),
      }).catch(err => console.log('Something went wrong!', err))
    })
    .catch(err => console.log('Something went wrong!', err))
}, SLEEP_SECONDS)
