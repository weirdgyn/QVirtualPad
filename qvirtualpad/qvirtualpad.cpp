#include "qvirtualpad.h"

#include <QtMath>

QVirtualPad::QVirtualPad(QWidget *parent)
    : QWidget{parent}, mOpacityEffect(new QGraphicsOpacityEffect(this)),
      mBorderWidth(1), mPadSizeRatio(DEF_PAD_SIZE_RATIO), mMomentary(true),
      mBackgroundColor(Qt::red), mBackgroundFocalColor(Qt::white),
      mPadColor(Qt::black), mPadFocalColor(Qt::white), mBorderColor(Qt::black),
      mAxis(Axis::Both), mOpacity(1), mExternalDeadZone(false), mDeadZone(0),
      mMarks(Marks::None) {
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

  QPainter _painter(this);

  _painter.setRenderHint(QPainter::Antialiasing, true);

  drawBackground(_painter);

  drawMarks(_painter);

  drawPad(_painter);
}

void QVirtualPad::mousePressEvent(QMouseEvent *event) {
  mClicked = true;

  updatePosition(event->pos().x() - mFrame.center().x(),
                 event->pos().y() - mFrame.center().y());

  repaint();
}

void QVirtualPad::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event)
  mClicked = false;

  if (mMomentary)
    updatePosition(0, 0);
  else
    updatePosition(event->pos().x() - mFrame.center().x(),
                   event->pos().y() - mFrame.center().y());

  repaint();
}

void QVirtualPad::mouseMoveEvent(QMouseEvent *event) {
  if (!mClicked)
    return;

  updatePosition(event->pos().x() - mFrame.center().x(),
                 event->pos().y() - mFrame.center().y());

  repaint();
}

void QVirtualPad::resize() {
  mFrame = getFrame();

  updatePosition(0, 0);
}

void QVirtualPad::center() { updatePosition(0, 0); }

QRectF QVirtualPad::getFrame() {
  int _size = qMin(this->width(), this->height()) - (mBorderWidth);

  QSizeF _widgetSize = QSizeF(_size, _size);

  QRectF _frame = QRectF();
  _frame.setSize(_widgetSize);

  float _xOffset = (this->width() - _widgetSize.width()) / 2;
  float _yOffset = (this->height() - _widgetSize.height()) / 2;

  QPointF _offsetPoint(_xOffset, _yOffset);
  _frame.moveTopLeft(_offsetPoint);

  return _frame;
}

QPainterPath *QVirtualPad::createMark(double angle, QPointF offset) {
  QPainterPath *_mark = new QPainterPath();

  QPolygonF _polygon;
  QTransform _transform;

  // Triangle
  _polygon << QPointF(-4, 0) << QPointF(0, 8) << QPointF(4, 0)
           << QPointF(-4, 0);
  //

  double _scaleX =
      MARKS_SIZE_RATIO * mFrame.width() / _polygon.boundingRect().width();

  double _scaleY = MARKS_SIZE_RATIO * mFrame.height() /
                   _polygon.boundingRect().height();

  _transform.translate(mFrame.center().x(), mFrame.center().y());
  _transform.translate(offset.x(), offset.y());
  _transform.scale(_scaleX, _scaleY);
  _transform.rotate(angle);

  QPolygonF _final = _transform.map(_polygon);
  _mark->addPolygon(_final);

  return _mark;
}

QPainterPath *QVirtualPad::createMarks() {
  QPainterPath *_marks;
  double _x, _y;

  switch (mMarks) {
  case Marks::NSWE:
    _marks = new QPainterPath();
    switch (mAxis) {
    case Axis::Both:
      _marks->addPath(*createMark(
          90, QPointF((-mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      _marks->addPath(*createMark(
          -90, QPointF((mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      _marks->addPath(*createMark(
          180, QPointF(0, (-mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      _marks->addPath(*createMark(
          0, QPointF(0, (mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      break;
    case Axis::X:
      _marks->addPath(*createMark(
          90, QPointF((-mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      _marks->addPath(*createMark(
          -90, QPointF((mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      break;
    case Axis::Y:
      _marks->addPath(*createMark(
          180, QPointF(0, (-mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      _marks->addPath(*createMark(
          0, QPointF(0, (mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      break;
    }
    break;
  case Marks::Full:
    _marks = new QPainterPath();
    switch (mAxis) {
    case Axis::Both:
      _marks->addPath(*createMark(
          90, QPointF((-mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      _marks->addPath(*createMark(
          -90, QPointF((mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      _marks->addPath(*createMark(
          180, QPointF(0, (-mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      _marks->addPath(*createMark(
          0, QPointF(0, (mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      // Diagonal
      _x = (mFrame.width() / 2) * DEF_MARKS_OFF_RATIO * (M_SQRT2 / 2);
      _y = (mFrame.height() / 2) * DEF_MARKS_OFF_RATIO * (M_SQRT2 / 2);
      _marks->addPath(*createMark(315, QPointF(_x, _y)));

      _marks->addPath(*createMark(45, QPointF(-_x, _y)));

      _marks->addPath(*createMark(225, QPointF(_x, -_y)));

      _marks->addPath(*createMark(135, QPointF(-_x, -_y)));
      break;
    case Axis::X:
      _marks->addPath(*createMark(
          90, QPointF((-mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      _marks->addPath(*createMark(
          -90, QPointF((mFrame.width() / 2) * DEF_MARKS_OFF_RATIO, 0)));
      break;
    case Axis::Y:
      _marks->addPath(*createMark(
          180, QPointF(0, (-mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
      _marks->addPath(*createMark(
          0, QPointF(0, (mFrame.height() / 2) * DEF_MARKS_OFF_RATIO)));
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
  if (x > mFrame.width() / 2)
    x = mFrame.width() / 2;

  if (y > mFrame.height() / 2)
    y = mFrame.height() / 2;

  if (x <= -mFrame.width() / 2)
    x = -mFrame.width() / 2;

  if (y <= -mFrame.width() / 2)
    y = -mFrame.height() / 2;

  if (mExternalDeadZone) {
    float _r = qSqrt(qPow(x, 2) + qPow(y, 2));
    float _r1 = mFrame.width() / 2;

    if (_r > _r1) {
      double _alfa = qAtan2(-y, x) + M_PI / 2;

      if (_alfa != NAN) {
        x = qSin(_alfa) * _r1;
        y = qCos(_alfa) * _r1;
      }
    }
  }

  switch (mAxis) {
  case Axis::Both:
    mPadPosition.setX(mFrame.center().x() + x);
    mPadPosition.setY(mFrame.center().y() + y);
    mValueAxis.setX(x / mFrame.width());
    mValueAxis.setY(y / mFrame.height());
    break;
  case Axis::X:
    mPadPosition.setX(mFrame.center().x() + x);
    mPadPosition.setY(mFrame.center().y());
    mValueAxis.setX(x / mFrame.width());
    mValueAxis.setY(0);
    break;
  case Axis::Y:
    mPadPosition.setX(mFrame.center().x());
    mPadPosition.setY(mFrame.center().y() + y);
    mValueAxis.setX(0);
    mValueAxis.setY(y / mFrame.height());
    break;
  }

  mValueAxis.setX(2 * mValueAxis.x());
  mValueAxis.setY(-2 * mValueAxis.y());

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
                                mFrame.width() * mPadSizeRatio / 2);

  _pad_gradient.setColorAt(0, mPadFocalColor);
  _pad_gradient.setColorAt(1, mPadColor);

  _pad_gradient.setFocalPoint(
      _pad_gradient.center().x() + _pad_gradient.radius() * mPadFocalPosRatio,
      _pad_gradient.center().y() + _pad_gradient.radius() * mPadFocalPosRatio);

  QBrush _pad_brush(_pad_gradient);

  QRectF _rect(mFrame);

  QRectF _pad_rect = QRectF(0, 0, _rect.size().width() * mPadSizeRatio,
                            _rect.size().height() * mPadSizeRatio);

  _pad_rect.moveCenter(mPadPosition);

  painter.setBrush(_pad_brush);

  painter.drawEllipse(_pad_rect);
}

void QVirtualPad::drawBackground(QPainter &painter) {
  QRadialGradient _gradient(mFrame.center(), mFrame.width() / 2);

  _gradient.setColorAt(0, mBackgroundFocalColor);
  _gradient.setColorAt(1, mBackgroundColor);

  _gradient.setFocalPoint(
      _gradient.center().x() + _gradient.radius() * mBackgrounddFocalPosRatio,
      _gradient.center().y() + _gradient.radius() * mBackgrounddFocalPosRatio);

  QBrush _brush(_gradient);

  QPen _pen(mBorderColor);

  QRectF _rect(mFrame);

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
  center();
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
  center();
  repaint();
}

bool QVirtualPad::momentary() const { return mMomentary; }

void QVirtualPad::setMomentary(bool momentary) {
  if (mMomentary == momentary)
    return;
  mMomentary = momentary;
  emit momentaryChanged();
  center();
  repaint();
}

int QVirtualPad::borderWidth() const { return mBorderWidth; }

void QVirtualPad::setBorderWidth(int borderWidth) {
  if (mBorderWidth == borderWidth)
    return;

  if (borderWidth > mFrame.width() / 8 || borderWidth < 1)
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

QColor QVirtualPad::padFocalColor() const { return mPadFocalColor; }

void QVirtualPad::setPadFocalColor(const QColor &padFocalColor) {
  if (mPadFocalColor == padFocalColor)
    return;
  mPadFocalColor = padFocalColor;
  emit padFocalColorChanged();
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

QColor QVirtualPad::backgroundFocalColor() const {
  return mBackgroundFocalColor;
}

void QVirtualPad::setBackgroundFocalColor(const QColor &backgroundFocalColor) {
  if (mBackgroundFocalColor == backgroundFocalColor)
    return;
  mBackgroundFocalColor = backgroundFocalColor;
  emit backgroundFocalColorChanged();
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
