import QtQuick 2.9
import QtQuick.Controls 1.4

ApplicationWindow{
    id: all
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
        SpinBox{id:widthX;prefix:"width:";value:640;maximumValue:1500;minimumValue:100;stepSize:1}
        SpinBox{id:heightY;prefix:"maxHeight:";value:480;maximumValue:1500;minimumValue:100;stepSize:1}
        SpinBox{id:quality;prefix:"quality:";decimals:2;value:0.14;maximumValue:1;minimumValue:0.01;stepSize:0.01;width:widthX.width}
        Button{text:qsTr("complete");onClicked:settings.visible=false}
    }
    toolBar: ToolBar{z:3;Row{anchors.fill: parent
        Text {
            text: qsTr("y=")
            x:0
            width: 20
        }
        TextInput{
            id: func
            text: "2*x"
            width: parent.width/3
        }
        Button{
            text: qsTr("Settings")
            onClicked: settings.visible=true
            width: parent.width/3-20
        }
        Button{
            onClicked: all.drawGraph()
            text: "Ok"
            focus: true
            Keys.onReturnPressed: all.drawGraph()
            width: parent.width/3
        }
    }}
    function drawGraph(){
        all.width=widthX.value
        all.height=heightY.value
        var x=-widthX.value/2;
        var points= [widthX.value/quality.value];
        for(var i=0; i<widthX.value/quality.value; i++){
            points[i]=Qt.createComponent("Point.qml").createObject(all,
                            {x:x+widthX.value/2,y:-eval(func.text)+heightY.value/2}
                                                                   );
            x+=quality.value;
        }
    }
    function sin(i){return Math.sin(i)}
    function cos(i){return Math.cos(i)}
    Rectangle{
     color: "orange"
     width: all.width
     height: 3
     x:0; y: heightY.value/2-45
     z: 2
    }
    Rectangle{
     color: "orange"
     width: 3
     height: all.height
     x: all.width/2; y: 0
     z: 2
    }
}
