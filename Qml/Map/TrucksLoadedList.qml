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
                anchors.right: truckerListCont.parent.right
                anchors.left: undefined
            }
        },
        State {
            name: "closed"
            AnchorChanges {
                target: truckerListCont
                anchors.left: truckerListCont.parent.right
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
        id: truckerList
        anchors.centerIn: parent
        height: parent.height-10
        width: 200
        currentIndex: -1
        clip: true
        model: MapManager.truckerModel

        Connections {
            target: MapManager.truckerModel
            onRowAdded: {
                webView.experimental.evaluateJavaScript(GM.addMarker(lat,lon,name,index))
            }
            onRowRemoved: {
                webView.experimental.evaluateJavaScript(GM.removeMarker(index))
            }
        }

        onCountChanged: {
            if(count > 0) {
                truckerListCont.state = "open"
            } else {
                truckerListCont.state = "closed"
            }
        }

        onCurrentIndexChanged: {
            webView.experimental.evaluateJavaScript(GM.setAnimation(currentIndex))
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
            onBtnDoubleClick: webView.experimental.evaluateJavaScript(GM.moveMapTo(latitude,longitude))

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
                                webView.experimental.evaluateJavaScript(GM.hideMarker(index))
                            }
                            else {
                                webView.experimental.evaluateJavaScript(GM.showMarker(index))
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
