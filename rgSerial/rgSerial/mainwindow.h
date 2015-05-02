#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settingsdialog.h>
#include <robot.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
 private slots:
  void openSerialPort();
  void closeSerialPort();
  void writeData(const QByteArray &data);
  void readData();
  void handleError(QSerialPort::SerialPortError error);
  void writeSomedata();
  void pushButton2();
  void pushButton3();
 private:
  Ui::MainWindow* ui;
  SettingsDialog* settings;
  QSerialPort* serial;

  Robot* robot;
};

#endif  // MAINWINDOW_H
