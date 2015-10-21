import QtQuick 2.0

Rectangle {
    width: 10
    height: 10
    radius: 5
    color: selected ? colorEnabled : colorDisabled

    property bool selected: false
    property color colorEnabled: "green"
    property color colorDisabled: "red"
}
