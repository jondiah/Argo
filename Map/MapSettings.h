#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <QObject>
#include <QVariant>

class MapSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(QVariant mapTypeId READ mapTypeId WRITE setMapTypeId NOTIFY mapTypeIdChanged)
    Q_PROPERTY(QVariant htmlString READ htmlString WRITE setHtmlString NOTIFY htmlStringChanged)
    Q_PROPERTY(QVariant lat READ lat WRITE setLat NOTIFY latChanged)
    Q_PROPERTY(QVariant lng READ lng WRITE setLng NOTIFY lngChanged)
public:
    explicit MapSettings(QObject *parent = 0);

    QVariant zoom() const;
    void setZoom(const QVariant& z);

    QVariant mapTypeId() const;
    void setMapTypeId(const QVariant& id);

    QVariant htmlString() const;
    void setHtmlString(const QVariant& id);

    QVariant lat() const;
    void setLat(const QVariant& id);

    QVariant lng() const;
    void setLng(const QVariant& id);

    Q_INVOKABLE QString getApiKey() const { return m_strApiKey; }

signals:
    void zoomChanged();
    void mapTypeIdChanged();
    void htmlStringChanged();
    void latChanged();
    void lngChanged();

private:
    QString m_strMapTypeId;
    QString m_strApiKey;
    int m_nZoom;
    double m_dLat;
    double m_dLng;
};

#endif // SETTINGS_MANAGER_H
