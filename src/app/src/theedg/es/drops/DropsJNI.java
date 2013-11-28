package theedg.es.drops;

public class DropsJNI {
  static {
    System.loadLibrary("drops-jni");
  }

  public native long start(String directory);
  public native void stop(long self);

}
