# QVirtualPad

QVirtualPad is a Qt5 widget that implements an interactive virtual pad (or virtual joystick if you like but I found that it resembles more a pad).

To use this widget you should download the source code of this repository and then you can opt between:
- use the class code directly adding  ```qvirtualpad.h ```,  ```qvirtualpad.cpp ``` files to your code;
- include the class folder adding a  ```include(qvirtualpad/qvirtualpad.pri) ``` directive to your  ```.pro ``` file.

Optionally you can compile the widget plugin to enhance the visual integration experience (load  ```VirtualPad.pro ``` file).

If you have installed succesfully the plugin you can enjoy the full user experience as you can drop QVirtualPad into your form straight form the pallette in QtCreator (or QtDesigner), there you can manage properties as any other widget.
If you are using QVirtualPad trough source code then you can add the widget to the UI programatically or you have to *promote* a widget _placeholder_ in your UI to ```QVirtualPad``` class (referencing the correct header: ```qvirtualpad.h``` of course).
You don't need to make the _placeholder_ square but to enhance its look & feel ```QVirtualPad``` have beend designed to always _use_ a square footprint (inside assigned widget area).
Besides the way you placed QVirtualPad in your UI you can choose between two usage mode:
- event driven
- polling

With event driven method you simply need to connect to the ```positionUpdate``` signal and then wait for the user to *move* the pad. At every movement you will receive an update event along with a ```QPointF``` argument with the current normalized axis value ```[-1..1]```.
Axis ranges uses canonical math convention so x,y are 0 at origin/center of the pad and increase up to 1 respectively going right and up, simmetrically they decrease going left and down up to -1.

If you choose the polling method instead you simply have to call ```X()``` and ```Y()``` getters to acquire normalized axis values.

You can customize the look and behaviour of the widget through its properties.
You can find an example of the code needed to use this widget in the associated Qt application (```Test.pro```).

For the sake of documentation this is a complete list of ```QVirtualPad``` widget properties and their usage:

- ```QColor backgroundColor```: is the main color of the background gradient (default: ```Qt::red```).
- ```QColor backgroundFocalColor```: is the color of the focal point of the background gradient (default: ```Qt::white```). Note if you specify the same color as ```backgroundColor``` you'll get a flat appearance.
- ```QColor padColor```: is the main color of the pad gradient (default: ```Qt::black```).
- ```QColor padFocalColor```: is the color of the focal point of the pad gradient (default: ```Qt::white```). Note if you specify the same color as ```padColor``` you'll get a flat pad appearance.
- ```QColor borderColor```: is the color of the external border of both background and pad area (default: ```Qt::black```).
- ```int borderWidth```: is the thickness of border (default: ```1```).
- ```float opacity```: is the opacity of the widget itself (```0``` fully transparent ```1``` completely opaque, default) 
- ```bool momentary```: this property tells if the pad will return to the center position when left (```true```, default) or if it will stay in the last position reached (```false```).
- ```float padSizeRatio```: is the dimensional ratio of the pad against the widget size (minimum ```0.1f```, maximum ```0.66f```, default: ```0.5f```)
- ```bool externalDeadZone```: this propery enables/disable movement of the pad outside background zone (default: ```false```). Please note that also axis values are therefore limited.
- ```float deadZone```: internal dead zone radius (in normalized units default: ```0```)
- ```Axis axis```: this property tells if the widget moves along two axis (```Both```, default) or just one (```X```,```Y```)
- ```Marks marks```: this property tells if you want direction marks depicted on the background. You can choose between none (```None```, default), four indicators (```NSWE```) or eight indicators (```Full```). Please note that if you choose a single _axis_ mode only marks on enabled movements will be drawn.

There are also a number of static constants made public for reference use:
- ```DEF_PAD_SIZE_RATIO```  (default pad size ratio, see above)
- ```MAX_PAD_SIZE_RATIO```  (maximum pad size ratio, see above)
- ```MIN_PAD_SIZE_RATIO```  (minimum pad size ratio, see above)
- ```DEF_FOCAL_POS_RATIO``` (this is the position ratio of the focal point inside gradients)
- ```DEF_MARKS_OFF_RATIO``` (this is the offset ratio of the direction marks drawn on background)

If you are guessing how this widget may look like:

![QVirtualPad in all its beauty](images/screenshot1.png?raw=true "QVirtualPad in all its beauty")

This is the widget running in its associated Qt application.

## Known bugs/missing features
- ~~External deadzone: this's not working at the moment~~
- ~~Full marks setting: works as NSWE (missing diagonal directions)~~ 
- ~~Non square widget area lead to misplaced marks drawings (top or left) and axis values~~
- Plugin/widget compilation issues on Windows environment

## TODO
- ~~Distribute as Qt subproject (.pri)~~
- Distribute as library/plugin
- ~~Integration in _Qt Designer_ (?!)~~
- Translation
- ~~Docs (doxygen)~~
- Add support for stylesheets
- More features...

## References
[Qt framework](http://qt.io)

## License
Copyright 2023 Michele Santucci.
This product is released under MIT License.

## Greetings
Thanks to everyone collaborating... special mention to my nephew Lorenzo for its help in fixing **External deadzone** feature.
#

Live long and prosper!

That's all folks.

Bye by[t]e[s]...Weirdgyn!
