import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

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
     text: "Quit"
     onClicked: Qt.quit();
 }
}
