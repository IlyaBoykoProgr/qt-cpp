import QtQuick 2.0

Rectangle{
    color:"black"
    height: 2
    width: 2
    x:0; y:0
    Component.onCompleted: an.running=true
    NumberAnimation on x{
        running: false
        id: an
        from: 0
        to: x
        duration: 500
    }
}
