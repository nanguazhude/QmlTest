import QtQuick 2.9

Rectangle{
    color: Qt.rgba(0,0,0,0)
    id : _root;


Rectangle{
    width: 10
    height: 10
    color: Qt.rgba(0.2,0.8,0.7,1)
    id : _split_point ;
    x : 150 ;
    y : 150 ;
}

MouseArea{
    anchors.fill: _split_point ;
    drag.target: _split_point
    drag.axis: Drag.XAndYAxis
    drag.minimumX: _root.width * 0.1 ;
    drag.maximumX:  _root.width * 0.8 ;
    drag.minimumY: _root.height * 0.1;
    drag.maximumY: _root.height * 0.8;
}


}
























