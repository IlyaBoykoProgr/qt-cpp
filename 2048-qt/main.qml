import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import "Logic.js" as Logic

Window {
    id: mainMenu
    visible: true
    width: 500
    height: 300
    title: qsTr("2048forPRO menu")
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
        id: buttons
        height: parent.height
        width: parent.width/3
        anchors.centerIn: parent
        Image{
            id: logo
            source: "2048.png"
        }
        Button{
            id: play
            anchors.left: buttons.left
            anchors.right: buttons.right
            anchors.top: logo.bottom
            anchors.bottom: help.top
            text:"Play"
            focus: true
            Keys.onReturnPressed:{
                board.visible = true
                Logic.begin(board,scoreBoard);
                mainMenu.visible = false
            }
            onClicked: {
                board.visible = true
                Logic.begin(board);
                mainMenu.visible = false
            }
        }
        Button{
            id: help
            height: buttons.height/3
            anchors.left: buttons.left
            anchors.right: buttons.right
            anchors.bottom: buttons.bottom
            text: "How to play"
            onClicked: helpWindow.show();
        }
    }

    Window{
        id: board
        title: qsTr("2048forPRO playing")
        height: width+40
        width: 400
        onHeightChanged: width=height-40
        visible: false
        x: mainMenu.x
        y: mainMenu.y
        Text {
            id:scoreBoard
            property int sc: 0
            height: 30
            text: "Score: " + sc.toString()
        }
    }
    Window{
        id:helpWindow
        x:mainMenu.x
        y:mainMenu.y
        width: 400
        height: 300
        title: qsTr("2048forPRO help")
        Text {
            text: qsTr("This.. is.. Help!\n\nYou need to move plates using arrows.\n2 same plates joins to 1 bigger.\nGet the 2048 plate!")
        }
    }
}

