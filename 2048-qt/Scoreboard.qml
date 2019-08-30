import QtQuick 2.0
import QtMultimedia 5.0

Text {
    id: s
    property int score: 0
    x: 0
    y: 0
    z: 2
    height: 20
    text: "Score: "+score.toString()
    onScoreChanged: onMove()
    Behavior on score {
        SequentialAnimation{
            RotationAnimation{target:s;to:40;duration:200;}
            RotationAnimation{target:s;to:-40;duration:200;}
            RotationAnimation{target:s;to:0;duration:200;}
        }
    }

    function onMove(){
        moved.stop();
        moved.play();
    }

    Audio{
        id: moved
        source: "кнут.ogg"
    }

    SequentialAnimation on x{
        loops: Animation.Infinite
        NumberAnimation{to: 300;duration: 7000}
        NumberAnimation{to: 10;duration: 7000}
    }
}
