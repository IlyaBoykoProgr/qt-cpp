import QtQuick 2.9
import QtQuick.Controls 1.4

ApplicationWindow{
    visible: true
    width: 640
    height: 480
    title: qsTr("Function viewer")
    Grid{
        z: 2
        visible: false
        id: settings
        x: parent.x
        y: parent.y
        columns: 2
        rows: 2
        SpinBox{id:widthX;prefix:"width:";value:400;maximumValue:1500;minimumValue:100;stepSize:1}
        SpinBox{id:heightY;prefix:"maxHeight:";value:400;maximumValue:1500;minimumValue:100;stepSize:1}
        SpinBox{id:quality;prefix:"quality:";decimals:3;value:0.02;maximumValue:1;minimumValue:0.001;stepSize:0.001;width:widthX.width}
        Button{text:qsTr("complete");onClicked:settings.visible=false}
    }
    toolBar: ToolBar{Row{anchors.fill: parent
        Text {
            text: qsTr("y=")
            x:0
            width: 20
        }
        TextInput{
            id: func
            text: "x*x"
            width: parent.width/2
        }
        Button{
            text: qsTr("Settings")
            onClicked: settings.visible=true
            width: parent.width/2-20
        }
    }}
}
