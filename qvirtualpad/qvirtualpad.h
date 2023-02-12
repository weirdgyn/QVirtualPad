#ifndef QVIRTUALPAD_H
#define QVIRTUALPAD_H

#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>

/* TODO:
 *    oval background shape  in single axis movement?
 *    Complete mmissingg marks (SW,NE,SE,NW)
 *    fix external deadzone
 */

class QVirtualPad : public QWidget {
  Q_OBJECT

public:
  constexpr static const float DEF_PAD_SIZE_RATIO = 0.5f;
  constexpr static const float MAX_PAD_SIZE_RATIO = 0.66f;
  constexpr static const float MIN_PAD_SIZE_RATIO = 0.1f;
  constexpr static const float DEF_FOCAL_POS_RATIO = 0.5f;
  constexpr static const float DEF_MARKS_OFF_RATIO = 0.95f;
  constexpr static const float MARKS_SIZE_RATIO = 0.0286f;  // 1/35

  enum class Axis { Both = 0, X, Y };
  Q_ENUM(Axis)

  static QString AxisToString(Axis axis);
  static Axis StringToAxis(QString axis);

  enum class Marks { None = 0, NSWE, Full };
  Q_ENUM(Marks)

  static QString MarksToString(Marks axis);
  static Marks StringToMarks(QString marks);

  explicit QVirtualPad(QWidget *parent = nullptr);

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE
                 setBackgroundColor NOTIFY backgroundColorChanged)
  QColor backgroundColor() const;
  void setBackgroundColor(const QColor &backgroundColor);

  Q_PROPERTY(QColor backgroundFocusColor READ backgroundFocusColor WRITE
                 setBackgroundFocusColor NOTIFY backgroundFocusColorChanged)
  QColor backgroundFocusColor() const;
  void setBackgroundFocusColor(const QColor &backgroundFocusColor);

  Q_PROPERTY(
      QColor padColor READ padColor WRITE setPadColor NOTIFY padColorChanged)
  QColor padColor() const;
  void setPadColor(const QColor &padColor);

  Q_PROPERTY(QColor padFocusColor READ padFocusColor WRITE setPadFocusColor
                 NOTIFY padFocusColorChanged)
  QColor padFocusColor() const;
  void setPadFocusColor(const QColor &padFocusColor);

  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY
                 borderColorChanged)
  QColor borderColor() const;
  void setBorderColor(const QColor &borderColor);

  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
                 borderWidthChanged)
  int borderWidth() const;
  void setBorderWidth(int borderWidth);

  Q_PROPERTY(
      bool momentary READ momentary WRITE setMomentary NOTIFY momentaryChanged)
  bool momentary() const;
  void setMomentary(bool momentary);

  Q_PROPERTY(Axis axis READ axis WRITE setAxis NOTIFY axisChanged)
  Axis axis() const;
  void setAxis(Axis axis);

  Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
  float opacity() const;
  void setOpacity(float opacity);

  Q_PROPERTY(float padSizeRatio READ padSizeRatio WRITE setPadSizeRatio NOTIFY
                 padSizeRatioChanged)
  float padSizeRatio() const;
  void setPadSizeRatio(float padSizeRatio);

  Q_PROPERTY(bool externalDeadZone READ externalDeadZone WRITE
                 setExternalDeadZone NOTIFY externalDeadZoneChanged)
  bool externalDeadZone() const;
  void setExternalDeadZone(bool externalDeadZone);

  Q_PROPERTY(
      float deadZone READ deadZone WRITE setDeadZone NOTIFY deadZoneChanged)
  float deadZone() const;
  void setDeadZone(float deadZone);

  Q_PROPERTY(Marks marks READ marks WRITE setMarks NOTIFY marksChanged)
  Marks marks() const;
  void setMarks(Marks marks);

  double x();
  double y();

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void resize();
  QRectF getFrame();
  QPointF getWidgetFrameOffset(QSizeF widgetSize);
  void updatePosition(double x, double y);
  QPainterPath *createMarks();
  QPainterPath *createMark(double angle, QPointF offset);

  void drawMarks(QPainter &painter);
  void drawPad(QPainter &painter);
  void drawBackground(QPainter &painter);

signals:
  void positionUpdate(QPointF point);
  void backgroundColorChanged();
  void backgroundFocusColorChanged();
  void padColorChanged();
  void padFocusColorChanged();
  void borderColorChanged();
  void borderWidthChanged();
  void momentaryChanged();
  void axisChanged();
  void opacityChanged();
  void padSizeRatioChanged();
  void externalDeadZoneChanged();
  void deadZoneChanged();
  void marksChanged();

private:
  QRectF mWidgetFrame;
  bool mClicked;
  QPoint mPadPosition;
  QPointF mValueAxis;
  QGraphicsOpacityEffect mOpacityEffect = QGraphicsOpacityEffect(this);
  float mBackgrounddFocalPosRatio;
  float mPadFocalPosRatio;

  // PROPERTIES
  int mBorderWidth;
  float mPadSizeRatio;
  bool mMomentary;
  QColor mBackgroundColor;
  QColor mBackgroundFocusColor;
  QColor mPadColor;
  QColor mPadFocusColor;
  QColor mBorderColor;
  Axis mAxis;
  float mOpacity;
  bool mExternalDeadZone;
  float mDeadZone;
  Marks mMarks;
};

#endif // QVIRTUALPAD_H
