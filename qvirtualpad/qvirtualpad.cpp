#include "qvirtualpad.h"

#include <QtMath>

QVirtualPad::QVirtualPad(QWidget *parent)
    : QWidget{parent}, mBorderWidth(1), mPadSizeRatio(DEF_PAD_SIZE_RATIO),
      mMomentary(true), mBackgroundColor(Qt::red),
      mBackgroundFocusColor(Qt::white), mPadColor(Qt::black),
      mPadFocusColor(Qt::white), mBorderColor(Qt::black), mAxis(Axis::Both),
      mOpacity(1), mExternalDeadZone(false), mDeadZone(0), mMarks(Marks::None) {
  mClicked = false;
  mBackgrounddFocalPosRatio = DEF_FOCAL_POS_RATIO;
  mPadFocalPosRatio = DEF_FOCAL_POS_RATIO;
  setMouseTracking(true);
  mOpacityEffect.setOpacity((float)(mOpacity));
  setAutoFillBackground(true);
  setGraphicsEffect(&mOpacityEffect);
}

QString QVirtualPad::AxisToString(Axis axis) {
  switch (axis) {
  case Axis::Both:
    return "Both";
  case Axis::X:
    return "X";
  default:
  case Axis::Y:
    return "Y";
  }
}

QVirtualPad::Axis QVirtualPad::StringToAxis(QString axis) {
  if (axis.toLower() == "both")
    return Axis::Both;
  else if (axis.toLower() == "x")
    return Axis::X;
  else // if(type.toLower()=="y")
    return Axis::Y;
}

QString QVirtualPad::MarksToString(Marks axis) {
  switch (axis) {
  case Marks::NSWE:
    return "NSWE";
  case Marks::Full:
    return "Full";
  default:
  case Marks::None:
    return "None";
  }
}

QVirtualPad::Marks QVirtualPad::StringToMarks(QString marks) {
  if (marks.toLower() == "nswe")
    return Marks::NSWE;
  else if (marks.toLower() == "full")
    return Marks::Full;
  else // if(marks.toLower()=="none")
    return Marks::None;
}

void QVirtualPad::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);

  resize();
}

void QVirtualPad::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);

  drawBackground(painter);

  drawMarks(painter);

  drawPad(painter);
}

void QVirtualPad::mousePressEvent(QMouseEvent *event) {
  mClicked = true;

  updatePosition(event->pos().x(), event->pos().y());

  repaint();
}

void QVirtualPad::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event)
  mClicked = false;

  if (mMomentary)
    updatePosition(mWidgetFrame.center().x(), mWidgetFrame.center().y());
  else
    updatePosition(event->pos().x(), event->pos().y());

  repaint();
}

void QVirtualPad::mouseMoveEvent(QMouseEvent *event) {
  if (!mClicked)
    return;

  updatePosition(event->pos().x(), event->pos().y());

  repaint();
}

void QVirtualPad::resize() {
  mWidgetFrame = getFrame();

  updatePosition(mWidgetFrame.center().x(), mWidgetFrame.center().y());
}

QRectF QVirtualPad::getFrame() {
  int _size = qMin(this->width(), this->height()) - (mBorderWidth * 2);

  QSizeF _widgetSize = QSizeF(_size, _size);

  QRectF _frame = QRectF();
  _frame.setSize(_widgetSize);

  QPointF _offsetPoint = getWidgetFrameOffset(_widgetSize);
  _frame.moveTopLeft(_offsetPoint);

  return _frame;
}

QPointF QVirtualPad::getWidgetFrameOffset(QSizeF size) {
  float _xOffset = (this->width() - size.width()) / 2 - mBorderWidth;
  float _yOffset = (this->height() - size.height()) / 2 - mBorderWidth;

  return QPointF(_xOffset, _yOffset);
}

QPainterPath *QVirtualPad::createMark(double angle, QPointF offset) {
  QPainterPath *_mark = new QPainterPath();

  QPolygonF _polygon;
  QTransform _transform;

  // Triangle
  _polygon << QPointF(-4, 0) << QPointF(0, 8) << QPointF(4, 0)
           << QPointF(-4, 0);

  double _scaleX =
      MARKS_SIZE_RATIO * mWidgetFrame.width() / _polygon.boundingRect().width();

  double _scaleY = MARKS_SIZE_RATIO * mWidgetFrame.height() /
                   _polygon.boundingRect().height();

  _transform.translate(offset.x(), offset.y());
  _transform.scale(_scaleX, _scaleY);
  _transform.rotate(angle);
  QPolygonF _final = _transform.map(_polygon);
  _mark->addPolygon(_final);

  return _mark;
}

QPainterPath *QVirtualPad::createMarks() {
  QPainterPath *_marks;

  switch (mMarks) {
  case Marks::NSWE:
    _marks = new QPainterPath();
    switch (mAxis) {
    case Axis::Both:
      _marks->addPath(*createMark(
          90, QPointF(mWidgetFrame.width() * (1 - DEF_PAD_SIZE_RATIO),
                      mWidgetFrame.center().y())));
      _marks->addPath(
          *createMark(-90, QPointF(mWidgetFrame.right() * DEF_MARKS_OFF_RATIO,
                                   mWidgetFrame.center().y())));
      _marks->addPath(*createMark(
          180, QPointF(mWidgetFrame.center().x(),
                       mWidgetFrame.height() * (1 - DEF_MARKS_OFF_RATIO))));
      _marks->addPath(
          *createMark(0, QPointF(mWidgetFrame.center().x(),
                                 mWidgetFrame.bottom() * DEF_MARKS_OFF_RATIO)));
      break;
    case Axis::X:
      _marks->addPath(*createMark(
          90, QPointF(mWidgetFrame.width() * (1 - DEF_MARKS_OFF_RATIO),
                      mWidgetFrame.center().y())));
      _marks->addPath(
          *createMark(-90, QPointF(mWidgetFrame.right() * DEF_MARKS_OFF_RATIO,
                                   mWidgetFrame.center().y())));
      break;
    case Axis::Y:
      _marks->addPath(*createMark(
          180, QPointF(mWidgetFrame.center().x(),
                       mWidgetFrame.height() * (1 - DEF_MARKS_OFF_RATIO))));
      _marks->addPath(
          *createMark(0, QPointF(mWidgetFrame.center().x(),
                                 mWidgetFrame.bottom() * DEF_MARKS_OFF_RATIO)));
      break;
    }
    break;
  case Marks::Full:
    _marks = new QPainterPath();
    switch (mAxis) {
    case Axis::Both:
      _marks->addPath(*createMark(
          90, QPointF(mWidgetFrame.width() * (1 - DEF_MARKS_OFF_RATIO),
                      mWidgetFrame.center().y())));
      _marks->addPath(
          *createMark(-90, QPointF(mWidgetFrame.right() * DEF_MARKS_OFF_RATIO,
                                   mWidgetFrame.center().y())));
      _marks->addPath(*createMark(
          180, QPointF(mWidgetFrame.center().x(),
                       mWidgetFrame.height() * (1 - DEF_MARKS_OFF_RATIO))));
      _marks->addPath(
          *createMark(0, QPointF(mWidgetFrame.center().x(),
                                 mWidgetFrame.bottom() * DEF_MARKS_OFF_RATIO)));
      break;
    case Axis::X:
      _marks->addPath(*createMark(
          90, QPointF(mWidgetFrame.width() * (1 - DEF_MARKS_OFF_RATIO),
                      mWidgetFrame.center().y())));
      _marks->addPath(
          *createMark(-90, QPointF(mWidgetFrame.right() * DEF_MARKS_OFF_RATIO,
                                   mWidgetFrame.center().y())));
      break;
    case Axis::Y:
      _marks->addPath(*createMark(
          180, QPointF(mWidgetFrame.center().x(),
                       mWidgetFrame.height() * (1 - DEF_MARKS_OFF_RATIO))));
      _marks->addPath(
          *createMark(0, QPointF(mWidgetFrame.center().x(),
                                 mWidgetFrame.bottom() * DEF_MARKS_OFF_RATIO)));
      break;
    }
    break;
  default:
  case Marks::None:
    _marks = nullptr;
  }

  return _marks;
}

void QVirtualPad::updatePosition(double x, double y) {
  if (x > mWidgetFrame.right())
    x = mWidgetFrame.right();

  if (y > mWidgetFrame.bottom())
    y = mWidgetFrame.bottom();

  if (x < mWidgetFrame.x())
    x = mWidgetFrame.x();

  if (y < mWidgetFrame.y())
    y = mWidgetFrame.y();

  if (mExternalDeadZone) {
    int _dx = x - mWidgetFrame.center().x();
    int _dy = y - mWidgetFrame.center().y();

    float _r = qSqrt(qPow(_dx, 2) + qPow(_dy, 2));
    float _r1 = mWidgetFrame.width() / 2;

    if (_r > _r1) {
      double _alfa = qAtan2(_dy, _dx);

      x = qSin(_alfa) * _r1;
      y = qCos(_alfa) * _r1;
    }
  }

  switch (mAxis) {
  case Axis::Both:
    mPadPosition.setX(x);
    mPadPosition.setY(y);
    mValueAxis.setX(x / mWidgetFrame.width());
    mValueAxis.setY(y / mWidgetFrame.height());
    break;
  case Axis::X:
    mPadPosition.setX(x);
    mPadPosition.setY(mWidgetFrame.center().y());
    mValueAxis.setX(x / mWidgetFrame.width());
    mValueAxis.setY(mWidgetFrame.center().y() / mWidgetFrame.height());
    break;
  case Axis::Y:
    mPadPosition.setX(mWidgetFrame.center().x());
    mPadPosition.setY(y);
    mValueAxis.setX(mWidgetFrame.center().x() / mWidgetFrame.width());
    mValueAxis.setY(y / mWidgetFrame.height());
    break;
  }

  mValueAxis.setX(2 * mValueAxis.x() - 1);
  mValueAxis.setY(2 * mValueAxis.y() - 1);

  if (qSqrt(qPow(mValueAxis.x(), 2) + qPow(mValueAxis.y(), 2)) < mDeadZone) {
    mValueAxis.setX(0);
    mValueAxis.setY(0);
  }

  emit positionUpdate(mValueAxis);
}

double QVirtualPad::x() { return mValueAxis.x(); }

double QVirtualPad::y() { return mValueAxis.y(); }

void QVirtualPad::drawMarks(QPainter &painter) {
  QPainterPath *_marks = createMarks();

  if (_marks != nullptr) {
    painter.setPen(mBorderColor);
    painter.setBrush(mBorderColor);
    painter.drawPath(*_marks);
  }
}

void QVirtualPad::drawPad(QPainter &painter) {
  QRadialGradient _pad_gradient(mPadPosition,
                                mWidgetFrame.width() * mPadSizeRatio / 2);

  _pad_gradient.setColorAt(0, mPadFocusColor);
  _pad_gradient.setColorAt(1, mPadColor);

  _pad_gradient.setFocalPoint(
      _pad_gradient.center().x() + _pad_gradient.radius() * mPadFocalPosRatio,
      _pad_gradient.center().y() + _pad_gradient.radius() * mPadFocalPosRatio);

  QBrush _pad_brush(_pad_gradient);

  QRectF _rect(mWidgetFrame);

  QRectF _pad_rect = QRectF(0, 0, _rect.size().width() * mPadSizeRatio,
                            _rect.size().height() * mPadSizeRatio);

  _pad_rect.moveCenter(mPadPosition);

  painter.setBrush(_pad_brush);

  painter.drawEllipse(_pad_rect);
}

void QVirtualPad::drawBackground(QPainter &painter) {
  QRadialGradient _gradient(mWidgetFrame.center(), mWidgetFrame.width() / 2);

  _gradient.setColorAt(0, mBackgroundFocusColor);
  _gradient.setColorAt(1, mBackgroundColor);

  _gradient.setFocalPoint(
      _gradient.center().x() + _gradient.radius() * mBackgrounddFocalPosRatio,
      _gradient.center().y() + _gradient.radius() * mBackgrounddFocalPosRatio);

  QBrush _brush(_gradient);

  QPen _pen(mBorderColor);

  QRectF _rect(mWidgetFrame);

  _pen.setWidth(mBorderWidth);

  painter.setPen(_pen);

  painter.setBrush(_brush);

  painter.drawEllipse(_rect);
}

QVirtualPad::Marks QVirtualPad::marks() const { return mMarks; }

void QVirtualPad::setMarks(QVirtualPad::Marks marks) {
  if (mMarks == marks)
    return;
  mMarks = marks;
  emit marksChanged();
  repaint();
}

float QVirtualPad::deadZone() const { return mDeadZone; }

void QVirtualPad::setDeadZone(float deadZone) {
  if (qFuzzyCompare(mDeadZone, deadZone))
    return;

  if (deadZone < 0 || deadZone > 1)
    return;

  mDeadZone = deadZone;
  emit deadZoneChanged();
  repaint();
}

bool QVirtualPad::externalDeadZone() const { return mExternalDeadZone; }

void QVirtualPad::setExternalDeadZone(bool externalDeadZone) {
  if (mExternalDeadZone == externalDeadZone)
    return;
  mExternalDeadZone = externalDeadZone;
  emit externalDeadZoneChanged();
  repaint();
}

float QVirtualPad::padSizeRatio() const { return mPadSizeRatio; }

void QVirtualPad::setPadSizeRatio(float padSizeRatio) {
  if (mPadSizeRatio == padSizeRatio)
    return;

  if (padSizeRatio > MAX_PAD_SIZE_RATIO || padSizeRatio < MIN_PAD_SIZE_RATIO)
    return;

  mPadSizeRatio = padSizeRatio;
  emit padSizeRatioChanged();
  repaint();
}

float QVirtualPad::opacity() const { return mOpacity; }

void QVirtualPad::setOpacity(float opacity) {
  if (mOpacity == opacity)
    return;

  if (opacity > 1 || opacity < 0)
    return;

  mOpacity = opacity;
  mOpacityEffect.setOpacity(opacity);

  emit opacityChanged();
  repaint();
}

QVirtualPad::Axis QVirtualPad::axis() const { return mAxis; }

void QVirtualPad::setAxis(QVirtualPad::Axis axis) {
  if (mAxis == axis)
    return;
  mAxis = axis;
  emit axisChanged();
  repaint();
}

bool QVirtualPad::momentary() const { return mMomentary; }

void QVirtualPad::setMomentary(bool momentary) {
  if (mMomentary == momentary)
    return;
  mMomentary = momentary;
  emit momentaryChanged();
  repaint();
}

int QVirtualPad::borderWidth() const { return mBorderWidth; }

void QVirtualPad::setBorderWidth(int borderWidth) {
  if (mBorderWidth == borderWidth)
    return;

  if (borderWidth > mWidgetFrame.width() / 8 || borderWidth < 1)
    return;

  mBorderWidth = borderWidth;
  emit borderWidthChanged();
  repaint();
  resize();
}

QColor QVirtualPad::borderColor() const { return mBorderColor; }

void QVirtualPad::setBorderColor(const QColor &borderColor) {
  if (mBorderColor == borderColor)
    return;
  mBorderColor = borderColor;
  emit borderColorChanged();
  repaint();
}

QColor QVirtualPad::padFocusColor() const { return mPadFocusColor; }

void QVirtualPad::setPadFocusColor(const QColor &padSpotColor) {
  if (mPadFocusColor == padSpotColor)
    return;
  mPadFocusColor = padSpotColor;
  emit padFocusColorChanged();
  repaint();
}

QColor QVirtualPad::padColor() const { return mPadColor; }

void QVirtualPad::setPadColor(const QColor &padColor) {
  if (mPadColor == padColor)
    return;
  mPadColor = padColor;
  emit padColorChanged();
  repaint();
}

QColor QVirtualPad::backgroundFocusColor() const {
  return mBackgroundFocusColor;
}

void QVirtualPad::setBackgroundFocusColor(const QColor &backgroundSpotColor) {
  if (mBackgroundFocusColor == backgroundSpotColor)
    return;
  mBackgroundFocusColor = backgroundSpotColor;
  emit backgroundFocusColorChanged();
  repaint();
}

QColor QVirtualPad::backgroundColor() const { return mBackgroundColor; }

void QVirtualPad::setBackgroundColor(const QColor &backgroundColor) {
  if (mBackgroundColor == backgroundColor)
    return;
  mBackgroundColor = backgroundColor;
  emit backgroundColorChanged();
  repaint();
}
