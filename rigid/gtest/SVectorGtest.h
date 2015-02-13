#ifndef SVECTORGTEST_H
#define SVECTORGTEST_H

using namespace SVector;

class SVectorfTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  void compare(const SVectorf &a, float x, float y, float z,
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
  // inline SVector() : data{0} {}
  SVectorf a;
  compare(a, 0, 0, 0, 0);
}

TEST_F(SVectorfTest, Constructors1) {
  // inline SVector(T x, T y, T z, T w = T(0)) : data{x, y, z, w} {};
  SVectorf b(2, 3, 4, 5);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Constructors1a) {
  // inline SVector(T x, T y, T z, T w = T(0)) : data{x, y, z, w} {};
  SVectorf b(2, 3, 4);
  compare(b, 2, 3, 4, 0);
}

TEST_F(SVectorfTest, Constructors2) {
  // inline SVector(const SVector &t) : data{t.z, t.y, t.x, t.w} {};
  SVectorf b(2, 3, 4, 5);
  SVectorf c(b);
  compare(b, c);
}

TEST_F(SVectorfTest, Constructors3) {
  // inline SVector(T v) : data{v, v, v, v} {};
  SVectorf b(2);
  compare(b, 2, 2, 2, 2);
}

TEST_F(SVectorfTest, Constructors4) {
  // inline SVector(T *v) : data{v[0], v[1], v[2], v[3]} {}
  float v[4] = {2, 3, 4, 5};
  SVectorf b(v);
  compare(b, 2, 3, 4, 5);
}

#endif // SVECTORGTEST_H