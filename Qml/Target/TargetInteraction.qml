import QtQuick 2.3
//import ConnectionManager 1.0

import "../Components"

ApplicationWindow {
    anchors.fill: parent
    color: "lightgreen"
    objectName: "Target Interaction"

//    ConnectionManager {
//        id: connectionManager
//        host: connectionSettings.host
//        port: connectionSettings.port
//    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        width: childrenRect.width + 10
        height: childrenRect.height + 10
        color: "orange"

        Column {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 5
            spacing: 5
            width: childrenRect.width
            height: childrenRect.height

            Button {
                text: "Settings"
                onBtnClicked: connectionSettings.show()
            }

            Button {
                text: "Connect"
                onBtnClicked: {
                    if(!connectionManager.connected) {
                        connectionManager.createConnection()
                    }
                }

                Indicator {
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 5
                    selected: connectionManager.connected
                }
            }

            Button {
                text: "Send message"
                buttonEnabled: connectionManager.connected
                onBtnClicked: {
                    replyText.text = replyText.text + "\n" + connectionManager.sendMessage(messageToSend.text)
                }
            }

            TextProvider {
                id: messageToSend
                text: "Message"
            }
        }
    }

    ConnectionSettings {
        id: connectionSettings
    }

    Rectangle {
        width: 200
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "white"
        border.color: "black"

        Flickable {
            anchors.fill: parent
            anchors.margins: 5
            contentHeight: replyText.height
            contentWidth: replyText.width

            Text {
                id: replyText
                width: parent.width
                height: paintedHeight
                wrapMode: Text.WordWrap
                text: "Messages from target!"
            }
        }
    }
}
