
import QtQuick 2.1
import QmlDrops 1.0


Item {
  id: root
  
  QtObject {
    id: priv
    property QmlDrops self
  }
  
  property string path: "/tmp/drops"
  property bool running: false
  
  function start() {
    priv.self = QmlDrops.construct(path)
    running = true
  }
  
  function stop() {
    QmlDrops.destruct(priv.self)
    running = false
  }
  
  Component.onDestruction: stop()
}
