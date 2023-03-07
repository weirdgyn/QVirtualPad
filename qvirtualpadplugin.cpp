#include "virtualpadplugin.h"
#include "qvirtualpad/qvirtualpad.h"

VirtualPadPlugin::VirtualPadPlugin(QObject *parent) : QObject(parent) {}

void VirtualPadPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
  if (initialized)
    return;

  initialized = true;
}

bool VirtualPadPlugin::isInitialized() const { return initialized; }

QWidget *VirtualPadPlugin::createWidget(QWidget *parent) {
  return new QVirtualPad(parent);
}

QString VirtualPadPlugin::name() const { return QStringLiteral("QVirtualPad"); }

QString VirtualPadPlugin::group() const {
  return QStringLiteral("Custom widgets");
}

QIcon VirtualPadPlugin::icon() const { return QIcon(QLatin1String(":/images/virtualpad.ico")); }

QString VirtualPadPlugin::toolTip() const { return QString(); }

QString VirtualPadPlugin::whatsThis() const { return QString(); }

bool VirtualPadPlugin::isContainer() const { return false; }

QString VirtualPadPlugin::domXml() const {
  return "<ui language=\"c++\" displayname=\"Virtual Pad\">\n"
         " <widget class=\"QVirtualPad\" name=\"virtualPad\">\n"
         "  <property name=\"geometry\">\n"
         "   <rect>\n"
         "    <x>0</x>\n"
         "    <y>0</y>\n"
         "    <width>300</width>\n"
         "    <height>300</height>\n"
         "   </rect>\n"
         "  </property>\n"
         "  <property name=\"toolTip\" >\n"
         "   <string>Virtual pad/joystick</string>\n"
         "  </property>\n"
         "  <property name=\"whatsThis\" >\n"
         "   <string>A virtual pad to use inside applications.</string>\n"
         "  </property>\n"
         " </widget>\n"
         "</ui>\n";
}

QString VirtualPadPlugin::includeFile() const {
  return QStringLiteral("qvirtualpad/qvirtualpad.h");
}
