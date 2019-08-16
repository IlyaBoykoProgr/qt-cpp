import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: mainMenu
    visible: true
    width: 500
    height: 300
    title: qsTr("2048 menu")
    SequentialAnimation{
        loops: Animation.Infinite
        running: true
        ColorAnimation {
            target: mainMenu
            properties: "color"
            from: "white"
            to: "pink"
            duration: 1000
        }
        ColorAnimation {
            target: mainMenu
            properties: "color"
            from: "pink"
            to: "white"
            duration: 1000
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
        MouseArea{
            id: play
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: logo.bottom
            anchors.bottom: parent.bottom
            Text{text:"Play"; anchors.centerIn: parent}
            onClicked: {
                board.visible = true
                mainMenu.visible = false
            }
        }
    }

    GameBoard{
     id: board
     visible: false
    }

}
