#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QColorDialog mColorDialog;

protected:
  void showEvent(QShowEvent* event);

private slots:
  void OnPositionUpdate(QPointF position);
  void on_momentary_stateChanged(int arg1);
  void on_axis_currentTextChanged(const QString &arg1);
  void on_padsizeratio_valueChanged(double arg1);
  void on_borderColor_clicked();
  void on_backgroundColor_clicked();
  void on_padColor_clicked();
  void on_backgroundFocusColor_clicked();
  void on_padFocusColor_clicked();
  void on_borderwidth_valueChanged(double arg1);
  void on_opacity_valueChanged(double arg1);
  void on_deadZoneRadius_valueChanged(double arg1);
  void on_externalDeadzoneCheckBox_stateChanged(int arg1);
  void on_marks_currentTextChanged(const QString &arg1);
};
#endif // MAINWINDOW_H
