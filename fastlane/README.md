fastlane documentation
================
# Installation

Make sure you have the latest version of the Xcode command line tools installed:

```
xcode-select --install
```

Install _fastlane_ using
```
[sudo] gem install fastlane -NV
```
or alternatively using `brew cask install fastlane`

# Available Actions
## iOS
### ios beta
```
fastlane ios beta
```
Sets up a new build for TestFlight

----

## Android
### android bump
```
fastlane android bump
```
Bump build and version numbers
### android buildProduction
```
fastlane android buildProduction
```
Build apk file
### android buildStaging
```
fastlane android buildStaging
```

### android beta
```
fastlane android beta
```
Publish beta build
### android playstore
```
fastlane android playstore
```
Publish release build

----

This README.md is auto-generated and will be re-generated every time [fastlane](https://fastlane.tools) is run.
More information about fastlane can be found on [fastlane.tools](https://fastlane.tools).
The documentation of fastlane can be found on [docs.fastlane.tools](https://docs.fastlane.tools).
