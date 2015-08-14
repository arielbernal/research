#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QtCore>
#include <QSerialPort>

class SerialCom : public QObject {
  Q_OBJECT

 public:
  explicit SerialCom(QObject* parent = 0)
      : QObject(parent), serial(new QSerialPort) {
    // connect(this, SIGNAL(timeout()), this, SLOT(writeMotors()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(showTime()));
    vMotors[0] = 0;
    vMotors[1] = 0;
    timer.start(50);
  }

  void openSerialPort() {
    serial->setPortName("COM11");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
      std::cout << "Serial Port Open" << std::endl;
    } else {
      std::cout << "Serial Port Error" << std::endl;
    }
  }
 private slots:
  void showTime() {
    qDebug() << "Current date and time:"
             << QDateTime::currentDateTime().toString();
  }

 private:
  QSerialPort* serial;
  char vMotors[2];
  QTimer timer;
};
#endif  // SERIALCOM_H
