#ifndef FPS_H
#define FPS_H

#include <QTime>
#include <stdint.h>

namespace glp {

class FPS {
public:
  FPS(uint32_t FrameMax = 10) : FrameCount(0), FrameMax(FrameMax), Fps(0) {}

  void start() { FPSTime.start(); }

  void stop() {
    FrameCount = 0;
  }

  void setFrameMax(uint32_t FMax) { FrameMax = FMax; }

  float update() {
    if (FrameCount == FrameMax) {
    //  std::cout << FrameCount << " -  " <<FPSTime.elapsed() << std::endl;
      Fps = float(FrameCount) / FPSTime.elapsed() * 1000.0f;

      FrameCount = 0;
      FPSTime.start();
    } else if (FrameCount == 0) {
      FPSTime.start();
    }
    FrameCount++;
    return Fps;
  }

private:
  QTime FPSTime;
  uint32_t FrameCount;
  uint32_t FrameMax;
  float Fps;
};

} // namespace glp

#endif // FPS_H
