import QtQuick 2.0

Rectangle{
    id:root
    color:"black"
    height: 2
    width: 2
    x:0; y:0;
    Component.onCompleted:{
        if(y<42)root.visible=false
        root.z=0
    }
}
