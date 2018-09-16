import QtQuick 2.9


Rectangle{
    color: "red"
    id : _id_red
    property int count : 0;
    Rectangle{
        color: "green"
        anchors.leftMargin :   parent.width*0.1
        anchors.rightMargin :  parent.width*0.1
        anchors.topMargin : parent.height*0.1
        anchors.bottomMargin: parent.height*0.1
        anchors.fill: parent
        id : _id_green
        Rectangle{
            color: "blue"
            anchors.leftMargin : parent.width*0.1
            anchors.rightMargin :  parent.width*0.1
            anchors.topMargin : parent.height*0.1
            anchors.bottomMargin: parent.height*0.1
            anchors.fill: parent
            id : _id_blue
            Keys.onPressed: {
                console.log("blue-" +(_id_red.count++) )
                event.accepted = false ;
            }
            Keys.enabled: true ;
            Keys.forwardTo: [_id_green]
            focus: true ;
            onActiveFocusChanged: console.log( activeFocus?"blue:a":"blue:b" )
        }/*endl*/
        Keys.onPressed: {
            console.log("green")
            event.accepted = false ;
        }
        Keys.enabled: true
        focus: false ;
        //Keys.forwardTo: [_id_red]
        onActiveFocusChanged: console.log( activeFocus?"green:a":"green:b" )
    }/*endl*/
    Keys.onPressed: {
        console.log("red")
        event.accepted = false ;
    }
    Keys.enabled: true
    focus: false ;
    onActiveFocusChanged: console.log( activeFocus?"red:a":"red:b" )
}




/**
//FocusScope
QQuickKeysAttached
qquickitem_p.h
Keyboard Focus in Qt Quick
**/







