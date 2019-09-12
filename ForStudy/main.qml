import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Graphic painting!");
    Row{
        id: controls
        width: root.width
        height: 40
        Text {
            width: parent.width/6-80
            text: qsTr("y=")
        }
        TextInput{
            width: parent.width/6+80
            id: func
            text: "x*x/3"
            onTextChanged: canvas.drawGraph();
        }

        SpinBox {
            id: widthX
            width: parent.width/3
            value: 200
            prefix: "width x:"
            maximumValue: 1000
            minimumValue: 1
        }

        SpinBox {
            id: heightY
            width: parent.width/3
            prefix: "height y:"
            maximumValue: 1000
            minimumValue: 1
            value: 200
        }
        Canvas{
        id: canvas
        anchors.top: controls.top
        width: root.width
        height: root.height-controls.height
        function drawGraph(){
            var x= -widthX.value/2;
            var ctx = canvas.getContext('2d');
            for(x;x<=widthX.value/2;x++){
                console.log(func.text);
                var y= eval(func.text);
                if(heightY.value/2<=y || -heightY.value/2<=y){
                    ctx.arc(x, y, 2, 0, 2*Math.PI, false);
                    ctx.fill();
                }
            }
        }
        }
    }
}
