import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import "Logic.js" as Logic

Window{
    title: qsTr("2048 playing")
    height: width
    width: 400

    Component.onCompleted: {
        Logic.begin();
    }
}
