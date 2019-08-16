.pragma library

var cells=[];
var cell = Qt.createComponent("Cell.qml");

function newCell(){

}

function begin(){
    for(var i=0; i<4; i++)cells[i] = [];

    for(var i=0; i<4; i++)
        for(var j; j<4; j++)
            cells[i][j] = null;
    newCell();newCell();
}
