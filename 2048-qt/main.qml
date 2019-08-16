import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: mainMenu
    visible: true
    width: 640
    height: 480
    title: qsTr("2048 menu")

    Column{
        height: parent.height
        width: parent.width/3
        anchors.centerIn: parent
        Image{
            source: "2048.png"
        }
        Button{
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
