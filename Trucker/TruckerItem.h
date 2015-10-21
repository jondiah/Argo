#ifndef TRUCKERITEM_H
#define TRUCKERITEM_H

#include <QObject>

class TruckerItem : public QObject
{
public :
    TruckerItem(QString name, qreal lat, qreal lon);

    QString name() { return m_name; }
    qreal latitude() { return m_lat; }
    qreal longitude() { return m_lon; }

    void setName(QString name) { m_name = name; }
    void setLatitude(qreal lat) { m_lat = lat; }
    void setLongitude(qreal lon) { m_lon = lon; }

private:
    QString m_name;
    qreal m_lat;
    qreal m_lon;
};

#endif // TRUCKERITEM_H
