import QtQuick 2.0
import QtWebKit 3.0
import MapSettings 1.0
import MapManager 1.0
import QtWebKit.experimental 1.0
import "GoogleMapsInteraction.js" as GM

import "../Components"

ApplicationWindow {
    anchors.fill: parent
    color: "lightgray"
    objectName: "Map Interaction"

    MapSettings {
        id: mapSettings
    }

    Connections {
        target: MapManager

        onAddTripPosition: {
            console.log("QML: ", name,lat,lon)
            webView.experimental.evaluateJavaScript(GM.addTripPosition(name,lat,lon))
        }
    }

    Item {
        id: topBar
        anchors.left: parent.left
        anchors.top: parent.top
        height: 60
        width: parent.width

        Row {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 5
            spacing: 5
            // Add file
            Button {
                width: 100
                height: 50
                textPointSize: 24
                text: ""
                border.color: "black"
                border.width: 2
                onBtnClicked: {
                    if(loaderMapFileLoader.active) {
                        loaderMapFileLoader.item.close()
                    } else {
                        loaderMapFileLoader.active = true
                    }
                }
            }
        }

        Row {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 5
            spacing: 5
            // Settings
            Button {
                width: 100
                height: 50
                textPointSize: 24
                text: ""
                border.color: "black"
                border.width: 2
                onBtnClicked: {
                    if(loaderMapSettings.active) {
                        loaderMapSettings.item.close()
                    } else {
                        loaderMapSettings.active = true
                    }
                }
            }
        }

        Text {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontAwesome.name
            font.pixelSize: 32
            height: parent.height
            text: "Argo"

            MouseArea {
                anchors.fill: parent
            }
        }
    }

    WebView {
        id: webView
        anchors.top: topBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        url: mapSettings.htmlString//"Standard.html"
        visible: loadProgress === 100
        // Enable communication between QML and WebKit
        experimental.preferences.navigatorQtObjectEnabled: true;
        // When the document loads, post the outerHTML back to the QML layer.
        //        onLoadingChanged: {
        //            if (loadRequest.status === WebView.LoadSucceededStatus) {
        //                experimental.evaluateJavaScript(
        //                            "navigator.qt.postMessage(document.documentElement.outerHTML)");
        //            }
        //        }

        // When we get the message, dump the string data to the console.
        //        experimental.onMessageReceived: {
        //            //console.log(message.data);
        //            console.log("Message received")
        //        }

        Component.onCompleted: url = mapSettings.htmlString
    }

    Button {
        id: mapTypeHandle
        anchors.top: mapTypeCont.top
        anchors.right: mapTypeCont.left
        width: 24
        height: 20
        radius: 0
        text: mapTypeCont.state === "open" ? "" : ""
        onBtnClicked: {
            if(mapTypeCont.state === "open")
                mapTypeCont.state = "closed"
            else
                mapTypeCont.state = "open"
        }
    }

    Rectangle {
        id: mapTypeCont
        anchors.top: topBar.bottom
        anchors.topMargin: 10
        height: 210
        width: 110
        color: "lightgray"
        state: "closed"
        states:[
            State {
                name: "open"
                AnchorChanges {
                    target: mapTypeCont
                    anchors.right: mapTypeCont.parent.right
                    anchors.left: undefined
                }
            },
            State {
                name: "closed"
                AnchorChanges {
                    target: mapTypeCont
                    anchors.left: mapTypeCont.parent.right
                    anchors.right: undefined
                }
            }
        ]

        transitions: [
            Transition {
                from: "*"
                to: "*"
                AnchorAnimation {
                    duration: 200
                }
            }
        ]
        ListView {
            id: mapTypeView
            anchors.centerIn: parent
            height: 200
            width: 100
            currentIndex: 2
            clip: true

            model:  ListModel {
                id: mapTypeModel
                ListElement { modelData: "RoadMap";      type: "google.maps.MapTypeId.ROADMAP"}
                ListElement { modelData: "Satellite";    type: "google.maps.MapTypeId.SATELLITE"}
                ListElement { modelData: "Hybrid";       type: "google.maps.MapTypeId.HYBRID"}
                ListElement { modelData: "Terrain";      type: "google.maps.MapTypeId.TERRAIN"}
            }

            onCurrentIndexChanged: {
                webView.experimental.evaluateJavaScript(GM.changeMapType(model.get(currentIndex).type))
            }

            delegate: Button {
                width: 100
                height: 50
                text: modelData
                radius: 0
                opacity: mapTypeView.currentIndex === index ? 1 : 0.5
                onBtnClicked: mapTypeView.currentIndex = index

            }
        }
    }

    Button {
        id: truckerListHandle
        anchors.top: truckerListCont.top
        anchors.right: truckerListCont.left
        width: 34
        height: 30
        radius: 0
        text: truckerListCont.state === "open" ? "" : ""
        textPointSize: 20
        onBtnClicked: {
            if(truckerListCont.state === "open")
                truckerListCont.state = "closed"
            else
                truckerListCont.state = "open"
        }
    }

    TrucksLoadedList {
        id: truckerListCont
        width: 210
        anchors.top: mapTypeCont.bottom
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        color: "lightgray"
    }

    Button {
        id: truckerRunningListHandle
        anchors.top: truckerRunningListCont.top
        anchors.left: truckerRunningListCont.right
        width: 34
        height: 30
        radius: 0
        text: truckerRunningListCont.state === "open" ? "" : ""
        textPointSize: 20
        onBtnClicked: {
            if(truckerRunningListCont.state === "open")
                truckerRunningListCont.state = "closed"
            else
                truckerRunningListCont.state = "open"
        }
    }

    TrucksRunningList {
        id: truckerRunningListCont
        width: 210
        anchors.top: truckerListCont.top
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        color: "lightgray"
    }

    Loader {
        id: loaderMapFileLoader
        active: false
        anchors.top: topBar.bottom
        anchors.right: parent.right
        source: "/Qml/Map/MapFileLoader.qml"

        onStatusChanged: {
            if(status === Loader.Ready) {
                item.closeFinished.connect(fileLoaderClosed)
                item.mapFileLoaded.connect(trucksLoaded)
                item.open()
            }
        }

        function fileLoaderClosed() {
            item.closeFinished.disconnect(fileLoaderClosed)
            item.mapFileLoaded.disconnect(trucksLoaded)
            active = false
        }

        function trucksLoaded(trucksModel) {
            item.internalState = "closed"
        }
    }

    Loader {
        id: loaderMapSettings
        active: false
        anchors.top: topBar.bottom
        anchors.left: parent.left
        source: "/Qml/Map/MapSettings.qml"

        onStatusChanged: {
            if(status === Loader.Ready) {
                item.closeFinished.connect(settingsLoaderClosed)
                item.settingsLoaded.connect(settingsLoaded)
                item.open()
            }
        }

        function settingsLoaderClosed() {
            item.closeFinished.disconnect(settingsLoaderClosed)
            item.settingsLoaded.disconnect(settingsLoaded)
            active = false
        }

        function settingsLoaded() {
            item.internalState = "closed"
        }
    }
}
