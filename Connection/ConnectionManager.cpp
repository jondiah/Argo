#include "ConnectionManager.h"
#include <QDebug>

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent)
{
    setNumberOfConnectedClients(0);

    // Listen at port 10000 for incomming clients
    m_server = new QTcpServer;
    m_server->listen(QHostAddress::Any,10000);

    // Indicate when a client connected
    QObject::connect(m_server,SIGNAL(newConnection()),
                     this, SLOT(clientConnected()));
}

int ConnectionManager::numberOfConnectedClients() const
{
    return m_numberOfConnectedClients;
}

void ConnectionManager::setNumberOfConnectedClients(int arg)
{
    if (m_numberOfConnectedClients == arg)
        return;

    m_numberOfConnectedClients = arg;
    emit numberOfConnectedClientsChanged(arg);
}

void ConnectionManager::messageFromClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
    QTextStream in(socket);

    QString str;
    in >> str;

    // Tell listeners that a message been received
    emit messageFromUser(str);
}

void ConnectionManager::clientConnected()
{
    if(m_server->hasPendingConnections()) {
        QTcpSocket *client =  m_server->nextPendingConnection();

        // Delete the client when its disconnected
        connect(client, SIGNAL(disconnected()),
                this, SLOT(clientConnectionDeleted()));

        // Accept incomming messages from the client
        connect(client, SIGNAL(readyRead()),
                this, SLOT(messageFromClient()));

        // Save the connected client
        m_connectedClients.append(client);

        qDebug() << client->peerAddress();
    }
}

void ConnectionManager::clientConnectionDeleted()
{
    QObject *signalSender = QObject::sender();

    if(signalSender != NULL) {
        signalSender->deleteLater();

        bool clientFound = false;
        for(int i = 0; i < m_connectedClients.count(); i++) {
            if(m_connectedClients.at(i) == signalSender) {
                m_connectedClients.removeAt(i);
                clientFound = true;
                break;
            }
        }

        if(!clientFound) {
            qDebug() << Q_FUNC_INFO << "Didn't found the client in the list";
        }
    }
    else {
        qDebug() << Q_FUNC_INFO << "The signalSender == null";
    }
}
