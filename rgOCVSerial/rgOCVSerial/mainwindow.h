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
   void delay(int ms);
 private slots:
  void openSerialPort();
  void closeSerialPort();
  void writeData(const QByteArray &data);
  void readData();
  void handleError(QSerialPort::SerialPortError error);
  void writeSomedata();
  void pushButton2();
  void btnRead();

  void changeHL(int v);
  void changeHH(int v);
  void changeSL(int v);
  void changeSH(int v);
  void changeVL(int v);
  void changeVH(int v);
  void openNewImage();

 private:
  Ui::MainWindow* ui;
  SettingsDialog* settings;
  QSerialPort* serial;

  Robot* robot;
  bool receiveData;
  char data[2000];
  int bytesRead;
  int bytesTotalRead;

};

#endif  // MAINWINDOW_H
