# QVirtualPad

QVirtualPad is a Qt widget that implements an interactive virtual pad (or virtual joystick 
if you like but I found it more resembling a pad).
The installation/use is pretty straightforward, since the widget is distributed as source code
at this moment the only steps you need is to download the two main source files:
- qvirtualpad.h
- qvirtualpad.cpp

copy these files into you source code folder and the include it in you project.
To use the widget you simply have to 'promote' a widget in your ui to QVirtualPad class (referincing the correct header: qvirtualpad.h of course).
Once placed in your ui you can opt between two usage mode:
- event driven;
- polling;

In the event driven method you simply connect to the positionUpdate signal and then wait for the user to 'move' the pad. At every movement you will receive the update event along with a QPointF argument with the current normalized axis value [-1..1].

If you opt for the polling method instead you simply have to call X() and Y() getters to acquire actual normalized axis values.
You can customize the look and behaviour of the widget trough its properties.
You can find a detailed description of the code needed to use the widget in the associated Qt application (virtualpad.pro).

For the sake of documentation this's a complete list of QVirtualPad widget properties and their usage:

- QColor backgroundColor: is the main color of the background gradient (default red).
- QColor backgroundFocusColor: is the color of the focal point of the background gradient (default white).
- QColor padColor: is the main color of the pad gradient (default black).
- QColor padFocusColor: is the color of the focal point of the pad gradient (default white).
- QColor borderColor: is the color of the external border of both background and pad (default black).
- int borderWidth: is the thickness of the external border (default 1).
- float opacity: is the opacity of the widget itself (0 fully transparent 1 completely opaque: default 1) 
- bool momentary: this property tells if the pad will return to the center position if left or it will stay in the last position reached (default false).
- float padSizeRatio: is the dimensional ratio of the pad against the widget size (minimum 0.1, maximum 0.66: default 0.5)
- bool externalDeadZone: this propery enables/disable the external circular dead zone (default: false)
- float deadZone: internal dead zone 
