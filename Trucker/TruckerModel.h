#ifndef TRUCKERMODEL_H
#define TRUCKERMODEL_H

#include <QAbstractListModel>
#include "TruckerItem.h"
#include <QList>

class TruckerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TruckerRoles {
        NameRole = Qt::UserRole + 1,
        LatitiudeRole,
        LongitudeRole
    };

    explicit TruckerModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void appendRow(TruckerItem *item);
    void refresh();
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void deleteRow(int index);
    void deleteAllRows();
signals:
    void countChanged(int);
    void rowAdded(int index, QString name, qreal lat, qreal lon);
    void rowRemoved(int index);

public slots:

private:
//    Q_DISABLE_COPY(TruckerModel);
    QList<TruckerItem *> m_items;
    int m_count;

};

#endif // TRUCKERMODEL_H
