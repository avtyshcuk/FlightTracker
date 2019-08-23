#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "samregistry.h"
#include "samitem.h"
#include "airplane.h"
#include "beampositionitem.h"
#include "beamsimulator.h"
#include "pointsreceiver.h"
#include "trackregistry.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SamItem>("Tracker", 1, 0, "SamItem");
    qmlRegisterType<BeamPositionItem>("Tracker", 1, 0, "BeamPositionItem");
    qmlRegisterType<AirPlane>("Tracker", 1, 0, "AirPlane");

    QQmlApplicationEngine engine;
    QQmlContext *rootContext = engine.rootContext();

    SamRegistry samRegistry;
    rootContext->setContextProperty("samRegistry", &samRegistry);

    BeamSimulator beamSimulator;
    beamSimulator.setSamRegistry(&samRegistry);
    rootContext->setContextProperty("beamSimulator", &beamSimulator);

    PointsReceiver pointsReceiver;
    pointsReceiver.setSamRegistry(&samRegistry);
    rootContext->setContextProperty("pointsReciever", &pointsReceiver);

    TrackRegistry trackRegistry;
    trackRegistry.setBeamSimulator(&beamSimulator);
    trackRegistry.setPointsReceiver(&pointsReceiver);
    trackRegistry.setSamRegistry(&samRegistry);
    rootContext->setContextProperty("trackRegistry", &trackRegistry);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
