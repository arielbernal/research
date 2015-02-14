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
  SVector() : data{0} {}

  SVector(const SVector &t) : data{t.x, t.y, t.z, t.w} {};

  SVector(T x, T y, T z, T w = T(0)) : data{x, y, z, w} {};

  SVector(T v) : data{v, v, v, v} {};

  SVector(T *v) : data{v[0], v[1], v[2], v[3]} {}

  // assigments
  void operator()(const SVector &t) { set(t.x, t.y, t.z, t.w); }

  void operator()(T x, T y, T z, T w = T(0)) { set(x, y, z, w); }

  void operator()(T v) { set(v, v, v, v); }

  void clear() { memset(data, 0, 4 * sizeof(T)); }

  T &operator[](size_t i) { return data[i]; }

  // unary operators
  const SVector &operator+() { return *this; }
  const SVector operator-() {
    SVector t(-x, -y, -z, -w);
    return t;
  }
  const SVector &operator++() {
    ++x;
    ++y;
    ++z;
    ++w;
    return *this;
  }
  const SVector &operator--() {
    --x;
    --y;
    --z;
    --w;
    return *this;
  }

  const SVector operator++(int d) {
    SVector v(*this);
    ++(*this);
    return v;
  }

  const SVector operator--(int d) {
    SVector v(*this);
    --(*this);
    return v;
  }

  // T* mutators
  void operator=(const T *v) { memcpy(data, v, sizeof(T) * 4); }

  // scalar mutators
  void operator=(T v) { set(v, v, v, v); }

  void operator+=(float v) {
    x += v;
    y += v;
    z += v;
    w += v;
  }

  void operator-=(float v) {
    x -= v;
    y -= v;
    z -= v;
    w -= v;
  }

  void operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
  }

  void operator/=(float v) {
    x /= v;
    y /= v;
    z /= v;
    w /= v;
  }

  // vector mutators
  void operator=(const SVector &v) { memcpy(data, v.data, sizeof(T) * 4); }

  void operator+=(const SVector &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
  }

  void operator-=(const SVector &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
  }

  void operator*=(const SVector &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
  }

  void operator/=(const SVector &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
  }

  void print() {
    std::cout << "[" << x << ", " << y << ", " << z << ", " << w << "]\n";
  }

 private:
  void set(T vx, T vy, T vz, T vw = 0) {
    x = vx;
    y = vy;
    z = vz;
    w = vw;
  }
};

// binary operators
// ================= (+) ====================
template <typename T, typename K>
SVector<T> operator+(K k, const SVector<T> &v) {
  SVector<T> w(k);
  w += v;
  return w;
}

template <typename T, typename K>
SVector<T> operator+(const SVector<T> &v, K k) {
  SVector<T> w(k);
  w += v;
  return w;
}

// inline SVector<float> operator+(const SVector<float> &v, const SVector<float> &w) {
//   float4 u;
//   u.xmm = _mm_add_ps(v.xmm, w.xmm);
//   return u;
//}

//================= (-) ====================
template <typename T, typename K>
SVector<T> operator-(K k, const SVector<T> &v) {
  SVector<T> w(k);
  w -= v;
  return w;
}

template <typename T, typename K>
SVector<T> operator-(const SVector<T> &v, K k) {
  SVector<T> w(v);
  w -= k;
  return w;
}

template <typename T>
SVector<T> operator-(const SVector<T> &v, const SVector<T> &w) {
  SVector<T> t(v);
  t -= w;
  return t;
}

typedef SVector<float> SVectorf;

}  // namespace SVector

#endif  // SVECTOR_H