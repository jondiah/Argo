#include "ApplicationManager.h"
#include <QDebug>

ApplicationManager::ApplicationManager(QObject *parent) :
    QObject(parent)
{
    m_connectionManager = new ConnectionManager;
    m_messageHandler = new MessageHandler;
    m_mapManager = MapManager::instance();

    QObject::connect(m_connectionManager, SIGNAL(messageFromUser(QString)),
                     m_messageHandler, SLOT(incommingMessage(QString)));
    QObject::connect(m_messageHandler, SIGNAL(newTrackingPosition(QString,qreal,qreal)),
                     this, SLOT(saveTrackingPosition(QString,qreal,qreal)));
}

void ApplicationManager::saveTrackingPosition(QString name, qreal lat, qreal lon)
{
    // Add this tracking to the trackingModel
    m_mapManager->addTrackingToModel(name,lat,lon);

    // Tell mapManager to indicate the map to paint the new waypoint
    emit m_mapManager->addTripPosition(name, lat, lon);
}


