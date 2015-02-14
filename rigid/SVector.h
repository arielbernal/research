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

  // math
  T norm() { return sqrt(x * x + y * y + z * z + w * w); }

  T norm2() { return x * x + y * y + z * z + w * w; }

  void normalize() {
    T n = norm();
    if (fabs(n) > 0.00001) *this /= n;
  }

  // string
  const std::string str() {
    std::ostringstream output;
    output << "[" << x << ", " << y << ", " << z << ", " << w << "]";
    return output.str();
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

template <typename T>
SVector<T> operator+(const SVector<T> &v, const SVector<T> &w) {
  SVector<T> t(v);
  t += w;
  return t;
}

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

//================= (*) ====================
template <typename T, typename K>
SVector<T> operator*(K k, const SVector<T> &v) {
  SVector<T> w(k);
  w *= v;
  return w;
}

template <typename T, typename K>
SVector<T> operator*(const SVector<T> &v, K k) {
  SVector<T> w(v);
  w *= k;
  return w;
}

template <typename T>
SVector<T> operator*(const SVector<T> &v, const SVector<T> &w) {
  SVector<T> t(v);
  t *= w;
  return t;
}

//================= (/) ====================
template <typename T, typename K>
SVector<T> operator/(K k, const SVector<T> &v) {
  SVector<T> w(k);
  w /= v;
  return w;
}

template <typename T, typename K>
SVector<T> operator/(const SVector<T> &v, K k) {
  SVector<T> w(v);
  w /= k;
  return w;
}

template <typename T>
SVector<T> operator/(const SVector<T> &v, const SVector<T> &w) {
  SVector<T> t(v);
  t /= w;
  return t;
}

template <typename T>
T dot3d(const SVector<T> &v, const SVector<T> &w) {
  return v.x * w.x + v.y * w.y + v.z * w.z;
}

template <typename T>
T dot(const SVector<T> &v, const SVector<T> &w) {
  return v.x * w.x + v.y * w.y + v.z * w.z + v.w * w.w;
}

template <typename T>
SVector<T> cross3d(const SVector<T> &v, const SVector<T> &w) {
  SVector<T> x(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z,
               v.x * w.y - v.y * w.x);
  return x;
}

template <typename T>
SVector<T> normal3d(const SVector<T> &v, const SVector<T> &w) {
  SVector<T> x = cross3d(v, w);
  x.normalize();
  return x;
}

template <typename T>
SVector<T> sqrt(const SVector<T> &v) { 
  SVector<T> w;
  w.x = std::sqrt(v.x);
  w.y = std::sqrt(v.y);
  w.z = std::sqrt(v.z);
  w.w = std::sqrt(v.w);
  return w;
}

typedef SVector<float> SVectorf;

}  // namespace SVector

#endif  // SVECTOR_H