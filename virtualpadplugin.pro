QT          += widgets uiplugin

CONFIG += c++17

QTDIR_build {
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = VirtualPadPlugin
load(qt_plugin)
CONFIG += install_ok
} else {
CONFIG      += plugin
TEMPLATE    = lib
TARGET = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

}

HEADERS     = virtualpadplugin.h
SOURCES     = virtualpadplugin.cpp
#!

RESOURCES += \
    icons.qrc

include (qvirtualpad/qvirtualpad.pri)
