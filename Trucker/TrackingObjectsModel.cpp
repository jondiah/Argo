#include "TrackingObjectsModel.h"
#include <qqmlengine.h>
#include <QDebug>

TrackingObjectsModel::TrackingObjectsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QHash<int, QByteArray> TrackingObjectsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[LatitiudeRole] = "latitude";
    roles[LongitudeRole] = "longitude";
    roles[NumberOfWaypointsRole] = "numberOfWaypoints";
    roles[WaypointsRole] = "waypoints";
    return roles;
}

int TrackingObjectsModel::rowCount(const QModelIndex &parent) const
{
    return this->m_items.count();
}

QVariant TrackingObjectsModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    TrackingItem *item = m_items[index.row()];
    if ( role == NameRole )
        return item->name();
    else if ( role == LatitiudeRole )
        return item->latitude();
    else if ( role == LongitudeRole )
        return item->longitude();
    else if ( role == NumberOfWaypointsRole )
        return item->numberOfWaypoints();
    else if ( role == WaypointsRole )
        return item->waypoints();
    else
        return QVariant();
}

bool TrackingObjectsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    TrackingItem* Item = m_items.at(index.row());

    if (role == NameRole)
        Item->setName(value.toString());
    else if (role == LatitiudeRole)
        Item->setLatitude(value.toReal());
    else if (role == LongitudeRole)
        Item->setLongitude(value.toReal());
    else if (role == NumberOfWaypointsRole)
        Item->setNumberOfWaypoints(value.toInt());
    else if (role == WaypointsRole)
        Item->setWaypoints(value.toStringList());
    else {
        return false;
    }

    emit dataChanged(index, index);
    refresh();

    return true;
}

void TrackingObjectsModel::refresh()
{
    beginResetModel();
    endResetModel();
}

void TrackingObjectsModel::deleteAllRows() {
    for(int i = m_items.count()-1; i > -1; i--) {
        deleteRow(i);
    }
}

void TrackingObjectsModel::deleteRow(int index) {
    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    emit rowRemoved(index);
    emit countChanged(this->rowCount());
    endRemoveRows();
}

void TrackingObjectsModel::appendRow(TrackingItem *item)
{
    if (item != NULL)
    {
        int position = rowCount();
        beginInsertRows(QModelIndex(), position, position);
        m_items.append(item);
        emit rowAdded(position,item->name(), item->latitude(), item->longitude(), item->numberOfWaypoints(), item->waypoints());
        endInsertRows();
        emit countChanged(this->rowCount());
    }
}

