#include "MessageHandler.h"
#include <QDebug>

MessageHandler::MessageHandler(QObject *parent) :
    QObject(parent)
{
}

void MessageHandler::parseMessage(QString msg)
{
    qDebug() << Q_FUNC_INFO << msg;

    // Number of items in the message
    int numberOfItems = 0;

    // Save all the items in a list
    QStringList listOfItems;

    // Split the message int packages
    listOfItems = msg.split(";");
    numberOfItems = listOfItems.count();

    if(numberOfItems == 0) {
        qDebug() << Q_FUNC_INFO << "The message didnt have any items";
    }
    else if(numberOfItems == 1) {
        qDebug() << Q_FUNC_INFO << "The message only had one item which is: " << listOfItems.at(0);
    }
    else if(numberOfItems == 2) {
        QString name;
        QString pos;
        qreal lat, lon;
        // Name, Position
        name = listOfItems.at(0);
        pos = listOfItems.at(1);
        lat = pos.split(",").at(0).toDouble();
        lon = pos.split(",").at(1).toDouble();

        qDebug() << Q_FUNC_INFO << "The message hade two items: " << name << lat << lon;

        emit newTrackingPosition(name, lat, lon);
    }
    else if(numberOfItems > 2) {
        qDebug() << Q_FUNC_INFO << "The message hade more than two items which are: " << listOfItems;
    }
}

void MessageHandler::incommingMessage(QString msg)
{
    qDebug() << Q_FUNC_INFO << msg;

    if(msg.size() > 0) {
        parseMessage(msg);
    }
    else {
        qDebug() << Q_FUNC_INFO << "The message has no content";
    }
}
