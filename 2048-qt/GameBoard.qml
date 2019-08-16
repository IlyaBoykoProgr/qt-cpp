import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

Window{
    title: qsTr("2048 playing")
    height: width
    width: 400

    GridView{
        id: view
        cellHeight: parent.height/4
        cellWidth: cellHeight
        model: ListModel{
            id: plates
        }
        delegate: Rectangle{
            height: view.cellHeight
            width: view.cellWidth
            Text {
                text: qsTr(score)
                anchors.centerIn: parent
            }
            color: qsTr("#255, 255", score/8)
        }
    }
}
