import QtQuick 2.3

Rectangle {
    width: 100
    height: 50
    radius: 10
    color: btnMa.pressed ? colorPressed : colorDefault
    opacity: buttonEnabled ? 1 : 0.5

    property alias textPointSize: btnText.font.pointSize
    property alias textColor: btnText.color
    property alias textFont: btnText.font
    property alias text: btnText.text
    property alias textVAlignment: btnText.verticalAlignment
    property alias textHAlignment: btnText.horizontalAlignment

    property color colorPressed: "darkgrey"
    property color colorDefault: "lightgray"
    property color colorText: "black"

    property bool buttonEnabled: true
    property bool buttonSelected: false

    signal btnClicked()
    signal btnPressed()
    signal btnLongPress()
    signal btnReleased()
    signal btnDoubleClick()

    Text {
        id: btnText
        anchors.fill: parent
        anchors.margins: 5
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: colorText
    }

    MouseArea {
        id: btnMa
        anchors.fill: parent
        enabled: buttonEnabled
        onClicked: btnClicked()
        onPressed: btnPressed()
        onPressAndHold: btnLongPress()
        onReleased: btnReleased()
        onDoubleClicked: btnDoubleClick()
    }
}
