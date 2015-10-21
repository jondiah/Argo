#ifndef TRACKINGITEM_H
#define TRACKINGITEM_H

#include <QObject>
#include <QStringList>

class TrackingItem : public QObject
{
public :
    TrackingItem(QString name, qreal lat, qreal lon, int nrWaypoints, QStringList waypoints);

    QString name() { return m_name; }
    qreal latitude() { return m_lat; }
    qreal longitude() { return m_lon; }
    int numberOfWaypoints() { return m_numberOfWayoints; }
    QStringList waypoints() { return m_waypoints; }

    void setName(QString name) { m_name = name; }
    void setLatitude(qreal lat) { m_lat = lat; }
    void setLongitude(qreal lon) { m_lon = lon; }
    void setNumberOfWaypoints(int nr) { m_numberOfWayoints = m_numberOfWayoints + nr; }
    void setWaypoints(QStringList pos) { m_waypoints = pos; }

private:
    QString m_name;
    qreal m_lat;
    qreal m_lon;
    int m_numberOfWayoints;
    QStringList m_waypoints;
};

#endif // TRACKINGITEM_H
