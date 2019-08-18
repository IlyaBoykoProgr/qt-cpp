import QtQuick 2.3
import QtQuick.Window 2.2
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
        MouseArea{
            id: play
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: logo.bottom
            anchors.bottom: parent.bottom
            Text{text:"Play"; anchors.centerIn: parent}
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
        height: width
        width: 400
        onWidthChanged: height=width
        onHeightChanged: width=height
        visible: false
        x: mainMenu.x
        y: mainMenu.y
        Rectangle{
            anchors.fill: parent
            z:-1
            Keys.enabled: true
            Keys.onPressed:{
                switch(event.key){
                case Qt.Key_Up:
                    Logic.up();
                break;
                case Qt.Key_Down:
                    Logic.down();
                break;
                case Qt.Key_Left:
                    Logic.left();
                break;
                case Qt.Key_Right:
                    Logic.right();
                break;
                }
            }
        }
    }

}
