
import QtTest 1.0
import QtQuick 2.1

import QmlDrops 1.0


TestCase {
  id: test
  name: "QmlDrops"
  
  function test_test() {
    var verbose = false
    QmlDrops.test(verbose)
  }
}

