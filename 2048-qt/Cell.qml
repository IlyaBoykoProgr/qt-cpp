import QtQuick 2.0
import "Logic.js" as Logic

Rectangle{
    property int row//0-4
    property int col//0-4
    property int score
    color: "yellow"
    height: parent.height/4
    width: parent.width/4
    border.color: "orange"
    border.width: 5
    radius: 10
    x: row* width
    y: col* height
    Text{
        text: score.toString()
        anchors.centerIn: parent
    }
    function move(where){
        console.log("moving ",where," on ",row," ",col);
        switch(where){
        case "down":
            while(Logic.isEmpty(col,row+1)){
                row++;
                Logic.cells[col][row]=cell.createObject(gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col][row-1]=null;
            }
        break;
        case "up":
            while(Logic.isEmpty(col,row-1)){
                row--;
                Logic.cells[col][row]=cell.createObject(gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col][row+1]=null;
            }
        break;
        case "right":
            while(Logic.isEmpty(col+1,row)){
                col++;
                Logic.cells[col][row]=cell.createObject(gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col-1][row]=null;
            }
        break;
        case "left":
            while(Logic.isEmpty(col-1,row)){
                col--;
                Logic.cells[col][row]=cell.createObject(gameArea, {"row": row, "col": col, "score": score});
                Logic.cells[col+1][row]=null;
            }
        break;
        }
        Logic.newCell();
    }
    Behavior on row{NumberAnimation{duration:400}}
    Behavior on col{NumberAnimation{duration:400}}
    Behavior on score{NumberAnimation{duration:400;easing:Easing.InElastic}}
}
