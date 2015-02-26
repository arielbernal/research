#ifndef RGSVECTOR_H
#define RGSVECTOR_H

#include <cmath>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <sstream>

namespace rg {

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
  static const __m128 qI;

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

  float norm3d() {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(xmm, xmm, 0xE1)));
  }

  float norm2() { return _mm_cvtss_f32(_mm_dp_ps(xmm, xmm, 0xF1)); }

  void normalize() {
    float v = norm();
    if (fabs(v) > 1E-10) {
      WALIGN __m128 xmm1 = _mm_set1_ps(v);
      xmm = _mm_div_ps(xmm, xmm1);
    }
  }

  // Quaternions
  float4 qconjugate() {
    WALIGN __m128 qs = _mm_set_ps(-z, -y, -x, w);
    return float4(qs);
  }

  // quaternions functions
  // right multiplication p = p * q
  void qmult(const float4 &q) {
    WALIGN __m128 qw = _mm_set_ps(-q.z, -q.y, -q.x, q.w);
    WALIGN __m128 qx = _mm_set_ps(-q.y, q.z, q.w, q.x);
    WALIGN __m128 qy = _mm_set_ps(q.x, q.w, -q.z, q.y);
    WALIGN __m128 qz = _mm_set_ps(q.w, -q.x, q.y, q.z);

    float tw = _mm_cvtss_f32(_mm_dp_ps(qw, xmm, 0xf1));
    float tx = _mm_cvtss_f32(_mm_dp_ps(qx, xmm, 0xf1));
    float ty = _mm_cvtss_f32(_mm_dp_ps(qy, xmm, 0xf1));
    float tz = _mm_cvtss_f32(_mm_dp_ps(qz, xmm, 0xf1));

    xmm = _mm_set_ps(tz, ty, tx, tw);
  }

  // left multiplication p = q * p
  void qmultl(const float4 &q) {
    WALIGN __m128 pw = _mm_set_ps(-z, -y, -x, w);
    WALIGN __m128 px = _mm_set_ps(-y, z, w, x);
    WALIGN __m128 py = _mm_set_ps(x, w, -z, y);
    WALIGN __m128 pz = _mm_set_ps(w, -x, y, z);

    float tw = _mm_cvtss_f32(_mm_dp_ps(pw, q.xmm, 0xf1));
    float tx = _mm_cvtss_f32(_mm_dp_ps(px, q.xmm, 0xf1));
    float ty = _mm_cvtss_f32(_mm_dp_ps(py, q.xmm, 0xf1));
    float tz = _mm_cvtss_f32(_mm_dp_ps(pz, q.xmm, 0xf1));

    xmm = _mm_set_ps(tz, ty, tx, tw);
  }

  // euler to quat
  void euler(float xe, float ye, float ze) {
    float xe2 = xe / 2;  // roll
    float ye2 = ye / 2;  // pitch
    float ze2 = ze / 2;  // yaw
    float cr = cos(xe2);
    float cp = cos(ye2);
    float cy = cos(ze2);
    float sr = sin(xe2);
    float sp = sin(ye2);
    float sy = sin(ze2);
    float cpcy = cp * cy;
    float spsy = sp * sy;
    float spcy = sp * cy;
    float cpsy = cp * sy;
    float tw = cr * cpcy + sr * spsy;
    float tx = sr * cpcy - cr * spsy;
    float ty = cr * spcy + sr * cpsy;
    float tz = cr * cpsy - sr * spcy;
    xmm = _mm_set_ps(tz, ty, tx, tw);
  }

  float4 axis() {
    float4 q(xmm);
    q.normalize();
    float temp_angle = acos(q.w) * 2;
    float vnorm = std::sqrt(1 - q.w * q.w);
    WALIGN __m128 t;
    if (vnorm < 0.001) {
      t = _mm_set_ps(0, 0, 1, 0);
    } else {
      WALIGN __m128 n = _mm_set1_ps(vnorm);
      t = _mm_div_ps(q.xmm, n);
    }
    float4 ret(t);
    ret.w = temp_angle;
    return ret;
  }

  void rotationMatrix(float *Matrix) {
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = w * x;
    float yy = y * y;
    float yz = y * z;
    float yw = w * y;
    float zz = z * z;
    float zw = w * z;

    Matrix[0] = 1 - 2 * (yy + zz);
    Matrix[1] = 2 * (xy - zw);
    Matrix[2] = 2 * (xz + yw);

    Matrix[4] = 2 * (xy + zw);
    Matrix[5] = 1 - 2 * (xx + zz);
    Matrix[6] = 2 * (yz - xw);

    Matrix[8] = 2 * (xz - yw);
    Matrix[9] = 2 * (yz + xw);
    Matrix[10] = 1 - 2 * (xx + yy);

    Matrix[3] = Matrix[7] = Matrix[11] = Matrix[12] = Matrix[13] = Matrix[14] =
        0;
    Matrix[15] = 1;
  }

  void mult(const float M[]) {
    WALIGN __m128 r0 = _mm_set_ps(M[2], M[1], M[0], M[3]);
    WALIGN __m128 r1 = _mm_set_ps(M[6], M[5], M[4], M[7]);
    WALIGN __m128 r2 = _mm_set_ps(M[10], M[9], M[8], M[11]);
    WALIGN __m128 r3 = _mm_set_ps(M[14], M[13], M[12], M[15]);
    float x = _mm_cvtss_f32(_mm_dp_ps(r0, xmm, 0xF1));
    float y = _mm_cvtss_f32(_mm_dp_ps(r1, xmm, 0xF1));
    float z = _mm_cvtss_f32(_mm_dp_ps(r2, xmm, 0xF1));
    float w = _mm_cvtss_f32(_mm_dp_ps(r3, xmm, 0xF1));
    xmm = _mm_set_ps(z, y, x, w);
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

const __m128 float4::mm_one = _mm_set1_ps(1.0f);
const __m128 float4::mm_two = _mm_set1_ps(2.0f);
const __m128 float4::qI = _mm_set_ps(0, 0, 0, 1.0f);

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

// Quaternions
// Multiplication
float4 qmult(const float4 &p, const float4 &q) {
  WALIGN __m128 qw = _mm_set_ps(-q.z, -q.y, -q.x, q.w);
  WALIGN __m128 qx = _mm_set_ps(-q.y, q.z, q.w, q.x);
  WALIGN __m128 qy = _mm_set_ps(q.x, q.w, -q.z, q.y);
  WALIGN __m128 qz = _mm_set_ps(q.w, -q.x, q.y, q.z);

  float tw = _mm_cvtss_f32(_mm_dp_ps(qw, p.xmm, 0xf1));
  float tx = _mm_cvtss_f32(_mm_dp_ps(qx, p.xmm, 0xf1));
  float ty = _mm_cvtss_f32(_mm_dp_ps(qy, p.xmm, 0xf1));
  float tz = _mm_cvtss_f32(_mm_dp_ps(qz, p.xmm, 0xf1));

  WALIGN __m128 xmm = _mm_set_ps(tz, ty, tx, tw);
  return float4(xmm);
}

float4 euler(float xe, float ye, float ze) {
  float xe2 = xe / 2;  // roll
  float ye2 = ye / 2;  // pitch
  float ze2 = ze / 2;  // yaw
  float cr = cos(xe2);
  float cp = cos(ye2);
  float cy = cos(ze2);
  float sr = sin(xe2);
  float sp = sin(ye2);
  float sy = sin(ze2);
  float cpcy = cp * cy;
  float spsy = sp * sy;
  float spcy = sp * cy;
  float cpsy = cp * sy;
  float tw = cr * cpcy + sr * spsy;
  float tx = sr * cpcy - cr * spsy;
  float ty = cr * spcy + sr * cpsy;
  float tz = cr * cpsy - sr * spcy;
  float4 v(tx, ty, tz, tw);
  v.normalize();
  return v;
}

float4 axis(const float4 &q) {
  float4 qtemp(q);
  return qtemp.axis();
}

float4 mult(const float M[], const float4 &q) {
  float4 r(q);
  r.mult(M);
  return float4(r);
}

float4 qrotate(const float4 &q, const float4 &v, bool norm = false) {
  float4 qt(q);
  if (norm) qt.normalize();
  float4 qs = qt.qconjugate();
  float4 rot = qmult(q, qmult(v, qs));
  return rot;
}

}  // namespace rg

#endif  // RGSVECTOR_H
