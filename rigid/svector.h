#ifndef SVECTOR_H
#define SVECTOR_H

#include <cmath>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <sstream>

namespace svector {
#if WIN32
#define WALIGN __declspec(align(16))
#else
#define WALIGN
#endif

class float4 {
 public:
  WALIGN union {
    struct {
      float w, x, y, z;
    };
    __m128 xmm;
  };

  static const __m128 mm_one;
  static const __m128 mm_two;

  // constructors
  float4() : xmm(_mm_setzero_ps()) {}

  float4(float x, float y, float z, float w = 0.0f)
      : xmm(_mm_set_ps(z, y, x, w)) {};

  float4(const float4 &t) : xmm(t.xmm) {};

  float4(const __m128 &xmm) : xmm(xmm) {};

  float4(float v) : xmm(_mm_set1_ps(v)) {};

  float4(float v[]) : xmm(_mm_set_ps(v[2], v[1], v[0], v[3])) {};

  // assignments
  void operator()(const float4 &t) { xmm = t.xmm; }

  void operator()(float x, float y, float z, float w) {
    xmm = _mm_set_ps(z, y, x, w);
  }

  void operator()(float v[]) { xmm = _mm_set_ps(v[2], v[1], v[0], v[3]); }

  void clear() { xmm = _mm_setzero_ps(); }

  float &operator[](size_t i) {
    switch (i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
    }
    return w;
  }

  // unary operators
  float4 &operator+() { return *this; }
  float4 operator-() {
    float4 t(-x, -y, -z, -w);
    return t;
  }
  float4 &operator++() {
    xmm = _mm_add_ps(xmm, mm_one);
    return *this;
  }
  float4 &operator--() {
    xmm = _mm_sub_ps(xmm, mm_one);
    return *this;
  }
  float4 operator++(int d) {
    float4 v(*this);
    xmm = _mm_add_ps(xmm, mm_one);
    return v;
  }
  float4 operator--(int d) {
    float4 v(*this);
    xmm = _mm_sub_ps(xmm, mm_one);
    return v;
  }

  // mutators
  void operator=(__m128 xmmx) { xmm = xmmx; }
  void operator=(float v[]) { xmm = _mm_set_ps(v[2], v[1], v[0], v[3]); }

  // scalar mutators
  void operator=(float v) { xmm = _mm_set1_ps(v); }
  float4 &operator+=(float v) {
    WALIGN __m128 xmm1 = _mm_set1_ps(v);
    xmm = _mm_add_ps(xmm, xmm1);
    return *this;
  }
  float4 &operator-=(float v) {
    WALIGN __m128 xmm1 = _mm_set1_ps(v);
    xmm = _mm_sub_ps(xmm, xmm1);
    return *this;
  }

  float4 &operator*=(float v) {
    WALIGN __m128 xmm1 = _mm_set1_ps(v);
    xmm = _mm_mul_ps(xmm, xmm1);
    return *this;
  }

  float4 &operator/=(float v) {
    WALIGN __m128 xmm1 = _mm_set1_ps(v);
    xmm = _mm_div_ps(xmm, xmm1);
    return *this;
  }

  // vector mutators
  void operator=(const float4 &v) { xmm = v.xmm; }

  float4 &operator+=(const float4 &v) {
    xmm = _mm_add_ps(xmm, v.xmm);
    return *this;
  }

  float4 &operator-=(const float4 &v) {
    xmm = _mm_sub_ps(xmm, v.xmm);
    return *this;
  }

  float4 &operator*=(const float4 &v) {
    xmm = _mm_mul_ps(xmm, v.xmm);
    return *this;
  }

  float4 &operator/=(const float4 &v) {
    xmm = _mm_div_ps(xmm, v.xmm);
    return *this;
  }

  // math
  float norm() { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(xmm, xmm, 0xF1))); }

  float norm2() { return _mm_cvtss_f32(_mm_dp_ps(xmm, xmm, 0xF1)); }

  void normalize() {
    float v = norm();
    if (fabs(v) > 1E-10) {
      WALIGN __m128 xmm1 = _mm_set1_ps(v);
      xmm = _mm_div_ps(xmm, xmm1);
    }
  }

  // quaternions functions
  float4 &quaternion_mult(const float4 &q) {
    __m128 q0 = _mm_set_ps(q.y, -q.z, q.w, q.x);
    __m128 q1 = _mm_set_ps(-q.x, q.w, q.z, q.y);
    __m128 q2 = _mm_set_ps(q.w, q.x, -q.y, q.z);
    __m128 q3 = _mm_set_ps(-q.z, -q.y, -q.x, q.w);

    float tx = _mm_cvtss_f32(_mm_dp_ps(q0, xmm, 0xf1));
    float ty = _mm_cvtss_f32(_mm_dp_ps(q1, xmm, 0xf1));
    float tz = _mm_cvtss_f32(_mm_dp_ps(q2, xmm, 0xf1));
    float tw = _mm_cvtss_f32(_mm_dp_ps(q3, xmm, 0xf1));

    xmm = _mm_set_ps(tz, ty, tx, tw);
    return *this;
  }

  // string
  const std::string str() {
    std::ostringstream output;
    output << "[" << x << ", " << y << ", " << z << ", " << w << "]";
    return output.str();
  }
  void print() { std::cout << str() << std::endl; }
  friend std::ostream &operator<<(std::ostream &os, const float4 &v);
};

std::ostream &operator<<(std::ostream &os, const float4 &v) {
  os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
  return os;
}

//
//

//
//  inline void euler(float xe, float ye, float ze) {
//    __m128 mmh = _mm_set_ps(ze, ye, xe, 0);
//    mmh = _mm_div_ps(mmh, mm_two);
//#if WIN32
//    __declspec(align(16)) float h[4] = {0};
//#else
//    float h[4] = {0};
//#endif
//    _mm_store_ps(h, mmh);
//
//    float c[3] = {float(cos(h[1])), float(cos(h[2])), float(cos(h[3]))};
//    float s[3] = {float(sin(h[1])), float(sin(h[2])), float(sin(h[3]))};
//    float tw = c[0] * c[1] * c[2] + s[0] * s[2] * s[1];
//    float tx = s[0] * c[1] * c[2] - c[0] * s[2] * s[1];
//    float ty = c[0] * s[1] * c[2] + s[0] * c[2] * s[1];
//    float tz = c[0] * c[1] * s[2] - s[0] * s[2] * c[1];
//    xmm = _mm_set_ps(tz, ty, tx, tw);
//    normalize();
//  }
//
//  inline void rotationMatrix(float *Matrix) {
//    float xx = x * x;
//    float xy = x * y;
//    float xz = x * z;
//    float xw = w * x;
//    float yy = y * y;
//    float yz = y * z;
//    float yw = w * y;
//    float zz = z * z;
//    float zw = w * z;
//
//    Matrix[0] = 1 - 2 * (yy + zz);
//    Matrix[1] = 2 * (xy - zw);
//    Matrix[2] = 2 * (xz + yw);
//
//    Matrix[4] = 2 * (xy + zw);
//    Matrix[5] = 1 - 2 * (xx + zz);
//    Matrix[6] = 2 * (yz - xw);
//
//    Matrix[8] = 2 * (xz - yw);
//    Matrix[9] = 2 * (yz + xw);
//    Matrix[10] = 1 - 2 * (xx + yy);
//
//    Matrix[3] = Matrix[7] = Matrix[11] = Matrix[12] = Matrix[13] = Matrix[14]
// =
//        0;
//    Matrix[15] = 1;
//  }
//
//  inline float4 axis() {
//    float temp_angle = acos(w) * 2;
//    float vnorm = norm(0xE1);
//    __m128 t;
//    if (fabs(vnorm) < 0.001) {
//      t = _mm_set_ps(0, 0, 1, 0);
//    } else {
//      __m128 n = _mm_set1_ps(vnorm);
//      t = _mm_div_ps(xmm, n);
//    }
//    float4 ret(t);
//    ret.w = temp_angle;
//    return ret;
//  }
//
//};
//
const __m128 float4::mm_one = _mm_set1_ps(1.0f);
const __m128 float4::mm_two = _mm_set1_ps(2.0f);

// binary operators
//================= (+) ====================
float4 operator+(float k, const float4 &v) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_add_ps(xmm, v.xmm);
  return float4(xmm1);
}

float4 operator+(const float4 &v, float k) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_add_ps(v.xmm, xmm);
  return float4(xmm1);
}

float4 operator+(const float4 &v, const float4 &w) {
  WALIGN __m128 xmm = _mm_add_ps(v.xmm, w.xmm);
  return float4(xmm);
}

//================= (-) ====================
float4 operator-(float k, const float4 &v) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_sub_ps(xmm, v.xmm);
  return float4(xmm1);
}

float4 operator-(const float4 &v, float k) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_sub_ps(v.xmm, xmm);
  return float4(xmm1);
}

float4 operator-(const float4 &v, const float4 &w) {
  WALIGN __m128 xmm = _mm_sub_ps(v.xmm, w.xmm);
  return float4(xmm);
}

//================= (*) ====================
float4 operator*(float k, const float4 &v) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_mul_ps(xmm, v.xmm);
  return float4(xmm1);
}

float4 operator*(const float4 &v, float k) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_mul_ps(v.xmm, xmm);
  return float4(xmm1);
}

float4 operator*(const float4 &v, const float4 &w) {
  WALIGN __m128 xmm = _mm_mul_ps(v.xmm, w.xmm);
  return float4(xmm);
}

//================= (/) ====================
float4 operator/(float k, const float4 &v) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_div_ps(xmm, v.xmm);
  return float4(xmm1);
}

float4 operator/(const float4 &v, float k) {
  WALIGN __m128 xmm = _mm_set1_ps(k);
  WALIGN __m128 xmm1 = _mm_div_ps(v.xmm, xmm);
  return float4(xmm1);
}

float4 operator/(const float4 &v, const float4 &w) {
  WALIGN __m128 xmm = _mm_div_ps(v.xmm, w.xmm);
  return float4(xmm);
}

// mathematical functions
float dot3d(const float4 &v, const float4 &w) {
  return _mm_cvtss_f32(_mm_dp_ps(v.xmm, w.xmm, 0xE1));
}

float dot(const float4 &v, const float4 &w) {
  return _mm_cvtss_f32(_mm_dp_ps(v.xmm, w.xmm, 0xF1));
}

float4 cross3d(const float4 &v, const float4 &w) {
  WALIGN __m128 r0 = _mm_sub_ps(
      _mm_mul_ps(v.xmm, _mm_shuffle_ps(w.xmm, w.xmm, _MM_SHUFFLE(1, 3, 2, 0))),
      _mm_mul_ps(w.xmm, _mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(1, 3, 2, 0))));
  WALIGN __m128 r1 = _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(1, 3, 2, 0));
  return float4(r1);
}

float4 normal3d(const float4 &v, const float4 &w) {
  float4 x = cross3d(v, w);
  x.normalize();
  return x;
}

float4 sqrt(const float4 &v) {
  WALIGN __m128 xmm = _mm_sqrt_ps(v.xmm);
  return float4(xmm);
}

// inline float4 quaternion_mult(const float4 &v, const float4 &w) {
//  float4 x(v);
//  x.quaternion_mult(w);
//  return x;
//}

}  // namespace svector

#endif  // SVECTOR_H
