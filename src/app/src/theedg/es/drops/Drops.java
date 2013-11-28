package theedg.es.drops;

import theedg.es.drops.DropsJNI;

public class Drops {

  public Drops() {
    this("/sdcard/DCIM");
  }

  public Drops(String watchDirectory) {
    dropsJNI = new DropsJNI();
    directory = watchDirectory;
  }

  public void start() {
    self = dropsJNI.start(directory);
  }

  public void stop() {
    dropsJNI.stop(self);
  }

  private DropsJNI dropsJNI;
  private String directory;
  private long self;

}
