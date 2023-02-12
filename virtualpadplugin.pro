QT          += widgets uiplugin

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

HEADERS     = qvirtualpad/qvirtualpad.h \
              virtualpadplugin.h
SOURCES     = qvirtualpad/qvirtualpad.cpp \
              virtualpadplugin.cpp
#!
