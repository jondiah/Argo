import QtQuick 2.0
import MapManager 1.0
import "GoogleMapsInteraction.js" as GM

import "../Components"

Rectangle {
    id: truckerListCont
    state: "closed"
    states:[
        State {
            name: "open"
            AnchorChanges {
                target: truckerListCont
                anchors.left: truckerListCont.parent.left
                anchors.right: undefined
            }
        },
        State {
            name: "closed"
            AnchorChanges {
                target: truckerListCont
                anchors.right: truckerListCont.parent.left
                anchors.left: undefined
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
        id: truckerList
        anchors.centerIn: parent
        height: parent.height-10
        width: 200
        currentIndex: -1
        clip: true
        model: MapManager.runningModel

        onCountChanged: {
            if(count > 0) {
                truckerListCont.state = "open"
            } else {
                truckerListCont.state = "closed"
            }
        }

        delegate: Button {
            width: 200
            height: 50
            radius: 0
            text: name
            textFont.underline: truckerList.currentIndex === index ? true : false
            textHAlignment: Text.AlignLeft
            opacity: truckerList.currentIndex === index ? 1 : 0.5

            onBtnClicked: {
                truckerList.currentIndex = index
            }

            Rectangle {
                width: 30
                height: 30
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                radius: 15

                Rectangle {
                    width: 24
                    height: 24
                    anchors.centerIn: parent
                    radius: 12
                    color: selected ? "green" : "transparent"

                    property bool selected: true

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(parent.selected) {
                                webView.experimental.evaluateJavaScript(GM.hideTrackingObject(index))
                            }
                            else {
                                webView.experimental.evaluateJavaScript(GM.showTrackingObject(index))
                            }

                            parent.selected = !parent.selected
                        }
                    }
                }
            }
        }

        Component.onCompleted: currentIndex = 0
    }
}
