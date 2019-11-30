//USER DEFINES
    #define CELLS 15
    #define SIZE 500
//

#define everyCell for(int x=0;x<CELLS;x++)for(int y=0;y<CELLS;y++)
#if CELLS > 50
#warning Really? CELLS is a big number...
#endif
#include "universal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Universal w(CELLS,SIZE);
    w.show();

    return a.exec();
}
