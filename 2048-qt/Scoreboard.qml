import QtQuick 2.0

Text {
    id: s
    property int score: 0
    x: 0
    y: 0
    z: 2
    height: 20
    text: "Score: "+score.toString()
    Behavior on score {ParallelAnimation{
        NumberAnimation{duration:400}
        SequentialAnimation{
            RotationAnimation{target:s;to:40;duration:100;}
            RotationAnimation{target:s;to:-40;duration:100;}
            RotationAnimation{target:s;to:0;duration:100;}
        }
    }}
    SequentialAnimation on x{
        loops: Animation.Infinite
        NumberAnimation{to: 300;duration: 7000}
        NumberAnimation{to: 10;duration: 7000}
    }
}
