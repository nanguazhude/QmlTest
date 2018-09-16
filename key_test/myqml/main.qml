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
                console.log("blue" +(count++) )
                event.accepted = false ;
            }
            Keys.enabled: true
            Keys.forwardTo: [_id_green]
            focus: true
        }/*endl*/
        Keys.onPressed: {
            console.log("green")
            event.accepted = false ;
        }
        Keys.enabled: true
        focus: true ;
        //Keys.forwardTo: [_id_red]
    }/*endl*/
    Keys.onPressed: {
        console.log("red")
        event.accepted = false ;
    }
    Keys.enabled: true
    focus: false
    //focus: true

}


/**
QQuickKeysAttached
qquickitem_p.h
Keyboard Focus in Qt Quick
**/







