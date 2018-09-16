import QtQuick 2.9


Rectangle{
    color: "red"
    Rectangle{
        color: "green"
        anchors.leftMargin :   parent.width*0.1
        anchors.rightMargin :  parent.width*0.1
        anchors.topMargin : parent.height*0.1
        anchors.bottomMargin: parent.height*0.1
        anchors.fill: parent
        Rectangle{
            color: "blue"
            anchors.leftMargin : parent.width*0.1
            anchors.rightMargin :  parent.width*0.1
            anchors.topMargin : parent.height*0.1
            anchors.bottomMargin: parent.height*0.1
            anchors.fill: parent
            Keys.onPressed: {
                console.log("blue")
                event.accepted = true ;
            }
            Keys.enabled: true
            focus: true
        }/*endl*/
        Keys.onPressed: {
            console.log("green")
            event.accepted = false ;
        }
        Keys.enabled: true
        focus: true
    }/*endl*/
    Keys.onPressed: {
        console.log("blue")
        event.accepted = false ;
    }
    Keys.enabled: true
    focus: true
}










