import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
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
    radius: 12
    x: row* width
    y: col* height+20
    Text{
        text: parent.score==0 ? "" : parent.score.toString()
        anchors.centerIn: parent
    }
    function move(where){
        switch(where){
        case "right":
            if(row+1==4)return;
            if(Logic.isEmpty(row+1,col)){
                Logic.setScore(score,row+1,col);
                Logic.setScore(0,row,col);
            }
            if(Logic.cells[row+1][col].score===score){
                Logic.add(score*2);
                Logic.setScore(score*2,row+1,col);
                Logic.setScore(0,row,col);
            }
        break;
        case "left":
            if(row-1==-1)return;
            if(Logic.isEmpty(row-1,col)){
                Logic.setScore(score,row-1,col);
                Logic.setScore(0,row,col)
            }
            if(Logic.cells[row-1][col].score===score){
                Logic.add(score*2);
                Logic.setScore(score*2,row-1,col);
                Logic.setScore(0,row,col);
            }
        break;
        case "down":
            if(col+1==4)return;
            if(Logic.isEmpty(row,col+1)){
                Logic.setScore(score,row,col+1)
                Logic.setScore(0,row,col)
            }
            if(Logic.cells[row][col+1].score===score){
                Logic.add(score*2);
                Logic.setScore(score*2,row,col+1);
                Logic.setScore(0,row,col);
            }
        break;
        case "up":
            if(col-1==-1)return;
            if(Logic.isEmpty(row,col-1)){
                Logic.setScore(score,row,col-1);
                Logic.setScore(0,row,col);
            }
            if(Logic.cells[row][col-1].score===score){
                Logic.add(score*2);
                Logic.setScore(score*2,row,col-1);
                Logic.setScore(0,row,col);
            }
        break;
        }
    }
    function is0(){
        return score==0;
    }
    focus: true
    Keys.onUpPressed: Logic.up();
    Keys.onDownPressed: Logic.down();
    Keys.onLeftPressed: Logic.left();
    Keys.onRightPressed: Logic.right();
    Behavior on color{ColorAnimation{duration:300}}
    onScoreChanged: if(score==2048 && !Logic.win){winDialog.show();Logic.win=true}
    Window{
        id: winDialog
        visible: false
        Text {
            id: winText
            anchors.top: winDialog.top
            anchors.left: winDialog.left
            anchors.right: winDialog.right
            text: qsTr("You win! :)")
            color: "green"
        }
        Button{
            id: quit
            anchors.top: winText.bottom
            anchors.left: winDialog.left
            anchors.right: winDialog.right
            anchors.bottom: winDialog.bottom
            text: "Quit?"
            onClicked: Qt.quit();
        }
    }
}
