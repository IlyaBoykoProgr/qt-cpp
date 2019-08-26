import QtQuick 2.0

Text {
    property int score: 0
    x: 0
    y: 0
    z: 2
    height: 20
    text: "Score: "+score.toString()
    Behavior on score{NumberAnimation{
        duration: 500
        easing.type: Easing.OutBack
        easing.overshoot: 100
    }}

    NumberAnimation on x{
        duration: 700
        from: 500
        to: 0
        easing.type: Easing.OutBounce
        running: true
    }
}
