.pragma library

var cells= [];
var cell = Qt.createComponent("Cell.qml");
var gameArea;
var x,y;

function newCell(){
    x=0; y=0;
   while(!isEmpty(x,y)){
        x=getRandomRound(0,4);
        y=getRandomRound(0,4);
   }
    cells[x][y]=cell.createObject(gameArea, {"row": x, "col": y, "score": 2})
}

function begin(where){
    gameArea=where;
    for(var i=0; i<4; i++)cells[i] =[];
    newCell();
}

function isEmpty(x,y)
{   if(x>3 || x<0 || y>3 || y<0) {
        return false;
    }
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

function up(){
    for(x=0;x<4;x++)
        for(y=0;y<4;y++)
            if(!isEmpty(x,y))cells[x][y].move("up");
   // newCell();
}
function down(){
    for(x=3;x>=0;x--)
        for(y=0;y<4;y++)
            if(!isEmpty(x,y))cells[x][y].move("down");
   // newCell();
}
function left(){
    for(y=0;y<4;y++)
        for(x=0;x<4;x++)
            if(!isEmpty(x,y))cells[x][y].move("left");
    //newCell();
}
function right(){
    var x,y;
    for(y=3;y>=0;y--)
        for(x=0;x<4;x++)
            if(!isEmpty(x,y))cells[x][y].move("right");
   // newCell();
}
