#ifndef RGGLMOUSEHANDLER_H
#define RGGLMOUSEHANDLER_H

#include <gl/rgGLHeaders.h>

namespace rg {

class GLMouseHandler {
  enum { BUTTON_LEFT = 0, BUTTON_RIGHT = 1, BUTTON_MIDDLE = 2 };
  enum { BUTTON_PRESSED = 1, BUTTON_RELESED = 0 };

 public:
  void set(size_t btn, bool pressed) {
    Button = btn;
    Pressed = pressed;
  }

  void position(float x, float y) {
    x0 = x1;
    y0 = y1;
    x1 = x;
    y1 = y;
  }
  
  float getX() { return x1; }
  float getY() { return y1; }
  float getX0() { return x0; }
  float getY0() { return y0; }
  float dx() { return x1 - x0; }
  float dy() { return y1 - y0; }

  bool isMiddleButtonPressed() {
    return (Button == BUTTON_MIDDLE && Pressed == BUTTON_PRESSED);
  }
  bool isLeftButtonPressed() {
    return (Button == BUTTON_LEFT && Pressed == BUTTON_PRESSED);
  }
  bool isRightButtonPressed() {
    return (Button == BUTTON_RIGHT && Pressed == BUTTON_PRESSED);
  }

 private:
  bool Pressed;
  size_t Button;
  float x0, y0;
  float x1, y1;
};

}  // namespace rg

#endif  // RGGLMOUSEHANDLER_H