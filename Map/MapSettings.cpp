#include "MapSettings.h"
#include <QSettings>
#include <QDebug>

MapSettings::MapSettings(QObject *parent) :
    QObject(parent)
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, "qml/google_maps_browser_qml");
    QSettings settings(QSettings::UserScope, "Condeco", "Maps Client");
    m_nZoom = settings.value("zoom", 13).toInt();
    m_strMapTypeId = settings.value("mapTypeId", "google.maps.MapTypeId.ROADMAP").toString();
    m_dLat = settings.value("lat", 57.781256).toDouble();
    m_dLng = settings.value("lng", 14.18335).toDouble();

    // Read from file
    m_strApiKey = "AIzaSyDLR6b9VBLPvul183zQbdYrtV48LVgJCFc";
}

QVariant MapSettings::zoom() const
{
    return m_nZoom;
}

void MapSettings::setZoom(const QVariant& zoom)
{
    m_nZoom = zoom.toInt();
    QSettings settings(QSettings::UserScope, "Condeco", "Maps Client");
    settings.setValue("zoom", m_nZoom);
}

QVariant MapSettings::mapTypeId() const
{
    return m_strMapTypeId;
}

void MapSettings::setMapTypeId(const QVariant& id)
{
    m_strMapTypeId = id.toString();
    QSettings settings(QSettings::UserScope, "Condeco", "Maps Client");
    settings.setValue("mapTypeId", m_strMapTypeId);
}

QVariant MapSettings::lat() const
{
    return m_dLat;
}

void MapSettings::setLat(const QVariant& lat)
{
    m_dLat = lat.toDouble();
    QSettings settings(QSettings::UserScope, "Condeco", "Maps Client");
    settings.setValue("lat", m_dLat);
}

QVariant MapSettings::lng() const
{
    return m_dLng;
}

void MapSettings::setLng(const QVariant& lng)
{
    m_dLng = lng.toDouble();
    QSettings settings(QSettings::UserScope, "Condeco", "Maps Client");
    settings.setValue("lng", m_dLng);
}


QVariant MapSettings::htmlString() const
{
    if( m_strApiKey == "YOUR_API_KEY_HERE" ) {
        return "<html><body><h1 style=\"text-align: center; margin-top: 40px;\">Set your API KEY in code.</h1></body></html>";
    }

    QString str =
            "<!DOCTYPE html>"
            "<html>"
            "<head>"
            "<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\" charset=\"utf-8\"  />"
            "<style type=\"text/css\">"
            "html { height: 100% }"
            "body { height: 100%; margin: 0; padding: 0 }"
            "#map_canvas { height: 100% }"
            "</style>"
            "<script type=\"text/javascript\""
            "src=\"http://maps.googleapis.com/maps/api/js?key=%5&sensor=false\">"
            "</script>"
            "<script type=\"text/javascript\">"
            "var map; "
            "var marker; "
            "function initialize() {"
            "var myOptions = {"
            "center: new google.maps.LatLng(%2, %3),"
            "zoom: %1,"
            "mapTypeId: %4,"
            "panControl: true,"
            "zoomControl: false,"
            "mapTypeControl: false,"
            "mapTypeControlOptions: {"
            "position: google.maps.ControlPosition.RIGHT_CENTER"
            "}"
            "};"
            "map = new google.maps.Map(document.getElementById(\"map_canvas\"), myOptions);"
            "}"
            "</script>"
            "</head>"
            "<body onload=\"initialize()\">"
            "<div id=\"map_canvas\" style=\"width:100%; height:100%\"></div>"
            "</body>"
            "</html>";
    str = str.arg(m_nZoom).arg(m_dLat).arg(m_dLng).arg(m_strMapTypeId).arg(m_strApiKey);
    return str;
}

void MapSettings::setHtmlString(const QVariant&)
{

}
