TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    control.cpp

RESOURCES += qml.qrc

#создается для компиляции файлов отдельных
OTHER_FILES += \
    viewMain.qml \
    viewProjectsOnline.qml \
    viewProjectsOffline.qml \

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    control.h
