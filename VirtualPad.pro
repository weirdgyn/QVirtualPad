CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qvirtualpadplugin)
TEMPLATE    = lib

HEADERS     = qvirtualpadplugin.h
SOURCES     = qvirtualpadplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer gui multimedia svg
} else {
    CONFIG += designer gui multimedia svg
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(qvirtualpad/qvirtualpad.pri)
