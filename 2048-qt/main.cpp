#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  app.setApplicationName("2048-qml");
  app.setApplicationVersion("2.4");
  app.setWindowIcon(QIcon(":/2048.png"));

  return app.exec();
}
