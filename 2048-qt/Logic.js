.pragma library

var cells= [];
var cell = Qt.createComponent("Cell.qml");
var gameArea;

function newCell(){
    var x,y;
    while(isEmpty(x,y)){
        x=getRandomRound(0,4);
        y=getRandomRound(0,4);
    }
    cells[x][y]=cell.createObject(gameArea, {"row": x, "col": y, "score": 2})
}

function begin(where){
    gameArea=where;
    for(var i=0; i<4; i++)cells[i] =[];

    newCell();newCell();
}

function isEmpty(x,y)
{
    if (cells[x][y] == null) {
        return true;
    } else {
        return false;
    }
}

function getRandomRound(min, max)
{
    return Math.round(Math.random() * (max - min) + min);
}
