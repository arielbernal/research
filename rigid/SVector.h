#ifndef SVECTOR_H
#define SVECTOR_H

#include <cmath>
#include <sstream>
#include <cstring>

namespace SVector {

template <typename T>
class SVector {
 public:
  union {
    struct {
      T x, y, z, w;
    };
    T data[4];
  };
  // constructors
  inline SVector() : data{0} {}

  inline SVector(const SVector &t) : data{t.x, t.y, t.z, t.w} {};

  inline SVector(T x, T y, T z, T w = T(0)) : data{x, y, z, w} {};

  inline SVector(T v) : data{v, v, v, v} {};

  inline SVector(T *v) : data{v[0], v[1], v[2], v[3]} {}

  // assigments
  inline void operator()(const SVector &t) { set(t.x, t.y, t.z, t.w); }

  inline void operator()(T x, T y, T z, T w = T(0)) { set(x, y, z, w); }

  inline void zero() { memset(data, 0, 4 * sizeof(T)); }

  // random access
  inline T &operator[](size_t i) { return data[i]; }

  // unary operators
  inline SVector operator+() { return *this; }
  inline SVector operator-() {
    SVector t(-x, -y, -z, -w);
    return t;
  }
  inline SVector operator++() {
    ++data[0];
    ++data[1];
    ++data[2];
    ++data[3];
    return *this;
  }
  inline SVector operator--() {
    --data[0];
    --data[1];
    --data[2];
    --data[3];
    return *this;
  }

  void print() {
    std::cout << "[" << x << ", " << y << ", " << z << ", " << w << "]\n";
  }

 private:
  void set(T x, T y, T z, T w = 0) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
  }
};

typedef SVector<float> SVectorf;

}  // namespace SVector

#endif  // SVECTOR_H