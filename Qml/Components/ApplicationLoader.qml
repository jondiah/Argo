import QtQuick 2.0

Loader {
    id: appLoader
    anchors.fill: parent
    active: false

    property bool applicationToLoad: false
    property string applicationUrl: ""
    property string runningApplication: "None"

    onStatusChanged: {
        if(status === Loader.Null) {
            runningApplication = "None"
        } else if(status === Loader.Ready) {
            appLoader.item.openFinished.connect(currentApplicationOpen)
            appLoader.item.closeFinished.connect(currentApplicationClosed)
            appLoader.item.openApplication()
            runningApplication = appLoader.item.objectName
        } else if(status === Loader.Loading) {

        } else if(status === Loader.Error) {

        }
    }

    function loadApplication(name) {
        if(appLoader.item == undefined) {
            source = name;
            active = true

            applicationToLoad = false
            applicationUrl = ""

        } else {
            applicationToLoad = true
            applicationUrl = name

            // Application is running, close it first
            appLoader.item.closeApplication()
        }
    }

    function currentApplicationClosed() {
        appLoader.item.openFinished.disconnect(currentApplicationOpen)
        appLoader.item.closeFinished.disconnect(currentApplicationClosed)
        active = false
        source = ""

        if(applicationToLoad) {
            loadApplication(applicationUrl)
        }
    }

    function currentApplicationOpen() {
    }
}
