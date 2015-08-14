#include <serialcom.h>


void SerialCom::writeMotors() {
  if (serial->isOpen()) {
    std::cout << "Here" << std::endl;
    char v[2] = {char(-vMotors[0]), char(-vMotors[1])};
    serial->write(v, 2);
  }
}
