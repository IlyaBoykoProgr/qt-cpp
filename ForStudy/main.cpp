#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "exiter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    exiter one;

    char code=1;
    while(code!=0){
    QQmlApplicationEngine engine(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* restarter=engine.rootObjects()[0]->findChild<QObject*>("reset");
    if(!restarter)return -1;
    QObject::connect(restarter,SIGNAL(restart(int)),&one,SLOT(exit(int)));
    code = app.exec();
    };
    return 0;
}
