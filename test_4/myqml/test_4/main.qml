import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Particles 2.11
import QtGraphicalEffects 1.0

import SSTDQml 1.0

Rectangle{
    width : 500 ;
    height: 500 ;

    MyRectangle{
        anchors.fill: parent;
        fillColor : Qt.rgba(1,0,0,1);
        Component.onCompleted: { console.log(  testValue.toString()  ) }
    }

    TestAny{
        anchors.fill : parent;
        font.pointSize : 52;
    }

}


