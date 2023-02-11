#include <QGraphicsOpacityEffect>
#include <QtMath>

#include "mainwindow.h"
#include "qvirtualpad.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->vg, &QVirtualPad::positionUpdate, this,
          &MainWindow::OnPositionUpdate);

  mColorDialog.setModal(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showEvent(QShowEvent *event) {
  Q_UNUSED(event);
  ui->momentary->setCheckState(ui->vg->momentary() ? Qt::CheckState::Checked
                                                   : Qt::CheckState::Unchecked);

  ui->borderwidth->setValue(ui->vg->borderWidth());
  ui->opacity->setValue(ui->vg->opacity());
  ui->padsizeratio->setValue(ui->vg->padSizeRatio());
  ui->deadZoneRadius->setValue(ui->vg->deadZone());
  ui->marks->setCurrentText(QVirtualPad::MarksToString(ui->vg->marks()));
  ui->axis->setCurrentText(QVirtualPad::AxisToString(ui->vg->axis()));
}

void MainWindow::OnPositionUpdate(QPointF position) {
  ui->X->setText(QString::number(position.x()));
  ui->Y->setText(QString::number(position.y()));
  ui->lblRadiusValue->setText(QString::number(qSqrt(qPow(position.x(),2) + qPow(position.y(),2))));
}

void MainWindow::on_momentary_stateChanged(int arg1) {
  ui->vg->setMomentary((bool)arg1);
}

void MainWindow::on_axis_currentTextChanged(const QString &arg1) {
  ui->vg->setAxis(QVirtualPad::StringToAxis(arg1));
}

void MainWindow::on_padsizeratio_valueChanged(double arg1) {
  ui->vg->setPadSizeRatio(arg1);
}

void MainWindow::on_borderColor_clicked() {
  mColorDialog.setCurrentColor(ui->vg->borderColor());

  auto conn = std::make_shared<QMetaObject::Connection>();

  *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                  [this, conn]() {
                    ui->vg->setBorderColor(mColorDialog.currentColor());
                    disconnect(*conn);
                  });

  mColorDialog.show();
}

void MainWindow::on_backgroundColor_clicked() {
  mColorDialog.setCurrentColor(ui->vg->backgroundColor());

  auto conn = std::make_shared<QMetaObject::Connection>();

  *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                  [this, conn]() {
                    ui->vg->setBackgroundColor(mColorDialog.currentColor());
                    disconnect(*conn);
                  });

  mColorDialog.show();
}

void MainWindow::on_padColor_clicked() {
  mColorDialog.setCurrentColor(ui->vg->padColor());

  auto conn = std::make_shared<QMetaObject::Connection>();

  *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                  [this, conn]() {
                    ui->vg->setPadColor(mColorDialog.currentColor());
                    disconnect(*conn);
                  });

  mColorDialog.show();
}

void MainWindow::on_backgroundFocusColor_clicked() {
  mColorDialog.setCurrentColor(ui->vg->backgroundFocusColor());

  auto conn = std::make_shared<QMetaObject::Connection>();

  *conn = connect(
      &mColorDialog, &QColorDialog::colorSelected, this, [this, conn]() {
        ui->vg->setBackgroundFocusColor(mColorDialog.currentColor());
        disconnect(*conn);
      });

  mColorDialog.show();
}

void MainWindow::on_padFocusColor_clicked() {
  mColorDialog.setCurrentColor(ui->vg->padFocusColor());

  auto conn = std::make_shared<QMetaObject::Connection>();

  *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                  [this, conn]() {
                    ui->vg->setPadFocusColor(mColorDialog.currentColor());
                    disconnect(*conn);
                  });

  mColorDialog.show();
}

void MainWindow::on_borderwidth_valueChanged(double arg1) {
  ui->vg->setBorderWidth(arg1);
}

void MainWindow::on_opacity_valueChanged(double arg1) {
  ui->vg->setOpacity(arg1);
}

void MainWindow::on_deadZoneRadius_valueChanged(double arg1) {
  ui->vg->setDeadZone(arg1);
}

void MainWindow::on_externalDeadzoneCheckBox_stateChanged(int arg1)
{
    ui->vg->setExternalDeadZone((bool)arg1);
}

void MainWindow::on_marks_currentTextChanged(const QString &arg1)
{
    ui->vg->setMarks(QVirtualPad::StringToMarks(arg1));
}

