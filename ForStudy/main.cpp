#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <restarter.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    char code=0;
    do{

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())return -1;
    app.exec();

    }while(!code==123);
    return 0;
}
