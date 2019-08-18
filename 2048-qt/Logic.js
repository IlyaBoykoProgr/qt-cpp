.pragma library

var cells= [];
var cell = Qt.createComponent("Cell.qml");
var gameArea;
var x,y;

function newCell(){
    x=getRandomRound(0,4);
    y=getRandomRound(0,4);
   while(!isEmpty(x,y)){
        x=getRandomRound(0,4);
        y=getRandomRound(0,4);
   }
   setScore(2,x,y);
}

function setScore(sco, xa,ya){
    cells[xa][ya].score = sco;
}

function begin(where){
    gameArea=where;
    for(var i=0; i<4; i++){
        cells[i] =[];
        for(var j=0; j<4; j++)
            cells[i][j]=cell.createObject(gameArea, {"row": i, "col": j, "score": 0})
    }
    newCell();
}

function isEmpty(xa,ya)
{   if(xa>3||xa<0||ya>3||ya<0) {
        console.log("no here");
        return false;
    }
    if (cells[xa][ya].is0() == true) {
        console.log("its empty");
        return true;
    } else {
        console.log("just no");
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
   newCell();
}
function down(){
    for(x=3;x>=0;x--)
        for(y=0;y<4;y++)
            if(!isEmpty(x,y))cells[x][y].move("down");
   newCell();
}
function left(){
    for(y=0;y<4;y++)
        for(x=0;x<4;x++)
            if(!isEmpty(x,y))cells[x][y].move("left");
   newCell();
}
function right(){
    var x,y;
    for(y=3;y>=0;y--)
        for(x=0;x<4;x++)
            if(!isEmpty(x,y))cells[x][y].move("right");
   newCell();
}
