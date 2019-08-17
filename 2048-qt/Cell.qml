import QtQuick 2.0

Rectangle{
    property int row//0-4
    property int cell//0-4
    property int score
    color: "yellow"
    height: parent.height/4
    width: parent.width/4
    x: row* width
    y: row* height
    Text{
        text: score.toString()
        anchors.fill: parent
    }
    function moveTo(x,y){

    }
    MouseArea{
        anchors.fill: parent
        onClicked: console.info("i'm here")
    }
}
