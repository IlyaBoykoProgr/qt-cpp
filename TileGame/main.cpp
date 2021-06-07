#include <QApplication>
#include "graphics.h"

int main(int argc,char** argv){
    QApplication app(argc,argv);
    srand(time(0));
    int code;
    do{
        Graphics gr;
        code = app.exec();
    }while(code==-45);
    return code;
}
