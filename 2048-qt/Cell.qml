import QtQuick 2.0
import "Logic.js" as Logic

Rectangle{
    id: me
    property int row:0//0-4
    property int col:0//0-4
    property int score
    color: switch(score){
           case 0:
            "white"
           break;
           case 2:
            "red"
           break;
           case 4:
            "orange"
           break;
           case 8:
            "yellow"
           break;
           case 16:
            "lime"
           break;
           case 32:
            "green"
           break;
           case 64:
            "aqua"
           break;
           case 128:
            "blue"
           break;
           case 256:
            "magenta"
           break;
           case 512:
            "purple"
           break;
           case 1024:
            "pink"
           break;
           case 2048:
            "maroon"
           break;
           }
    height: parent.height/4
    width: parent.width/4
    border.width: score==0 ? 0 : 5
    radius: 10
    x: row* width
    y: col* height-20
    Text{
        text: parent.score==0 ? "" : parent.score.toString()
        anchors.centerIn: parent
    }
    function move(where){
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
    Behavior on score{PropertyAnimation{
            duration:200;
            easing.type:Easing.InCubic
    }}
}
