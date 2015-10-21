import QtQuick 2.3
import QtQuick.Window 2.2
import QtWebKit 3.0
import "Components"

Window {
    visible: true
    width: 1000
    height: 800
    color: "lightgray"

    Item {
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height
        width: parent.width//-120

        ApplicationLoader {
            id: appLoader
        }
    }

    FontLoader {
        id: fontAwesome
        source: "/Fonts/font-awesome-4.2.0/fonts/FontAwesome.otf"
    }

    Rectangle {
        id: loadingRect
        anchors.fill: parent
        color: "lightgray"

        Behavior on opacity {
            NumberAnimation {duration: 500}
        }
        onOpacityChanged: {
            if(opacity === 0) {
                loadingRect.visible = false
            }
        }

        Text {
            id: loadingSpinner
            width: 200
            height: 200
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 64
            text: ""
        }

        Timer {
            id: startupTimer
            repeat: true
            interval: 5
            onTriggered: {
                loadingSpinner.rotation = loadingSpinner.rotation + 1
                if(loadingSpinner.rotation > 100) {
                    startupTimer.stop()
                    loadingRect.opacity = 0;
                } else {
                    startupTimer.restart()
                }
            }
        }
    }

    Component.onCompleted: {
        startupTimer.start()
        appLoader.loadApplication("/Qml/Map/MapInteraction.qml")
    }
}
