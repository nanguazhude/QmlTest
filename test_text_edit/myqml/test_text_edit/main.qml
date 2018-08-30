import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("TestTextEdit");
    color: Qt.rgba(0.3,0.3,0.3,1);

    Rectangle{
        id : _id_background;
        anchors.centerIn: parent;
        width:  Math.max( parent.width,parent.height)*1.5/*rotation: 45*/;
        height: Math.max( parent.width,parent.height)*1.5/*rotation: 45*/;
        gradient: Gradient {
            GradientStop {
                position: 0
                color: Qt.rgba(0.3,0.3,0.3,1)
            }

            GradientStop {
                position: 1
                color: Qt.rgba(0.4,0.4,0.4,1)
            }
        }
        rotation: 45;
        antialiasing : true;
        z : -1;
    }

    TextEdit{
        anchors.fill: parent ;
        id : _id_text_edit;
        objectName: "_id_text_edit";
        font.pointSize : 32;
        Component.onCompleted: { console.log( _id_text_edit ) }
    }
}

/***************************/
//https://blog.csdn.net/liang19890820/article/details/60466716
//Qt.binding
/***************************/

