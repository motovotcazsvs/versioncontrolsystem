TEMPLATE = app

QT += qml quick core network
CONFIG += c++11

SOURCES += main.cpp \
    control.cpp \
    tcpipastm.cpp

RESOURCES += qml.qrc

#создается для компиляции файлов отдельных
OTHER_FILES += \
    ViewMain.qml \

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    control.h \
    tcpipastm.h
