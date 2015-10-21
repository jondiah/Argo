import QtQuick 2.0

Rectangle {
    id: appWindow
    anchors.fill: parent
    visible: false
    opacity: 0
    scale: 0
    clip: true

    property alias applicationState: internalState.state

    signal closeFinished()
    signal openFinished()

    function closeApplication() {
        internalState.state = "closed"
    }

    function openApplication() {
        internalState.state = "open"
    }

    function openAnimationFinsihed() {
        openFinished()
    }

    function closeAnimationFinished() {
        closeFinished()
    }

    function minimizeWindow() {
        internalState.state = "minimized"
    }

    StateGroup {
        id: internalState
        state: "closed"
        states: [
            State {
                name: "open"
                PropertyChanges {
                    target: appWindow
                    opacity: 1
                    scale: 1
                }
            },
            State {
                name: "closed"
                PropertyChanges {
                    target: appWindow
                    opacity: 0
                    scale: 0
                }
            },
            State {
                name: "minimized"
                PropertyChanges {
                    target: appWindow
                    opacity: 0.7
                    scale: 0.35
                }
            }
        ]
        transitions: [
            Transition {
                from: "*"
                to: "open"
                SequentialAnimation {
                    PropertyAction { target: appWindow; property: "visible"; value: true}
                    ParallelAnimation {
                        NumberAnimation { target: appWindow; property: "opacity"; duration: 500 }
                        NumberAnimation { target: appWindow; property: "scale"; duration: 500 }
                    }
                    ScriptAction { script: openAnimationFinsihed() }
                }
            },
            Transition {
                from: "*"
                to: "closed"
                SequentialAnimation {
                    ParallelAnimation {
                        NumberAnimation { target: appWindow; property: "opacity"; duration: 500 }
                        NumberAnimation { target: appWindow; property: "scale"; duration: 500 }
                    }
                    PropertyAction { target: appWindow; property: "visible"; value: false}
                    ScriptAction { script: closeAnimationFinished() }
                }
            },
            Transition {
                from: "*"
                to: "minimized"
                SequentialAnimation {
                    ParallelAnimation {
                        NumberAnimation { target: appWindow; property: "opacity"; duration: 500 }
                        NumberAnimation { target: appWindow; property: "scale"; duration: 500 }
                    }
                }
            }
        ]
    }

//    Row {
//        anchors.right: parent.right
//        anchors.top: parent.top
//        anchors.margins: 5
//        spacing: 5
//        z: 100
//        Button {
//            text: "_"
//            onBtnClicked: {
//                minimizeWindow()
//            }
//        }
//        Button {
//            text: "X"
//            onBtnClicked: {
//                closeApplication()
//            }
//        }
//    }

//    MouseArea {
//        z: 101
//        anchors.fill: parent
//        enabled: internalState.state === "minimized"
//        onClicked: openApplication()
//    }
}
