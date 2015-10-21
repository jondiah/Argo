import QtQuick 2.0
import Qt.labs.folderlistmodel 2.1
import MapManager 1.0

import "../Components"

Rectangle {
    id: mapFileLoader
    width: 400
    height: 0
    anchors.centerIn: parent
    color: "lightgray"

    property alias internalState: internalState.state

    signal closeFinished()
    signal openFinished()
    signal mapFileLoaded(var trucksModel)

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
                    target: mapFileLoader
                    height: 600
                }
            },
            State {
                name: "closed"
                PropertyChanges {
                    target: mapFileLoader
                    height: 0
                }
            }
        ]
        transitions: [
            Transition {
                from: "*"
                to: "open"
                SequentialAnimation {
                    PropertyAction { target: mapFileLoader; property: "visible"; value: true}
                    NumberAnimation { target: mapFileLoader; property: "height"; duration: 200 }
                    ScriptAction { script: openAnimationFinsihed() }
                }
            },
            Transition {
                from: "*"
                to: "closed"
                SequentialAnimation {
                    NumberAnimation { target: mapFileLoader; property: "height"; duration: 200 }
                    PropertyAction { target: mapFileLoader; property: "visible"; value: false}
                    ScriptAction { script: closeAnimationFinished() }
                }
            }
        ]
    }

    FolderListModel {
        id: folderModel
        folder: "/home/jondiah/"
        showDirsFirst: true
        showDotAndDotDot: true
        nameFilters: "*.txt"
    }

    Text {
        id: labelOpenFile
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 40
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 24
        font.family: fontAwesome.name
        text: "" + " Load File"
    }

    Rectangle {
        id: separator
        anchors.top: labelOpenFile.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 100
        color: "black"
        height: 3
    }

    ListView {
        id: folderView
        anchors.top: separator.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        clip: true
        model: folderModel

        delegate: Item {
            height: 60
            width: folderView.width
            Button {
                anchors.fill: parent
                anchors.margins: 5
                text: fileName
                color: colorDefault
                border.color: "black"
                border.width: 1
                textColor: fileIsDir ? "black" : "darkgreen"

                onBtnClicked: {
                    var clickedFileURL = folderModel.get(index,"fileURL")
                    var clickedFileSuffix = folderModel.get(index,"fileSuffix")
                    if(fileIsDir) {
                        folderModel.folder = clickedFileURL
                    } else {
                        var res = MapManager.parseFile(clickedFileURL,clickedFileSuffix)
                        mapFileLoaded(res)
                    }
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: fileIsDir ? "" : ""

                }
            }
        }
    }
}

