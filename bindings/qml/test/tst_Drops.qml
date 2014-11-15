
import QtTest 1.0
import QtQuick 2.1

import QmlDrops 1.0


TestCase {
  id: test
  name: "Drops"
  
  Drops {
    id: subject
    path: "/tmp/drops_test"
  }
  
  function test_it() {
    compare(subject.running, false)
    
    subject.start()
    compare(subject.running, true)
    
    wait(1000)
    
    subject.stop()
    compare(subject.running, false)
  }
}
