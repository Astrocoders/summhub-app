package com.summhub;

import android.app.Application;

import com.facebook.react.ReactApplication;
import fr.greweb.reactnativeviewshot.RNViewShotPackage;
import com.entria.views.RNViewOverflowPackage;
import com.oblador.vectoricons.VectorIconsPackage;
import org.devio.rn.splashscreen.SplashScreenReactPackage;
import cl.json.RNSharePackage;
import com.reactnative.photoview.PhotoViewPackage;
import com.BV.LinearGradient.LinearGradientPackage;
import com.reactnative.ivpusic.imagepicker.PickerPackage;
import com.swmansion.gesturehandler.react.RNGestureHandlerPackage;
import com.RNFetchBlob.RNFetchBlobPackage;
import org.reactnative.camera.RNCameraPackage;
import com.cmcewen.blurview.BlurViewPackage;
import com.facebook.react.ReactNativeHost;
import com.facebook.react.ReactPackage;
import com.facebook.react.shell.MainReactPackage;
import com.facebook.soloader.SoLoader;

import java.util.Arrays;
import java.util.List;

public class MainApplication extends Application implements ReactApplication {

  private final ReactNativeHost mReactNativeHost = new ReactNativeHost(this) {
    @Override
    public boolean getUseDeveloperSupport() {
      return BuildConfig.DEBUG;
    }

    @Override
    protected List<ReactPackage> getPackages() {
      return Arrays.<ReactPackage>asList(
          new MainReactPackage(),
            new RNFetchBlobPackage(),
            new RNViewShotPackage(),
            new RNViewOverflowPackage(),
            new VectorIconsPackage(),
            new SplashScreenReactPackage(),
            new RNSharePackage(),
            new PhotoViewPackage(),
            new LinearGradientPackage(),
            new PickerPackage(),
            new RNGestureHandlerPackage(),
            new RNCameraPackage(),
            new BlurViewPackage()
      );
    }

    @Override
    protected String getJSMainModuleName() {
      return "index";
    }
  };

  @Override
  public ReactNativeHost getReactNativeHost() {
    return mReactNativeHost;
  }

  @Override
  public void onCreate() {
    super.onCreate();
    SoLoader.init(this, /* native exopackage */ false);
  }
}
