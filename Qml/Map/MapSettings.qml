import QtQuick 2.0
import MapManager 1.0

import "../Components"

Rectangle {
    id: mapSettings
    width: 400
    height: 0
    anchors.centerIn: parent
    color: "lightgray"

    property alias internalState: internalState.state

    signal closeFinished()
    signal openFinished()
    signal settingsLoaded()

    function close() {
        internalState.state = "closed"
    }

    function open() {
        internalState.state = "open"
    }

    function openAnimationFinsihed() {
        openFinished()
    }

    function closeAnimationFinished() {
        closeFinished()
    }

    StateGroup {
        id: internalState
        state: "closed"
        states: [
            State {
                name: "open"
                PropertyChanges {
                    target: mapSettings
                    height: 600
                }
            },
            State {
                name: "closed"
                PropertyChanges {
                    target: mapSettings
                    height: 0
                }
            }
        ]
        transitions: [
            Transition {
                from: "*"
                to: "open"
                SequentialAnimation {
                    PropertyAction { target: mapSettings; property: "visible"; value: true}
                    NumberAnimation { target: mapSettings; property: "height"; duration: 200 }
                    ScriptAction { script: openAnimationFinsihed() }
                }
            },
            Transition {
                from: "*"
                to: "closed"
                SequentialAnimation {
                    NumberAnimation { target: mapSettings; property: "height"; duration: 200 }
                    PropertyAction { target: mapSettings; property: "visible"; value: false}
                    ScriptAction { script: closeAnimationFinished() }
                }
            }
        ]
    }

    Text {
        id: labelSettings
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 40
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 24
        font.family: fontAwesome.name
        text: "" + " Settings"
    }

    Rectangle {
        id: separator
        anchors.top: labelSettings.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 100
        color: "black"
        height: 3
    }
}

