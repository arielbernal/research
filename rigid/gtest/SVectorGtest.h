#ifndef SVECTORGTEST_H
#define SVECTORGTEST_H

#include "../svector.h"

using namespace svector;

class Test_float4 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  void compare(float x, float y, float z, float w, const float4 &a) {
    EXPECT_EQ(x, a.x);
    EXPECT_EQ(y, a.y);
    EXPECT_EQ(z, a.z);
    EXPECT_EQ(w, a.w);
  }
  void compare(const float4 &A, const float4 &B) {
    EXPECT_EQ(A.x, B.x);
    EXPECT_EQ(A.y, B.y);
    EXPECT_EQ(A.z, B.z);
    EXPECT_EQ(A.w, B.w);
  }
};

TEST_F(Test_float4, Constructors) {
  float4 a;
  compare(0, 0, 0, 0, a);
  float4 b(1, 2, 3, 4);
  compare(1, 2, 3, 4, b);
  float4 c(b);
  compare(1, 2, 3, 4, c);
  float4 d(3);
  compare(3, 3, 3, 3, d);
  float f[4] = {2, 3, 4, 5};
  float4 e(f);
  compare(2, 3, 4, 5, e);
  __m128 xmm = _mm_set_ps(2, 3, 4, 5);
  float4 g(xmm);
  compare(4, 3, 2, 5, g);
}

TEST_F(Test_float4, Assignment) {
  float4 a;
  a(1, 2, 3, 4);
  compare(1, 2, 3, 4, a);
  float4 b;
  b(a);
  compare(1, 2, 3, 4, b);
  float f[4] = {2, 3, 4, 5};
  float4 e;
  e(f);
  compare(2, 3, 4, 5, e);
  e.clear();
  compare(0, 0, 0, 0, e);
  float4 d(2, 3, 4, 5);
  EXPECT_EQ(4, d[2]);
  d[1] = 5;
  compare(2, 5, 4, 5, d);
}

TEST_F(Test_float4, UnaryOperators) {
  float4 a(1, 2, 3, 4);
  float4 b;
  // float4 &operator+()
  b = +a;
  compare(a, b);
  // float4 operator-()
  b = -a;
  compare(-1, -2, -3, -4, b);
  // float4 operator++()
  b = ++a;
  compare(2, 3, 4, 5, a);
  compare(2, 3, 4, 5, b);
  // float4 operator--();
  b = --a;
  compare(1, 2, 3, 4, a);
  compare(1, 2, 3, 4, b);
  // float4 operator++(int)
  b = a++;
  compare(2, 3, 4, 5, a);
  compare(1, 2, 3, 4, b);
  // float4 operator--(int);
  b = a--;
  compare(1, 2, 3, 4, a);
  compare(2, 3, 4, 5, b);
}

TEST_F(Test_float4, Mutators) {
  float v[4] = {1, 2, 3, 4};
  float4 b;
  b = v;
  compare(1, 2, 3, 4, b);
}

TEST_F(Test_float4, ScalarMutators) {
  float4 b;
  b = 3;
  compare(3, 3, 3, 3, b);
  b(1, 2, 3, 4);
  b += 5;
  compare(6, 7, 8, 9, b);
  b -= 5;
  compare(1, 2, 3, 4, b);
  b *= 2;
  compare(2, 4, 6, 8, b);
  b /= 2;
  compare(1, 2, 3, 4, b);
}

TEST_F(Test_float4, VectorMutators) {
  float4 b;
  float4 a(2, 3, 4, 5);
  float4 c(2, 2, 2, 2);
  b = a;
  compare(2, 3, 4, 5, b);
  b += c;
  compare(4, 5, 6, 7, b);
  b -= c;
  compare(2, 3, 4, 5, b);
  b *= c;
  compare(4, 6, 8, 10, b);
  b /= c;
  compare(2, 3, 4, 5, b);
}

TEST_F(Test_float4, BinaryOperatorsPlus) {
  float4 a(2, 3, 4, 5);
  float4 b;
  b = a + 2.0f;
  compare(4, 5, 6, 7, b);
  b = 2.0f + a;
  compare(4, 5, 6, 7, b);
  float4 c;
  c = a + b;
  compare(6, 8, 10, 12, c);
}

TEST_F(Test_float4, BinaryOperatorsMinus) {
  float4 a(2, 3, 4, 5);
  float4 b;
  b = a - 2.0f;
  compare(0, 1, 2, 3, b);
  b = 2.0f - a;
  compare(0, -1, -2, -3, b);
  float4 c;
  c = a - b;
  compare(2, 4, 6, 8, c);
}

TEST_F(Test_float4, BinaryOperatorsProduct) {
  float4 a(2, 3, 4, 5);
  float4 b;
  b = a * 2.0f;
  compare(4, 6, 8, 10, b);
  b = 2.0f * a;
  compare(4, 6, 8, 10, b);
  float4 c;
  c = a * b;
  compare(8, 18, 32, 50, c);
}

TEST_F(Test_float4, BinaryOperatorsDivision) {
  float4 a(2, 3, 4, 5);
  float4 b;
  b = a / 2.0f;
  compare(1, 1.5, 2, 2.5, b);
  b = 2.0f / a;
  compare(1, 2.0f / 3.0f, 2.0f / 4.0f, 2.0f / 5.0f, b);
  b(1, 2, 3, 4);
  float4 c;
  c = a / b;
  compare(2.0f / 1.0f, 3.0f / 2.0f, 4.0f / 3.0f, 5.0f / 4.0f, c);
}

TEST_F(Test_float4, Norm) {
  float4 a(3, 4, 0, 0);
  float n = a.norm();
  EXPECT_EQ(5, n);
}

TEST_F(Test_float4, Norm2) {
  float4 a(3, 4, 0, 0);
  float n = a.norm2();
  EXPECT_EQ(25, n);
}

TEST_F(Test_float4, Normalize) {
  float4 a(3, 4, 0, 0);
  a.normalize();
  compare(3.0f / 5.0f, 4.0f / 5.0f, 0, 0, a);
}

TEST_F(Test_float4, StreamOperator) {
  float4 a(3, 4, 5, 6);
  EXPECT_EQ("[3, 4, 5, 6]", a.str());
}

TEST_F(Test_float4, DotProduct) {
  float4 a(1, 2, 3, 4);
  float4 b(2, 3, 4, 5);
  EXPECT_EQ(20, dot3d(a, b));
  EXPECT_EQ(40, dot(a, b));
}

TEST_F(Test_float4, CrossProduct3d) {
  float4 a(1, 0, 0);
  float4 b(0, 1, 0);
  float4 c = cross3d(a, b);
  compare(0, 0, 1, 0, c);

  a(1, 2, 3, 4);
  b(5, 6, 7, 8);
  c = cross3d(a, b);
  compare(-4, 8, -4, 0, c);
}

TEST_F(Test_float4, Normal3d) {
  float4 a(2, 0, 0);
  float4 b(0, 2, 0);
  float4 c = normal3d(a, b);
  compare(0, 0, 1, 0, c);
}

TEST_F(Test_float4, Sqrt) {
  float4 a(9, 4, 16);
  float4 b = sqrt(a);
  compare(3, 2, 4, 0, b);
}

#endif  // SVECTORGTEST_H