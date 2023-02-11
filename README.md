# QVirtualPad

QVirtualPad is a Qt widget that implements an interactive virtual pad (or virtual joystick 
if you like but I found it more resembling a pad).
The installation/use is pretty straightforward, since the widget is distributed as source code
at this moment the only steps you need is to download the two main source files:
- qvirtualpad.h
- qvirtualpad.cpp

copy these files into you source code folder and the include it in you project.
To use the widget you simply add to 'promote' a widget in you ui to QVirtualPad class (referincing 
the correct header: qvirtualpad.h of course).
You can then customize the behaviour of the widget trough its properties.
You can find a detailed description of the code needed to use the widget in the associated Qt application
(virtualpad.pro).
For the sake of documentation this's a complete list of QVirtualPad widget properties and their usage:


