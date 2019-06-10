#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "samregistry.h"
#include "samitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SamItem>("Tracker", 1, 0, "SamItem");

    QQmlApplicationEngine engine;
    QQmlContext *rootContext = engine.rootContext();

    SamRegistry samRegistry;
    rootContext->setContextProperty("samRegistry", &samRegistry);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
