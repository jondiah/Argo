#ifndef TRACKINGOBJECTSMODEL_H
#define TRACKINGOBJECTSMODEL_H

#include <QAbstractListModel>
#include "TrackingItem.h"
#include <QList>

class TrackingObjectsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TruckerRoles {
        NameRole = Qt::UserRole + 1,
        LatitiudeRole,
        LongitudeRole,
        NumberOfWaypointsRole,
        WaypointsRole
    };

    explicit TrackingObjectsModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void appendRow(TrackingItem *item);
    void refresh();
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void deleteRow(int index);
    void deleteAllRows();
signals:
    void countChanged(int);
    void rowAdded(int index, QString name, qreal lat, qreal lon, int numberOfWaypoints, QStringList waypoints);
    void rowRemoved(int index);

public slots:

private:
//    Q_DISABLE_COPY(TrackingObjectsModel);
    QList<TrackingItem *> m_items;
    int m_count;

};


#endif // TRACKINGOBJECTSMODEL_H
