#include "TruckerModel.h"
#include <qqmlengine.h>
#include <QDebug>

TruckerModel::TruckerModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QHash<int, QByteArray> TruckerModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[LatitiudeRole] = "latitude";
    roles[LongitudeRole] = "longitude";
    return roles;
}

int TruckerModel::rowCount(const QModelIndex &parent) const
{
    return this->m_items.count();
}

QVariant TruckerModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    TruckerItem *item = m_items[index.row()];
    if ( role == NameRole )
        return item->name();
    else if ( role == LatitiudeRole )
        return item->latitude();
    else if ( role == LongitudeRole )
        return item->longitude();
    else
        return QVariant();
}

bool TruckerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    TruckerItem* truckerItem = m_items.at(index.row());

    if (role == NameRole)
        truckerItem->setName(value.toString());
    else if (role == LatitiudeRole)
        truckerItem->setLatitude(value.toReal());
    else if (role == LongitudeRole)
        truckerItem->setLongitude(value.toReal());

    emit dataChanged(index, index);
    refresh();

    return true;
}

void TruckerModel::refresh()
{
    beginResetModel();
    endResetModel();
}

void TruckerModel::deleteAllRows() {
    for(int i = m_items.count()-1; i > -1; i--) {
        deleteRow(i);
    }
}

void TruckerModel::deleteRow(int index) {
    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    emit rowRemoved(index);
    emit countChanged(this->rowCount());
    endRemoveRows();
}

void TruckerModel::appendRow(TruckerItem *item)
{
    if (item != NULL)
    {
        int position = rowCount();
        beginInsertRows(QModelIndex(), position, position);
        m_items.append(item);
        emit rowAdded(position,item->name(), item->latitude(), item->longitude());
        endInsertRows();
        emit countChanged(this->rowCount());
    }
}

