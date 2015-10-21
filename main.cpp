#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "Connection/ConnectionManager.h"
#include "Map/MapSettings.h"
#include "Map/MapManager.h"
#include "Trucker/TruckerModel.h"
#include "Trucker/TrackingObjectsModel.h"
#include "ApplicationManager.h"
#include <QVariant>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ApplicationManager appManager;

    qmlRegisterType<TruckerModel>("TruckerModel", 1, 0, "TruckerModel");
    qmlRegisterType<TrackingObjectsModel>("TrackingObjectsModel", 1, 0, "TrackingObjectsModel");

    qmlRegisterType<MapSettings>("MapSettings", 1, 0, "MapSettings");
    qmlRegisterSingletonType<MapManager>("MapManager", 1, 0, "MapManager", &getMapManager);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/Qml/StartView.qml")));

    return app.exec();
}

