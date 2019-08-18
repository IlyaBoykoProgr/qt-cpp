import QtQuick 2.0
import "Logic.js" as Logic

Rectangle{
    id: me
    property int row:0//0-4
    property int col:0//0-4
    property int score
    color: score==0 ? "white":"yellow"
    height: parent.height/4
    width: parent.width/4
    border.color: "orange"
    border.width: score==0 ? 0 : 5
    radius: 10
    x: row* width
    y: col* height-20
    Text{
        text: parent.score==0 ? "" : parent.score.toString()
        anchors.centerIn: parent
    }
    function move(where){
        console.log("moving ",where," on ",row," ",col);
        switch(where){
        case "right":
            if(Logic.isEmpty(col,row+1)){
                Logic.setScore(score,row+1,col);
                Logic.setScore(0,row,col);
            }
        break;
        case "left":
            if(Logic.isEmpty(col,row-1)){
                Logic.setScore(score,row-1,col)
                Logic.setScore(0,row,col)
            }
        break;
        case "down":
            if(Logic.isEmpty(col+1,row)){
                Logic.setScore(score,row,col+1)
                Logic.setScore(0,row,col)
            }
        break;
        case "up":
            if(Logic.isEmpty(col-1,row)){
                Logic.setScore(score,row,col-1);
                Logic.setScore(0,row,col-1);
            }
        break;
        }
    }
    function is0(){
        return score==0;
    }

    Component.onCompleted: PropertyAnimation{
        target: me; properties: "scale"
        from: 0; to: 1
        duration: 300
    }
    Behavior on score{PropertyAnimation{duration:400;easing.type:Easing.InCubic}}
    Behavior on score{PropertyAnimation{to:0;duration:0}}
}
