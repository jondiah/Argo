#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <Connection/ConnectionManager.h>
#include <Connection/MessageHandler.h>
#include "Map/MapManager.h"

class ApplicationManager : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationManager(QObject *parent = 0);

signals:

public slots:
    void saveTrackingPosition(QString name, qreal lat, qreal lon);

private:
    ConnectionManager *m_connectionManager;
    MessageHandler *m_messageHandler;
    MapManager *m_mapManager;

};

#endif // APPLICATIONMANAGER_H
