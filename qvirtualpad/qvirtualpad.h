#ifndef QVIRTUALPAD_H
#define QVIRTUALPAD_H

#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

/**
 * @brief implements an interactive virtual pad/joystick.
 * 
 */
class QDESIGNER_WIDGET_EXPORT QVirtualPad : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Pad size ratio against full widget frame.
   * 
   */
  constexpr static const float DEF_PAD_SIZE_RATIO = 0.5f;

  /**
   * @brief Max pad size ratio. 
   * 
   */
  constexpr static const float MAX_PAD_SIZE_RATIO = 0.66f;

  /**
   * @brief Min pad size ratio.
   * 
   */
  constexpr static const float MIN_PAD_SIZE_RATIO = 0.1f;

  /**
   * @brief Focal point pos ratio against focal size.
   * 
   */
  constexpr static const float DEF_FOCAL_POS_RATIO = 0.5f;

  /**
   * @brief Direction marks offset ratio against widget frame size.
   * 
   */
  constexpr static const float DEF_MARKS_OFF_RATIO = 0.9f;

  /**
   * @brief Size ratio of direction markings againsta widget frame size.
   * 
   */
  constexpr static const float MARKS_SIZE_RATIO = 0.0286f;  // 1/35
  
  /**
   * @brief Allowed axis movements.
   * 
   */
  enum class Axis { 
    Both = 0, /**< Both axis allowed  */ 
    X,        /**< Only X allowed     */
    Y         /**< Only Y allowed     */
  };
  Q_ENUM(Axis)

  /**
   * @brief Convert argument into a readable string.
   * 
   * @param axis 
   * @return QString 
   * @see Axis
   */
  static QString AxisToString(Axis axis);

  /**
   * @brief Convert argument string in an Axis value.
   * 
   * @param axis 
   * @return Axis 
   * @see Axis
   */
  static Axis StringToAxis(QString axis);

  /**
   * @brief Direction markings.
   * @see Marks
   */
  enum class Marks { 
    None = 0, /**< No marks */ 
    NSWE,     /**< 4 marks */
    Full      /**< 8 marks */
  };
  Q_ENUM(Marks)

  /**
   * @brief Convert argument into a readable string.
   * 
   * @param axis 
   * @return QString 
   * @see Marks
   */
  static QString MarksToString(Marks axis);

  /**
   * @brief Convert argument string in a Marks value.
   * 
   * @param marks 
   * @return Marks 
   */
  static Marks StringToMarks(QString marks);

  /**
   * @brief Construct a new QVirtualPad object
   * 
   * @param parent 
   */
  explicit QVirtualPad(QWidget *parent = nullptr);

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE
                 setBackgroundColor NOTIFY backgroundColorChanged)
  /**
   * @brief backgroundColor property getter.
   * 
   * @return QColor backgroundColor value
   * @see mBackgroundColor
   */
  QColor backgroundColor() const;
  /**
   * @brief backgroundColor property setter.
   * 
   * @param backgroundColor new value
   * @see mBackgroundColor
   */
  void setBackgroundColor(const QColor &backgroundColor);

  Q_PROPERTY(QColor backgroundFocusColor READ backgroundFocusColor WRITE
                 setBackgroundFocusColor NOTIFY backgroundFocusColorChanged)
  /**
   * @brief backgroundFocusColor property getter.
   * 
   * @return QColor backgroundFocusColor value
   * @see mBackgroundFocusColor
   */
  QColor backgroundFocusColor() const;
  /**
   * @brief backgroundFocusColor property setter.
   * 
   * @param backgroundFocusColor new value 
   * @see mBackgroundFocusColor
   */
  void setBackgroundFocusColor(const QColor &backgroundFocusColor);

  Q_PROPERTY(
      QColor padColor READ padColor WRITE setPadColor NOTIFY padColorChanged)
  /**
   * @brief padColor property getter.
   * 
   * @return QColor padColor value
   * @see mPadColor 
   */
  QColor padColor() const;
  /**
   * @brief padColor property setter.
   * 
   * @param padColor new value
   * @see mPadColor 
   */
  void setPadColor(const QColor &padColor);

  Q_PROPERTY(QColor padFocusColor READ padFocusColor WRITE setPadFocusColor
                 NOTIFY padFocusColorChanged)
  /**
  * @brief padFocalColor property getter.
  * 
  * @return QColor padFocalColor value
  * @see mPadFocalColor
  */
  QColor padFocalColor() const;
  /**
   * @brief padFocalColor property setter.
   * 
   * @param padFocalColor new value
   * @see mPadFocalColor
   */
  void setPadFocalColor(const QColor &padFocalColor);

  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY
                 borderColorChanged)
  /**
   * @brief borderColor property getter.
   * 
   * @return QColor borderColor value
   * @see mBorderColor 
   */
  QColor borderColor() const;
  /**
   * @brief borderColor property setter.
   * 
   * @param borderColor new value
   * @see mBorderColor 
   */
  void setBorderColor(const QColor &borderColor);

  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
                 borderWidthChanged)
  /**
   * @brief borderWidth property getter.
   * 
   * @return int borderWidth value
   * @see mBorderWidth 
   */
  int borderWidth() const;
  /**
   * @brief borderWidth property setter.
   * 
   * @param borderWidth new value
   * @see mBorderWidth
   */
  void setBorderWidth(int borderWidth);

  Q_PROPERTY(
      bool momentary READ momentary WRITE setMomentary NOTIFY momentaryChanged)
  /**
   * @brief momentary property getter.
   * 
   * @return true the pad position is momentary (returns to center when left)
   * @return false the pad position is sticky (stay in the last position reached when left)
   * @see mMomentary
   */
  bool momentary() const;
  /**
   * @brief momentarey property setter.
   * 
   * @param momentary 
   * @see mMomentary
   */
  void setMomentary(bool momentary);

  Q_PROPERTY(Axis axis READ axis WRITE setAxis NOTIFY axisChanged)
  /**
   * @brief axis property getter.
   * 
   * @return Axis axis value
   * @see Axis, mAxis
   */
  Axis axis() const;
  /**
   * @brief axis property setter.
   * 
   * @param axis new value
   * @see Axis, mAxis
   */
  void setAxis(Axis axis);

  Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
  /**
   * @brief opacity property getter.
   * 
   * @return float opacity value
   * @see mOpacity
   */
  float opacity() const;
  /**
   * @brief opacity property setter.
   * 
   * @param opacity new value
   * @see mOpacity
   */
  void setOpacity(float opacity);

  Q_PROPERTY(float padSizeRatio READ padSizeRatio WRITE setPadSizeRatio NOTIFY
                 padSizeRatioChanged)
  /**
   * @brief padSizeRatio property getter.
   * 
   * @return float padSizeRatio value
   * @see mPadSizeRatio
   */
  float padSizeRatio() const;
  /**
   * @brief padSizeRatio property setter.
   * 
   * @param padSizeRatio new value
   * @see mPadSizeRatio
   */
  void setPadSizeRatio(float padSizeRatio);

  Q_PROPERTY(bool externalDeadZone READ externalDeadZone WRITE
                 setExternalDeadZone NOTIFY externalDeadZoneChanged)
  /**
   * @brief externalDeadZone property getter.
   * 
   * @return true movements of pad are limited inside a circular area of radius = 1 
   * @return false movements of pad are allowed to a sqare area with edges length = 2
   * @see mExternalDeadZone
   */
  bool externalDeadZone() const;
  /**
   * @brief externalDeadZone property setter.
   * 
   * @param externalDeadZone new value
   * @see mExternalDeadZone
   */
  void setExternalDeadZone(bool externalDeadZone);

  Q_PROPERTY(
      float deadZone READ deadZone WRITE setDeadZone NOTIFY deadZoneChanged)
  /**
   * @brief deadZone property getter.
   * 
   * @return float deadZone value
   * @see mDeadZone
   */
  float deadZone() const;
  /**
   * @brief deadZone property setter.
   * 
   * @param deadZone new value
   * @see mDeadZone
   */
  void setDeadZone(float deadZone);

  Q_PROPERTY(Marks marks READ marks WRITE setMarks NOTIFY marksChanged)
  /**
   * @brief marks property getter.
   * 
   * @return Marks marks value
   * @see Marks, mMarks
   */
  Marks marks() const;
  /**
   * @brief marks property setter.
   * 
   * @param marks new value
   * @see Marks, mMarks
   */
  void setMarks(Marks marks);

  /**
   * @brief X axis normalized value [-1...1]
   * 
   * @return double
   * @see mValueAxis
   */
  double x();
  /**
   * @brief Y axis normalized value [-1...1]
   * 
   * @return double 
   * @see mValueAxis
   */  
  double y();

protected:
  /**
   * @brief override of base class resizeEvent
   * 
   * Invoked when widget area is resized.
   * Will update internal sub-areas size accordingly with defined ratios.
   * 
   * @param event Event descriptor
   * @see resize
   */
  void resizeEvent(QResizeEvent *event);
  /**
   * @brief override of base class paintEvent.
   * 
   * Invoked when widget area need to be repainted.
   * Forced by repaint() method calls.
   * Will depict widget current status.
   * 
   * @param event Event descriptor
   */
  void paintEvent(QPaintEvent *event);
  /**
   * @brief override of base class mousePressEvent
   * 
   * Invoked when user press mouse button/touch inside widget area.
   * This action enables pad movement.
   * 
   * @param event Event descriptor
   */
  void mousePressEvent(QMouseEvent *event);
  /**
   * @brief override of base class mouseReleaseEvent
   * 
   * Invoked when the user release mouse button/touch inside widget area.
   * This action disable pad movement.
   * Pad stay/return in last/center position depending on the momentary property value.
   * 
   * @param event event descriptor
   */  
  void mouseReleaseEvent(QMouseEvent *event);
    /**
   * @brief override of base class mouseMoveEvent
   * 
   * Invoked when user moves inside the widget area.
   * Movement are tracked only if a mousePressEvent has been received.
   * Tracking of user mouse pointer movements are reflected in update 
   * of pad position.
   * 
   * @param event event descriptor
   */
  void mouseMoveEvent(QMouseEvent *event);

  /**
   * @brief Resize handler
   * 
   * Handles widget resize related actions.
   * 
   * @see resizeEvent
   */
  void resize();
  /**
   * @brief Set pad position to center.
   * @see updatePosition
   */
  void center();
   /**
   * @brief Evaluate internal widget frame.
   * 
   * @return QRectF 
   */
  QRectF getFrame();
  /**
   * @brief Set pad position.
   * 
   * @param x 
   * @param y
   * @see mPadPosition
   */
  void updatePosition(double x, double y);
  /**
   * @brief Create direction marks sets (depending on marks property). 
   * 
   * @return QPainterPath* path describing marks
   * @see createMark, drawMarks, drawMark
   */
  QPainterPath *createMarks();
  /**
   * @brief Create a direction mark.
   * 
   * @param angle mark/arrow direction
   * @param offset location of mark
   * @return QPainterPath* path describing mark
   * @see createMarks, drawMarks, drawMark
   */
  QPainterPath *createMark(double angle, QPointF offset);
  /**
   * @brief Draw direction mark.
   * 
   * @param painter
   * @see createMarks, drawMarks, createMark
   */
  void drawMarks(QPainter &painter);
  /**
   * @brief Draw pad in current position.
   * 
   * @param painter 
   * @see updatePosition
   */
  void drawPad(QPainter &painter);
  /**
   * @brief draw bakground elements.
   * 
   * @param painter 
   */
  void drawBackground(QPainter &painter);

signals:
  /**
   * @brief signal an update of pad position.
   * 
   * @param point updated normalized position [-1...1]
   */
  void positionUpdate(QPointF point);
  /**
   * @brief signal an update in background color.
   * 
   */
  void backgroundColorChanged();
    /**
   * @brief signal an update in background focal point color.
   * 
   */
  void backgroundFocalColorChanged();
  /**
   * @brief signal an update in pad color.
   * 
   */
  void padColorChanged();
  /**
   * @brief signal an update in pad focal point color.
   * 
   */
  void padFocalColorChanged();
  /**
   * @brief signal an update in border color.
   * 
   */
  void borderColorChanged();
  /**
   * @brief signal an update in border width.
   * 
   */
  void borderWidthChanged();
  /**
   * @brief signal an update in momentary property.
   * 
   */
  void momentaryChanged();
  /**
   * @brief signal an update in axis property.
   * 
   */
  void axisChanged();
  /**
   * @brief signal an update in opacity property.
   * 
   */
  void opacityChanged();
  /**
   * @brief signal an update in padSizeRatio property.
   * 
   */
  void padSizeRatioChanged();
  /**
   * @brief signal an update in externalDeadZone property.
   * 
   */
  void externalDeadZoneChanged();
  /**
   * @brief signal an update in deadZone property.
   * 
   */
  void deadZoneChanged();
  /**
   * @brief signal an update in marks property.
   * 
   */  
  void marksChanged();

private:
  /**
   * @brief Widget internal frame
   * 
   * The widget frame is evaluated as the largest square area inside designed widget area.
   * The frame is centered in widget area.
   * 
   */
  QRectF mWidgetFrame;
  /**
   * @brief Store clicking status of widget.
   * 
   */
  bool mClicked;
  /**
   * @brief Current pad position.
   * 
   */  
  QPoint mPadPosition;
  /**
   * @brief Normalized value of axis.
   * 
   */  
  QPointF mValueAxis;
  /**
   * @brief Opacity effect.
   * 
   */
  QGraphicsOpacityEffect mOpacityEffect;

  // PROPERTIES
  /**
   * @brief Background focal position ratio [property].
   * @see backgroundFocalPosRatio, setBackgroundFocalPosRatio
   */
  float mBackgrounddFocalPosRatio;
  /**
   * @brief Pad focal position ratio [property].
   * @see padFocalPosRatio, setPadFocalPosRatio
   */
  float mPadFocalPosRatio;  
  /**
   * @brief Border width (pixel) [property].
   * @see borderWidth, setBorderWidth
   */
  int mBorderWidth;
  /**
   * @brief Pad size ratio [property].
   * @see padSizeRatio, setPadSizeRatio
   */
  float mPadSizeRatio;
  /**
   * @brief Momentary position [property].
   * @see momentary, setMomentary
   */
  bool mMomentary;
  /**
   * @brief Background color [property].
   * @see backgroundColor, setBackgroundColor
   */
  QColor mBackgroundColor;
  /**
   * @brief Background focal color [property].
   * @see backgroundFocalColor, setBackgroundFocalColor
   */  
  QColor mBackgroundFocalColor;
  /**
   * @brief Pad color [property].
   * @see padColor, setPadColor
   */    
  QColor mPadColor;
  /**
   * @brief Pad focal color [property].
   * @see padFocalColor, setPadFocalColor
   */    
  QColor mPadFocalColor;
  /**
   * @brief Border color [property].
   * @see padBorderColor, setBorderColor
   */      
  QColor mBorderColor;
  /**
   * @brief Momvemnt axis [property].
   * @see axis, setAxis
   */    
  Axis mAxis;
  /**
   * @brief Opacity [property].
   * @see opacity, setOpacity
   */    
  float mOpacity;
  /**
   * @brief External dead zone flag [property].
   * @see externalDeadZone, setExternalDeadZone
   */    
  bool mExternalDeadZone;
  /**
   * @brief Dead zone normalized radius [property].
   * @see deadZone, setDeadZone
   */     
  float mDeadZone;
  /**
   * @brief Direction marks [property].
   * @see marks, setMarks
   */   
  Marks mMarks;
};

#endif // QVIRTUALPAD_H
