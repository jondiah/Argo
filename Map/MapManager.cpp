#include "MapManager.h"
#include <QDebug>

MapManager::MapManager(QObject *parent) :
    Base(parent)
{
    m_truckerModel = new TruckerModel;
    m_runningModel = new TrackingObjectsModel;
}

MapManager* MapManager::instance()
{
    static MapManager* obj = new MapManager();
    return obj;
}

bool MapManager::parseFile(const QUrl &url, QString suffix)
{
    qDebug() << Q_FUNC_INFO << url << suffix;

    if(suffix == "txt") {
        m_fileParser.setFilePath(url.path());

        // Remove previous model data
        if(m_truckerModel->rowCount() > 0) {
            m_truckerModel->deleteAllRows();
        }

        m_fileParser.parseFile(*m_truckerModel);

        return true;
    }

    return false;
}

TruckerModel *MapManager::truckerModel()
{
    return m_truckerModel;
}

TrackingObjectsModel *MapManager::runningModel()
{
    return m_runningModel;
}

void MapManager::addTrackingToModel(QString name, qreal lat, qreal lon)
{
    qDebug() << Q_FUNC_INFO << name << lat << lon;

    QString slat = QString::number(lat);
    QString slon = QString::number(lon);
    QStringList pos;
    pos.append(slat);
    pos.append(slon);

    int foundIndex = -1;

    for(int i = 0; i < m_runningModel->rowCount(); i++) {
        // Check the model if this name is already registred
        if(m_runningModel->data(m_runningModel->index(i),TrackingObjectsModel::NameRole) == name) {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1) {
        qDebug() << Q_FUNC_INFO << "The name wasn't found, add a new object to the model";
        m_runningModel->appendRow(new TrackingItem(name,lat,lon,1,pos));
    }
    else {
        qDebug() << Q_FUNC_INFO << "The name " << name << "was found at index " << foundIndex;

        // Get the number of waypoints and add one more
        int nr = m_runningModel->data(m_runningModel->index(foundIndex),TrackingObjectsModel::NumberOfWaypointsRole).toInt() + 1;
        m_runningModel->setData(m_runningModel->index(foundIndex),QVariant::fromValue(nr),TrackingObjectsModel::NumberOfWaypointsRole);

        // Get current waypoints and add the new ones
        QStringList list = m_runningModel->data(m_runningModel->index(foundIndex),TrackingObjectsModel::WaypointsRole).toStringList();
        list.append(slat);
        list.append(slon);
        m_runningModel->setData(m_runningModel->index(foundIndex),QVariant::fromValue(list),TrackingObjectsModel::WaypointsRole);
    }
}
