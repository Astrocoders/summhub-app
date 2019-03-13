# SummHub App


## Setup
```
yarn install
```

CocoaPods
```
cd ios/
pod install
```

If you don't have CocoaPods, install with RubyGem

```
gem install cocoapods
```

SummHub App

## Running
```
# IMPORTANT: Use this to run in emulator/device. It execs the right flavor for you.
$ yarn rn:run-android
$ yarn start
```
and
```
yarn bsb -make-world -w
```
in parallel. Also remember to go to Pinkman server and leave it running.


## Releasing

### Generating app icon
Put a icon.png at the root folder and 
```
$ yarn app-icon generate
```

### Android
#### Staging
Run
```
# APP_HOST is the app linking site
APP_HOST=summhub.app yarn android:staging:generate
```
#### Production
Run
```
# APP_HOST is the app linking site
APP_HOST=summhub.app yarn android:release:generate
```

# gen, the simple generator 
Includes bikeshedding protection ™️

## available commands

if you call the gen creator without arguments it'll show to you it's help

```
φ yarn gen Story
yarn run v1.9.2
$ node .bin/gen Story
🤷 No arguments provided. Here's how to use this creator:

--name=value Component name for the story
✨  Done in 0.23s.
```

### yarn gen Story
### yarn gen Scene
### yarn gen Component

###### [Made with ❤️  by Astrocoders](https://astrocoders.com)
