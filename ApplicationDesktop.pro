TEMPLATE = app
QT += qml quick

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

SOURCES += main.cpp \
    Connection/ConnectionManager.cpp \
    FileHandling/FileParser.cpp \
    Trucker/TruckerModel.cpp \
    Trucker/TruckerItem.cpp \
    Map/MapManager.cpp \
    Map/MapSettings.cpp \
    Connection/MessageHandler.cpp \
    ApplicationManager.cpp \
    Trucker/TrackingObjectsModel.cpp \
    Trucker/TrackingItem.cpp

include(deployment.pri)

HEADERS += \
    Connection/ConnectionManager.h \
    FileHandling/FileParser.h \
    Trucker/TruckerModel.h \
    Trucker/TruckerItem.h \
    Map/MapManager.h \
    Map/MapSettings.h \
    Connection/MessageHandler.h \
    ApplicationManager.h \
    Trucker/TrackingObjectsModel.h \
    Trucker/TrackingItem.h

RESOURCES += \
    qml.qrc \
    images.qrc \
    fonts.qrc

OTHER_FILES +=

