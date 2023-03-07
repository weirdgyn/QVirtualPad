#include "qvirtualpadplugin.h"
#include "qvirtualpad/qvirtualpad.h"

QVirtualPadPlugin::QVirtualPadPlugin(QObject *parent) : QObject(parent) {}

void QVirtualPadPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
  if (initialized)
    return;

  initialized = true;
}

bool QVirtualPadPlugin::isInitialized() const { return initialized; }

QWidget *QVirtualPadPlugin::createWidget(QWidget *parent) {
  return new QVirtualPad(parent);
}

QString QVirtualPadPlugin::name() const { return QStringLiteral("QVirtualPad"); }

QString QVirtualPadPlugin::group() const {
  return QStringLiteral("Custom widgets");
}

QIcon QVirtualPadPlugin::icon() const { return QIcon(QLatin1String(":/images/virtualpad.ico")); }

QString QVirtualPadPlugin::toolTip() const { return QString(); }

QString QVirtualPadPlugin::whatsThis() const { return QString(); }

bool QVirtualPadPlugin::isContainer() const { return false; }

QString QVirtualPadPlugin::domXml() const {
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

QString QVirtualPadPlugin::includeFile() const {
  return QStringLiteral("qvirtualpad/qvirtualpad.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qvirtualpadplugin, QVirtualPadPlugin)
#endif // QT_VERSION < 0x050000
