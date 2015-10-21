import QtQuick 2.0

Rectangle {
    color: "white"
    border.color: "black"
    width: 100
    height: 25
    radius: 5

    property alias text: textInput.text

    TextEdit {
        id: textInput
        anchors.fill: parent
        anchors.margins: 5
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: ""
    }
}
