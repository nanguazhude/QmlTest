import SSTDQml 1.0
import QtQuick 2.9

Rectangle{

    width : 500 ;
    height: 500 ;

    TestAny {
        z : 10 ;
        width : 12 ;
        height : 12 ;
        anchors.centerIn: parent;
    }

    MyRectangle {
        anchors.fill: parent;
        fillColor : Qt.rgba(1,0,0,1);
        Component.onCompleted: { console.log( testValue.toString() ) }
    }

}

