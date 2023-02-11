# QVirtualPad

QVirtualPad is a Qt widget that implements an interactive virtual pad (or virtual joystick if you like but I found that it resembles more a pad).
The installation/use is pretty straightforward, since the widget is distributed as source code
at this moment the only steps you need are to download the two main source files:
- ```qvirtualpad.h```
- ```qvirtualpad.cpp```

copy these files into you source code folder and then include them in you project.
To use the widget you simply have to *promote* a widget in your ui to ```QVirtualPad``` class (referencing the correct header: ```qvirtualpad.h``` of course).
You don't need to make the widget square but for a better user experience the widget will always use a square footprint.
Once placed in your ui you can choose between two usage mode:
- event driven;
- polling;

In the event driven method you simply connect to the ```positionUpdate``` signal and then wait for the user to *move* the pad. At every movement you will receive an update event along with a ```QPointF``` argument with the current normalized axis value [-1..1].

If you choose the polling method instead you simply have to call ```X()``` and ```Y()``` getters to acquire normalized axis values.

You can customize the look and behaviour of the widget trough its properties.
You can find an example of the code needed to use this widget in the associated Qt application (```virtualpad.pro```).

For the sake of documentation this is a complete list of ```QVirtualPad``` widget properties and their usage:

- ```QColor backgroundColor```: is the main color of the background gradient (default: ```Qt::red```).
- ```QColor backgroundFocusColor```: is the color of the focal point of the background gradient (default: ```Qt::white```).
- ```QColor padColor```: is the main color of the pad gradient (default: ```Qt::black```).
- ```QColor padFocusColor```: is the color of the focal point of the pad gradient (default: ```Qt::white```).
- ```QColor borderColor```: is the color of the external border of both background and pad (default: ```Qt::black```).
- ```int borderWidth```: is the thickness of the external border (default: ```1```).
- ```float opacity```: is the opacity of the widget itself (0 fully transparent 1 completely opaque: default: ```1```) 
- ```bool momentary```: this property tells if the pad will return to the center position when left or if it will stay in the last position reached (default: ```true```).
- ```float padSizeRatio```: is the dimensional ratio of the pad against the widget size (minimum ```0.1```, maximum ```0.66```, default: ```0.5```)
- ```bool externalDeadZone```: this propery enables/disable the external circular dead zone (default: ```false```)
- ```float deadZone```: internal dead zone radius (in normalized units default: ```0```)
- ```Axis axis```: this property tells if the widget moves along two axis (```Both```, default) or just along one (```X```,```Y```)
- ```Marks marks```: this property tells if you want direction marks depicted on the background you can choose between none (```None```, default), four indicators (```NSWE```) or eight indicators (```Full```). Please note that if you choose a single axis movement only the indicator of the free axis available movement  will be drawn.

There are also a number of static constants made public for reference use:
- ```DEF_PAD_SIZE_RATIO```  (default pad size ratio, see above)
- ```MAX_PAD_SIZE_RATIO```  (maximum pad size ratio, see above)
- ```MIN_PAD_SIZE_RATIO```  (minimum pad size ratio, see above)
- ```DEF_FOCAL_POS_RATIO``` (this is the position ratio of the focal point inside gradients)
- ```DEF_MARKS_OFF_RATIO``` (this is the offset ratio of the direction marks drawn on background)

If you are guessing how this widget may look like:

![QVirtualPad in all its beauty](images/screenshot1.png?raw=true "QVirtualPad")

This's the widget running inside its associated Qt application.

## Known bugs/missing features

- ~~External deadzone: this's not working at the moment~~
- ```Full``` marks setting: works as ```NSWE``` (missing diagonal directions) 

## TODO

- Distribute as subproject (.pri)
- Distribute as library
- Integration in Qt Designer (?!)
- Translation
- Docs (doxygen)
#

Live long and prosper!

That's all folks.

Bye by[t]e[s]...Weirdgyn!
