import QtQuick 2.0
import "Logic.js" as Logic

Rectangle{
    property int row:0//0-4
    property int col:0//0-4
    property int score:0
    color: "yellow"
    height: parent.height/4
    width: parent.width/4
    border.color: "orange"
    border.width: 5
    radius: 10
    x: row* width
    y: col* height-20
    Text{
        text: score.toString()
        anchors.centerIn: parent
    }
    function move(where){
        console.log("moving ",where," on ",row," ",col);
        switch(where){
        case "right":
            if(Logic.isEmpty(col,row+1)){
                row++;
                Logic.cells[col][row]=Logic.cell.createObject(Logic.gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col][row-1]=null;
            }
        break;
        case "left":
            if(Logic.isEmpty(col,row-1)){
                row--;
                Logic.cells[col][row]=Logic.cell.createObject(Logic.gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col][row+1]=null;
            }
        break;
        case "down":
            if(Logic.isEmpty(col+1,row)){
                col++;
                Logic.cells[col][row]=Logic.cell.createObject(Logic.gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col-1][row]=null;
            }
        break;
        case "up":
            if(Logic.isEmpty(col-1,row)){
                col--;
                Logic.cells[col][row]=Logic.cell.createObject(Logic.gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col+1][row]=null;
            }
        break;
        }
    }
    Behavior on x{NumberAnimation{duration:400;easing.type:Easing.InCubic}}
    Behavior on y{NumberAnimation{duration:400;easing.type:Easing.InCubic}}
    Behavior on score{NumberAnimation{duration:400;easing.type:Easing.InCubic}}
}
