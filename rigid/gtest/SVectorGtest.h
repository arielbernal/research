#ifndef SVECTORGTEST_H
#define SVECTORGTEST_H

using namespace SVector;

class SVectorfTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  void compare(const SVectorf &a, float x, float y = 0, float z = 0,
               float w = 0) {
    EXPECT_EQ(x, a.x);
    EXPECT_EQ(y, a.y);
    EXPECT_EQ(z, a.z);
    EXPECT_EQ(w, a.w);
  }
  void compare(const SVectorf &A, const SVectorf &B) {
    EXPECT_EQ(A.x, B.x);
    EXPECT_EQ(A.y, B.y);
    EXPECT_EQ(A.z, B.z);
    EXPECT_EQ(A.w, B.w);
  }
};

TEST_F(SVectorfTest, Constructors0) {
  // SVector() : data{0}
  SVectorf a;
  compare(a, 0, 0, 0, 0);
}

TEST_F(SVectorfTest, Constructors1) {
  // SVector(T x, T y, T z, T w = T(0))
  SVectorf b(2, 3, 4, 5);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Constructors1a) {
  // SVector(T x, T y, T z, T w = T(0))
  SVectorf b(2, 3, 4);
  compare(b, 2, 3, 4, 0);
}

TEST_F(SVectorfTest, Constructors2) {
  // SVector(const SVector &t)
  SVectorf b(2, 3, 4, 5);
  SVectorf c(b);
  compare(b, c);
}

TEST_F(SVectorfTest, Constructors3) {
  // SVector(T v)
  SVectorf b(2);
  compare(b, 2, 2, 2, 2);
}

TEST_F(SVectorfTest, Constructors4) {
  // SVector(T *v)
  float v[4] = {2, 3, 4, 5};
  SVectorf b(v);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Assignments0) {
  // void operator()(const SVector &t)
  SVectorf a(1, 2, 3, 4);
  SVectorf b;
  b(a);
  compare(b, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, Assignments1) {
  // void operator()(T x, T y, T z, T w = T(0))
  SVectorf a(1, 2, 3, 4);
  a(2, 3, 4);
  compare(a, 2, 3, 4, 0);
  a(4);
  compare(a, 4, 4, 4, 4);
}

TEST_F(SVectorfTest, Assignments2) {
  // void clear()
  SVectorf a(1, 2, 3, 4);
  a.clear();
  compare(a, 0);
}

TEST_F(SVectorfTest, Assignments3) {
  // T &operator[](size_t i)
  SVectorf a(1, 2, 3, 4);
  EXPECT_EQ(3, a[2]);
  a[1] = 5;
  compare(a, 1, 5, 3, 4);
}

TEST_F(SVectorfTest, UnaryOperators0) {
  SVectorf a(1, 2, 3, 4);
  SVectorf b;
  // SVector operator+()
  b = +a;
  compare(b, a);
  // SVector operator-()
  b = -a;
  compare(b, -1, -2, -3, -4);
}

TEST_F(SVectorfTest, UnaryOperators1) {
  SVectorf a(1, 2, 3, 4);
  // SVector operator++()
  ++a;
  compare(a, 2, 3, 4, 5);
  // SVector operator--()
  --a;
  compare(a, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, UnaryOperators2) {
  SVectorf a(1, 2, 3, 4);
  SVectorf b;
  // SVector operator++(int)
  b = a++;
  compare(a, 2, 3, 4, 5);
  compare(b, 1, 2, 3, 4);
  // SVector operator--(int)
  b = a--;
  compare(a, 1, 2, 3, 4);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Mutators) {
  float v[4] = {1, 2, 3, 4};
  SVectorf b;
  b = v;
  compare(b, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, ScalarMutators) {
  SVectorf b;
  // void operator=(T v)
  b = 3;
  compare(b, 3, 3, 3, 3);
  b(1, 2, 3, 4);
  // SVector &operator+=(float v)
  b += 5;
  compare(b, 6, 7, 8, 9);
  b -= 5;
  compare(b, 1, 2, 3, 4);
  b *= 2;
  compare(b, 2, 4, 6, 8);
  b /= 2;
  compare(b, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, VectorMutators) {
  SVectorf b;
  SVectorf a(2, 3, 4, 5);
  SVectorf c(2, 2, 2, 2);
  // void operator=(T v)
  b = a;
  compare(b, 2, 3, 4, 5);
  b += c;
  compare(b, 4, 5, 6, 7);
  b -= c;
  compare(b, 2, 3, 4, 5);
  b *= c;
  compare(b, 4, 6, 8, 10);
  b /= c;
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, BinaryOperatorsPlus) {
  SVectorf a(2, 3, 4, 5);
  SVectorf b;
  b = a + 2.0f;
  compare(b, 4, 5, 6, 7);
  b = 2.0f + a;
  compare(b, 4, 5, 6, 7);
  SVectorf c;
  c = a + b;
  compare(c, 6, 8, 10, 12);
}

TEST_F(SVectorfTest, BinaryOperatorsMinus) {
  SVectorf a(2, 3, 4, 5);
  SVectorf b;
  b = a - 2.0f;
  compare(b, 0, 1, 2, 3);
  b = 2.0f - a;
  compare(b, 0, -1, -2, -3);
  SVectorf c;
  c = a - b;
  compare(c, 2, 4, 6, 8);
}

TEST_F(SVectorfTest, BinaryOperatorsProduct) {
  SVectorf a(2, 3, 4, 5);
  SVectorf b;
  b = a * 2.0f;
  compare(b, 4, 6, 8, 10);
  b = 2.0f * a;
  compare(b, 4, 6, 8, 10);
  SVectorf c;
  c = a * b;
  compare(c, 8, 18, 32, 50);
}

TEST_F(SVectorfTest, BinaryOperatorsDivision) {
  SVectorf a(2, 3, 4, 5);
  SVectorf b;
  b = a / 2.0f;
  compare(b, 1, 1.5, 2, 2.5);
  b = 2.0f / a;
  compare(b, 1, 2.0f / 3.0f, 2.0f / 4.0f, 2.0f / 5.0f);
  b(1, 2, 3, 4);
  SVectorf c;
  c = a / b;
  compare(c, 2.0f / 1.0f, 3.0f / 2.0f, 4.0f / 3.0f, 5.0f / 4.0f);
}

TEST_F(SVectorfTest, Norm) {
  SVectorf a(3, 4, 0, 0);
  float n = a.norm();
  EXPECT_EQ(5, n);
}

TEST_F(SVectorfTest, Norm2) {
  SVectorf a(3, 4, 0, 0);
  float n = a.norm2();
  EXPECT_EQ(25, n);
}

TEST_F(SVectorfTest, Normalize) {
  SVectorf a(3, 4, 0, 0);
  a.normalize();
  compare(a, 3.0f / 5.0f, 4.0f / 5.0f, 0, 0);
}

TEST_F(SVectorfTest, DotProduct) {
  SVectorf a(1, 2, 3, 4);
  SVectorf b(2, 3, 4, 5);
  EXPECT_EQ(20, dot3d(a, b));
  EXPECT_EQ(40, dot(a, b));
}

TEST_F(SVectorfTest, CrossProduct3d) {
  SVectorf a(1, 0, 0);
  SVectorf b(0, 1, 0);
  SVectorf c = cross3d(a, b);
  compare(c, 0, 0, 1, 0);
}

TEST_F(SVectorfTest, Sqrt) {
  SVectorf a(9, 4, 16);
  SVectorf b = sqrt(a);
  compare(b, 3, 2, 4, 0);
}

TEST_F(SVectorfTest, Normal3d) {
  SVectorf a(2, 0, 0);
  SVectorf b(0, 2, 0);
  SVectorf c = normal3d(a, b);
  compare(c, 0, 0, 1, 0);
}

TEST_F(SVectorfTest, String) {
  SVectorf a(1, 2, 3, 4);
  EXPECT_EQ("[1, 2, 3, 4]", a.str());
}

#endif  // SVECTORGTEST_H