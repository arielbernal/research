#ifndef KEYPRESS_H
#define KEYPRESS_H

namespace keypress {
#if !WIN32
#include <termios.h>

class BufferToggle {
 public:
  BufferToggle() : toogledOff(false) {}
  void off() {
    if (!toogledOff) {
      tcgetattr(STDIN_FILENO, &t);  // get the current terminal I/O structure
      t.c_lflag &=
          ~ICANON;  // Manipulate the flag bits to do what you want it to do
      tcsetattr(STDIN_FILENO, TCSANOW, &t);  // Apply the new settings
      toogledOff = true;
    }
  }
  void on() {
    if (toogledOff) {
      tcgetattr(STDIN_FILENO, &t);  // get the current terminal I/O structure
      t.c_lflag |=
          ICANON;  // Manipulate the flag bits to do what you want it to do
      tcsetattr(STDIN_FILENO, TCSANOW, &t);  // Apply the new settings
      toogledOff = false;
    }
  }
  bool status() { return toogledOff; }

 private:
  struct termios t;
  bool toogledOff;
};

char getKeypressed() {
  BufferToggle bt;
  bt.off();
  char c = std::getchar();
  bt.on();
  return c;
}

#endif

}  // namespace keypress

#endif  // KEYPRESS_H