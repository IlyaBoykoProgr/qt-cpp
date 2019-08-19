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
     id: errorDialog
     visible: false
     width: 200
     height: 200
     Text {
         id: loseText

         anchors.top: parent.top
         anchors.left: parent.left
         anchors.right: parent.right
         text: qsTr("You losed! :(")
         color: "red"
     }
     Button{
         id: quit
         anchors.top: loseText.bottom
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.bottom: parent.bottom
         text: "Quit, haha"
         onClicked: Qt.quit();
     }
    }

    Window{
        id: board
        title: qsTr("2048forPRO playing")
        height: width+20
        width: 400
        onHeightChanged: width=height-20
        visible: false
        x: mainMenu.x
        y: mainMenu.y
        function lose(){
            errorDialog.visible=true;
        }
            Button{
                height: 20
                x:0
                anchors.bottom: parent.bottom
                text:"up"
                onClicked: Logic.up();
            }Button{
                x:100
                height: 20
                anchors.bottom: parent.bottom
                text:"down"
                onClicked: Logic.down()
            }Button{
                x:200
                height: 20
                anchors.bottom: parent.bottom
                text:"left"
                onClicked: Logic.left()
            }Button{
                height: 20
                x:300
                anchors.bottom: parent.bottom
                text:"right"
                onClicked: Logic.right()
            }
    }

}
