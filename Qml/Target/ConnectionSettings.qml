import QtQuick 2.0

import "../Components"

Rectangle {
    id: connectionSettings
    width: 110
    height: 200
    color: "orange"
    state: "closed"

    property alias host: hostIp.text
    property alias port: portNumber.text

    function show() {
        state = "open"
    }
    function hide() {
        state = "closed"
    }
    function toggle() {
        if(state === "open") {
            state = "closed"
        } else {
            state = "open"
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 5

        TextProvider {
            id: hostIp
            text: "192.168.0.14"
        }

        TextProvider {
            id: portNumber
            text: "10000"
        }

        Button {
            text: "Close"
            onBtnClicked: hide()
        }
    }


    states: [
        State {
            name: "open"
            PropertyChanges {
                target: connectionSettings
                x: 0
            }
        },
        State {
            name: "closed"
            PropertyChanges {
                target: connectionSettings
                x: -width
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "open"
            NumberAnimation {
                target: connectionSettings
                property: "x"
                duration: 500
            }
        },
        Transition {
            from: "*"
            to: "closed"
            NumberAnimation {
                target: connectionSettings
                property: "x"
                duration: 500
            }
        }
    ]
}
