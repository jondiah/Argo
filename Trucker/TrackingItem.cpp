#include "TrackingItem.h"

TrackingItem::TrackingItem(QString name, qreal lat, qreal lon, int nrWaypoints, QStringList waypoints) :
    m_name(name),
    m_lat(lat),
    m_lon(lon),
    m_numberOfWayoints(nrWaypoints),
    m_waypoints(waypoints)
{
}
