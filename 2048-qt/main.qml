import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import "Logic.js" as Logic

Window {
    id: mainMenu
    visible: true
    width: 500
    height: 300
    title: qsTr("2048 menu")
    SequentialAnimation on color{
        loops: Animation.Infinite
        ColorAnimation {
            from: "white";to: "pink";duration: 1000
        }
        ColorAnimation {
            from: "pink";to: "white";duration: 1000
        }
    }

    Column{
        height: parent.height
        width: parent.width/3
        anchors.centerIn: parent
        Image{
            id: logo
            source: "2048.png"
        }
        Button{
            id: play
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: logo.bottom
            anchors.bottom: parent.bottom
            text:"Play"
            onClicked: {
                board.visible = true
                Logic.begin(board);
                mainMenu.visible = false
            }
        }
    }

    Window{
        id: board
        title: qsTr("2048 playing")
        height: width+20
        width: 400
        onHeightChanged: width=height-20
        visible: false
        x: mainMenu.x
        y: mainMenu.y
            Button{
                height: 20
                x:50
                anchors.bottom: parent.bottom
                text:"up"
                onClicked: Logic.up()
            }Button{
                x:150
                height: 20
                anchors.bottom: parent.bottom
                text:"down"
                onClicked: Logic.down()
            }Button{
                x:250
                height: 20
                anchors.bottom: parent.bottom
                text:"left"
                onClicked: Logic.left()
            }Button{
                height: 20
                x:350
                anchors.bottom: parent.bottom
                text:"right"
                onClicked: Logic.right()
            }
    }

}
