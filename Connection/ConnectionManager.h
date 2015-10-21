#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <iostream>
#include <string>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "MessageHandler.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numberOfConnectedClients READ numberOfConnectedClients NOTIFY numberOfConnectedClientsChanged)

public:
    explicit ConnectionManager(QObject *parent = 0);

    int numberOfConnectedClients() const;

signals:
    void messageFromUser(QString message);
    void numberOfConnectedClientsChanged(int arg);

public slots:
    void messageFromClient();
    void clientConnected();
    void clientConnectionDeleted();

private:
    void setNumberOfConnectedClients(int arg);

    QTcpServer *m_server;
    QList<QTcpSocket *> m_connectedClients;

    int m_numberOfConnectedClients;
};

#endif // CONNECTIONMANAGER_H
