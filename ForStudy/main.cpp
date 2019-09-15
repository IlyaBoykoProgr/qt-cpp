#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <restarter.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    Restarter* once=new Restarter;
    engine.rootContext()->setContextProperty("appRestart",once);
    return app.exec();
}
