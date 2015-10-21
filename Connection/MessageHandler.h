#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = 0);
    void parseMessage(QString msg);

signals:
    void newTrackingPosition(QString name, qreal lat, qreal lon);

public slots:
    void incommingMessage(QString msg);

};

#endif // MESSAGEHANDLER_H
