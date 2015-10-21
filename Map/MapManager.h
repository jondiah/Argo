#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QObject>
#include <QUrl>
#include <QtQml>
#include <FileHandling/FileParser.h>
#include <Trucker/TruckerModel.h>
#include <Trucker/TruckerItem.h>
#include <Trucker/TrackingObjectsModel.h>
#include <Trucker/TrackingItem.h>

class MapManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(TruckerModel *truckerModel READ truckerModel NOTIFY truckerModelChanged)
    Q_PROPERTY(TrackingObjectsModel *runningModel READ runningModel NOTIFY runningModelChanged)
    typedef QObject Base;
public:
    static MapManager* instance();
    Q_INVOKABLE bool parseFile(QUrl const &url, QString suffix);

    TruckerModel *truckerModel();
    TrackingObjectsModel *runningModel();

    void addTrackingToModel(QString name, qreal lat, qreal lon);

signals:
    void truckerModelChanged();
    void runningModelChanged();
    void addTripPosition(QString name, qreal lat, qreal lon);
    void addMarker(int index);
    void removeMarker(int index);

public slots:

private:
    MapManager(QObject* parent = NULL);
    FileParser m_fileParser;
    TruckerModel *m_truckerModel;
    TrackingObjectsModel *m_runningModel;
};

static QObject *getMapManager(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return MapManager::instance();
}

#endif // MAPMANAGER_H
