.pragma library

var cells= [];
var cell = Qt.createComponent("Cell.qml");
var gameArea;

function newCell(){
    var x,y;
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
    newCell();newCell();
}

function isEmpty(x,y)
{
    if (cells[x][y] == null || (x>3 || x<0 || y>3 || y<0) ) {
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
    var x,y;
    for(x=0;x<4;x++)
        for(y=0;y<4;y++)
            if(!isEmpty(x,y))cells[x][y].move("up");
}
function down(){
    var x,y;
    for(x=3;x>=0;x--)
        for(y=0;y<4;y++)
            if(!isEmpty(x,y))cells[x][y].move("up");
}
function left(){
    var x,y;
    for(y=0;y<4;y++)
        for(x=0;x<4;x++)
            if(!isEmpty(x,y))cells[x][y].move("up");
}
function right(){
    var x,y;
    for(y=3;y>=0;y--)
        for(x=0;x<4;x++)
            if(!isEmpty(x,y))cells[x][y].move("up");
}
