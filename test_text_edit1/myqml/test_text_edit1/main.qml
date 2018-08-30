import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import myqml.test_text_edit 1.0

Window {
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("TestTextEdit");
    color: Qt.rgba(0.8,0.8,0.8,1);

    Flickable {
        width :  parent.width ;
        height : parent.height;
        contentHeight: _id_textEdit.height ;
        contentWidth: parent.width ;
        MyTextEdit{
            id : _id_textEdit;
            width: parent.width ;
            objectName: "_id_text_edit";

            textEdit : TextEdit {
                width: parent.width ;
                wrapMode : TextEdit.Wrap;
                readOnly: true;
                selectByMouse : true;
            }

            textFrameDelegate : Rectangle {
                color: Qt.rgba(Math.random()/3+0.5,Math.random()/3+0.5,Math.random()/5+0.5,1)
            }

        }
    }

}

/***************************/
//https://blog.csdn.net/liang19890820/article/details/60466716
//Qt.binding
/***************************/

